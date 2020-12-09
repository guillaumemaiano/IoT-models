// GPIO definitions
// *********
const uint8_t whiteLED_TIE = D5; // GPIO14
const uint8_t redLED_Bunker = D8; // GPIO15
const uint8_t whiteLED_Xwing = D2; // GPIO4
const uint8_t blueLED_Xwing = D1; // GPIO5

// routines setup
// *********
// interval definitions in milliseconds
const unsigned long large_silence_interval = 1000;
const unsigned long short_silence_interval = 100;
const unsigned long short_emission_interval = 100;

// time tracker definitions
unsigned long time_tracker_millis_bunker = 0; // bunkerLights routine
unsigned long time_tracker_millis_droid = 0; // droidLights routine tracker

// triggers for the routines
bool isBunkerRoutineActive = true;

// initialize four leds as outputs

// structure to pass data through the droidLights routine
struct DroidLightsParameters {
  const int defaultDuration = 270; // ceil(4 seconds /15 points)
  const int maxDuration = 4000; // max duration of a cycle in milliseconds
  const int maxPoints = 15; // max occurrences of a "point" (up signal of varying length)
  const int durations[3] = {100, 300, 500}; // possible durations of a point (short, medium, long)
  const int separationInterval = 100; // a millisecond duration to separate "points" visually
  bool isDroidSetup = false; // needs to be set to false every time the non-blocking routine completes a full run
  int beeps = 0;
  int points[0]; // flexible array members do not work with Arduino IDE (GCC 5.4.0, 6 required...)
  // attempting systematic free-and-overwrite
};

struct DroidLightsParameters droidLightsParameters;

// routines declaration
void setupDroidLights(struct DroidLightsParameters*);
void droidLights(struct DroidLightsParameters*);

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
}

// main loop runs perpetually after setup has run
void loop() {
  if (isBunkerRoutineActive) {
    bunkerLights();
  }
  droidLights(&droidLightsParameters);
}

// basic non-blocking version of bunker lights
// uses only one tracker, computes the durations on the fly every iteration (unoptimized, more readable)
void bunkerLights() {
	// shut the led at loop start
        	digitalWrite(redLED_Bunker,
        LOW);

}

void setupDroidLights(struct DroidLightsParameters *droidLightsParameters) {
  // prep randoms
  randomSeed(analogRead(0));
  droidLightsParameters->beeps = random(1, droidLightsParameters->maxDuration);
  int points[droidLightsParameters->beeps];
  for (int point = 0; point < droidLightsParameters->beeps; point++) {
        int pointLength = random(0,4); // if 3, then point is a blank
        if (pointLength == 3) {
                points[point] = 0; // standard empty point is 270ms long
        } else {
          points[point] = droidLightsParameters->durations[pointLength];
        }
  }
  droidLightsParameters->points = &points;
  droidLightsParameters->isDroidSetup =  true;
}

void droidLights(struct DroidLightsParameters * droidLightsParameters) {
  if (!droidLightsParameters->isDroidSetup) {
     setupDroidLights(droidLightsParameters);
  }
  // execute blocking basic loop
  // Turn off Droid LED at loop start
  digitalWrite(blueLED_Xwing,
        LOW);
  int currentDuration = 0;
  for (int currentPoint = 0; currentPoint < droidLightsParameters->beeps && currentDuration < droidLightsParameters->maxDuration; currentPoint++) {
        if (droidLightsParameters->points[currentPoint] == 0){
                // make sure that led *is* off, as it should be
                digitalWrite(blueLED_Xwing,
                LOW);
                delay(droidLightsParameters->defaultDuration);
                currentDuration += droidLightsParameters->defaultDuration;
        } else {
                int value = droidLightsParameters->points[currentPoint];
                digitalWrite(blueLED_Xwing,
                HIGH);
                delay(value);
                currentDuration += value;
                digitalWrite(blueLED_Xwing,
                LOW);
                delay(droidLightsParameters->separationInterval);
        }
  }
  droidLightsParameters->isDroidSetup = false;
  if (droidLightsParameters->beeps != 0) {
		free(droidLightsParameters->points);
		droidLightsParameters->beeps = 0;
  }
}
