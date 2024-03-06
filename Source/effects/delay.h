/*
  ==============================================================================

    delay.h
    Created: 28 Jan 2024 7:32:02pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <vector>
#include <cmath>
#include "modulation.h"
#include "../Utils.h"
#include "../Synth.h"

class Delay
{
public:
  void init(Synth *synth_)
  {
    synth = synth_;
  }

  void setModulationDepth(float modulationDepth)
  {
    mod.modulationDepth = modulationDepth;
  }
  void setModulationSpeed(float modulationSpeed)
  {
    mod.inc = modulationSpeed / sampleRate;
    mod.reset();
  }
  void setSize(int bufferSize_, float sampleRate_)
  {
    bufferSize = bufferSize_;
    bufferL.resize(bufferSize);
    bufferR.resize(bufferSize);
    sampleRate = sampleRate_;
    mod.modulationDepth = 0.0f;
    mod.inc = 0.1f / sampleRate;
    mod.reset();
  }

  Utils::Signal render(Utils::Signal input)
  {
    write(input);
    return nextSample();
  }

  void write(Utils::Signal input)
  {

    bufferL[writePos] = (input.left * inputGain) + (bufferL[readPos] * feedback);
    bufferR[writePos] = (input.right * inputGain) + (bufferR[readPos] * feedback);

    if (++writePos >= bufferSize)
    {
      writePos = 0.0f;
    }
  }

  Utils::Signal nextSample()
  {
    Utils::Signal output;

    float modVal = mod.nextSample();
    float targetDelayMod = fmod(targetDelaytime * modVal, 1.0f);

    if (delaytime != targetDelayMod)
    {
      delaytime = Utils::lerp(delaytime, targetDelayMod, interpolationTime);
    }

    int offset = bufferSize * delaytime;
    readPos = writePos - offset;

    if (readPos < 0.0f)
    {
      readPos += bufferSize;
    }

    float sampleL = Utils::cubicHermiteSpline(bufferL.data(), static_cast<float>(readPos), bufferSize);
    float sampleR = Utils::cubicHermiteSpline(bufferR.data(), static_cast<float>(readPos), bufferSize);

    output.left = sampleL;
    output.right = sampleR;

    output *= outputGain;

    return output;
  }

  void setFeedback(float feedback_)
  {
    feedback = feedback_;
  }

  void setDelaytime(float delaytime_)
  {
    targetDelaytime = delaytime_;
  }

  void setInputGain(float inputGain_)
  {
    inputGain = inputGain_;
  }

  void setOutputGain(float outputGain_)
  {
    outputGain = outputGain_;
  }

  void setInterpolationTime(float interpolationTime_)
  {

    interpolationTime = interpolationTime_ * 0.0001f;
  }

private:
  int writePos{0};
  int readPos{0};
  int newReadPos{0};
  float interpolationTime{0.001f};
  int bufferSize;
  float sampleRate;

  Synth *synth;

  Modulation mod;

  float delaytime{0.5f};
  float targetDelaytime{0.5f};

  float feedback{0.99f};
  float inputGain{1.0f};
  float outputGain{1.0f};

  std::vector<float> bufferL;
  std::vector<float> bufferR;
};