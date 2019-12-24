// 
// 
// 

#include "ZigZag.h"
#include "HelperFunctions.h"

ZigZag::ZigZag(Shape shape)
{
	_shape = shape;
	color = CRGB::Red;
}

void ZigZag::Perform(double t)
{	
	// t ranges from 0 to 1, indicating a full animation cycle

	// a----------------------b

	// at t = 0.0, lit pixel is at a
	// at t = 0.5  lit pixel is at b
	// at t = 1.0  lit pixel is back at a
	
	// Determine which LED to light up.
	// Scale t so that it goes from 0 - 1 and back to 0
	t = t * 2;
	if (t > 1) t = 2 - t;

	t = getSmoothTime(t);

	// The LED to light is t * number of LEDS in this shape
	double LEDtoLight = t * (_shape.leds.size() - 1);
	
	// This will likely be a fractional number
	// e.g.  7.25
	// In this case light LED 7 with 75% of brightness and LED 8 with 25% brightness	
	double fraction = std::fmod(LEDtoLight, 1);  // 0.25

	// Fade leds to 0
	for (std::vector<uint16_t>::iterator i = _shape.leds.begin(); i != _shape.leds.end(); i++)
	{
		_leds[*i].fadeToBlackBy(fade);
	}
		
	_leds[_shape.leds.at((int)round(LEDtoLight))] = color;
}