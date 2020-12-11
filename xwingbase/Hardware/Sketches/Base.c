#include "Lights.h"
#include "Lights_Bunker.h"
#include "Lights_Droid.h"


#define DEBUG_SERIAL false

// triggers for the routines
bool isBunkerRoutineActive = true;
bool isDroidRoutineActive = true;

// hardware setup
void setup() {
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
}

// main loop runs perpetually after setup has run
void loop() {
	if (isBunkerRoutineActive) {
		bunkerLights();
	}
	if (isDroidRoutineActive) {
		droidLights(&droidLightsParameters);
	}
}
