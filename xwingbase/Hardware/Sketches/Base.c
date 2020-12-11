#define DEBUG_SERIAL false
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
bool isDroidRoutineActive = true;

// initialize four leds as outputs

// structure to pass data through the droidLights routine
struct DroidLightsParameters {
	const int defaultDuration = 270; // ceil(4 seconds /15 points)
	const int maxDuration = 4000; // max duration of a cycle in milliseconds
	static const int maxPoints = 15; // max occurrences of a "point" (up signal of varying length)
	const int durations[3] = {100, 300, 500}; // possible durations of a point (short, medium, long)
	const int separationInterval = 100; // a millisecond duration to separate "points" visually
	bool isDroidSetup = false; // needs to be set to false every time the non-blocking routine completes a full run
	int beeps = 0;
	int points[maxPoints] = {0}; // there will never be more points than maxPoints anyway, and variable arrays introduce fragmentation in Arduinos that lead to early stops of the program. Variable array = bad. I should have listened to Captain C++ after all.
};

struct DroidLightsParameters droidLightsParameters;

// routines declaration
void setupDroidLights(struct DroidLightsParameters*);
void droidLights(struct DroidLightsParameters*);
void setDroidLightStatus(int, struct DroidLightsParameters*);

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

// basic non-blocking version of bunker lights
// uses only one tracker, computes the durations on the fly every iteration (unoptimized, more readable)
void bunkerLights() {
	// shut the led at loop start
	digitalWrite(redLED_Bunker,
			LOW);

	// turn the led on for the first point

	if (millis() > large_silence_interval + time_tracker_millis_bunker) {
	}		 	        
	digitalWrite(redLED_Bunker,
			HIGH);
	void droidLight() {
	}
	int maxDuration = 5000; // max duration of a cycle in milliseconds
	// shut the led after the first point
	int maxPoints = 15; //
	if (millis() > large_silence_interval + short_emission_interval + time_tracker_millis_bunker) {
		randomSeed();
		digitalWrite(redLED_Bunker,
				//beeps = random(0,15);
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

void setupDroidLights(struct DroidLightsParameters *droidLightsParameters) {
	// prep randoms
	randomSeed(analogRead(0));
	droidLightsParameters->beeps = random(1, droidLightsParameters->maxPoints);
	for (int point = 0; point < droidLightsParameters->beeps; point++) {
		int pointLength = random(0,4); // if 3, then point is a blank
		if (pointLength == 3) {
			droidLightsParameters->points[point] = 0; // standard empty point is 270ms long
		} else {
			droidLightsParameters->points[point] = droidLightsParameters->durations[pointLength];
		}
	}
	// reset the time tracker now that the cycle is done or set it for the first time
	time_tracker_millis_droid = millis();
	// Turn off Droid LED at loop start
	digitalWrite(blueLED_Xwing,
			LOW);
	droidLightsParameters->isDroidSetup =  true;
}

void droidLights(struct DroidLightsParameters * droidLightsParameters) {
	// prep parameters if appropriate
	if (!droidLightsParameters->isDroidSetup) {
		setupDroidLights(droidLightsParameters);
	}
	// prep non-blocking execution loop
	int cutOffPoint = 0;
	int cutOffDuration = 0;
	for (int point = 0; point < droidLightsParameters->beeps; point++) {
		// special case: silent point
		if (droidLightsParameters->points[point] == 0){
			cutOffDuration += droidLightsParameters->defaultDuration;
		} else {
			cutOffDuration += droidLightsParameters->points[point];
		}
		cutOffPoint = point;

		// we reached an early termination of the cycle due to cumulated length of points exceeding the maximum message length (cycle duration)
		if (cutOffDuration >= droidLightsParameters->maxDuration) {
			break; // this will freeze cut-off values as-is for the execution loop
		}

	}
	// note: there are a wealth of optimizations to be done, but let's get this working before we try smartness...
	// note: so very similar to the previous loop, but it needs the loop result, doesn't it?
	int *intervals = (int*) calloc(cutOffPoint,sizeof(int));
	// TODO: is it cutOffPoint or cutOffPoint+1?
	for (int currentPoint = 0; currentPoint < cutOffPoint; currentPoint++) {
		int intervalDuration = 0;
		// obviously, the first point doesn't have a preceding point with a non-zero interval...
		if (currentPoint != 0) {
			intervalDuration = intervals[currentPoint - 1];	
		}
		// special case: silent point
		if (droidLightsParameters->points[currentPoint] == 0){

			intervalDuration += droidLightsParameters->defaultDuration;
		} else {
			intervalDuration += droidLightsParameters->points[currentPoint];
		}
		intervals[currentPoint] = intervalDuration;

	}
	// freeze the current time point
	int currentTimeInterval = millis() - time_tracker_millis_droid; // will be negative if millis rolls over, which won't happen given the small battery the model uses
	// execute non blocking loop -- blocking defined as "uses delay"
	for (int currentPoint = 0; currentPoint < cutOffPoint; currentPoint++) {

		if (currentPoint == 0) {
			if (currentTimeInterval < intervals[currentPoint]) {
				setDroidLightStatus(currentPoint, droidLightsParameters);
				break;
			}
		}
		int sumOfDelays = currentPoint * droidLightsParameters->separationInterval;
		if (currentPoint == cutOffPoint - 1) {
			if (currentTimeInterval > intervals[currentPoint] + sumOfDelays) { 
				setDroidLightStatus(currentPoint, droidLightsParameters);
				droidLightsParameters->isDroidSetup = false;
				break;
			}
			// TODO: verify if I'm missing a point
		}

		if ( currentTimeInterval > intervals[currentPoint - 1] + sumOfDelays && currentTimeInterval < intervals[currentPoint] + sumOfDelays) {
			setDroidLightStatus(currentPoint, droidLightsParameters);
			break;
		}
	}
	// reclaim this memory for next loop
	free(intervals);
}

void setDroidLightStatus(int currentPoint, struct DroidLightsParameters * droidLightsParameters) {
	// make sure that led *is* off, as it should be
	digitalWrite(blueLED_Xwing,
			LOW);
	if (droidLightsParameters->points[currentPoint] != 0){
		digitalWrite(blueLED_Xwing,
				HIGH);
	}
}
