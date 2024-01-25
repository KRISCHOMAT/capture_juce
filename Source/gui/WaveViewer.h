/*
  ==============================================================================

    MyComponent.h
    Created: 21 Jan 2024 6:05:55pm
    Author:  christiangrothe

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CaptureAudioProcessorEditor;
class AudioBuffer;

//==============================================================================
/*
 */
class WaveViewer : public juce::Component, public juce::Timer
{
public:
  WaveViewer(AudioBuffer &buffer_, CaptureAudioProcessorEditor &editor_);

  ~WaveViewer() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  AudioBuffer &buffer;
  CaptureAudioProcessorEditor &editor;

  void timerCallback() override;

  double calculateAverage(const float *data, int startIndex, int endIndex)
  {
    double sum = 0.0;

    for (int i = startIndex; i < endIndex; ++i)
      sum += static_cast<double>(data[i]);

    return sum / static_cast<double>(endIndex - startIndex);
  }

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveViewer);
};
