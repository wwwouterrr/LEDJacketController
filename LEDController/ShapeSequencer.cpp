// 
// 
// 

#include "ShapeSequencer.h"

ShapeSequencer::ShapeSequencer(CRGB *leds, std::string sequence, uint16_t shapeduration, uint16_t betweenduration, uint16_t afterglow)
{
	_sequence = sequence;
	_shapeduration = shapeduration;
	_betweenduration = betweenduration;
	_afterglow = afterglow;
	_leds = leds;
	ffc = false;
	changed = false;
	palette = RainbowColors_p;
	color = ColorFromPalette(palette, scale8(random8(), 240));
}

void ShapeSequencer::SetPalette(CRGBPalette16 pal)
{
	palette = pal;
}

void ShapeSequencer::SetFFC(boolean v)
{
	ffc = v;
}

void ShapeSequencer::SetTPC(uint16_t v)
{
	_shapeduration = v;
}

void ShapeSequencer::reset()
{
	_currentPosition = 0;
}

void ShapeSequencer::SetBBC(uint16_t v)
{
	_betweenduration = v;
}

void ShapeSequencer::SetFAD(uint16_t v)
{
	_afterglow = v;
}

void ShapeSequencer::SetText1(std::string v)
{
	_sequencep1 = v;
	_sequence = _sequencep1 + _sequencep2;
	_currentPosition = 0;
	//changed = true;
}

void ShapeSequencer::SetText2(std::string v)
{
	_sequencep2 = v;
	_sequence = _sequencep1 + _sequencep2;
	_currentPosition = 0;
	//changed = true;
}

bool ShapeSequencer::Perform(bool returnWhenDone)
{
	// Determine whether next character should be drawn
	if (millis() - _timeStampLastShape >= _shapeduration)
	{
		newShape = true;

		if (_betweenduration > 0) // clear shape and show blank for betweenduration
		{		
			if (!inPause) // start of pause
			{
				timeBeforePause = millis();
				inPause = true;
			}

			if (timeBeforePause + _betweenduration < millis()) // end of pause
			{
				inPause = false;
			}

			if (inPause)
			{
				if (_afterglow > 0) // fade LEDS
				{
					for (uint16_t i = 0; i < NUM_LEDS; i++)
					{
						_leds[i].fadeToBlackBy(_afterglow);
					}
				}
				else
				{
					for (uint16_t i = 0; i < NUM_LEDS; i++)
					{
						_leds[i] = CRGB::Black;
					}
				}

				return false;
			}
		}

		// Reset at end of string
		if (_currentPosition + 1 > _sequence.length())
		{
			_currentPosition = 0;
			if (returnWhenDone) return true;
		}

		/*
			if (returnWhenDone) return true;

			if (changed)
			{
				_sequence = _newsequence;				
				changed = false;
			}
		}*/

		// Read next key from sequence
		_key = _sequence.substr(_currentPosition, 1); // Assume key is one character.
		if (_key == ".")
		{
			int endPos = _sequence.find(".", _currentPosition + 1);
			_key = _sequence.substr(_currentPosition, endPos - _currentPosition + 1); // Find larger keys encapsulated by dots (special shapes)
			_currentPosition = endPos + 1;
		}
		else _currentPosition++;

		// Get associated shape from shapes map
		_shapeIterator = shapes.find(_key);  // Try to find shape
		if (_shapeIterator != shapes.end()) _currentShape = _shapeIterator->second; // Shape found. Set as current shape.

		_timeStampLastShape = millis(); // Record timestamp of when this shape was shown

		if (!ffc) color = ColorFromPalette(palette, scale8(random8(), 240));	// If fast flashing colours is disabled, change colour every character
	}
	else
	{
		newShape = false;
	}

	if (ffc) color = ColorFromPalette(palette, scale8(random8(), 240));			// If fast flashing colours is enabled, change colour every render
	

	for (uint16_t i = 0; i < NUM_LEDS; i++)
	{
		if (_afterglow > 0)
		{
			_leds[i].fadeToBlackBy(_afterglow);
		}
		else _leds[i] = CRGB::Black;
		
		for (std::vector<uint16_t>::iterator ledIterator = _currentShape.leds.begin(); ledIterator != _currentShape.leds.end(); ledIterator++)
		{
			_leds[*ledIterator] = color;
		}
	}

	return false;
}
