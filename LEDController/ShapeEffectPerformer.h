// ShapeEffectPerformer.h

#ifndef _SHAPEEFFECTPERFORMER_h
#define _SHAPEEFFECTPERFORMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Effect.h"
#include "ShapeEffect.h"

class ShapeEffectPerformer : public Effect
{
	protected:

		std::vector<ShapeEffect*> effects;
		uint16_t animDuration = 0;

	public:

		ShapeEffectPerformer(CRGB *leds, double sp, double sc, uint16_t fd);
		ShapeEffectPerformer(CRGB *leds);
		void AddEffect(ShapeEffect* effect);
		bool Perform(bool returnWhenDone);
		void SetSpeed(double s) override;
		void SetScale(double s) override;
		void SetFade(uint8_t f) override;
		void SetPalette(CRGBPalette16 newPalette) override;
};

#endif

