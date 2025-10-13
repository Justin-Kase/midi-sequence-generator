# MIDI Sequence Generator (VST3 + CLI) – v0.1.1

A simple JUCE-based VST3 MIDI generator for Bitwig that creates step-sequenced note patterns, plus a small CLI tool to export MIDI clips.

## Features
- VST3 MIDI effect plugin (no audio) that outputs MIDI notes
- Parameters: Steps (4-32), Swing (0-0.5), Density (0-1), Root (C2-A#5), Octaves (0-3)
- Basic major scale patterns with swing and density controls
- Minimal UI with rotary knobs
- CLI `midigen` to export `.mid` files without a DAW

## macOS Prereqs
- Xcode command line tools
- CMake 3.21+

## Build
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
Artifacts:
- Plugin: `build/MidiSequenceGenerator_artefacts/VST3/MIDI Sequence Generator.vst3`
- CLI: `build/midigen`

## Install to Bitwig
- Copy the `.vst3` folder to `~/Library/Audio/Plug-Ins/VST3/`
- Open Bitwig, enable VST3 scanning, and rescan plugins
- Insert the plugin on an instrument track as a Note FX (MIDI effect)

## Using the plugin in Bitwig
- Place it before an instrument. It outputs note-on/off events.
- Press play; it will generate one-bar sequences synced to host tempo.
- Adjust Steps/Swing/Density/Root/Octaves.

## CLI usage
```
./build/midigen --steps 16 --bars 4 --root 60 --swing 0.1 --density 0.7 --octaves 1 --out sequence.mid
```

## Notes / Next steps
- Add scale selection and patterns (minor, pentatonic, modes)
- Add seed and probability per step
- Support multi-bar generation in-processBlock with proper sample-accurate scheduling
- Persist parameters and add preset support
