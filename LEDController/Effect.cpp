// 
// 
// 

#include "Effect.h"

void Effect::SetPalette(CRGBPalette16 newPalette)
{
	currentPalette = newPalette;
}

void Effect::SetSpeed(double s)
{	
	speed = s;
}

void Effect::SetScale(double s)
{
	scale = s;
}

void Effect::SetFade(uint8_t f)
{
	fade = f;
}

void Effect::SetColorLoop(boolean l)
{
	colorLoop = l;
}