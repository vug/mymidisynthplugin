/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <unordered_map>
#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
/**
*/
class MyMidiSynthPlugInAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MyMidiSynthPlugInAudioProcessor();
    ~MyMidiSynthPlugInAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

	void reset() override;
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	Synthesiser mySynth;
	Oscillator osc1;
	Oscillator osc2;
	double oscVolumesMix = 0.0;
	ADSR arEnv;  // AR (Attack/Release) only envelope
	double cutOff = 22000.0;  // Hz
	double resonance = 1.0;
	bool isFilterUsingEnvelope = false;
	double delayDuration = 0.3;  // sec
	double delayFeedback = 0.0;
	bool isMonophonic = false;

private:
    //==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyMidiSynthPlugInAudioProcessor)

	void processBlockMonoPhonic(AudioBuffer<float>& buffer, MidiBuffer& midiMessages);
	void processBlockPolyPhonic(AudioBuffer<float>& buffer, MidiBuffer& midiMessages);
	void processDelay(AudioBuffer<float>& buffer);

	double currentSampleRate = 0.0;
	double noteFrequency;
	LinearSmoothedValue<double> masterVolume;  // overall Synth volume
	int lastNoteNumber = -1;
	long timeInSamples = 0l;
	IIRFilter filter;
	AudioBuffer<double> delayBuffer;
	int delayWriteIndex = 0; // in samples, relative to circular delay buffer

	std::unordered_map<int, long> pressedNotes;

	int getMostRecentNote();
};
