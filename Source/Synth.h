/*
  ==============================================================================

    Synth.h
    Created: 12 Jan 2024 9:21:13am
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include "Utils.h"
#include "Voice.h"
#include "Envelope.h"
#include "AudioBuffer.h"
#include "effects/delay.h"
#include "modulation/modulationMixer.h"

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
  void setDelayModDepth(float modDepth);
  void setDelayModSpeed(float modSpeed);

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

  float grainLengthModDepth;
  float grainDensModDepth;
  float playSpeedModDepth;
  float delayTimeModDepth;
  float delayLazynessModDepth;
  float delayInputModDepth;

  uint8_t grainDensModIndex{0};
  uint8_t grainLengthModIndex{1};
  uint8_t playSpeedModIndex{2};
  uint8_t delayTimeModIndex{3};
  uint8_t delayLazynessModIndex{1};
  uint8_t delayInputModIndex{2};

private:
  SynthState state{SynthState::Stop};

  static constexpr int VOICE_NUM = 32;
  Voice voices[VOICE_NUM];

  int writePos;
  bool isRecording;
};