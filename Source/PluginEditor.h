/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "gui/WaveViewer.h"
#include "gui/LevelMeter.h"

//==============================================================================
/**
 */
class CaptureAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    CaptureAudioProcessorEditor(CaptureAudioProcessor &);
    ~CaptureAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

    juce::Slider loopStartKnob;
    juce::Slider loopLengthKnob;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CaptureAudioProcessor &audioProcessor;

    // Knobs
    juce::Slider grainLengthKnob;
    juce::Slider densKnob;
    juce::Slider playSpeedKnob;
    juce::Slider sprayKnob;
    juce::Slider spreadKnob;
    juce::Slider grainDirKnob;
    juce::Slider playDirKnob;

    // Labels
    juce::Label loopStartLabel;
    juce::Label loopLengthLabel;
    juce::Label grainLengthLabel;
    juce::Label densLabel;
    juce::Label playSpeedLabel;
    juce::Label sprayLabel;
    juce::Label spreadLabel;
    juce::Label grainDirLabel;
    juce::Label playDirLabel;

    // Custom
    WaveViewer waveViewer;
    LevelMeter levelMeter;

    using APVTS = juce::AudioProcessorValueTreeState;
    using SliderAttachment = APVTS::SliderAttachment;

    SliderAttachment loopStarAttatchment{
        audioProcessor.apvts,
        ParameterID::loopStart.getParamID(),
        loopStartKnob};
    SliderAttachment loopLengthAttachment{
        audioProcessor.apvts,
        ParameterID::loopLength.getParamID(),
        loopLengthKnob};
    SliderAttachment grainLengthAttachment{
        audioProcessor.apvts,
        ParameterID::grainLength.getParamID(),
        grainLengthKnob};
    SliderAttachment densAttachment{
        audioProcessor.apvts,
        ParameterID::dens.getParamID(),
        densKnob};
    SliderAttachment playSpeedAttachment{
        audioProcessor.apvts,
        ParameterID::playSpeed.getParamID(),
        playSpeedKnob};
    SliderAttachment sprayAttachment{
        audioProcessor.apvts,
        ParameterID::spray.getParamID(),
        sprayKnob};
    SliderAttachment spreadAttachment{
        audioProcessor.apvts,
        ParameterID::spread.getParamID(),
        spreadKnob};
    SliderAttachment grainDirAttachment{
        audioProcessor.apvts,
        ParameterID::grainDir.getParamID(),
        grainDirKnob};
    SliderAttachment playDirAttachment{
        audioProcessor.apvts,
        ParameterID::playDir.getParamID(),
        playDirKnob};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CaptureAudioProcessorEditor)
};
