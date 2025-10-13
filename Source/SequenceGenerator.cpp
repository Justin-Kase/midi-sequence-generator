#include "SequenceGenerator.h"
#include <random>

void SequenceGenerator::configure(int ppq, int steps, int rootNote, const std::vector<int>& scaleSemis,
                                  float swingPercent, float density, int octaveSpread) {
    ppq_ = ppq > 0 ? ppq : 480;
    steps_ = steps > 0 ? steps : 16;
    root_ = rootNote;
    scale_ = scaleSemis.empty() ? std::vector<int>{0,2,4,5,7,9,11} : scaleSemis;
    swing_ = std::max(0.f, std::min(0.5f, swingPercent));
    density_ = std::max(0.f, std::min(1.f, density));
    octaveSpread_ = std::max(0, octaveSpread);
}

std::vector<NoteEvent> SequenceGenerator::generateBars(int bars) const {
    std::vector<NoteEvent> out;
    if (bars <= 0) return out;

    const int totalSteps = steps_ * bars;
    const uint32_t stepTicks = (ppq_ * 4) / steps_; // 4/4 grid over a bar

    std::mt19937 rng(42);
    std::uniform_real_distribution<float> uni(0.0f, 1.0f);
    std::uniform_int_distribution<int> octavePick(0, octaveSpread_);

    for (int s = 0; s < totalSteps; ++s) {
        if (uni(rng) > density_) continue;

        int degree = s % (int)scale_.size();
        int octave = octavePick(rng);
        int note = root_ + scale_[degree] + octave * 12;

        uint32_t start = s * stepTicks;
        // swing on odd steps
        if (s % 2 == 1) start += (uint32_t)(stepTicks * swing_);

        NoteEvent ev;
        ev.midiNote = note;
        ev.velocity = 0.85f;
        ev.startTick = start;
        ev.lengthTick = (uint32_t)(stepTicks * 0.9f);
        out.push_back(ev);
    }
    return out;
}
