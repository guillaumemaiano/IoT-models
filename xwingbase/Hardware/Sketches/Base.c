#include "Lights.h"
#include "Lights_Bunker.h"
#include "Lights_Droid.h"


#define DEBUG_SERIAL false

// GPIO definitions
// *********
extern const uint8_t whiteLED_TIE = D5; // GPIO14
extern const uint8_t redLED_Bunker = D8; // GPIO15
extern const uint8_t whiteLED_Xwing = D2; // GPIO4
extern const uint8_t blueLED_Xwing = D1; // GPIO5

// triggers for the routines
bool isBunkerRoutineActive = true;
bool isDroidRoutineActive = true;
bool isTIERoutineActive = true;
bool isXWingBoardRoutineActive = true;

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
#endif
	//software setup
	prepareXWing(&xwingLightsParameters);
}

// main loop runs perpetually after setup has run
void loop() {
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
