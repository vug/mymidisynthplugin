#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyMidiSynthPlugInAudioProcessorEditor::MyMidiSynthPlugInAudioProcessorEditor (MyMidiSynthPlugInAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible(osc1TypeSelect);
	osc1TypeSelect.addItem("Sinusoidal", (int)oscillatorTypes::sinusoidal);
	osc1TypeSelect.addItem("Triangle", (int)oscillatorTypes::triangle);
	osc1TypeSelect.addItem("Saw Tooth", (int)oscillatorTypes::sawtooth);
	osc1TypeSelect.addItem("Square", (int)oscillatorTypes::square);
	osc1TypeSelect.onChange = [this] { 
		processor.osc1.type = (oscillatorTypes)osc1TypeSelect.getSelectedId(); 
	};
	osc1TypeSelect.setSelectedId((int)processor.osc1.type);
	addAndMakeVisible(osc1TypeLabel);
	osc1TypeLabel.setText("Osc1 Type", dontSendNotification);

	addAndMakeVisible(osc1BandLimited);
	osc1BandLimited.setButtonText("band-limited");
	osc1BandLimited.onClick = [this] {
		processor.osc1.isBandLimited = osc1BandLimited.getToggleState();
	};
	osc1BandLimited.setToggleState(processor.osc1.isBandLimited, dontSendNotification);

	addAndMakeVisible(osc2TypeSelect);
	osc2TypeSelect.addItem("Sinusoidal", (int)oscillatorTypes::sinusoidal);
	osc2TypeSelect.addItem("Triangle", (int)oscillatorTypes::triangle);
	osc2TypeSelect.addItem("Saw Tooth", (int)oscillatorTypes::sawtooth);
	osc2TypeSelect.addItem("Square", (int)oscillatorTypes::square);
	osc2TypeSelect.onChange = [this] { 
		processor.osc2.type = (oscillatorTypes)osc2TypeSelect.getSelectedId(); 
	};
	osc2TypeSelect.setSelectedId((int)processor.osc2.type);
	addAndMakeVisible(osc2TypeLabel);
	osc2TypeLabel.setText("Osc2 Type", dontSendNotification);

	addAndMakeVisible(osc2BandLimited);
	osc2BandLimited.setButtonText("band-limited");
	osc2BandLimited.onClick = [this] {
		processor.osc2.isBandLimited = osc2BandLimited.getToggleState();
	};
	osc2BandLimited.setToggleState(processor.osc2.isBandLimited, dontSendNotification);


	addAndMakeVisible(shiftSemitonesKnob);
	shiftSemitonesKnob.setSliderStyle(Slider::Rotary);
	shiftSemitonesKnob.setRotaryParameters(1.5f * float_Pi, 2.5f * float_Pi, false);
	shiftSemitonesKnob.setRange(-12, 12, 1.0);
	shiftSemitonesKnob.setTextValueSuffix(" semitones");
	shiftSemitonesKnob.setTextBoxStyle(Slider::NoTextBox, false, 60, 20);
	shiftSemitonesKnob.setPopupDisplayEnabled(true, true, this, 2000);
	shiftSemitonesKnob.onValueChange = [this] {
		processor.osc2.freqShiftSemitones = (int)shiftSemitonesKnob.getValue();
	};
	shiftSemitonesKnob.setValue(processor.osc2.freqShiftSemitones);
	addAndMakeVisible(shiftSemitonesLabel);
	shiftSemitonesLabel.setText("transpose", dontSendNotification);

	addAndMakeVisible(shiftCentsKnob);
	shiftCentsKnob.setSliderStyle(Slider::Rotary);
	shiftCentsKnob.setRotaryParameters(1.5f * float_Pi, 2.5f * float_Pi, false);
	shiftCentsKnob.setRange(-100, 100, 1.0);
	shiftCentsKnob.setTextValueSuffix(" cents");
	shiftCentsKnob.setTextBoxStyle(Slider::NoTextBox, false, 60, 20);
	shiftCentsKnob.setPopupDisplayEnabled(true, true, this, 2000);
	shiftCentsKnob.onValueChange = [this] {
		processor.osc2.freqShiftCents = (int)shiftCentsKnob.getValue();
	};
	shiftCentsKnob.setValue(processor.osc2.freqShiftCents);
	addAndMakeVisible(shiftCentsLabel);
	shiftCentsLabel.setText("detune", dontSendNotification);


	addAndMakeVisible(oscMixSlider);
	oscMixSlider.setSliderStyle(Slider::LinearHorizontal);
	oscMixSlider.setRange(0.0, 1.0, 0.1);
	oscMixSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	oscMixSlider.setPopupDisplayEnabled(true, true, this, 2000);
	oscMixSlider.onValueChange = [this] {
		processor.oscVolumesMix = oscMixSlider.getValue();
	};
	oscMixSlider.setValue(processor.oscVolumesMix);
	addAndMakeVisible(oscMixLabel);
	oscMixLabel.setText("Osc Mix", dontSendNotification);

	addAndMakeVisible(envAttackSlider);
	envAttackSlider.setSliderStyle(Slider::LinearVertical);
	envAttackSlider.setRange(0.01, 2.0, 0.01);
	envAttackSlider.setTextValueSuffix(" sec");
	envAttackSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	envAttackSlider.setPopupDisplayEnabled(true, true, this, 2000);
	envAttackSlider.onValueChange = [this] {
		processor.arEnv.setParameters(getVolumeEnvelopeParameters());
	};
	envAttackSlider.setValue(processor.arEnv.getParameters().attack);
	addAndMakeVisible(envAttackLabel);
	envAttackLabel.setText("attack", dontSendNotification);

	addAndMakeVisible(envReleaseSlider);
	envReleaseSlider.setSliderStyle(Slider::LinearVertical);
	envReleaseSlider.setRange(0.01, 2.0, 0.01);
	envReleaseSlider.setTextValueSuffix(" sec");
	envReleaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	envReleaseSlider.setPopupDisplayEnabled(true, true, this, 2000);
	envReleaseSlider.onValueChange = [this] {
		processor.arEnv.setParameters(getVolumeEnvelopeParameters());
	};
	envReleaseSlider.setValue(processor.arEnv.getParameters().release);
	addAndMakeVisible(envReleaseLabel);
	envReleaseLabel.setText("release", dontSendNotification);

	addAndMakeVisible(cutOffSlider);
	cutOffSlider.setSliderStyle(Slider::LinearHorizontal);
	cutOffSlider.setRange(20.0, 22000.0, 10.0);
	cutOffSlider.setTextValueSuffix(" Hz");
	cutOffSlider.setSkewFactorFromMidPoint(2000.0);
	cutOffSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	cutOffSlider.setPopupDisplayEnabled(true, true, this, 2000);
	cutOffSlider.onValueChange = [this] {
		processor.cutOff = cutOffSlider.getValue();
	};
	cutOffSlider.setValue(processor.cutOff);
	addAndMakeVisible(cutOffLabel);
	cutOffLabel.setText("cut-off", dontSendNotification);

	addAndMakeVisible(resonanceSlider);
	resonanceSlider.setSliderStyle(Slider::LinearHorizontal);
	resonanceSlider.setRange(0.01, 5.0, 0.01);
	resonanceSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	resonanceSlider.setPopupDisplayEnabled(true, true, this, 2000);
	resonanceSlider.onValueChange = [this] {
		processor.resonance = resonanceSlider.getValue();
	};
	resonanceSlider.setValue(processor.resonance);
	addAndMakeVisible(resonanceLabel);
	resonanceLabel.setText("resonance", dontSendNotification);

	addAndMakeVisible(filterUsingEnvelope);
	filterUsingEnvelope.setButtonText("use envelope");
	filterUsingEnvelope.onClick = [this] {
		processor.isFilterUsingEnvelope = filterUsingEnvelope.getToggleState();
	};
	filterUsingEnvelope.setToggleState(processor.isFilterUsingEnvelope, dontSendNotification);

	addAndMakeVisible(delayDurationSlider);
	delayDurationSlider.setSliderStyle(Slider::LinearHorizontal);
	delayDurationSlider.setRange(0.01, 1.99, 0.01);
	delayDurationSlider.setTextValueSuffix(" sec");
	delayDurationSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	delayDurationSlider.setPopupDisplayEnabled(true, true, this, 2000);
	delayDurationSlider.onValueChange = [this] {
		processor.delayDuration = delayDurationSlider.getValue();
	};
	delayDurationSlider.setValue(processor.delayDuration);
	addAndMakeVisible(delayDurationLabel);
	delayDurationLabel.setText("delay", dontSendNotification);

	addAndMakeVisible(delayFeedbackSlider);
	delayFeedbackSlider.setSliderStyle(Slider::LinearHorizontal);
	delayFeedbackSlider.setRange(0.0, 0.99, 0.01);
	delayFeedbackSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	delayFeedbackSlider.setPopupDisplayEnabled(true, true, this, 2000);
	delayFeedbackSlider.onValueChange = [this] {
		processor.delayFeedback = delayFeedbackSlider.getValue();
	};
	delayFeedbackSlider.setValue(processor.delayFeedback);
	addAndMakeVisible(delayFeedbackLabel);
	delayFeedbackLabel.setText("feedback", dontSendNotification);

    setSize (400, 300);
}

ADSR::Parameters MyMidiSynthPlugInAudioProcessorEditor::getVolumeEnvelopeParameters() {
	ADSR::Parameters p;
	p.attack = (float)envAttackSlider.getValue();
	p.decay = 0.0;
	p.sustain = 1.0;
	p.release = (float)envReleaseSlider.getValue();
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
    g.drawFittedText ("My first VST3!", getLocalBounds(), Justification::bottom, 1);
}

void MyMidiSynthPlugInAudioProcessorEditor::resized()
{
	osc1TypeSelect.setBounds(10, 25, 100, 20);
	osc1TypeLabel.setBounds(10, 5, 100, 15);
	osc1BandLimited.setBounds(10, 45, 100, 30);
	oscMixSlider.setBounds(120, 20, 100, 20);
	oscMixLabel.setBounds(120, 5, 100, 15);
	osc2TypeSelect.setBounds(240, 25, 100, 20);
	osc2TypeLabel.setBounds(240, 5, 100, 15);
	osc2BandLimited.setBounds(240, 45, 100, 30);
	shiftSemitonesKnob.setBounds(240, 100, 50, 50);
	shiftSemitonesLabel.setBounds(230, 80, 100, 20);
	shiftCentsKnob.setBounds(310, 100, 50, 50);
	shiftCentsLabel.setBounds(310, 80, 100, 20);

	envAttackSlider.setBounds(20, 90, 30, 80);
	envAttackLabel.setBounds(10, 80, 50, 20);
	envReleaseSlider.setBounds(70, 90, 30, 80);
	envReleaseLabel.setBounds(60, 80, 50, 20);
	cutOffSlider.setBounds(130, 95, 100, 30);
	cutOffLabel.setBounds(140, 85, 100, 15);
	resonanceSlider.setBounds(130, 135, 100, 30);
	resonanceLabel.setBounds(140, 125, 100, 15);
	filterUsingEnvelope.setBounds(135, 155, 100, 30);

	delayDurationSlider.setBounds(10, 200, 100, 30);
	delayDurationLabel.setBounds(20, 190, 100, 15);
	delayFeedbackSlider.setBounds(10, 235, 100, 30);
	delayFeedbackLabel.setBounds(20, 225, 100, 15);

}
