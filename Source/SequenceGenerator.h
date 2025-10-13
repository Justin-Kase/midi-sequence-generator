#pragma once
#include <vector>
#include <cstdint>

struct NoteEvent {
    int midiNote = 60; // C4
    float velocity = 0.8f;
    uint32_t startTick = 0; // PPQ ticks
    uint32_t lengthTick = 480; // default 1 beat at 480 PPQ
};

// Simple step sequencer style generator
class SequenceGenerator {
public:
    // ppq: pulses per quarter note, steps: number of steps, density: [0..1]
    void configure(int ppq, int steps, int rootNote, const std::vector<int>& scaleSemis,
                   float swingPercent = 0.0f, float density = 0.7f, int octaveSpread = 1);

    // Generate events for N bars
    std::vector<NoteEvent> generateBars(int bars) const;

private:
    int ppq_ = 480;
    int steps_ = 16;
    int root_ = 60;
    std::vector<int> scale_ {0,2,4,5,7,9,11}; // major
    float swing_ = 0.0f; // 0..0.5 typical
    float density_ = 0.7f;
    int octaveSpread_ = 1;
};
