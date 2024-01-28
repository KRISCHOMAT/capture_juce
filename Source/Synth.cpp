/*
  ==============================================================================

    Synth.cpp
    Created: 12 Jan 2024 9:21:13am
    Author:  christiangrothe

  ==============================================================================
*/

#include "Synth.h"

void Synth::setPlayHead(float playHead)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].playHead = playHead;
  }
}
void Synth::setGrainLength(float grainLength)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].grainLength = grainLength;
  }
}
void Synth::setDensity(float rate)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].setGrainTriggerRate(rate);
  }
}
void Synth::setPlaySpeed(float playSpeed)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].setPlaySpeed(playSpeed);
  }
}
void Synth::setSpray(float sprayfactor)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].sprayFactor = sprayfactor;
  }
}

void Synth::setSpread(float spreadFactor)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].spreadFactor = spreadFactor;
  }
}

void Synth::setLoopStart(float loopStart)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].loopStart = loopStart;
  }
}

void Synth::setLoopLength(float loopLength)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].loopLength = loopLength;
  }
}

void Synth::render(const float *readPtr, float **writePtrs, int numSamples)
{
  if (isRecording)
  {
    record(readPtr, numSamples);
  }

  clearBuffer(writePtrs, numSamples);

  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    if (voices[voice].getIsPlaying())
    {
      voices[voice].render(writePtrs, numSamples);
    }
  }

  for (int i = 0; i < numSamples; i++)
  {
    delay.write(writePtrs[0][i]);
    float nextSample = delay.nextSample();
    writePtrs[0][i] += nextSample;
    writePtrs[1][i] += nextSample;
  }
}

void Synth::init(int totalChannelNum, int bufferSize, float sampleRate_)
{
  loopBuffer.setSize(bufferSize);
  delay.setSize(sampleRate_ * 10);
  writePos = 0.0f;
  isRecording = false;
  playbackDir = PlaybackDir::Normal;
  grainDir = PlaybackDir::Normal;

  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].init(totalChannelNum, bufferSize, sampleRate_, this, &loopBuffer);
  }
}

void Synth::record(const float *readPtr, int numSamples)
{
  int loopBufferSize = loopBuffer.getNumSamples();
  float *loopWritePtr = loopBuffer.getWritePtr();

  for (int sample = 0; sample < numSamples; sample++)
  {
    loopWritePtr[writePos] = readPtr[sample];
    writePos++;

    if (writePos > loopBufferSize)
    {
      writePos = 0;
      isRecording = false;
      break;
    }
  }
}

void Synth::clearBuffer(float **writePtrs, int numSamples)
{
  for (int sample = 0; sample < numSamples; sample++)
  {
    writePtrs[0][sample] = 0.0f;
    writePtrs[1][sample] = 0.0f;
  }
}

void Synth::handleMidi(uint8_t data1, uint8_t data2, uint8_t data3)
{
  switch (data1)
  {
  case MidiCommands::NoteOn:
  {
    for (int voice = 0; voice < VOICE_NUM; voice++)
    {
      if (!voices[voice].getIsPlaying())
      {
        voices[voice].startPlaying(data2);
        break;
      }
    }
    break;
  }

  case MidiCommands::NoteOff:
  {
    for (int voice = 0; voice < VOICE_NUM; voice++)
    {
      if (voices[voice].note == data2)
      {
        voices[voice].stopPlaying();
      }
    }
  }
  break;

  case MidiCommands::CC:
    handleMidiCc(data2, data3);
    break;

  default:
    DBG("other message " << data1 << " " << data2 << " " << data3);
    break;
  }
}

void Synth::handleMidiCc(uint8_t cc, uint8_t val)
{
  switch (cc)
  {
  case MidiCommands::startRecording:
    if (val > 0)
    {
      isRecording = true;
    }
    break;

  default:
    break;
  }
}
