#include "Segment.h"

Segment::Segment(uint16_t s)
{
	start = s;
	end = s;
}

Segment::Segment(uint16_t s, uint16_t e)
{
	start = s;
	end = e;
}
