// ShapeSequencer.h

#ifndef _SHAPESEQUENCER_h
#define _SHAPESEQUENCER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <map>
#include "Segment.h"
#include "LEDConstants.h"
#include "BLEConstants.h"
#include "Effect.h"

class ShapeSequencer : public Effect
{
private:

	uint16_t _currentPosition = 0;
	std::string _sequencep1, _sequencep2;
	std::string _sequence, _newsequence;
	long timeBeforePause;
	bool inPause = false;
	bool changed;
	bool ffc;
	bool lit[NUM_LEDS] = {};
	bool newShape = false;
	CRGB color;
	CRGBPalette16 palette;
	uint16_t _shapeduration;     // milliseconds
	uint16_t _betweenduration;   // milliseconds
	uint16_t _afterglow;         // milliseconds	
	std::string _key;
	Shape _currentShape, _tempShape;
	std::map<std::string, Shape>::const_iterator _shapeIterator;
	unsigned long _timeStampLastShape = 0;
	
public:

	ShapeSequencer(CRGB *leds, std::string sequence, uint16_t shapeduration, uint16_t betweenduration, uint16_t afterglow);
	void SetTPC(uint16_t v);
	void SetBBC(uint16_t v);
	void SetFAD(uint16_t v);
	void SetText1(std::string v);
	void SetText2(std::string v);
	void SetPalette(CRGBPalette16 pal);
	void SetFFC(boolean v);
	bool Perform(bool returnWhenDone);
	void reset();
};

#endif

