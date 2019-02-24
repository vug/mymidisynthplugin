#include "MySynthesizerVoice.h"

MySynthesizerVoice::MySynthesizerVoice() {
	double sr = getSampleRate();
	osc1 = Oscillator(sr);
	osc2 = Oscillator(sr);
	arEnv.setSampleRate(sr);
}

MySynthesizerVoice::~MySynthesizerVoice() {

}

bool MySynthesizerVoice::canPlaySound(SynthesiserSound* sound) {
	return dynamic_cast<MySynthesizerSound*> (sound) != nullptr;
}

void MySynthesizerVoice::setParameters(
	oscillatorTypes osc1Type,
	bool osc1isBandLimited,
	oscillatorTypes osc2Type,
	bool osc2isBandLimited,
	int osc2freqShiftCents,
	int osc2freqShiftSemitones,
	double oscVolumesMix,
	double attack,
	double release
) {
	osc1.type = osc1Type;
	osc2.type = osc2Type;
	this->oscVolumesMix = oscVolumesMix;
	osc2.freqShiftSemitones = osc2freqShiftSemitones;
	osc2.freqShiftCents = osc2freqShiftCents;
	osc1.isBandLimited = osc1isBandLimited;
	osc2.isBandLimited = osc2isBandLimited;

	ADSR::Parameters p;
	p.attack = attack;
	p.decay = 0.0f;
	p.sustain = 1.0f;
	p.release = release;
	arEnv.setParameters(p);
}

void MySynthesizerVoice::startNote(
	int midiNoteNumber,
	float velocity,
	SynthesiserSound* sound,
	int currentPitchWheelPosition) {

}

void MySynthesizerVoice::stopNote(float velocity, bool allowTailOff) {

}

void MySynthesizerVoice::renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) {

}

void MySynthesizerVoice::pitchWheelMoved(int newPitchWheelValue) {};
void MySynthesizerVoice::controllerMoved(int controllerNumber, int newControllerValue) {};
