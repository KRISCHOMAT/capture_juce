/*
  ==============================================================================

    GrainEnv.h
    Created: 5 Jan 2024 8:39:01pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GrainEnv
{
public:
  float nextValue()
  {
    level = std::sin(index * inc);
    index++;
    return level;
  }

  void init(float bufferSize_)
  {
    bufferSize = bufferSize_;
    loopSamples = bufferSize * 1.0f;
    calcInc();
  }

  void setLoopLength(float loopLength)
  {
    loopSamples = bufferSize * loopLength;
    calcInc();
  }

  void setPitch(float pitch_)
  {
    pitch = std::abs(pitch_);
    calcInc();
  }

  void reset()
  {
    index = 0.0f;
    level = 0.0f;
  }

private:
  float loopSamples;
  float bufferSize;
  float level{0};
  float pitch{1};
  int index{0};
  float inc;

  void calcInc()
  {
    float freq = (1.0f / loopSamples) * pitch;
    inc = 3.14159265359f * freq;
  }
};