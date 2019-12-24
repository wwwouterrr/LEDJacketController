#include "HelperFunctions.h"
#include <map>
#include "LEDConstants.h"

// This function generates a random palette that's a gradient
// between four different colors.  The first is a dim hue, the second is
// a bright hue, the third is a bright pastel, and the last is
// another bright hue.  This gives some visual bright/dark variation
// which is more interesting than just a gradient of different hues.
CRGBPalette16 getRandomPalette()
{
	return CRGBPalette16(
		CHSV(random8(), 255, 32),
		CHSV(random8(), 255, 255),
		CHSV(random8(), 128, 255),
		CHSV(random8(), 255, 255));
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
CRGBPalette16 getBlackAndWhiteStripedPalette()
{
	CRGB white = CRGB::White;
	CRGB black = CRGB::Black;

	return CRGBPalette16(
		black, black, black, black,
		black, black, black, white,
		black, black, black, black,
		black, black, black, black);
}

CRGBPalette16 getPurpleAndWhitePalette()
{
	return CRGBPalette16(
		CRGB::White,
		CRGB::Purple,
		CHSV(HUE_PURPLE, 100, 100),
		CRGB::Black);
}

CRGBPalette16 getBlackAndWhiteAndPurpleStripedPalette()
{
	CRGB white = CRGB::White;
	CRGB purple = CRGB::Purple;
	CRGB black = CRGB::Black;

	return CRGBPalette16(
		black, black, black, black,
		black, black, black, white,
		black, purple, black, black,
		black, black, black, black);

}

// This function sets up a palette of purple and green stripes.
CRGBPalette16 getPurpleAndGreenPalette()
{
	CRGB purple = CHSV(HUE_PURPLE, 255, 255);
	CRGB green = CHSV(HUE_GREEN, 255, 255);
	CRGB black = CRGB::Black;

	return CRGBPalette16(
		green, green, black, black,
		purple, purple, black, black,
		green, green, black, black,
		purple, purple, black, black);
}

bool inArray(uint16_t val, uint16_t *arr, int size)
{
	for (int i = 0; i < size; i++) if (arr[i] == val) return true;
	return false;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// String to integer
uint16_t stoi(std::string s)
{
	int number;
	std::stringstream iss(s);
	iss >> number;
	if (iss.fail())
	{
		return 65535;
	}
	else return number;
}

void ps(std::string s) // Print string to serial
{
	for (int i = 0; i < s.length(); i++) {
		Serial.print(s.at(i));
	}
	Serial.println();
}

// Smoothly transitions a value from begin to end, based on time (0-1)
double smoothTransition(double begin, double end, double time)
{
	return begin + pow(time, 2) * (3 - 2 * time) * (end - begin);
}

double getSmoothTime(double time)
{
	return pow(time, 2) * (3 - 2 * time);
}


Shape getShape(std::string s)
{
	std::map<std::string, Shape>::const_iterator _shapeIterator;
	_shapeIterator = shapes.find(s);  // Try to find shape
	if (_shapeIterator != shapes.end()) return _shapeIterator->second; // Shape found. Set as current shape.
}