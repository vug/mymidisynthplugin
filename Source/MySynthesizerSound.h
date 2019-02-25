#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MySynthesizerSound : public SynthesiserSound {
public:
	MySynthesizerSound();
	~MySynthesizerSound();

	bool appliesToNote(int) override;
	bool appliesToChannel(int) override;
private:
};
