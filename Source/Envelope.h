/*
  ==============================================================================

    Envelope.h
    Created: 3 Dec 2023 1:15:10pm
    Author:  John

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope  : public juce::Component
{
public:
    Envelope(SynthFrameworkAudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> attackTree;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> decayTree;

    juce::Slider attackSlider;
    juce::Slider releaseSlider;
    juce::Slider sustainSlider;
    juce::Slider decaySlider;

    juce::Label attackLabel;
    juce::Label releaseLabel;
    juce::Label sustainLabel;
    juce::Label decayLabel;

    SynthFrameworkAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
