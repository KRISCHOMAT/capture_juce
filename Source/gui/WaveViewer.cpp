/*
  ==============================================================================

    WaveViewer.cpp
    Created: 21 Jan 2024 6:05:55pm
    Author:  christiangrothe

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveViewer.h"
#include "../PluginEditor.h"

//==============================================================================
WaveViewer::WaveViewer(AudioBuffer &buffer_, CaptureAudioProcessorEditor &editor_) : buffer(buffer_), editor(editor_)
{
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
  startTimer(10);
}

WaveViewer::~WaveViewer()
{
}

void WaveViewer::paint(juce::Graphics &g)
{
  // Clear the background
  g.fillAll(juce::Colour::fromRGB(32, 62, 88));

  int height = getHeight();
  int width = getWidth();
  int scale = 20;
  int numSamples = buffer.getNumSamples();
  auto readPtr = buffer.getReadPtr();

  g.setColour(juce::Colours::white);

  // Create a Path to draw the waveform
  juce::Path waveformPath;

  // Calculate scaling factors
  float xScale = static_cast<float>(width) / static_cast<float>(numSamples);
  float yScale = height / 2.0f;
  float downsampleFactor = static_cast<float>(numSamples) / static_cast<float>(width);

  // Move the path to the starting point
  waveformPath.startNewSubPath(0, height / 2);

  // Draw lines to represent the waveform
  for (int i = 0; i < width; ++i)
  {
    int sampleIndex = static_cast<int>(i * downsampleFactor);
    int endIndex = static_cast<int>((i + 1) * downsampleFactor);

    float sample = calculateAverage(readPtr, sampleIndex, endIndex);

    float x = i * xScale;
    float y = (1.0f - (sample * scale)) * yScale;

    waveformPath.lineTo(i, y);
  }
  auto loopStart = editor.loopStartKnob.getValue() / 100;
  auto loopLength = editor.loopLengthKnob.getValue() / 100;

  g.strokePath(waveformPath, juce::PathStrokeType(1.0f));

  g.setColour(juce::Colour::fromRGB(87, 120, 92));
  g.fillRect(static_cast<float>(width * loopStart), 0.0f, 2.0f, static_cast<float>(height));

  g.setColour(juce::Colour::fromRGBA(59, 92, 119, 100));
  g.fillRect(static_cast<float>(width * loopStart) + 1, 0.0f, static_cast<float>(width * loopLength), static_cast<float>(height));
}

void WaveViewer::resized()
{
  // This method is where you should set the bounds of any child
  // components that your component contains..
}

void WaveViewer::timerCallback()
{
  repaint();
}
