#include "BlinkingStars.h"

BlinkingStars::BlinkingStars(CRGB *leds, double sp, double sc, uint8_t fd)
{	
	currentPalette	= CRGBPalette16(CRGB::Yellow);
	targetPalette	= CRGBPalette16(CRGB::Yellow);
	_leds = leds;	
	speed = sp;
	scale = sc;
	fade = fd;
}

bool BlinkingStars::Perform(bool returnWhenDone)
{
	fadeToBlackBy(_leds, NUM_LEDS, fade); // Fade  determines the strength of the fadeout effect

	if (millis() - lastPerformTime > (speed - 50) * -40) // Speed determines when to light up new LEDS	(speed 0 : 2s delay, speed 50 : no delay)
	{
		for (uint16_t i = 0; i < NUM_LEDS; i++)
		{
			if (random8() > 255 - ((scale + 1) * 2)) // Scale determines how many LEDS to light up	(scale 0 : 1%, scale 10: 9%)
			{
				_leds[i] = ColorFromPalette(currentPalette, scale8(random8(), 240));
			}
		}		

		lastPerformTime = millis();
	}	
}