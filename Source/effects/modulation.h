/*
  ==============================================================================

    modulation.h
    Created: 30 Jan 2024 4:43:31pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <math.h>
#include "../Utils.h"

class Modulation
{
public:
  double modulationDepth;
  double inc;
  double phase;

  void reset()
  {
    phase = 0.0;
    sin0 = modulationDepth * std::sin(phase * Utils::TWO_PI);
    sin1 = modulationDepth * std::sin((phase - inc) * Utils::TWO_PI);
    dsin = 2.0 * std::cos(inc * Utils::TWO_PI);
  }

  float nextSample()
  {
    double sinx = dsin * sin0 - sin1;
    sin1 = sin0;
    sin0 = sinx;
    return sinx + 1;
  }

private:
  double sin0;
  double sin1;
  double dsin;
};