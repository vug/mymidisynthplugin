#include "Oscillator.h"

Oscillator::Oscillator()
{

}

Oscillator::Oscillator(double sr)
{
	type = oscillatorTypes::sinusoidal;
	currentSampleRate = sr;
}


Oscillator::~Oscillator()
{
}

double Oscillator::oscillate()
{
	double x;
	switch (type) {
	case oscillatorTypes::sinusoidal:
		x = std::sin(phase);
		break;
	case oscillatorTypes::sawtooth:
		x = std::fmod(phase / MathConstants<double>::twoPi, 1.0);
		break;
	case oscillatorTypes::square:
		x = std::fmod(phase, MathConstants<double>::twoPi) < MathConstants<double>::pi;
		break;
	}

	phase += (frequency * freqMultiplier) * MathConstants<double>::twoPi / currentSampleRate;
	return x;
}

double Oscillator::func()
{
	return 0.0;
}