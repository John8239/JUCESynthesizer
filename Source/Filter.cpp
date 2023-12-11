/*
  ==============================================================================

    Filter.cpp
    Created: 9 Dec 2023 9:58:42am
    Author:  John

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"
#include "PluginProcessor.h"

//==============================================================================
Filter::Filter(SynthFrameworkAudioProcessor& p) : audioProcessor(p)
{
    setSize(250, 350);

    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    filterMenu.setJustificationType(juce::Justification::centred);
    filterTypeValue = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "filterType", filterMenu);

    filterCutoff.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0f, 10000.0f);
    filterCutoff.setValue(400.0);
    filterCutoff.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    // the AudioProcessorValueStateTree::SliderAttachment must come before the setSkewFactorFromMidPoint
    filterValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "filterCutoff", filterCutoff);
    filterCutoff.setSkewFactorFromMidPoint(1000.0f);

    filterRes.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1, 5);
    filterRes.setValue(1);
    filterRes.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    resValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "filterRes", filterRes);

    addAndMakeVisible(&filterMenu);
    addAndMakeVisible(&filterCutoff);
    addAndMakeVisible(&filterRes);
}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 30, getWidth(), 20);

    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);
}

void Filter::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100, 100, 70, 70);

}
