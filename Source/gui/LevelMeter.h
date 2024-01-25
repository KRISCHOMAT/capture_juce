class LevelMeter : public juce::Component, public juce::Timer
{
public:
    LevelMeter(float const &inputMagnitute_, float const &outputMagnitute_)
        : inputMagnitute(inputMagnitute_), outputMagnitute(outputMagnitute_), inputSmoothed(inputMagnitute_), outputSmoothed(outputMagnitute_)
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        startTimerHz(30); // Adjust timer frequency as needed
    }

    ~LevelMeter() override {}

    void paint(juce::Graphics &g) override
    {
        int meterHeight = getHeight() / 2;
        int halfMeterHeight = meterHeight / 2;

        g.setColour(juce::Colours::white);
        g.drawText("In", 0, 0, getWidth(), meterHeight, juce::Justification::centredLeft);
        g.drawText("Out", 0, meterHeight, getWidth(), meterHeight, juce::Justification::centredLeft);

        g.fillRect(25, 0, int(getWidth() * inputSmoothed), 20);
        g.fillRect(25, meterHeight, int(getWidth() * outputSmoothed), 20);
    }

    void resized() override {}

    void timerCallback() override
    {
        // Smooth input and output values
        smoothInput();
        smoothOutput();

        // Repaint component
        repaint();
    }

private:
    float const &inputMagnitute;
    float const &outputMagnitute;

    float inputSmoothed;
    float outputSmoothed;

    void smoothInput()
    {
        // You can adjust the smoothing factor (alpha) to control the smoothness
        float alpha = 0.2f; // Adjust as needed
        inputSmoothed = alpha * inputMagnitute + (1 - alpha) * inputSmoothed;
    }

    void smoothOutput()
    {
        // You can adjust the smoothing factor (alpha) to control the smoothness
        float alpha = 0.2f; // Adjust as needed
        outputSmoothed = alpha * outputMagnitute + (1 - alpha) * outputSmoothed;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LevelMeter)
};
