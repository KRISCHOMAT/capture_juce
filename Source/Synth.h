/*
  ==============================================================================

    Synth.h
    Created: 12 Jan 2024 9:21:13am
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Voice.h"
#include "Envelope.h"
#include "AudioBuffer.h"

class Synth
{
public:
  void init(int totalChannelNum, int bufferSize, float sampleRate_);
  void render(const float *readPtr, float **writePtrs, int numSamples);
  void record(const float *readPtr, int numSamples);
  void clearBuffer(float **writePtrs, int numSamples);

  void handleMidi(uint8_t data1, uint8_t data2, uint8_t data3);
  void handleMidiCc(uint8_t cc, uint8_t val);

  void setPlayHead(float playHead_);
  void setGrainLength(float grainLength_);
  void setPlaySpeed(float playSpeed_);
  void setDensity(float rate);
  void setSpray(float sprayFactor_);
  void setSpread(float spreadFactor_);
  void setLoopStart(float loopStart);
  void setLoopLength(float loopLength);

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

private:
  SynthState state{SynthState::Stop};

  static constexpr int VOICE_NUM = 32;
  Voice voices[VOICE_NUM];

  int writePos;
  bool isRecording;
};