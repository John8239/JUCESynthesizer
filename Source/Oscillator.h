/*
  ==============================================================================

    Oscillator.h
    Created: 2 Dec 2023 8:01:27pm
    Author:  John

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator : public juce::Component,
                   public juce::ComboBox::Listener // TODO: in the tutorial he sets this to private....
{
public:
    Oscillator(SynthFrameworkAudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:
    juce::ComboBox oscMenu;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    SynthFrameworkAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
