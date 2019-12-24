#include "ZigZag.h"
#include "ShapeEffectPerformer.h"
#include "Shape.h"
#include <list>
#include <map>
#include <FastLED.h>
#include "Segment.h"
#include "LEDConstants.h"
#include "BLEConstants.h"
#include "Fire.h"
#include "Noise.h"
#include "ShapeSequencer.h"
#include "BlinkingStars.h"
#include "HelperFunctions.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

CRGB leds[NUM_LEDS];

// ---- BLE Variables
BLEServer* pServer				   = NULL;
BLECharacteristic* pCharBrightness = NULL;
BLECharacteristic* pCharMode	   = NULL;
BLECharacteristic* pCharTextTPC	   = NULL;
BLECharacteristic* pCharTextBBC    = NULL;
BLECharacteristic* pCharTextFAD    = NULL;
BLECharacteristic* pCharTextEVR    = NULL;
BLECharacteristic* pCharTextPAL    = NULL;
BLECharacteristic* pCharTextFFC    = NULL;
BLECharacteristic* pCharText1	   = NULL;
BLECharacteristic* pCharText2	   = NULL;
BLECharacteristic* pCharEffect	   = NULL;
BLECharacteristic* pCharEffectSPD  = NULL;
BLECharacteristic* pCharEffectFAD  = NULL;
BLECharacteristic* pCharEffectSCL  = NULL;
BLECharacteristic* pCharEffectPAL  = NULL;
BLECharacteristic* pCharEffectCLL  = NULL;

enum Mode		{ text, effect, alternate, demo };
enum EffectType { noise, stars, fire, zigzag };

EffectType effecttype	= noise;
Mode mode				= demo;

unsigned long _timeStampLastText = 0;
boolean textWasReset = false;
int displayTextEvery = 60;

bool deviceConnected = false;
bool oldDeviceConnected = false;

uint8_t hitCount = 0;
unsigned long lastStatusSwitch = 999999;

boolean isSwitchingPalette = false;

long before, processingTime;

// Set up effets
std::string demoseq = "abcdefghijabcdefghij     k   l   m     n     m    n    m   n   m  n  m nmnmnmnmn        abcdefghijabcdefghij        klklklklklklklkl      ";
ShapeSequencer* effectShapeSequencer;

Noise* effectNoise;
BlinkingStars* effectBlinkingStars;
ShapeEffectPerformer* effectFire;
ShapeEffectPerformer* effectZigZag;

void setupEffects()
{
	effectShapeSequencer = new ShapeSequencer(leds, demoseq, 75, 0, 25);
	effectNoise = new Noise(leds);
	effectBlinkingStars = new BlinkingStars(leds, 49, 0, 10);	
	effectFire = new ShapeEffectPerformer(leds);
	
	effectFire->AddEffect(new Fire(getShape("l1"), 55, 80));
	effectFire->AddEffect(new Fire(getShape("l2"), 55, 80));
	effectFire->AddEffect(new Fire(getShape("l3"), 55, 80));
	effectFire->AddEffect(new Fire(getShape("l4"), 55, 80));
	effectFire->AddEffect(new Fire(getShape("l7"), 55, 80));
	effectFire->AddEffect(new Fire(getShape("l8"), 55, 80));

	effectZigZag = new ShapeEffectPerformer(leds,10,0,70);
	effectZigZag->AddEffect(new ZigZag(getShape("l1")));
	effectZigZag->AddEffect(new ZigZag(getShape("l2")));
	effectZigZag->AddEffect(new ZigZag(getShape("l3")));
	effectZigZag->AddEffect(new ZigZag(getShape("l4")));
	effectZigZag->AddEffect(new ZigZag(getShape("l7")));
	effectZigZag->AddEffect(new ZigZag(getShape("l8")));
}

Effect* activeEffect;

class MyServerCallbacks : public BLEServerCallbacks
{
	void onConnect(BLEServer* pServer)
	{
		deviceConnected = true;
		Serial.println("Device connected.");
		oldDeviceConnected = deviceConnected;
	};

	void onDisconnect(BLEServer* pServer)
	{
		deviceConnected = false;
		if (oldDeviceConnected)
		{
			Serial.println("Device disconnected. Wait 500 ms before advertising again.");
			delay(500);  // Give the bluetooth stack the chance to get things ready
			pServer->startAdvertising(); // Restart advertising
			Serial.println("Start advertising.");
			oldDeviceConnected = deviceConnected;
		}
	}
};

class BluetoothCallback : public BLECharacteristicCallbacks
{	
	void onWrite(BLECharacteristic *pCharacteristic)
	{
		std::string rxValue = pCharacteristic->getValue();
		uint16_t n = stoi(rxValue);

		if (pCharacteristic == pCharBrightness)
		{
			if (n < 65535) LEDS.setBrightness(n);
		}
		else if (pCharacteristic == pCharMode)
		{
			// Clear all LEDS on mode change
			FastLED.clear();

			if      (rxValue == "demo")			mode = demo;
			else if (rxValue == "effect")		mode = effect;
			else if (rxValue == "alternate")	mode = alternate;
			else if (rxValue == "text")			mode = text;
		}
		else if (pCharacteristic == pCharEffect) // Effect Type
		{
			// Clear all LEDS on effect change
			FastLED.clear();

			if (rxValue == "Noise")			effecttype = noise;
			else if (rxValue == "Fire")		effecttype = fire;
			else if (rxValue == "Stars")	effecttype = stars;
			else if (rxValue == "ZigZag")	effecttype = zigzag;
		}
		else if (pCharacteristic == pCharTextPAL) // Text palette
		{
			if      (rxValue == "Cloud")					effectShapeSequencer->SetPalette(CloudColors_p);
			else if (rxValue == "Lava")						effectShapeSequencer->SetPalette(LavaColors_p);
			else if (rxValue == "Party")					effectShapeSequencer->SetPalette(PartyColors_p);
			else if (rxValue == "Ocean")					effectShapeSequencer->SetPalette(OceanColors_p);
			else if (rxValue == "Forest")					effectShapeSequencer->SetPalette(ForestColors_p);
			else if (rxValue == "Heat")						effectShapeSequencer->SetPalette(HeatColors_p);
			else if (rxValue == "Rainbow")					effectShapeSequencer->SetPalette(RainbowColors_p);
			else if (rxValue == "RainbowStripe")			effectShapeSequencer->SetPalette(RainbowStripeColors_p);
			else if (rxValue == "Purple/Green")				effectShapeSequencer->SetPalette(getPurpleAndGreenPalette());
			else if (rxValue == "Purple/White")				effectShapeSequencer->SetPalette(getPurpleAndWhitePalette());
			else if (rxValue == "B/W Striped")				effectShapeSequencer->SetPalette(getBlackAndWhiteStripedPalette());
			else if (rxValue == "B/W/Purple Striped")		effectShapeSequencer->SetPalette(getBlackAndWhiteAndPurpleStripedPalette());
			else if (rxValue == "Red")						effectShapeSequencer->SetPalette(CRGBPalette16(CRGB::Red));
			else if (rxValue == "Yellow")					effectShapeSequencer->SetPalette(CRGBPalette16(CRGB::Yellow));
			else if (rxValue == "Green")					effectShapeSequencer->SetPalette(CRGBPalette16(CRGB::Green));
			else if (rxValue == "Blue")						effectShapeSequencer->SetPalette(CRGBPalette16(CRGB::Blue));
		}
		else if (pCharacteristic == pCharEffectPAL) // Effect palette
		{
			if (rxValue == "Cloud")							activeEffect->SetPalette(CloudColors_p);
			else if (rxValue == "Lava")						activeEffect->SetPalette(LavaColors_p);
			else if (rxValue == "Party")					activeEffect->SetPalette(PartyColors_p);
			else if (rxValue == "Ocean")					activeEffect->SetPalette(OceanColors_p);
			else if (rxValue == "Forest")					activeEffect->SetPalette(ForestColors_p);
			else if (rxValue == "Heat")						activeEffect->SetPalette(HeatColors_p);
			else if (rxValue == "Rainbow")					activeEffect->SetPalette(RainbowColors_p);
			else if (rxValue == "RainbowStripe")			activeEffect->SetPalette(RainbowStripeColors_p);
			else if (rxValue == "Purple/Green")				activeEffect->SetPalette(getPurpleAndGreenPalette());
			else if (rxValue == "Purple/White")				activeEffect->SetPalette(getPurpleAndWhitePalette());
			else if (rxValue == "B/W Striped")				activeEffect->SetPalette(getBlackAndWhiteStripedPalette());
			else if (rxValue == "B/W/Purple Striped")		activeEffect->SetPalette(getBlackAndWhiteAndPurpleStripedPalette());
			else if (rxValue == "Red")						activeEffect->SetPalette(CRGBPalette16(CRGB::Red));
			else if (rxValue == "Yellow")					activeEffect->SetPalette(CRGBPalette16(CRGB::Yellow));
			else if (rxValue == "Green")					activeEffect->SetPalette(CRGBPalette16(CRGB::Green));
			else if (rxValue == "Blue")						activeEffect->SetPalette(CRGBPalette16(CRGB::Blue));
		}
		else if (pCharacteristic == pCharEffectSPD) // Effect speed
		{			
			if (n < 65535) activeEffect->SetSpeed(n);
		}
		else if (pCharacteristic == pCharEffectSCL) // Effect scale
		{
			if (n < 65535) activeEffect->SetScale(n);
		}
		else if (pCharacteristic == pCharEffectFAD) // Effect fade
		{
			if (n < 65535) activeEffect->SetFade(n);
		}
		else if (pCharacteristic == pCharEffectCLL) // Colour loop
		{
			if (rxValue == "true")			activeEffect->SetColorLoop(true);
			else if (rxValue == "false")	activeEffect->SetColorLoop(false);
		}
		else if (pCharacteristic == pCharTextFFC) // Fast flashing colours toggle
		{
			if		(rxValue == "true")		effectShapeSequencer->SetFFC(true);
			else if (rxValue == "false")	effectShapeSequencer->SetFFC(false);
		}
		else if (pCharacteristic == pCharText1)   // Text (first 20 bytes)
		{
			effectShapeSequencer->SetText1(rxValue);
		}
		else if (pCharacteristic == pCharText2)   // Text (seconds 20 bytes)
		{
			effectShapeSequencer->SetText2(rxValue);
		}
		else if (pCharacteristic == pCharTextTPC) // Time per character (ms)
		{
			if (n < 65535) effectShapeSequencer->SetTPC(n);
		}
		else if (pCharacteristic == pCharTextBBC) // Blank between characters (ms)
		{
			if (n < 65535) effectShapeSequencer->SetBBC(n);
		}
		else if (pCharacteristic == pCharTextFAD) // Fadeout time (ms)
		{
			if (n < 65535) effectShapeSequencer->SetFAD(n);
		}
		else if (pCharacteristic == pCharTextEVR) // Display text every (s)
		{			
			if (n < 65535) displayTextEvery = n;
		}
	}
};

BluetoothCallback *BTCB = new BluetoothCallback();

void setupBLE()
{
	// Create the BLE Device
	BLEDevice::init("Wouter's LED Thing");

	// Create the BLE Server
	pServer = BLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());

	// Create the BLE Service
	BLEService *pService = pServer->createService(SERVICE_UUID);

	// Create BLE characteristics
	pCharBrightness = pService->createCharacteristic(UUID_BRIGHTNESS,	BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharMode		= pService->createCharacteristic(UUID_MODE,			BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharTextTPC	= pService->createCharacteristic(UUID_TEXT_TPC,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharTextBBC	= pService->createCharacteristic(UUID_TEXT_BBC,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharTextFAD	= pService->createCharacteristic(UUID_TEXT_FAD,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharTextEVR    = pService->createCharacteristic(UUID_TEXT_EVR,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharTextPAL	= pService->createCharacteristic(UUID_TEXT_PAL,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharTextFFC	= pService->createCharacteristic(UUID_TEXT_FFC,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharText1		= pService->createCharacteristic(UUID_TEXT_1,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharText2		= pService->createCharacteristic(UUID_TEXT_2,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharEffect		= pService->createCharacteristic(UUID_EFX,			BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharEffectFAD  = pService->createCharacteristic(UUID_EFX_FAD,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharEffectSPD  = pService->createCharacteristic(UUID_EFX_SPD,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharEffectSCL  = pService->createCharacteristic(UUID_EFX_SCL,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharEffectPAL  = pService->createCharacteristic(UUID_EFX_PAL,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
	pCharEffectCLL  = pService->createCharacteristic(UUID_EFX_CLL,		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);

	pCharBrightness->setCallbacks(BTCB);
	pCharMode->setCallbacks(BTCB);
	pCharTextTPC->setCallbacks(BTCB);
	pCharTextBBC->setCallbacks(BTCB);
	pCharTextFAD->setCallbacks(BTCB);
	pCharTextEVR->setCallbacks(BTCB);
	pCharTextPAL->setCallbacks(BTCB);
	pCharTextFFC->setCallbacks(BTCB);
	pCharText1->setCallbacks(BTCB);
	pCharText2->setCallbacks(BTCB);
	pCharEffect->setCallbacks(BTCB);
	pCharEffectFAD->setCallbacks(BTCB);
	pCharEffectSPD->setCallbacks(BTCB);
	pCharEffectSCL->setCallbacks(BTCB);
	pCharEffectPAL->setCallbacks(BTCB);
	pCharEffectCLL->setCallbacks(BTCB);
	
	// Start the service
	pService->start();

	// Start advertising
	BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
	pAdvertising->addServiceUUID(SERVICE_UUID);
	pAdvertising->setScanResponse(false);
	pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
	BLEDevice::startAdvertising();	
}

void setupLEDS()
{
	LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	LEDS.setBrightness(BRIGHTNESS);
}

void setup()
{
	Serial.begin(115200); // use the serial port	
	Serial.println("Start BLE setup");
	setupBLE();	
	Serial.println("Start LED setup");
	setupLEDS();
	Serial.println("Start effects setup");
	setupEffects();
	Serial.println("Finished with setup");
	Serial.println(ESP.getFreeHeap());
	activeEffect = effectNoise;
}

void loop()
{	
	switch (mode)
	{
		case demo:
			SetEffectForDemoMode();			
			break;

		case text:
			activeEffect = effectShapeSequencer;
			break;

		case effect:

			switch (effecttype) 
			{
				case stars:
					activeEffect = effectBlinkingStars;
					break;

				case noise:
					activeEffect = effectNoise;
					break;

				case fire:
					activeEffect = effectFire;
					break;

				case zigzag:
					activeEffect = effectZigZag;
					break;
			}

			break;

		case alternate:

			if (millis() - _timeStampLastText > (displayTextEvery * 1000)) // Time to display the text
			{
				activeEffect = effectShapeSequencer;

				if (!textWasReset)
				{					
					effectShapeSequencer->reset();
					textWasReset = true;
				}

				if (effectShapeSequencer->Perform(true)) // returns true when whole text has been displayed
				{					
					_timeStampLastText = millis();
					textWasReset = false;
				}
			}
			else
			{
				SetEffectForDemoMode();
			}

			break;
	}

	if (activeEffect != NULL) activeEffect->Perform(false);
	LEDS.show();		
}

#define HOLD_PALETTES_X_TIMES_AS_LONG 4
void SetEffectForDemoMode()
{
	uint8_t seq = ((millis() / 1000) / 30) % 20; //  Display something else every 30 seconds for a 10 minute demo sequence.
	static uint8_t lastSeq = 99;

	if (lastSeq != seq)
	{
		lastSeq = seq;

		switch (seq)
		{
			case 0: // Slow lava colours
				activeEffect = effectNoise;
				effectNoise->SetPalette(LavaColors_p);
				effectNoise->SetSpeed(2);
				effectNoise->SetScale(3);
				effectNoise->SetColorLoop(0);
				break;
			case 1: // Fast black and white flashes
				activeEffect = effectNoise;
				effectNoise->SetPalette(getBlackAndWhiteStripedPalette());
				effectNoise->SetSpeed(25);
				effectNoise->SetScale(3);
				effectNoise->SetColorLoop(1);
				break;
			case 2: // Blinking yellow stars
				FastLED.clear();
				activeEffect = effectBlinkingStars;
				effectBlinkingStars->SetPalette(CRGBPalette16(CRGB::Yellow));
				effectBlinkingStars->SetSpeed(49);
				effectBlinkingStars->SetScale(0);
				effectBlinkingStars->SetFade(10);
				break;
			case 3: // Blinking rainbow stars
				activeEffect = effectBlinkingStars;
				effectBlinkingStars->SetPalette(RainbowColors_p);
				effectBlinkingStars->SetSpeed(49);
				effectBlinkingStars->SetScale(1);
				effectBlinkingStars->SetFade(25);
				break;
			case 4: // Rainbow noise
				activeEffect = effectNoise;
				effectNoise->SetPalette(RainbowColors_p);
				effectNoise->SetSpeed(4);
				effectNoise->SetScale(3);
				effectNoise->SetColorLoop(1);
				break;
			case 5: // Ocean Colours
				activeEffect = effectNoise;
				effectNoise->SetPalette(OceanColors_p);
				effectNoise->SetSpeed(10);
				effectNoise->SetScale(12);
				effectNoise->SetColorLoop(0);
				break;
			case 6: // Heat colours noise
				activeEffect = effectNoise;
				effectNoise->SetPalette(HeatColors_p);
				effectNoise->SetSpeed(5);
				effectNoise->SetScale(7);
				effectNoise->SetColorLoop(1);
				break;
			case 7: // Slow white purple
				activeEffect = effectNoise;
				effectNoise->SetPalette(getBlackAndWhiteAndPurpleStripedPalette());
				effectNoise->SetSpeed(5);
				effectNoise->SetScale(7);
				effectNoise->SetColorLoop(0);
				break;
			case 8: // Fast white purple
				activeEffect = effectNoise;
				effectNoise->SetPalette(getBlackAndWhiteAndPurpleStripedPalette());
				effectNoise->SetSpeed(25);
				effectNoise->SetScale(5);
				effectNoise->SetColorLoop(0);
				break;
			case 9: // Zigzag slow red
				FastLED.clear();
				activeEffect = effectZigZag;
				effectZigZag->SetPalette(CRGBPalette16(CRGB::Red));
				effectZigZag->SetSpeed(5);
				effectZigZag->SetFade(50);
				break;
			case 10: // Zigzag faster yellow
				activeEffect = effectZigZag;
				effectZigZag->SetPalette(CRGBPalette16(CRGB::Yellow));
				effectZigZag->SetSpeed(25);
				effectZigZag->SetFade(40);
				break;
			case 11: // Fire effect
				FastLED.clear();
				activeEffect = effectFire;
				break;
			case 12: // Text effect
				FastLED.clear();
				activeEffect = effectShapeSequencer;
				effectShapeSequencer->SetText1(demoseq);
				effectShapeSequencer->SetText2("");
				effectShapeSequencer->SetTPC(75);
				effectShapeSequencer->SetBBC(0);
				effectShapeSequencer->SetFade(25);
				break;
			case 13: // Strobe
				FastLED.clear();
				activeEffect = effectBlinkingStars;
				effectBlinkingStars->SetPalette(getBlackAndWhiteStripedPalette());
				effectBlinkingStars->SetSpeed(50);
				effectBlinkingStars->SetScale(10);
				effectBlinkingStars->SetFade(30);
				break;
			case 14: // Party
				activeEffect = effectBlinkingStars;
				effectBlinkingStars->SetPalette(PartyColors_p);
				effectBlinkingStars->SetSpeed(45);
				effectBlinkingStars->SetScale(10);
				effectBlinkingStars->SetFade(20);
				break;
			case 15: // THIS IS NOT REAL - NOTHING IS REAL
				FastLED.clear();
				activeEffect = effectShapeSequencer;
				effectShapeSequencer->SetText1("THIS IS NOT REAL  l  NOTHING IS REAL  l  ");
				effectShapeSequencer->SetText2("");
				effectShapeSequencer->SetTPC(500);
				effectShapeSequencer->SetBBC(50);
				effectShapeSequencer->SetFade(40);
				break;
			case 16: // Fast red zigzag
				FastLED.clear();
				activeEffect = effectZigZag;
				effectZigZag->SetPalette(CRGBPalette16(CRGB::Red));
				effectZigZag->SetSpeed(50);
				effectZigZag->SetFade(100);
				break;
			case 17: // Purple white noise
				FastLED.clear();
				activeEffect = effectNoise;
				effectNoise->SetPalette(getPurpleAndWhitePalette());
				effectNoise->SetSpeed(22);
				effectNoise->SetScale(10);
				effectNoise->SetColorLoop(0);
				break;
			case 18: // Part stars
				FastLED.clear();
				activeEffect = effectBlinkingStars;
				effectBlinkingStars->SetPalette(LavaColors_p);
				effectBlinkingStars->SetSpeed(49);
				effectBlinkingStars->SetScale(10);
				effectBlinkingStars->SetFade(35);
				break;
			case 19: // Rainbow noise
				FastLED.clear();
				activeEffect = effectNoise;
				effectNoise->SetPalette(RainbowStripeColors_p);
				effectNoise->SetSpeed(0);
				effectNoise->SetScale(10);
				effectNoise->SetColorLoop(0);
				break;
		}		
	}
}
