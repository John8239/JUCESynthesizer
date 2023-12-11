/*
  ==============================================================================

    SynthSound.h
    Created: 20 Nov 2023 5:51:52pm
    Author:  John

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
    public:

        bool juce::SynthesiserSound::appliesToNote(int midiNoteNumber)
        {
            return true;
        }

        bool juce::SynthesiserSound::appliesToChannel(int midiChannel)
        {
            return true;
        }

    private:

};