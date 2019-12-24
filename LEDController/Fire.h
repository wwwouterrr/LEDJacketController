// Fire.h

#ifndef _FIRE_h
#define _FIRE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ShapeEffect.h"

class Fire : public ShapeEffect
{
	private:
		uint32_t _cooling = 0, _sparking = 0, _cooldown = 0;
		std::vector<byte> heat;

	public:
		Fire(Shape shape, int cooling, int sparking);
		CRGB ConvertHeatToColour(byte temperature);
		void Perform(double t);
};

#endif

