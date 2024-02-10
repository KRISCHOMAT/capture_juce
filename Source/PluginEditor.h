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
    juce::Slider delaytimeKnob;
    juce::Slider delayFeedbackKnob;
    juce::Slider delayLazynessKnob;
    juce::Slider delayInputGainKnob;
    juce::Slider delayOutputGainKnob;
    juce::Slider attackKnob;
    juce::Slider releaseKnob;
    juce::Slider delayModDepthKnob;
    juce::Slider delayModSpeedKnob;

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
    juce::Label attackLabel;
    juce::Label releaseLabel;
    juce::Label dlTimeLabel;
    juce::Label dlFeedbackLabel;
    juce::Label dlLazynessLabel;
    juce::Label dlInputLabel;
    juce::Label dlOuputLabel;
    juce::Label dlModDepthLabel;
    juce::Label dlModSpeedLabel;

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
    SliderAttachment delaytimeAttachment{
        audioProcessor.apvts,
        ParameterID::delaytime.getParamID(),
        delaytimeKnob};
    SliderAttachment delayFeedbackAttachment{
        audioProcessor.apvts,
        ParameterID::delayFeedback.getParamID(),
        delayFeedbackKnob};
    SliderAttachment delayLazynessAttachment{
        audioProcessor.apvts,
        ParameterID::interpolationTime.getParamID(),
        delayLazynessKnob};
    SliderAttachment delayInputGainAttachment{
        audioProcessor.apvts,
        ParameterID::delayInputGain.getParamID(),
        delayInputGainKnob};
    SliderAttachment delayOutputGainAttachment{
        audioProcessor.apvts,
        ParameterID::delayOutputGain.getParamID(),
        delayOutputGainKnob};
    SliderAttachment attackAttachment{
        audioProcessor.apvts,
        ParameterID::attack.getParamID(),
        attackKnob};
    SliderAttachment releaseAttachment{
        audioProcessor.apvts,
        ParameterID::release.getParamID(),
        releaseKnob};
    SliderAttachment dlModSpeedAttachment{
        audioProcessor.apvts,
        ParameterID::delayModSpeed.getParamID(),
        delayModSpeedKnob};
    SliderAttachment dlModDepthAttachment{
        audioProcessor.apvts,
        ParameterID::delayModDepth.getParamID(),
        delayModDepthKnob};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CaptureAudioProcessorEditor)
};
