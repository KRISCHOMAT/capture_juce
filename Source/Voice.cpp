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

void Voice::setAttack(float attack)
{
  env.setAttackMultiplier(attack);
}

void Voice::setRelease(float release)
{
  env.setReleaseMultiploer(release);
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

void Voice::init(int totalChannelNum, int bufferSize, float sampleRate_, Synth *synth_)
{
  synth = synth_;
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
    grains[grain].init(&synth->loopBuffer, sampleRate);
  }
}

void Voice::render(float **writePtrs, int numSamples)
{
  for (int sample = 0; sample < numSamples; sample++)
  {
    setPlayHead();
    activateGrain();
    Utils::Signal nextSamples = getGrainVals();
    writePtrs[0][sample] += nextSamples.left * 0.25f;
    writePtrs[1][sample] += nextSamples.right * 0.25f;
  }
}

Utils::Signal Voice::render()
{
  setPlayHead();
  activateGrain();
  Utils::Signal voiceOut = getGrainVals();
  voiceOut;
  return voiceOut;
}

inline void Voice::setPlayHead()
{
  switch (synth->playbackDir)
  {
  case Synth::PlaybackDir::Normal:
    playHead = (playHead >= 1.0f) | (playHead >= loopStart + loopLength)
                   ? loopStart
                   : playHead + (playHeadInc * synth->modMixer.getCurrentSample(synth->playSpeedModIndex, synth->playSpeedModDepth));
    break;

  case Synth::PlaybackDir::Reverse:
    playHead = playHead <= loopStart
                   ? loopStart + loopLength
                   : playHead - (playHeadInc * synth->modMixer.getCurrentSample(synth->playSpeedModIndex, synth->playSpeedModDepth));
    break;

  case Synth::PlaybackDir::BackAndForth:
    // TO DO
    break;
  }
}

void Voice::activateGrain()
{
  float triggerRateWithMod = grainTriggerRate * synth->modMixer.getCurrentSample(synth->grainDenseModIndex, synth->grainDenseModDepth);
  float grainLengthWithMod = grainLength * synth->modMixer.getCurrentSample(synth->grainLengthModIndex, synth->grainLengthModDepth);

  if (grainTriggerInc++ >= triggerRateWithMod)
  {
    float spray = random.nextSample() * sprayFactor;
    for (int grain = 0; grain < GRAIN_NUMS; grain++)
    {
      if (!grains[grain].isActive())
      {
        playHead = playHead < loopStart ? loopStart : playHead;
        float withSpray = (playHead + spray > 1.0f) ? playHead : playHead + spray;
        float pos = (random.nextSample() - 0.5f) * 2 * spreadFactor;
        bool isReverse = synth->grainDir == Synth::PlaybackDir::Normal ? false : true;
        grains[grain].activateGrain(withSpray, grainLengthWithMod, pos, pitch, isReverse);
        break;
      }
    }

    grainTriggerInc = 0;
  }
}

Utils::Signal Voice::getGrainVals()
{
  Utils::Signal output;
  float envVal = env.nextValue();
  for (int grain = 0; grain < GRAIN_NUMS; grain++)
  {
    if (grains[grain].isActive())
    {
      Utils::Signal newOutput = grains[grain].getValues();
      output.left += newOutput.left * envVal;
      output.right += newOutput.right * envVal;
    }
  }
  return output;
}
