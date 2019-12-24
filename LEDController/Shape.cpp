// 
// 
// 

#include "Shape.h"

Shape::Shape(std::vector<Segment> s)
{	
	// Iterate segments
	for (std::vector<Segment>::iterator segmentIterator = s.begin(); segmentIterator != s.end(); segmentIterator++)
	{
		if (segmentIterator->end >= segmentIterator->start)
		{
			for (uint16_t x = segmentIterator->start; x <= segmentIterator->end; x++)
			{
				leds.push_back(x);
			}
		}
		else
		{
			for (uint16_t x = segmentIterator->start; x >= segmentIterator->end; x--)
			{
				leds.push_back(x);
			}
		}		
	}
}