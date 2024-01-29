/*
  ==============================================================================

    GrainB.h
    Created: 7 Jan 2024 8:14:20pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "GrainEnv.h"
#include "AudioBuffer.h"

struct Output
{
  float left;
  float right;
};

class Grain
{
public:
  void init(AudioBuffer *loopBuffer_, float sampleRate_)
  {
    loopBuffer = loopBuffer_;
    sampleRate = sampleRate_;
  }

  Output getValues()
  {
    Output output;
    if (active)
    {
      float envelope = grainEnv.nextValue();
      phasor += phasorInc * pitch;
      if ((phasor >= 1.0f && !isReverse) || (phasor <= 0.0f && isReverse))
      {
        active = false;
        grainEnv.reset();
      }

      float panMultiplierLeft = std::max(0.0f, 1.0f - pos);
      float panMultiplierRight = std::max(0.0f, 1.0f + pos);

      float sample = getNextSample();
      output.left = sample * envelope * panMultiplierLeft;
      output.right = sample * envelope * panMultiplierRight;
    }

    return output;
  }

  void setGrainLength(float grainLength_)
  {
    grainLength = sampleRate * (grainLength_ / 1000.0f);
    grainEnv.init(grainLength);
    phasorInc = 1 / grainLength;
  }

  void setPitch(float pitch_)
  {
    pitch = pitch_;
    grainEnv.setPitch(pitch);
  }

  void activateGrain(float playHead, float grainLength, float pos_ = 0.0f, float pitch = 1.0f, bool isReverse_ = false)
  {
    active = true;
    pos = pos_;
    offset = playHead;
    phasor = isReverse ? 1.0f : 0.0f;
    isReverse = isReverse_;

    if (isReverse)
    {
      setPitch(-pitch);
    }
    else
    {
      setPitch(pitch);
    }
    setGrainLength(grainLength);
  }

  bool isActive()
  {
    return active;
  }

private:
  AudioBuffer *loopBuffer;
  GrainEnv grainEnv;
  float sampleRate;
  float phasor{0.0f};
  float phasorInc;
  float grainLength;
  float pitch{1.0f};
  float offset{0.0f};
  float pos{0};
  bool active{false};
  bool isReverse;

  template <typename Float>
  inline Float cubicHermiteSpline(const Float *buffer, const Float readHead, const int size) noexcept
  {
    const auto iFloor = std::floor(readHead);
    auto i1 = static_cast<int>(iFloor);
    auto i0 = i1 - 1;
    auto i2 = i1 + 1;
    auto i3 = i1 + 2;

    if (i3 >= size)
      i3 -= size;
    if (i2 >= size)
      i2 -= size;
    if (i0 < 0)
      i0 += size;

    const auto t = readHead - iFloor;
    const auto v0 = buffer[i0];
    const auto v1 = buffer[i1];
    const auto v2 = buffer[i2];
    const auto v3 = buffer[i3];

    const auto c0 = v1;
    const auto c1 = static_cast<Float>(.5) * (v2 - v0);
    const auto c2 = v0 - static_cast<Float>(2.5) * v1 + static_cast<Float>(2.) * v2 - static_cast<Float>(.5) * v3;
    const auto c3 = static_cast<Float>(1.5) * (v1 - v2) + static_cast<Float>(.5) * (v3 - v0);

    return ((c3 * t + c2) * t + c1) * t + c0;
  }

  float getNextSample()
  {
    if (!active)
    {
      return 0.0f;
    }

    int loopBufferLength = loopBuffer->getNumSamples();
    const float *loopBufferDataL = loopBuffer->getReadPtr();

    float sampleOffset = (loopBufferLength - grainLength) * offset;

    float index = phasor * (grainLength - 1);
    index += sampleOffset;
    auto sample = cubicHermiteSpline(loopBufferDataL, index, loopBufferLength);

    return sample;
  }
};