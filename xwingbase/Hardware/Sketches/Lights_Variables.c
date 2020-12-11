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
