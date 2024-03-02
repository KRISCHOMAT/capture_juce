/*
  ==============================================================================

    Synth.cpp
    Created: 12 Jan 2024 9:21:13am
    Author:  christiangrothe

  ==============================================================================
*/

#include "Synth.h"
#include <cstdint>

void Synth::setPlayHead(float playHead)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].playHead = playHead;
  }
}
void Synth::setAttack(float attack)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].setAttack(attack);
  }
}
void Synth::setRelease(float release)
{
  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].setRelease(release);
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

void Synth::setDelayFeedback(float feedback)
{
  delay.setFeedback(feedback);
}

void Synth::setDelaytime(float delaytime)
{
  delay.setDelaytime(delaytime);
}

void Synth::setInterpolationTime(float character)
{
  delay.setInterpolationTime(character);
}

void Synth::setDelayInputGain(float inputGain)
{
  delay.setInputGain(inputGain);
}

void Synth::setDelayOutputGain(float outputGain)
{
  delay.setOutputGain(outputGain);
}

void Synth::setDelayModDepth(float depth)
{
  delay.setModulationDepth(depth);
}

void Synth::setDelayModSpeed(float speed)
{
  delay.setModulationSpeed(speed);
}

void Synth::render(const float *readPtr, float **writePtrs, int numSamples)
{

  int loopBufferSize = loopBuffer.getNumSamples();
  float *loopWritePtr = loopBuffer.getWritePtr();

  for (int sample = 0; sample < numSamples; sample++)
  {
    Utils::Signal output;

    if (isRecording)
    {
      loopWritePtr[writePos] = readPtr[sample];
      writePos++;

      if (writePos > loopBufferSize)
      {
        writePos = 0;
        isRecording = false;
      }
    }

    writePtrs[0][sample] = 0.0f;
    writePtrs[1][sample] = 0.0f;

    for (int voice = 0; voice < VOICE_NUM; voice++)
    {
      if (voices[voice].getIsPlaying())
      {
        output += voices[voice].render();
      }
    }

    output *= 0.25;
    output += delay.render(output);

    writePtrs[0][sample] += output.left;
    writePtrs[1][sample] += output.right;
  }
}

void Synth::init(int totalChannelNum, int bufferSize, float sampleRate_)
{
  loopBuffer.setSize(bufferSize);
  delay.setSize(sampleRate_ * 1, sampleRate_);
  writePos = 0.0f;
  isRecording = false;
  playbackDir = PlaybackDir::Normal;
  grainDir = PlaybackDir::Normal;

  for (int voice = 0; voice < VOICE_NUM; voice++)
  {
    voices[voice].init(totalChannelNum, bufferSize, sampleRate_, this, &loopBuffer);
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
    // DBG(data2 << " " << data3);
    break;

  default:
    // DBG("other message " << data1 << " " << data2 << " " << data3);
    break;
  }
}

void Synth::handleMidiCc(uint8_t cc, uint8_t val)
{
  switch (cc)
  {
  case MidiCommands::startRecording:
    if (val > 50)
    {
      isRecording = true;
    }
    break;

  default:
    break;
  }
}
