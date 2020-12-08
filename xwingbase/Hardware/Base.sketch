// hardware definitions
const uint8_t whiteLED_TIE = D5; // GPIO14
const uint8_t redLED_Bunker = D8; // GPIO15
const uint8_t whiteLED_Xwing = D2; // GPIO4
const uint8_t blueLED_Xwing = D1; // GPIO5

// interval definitions in milliseconds
const unsigned long large_silence_interval = 1000;
const unsigned long short_silence_interval = 100;
const unsigned long short_emission_interval = 100;

// time tracker definitions
unsigned long time_tracker_millis_bunker = 0; // bunkerLights routine

// triggers for the routines
bool isBunkerRoutineActive = true;

// initialize four leds as outputs
void setup() {
  pinMode(whiteLED_TIE,
          OUTPUT);
  pinMode(blueLED_Xwing,
          OUTPUT);
  pinMode(whiteLED_Xwing,
          OUTPUT);
  pinMode(redLED_Bunker,
          OUTPUT);
}

// stripped loop calling the red led routine
void loop() {
	if (isBunkerRoutineActive) {
  		bunkerLights();
	}
}

// basic non-blocking version of bunker lights
// uses only one tracker, computes the durations on the fly every iteration (unoptimized, more readable)
void bunkerLights() {
	// shut the led at loop start
        	digitalWrite(redLED_Bunker,
        LOW);

}

void droidLight() {
  int maxDuration = 5000; // max duration of a cycle in milliseconds
  int maxPoints = 15; //
  randomSeed();
  //beeps = random(0,15);
}
