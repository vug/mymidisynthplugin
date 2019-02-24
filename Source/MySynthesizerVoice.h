#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "MySynthesizerSound.h"
#include "Oscillator.h"

class MySynthesizerVoice : public SynthesiserVoice {
public:
	MySynthesizerVoice();
	~MySynthesizerVoice();

	bool canPlaySound(SynthesiserSound*) override;

	void startNote(int midiNoteNumber,
		float velocity,
		SynthesiserSound* sound,
		int currentPitchWheelPosition) override;

	void stopNote(float velocity, bool allowTailOff) override;

	void renderNextBlock(AudioBuffer<double>& outputBuffer,
		int startSample,
		int numSamples) override;

	// To be called by Processor in processBlock(), just before calling synth.processBlock().
	void setParameters(
		oscillatorTypes osc1Type,
		bool osc1isBandLimited,
		oscillatorTypes osc2Type,
		bool osc2isBandLimited,
		int osc2freqShiftCents,
		int osc2freqShiftSemitones,
		double oscVolumesMix,
		double attack,
		double release
	);

	Oscillator osc1;
	Oscillator osc2;
	double oscVolumesMix;
	ADSR arEnv;

	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;

	//bool isVoiceActive() const;
	//void aftertouchChanged(int newAftertouchValue);
	//void channelPressureChanged(int newChannelPressureValue) override;
	//bool isPlayingChannel(int midiChannel) const;
private:
};
