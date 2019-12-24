// ZigZag.h

#ifndef _ZIGZAG_h
#define _ZIGZAG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ShapeEffect.h"

class ZigZag : public ShapeEffect
{
private:
	uint32_t _cooling = 0, _sparking = 0, _cooldown = 0;
	std::vector<byte> heat;

public:
	ZigZag(Shape shape);
	void Perform(double t);
};

#endif



