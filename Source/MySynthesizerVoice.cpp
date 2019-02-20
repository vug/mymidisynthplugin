#include "MySynthesizerVoice.h"

MySynthesizerVoice::MySynthesizerVoice() {

}

MySynthesizerVoice::~MySynthesizerVoice() {

}

bool MySynthesizerVoice::canPlaySound(SynthesiserSound* sound) {
	return dynamic_cast<MySynthesizerSound*> (sound) != nullptr;
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
