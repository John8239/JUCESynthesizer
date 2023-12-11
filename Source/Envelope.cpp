/*
  ==============================================================================

    Envelope.cpp
    Created: 3 Dec 2023 1:15:10pm
    Author:  John

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"
#include "PluginProcessor.h"

//==============================================================================
Envelope::Envelope(SynthFrameworkAudioProcessor& p) : audioProcessor(p)
{
    setSize(300, 350);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1, 5000);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40.0, 30);
    attackSlider.setNumDecimalPlacesToDisplay(1);
    attackSlider.setValue(0.1f);

    attackLabel.setText("A", juce::NotificationType::dontSendNotification);
    attackLabel.attachToComponent(&attackSlider, false);
    attackLabel.setJustificationType(juce::Justification::centred);

    //==============================================================================

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1, 5000);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40.0, 30);
    releaseSlider.setNumDecimalPlacesToDisplay(1);
    releaseSlider.setValue(0.1f);

    releaseLabel.setText("R", juce::NotificationType::dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, false);
    releaseLabel.setJustificationType(juce::Justification::centred);

    //==============================================================================

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.1, 5000);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40.0, 30);
    sustainSlider.setNumDecimalPlacesToDisplay(1);
    sustainSlider.setValue(0.1f);

    sustainLabel.setText("S", juce::NotificationType::dontSendNotification);
    sustainLabel.attachToComponent(&sustainSlider, false);
    sustainLabel.setJustificationType(juce::Justification::centred);

    //==============================================================================

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1, 5000);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40.0, 30);
    decaySlider.setNumDecimalPlacesToDisplay(1);
    decaySlider.setValue(0.1f);

    decayLabel.setText("D", juce::NotificationType::dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, false);
    decayLabel.setJustificationType(juce::Justification::centred);

    //==============================================================================

    addAndMakeVisible(&attackSlider);
    addAndMakeVisible(&releaseSlider);
    addAndMakeVisible(&sustainSlider);
    addAndMakeVisible(&decaySlider);

    attackTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "attack", attackSlider);
    releaseTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "release", releaseSlider);
    sustainTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "sustain", sustainSlider);
    decayTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "decay", decaySlider);

}

Envelope::~Envelope()
{
    attackTree.~ScopedPointer();
    releaseTree.~ScopedPointer();
    sustainTree.~ScopedPointer();
    decayTree.~ScopedPointer();
}

void Envelope::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 30, getWidth(), 20);

    g.setColour(juce::Colours::white);
    g.drawText("Envelope", titleArea, juce::Justification::centred);
}

void Envelope::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(45);

    int sliderWidth = 40;
    int sliderHeight = 225;

    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(40));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(40));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(40));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(40));

    /*attackSlider.setBounds(10, 65, 50, 180);
    releaseSlider.setBounds(65, 65, 50, 180);
    sustainSlider.setBounds(120, 65, 50, 180);
    decaySlider.setBounds(175, 65, 50, 180);*/
}
