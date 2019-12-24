#ifndef _Segment_h
#define _Segment_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

struct Segment
{
	uint16_t start;
	uint16_t end;

	Segment(uint16_t s);
	Segment(uint16_t s, uint16_t e);
};

#endif