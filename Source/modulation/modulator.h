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
    modulationType = ModulationType::Square;
    depth = 1.0f;
    sampleRate = sampleRate_;
    float inc = 1.0f / sampleRate;
    saw.setInc(inc);
    noise.setInc(inc);
    square.setInc(inc);
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
    switch (modulationType)
    {
    case ModulationType::Sine:
      return sine.nextSample();

    case ModulationType::Saw:
      return saw.nextSample();

    case ModulationType::Noise:
      return noise.nextSample();

    case ModulationType::Square:
      return square.nextSample();

    default:
      return 0.0f;
      break;
    }
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