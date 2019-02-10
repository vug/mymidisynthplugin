#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyMidiSynthPlugInAudioProcessorEditor::MyMidiSynthPlugInAudioProcessorEditor (MyMidiSynthPlugInAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible(osc1TypeSelect);
	osc1TypeSelect.addItem("Sinusoidal", (int)oscillatorTypes::sinusoidal);
	osc1TypeSelect.addItem("Saw Tooth", (int)oscillatorTypes::sawtooth);
	osc1TypeSelect.addItem("Square", (int)oscillatorTypes::square);

	osc1TypeSelect.onChange = [this] { processor.osc1.type = (oscillatorTypes)osc1TypeSelect.getSelectedId(); };
	osc1TypeSelect.setSelectedId((int)oscillatorTypes::sinusoidal);

	addAndMakeVisible(osc2TypeSelect);
	osc2TypeSelect.addItem("Sinusoidal", (int)oscillatorTypes::sinusoidal);
	osc2TypeSelect.addItem("Saw Tooth", (int)oscillatorTypes::sawtooth);
	osc2TypeSelect.addItem("Square", (int)oscillatorTypes::square);

	osc2TypeSelect.onChange = [this] { processor.osc2.type = (oscillatorTypes)osc2TypeSelect.getSelectedId(); };
	osc2TypeSelect.setSelectedId((int)oscillatorTypes::sinusoidal);

	addAndMakeVisible(shiftSemitonesKnob);
	shiftSemitonesKnob.setSliderStyle(Slider::Rotary);
	shiftSemitonesKnob.setRotaryParameters(1.5 * float_Pi, 2.5 * float_Pi, false);
	shiftSemitonesKnob.setRange(-12, 12, 1.0);
	shiftSemitonesKnob.setTextValueSuffix(" semitones");
	shiftSemitonesKnob.setValue(0);
	shiftSemitonesKnob.setTextBoxStyle(Slider::NoTextBox, false, 60, 20);
	shiftSemitonesKnob.setPopupDisplayEnabled(true, true, this, 2000);
	shiftSemitonesKnob.onValueChange = [this] { 
		processor.osc2.freqMultiplier = pow(2.0, shiftSemitonesKnob.getValue() / 12.0); 
	};

    setSize (400, 300);
}

MyMidiSynthPlugInAudioProcessorEditor::~MyMidiSynthPlugInAudioProcessorEditor()
{
}

//==============================================================================
void MyMidiSynthPlugInAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("My first VST3!", getLocalBounds(), Justification::centred, 1);
}

void MyMidiSynthPlugInAudioProcessorEditor::resized()
{
	osc1TypeSelect.setBounds(10, 10, 100, 20);
	osc2TypeSelect.setBounds(120, 10, 100, 20);
	shiftSemitonesKnob.setBounds(240, 10, 50, 50);
}
