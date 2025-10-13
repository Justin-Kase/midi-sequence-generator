#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiSequenceGeneratorAudioProcessor::MidiSequenceGeneratorAudioProcessor()
: juce::AudioProcessor (BusesProperties().withOutput("Out", juce::AudioChannelSet::stereo(), true))
{}

void MidiSequenceGeneratorAudioProcessor::prepareToPlay (double sampleRate, int) {
    sampleRate_ = sampleRate;
}

void MidiSequenceGeneratorAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiSequenceGeneratorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() != juce::AudioChannelSet::disabled();
}
#endif

void MidiSequenceGeneratorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) {
    buffer.clear();

    juce::AudioPlayHead* ph = getPlayHead();
    juce::AudioPlayHead::CurrentPositionInfo info;
    if (ph != nullptr && ph->getCurrentPosition (info)) {
        if (info.isPlaying && info.bpm > 0.0) {
            const int ppq = 480; // internal grid
            const int steps = params_.getRawParameterValue("steps")->load();
            const float swing = params_.getRawParameterValue("swing")->load();
            const float density = params_.getRawParameterValue("density")->load();
            const int root = (int) params_.getRawParameterValue("root")->load();
            const int octs = (int) params_.getRawParameterValue("octaves")->load();

            std::vector<int> major{0,2,4,5,7,9,11};
            generator_.configure(ppq, steps, root, major, swing, density, octs);

            const int numSamples = buffer.getNumSamples();
            const double samplesPerBeat = (sampleRate_ * 60.0) / info.bpm;
            const double ppqPerSample = 1.0 / samplesPerBeat; // beats per sample

            const double startPPQ = info.ppqPosition; // at start of buffer
            const double endPPQ = startPPQ + numSamples * ppqPerSample; // beats

            // Generate one bar of pattern in PPQ ticks, then wrap by floor(startPPQ)
            auto events = generator_.generateBars(1);
            const double ticksPerBeat = (double) ppq;

            for (const auto& ev : events) {
                double evStartBeat = (double) ev.startTick / ticksPerBeat; // beats into bar
                double evEndBeat = (double) (ev.startTick + ev.lengthTick) / ticksPerBeat;

                // Map to absolute beat timeline by repeating every 1 bar
                double barStart = std::floor(startPPQ);
                for (int rep = -1; rep <= 1; ++rep) {
                    double absOn = barStart + rep + evStartBeat;
                    double absOff = barStart + rep + evEndBeat;

                    // If within this buffer's PPQ window, schedule
                    if (absOn < endPPQ && absOff > startPPQ) {
                        int onSample = (int) juce::jlimit(0, numSamples - 1, (int) std::round((absOn - startPPQ) * samplesPerBeat));
                        int offSample = (int) juce::jlimit(0, numSamples - 1, (int) std::round((absOff - startPPQ) * samplesPerBeat));

                        if (onSample >= 0 && onSample < numSamples) {
                            juce::MidiMessage on = juce::MidiMessage::noteOn(1, ev.midiNote, (juce::uint8) juce::jlimit(1, 127, (int)std::round(ev.velocity * 127)));
                            midi.addEvent(on, onSample);
                        }
                        if (offSample >= 0 && offSample < numSamples) {
                            juce::MidiMessage off = juce::MidiMessage::noteOff(1, ev.midiNote);
                            midi.addEvent(off, offSample);
                        }
                    }
                }
            }
        }
    }
}

juce::AudioProcessorEditor* MidiSequenceGeneratorAudioProcessor::createEditor() {
    return new MidiSequenceGeneratorAudioProcessorEditor(*this);
}

void MidiSequenceGeneratorAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    if (auto state = params_.copyState()) {
        std::unique_ptr<juce::XmlElement> xml(state.createXml());
        copyXmlToBinary(*xml, destData);
    }
}

void MidiSequenceGeneratorAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState)
        params_.replaceState(juce::ValueTree::fromXml(*xmlState));
}
