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
	double nyquistFrequency = currentSampleRate / 2;
	int numHarmonics = 1;

	switch (type) {
	case oscillatorTypes::sinusoidal:
		x = std::sin(phase);
		break;
	case oscillatorTypes::sawtooth:
		if (isBandLimited) {
			numHarmonics = nyquistFrequency / f;
			for (int n = 1; n <= numHarmonics; n++) {
				x += ((n % 2 == 0) ? 1 : -1) * std::sin(n * phase) / n;
			}
			x = 0.5 - x / float_Pi;
		}
		else {
			x = std::fmod(phase / MathConstants<double>::twoPi, 1.0);
		}
		break;

	case oscillatorTypes::square:
		if (isBandLimited) {
			numHarmonics = nyquistFrequency / (2 * f);
			for (int n = 1; n <= numHarmonics; n++) {
				x += std::sin((2 * n - 1) * phase) / (2 * n - 1);
			}
			x = 4.0f / float_Pi * x;

		}
		else {
			x = (std::fmod(phase, MathConstants<double>::twoPi) < MathConstants<double>::pi) * 2.0 - 1.0;
		}
		break;
	}

	phase += MathConstants<double>::twoPi * f / currentSampleRate;
	return x;
}
