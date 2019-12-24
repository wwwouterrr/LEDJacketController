#ifndef _BLEConstants_h
#define _BLEConstants_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <BLEServer.h>

#define SERVICE_UUID    "4fafc201-1234-459e-5678-c5c9c331914b"
#define UUID_MODE			  "b936aa79-9bf6-442b-b689-c3bde7a3afce"
#define UUID_BRIGHTNESS	"beb5483e-1234-4688-5678-ea07361b26a8"	
#define UUID_TEXT_1			"8faa743c-a767-4f44-996b-75b648680f20"
#define UUID_TEXT_2			"8faa743c-a767-4f44-996b-75b648680f21"
#define UUID_TEXT_TPC		"4918adf4-1cb3-4503-994f-9402457b8e12"
#define UUID_TEXT_BBC		"6e90ed5e-6e35-4eff-bbbd-5d036907e7aa"
#define UUID_TEXT_FAD		"50a8b005-930b-4a73-8d0c-652c0dc81a3c"
#define UUID_TEXT_EVR		"12345678-930b-4a73-8d0c-652c0dc81a3c"
#define UUID_TEXT_PAL		"12345678-9999-4a73-8d0c-652c0dc81a3c"
#define UUID_TEXT_FFC		"12345678-8888-4a73-8d0c-652c0dc81a3c"
#define UUID_EFX			  "87654321-a767-1f4a-996b-15b648680f2a"
#define UUID_EFX_FAD		"12345678-a767-3f4c-996b-35b648680f2c"
#define UUID_EFX_SPD		"8faa743c-a767-1f4a-996b-15b648680f2a"
#define UUID_EFX_SCL		"8faa743c-a767-3f4c-996b-35b648680f2c"
#define UUID_EFX_PAL		"8faa743c-a767-4f4d-996b-45b648680f2d"
#define UUID_EFX_CLL		"8faa743c-a767-5f4e-996b-55b648680f2e"

#endif
