// 
// 
// 

#include "Fire.h"
#include "LEDConstants.h"

Fire::Fire(Shape shape, int cooling, int sparking)
{	
	_cooling = cooling;
	_sparking = sparking;	
	_shape = shape;
	heat.reserve(_shape.leds.size());
}

CRGB Fire::ConvertHeatToColour(byte temperature)
{
	// Scale 'heat' down from 0-255 to 0-191
	byte t192 = round((temperature / 255.0) * 191);

	// calculate ramp up from
	byte heatramp = t192 & 0x3F;  // 0..63
	heatramp <<= 2;               // scale up to 0..252

	// figure out which third of the spectrum we're in:
	if (t192 > 0x80) return CRGB(255, 255, heatramp);           // hottest
	else if (t192 > 0x40) return CRGB(255, heatramp, 0);        // middle
	else return CRGB(heatramp, 0, 0);                           // coolest
}

void Fire::Perform(double t)
{
	// Step 1.  Cool down every cell a little
	for (int c = 0; c < _shape.leds.size(); c++)
	{		
		_cooldown = random(0, ((_cooling * 10) / _shape.leds.size()) + 2);
		if (_cooldown > heat[c])  heat[c] = 0;
		else heat[c] = heat[c] - _cooldown;
	}
	
	// Step 2.  Heat from each cell drifts 'up' and diffuses a little
	for (int k = _shape.leds.size() - 1; k >= 2; k--) heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;

	// Step 3.  Randomly ignite new 'sparks' near the bottom
	if (random(255) < _sparking)
	{
		int y = random(7);
		heat[y] = heat[y] + random(160, 255);
	}

	// Step 4.  Convert heat to LED colors
	int c = 0;
	for (std::vector<uint16_t>::iterator i = _shape.leds.begin(); i != _shape.leds.end(); i++)
	{
		_leds[*i] = ConvertHeatToColour(heat[c++]);
	}	
}