// 
// 
// 

#include "ShapeEffectPerformer.h"
	
ShapeEffectPerformer::ShapeEffectPerformer(CRGB *leds, double sp, double sc, uint16_t fd)
{
	_leds = leds;
	speed = sp;
	scale = sc;
	fade = fd;

	animDuration = 500 + -100 * (speed - 50);
}

ShapeEffectPerformer::ShapeEffectPerformer(CRGB *leds)
{
	_leds = leds;	
	animDuration = 1;
}

void ShapeEffectPerformer::AddEffect(ShapeEffect* effect)
{
	effect->SetLEDS(_leds); // add reference to LEDS
	effect->fade = fade;
	effects.push_back(effect);
}

bool ShapeEffectPerformer::Perform(bool returnWhenDone)
{	
	// Perform all shape effects in the collection
	for (std::vector<ShapeEffect*>::iterator i = effects.begin(); i != effects.end(); i++)
	{		
		(*i)->Perform((millis() % animDuration) / (double)animDuration);
	}
	
	delay(20);

	return false;
}

void ShapeEffectPerformer::SetPalette(CRGBPalette16 newPalette)
{
	// Perform all shape effects in the collection
	for (std::vector<ShapeEffect*>::iterator i = effects.begin(); i != effects.end(); i++)
	{
		(*i)->color = ColorFromPalette(newPalette, random(8), 255);
	}
}

void ShapeEffectPerformer::SetSpeed(double s)
{
	speed = s;
	animDuration = 500 + -100 * (speed - 50);

	Serial.println("Set speed");
	Serial.println(animDuration);
}

void ShapeEffectPerformer::SetScale(double s)
{
	Serial.println("Set scale");
	scale = s;
}

void ShapeEffectPerformer::SetFade(uint8_t f)
{
	// Perform all shape effects in the collection
	for (std::vector<ShapeEffect*>::iterator i = effects.begin(); i != effects.end(); i++)
	{
		(*i)->fade = f;
	}
}