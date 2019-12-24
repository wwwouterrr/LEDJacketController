// Noise.h

#ifndef _NOISE_h
#define _NOISE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Effect.h"
#include "LEDConstants.h"
#include "BLEConstants.h"
#include "HelperFunctions.h"
#include <FastLED.h>

class Noise : public Effect
{
private:

	// The 8 bit version of our coordinates
	uint16_t x;
	uint16_t y;
	uint16_t z;

	uint8_t briScale = 100;

public:	
	Noise(CRGB *leds);
	bool Perform(bool returnWhenDone);
	void SetPalette(CRGBPalette16 newPalette) override;
	void SetSpeed(double s) override;
	void SetScale(double s) override;
};

#endif