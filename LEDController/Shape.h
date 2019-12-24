// Shape.h

#ifndef _SHAPE_h
#define _SHAPE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Segment.h"

// A shape consists of one or more segments
class Shape
{
public:
	std::vector<uint16_t> leds;
	Shape() {};
	Shape(std::vector<Segment> s);
};

#endif

