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
	double x = 0.0;
	double freqMultiplier = pow(2.0, freqShiftSemitones / 12.0 + freqShiftCents / 1200.0);
	double f = frequency * freqMultiplier;
	switch (type) {
	case oscillatorTypes::sinusoidal:
		x = std::sin(phase);
		break;
	case oscillatorTypes::sawtooth:
		x = std::fmod(phase / MathConstants<double>::twoPi, 1.0);
		break;
	case oscillatorTypes::square:
			x = (std::fmod(phase, MathConstants<double>::twoPi) < MathConstants<double>::pi) * 2.0 - 1.0;
		break;
	}

	phase += MathConstants<double>::twoPi * f / currentSampleRate;
	return x;
}
