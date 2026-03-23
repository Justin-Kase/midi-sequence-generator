# Bomb Sequence Generator 💣

A JUCE-based VST3 MIDI step sequencer by **Illbomb**. Generates step-sequenced note patterns with scale selection, per-step velocity variation, and a seed-based generative engine. Also ships a standalone CLI for exporting MIDI clips without a DAW.

## Download

**Pre-built VST3 binaries:**
- [macOS (Universal)](../../releases/latest/download/BombSequenceGenerator-macOS.zip)
- [Windows (x64)](../../releases/latest/download/BombSequenceGenerator-Windows.zip)
- [Linux (x64)](../../releases/latest/download/BombSequenceGenerator-Linux.zip)

### Installation
- **macOS:** Extract and copy `Bomb Sequence Generator.vst3` to `~/Library/Audio/Plug-Ins/VST3/`
- **Windows:** Extract and copy `Bomb Sequence Generator.vst3` to `C:\Program Files\Common Files\VST3\`
- **Linux:** Extract and copy `Bomb Sequence Generator.vst3` to `~/.vst3/`

## Features

- **VST3 MIDI effect** — no audio, pure MIDI note output, works as Note FX in Bitwig
- **10 scales** — Major, Minor, Pentatonic Major/Minor, Blues, Dorian, Phrygian, Lydian, Mixolydian, Locrian
- **Seed parameter (0–999)** — each seed generates a unique pattern and velocity curve instantly
- **Per-step velocity variation** — humanized feel driven by seed
- **7 controls** — Steps (4–32), Swing, Density, Root, Octaves, Scale, Seed
- **Live step grid** — active steps lit up with velocity-driven brightness, amber playhead
- **Dark UI** — custom look-and-feel with Illbomb branding

## Usage in Bitwig

1. Drop **Bomb Sequence Generator** as a Note FX on any instrument track
2. Hit play — it generates one-bar sequences synced to host tempo
3. Dial in your **Scale**, **Seed**, and **Density**
4. Turn the **Seed** knob to instantly flip to a new pattern
5. The step grid lights up in real time — brightness = velocity, amber cell = playhead

## CLI Usage

```bash
./build/Source/midigen \
  --steps 16 \
  --bars 4 \
  --root 60 \
  --swing 0.1 \
  --density 0.7 \
  --octaves 1 \
  --scale 4 \
  --seed 77 \
  --out sequence.mid
```

### Scale index reference

| Index | Scale |
|-------|-------|
| 0 | Major |
| 1 | Minor |
| 2 | Pentatonic Major |
| 3 | Pentatonic Minor |
| 4 | Blues |
| 5 | Dorian |
| 6 | Phrygian |
| 7 | Lydian |
| 8 | Mixolydian |
| 9 | Locrian |

## Build from Source

### Prerequisites
- CMake 3.21+
- Xcode CLI tools (macOS), MSVC (Windows), or GCC/Clang (Linux)
- Linux only: `sudo apt-get install libasound2-dev libjack-jackd2-dev libx11-dev libxcomposite-dev libxcursor-dev libxext-dev libxinerama-dev libxrandr-dev libxrender-dev libfreetype6-dev libwebkit2gtk-4.1-dev`

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

**Output:**
- Plugin: `build/Source/BombSeqGenerator_artefacts/Release/VST3/Bomb Sequence Generator.vst3`
- CLI: `build/Source/midigen`

## Changelog

### v0.2.0 (March 2026)
- ✅ 10 scale modes (Major, Minor, Blues, Pentatonic, Dorian, and more)
- ✅ Seed parameter — deterministic pattern + velocity generation
- ✅ Per-step velocity variation for humanized feel
- ✅ Full UI redesign — dark theme, live step grid, scale ComboBox
- ✅ Illbomb branding + logo

### v0.1.1 (Initial)
- Basic major scale step sequencer
- Steps, Swing, Density, Root, Octaves controls

## Tech Stack
- JUCE 8.x (fetched via CMake)
- C++17
- VST3

## License
MIT
