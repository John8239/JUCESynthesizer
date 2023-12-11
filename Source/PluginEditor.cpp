/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Oscillator.h"
#include "Filter.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscGUI(p), envGUI(p), filterGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 400);

    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
    
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (juce::Graphics& g)
{
    const juce::Colour gradientColor1 = juce::Colour::fromString("#ff331800");
    const juce::Colour gradientColor2 = juce::Colour::fromString("#ffb35300");
    const juce::Colour textColor = juce::Colour::fromString("#ffebdcc7");
    const juce::Rectangle<int> rect = getLocalBounds();

    g.setGradientFill(juce::ColourGradient::ColourGradient(
        gradientColor1, rect.getTopLeft().getX(), rect.getTopLeft().getY(),
        gradientColor2, rect.getBottomRight().getX(), rect.getBottomRight().getY(), true
    ));
    g.fillRect(0, 0, rect.getWidth(), rect.getHeight());

    g.setFont(juce::Font(24.0f));
    g.setColour(textColor);
    g.drawText("My Plugin", getLocalBounds(), juce::Justification::centredTop, true);
}

void SynthFrameworkAudioProcessorEditor::resized()
{
    const int componentWidth = 250;
    const int componentHeight = 250;
    juce::Rectangle<int> area = getLocalBounds();

    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}