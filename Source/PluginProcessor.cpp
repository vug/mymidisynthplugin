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

void MyMidiSynthPlugInAudioProcessor::setCurrentProgram (int)  // index
{
}

const String MyMidiSynthPlugInAudioProcessor::getProgramName (int)  // index
{
    return {};
}

void MyMidiSynthPlugInAudioProcessor::changeProgramName (int, const String&)  // index, newName
{
}

//==============================================================================
void MyMidiSynthPlugInAudioProcessor::prepareToPlay (double sampleRate, int)  // samplesPerBlock
{
	currentSampleRate = sampleRate;
	masterVolume.setValue(1.0);
	masterVolume.reset(sampleRate, 0.01);
	volArEnv.setSampleRate(sampleRate);
	volArEnv.reset();

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
	MidiMessage msg;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(msg, time);) {
		if (msg.isNoteOn()) {
			pressedNotes[msg.getNoteNumber()] = timeInSamples + (long)msg.getTimeStamp();
		}
		else if (msg.isNoteOff()) {
			pressedNotes.erase(msg.getNoteNumber());
		}
	}

	// TODO: frequency changes are snapped at block beginnings. They should happen the moment the note came in? 
	// Well... Notes were already pressed, and given via midiMessages, actually...
	if (!pressedNotes.empty())
	{
		noteFrequency = MidiMessage::getMidiNoteInHertz(getMostRecentNote());
		osc1.frequency = noteFrequency;
		osc2.frequency = noteFrequency;
		volArEnv.noteOn();  // switches to "attack" State at every block, which prevents triggering of decay and sustain phases, hence AR-Envelope.
	}
	else
	{
		volArEnv.noteOff();
	}

	for (int i = 0; i < buffer.getNumSamples(); i++) {
		double vol = masterVolume.getNextValue();
		float a = volArEnv.getNextSample();
		double x1 = osc1.oscillate();
		double x2 = osc2.oscillate();
		double m = oscVolumesMix;
		double currentSample = vol * a * ((1.0 - m) * x1 + m * x2);

		for (auto channel = buffer.getNumChannels() - 1; channel >= 0; --channel)  // left, right channel agnostic
		{
			buffer.addSample(channel, i, (float)currentSample);
		}
	}

	filterLeft.setCoefficients(IIRCoefficients::makeLowPass(currentSampleRate, cutOff, resonance));
	filterRight.setCoefficients(IIRCoefficients::makeLowPass(currentSampleRate, cutOff, resonance));
	float* left = buffer.getWritePointer(0);
	float* right = buffer.getWritePointer(1);
	filterLeft.processSamples(left, buffer.getNumSamples());
	filterRight.processSamples(right, buffer.getNumSamples());

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
	std::unique_ptr<XmlElement> xml (new XmlElement("MyMidiSynthParams"));
	xml->setAttribute("osc1Type", (int)osc1.type);
	xml->setAttribute("osc1isBandLimited", osc1.isBandLimited);
	xml->setAttribute("osc2Type", (int)osc2.type);
	xml->setAttribute("osc2isBandLimited", osc2.isBandLimited);
	xml->setAttribute("oscVolumesMix", oscVolumesMix);
	xml->setAttribute("freqShiftInSemitones", osc2.freqShiftSemitones);
	xml->setAttribute("freqShiftInCents", osc2.freqShiftCents);
	xml->setAttribute("adsrAttack", volArEnv.getParameters().attack);
	xml->setAttribute("adsrRelease", volArEnv.getParameters().release);
	xml->setAttribute("cutOff", cutOff);
	xml->setAttribute("resonance", resonance);
	copyXmlToBinary(*xml, destData);
}

void MyMidiSynthPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() == nullptr || !xmlState->hasTagName("MyMidiSynthParams")) {
		return;
	}
	osc1.type = (oscillatorTypes)xmlState->getIntAttribute("osc1Type");
	osc1.isBandLimited = xmlState->getBoolAttribute("osc1isBandLimited");
	osc2.type = (oscillatorTypes)xmlState->getIntAttribute("osc2Type");
	osc2.isBandLimited = xmlState->getBoolAttribute("osc2isBandLimited");
	oscVolumesMix = xmlState->getDoubleAttribute("oscVolumesMix");
	osc2.freqShiftSemitones = (int)xmlState->getDoubleAttribute("freqShiftInSemitones");
	osc2.freqShiftCents = (int)xmlState->getDoubleAttribute("freqShiftInCents");
	ADSR::Parameters p;
	p.attack = (float)xmlState->getDoubleAttribute("adsrAttack");
	p.decay = 0.0f;
	p.sustain = 1.0f;
	p.release = (float)xmlState->getDoubleAttribute("adsrRelease");
	volArEnv.setParameters(p);
	cutOff = xmlState->getDoubleAttribute("cutOff");
	resonance = xmlState->getDoubleAttribute("resonance");
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyMidiSynthPlugInAudioProcessor();
}

