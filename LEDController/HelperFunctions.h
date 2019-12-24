// HelperFunctions.h

#ifndef _HELPERFUNCTIONS_h
#define _HELPERFUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FastLED.h>
#include <sstream>
#include "Shape.h"


CRGBPalette16 getRandomPalette();
CRGBPalette16 getBlackAndWhiteStripedPalette();
CRGBPalette16 getPurpleAndWhitePalette();
CRGBPalette16 getBlackAndWhiteAndPurpleStripedPalette();
CRGBPalette16 getPurpleAndGreenPalette();
bool inArray(uint16_t val, uint16_t *arr, int size);
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
uint16_t stoi(std::string s);
void ps(std::string s);
double smoothTransition(double begin, double end, double time);
double getSmoothTime(double time);
Shape getShape(std::string s);

#endif

