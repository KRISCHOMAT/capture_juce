/*
  ==============================================================================

    modulator.h
    Created: 2 Mar 2024 9:36:21pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include "sine.h"
#include "noise.h"
#include "saw.h"
#include "square.h"

class Modulator
{
public:
  enum class ModulationType
  {
    Sine,
    Saw,
    Noise,
    Square
  };

  void init(int sampleRate_)
  {
    modulationType = ModulationType::Sine;
    depth = 0.5f;
    sampleRate = sampleRate_;
    float inc = 1.0f / sampleRate;
    saw.setInc(inc);
    noise.setInc(inc);
    square.setInc(inc);
    sine.setInc(inc);
  }

  void setFreq(float freq)
  {
    float inc = 1.0f / sampleRate / freq;
    saw.setInc(inc);
    noise.setInc(inc);
    square.setInc(inc);
  }

  void setModulationType(ModulationType newType)
  {
    modulationType = newType;
  }

  float nextSample()
  {
    float nextSample = 0.0f;
    switch (modulationType)
    {
    case ModulationType::Sine:
      return sine.nextSample() + 1.0f;
      break;

    case ModulationType::Saw:
      nextSample = saw.nextSample();
      break;

    case ModulationType::Noise:
      nextSample = noise.nextSample();
      break;

    case ModulationType::Square:
      nextSample = square.nextSample();
      break;
    }
    return depth * nextSample + 1.0f;
  }

private:
  float depth;
  int sampleRate;
  ModulationType modulationType;
  SampleAndHold noise;
  Saw saw;
  Sine sine;
  Square square;
};