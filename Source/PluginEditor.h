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
	Label osc1TypeLabel;
	ComboBox osc2TypeSelect;
	Label osc2TypeLabel;
	ToggleButton osc1BandLimited;
	ToggleButton osc2BandLimited;
	Slider shiftSemitonesKnob;
	Label shiftSemitonesLabel;
	Slider shiftCentsKnob;
	Label shiftCentsLabel;
	Slider oscMixSlider;
	Label oscMixLabel;
	Slider envAttackSlider;
	Label envAttackLabel;
	Slider envReleaseSlider;
	Label envReleaseLabel;
	Slider cutOffSlider;
	Label cutOffLabel;
	Slider resonanceSlider;
	Label resonanceLabel;
	ToggleButton filterUsingEnvelope;

	ADSR::Parameters getVolumeEnvelopeParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyMidiSynthPlugInAudioProcessorEditor)
};
