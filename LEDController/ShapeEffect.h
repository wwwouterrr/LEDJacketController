// ShapeEffect.h

#ifndef _SHAPEEFFECT_h
#define _SHAPEEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Effect.h"
#include "Shape.h"
#include <list>

// A shapeeffect is an effect that is only performed on a shape
class ShapeEffect
{
	protected:

		Shape _shape;
		CRGB *_leds;		

	public:

		CRGB color;
		uint8_t fade;
		ShapeEffect() {};
		void SetLEDS(CRGB * leds);
		virtual void Perform(double t) = 0;		
};

#endif