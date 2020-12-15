#include "Lights.h"
#include "Lights_Bunker.h"
#include "Lights_Droid.h"
#include "ModelWiFi.h"


#define DEBUG_SERIAL true

// GPIO 
// *********
extern const uint8_t blueLED_Xwing = D1; // GPIO5
extern const uint8_t whiteLED_Xwing = D2; // GPIO4
extern const uint8_t whiteLED_TIE = D5; // GPIO14
extern const uint8_t redLED_Bunker = D8; // GPIO15

extern const int ledsPinsAvailable = 4;

extern const uint8_t ledPins[4] = {
	whiteLED_TIE,
	redLED_Bunker,
	whiteLED_Xwing,
	blueLED_Xwing
};

// triggers for the routines
extern bool isBunkerRoutineActive = true;
extern bool isDroidRoutineActive = true;
extern bool isTIERoutineActive = true;

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
 // software setup
        wifiErrorSignalActive = false;
	statusWiFiConnection = WiFi.begin(ssid, pass);
	if (statusWiFiConnection != WL_Connected) {
	  //  turn the routines off to make the signal be 100% a warning sign
	  //  Maybe add a pushbutton to bypass this later - would cycle to automatic "all routines on" mode
	  deactivateRoutines();
          signalConnectionFailure(DEBUG_SERIAL);
	} else {
	  testConnection(DEBUG_SERIAL);
	}
}

// main loop runs perpetually after setup has run
void loop() {
	if (wifiErrorSignalActive) {
		blinkError(ErrorLEDDisplay.WiFi);
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
}
