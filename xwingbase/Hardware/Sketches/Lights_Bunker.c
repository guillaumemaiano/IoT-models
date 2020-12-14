#include "Lights.h"
#include "Lights_Bunker.h"

extern const uint8_t redLED_Bunker;

// time tracker
unsigned long time_tracker_millis_bunker = 0; // checks time elapsed since cycle started

// basic non-blocking version of bunker lights
// uses only one tracker, computes the durations on the fly every iteration (unoptimized, more readable)
void bunkerLights() {
	// shut the led at loop start
	digitalWrite(redLED_Bunker,
			LOW);

	// turn the led on for the first point

	if (millis() > large_silence_interval + time_tracker_millis_bunker) {
	digitalWrite(redLED_Bunker,
			HIGH);
	}
	// shut the led after the first point
	if (millis() > large_silence_interval + short_emission_interval + time_tracker_millis_bunker) {
		digitalWrite(redLED_Bunker,
				LOW);
	}
	// turn the led on for the second point
	if (millis() > large_silence_interval + short_emission_interval + short_silence_interval + time_tracker_millis_bunker) {
		digitalWrite(redLED_Bunker,
				HIGH);
	}
	// shut the led after the second point and updates the tracker for next loop
	if (millis() > large_silence_interval + short_emission_interval + short_silence_interval + short_emission_interval + time_tracker_millis_bunker) {
		time_tracker_millis_bunker = millis();	
		digitalWrite(redLED_Bunker,
				LOW);
	}
}

