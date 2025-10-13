#include "PluginEditor.h"
#include "PluginProcessor.h"

MidiSequenceGeneratorAudioProcessorEditor::MidiSequenceGeneratorAudioProcessorEditor (MidiSequenceGeneratorAudioProcessor& p)
: juce::AudioProcessorEditor (&p), processorRef_(p) {
    setResizable(true, true);
    setSize(420, 220);

    auto& params = processorRef_.parameters();

    auto initSlider = [&](juce::Slider& s, const juce::String& name){
        s.setSliderStyle(juce::Slider::Rotary);
        s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 18);
        s.setName(name);
        addAndMakeVisible(s);
    };

    initSlider(stepsSlider_, "Steps"); stepsAtt_.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(params, "steps", stepsSlider_));
    initSlider(swingSlider_, "Swing"); swingAtt_.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(params, "swing", swingSlider_));
    initSlider(densitySlider_, "Density"); densityAtt_.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(params, "density", densitySlider_));
    initSlider(rootSlider_, "Root"); rootAtt_.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(params, "root", rootSlider_));
    initSlider(octavesSlider_, "Octaves"); octavesAtt_.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(params, "octaves", octavesSlider_));
}

void MidiSequenceGeneratorAudioProcessorEditor::paint (juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(16.0f);
    g.drawFittedText("MIDI Sequence Generator", getLocalBounds().removeFromTop(24), juce::Justification::centredTop, 1);
}

void MidiSequenceGeneratorAudioProcessorEditor::resized() {
    auto area = getLocalBounds().reduced(12);
    auto row = area.removeFromTop(180);

    auto place = [&](juce::Slider& s){
        row.removeFromLeft(6);
        s.setBounds(row.removeFromLeft(80));
    };

    place(stepsSlider_);
    place(swingSlider_);
    place(densitySlider_);
    place(rootSlider_);
    place(octavesSlider_);
}
