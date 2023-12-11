/*
  ==============================================================================

    Filter.h
    Created: 9 Dec 2023 9:58:42am
    Author:  John

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Filter.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(SynthFrameworkAudioProcessor& p);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    juce::Slider filterCutoff;
    juce::Slider filterRes;

    juce::ComboBox filterMenu;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> filterValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> resValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeValue; 

    SynthFrameworkAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
