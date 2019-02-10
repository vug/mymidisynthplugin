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

	osc1TypeSelect.onChange = [this] { 
		processor.osc1.type = (oscillatorTypes)osc1TypeSelect.getSelectedId(); 
	};
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
		processor.osc2.freqMultiplier = getFreqShiftMultiplier();
	};

	addAndMakeVisible(shiftCentsKnob);
	shiftCentsKnob.setSliderStyle(Slider::Rotary);
	shiftCentsKnob.setRotaryParameters(1.5 * float_Pi, 2.5 * float_Pi, false);
	shiftCentsKnob.setRange(-100, 100, 1.0);
	shiftCentsKnob.setTextValueSuffix(" cents");
	shiftCentsKnob.setValue(0);
	shiftCentsKnob.setTextBoxStyle(Slider::NoTextBox, false, 60, 20);
	shiftCentsKnob.setPopupDisplayEnabled(true, true, this, 2000);
	shiftCentsKnob.onValueChange = [this] {
		processor.osc2.freqMultiplier = getFreqShiftMultiplier();
	};

	addAndMakeVisible(oscMixSlider);
	oscMixSlider.setSliderStyle(Slider::LinearHorizontal);
	oscMixSlider.setRange(0.0, 1.0, 0.1);
	oscMixSlider.setValue(0.0);
	oscMixSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	oscMixSlider.setPopupDisplayEnabled(true, true, this, 2000);
	oscMixSlider.onValueChange = [this] {
		processor.oscVolumesMix = oscMixSlider.getValue();
	};

	addAndMakeVisible(envAttackSlider);
	envAttackSlider.setSliderStyle(Slider::LinearVertical);
	envAttackSlider.setRange(0.01, 2.0, 0.01);
	envAttackSlider.setValue(0.01);
	envAttackSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	envAttackSlider.setPopupDisplayEnabled(true, true, this, 2000);
	envAttackSlider.onValueChange = [this] {
		processor.volArEnv.setParameters(getVolumeEnvelopeParameters());
	};

	addAndMakeVisible(envReleaseSlider);
	envReleaseSlider.setSliderStyle(Slider::LinearVertical);
	envReleaseSlider.setRange(0.01, 2.0, 0.01);
	envReleaseSlider.setValue(0.01);
	envReleaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	envReleaseSlider.setPopupDisplayEnabled(true, true, this, 2000);
	envReleaseSlider.onValueChange = [this] {
		processor.volArEnv.setParameters(getVolumeEnvelopeParameters());
	};

    setSize (400, 300);
}

double MyMidiSynthPlugInAudioProcessorEditor::getFreqShiftMultiplier() {
	return pow(2.0, shiftSemitonesKnob.getValue() / 12.0 + shiftCentsKnob.getValue() / 1200.0);
}

ADSR::Parameters MyMidiSynthPlugInAudioProcessorEditor::getVolumeEnvelopeParameters() {
	ADSR::Parameters p;
	p.attack = envAttackSlider.getValue();
	p.decay = 0.0;
	p.sustain = 1.0;
	p.release = envReleaseSlider.getValue();
	return p;
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
	oscMixSlider.setBounds(120, 10, 100, 20);
	osc2TypeSelect.setBounds(240, 10, 100, 20);
	shiftSemitonesKnob.setBounds(240, 40, 50, 50);
	shiftCentsKnob.setBounds(310, 40, 50, 50);

	envAttackSlider.setBounds(50, 40, 30, 80);
	envReleaseSlider.setBounds(80, 40, 30, 80);
}
