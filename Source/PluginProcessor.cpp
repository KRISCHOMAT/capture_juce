/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

template <typename T>
inline static void castParameter(juce::AudioProcessorValueTreeState &apvts,
                                 const juce::ParameterID &id, T &destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);
}

//==============================================================================
CaptureAudioProcessor::CaptureAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
      )
#endif
{

    castParameter(apvts, ParameterID::loopStart, loopStartParam);
    castParameter(apvts, ParameterID::loopLength, loopLengthParam);
    castParameter(apvts, ParameterID::grainLength, grainLengthParam);
    castParameter(apvts, ParameterID::dens, densParam);
    castParameter(apvts, ParameterID::playSpeed, playSpeedParam);
    castParameter(apvts, ParameterID::spray, sprayParam);
    castParameter(apvts, ParameterID::spread, spreadParam);
    castParameter(apvts, ParameterID::grainDir, grainDirParam);
    castParameter(apvts, ParameterID::playDir, playDirParam);
    castParameter(apvts, ParameterID::delayFeedback, delayFeedbackParam);
    castParameter(apvts, ParameterID::delaytime, delaytimeParam);
    castParameter(apvts, ParameterID::interpolationTime, interpolationTimeParam);
    castParameter(apvts, ParameterID::delayInputGain, delayInputGainParam);
    castParameter(apvts, ParameterID::delayOutputGain, delayOutputGainParam);
    castParameter(apvts, ParameterID::attack, attackParam);
    castParameter(apvts, ParameterID::release, releaseParam);

    apvts.state.addListener(this);
}

CaptureAudioProcessor::~CaptureAudioProcessor()
{
    apvts.state.removeListener(this);
}

juce::AudioProcessorValueTreeState::ParameterLayout CaptureAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::loopStart,
        "Loop Start",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::loopLength,
        "Loop Length",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        100.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::grainLength,
        "Grainlength",
        juce::NormalisableRange<float>(1.0f, 1000.0f, 1.0f),
        100.0f,
        juce::AudioParameterFloatAttributes().withLabel("ms")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::dens,
        "Dens",
        juce::NormalisableRange<float>(1.0, 1000.0f, 1.0f),
        100.0f,
        juce::AudioParameterFloatAttributes().withLabel("ms")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::playSpeed,
        "Play Speed",
        juce::NormalisableRange<float>(0.0f, 4.0f, 0.01f),
        0.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::spray,
        "Spray",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::spread,
        "Spread",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParameterID::grainDir,
        "Grain Direction",
        juce::StringArray{"Forward", "Reverse", "Back & Forth"}, 0));

    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParameterID::playDir,
        "Play Direction",
        juce::StringArray{"Forward", "Reverse", "Back & Forth"}, 0));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::delayFeedback,
        "Feedback",
        juce::NormalisableRange<float>(0.01f, 2.0f, 0.01f),
        0.5f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::delaytime,
        "Time",
        juce::NormalisableRange<float>(0.01f, 1.0f, 0.01f),
        0.5f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::interpolationTime,
        "Interpolation Time",
        juce::NormalisableRange<float>(0.01f, 1.0f, 0.01f),
        0.01f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::delayInputGain,
        "Input Gain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.01f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::delayOutputGain,
        "Output Gain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.01f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::attack,
        "Attack",
        juce::NormalisableRange<float>(0.1f, 10.0f, 0.01f),
        0.01f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::release,
        "Release",
        juce::NormalisableRange<float>(0.1f, 10.0f, 0.01f),
        0.01f));

    return layout;
}

//==============================================================================
const juce::String CaptureAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CaptureAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool CaptureAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool CaptureAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double CaptureAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CaptureAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int CaptureAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CaptureAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String CaptureAudioProcessor::getProgramName(int index)
{
    return {};
}

void CaptureAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
}

//==============================================================================
void CaptureAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    const int totalNumInputChannels = getTotalNumInputChannels();
    const int loopBufferSize = 10 * sampleRate;
    synth.init(totalNumInputChannels, loopBufferSize, sampleRate);
}

void CaptureAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CaptureAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void CaptureAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    inputRms = buffer.getRMSLevel(0, 0, buffer.getNumSamples());

    bool expected = true;
    if (parametersChanged.compare_exchange_strong(expected, false))
    {
        update();
    }

    float *writePtrs[2] = {buffer.getWritePointer(0), buffer.getWritePointer(1)};

    synth.render(buffer.getReadPointer(0), writePtrs, buffer.getNumSamples());
    handleMidi(midiMessages);
    outputRmsL = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    outputRmsR = buffer.getRMSLevel(1, 0, buffer.getNumSamples());
}

void CaptureAudioProcessor::handleMidi(juce::MidiBuffer &midiMessages)
{
    uint8_t data1;
    uint8_t data2;
    uint8_t data3;

    for (const auto metadata : midiMessages)
    {
        data1 = metadata.data[0];
        data2 = metadata.data[1];
        data3 = metadata.data[2];
        synth.handleMidi(data1, data2, data3);
    }
}

//==============================================================================
bool CaptureAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *CaptureAudioProcessor::createEditor()
{
    // auto editor = new juce::GenericAudioProcessorEditor(*this);
    // // editor->addAndMakeVisible(waveViewer);
    // editor->setSize(500, 550);
    // return editor;

    return new CaptureAudioProcessorEditor(*this);
}

//==============================================================================
void CaptureAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CaptureAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new CaptureAudioProcessor();
}

void CaptureAudioProcessor::update()
{

    synth.setGrainLength(grainLengthParam->get());
    synth.setDensity(densParam->get());
    synth.setPlaySpeed(playSpeedParam->get());
    synth.setSpray(sprayParam->get() / 100.0f);
    synth.setSpread(spreadParam->get() / 100.0f);
    synth.setLoopStart(loopStartParam->get() / 100.0f);
    synth.setLoopLength(loopLengthParam->get() / 100.0f);
    synth.setDelayFeedback(delayFeedbackParam->get());
    synth.setDelaytime(delaytimeParam->get());
    synth.setInterpolationTime(interpolationTimeParam->get());
    synth.setDelayInputGain(delayInputGainParam->get());
    synth.setDelayOutputGain(delayOutputGainParam->get());
    synth.setAttack(attackParam->get());
    synth.setRelease(releaseParam->get());

    synth.playbackDir = static_cast<Synth::PlaybackDir>(playDirParam->getIndex());
    synth.grainDir = static_cast<Synth::PlaybackDir>(grainDirParam->getIndex());
}