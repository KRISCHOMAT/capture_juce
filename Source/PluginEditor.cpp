/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CaptureAudioProcessorEditor::CaptureAudioProcessorEditor(CaptureAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p), waveViewer(p.synth.loopBuffer, *this)
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

  addAndMakeVisible(waveViewer);

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

  setSize(600, 550);
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

  waveViewer.setBounds(padding, padding + 50, getWidth() - (padding * 2), 100);

  loopStartKnob.setBounds(padding, marginTop, knobWidth, knobHeight);
  loopLengthKnob.setBounds(padding + knobWidth * 1, marginTop, knobWidth, knobHeight);
  grainLengthKnob.setBounds(padding + knobWidth * 2, marginTop, knobWidth, knobHeight);
  densKnob.setBounds(padding + knobWidth * 3, marginTop, knobWidth, knobHeight);
  playSpeedKnob.setBounds(padding + knobWidth * 4, marginTop, knobWidth, knobHeight);
  sprayKnob.setBounds(padding + knobWidth * 5, marginTop, knobWidth, knobHeight);
  spreadKnob.setBounds(padding + knobWidth * 6, marginTop, knobWidth, knobHeight);
  grainDirKnob.setBounds(padding, marginTop + knobHeight + 50, knobWidth, knobHeight);
  playDirKnob.setBounds(padding + knobWidth * 1, marginTop + knobHeight + 50, knobWidth, knobHeight);
}
