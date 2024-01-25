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

  juce::AudioBuffer<float> *currentOutput{nullptr};

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

  void valueTreePropertyChanged(juce::ValueTree &, const juce::Identifier &) override
  {
    parametersChanged.store(true);
  }

  std::atomic<bool> parametersChanged{true};

  void update();

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CaptureAudioProcessor)
};
