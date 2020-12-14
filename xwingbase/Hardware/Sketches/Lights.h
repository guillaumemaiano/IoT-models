extern static const int maxPoints;

// initialize four leds as outputs
// GPIO definitions
// *********
extern const uint8_t whiteLED_TIE; // = D5; // GPIO14
extern const uint8_t redLED_Bunker; // = D8; // GPIO15
extern const uint8_t whiteLED_Xwing; // = D2; // GPIO4
extern const uint8_t blueLED_Xwing; // = D1; // GPIO5


// structure to pass data through the droidLights routine
struct DroidLightsParameters {
	bool isDroidSetup; // needs to be set to false every time the non-blocking routine completes a full run
	int beeps;
	int points[maxPoints] ; // there will never be more points than maxPoints anyway, and variable arrays introduce fragmentation in Arduinos that lead to early stops of the program. Variable array = bad.
};


// structure to pass data through the xwingLights routine
struct XWingLightsParameters {
	bool isXWingOn; // mirrors the HIGH/LOW state of the whiteLEDXWing
	int cycleTime;
};

// datastructures for routines
struct DroidLightsParameters droidLightsParameters;
struct XWingLightsParameters xwingLightsParameters;

// name-mangling in CPP
 #ifdef __cplusplus
 extern "C" {
 #endif
// routines declaration
 void bunkerLights();
 void fighterTIELights();
 void xwingLights(struct XWingLightsParameters*);
 void droidLights(struct DroidLightsParameters*);
 #ifdef __cplusplus
 }
 #endif
