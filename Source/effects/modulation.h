/*
  ==============================================================================

    modulation.h
    Created: 30 Jan 2024 4:43:31pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <math.h>
#include "../Utils.h"

class Modulation
{
public:
  double amplitude;
  double inc;
  double phase;

  void reset()
  {
    phase = 0.0f;
    sin0 = amplitude * std::sin(phase * TWO_PI);
    sin1 = amplitude * std::sin((phase - inc) * TWO_PI);
    dsin = 2.0f * std::cos(inc * TWO_PI);
  }

  float nextSample()
  {
    double sinx = dsin * sin0 - sin1;
    sin1 = sin0;
    sin0 = sinx;
    DBG(sinx + 1);
    return sinx;
  }

private:
  double sin0;
  double sin1;
  double dsin;
};