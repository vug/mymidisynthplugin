/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Oscillator.h"

//==============================================================================
MyMidiSynthPlugInAudioProcessor::MyMidiSynthPlugInAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

}

MyMidiSynthPlugInAudioProcessor::~MyMidiSynthPlugInAudioProcessor()
{
}

//==============================================================================
const String MyMidiSynthPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyMidiSynthPlugInAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyMidiSynthPlugInAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyMidiSynthPlugInAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyMidiSynthPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyMidiSynthPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyMidiSynthPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyMidiSynthPlugInAudioProcessor::setCurrentProgram (int index)
{
}

const String MyMidiSynthPlugInAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyMidiSynthPlugInAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MyMidiSynthPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	currentSampleRate = sampleRate;
	amplitude.reset(sampleRate, 0.01);
	volumeADSR.setSampleRate(sampleRate);
	ADSR::Parameters p;
	p.attack = 0.5f;
	p.decay = 0.0f;
	p.sustain = 1.0f;
	p.release = 0.75f;
	volumeADSR.setParameters(p);
	volumeADSR.reset();

	osc1 = Oscillator(currentSampleRate);
	osc2 = Oscillator(currentSampleRate);
}

void MyMidiSynthPlugInAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyMidiSynthPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MyMidiSynthPlugInAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	int time;
	MidiMessage m;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {
		if (m.isNoteOn()) {
			pressedNotes[m.getNoteNumber()] = timeInSamples + m.getTimeStamp();
		}
		else if (m.isNoteOff()) {
			pressedNotes.erase(m.getNoteNumber());
		}
	}

	if (!pressedNotes.empty())  // TODO: frequency changes are snapped at block beginnings. Note right. They should happen the moment the note came in? Well... Note were already pressed actually...
	{
		noteFrequency = MidiMessage::getMidiNoteInHertz(getMostRecentNote());
		osc1.frequency = noteFrequency;
		osc2.frequency = noteFrequency;
		amplitude.setValue(1.0);
		volumeADSR.noteOn();
	}
	else
	{
		amplitude.setValue(0.0);
		volumeADSR.noteOff();
	}

	for (int i = 0; i < buffer.getNumSamples(); i++) {
		float a = amplitude.getNextValue();
		float b = volumeADSR.getNextSample();
		double x1 = osc1.oscillate();
		double x2 = osc2.oscillate();
		double m = oscVolumesMix;
		float currentSample = b * ((1.0 - m) * x1 + m * x2);

		for (auto channel = buffer.getNumChannels() - 1; channel >= 0; --channel)  // left, right channel agnostic
		{
			buffer.addSample(channel, i, currentSample);
		}
	}

	timeInSamples += buffer.getNumSamples();
}


int MyMidiSynthPlugInAudioProcessor::getMostRecentNote() {
	using pair_type = decltype(pressedNotes)::value_type;
	auto lastNotePair = std::max_element(
		pressedNotes.begin(),
		pressedNotes.end(),
		[](const pair_type& p1, const pair_type& p2) { return p1.second < p2.second; }
	);
	return lastNotePair->first;
}

//==============================================================================
bool MyMidiSynthPlugInAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MyMidiSynthPlugInAudioProcessor::createEditor()
{
    return new MyMidiSynthPlugInAudioProcessorEditor (*this);
}

//==============================================================================
void MyMidiSynthPlugInAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MyMidiSynthPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyMidiSynthPlugInAudioProcessor();
}

