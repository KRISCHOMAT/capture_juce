/*
  ==============================================================================

    delay.h
    Created: 28 Jan 2024 7:32:02pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Delay
{
public:
  void setSize(int bufferSize_)
  {
    bufferSize = bufferSize_;
    readPos = bufferSize / 2;
    bufferL.resize(bufferSize);
    bufferR.resize(bufferSize);
  }

  void write(float sample)
  {
    bufferL[writePos] = (sample * inputGain) + (bufferL[writePos] * feedback);
    if (writePos++ > bufferSize * delayTime)
    {
      writePos = 0;
    }
  }

  float nextSample()
  {
    float next = bufferL[readPos];
    if (readPos++ > bufferSize * delayTime)
    {
      readPos = 0;
    }
    return next;
  }

  void setFeedback(float feedback_)
  {
    feedback = feedback_;
  }

  void setInputGain(float inputGain_)
  {
    inputGain = inputGain_;
  }

  void setOutputGain(float outputGain_)
  {
    outputGain = outputGain_;
  }

private:
  int writePos{0};
  int readPos{0};
  int bufferSize;

  float delayTime{0.01f};

  float feedback{0.99f};
  float inputGain{1.0f};
  float outputGain{1.0f};

  std::vector<float> bufferL;
  std::vector<float> bufferR;
};