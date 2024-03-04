/*
  ==============================================================================

    modulationMixer.h
    Created: 3 Mar 2024 1:37:47pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include "modulator.h"

class ModulationMixer
{

public:
  void init(float sampleRate_)
  {
    for (int mod = 0; mod < MOD_NUM; mod++)
    {
      mods[mod].init(sampleRate_);
      for (int mix = 0; mix > MIX_NUM; mix++)
      {
        setMixDepth(mix, mod, 0.2f);
      }
    }
    mods[0].setModulationType(Modulator::ModulationType::Noise);
    mods[1].setModulationType(Modulator::ModulationType::Saw);
    mods[2].setModulationType(Modulator::ModulationType::Square);
    mods[3].setModulationType(Modulator::ModulationType::Sine);

    mods[0].setFreq(1.0f);
    mods[1].setFreq(2.0f);
    mods[2].setFreq(3.0f);
    mods[3].setFreq(4.0f);
  }

  void update()
  {
    for (int mod = 0; mod < MOD_NUM; mod++)
    {
      mods[mod].nextSample();
    }
  }

  float gutCurrentSample(uint8_t index, float depth)
  {
    float sample = 0.0f;
    for (int i = 0; i < MOD_NUM; i++)
    {
      for (int y = 0; y < MIX_NUM; y++)
      {

        sample += (mods[i].currentSample * mixes[i][y]);
      }
    }
    return (sample * depth) + 1.0f;
  }

  void setMixDepth(int mixIndex, int modIndex, float val)
  {
    mixes[mixIndex][modIndex] = val;
  }

  void setModFreq(int modIndex, float freq)
  {
    mods[modIndex].setFreq(freq);
  }

  void setModType(int modIndex, Modulator::ModulationType newType)
  {
    mods[modIndex].setModulationType(newType);
  }

private:
  static constexpr int MOD_NUM = 4;
  static constexpr int MIX_NUM = 4;

  Modulator mods[MOD_NUM];
  float mixes[MIX_NUM][MOD_NUM];
};