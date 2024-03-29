/*
  ==============================================================================

    Synth.h
    Created: 12 Jan 2024 9:21:13am
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <cstdint>
#include "Voice.h"
#include "Envelope.h"
#include "AudioBuffer.h"
#include "modulation/modulationMixer.h"
#include "effects/delay.h"

// class Delay;

class Synth
{
public:
  void init(int totalChannelNum, int bufferSize, float sampleRate_);
  void render(const float *readPtr, float **writePtrs, int numSamples);

  void handleMidi(uint8_t data1, uint8_t data2, uint8_t data3);
  void handleMidiCc(uint8_t cc, uint8_t val);

  void setAttack(float attack);
  void setRelease(float release);
  void setPlayHead(float playHead_);
  void setGrainLength(float grainLength_);
  void setPlaySpeed(float playSpeed_);
  void setDensity(float rate);
  void setSpray(float sprayFactor_);
  void setSpread(float spreadFactor_);
  void setLoopStart(float loopStart);
  void setLoopLength(float loopLength);
  void setDelaytime(float delaytime);
  void setDelayFeedback(float feedback);
  void setInterpolationTime(float character);
  void setDelayInputGain(float inputGain);
  void setDelayOutputGain(float outputGain);

  enum MidiCommands
  {
    NoteOn = 144,
    NoteOff = 128,
    CC = 176,
    startRecording = 22
  };

  enum SynthState
  {
    Stop,
    Play,
    Record
  };

  enum PlaybackDir
  {
    Normal,
    Reverse,
    BackAndForth
  };

  PlaybackDir grainDir;
  PlaybackDir playbackDir;
  AudioBuffer loopBuffer;
  Delay delay;
  ModulationMixer modMixer;

  // Modulation
  float grainLengthModDepth{0.0f};
  float grainDenseModDepth{0.0f};
  float playSpeedModDepth{0.0f};
  float delayTimeModDepth{0.0f};
  float delayLazynessModDepth{0.0f};
  float delayInputModDepth{0.0f};

  uint8_t grainDenseModIndex{0};
  uint8_t grainLengthModIndex{1};
  uint8_t playSpeedModIndex{2};
  uint8_t delayTimeModIndex{3};
  uint8_t delayLazynessModIndex{1};
  uint8_t delayInputModIndex{2};

  void setModulation(float &depthDestiny, float newDepth, uint8_t &indexDestinty, uint8_t newIndex);
  void setModulation(float &depthDestiny, float newDepth);
  void setModulation(uint8_t &indexDestinty, uint8_t newIndex);
  void setModulationType(uint8_t index, Modulator::ModulationType newType);
  void setModulationFreq(uint8_t index, float newFreq);

private:
  SynthState state{SynthState::Stop};

  static constexpr int VOICE_NUM = 32;
  Voice voices[VOICE_NUM];

  int writePos;
  bool isRecording;
};