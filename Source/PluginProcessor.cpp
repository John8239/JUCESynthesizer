/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessor::SynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                        attackTime(0.1f),
                        releaseTime(0.1f),
                        sustainTime(0.1f),
                        decayTime(0.1f),
                        tree(*this, nullptr)
#endif
{
    juce::NormalisableRange<float> attackParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> releaseParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> decayParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> sustainParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> waveTypeParam(0.0f, 2.0f);
    juce::NormalisableRange<float> filterValueParam(20.0f, 10000.0f);
    juce::NormalisableRange<float> filterResParam(1.0f, 5.0f);

    juce::NormalisableRange<float> filterTypeValueParam(0, 2);

    tree.createAndAddParameter(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>("attack", "Attack", "Attack", attackParam, 0.1f, nullptr, nullptr));
    tree.createAndAddParameter(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>("release", "Release", "Release", releaseParam, 0.1f, nullptr, nullptr));
    tree.createAndAddParameter(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>("sustain", "Sustain", "Sustain", sustainParam, 0.1f, nullptr, nullptr));
    tree.createAndAddParameter(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>("decay", "Decay", "Decay", decayParam, 0.1f, nullptr, nullptr));
    tree.createAndAddParameter(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>("waveType", "waveType", "waveType", waveTypeParam, 0.0f, nullptr, nullptr));
    tree.createAndAddParameter(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>("filterCutoff", "FilterCutoff", "filterCutoff", filterValueParam, 400.0f, nullptr, nullptr));
    tree.createAndAddParameter(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>("filterRes", "filterRes", "filterRes", filterResParam, 1.0f, nullptr, nullptr));

    tree.createAndAddParameter(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>("filterType", "filterType", "filterType", filterTypeValueParam, 0, nullptr, nullptr));

    tree.state = juce::ValueTree("savedPar");
    
    mySynth.clearVoices();
    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

SynthFrameworkAudioProcessor::~SynthFrameworkAudioProcessor()
{
}

//==============================================================================
const juce::String SynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthFrameworkAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthFrameworkAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {

            myVoice->getEnvelopeParam((float*)tree.getRawParameterValue("attack"), 
                              (float*)tree.getRawParameterValue("release"), 
                              (float*)tree.getRawParameterValue("sustain"),
                              (float*)tree.getRawParameterValue("decay"));

            myVoice->getOscType((float*)tree.getRawParameterValue("waveType"));

            myVoice->getFilterParams((float*)tree.getRawParameterValue("filterType"),
                                     (float*)tree.getRawParameterValue("filterCutoff"),
                                     (float*)tree.getRawParameterValue("filterRes"));
        }
    }

    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthFrameworkAudioProcessor::createEditor()
{
    return new SynthFrameworkAudioProcessorEditor (*this);
}

//==============================================================================
void SynthFrameworkAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthFrameworkAudioProcessor();
}
