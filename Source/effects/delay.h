/*
  ==============================================================================

    delay.h
    Created: 28 Jan 2024 7:32:02pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils.h"

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

  void write(float sampleL, float sampleR)
  {
    bufferL[writePos] = (sampleL * inputGain) + (bufferL[writePos] * feedback);
    bufferR[writePos] = (sampleR * inputGain) + (bufferR[writePos] * feedback);

    if (writePos++ > bufferSize * delaytime)
    {
      writePos = 0;
    }
  }

  Output nextSample()
  {
    Output output;
    output.left = bufferL[readPos];
    output.right = bufferR[readPos];

    if (readPos++ > bufferSize * delaytime)
    {
      readPos = 0;
    }
    return output;
  }

  void setFeedback(float feedback_)
  {
    feedback = feedback_;
  }

  void setDelaytime(float delaytime_)
  {
    delaytime = delaytime_;
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

  float delaytime{0.01f};

  float feedback{0.99f};
  float inputGain{1.0f};
  float outputGain{1.0f};

  std::vector<float> bufferL;
  std::vector<float> bufferR;
};