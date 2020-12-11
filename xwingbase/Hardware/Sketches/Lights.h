#include "Arduino.h"

// datastructure for routine
struct DroidLightsParameters droidLightsParameters;

// initialize four leds as outputs

// structure to pass data through the droidLights routine
struct DroidLightsParameters {
	bool isDroidSetup; // needs to be set to false every time the non-blocking routine completes a full run
	int beeps;
	int points[maxPoints] ; // there will never be more points than maxPoints anyway, and variable arrays introduce fragmentation in Arduinos that lead to early stops of the program. Variable array = bad.
};


// routines declaration
void bunkerLights();
void droidLights(struct DroidLightsParameters*);
