/*
  ==============================================================================

    Voice.cpp
    Created: 12 Jan 2024 7:39:58am
    Author:  christiangrothe

  ==============================================================================
*/

#include "Voice.h"
#include "Synth.h"
#include "AudioBuffer.h"

void Voice::setPlaySpeed(float playSpeed_)
{
  playBackSpeed = playSpeed_;
  playHeadInc = (1 / loopBufferSize) * playBackSpeed;
}

void Voice::setGrainTriggerRate(float rate)
{
  grainTriggerRate = sampleRate * (rate / 1000.0f);
}

void Voice::startPlaying(int note_)
{
  note = note_;
  int semitoneDifference = note - 60;
  float newPitch = pow(2.0f, static_cast<float>(semitoneDifference) / 12.0f);
  pitch = newPitch;
  isPlaying = true;
  env.attack();
}

void Voice::stopPlaying()
{
  note = -1;
  env.release();
}

bool Voice::getIsPlaying()
{
  return isPlaying;
}

void Voice::init(int totalChannelNum, int bufferSize, float sampleRate_, Synth *synth_, AudioBuffer *loopBuffer)
{
  synth = synth_;
  loopBufferPtr = loopBuffer;
  loopBufferSize = bufferSize;

  sampleRate = sampleRate_;
  grainTriggerRate = sampleRate * (500.f / 1000.0f);
  grainTriggerInc = grainTriggerRate;
  isPlaying = false;
  grainLength = 500.0f;

  playBackSpeed = 0.0f;
  playHead = 0.0f;
  playHeadInc = (1 / loopBufferSize);
  writePos = 0.0f;

  pitch = 1.0f;
  sprayFactor = 0.0f;
  spreadFactor = 0.0f;

  loopStart = 0.0f;
  loopLength = 1.0f;

  env.init(sampleRate, 0.1f, [this]()
           { 
            isPlaying = false;
            note = -1; });

  for (int grain = 0; grain < GRAIN_NUMS; grain++)
  {
    grains[grain].init(loopBufferPtr, sampleRate);
  }
}

Output Voice::render()
{
  setPlayHead();
  activateGrain();
  Output nextSamples = getGrainVals();
  return nextSamples;
}

inline void Voice::setPlayHead()
{
  switch (synth->playbackDir)
  {
  case Synth::PlaybackDir::Normal:
    playHead = (playHead >= 1.0f) | (playHead >= loopStart + loopLength) ? loopStart : playHead + playHeadInc;
    break;

  case Synth::PlaybackDir::Reverse:
    playHead = playHead <= loopStart ? loopStart + loopLength : playHead - playHeadInc;
    break;

  case Synth::PlaybackDir::BackAndForth:
    // TO DO
    break;

  default:
    playHead = playHead >= 1.0f ? 0.0f : playHead + playHeadInc;
    break;
  }
}

void Voice::activateGrain()
{

  if (grainTriggerInc++ >= grainTriggerRate)
  {
    float spray = random.nextFloat() * sprayFactor;
    for (int grain = 0; grain < GRAIN_NUMS; grain++)
    {
      if (!grains[grain].isActive())
      {
        playHead = playHead < loopStart ? loopStart : playHead;
        float withSpray = (playHead + spray > 1.0f) ? playHead : playHead + spray;
        float pos = (random.nextFloat() - 0.5f) * 2 * spreadFactor;
        bool isReverse = synth->grainDir == Synth::PlaybackDir::Normal ? false : true;
        grains[grain].activateGrain(withSpray, grainLength, pos, pitch, isReverse);
        break;
      }
    }

    grainTriggerInc = 0;
  }
}

Output Voice::getGrainVals()
{
  Output output;
  float envVal = env.nextValue();
  for (int grain = 0; grain < GRAIN_NUMS; grain++)
  {
    if (grains[grain].isActive())
    {
      Output newOutput = grains[grain].getValues();
      output.left += newOutput.left * envVal;
      output.right += newOutput.right * envVal;
    }
  }
  return output;
}
