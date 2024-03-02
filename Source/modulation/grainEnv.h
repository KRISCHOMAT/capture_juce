/*
  ==============================================================================

    grainEnv.h
    Created: 2 Mar 2024 8:12:40pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include "lfo.h"

class GrainEnv : public Lfo
{
public:
  void reset() override
  {
    phase = 0.0;
    sin0 = std::sin(phase * Utils::PI);
    sin1 = std::sin((phase - inc) * Utils::PI);
    dsin = 2.0 * std::cos(inc * Utils::PI);
  }
};