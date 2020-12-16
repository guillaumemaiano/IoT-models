#include "Lights.h"
#include "Lights_Bunker.h"
#include "Lights_Droid.h"
#include "ModelWiFi.h"

#define DEBUG_SERIAL true

#define LED_PINS 4

// GPIO 
// *********
extern const uint8_t blueLED_Xwing = D1; // GPIO5
extern const uint8_t whiteLED_Xwing = D2; // GPIO4
extern const uint8_t whiteLED_TIE = D5; // GPIO14
extern const uint8_t redLED_Bunker = D8; // GPIO15

extern const int ledsPinsAvailable = LED_PINS;

extern const uint8_t ledPins[LED_PINS] = {
	whiteLED_TIE,
	redLED_Bunker,
	whiteLED_Xwing,
	blueLED_Xwing
};

// triggers for the routines
//extern bool isXWingBoardRoutineActive;
//extern bool isBunkerRoutineActive;
//extern bool isDroidRoutineActive;
//extern bool isTIERoutineActive;

// parameters for the droid lights function
struct DroidLightsParameters droidLightsParameters;

void setup() {
	// hardware setup
	pinMode(whiteLED_TIE,
			OUTPUT);
	pinMode(blueLED_Xwing,
			OUTPUT);
	pinMode(whiteLED_Xwing,
			OUTPUT);
	pinMode(redLED_Bunker,
			OUTPUT);
#ifdef DEBUG_SERIAL
	Serial.begin(74880); // 115200 bauds in-source log works, but the reboot log demands 74880 bauds, so we'll use that instead
	Serial.println("Debug mode enabled");
	for (uint8_t t = 4; t > 0; t--) {
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}
#endif
	// software setup
	wifiErrorSignalActive = false;
#ifdef DEBUG_SERIAL
	setupWiFi(true);
#else
	setupWiFi(false);
#endif
	//software setup
	prepareXWing(&xwingLightsParameters);
}

// main loop runs perpetually after setup has run
void loop() {
	if (wifiErrorSignalActive) {
		ErrorLEDDisplay error = LEDWiFiError;
		blinkError(error);
	}
	if (isBunkerRoutineActive) {
		bunkerLights();
	}
	if (isDroidRoutineActive) {
		droidLights(&droidLightsParameters);
	}
	if (isTIERoutineActive) {
		// run-once or it will blink at loop-rate and look dimmed...
		isTIERoutineActive = false;
		fighterTIELights();
	}
	if (isXWingBoardRoutineActive) {
		xwingLights(&xwingLightsParameters);
	}
}
