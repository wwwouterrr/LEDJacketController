#include "Noise.h"

Noise::Noise(CRGB *leds)
{
	// Initialize our coordinates to some random values
	x = random8();
	y = random8();
	z = random8();

	currentPalette = LavaColors_p;
	targetPalette  = LavaColors_p;
	_leds = leds;

	speed = 6;
	scale = 6;
	colorLoop = 1;

	targetSpeed = speed;
	targetScale = scale;
}

void Noise::SetPalette(CRGBPalette16 newPalette)
{
	targetPalette = newPalette;
}

void Noise::SetSpeed(double s)
{
	targetSpeed = s;
}

void Noise::SetScale(double s)
{
	targetScale = s;
}

bool Noise::Perform(bool returnWhenDone)
{	
	nblendPaletteTowardPalette(currentPalette, targetPalette);

	// Smoothly transition speed and scale when changed	
	if (targetSpeed != speed) // target speed changed
	{
		speed += (targetSpeed - speed) / 100;
		if (abs(targetSpeed - speed) < 0.1) speed = targetSpeed;
	}

	if (targetScale != scale) // target speed changed
	{
		scale += (targetScale - scale) / 100;
		if (abs(targetScale - scale) < 0.1) scale = targetScale;
	}

	// If we're runing at a low "speed", some 8-bit artifacts become visible
	// from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
	// The amount of data smoothing we're doing depends on "speed".

	static uint8_t ihue = random8();

	uint8_t dataSmoothing = 0;
	if (speed < 50)
	{
		dataSmoothing = 200 - (speed * 4);
	}

	// For each LED
	for (uint16_t i = 0; i < NUM_LEDS; i++)
	{	
		uint16_t id = i;

		// Get coordinate of LED
		uint8_t xCood = pgm_read_byte(&(ledsArray[i][0]));
		uint8_t yCood = pgm_read_byte(&(ledsArray[i][1]));

		uint16_t xoffset = scale * xCood;
		uint16_t yoffset = scale * yCood;

		uint8_t index = inoise8(x + xoffset, y + yoffset, z);

		// The range of the inoise8 function is roughly 16-238.
		// These two operations expand those values out to roughly 0..240
		index = qsub8(index, 16);
		index = qadd8(index, scale8(index, 20));

		uint8_t bri = inoise8(x + yoffset, y + xoffset, z); // another random point for brightness

		// The range of the inoise8 function is roughly 16-238.
		// These two operations expand those values out to roughly 0..255
		bri = qsub8(bri, 16);
		bri = qadd8(bri, scale8(bri, 39));

		if (dataSmoothing)
		{
			uint8_t olddata = inoise8(x + xoffset - speed / 8, y + yoffset + speed / 16, z - speed);
			uint8_t newdata = scale8(olddata, dataSmoothing) + scale8(index, 256 - dataSmoothing);
			index = newdata;
		}

		// if this palette is a 'loop', add a slowly-changing base value
		if (colorLoop)
		{
			index += ihue;
		}

		bri = dim8_raw(scale8(bri, briScale));
		
		CRGB color = ColorFromPalette(currentPalette, index, bri);	
		_leds[id] = color;				
	}

	// Slow animation
	long processingTime = millis() - lastPerformTime;
	if (processingTime < 20) delay(20 - processingTime); // aim for 50 Hz
	lastPerformTime = millis();

	z += speed;

	// apply slow drift to X and Y, just for visual variation.
	x += speed / 8;
	y -= speed / 16;

	ihue++;

	return true;
}

