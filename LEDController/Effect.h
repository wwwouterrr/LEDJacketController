// Effect.h

#ifndef _EFFECT_h
#define _EFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FastLED.h>
#include "Segment.h"

class Effect
{
	protected: 
	
		CRGB *_leds;		
		CRGBPalette16 currentPalette;
		CRGBPalette16 targetPalette;
		double speed, scale, targetSpeed, targetScale;
		uint8_t fade;
		boolean colorLoop;
		long lastPerformTime = 0;
		
	public:
			
		Effect() {};
		virtual void SetSpeed(double s);
		virtual void SetScale(double s);
		virtual void SetFade(uint8_t f);
		virtual void SetPalette(CRGBPalette16 newPalette);
		void SetColorLoop(boolean l);		
		virtual bool Perform(bool returnWhenDone) = 0;
};


#endif

