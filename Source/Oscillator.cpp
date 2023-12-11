/*
  ==============================================================================

    Oscillator.cpp
    Created: 2 Dec 2023 8:01:27pm
    Author:  John

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFrameworkAudioProcessor& p) : audioProcessor(p)
{
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);

    addAndMakeVisible(oscMenu);
    oscMenu.addListener(this);

    oscMenu.setJustificationType(juce::Justification::centred);

    waveSelection = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "waveType", oscMenu);

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);
    oscMenu.setBounds(area.removeFromTop(20));

}

void Oscillator::comboBoxChanged(juce::ComboBox*)
{

}
