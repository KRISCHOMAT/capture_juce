/*
  ==============================================================================

    Utils.h
    Created: 20 Jan 2024 10:29:54am
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename T>
inline static void castParameter(juce::AudioProcessorValueTreeState &apvts,
                                 const juce::ParameterID &id, T &destination)
{
  destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
  jassert(destination);
}