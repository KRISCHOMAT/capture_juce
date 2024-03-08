/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CaptureAudioProcessorEditor::CaptureAudioProcessorEditor(CaptureAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p), waveViewer(*this), levelMeter(&p)
{

    int textBoxWidth = 80;
    int textBoxHeight = 20;

    // Knobs
    loopStartKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    loopStartKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(loopStartKnob);

    loopLengthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    loopLengthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(loopLengthKnob);

    grainLengthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainLengthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(grainLengthKnob);

    densKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    densKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(densKnob);

    playSpeedKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    playSpeedKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(playSpeedKnob);

    sprayKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sprayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(sprayKnob);

    spreadKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    spreadKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(spreadKnob);

    grainDirKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainDirKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(grainDirKnob);

    playDirKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    playDirKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(playDirKnob);

    delaytimeKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delaytimeKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delaytimeKnob);

    delayFeedbackKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayFeedbackKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayFeedbackKnob);

    delayLazynessKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayLazynessKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayLazynessKnob);

    delayInputGainKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayInputGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayInputGainKnob);

    delayOutputGainKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayOutputGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayOutputGainKnob);

    releaseKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(releaseKnob);

    attackKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(attackKnob);

    delayModDepthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayModDepthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayModDepthKnob);

    delayModSpeedKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayModSpeedKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayModSpeedKnob);

    // Modulation
    grainDenseModDepthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainDenseModDepthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(grainDenseModDepthKnob);

    grainLengthModDepthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainLengthModDepthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(grainLengthModDepthKnob);

    playSpeedModDepthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    playSpeedModDepthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(playSpeedModDepthKnob);

    delayTimeModDepthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeModDepthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayTimeModDepthKnob);

    delayLazynessModDepthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayLazynessModDepthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayLazynessModDepthKnob);

    delayInputModDepthKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayInputModDepthKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayInputModDepthKnob);

    grainDenseModIndexKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainDenseModIndexKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(grainDenseModIndexKnob);

    grainLengthModIndexKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    grainLengthModIndexKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(grainLengthModIndexKnob);

    playSpeedModIndexKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    playSpeedModIndexKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(playSpeedModIndexKnob);

    delayTimeModIndexKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeModIndexKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayTimeModIndexKnob);

    delayLazynessModIndexKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayLazynessModIndexKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayLazynessModIndexKnob);

    delayInputModIndexKnob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayInputModIndexKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(delayInputModIndexKnob);

    addAndMakeVisible(delayModSpeedKnob);
    // custom components
    addAndMakeVisible(waveViewer);
    addAndMakeVisible(levelMeter);

    // Labels
    loopStartLabel.attachToComponent(&loopStartKnob, false);
    loopStartLabel.setText("Loop-Start", juce::NotificationType::dontSendNotification);
    loopStartLabel.setJustificationType(juce::Justification::centred);

    loopLengthLabel.attachToComponent(&loopLengthKnob, false);
    loopLengthLabel.setText("Loop-Length", juce::NotificationType::dontSendNotification);
    loopLengthLabel.setJustificationType(juce::Justification::centred);

    grainLengthLabel.attachToComponent(&grainLengthKnob, false);
    grainLengthLabel.setText("Grain-Length", juce::NotificationType::dontSendNotification);
    grainLengthLabel.setJustificationType(juce::Justification::centred);

    densLabel.attachToComponent(&densKnob, false);
    densLabel.setText("Dens", juce::NotificationType::dontSendNotification);
    densLabel.setJustificationType(juce::Justification::centred);

    playSpeedLabel.attachToComponent(&playSpeedKnob, false);
    playSpeedLabel.setText("Play-Speed", juce::NotificationType::dontSendNotification);
    playSpeedLabel.setJustificationType(juce::Justification::centred);

    sprayLabel.attachToComponent(&sprayKnob, false);
    sprayLabel.setText("Spray", juce::NotificationType::dontSendNotification);
    sprayLabel.setJustificationType(juce::Justification::centred);

    spreadLabel.attachToComponent(&spreadKnob, false);
    spreadLabel.setText("Spread", juce::NotificationType::dontSendNotification);
    spreadLabel.setJustificationType(juce::Justification::centred);

    grainDirLabel.attachToComponent(&grainDirKnob, false);
    grainDirLabel.setText("Grain-Dir", juce::NotificationType::dontSendNotification);
    grainDirLabel.setJustificationType(juce::Justification::centred);

    playDirLabel.attachToComponent(&playDirKnob, false);
    playDirLabel.setText("Play-Dir", juce::NotificationType::dontSendNotification);
    playDirLabel.setJustificationType(juce::Justification::centred);

    attackLabel.attachToComponent(&attackKnob, false);
    attackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);

    releaseLabel.attachToComponent(&releaseKnob, false);
    releaseLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);

    dlFeedbackLabel.attachToComponent(&delayFeedbackKnob, false);
    dlFeedbackLabel.setText("Feedback", juce::NotificationType::dontSendNotification);
    dlFeedbackLabel.setJustificationType(juce::Justification::centred);

    dlTimeLabel.attachToComponent(&delaytimeKnob, false);
    dlTimeLabel.setText("Time", juce::NotificationType::dontSendNotification);
    dlTimeLabel.setJustificationType(juce::Justification::centred);

    dlLazynessLabel.attachToComponent(&delayLazynessKnob, false);
    dlLazynessLabel.setText("Lazyness", juce::NotificationType::dontSendNotification);
    dlLazynessLabel.setJustificationType(juce::Justification::centred);

    dlInputLabel.attachToComponent(&delayInputGainKnob, false);
    dlInputLabel.setText("Input", juce::NotificationType::dontSendNotification);
    dlInputLabel.setJustificationType(juce::Justification::centred);

    dlOuputLabel.attachToComponent(&delayOutputGainKnob, false);
    dlOuputLabel.setText("Output", juce::NotificationType::dontSendNotification);
    dlOuputLabel.setJustificationType(juce::Justification::centred);

    dlModSpeedLabel.attachToComponent(&delayModSpeedKnob, false);
    dlModSpeedLabel.setText("Mod-Speed", juce::NotificationType::dontSendNotification);
    dlModSpeedLabel.setJustificationType(juce::Justification::centred);

    dlModDepthLabel.attachToComponent(&delayModDepthKnob, false);
    dlModDepthLabel.setText("Mod-Depth", juce::NotificationType::dontSendNotification);
    dlModDepthLabel.setJustificationType(juce::Justification::centred);

    grainDenseModLabel.attachToComponent(&grainDenseModDepthKnob, false);
    grainDenseModLabel.setText("Dense", juce::NotificationType::dontSendNotification);
    grainDenseModLabel.setJustificationType(juce::Justification::centred);

    grainLengthModLabel.attachToComponent(&grainLengthModDepthKnob, false);
    grainLengthModLabel.setText("Length", juce::NotificationType::dontSendNotification);
    grainLengthModLabel.setJustificationType(juce::Justification::centred);

    playSpeedModLabel.attachToComponent(&playSpeedModDepthKnob, false);
    playSpeedModLabel.setText("Speed", juce::NotificationType::dontSendNotification);
    playSpeedModLabel.setJustificationType(juce::Justification::centred);

    delayTimeModLabel.attachToComponent(&delayTimeModDepthKnob, false);
    delayTimeModLabel.setText("DL Time", juce::NotificationType::dontSendNotification);
    delayTimeModLabel.setJustificationType(juce::Justification::centred);

    delayLazynessModLabel.attachToComponent(&delayLazynessModDepthKnob, false);
    delayLazynessModLabel.setText("DL Lazy", juce::NotificationType::dontSendNotification);
    delayLazynessModLabel.setJustificationType(juce::Justification::centred);

    delayInputModLabel.attachToComponent(&delayInputModDepthKnob, false);
    delayInputModLabel.setText("DL In", juce::NotificationType::dontSendNotification);
    delayInputModLabel.setJustificationType(juce::Justification::centred);
    setSize(600, 850);
}

CaptureAudioProcessorEditor::~CaptureAudioProcessorEditor()
{
}

//==============================================================================
void CaptureAudioProcessorEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colour::fromRGB(8, 41, 67));
    g.setColour(juce::Colours::white);
    g.setFont(40.0f);
    g.drawText("Capture", 20, 20, getWidth() - 40, 40, juce::Justification::topRight, true);
}

void CaptureAudioProcessorEditor::resized()
{
    int knobWidth = 80;
    int knobHeight = 90;
    int padding = 20;
    int marginTop = 220;

    levelMeter.setBounds(padding, padding / 2, 100, 50);
    waveViewer.setBounds(padding, padding + 50, getWidth() - (padding * 2), 100);

    // grain row
    loopStartKnob.setBounds(padding, marginTop, knobWidth, knobHeight);
    loopLengthKnob.setBounds(padding + knobWidth * 1, marginTop, knobWidth, knobHeight);
    grainLengthKnob.setBounds(padding + knobWidth * 2, marginTop, knobWidth, knobHeight);
    densKnob.setBounds(padding + knobWidth * 3, marginTop, knobWidth, knobHeight);
    playSpeedKnob.setBounds(padding + knobWidth * 4, marginTop, knobWidth, knobHeight);
    sprayKnob.setBounds(padding + knobWidth * 5, marginTop, knobWidth, knobHeight);
    spreadKnob.setBounds(padding + knobWidth * 6, marginTop, knobWidth, knobHeight);

    // grainDir & Env
    grainDirKnob.setBounds(padding + knobWidth * 1, marginTop + knobHeight + 50, knobWidth, knobHeight);
    playDirKnob.setBounds(padding + knobWidth * 2, marginTop + knobHeight + 50, knobWidth, knobHeight);
    attackKnob.setBounds(padding + knobWidth * 4, marginTop + knobHeight + 50, knobWidth, knobHeight);
    releaseKnob.setBounds(padding + knobWidth * 5, marginTop + knobHeight + 50, knobWidth, knobHeight);

    // Delay Row
    delayFeedbackKnob.setBounds(padding, marginTop + knobHeight * 2 + 100, knobWidth, knobHeight);
    delaytimeKnob.setBounds(padding + knobWidth * 1, marginTop + knobHeight * 2 + 100, knobWidth, knobHeight);
    delayLazynessKnob.setBounds(padding + knobWidth * 2, marginTop + knobHeight * 2 + 100, knobWidth, knobHeight);
    delayInputGainKnob.setBounds(padding + knobWidth * 3, marginTop + knobHeight * 2 + 100, knobWidth, knobHeight);
    delayOutputGainKnob.setBounds(padding + knobWidth * 4, marginTop + knobHeight * 2 + 100, knobWidth, knobHeight);
    delayModSpeedKnob.setBounds(padding + knobWidth * 5, marginTop + knobHeight * 2 + 100, knobWidth, knobHeight);
    delayModDepthKnob.setBounds(padding + knobWidth * 6, marginTop + knobHeight * 2 + 100, knobWidth, knobHeight);

    // Modulation Row Depth
    grainDenseModDepthKnob.setBounds(padding, marginTop + knobHeight * 3 + 150, knobWidth, knobHeight);
    grainLengthModDepthKnob.setBounds(padding + knobWidth * 1, marginTop + knobHeight * 3 + 150, knobWidth, knobHeight);
    playSpeedModDepthKnob.setBounds(padding + knobWidth * 2, marginTop + knobHeight * 3 + 150, knobWidth, knobHeight);
    delayTimeModDepthKnob.setBounds(padding + knobWidth * 3, marginTop + knobHeight * 3 + 150, knobWidth, knobHeight);
    delayLazynessModDepthKnob.setBounds(padding + knobWidth * 4, marginTop + knobHeight * 3 + 150, knobWidth, knobHeight);
    delayInputModDepthKnob.setBounds(padding + knobWidth * 5, marginTop + knobHeight * 3 + 150, knobWidth, knobHeight);

    grainDenseModIndexKnob.setBounds(padding, marginTop + knobHeight * 4 + 150, knobWidth, knobHeight);
    grainLengthModIndexKnob.setBounds(padding + knobWidth * 1, marginTop + knobHeight * 4 + 150, knobWidth, knobHeight);
    playSpeedModIndexKnob.setBounds(padding + knobWidth * 2, marginTop + knobHeight * 4 + 150, knobWidth, knobHeight);
    delayTimeModIndexKnob.setBounds(padding + knobWidth * 3, marginTop + knobHeight * 4 + 150, knobWidth, knobHeight);
    delayLazynessModIndexKnob.setBounds(padding + knobWidth * 4, marginTop + knobHeight * 4 + 150, knobWidth, knobHeight);
    delayInputModIndexKnob.setBounds(padding + knobWidth * 5, marginTop + knobHeight * 4 + 150, knobWidth, knobHeight);
}
