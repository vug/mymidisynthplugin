#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

enum class oscillatorTypes : int {
	sinusoidal = 1,
	sawtooth = 2,
	square
};

class Oscillator
{
public:
	Oscillator();
	Oscillator(double sr);
	~Oscillator();

	double oscillate();
	oscillatorTypes type;
	double frequency = 220.0;
	int freqShiftSemitones = 0;
	int freqShiftCents = 0;
	bool isBandLimited = true;

private:
	double phase = 0.0;
	
	double currentSampleRate = 0.0;
};