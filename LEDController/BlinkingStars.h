// BlinkingStars.h

#ifndef _BLINKINGSTARS_h
#define _BLINKINGSTARS_h

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

class BlinkingStars : public Effect
{
private:
	
public:
	BlinkingStars(CRGB *leds, double sp, double sc, uint8_t fd);
	bool Perform(bool returnWhenDone);

};

#endif

