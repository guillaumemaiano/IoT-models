#include "Lights.h"
#include "Lights_Droid.h"

// Needed because the pin definition is trickier than it looks (Arduino IDE adding dependencies)
extern const uint8_t blueLED_Xwing;

unsigned long time_tracker_millis_droid = 0; // checks time elapsed since cycle started

void setupDroidLights(struct DroidLightsParameters *droidLightsParameters) {
	// prep randoms
	srand(analogRead(0));
	droidLightsParameters->beeps = (rand()+1)%maxPoints;
	for (int point = 0; point < droidLightsParameters->beeps; point++) {
		int pointLength = rand()%4;//(0,4); // if 3, then point is a blank
		if (pointLength == 3) {
			droidLightsParameters->points[point] = 0; // standard empty point is 270ms long
		} else {
			droidLightsParameters->points[point] = durations[pointLength];
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
			cutOffDuration += defaultDuration;
		} else {
			cutOffDuration += droidLightsParameters->points[point];
		}
		cutOffPoint = point;

		// we reached an early termination of the cycle due to cumulated length of points exceeding the maximum message length (cycle duration)
		if (cutOffDuration >= maxDuration) {
			break; // this will freeze cut-off values as-is for the execution loop
		}

	}
	// note: there are a wealth of optimizations to be done, but let's get this working before we try smartness...
	// note: so very similar to the previous loop, but it needs the loop result, doesn't it?
	int *intervals = (int*) calloc(cutOffPoint+1,sizeof(int));
	for (int currentPoint = 0; currentPoint < cutOffPoint + 1; currentPoint++) {
		int intervalDuration = 0;
		// obviously, the first point doesn't have a preceding point with a non-zero interval...
		if (currentPoint != 0) {
			intervalDuration = intervals[currentPoint - 1];	
		}
		// special case: silent point
		if (droidLightsParameters->points[currentPoint] == 0){

			intervalDuration += defaultDuration;
		} else {
			intervalDuration += points[currentPoint];
		}
		intervals[currentPoint] = intervalDuration;

	}
	// freeze the current time point
	int currentTimeInterval = millis() - time_tracker_millis_droid; // will be negative if millis rolls over, which won't happen given the small battery the model uses
	// execute non blocking loop -- blocking defined as "uses delay"
	for (int currentPoint = 0; currentPoint < cutOffPoint + 1; currentPoint++) {

		if (currentPoint == 0) {
			if (currentTimeInterval < intervals[currentPoint]) {
				setDroidLightStatus(currentPoint, droidLightsParameters);
				break;
			}
		}
		int sumOfDelays = currentPoint * separationInterval;
		if (currentPoint == cutOffPoint) {
			if (currentTimeInterval > intervals[currentPoint] + sumOfDelays) { 
				setDroidLightStatus(currentPoint, droidLightsParameters);
				droidLightsParameters->isDroidSetup = false;
				break;
			}
		}
		// shutdown the droid LED, lest it stays on during the separating pauses!
		digitalWrite(blueLED_Xwing,
				LOW);
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
