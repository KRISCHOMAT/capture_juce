/*
  ==============================================================================

    Voice.h
    Created: 6 Jan 2024 9:41:06pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include "Grain.h"
#include "Envelope.h"
#include "Utils.h"
#include "modulation/modulationMixer.h"
#include "modulation/noise.h"

class Synth;
class AudioBuffer;

class Voice
{
public:
  void setPlaySpeed(float playSpeed_);
  void setAttack(float attack);
  void setRelease(float release);
  void setGrainTriggerRate(float rate);
  void init(int totalChannelNum, int bufferSize, float sampleRate_, Synth *synth);
  void render(float **writePtrs, int numSamples);
  Utils::Signal render();

  void startPlaying(int note_);
  void stopPlaying();
  bool getIsPlaying();

  int note{-1};
  float playHead;
  float grainLength;
  float sprayFactor;
  float spreadFactor;

  float loopStart;
  float loopLength;

  enum MidiCommands
  {
    NoteOn = 144,
    NoteOff = 128,
    CC = 176,
    startRecording = 22
  };

private:
  Synth *synth;

  static constexpr int GRAIN_NUMS = 256;
  Grain grains[GRAIN_NUMS];

  Envelope env;

  Noise random;

  int writePos;
  float sampleRate;
  float playBackSpeed;
  float playHeadInc;
  float loopBufferSize;
  bool isPlaying;
  float pitch;
  float grainTriggerModDepth{3};
  float grainLengthModDepth{3};

  float grainTriggerRate; // amount of triggers per second
  float grainTriggerInc;  // counts from 0 to grainTriggerRate

  void activateGrain();
  Utils::Signal getGrainVals();
  void setPlayHead();
};