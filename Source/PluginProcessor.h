/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "JucePluginDefines.h"
#include "Synth.h"

namespace ParameterID
{
#define PARAMETER_ID(str) const juce::ParameterID str(#str, 1);
  PARAMETER_ID(loopStart)
  PARAMETER_ID(loopLength)
  PARAMETER_ID(grainLength)
  PARAMETER_ID(dens)
  PARAMETER_ID(playSpeed)
  PARAMETER_ID(spray)
  PARAMETER_ID(spread)
  PARAMETER_ID(grainDir)
  PARAMETER_ID(playDir)
  PARAMETER_ID(delaytime)
  PARAMETER_ID(delayFeedback)
  PARAMETER_ID(interpolationTime)
  PARAMETER_ID(delayInputGain)
  PARAMETER_ID(delayOutputGain)
}

//==============================================================================
/**
 */
class CaptureAudioProcessor : public juce::AudioProcessor,
                              public juce::ValueTree::Listener
{
public:
  //==============================================================================
  CaptureAudioProcessor();
  ~CaptureAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

  float inputRms{0.0f};
  float outputRmsL{0.0f};
  float outputRmsR{0.0f};

  juce::AudioProcessorValueTreeState apvts{*this, nullptr, "Parameters", createParameterLayout()};
  Synth synth;

private:
  void handleMidi(juce::MidiBuffer &midiMessages);

  juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

  juce::AudioParameterFloat *loopStartParam;
  juce::AudioParameterFloat *loopLengthParam;
  juce::AudioParameterFloat *grainLengthParam;
  juce::AudioParameterFloat *densParam;
  juce::AudioParameterFloat *playSpeedParam;
  juce::AudioParameterFloat *sprayParam;
  juce::AudioParameterFloat *spreadParam;
  juce::AudioParameterChoice *grainDirParam;
  juce::AudioParameterChoice *playDirParam;
  juce::AudioParameterFloat *delaytimeParam;
  juce::AudioParameterFloat *delayFeedbackParam;
  juce::AudioParameterFloat *interpolationTimeParam;
  juce::AudioParameterFloat *delayOutputGainParam;
  juce::AudioParameterFloat *delayInputGainParam;

  void valueTreePropertyChanged(juce::ValueTree &, const juce::Identifier &) override
  {
    parametersChanged.store(true);
  }

  std::atomic<bool> parametersChanged{true};

  void update();

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CaptureAudioProcessor)
};
