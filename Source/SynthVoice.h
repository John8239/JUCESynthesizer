/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Nov 2023 5:52:01pm
    Author:  John

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
    public:

        bool juce::SynthesiserVoice::canPlaySound(juce::SynthesiserSound* sound)
        {
            return dynamic_cast<SynthSound*>(sound) != nullptr;
        }

        //=================== Oscillator ===================//
        void getOscType(float* selection)
        {
            theWave = *selection;
        }

        double setOscType()
        {
            if (theWave == 0)
            {
                return osc1.sinewave(frequency);
            }
            else if (theWave == 1)
            {
                return osc1.saw(frequency);
            }
            else if (theWave == 2)
            {
                return osc1.square(frequency);
            }
            else
            {
                return osc1.sinewave(frequency);
            }
        }

        //=================== Envelope ===================//

        void getEnvelopeParam(float* attack, float* release, float* sustain, float* decay)
        {
            env1.setAttack(double(*attack));
            env1.setRelease(double(*release));
            env1.setSustain(double(*sustain));
            env1.setDecay(double(*decay));
        }

        double setEnvelope()
        {
            return env1.adsr(setOscType(), env1.trigger);
        }

        //=================== Filter ===================//

        void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
        {
            filterChoice = *filterType;
            cutoff = *filterCutoff;
            filterRes = &resonance;
        }

        // LEFT OFF: at timestamp - 31:17 in JUCE Tutorial 26 - Build a Synth Part 6 (Filter and UI)
        double setFilter()
        {
            if (filterChoice == 0)
            {
                return filter1.lores(setEnvelope(), cutoff, resonance);
            }
            if (filterChoice == 1)
            {
                return filter1.hires(setEnvelope(), cutoff, resonance);
            }
            if (filterChoice == 2)
            {
                return filter1.bandpass(setEnvelope(), cutoff, resonance);
            }
            else
            {
                return filter1.lores(setEnvelope(), cutoff, resonance);
            }
        }

        //==================================================//

        void juce::SynthesiserVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
        {
            env1.trigger = 1;
            level = velocity;
            frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        }

        void juce::SynthesiserVoice::stopNote(float velocity, bool allowTailOff)
        {
            env1.trigger = 0;
            allowTailOff = true;

            if(velocity == 0)
                clearCurrentNote();
        }

        void juce::SynthesiserVoice::pitchWheelMoved(int newPitchWheelValue)
        {

        }

        void juce::SynthesiserVoice::controllerMoved(int controllerNumber, int newControllerValue)
        {

        }
        
        void juce::SynthesiserVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
        {
            for (int sample = 0; sample < numSamples; ++sample)
            {
                for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                {
                    outputBuffer.addSample(channel, startSample, setFilter() * 0.3f);
                }

                ++startSample;
            }
        }

    private:
        double level;
        double frequency;
        int theWave;

        int filterChoice;
        float cutoff;
        float resonance;

        maxiOsc osc1;
        maxiEnv env1;
        maxiFilter filter1;
};
