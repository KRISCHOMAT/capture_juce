
#pragma once
#include <JuceHeader.h>

class LevelMeter : public juce::Component, public juce::Timer
{
public:
    LevelMeter(CaptureAudioProcessor *p)
        : processor(p)
    {
        startTimerHz(30);
    }

    ~LevelMeter() override {}

    void paint(juce::Graphics &g) override
    {
        int meterHeight = getHeight() / 2;
        int halfMeterHeight = meterHeight / 2;

        int height = getHeight();
        int padding = height * 0.1;

        g.setColour(juce::Colours::white);
        g.drawText("In", 0, 0, getWidth(), meterHeight, juce::Justification::centredLeft);
        g.drawText("Out", 0, meterHeight, getWidth(), meterHeight, juce::Justification::centredLeft);

        g.fillRect(25, 0, int(getWidth() * smoothedInputRms), 20);
        g.fillRect(25, meterHeight, int(getWidth() * smoothedOutputRmsL), 10);
        g.fillRect(25, meterHeight + halfMeterHeight, int(getWidth() * smoothedOutputRmsR), 10);
    }

    void resized() override {}

    void timerCallback() override
    {
        smooth(smoothedInputRms, processor->inputRms);
        smooth(smoothedOutputRmsL, processor->outputRmsL);
        smooth(smoothedOutputRmsR, processor->outputRmsR);

        repaint();
    }

private:
    CaptureAudioProcessor *processor;

    float smoothedInputRms{0.0f};
    float smoothedOutputRmsL{0.0f};
    float smoothedOutputRmsR{0.0f};

    void smooth(float &smoothedInput, const float &input, float alpha = 0.8f)
    {
        float inputLog = 20.0f * log10(input);
        float smoothedLog = alpha * inputLog + (1 - alpha) * smoothedLog;
        smoothedInput = pow(10, smoothedLog / 20.0f);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LevelMeter)
};
