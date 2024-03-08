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
    CaptureAudioProcessor &audioProcessor;

private:
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

    // Modulation
    juce::Slider grainDenseModDepthKnob;
    juce::Slider grainLengthModDepthKnob;
    juce::Slider playSpeedModDepthKnob;
    juce::Slider delayTimeModDepthKnob;
    juce::Slider delayLazynessModDepthKnob;
    juce::Slider delayInputModDepthKnob;

    juce::Slider grainDenseModIndexKnob;
    juce::Slider grainLengthModIndexKnob;
    juce::Slider playSpeedModIndexKnob;
    juce::Slider delayTimeModIndexKnob;
    juce::Slider delayLazynessModIndexKnob;
    juce::Slider delayInputModIndexKnob;

    juce::Slider mod0Freq;
    juce::Slider mod1Freq;
    juce::Slider mod2Freq;
    juce::Slider mod3Freq;

    juce::Slider mix0Mod0;
    juce::Slider mix0Mod1;
    juce::Slider mix0Mod2;
    juce::Slider mix0Mod3;

    juce::Slider mix1Mod0;
    juce::Slider mix1Mod1;
    juce::Slider mix1Mod2;
    juce::Slider mix1Mod3;

    juce::Slider mix2Mod0;
    juce::Slider mix2Mod1;
    juce::Slider mix2Mod2;
    juce::Slider mix2Mod3;

    juce::Slider mix3Mod0;
    juce::Slider mix3Mod1;
    juce::Slider mix3Mod2;
    juce::Slider mix3Mod3;

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

    juce::Label grainDenseModLabel;
    juce::Label grainLengthModLabel;
    juce::Label playSpeedModLabel;
    juce::Label delayTimeModLabel;
    juce::Label delayLazynessModLabel;
    juce::Label delayInputModLabel;
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

    // Modulation
    SliderAttachment grainDenseModDepthAttachment{
        audioProcessor.apvts,
        ParameterID::grainDenseModDepth.getParamID(),
        grainDenseModDepthKnob};
    SliderAttachment grainLengthModDepthAttachment{
        audioProcessor.apvts,
        ParameterID::grainLengthModDepth.getParamID(),
        grainLengthModDepthKnob};
    SliderAttachment playSpeedModDepthAttachment{
        audioProcessor.apvts,
        ParameterID::playSpeedModDepth.getParamID(),
        playSpeedModDepthKnob};
    SliderAttachment delayTimeModDepthAttachment{
        audioProcessor.apvts,
        ParameterID::delayTimeModDepth.getParamID(),
        delayTimeModDepthKnob};
    SliderAttachment delayLazynessModDepthAttachment{
        audioProcessor.apvts,
        ParameterID::delayLazynessModDepth.getParamID(),
        delayLazynessModDepthKnob};
    SliderAttachment delayInputModDepthKnobAttachment{
        audioProcessor.apvts,
        ParameterID::delayInputModDepth.getParamID(),
        delayInputModDepthKnob};

    SliderAttachment grainDenseModIndexAttachment{
        audioProcessor.apvts,
        ParameterID::grainDenseModIndex.getParamID(),
        grainDenseModIndexKnob};
    SliderAttachment grainLengthModIndexAttachment{
        audioProcessor.apvts,
        ParameterID::grainLengthModIndex.getParamID(),
        grainLengthModIndexKnob};
    SliderAttachment playSpeedModIndexAttachment{
        audioProcessor.apvts,
        ParameterID::playSpeedModIndex.getParamID(),
        playSpeedModIndexKnob};
    SliderAttachment delayTimeModIndexAttachment{
        audioProcessor.apvts,
        ParameterID::delayTimeModIndex.getParamID(),
        delayTimeModIndexKnob};
    SliderAttachment delayLazynessModIndexAttachment{
        audioProcessor.apvts,
        ParameterID::delayLazynessModIndex.getParamID(),
        delayLazynessModIndexKnob};
    SliderAttachment delayInputModIndexKnobAttachment{
        audioProcessor.apvts,
        ParameterID::delayInputModIndex.getParamID(),
        delayInputModIndexKnob};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CaptureAudioProcessorEditor)
};
