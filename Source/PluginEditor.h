/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MyMidiSynthPlugInAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    MyMidiSynthPlugInAudioProcessorEditor (MyMidiSynthPlugInAudioProcessor&);
    ~MyMidiSynthPlugInAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyMidiSynthPlugInAudioProcessor& processor;
	ComboBox osc1TypeSelect;
	ComboBox osc2TypeSelect;
	Slider shiftSemitonesKnob;
	Slider shiftCentsKnob;
	Slider oscMixSlider;
	Slider envAttackSlider;
	Slider envReleaseSlider;

	double getFreqShiftMultiplier();
	ADSR::Parameters getVolumeEnvelopeParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyMidiSynthPlugInAudioProcessorEditor)
};
