#include "ModelWifi.h"
#include "Lights.h" // Needed so I can blink the LED

unsigned long cycleDuration = 0;
unsigned long cycleStart = 0;

void signalConnectionFailure(bool log){
	wifiErrorSignalActive = true;
	if (log) {
		Serial.println("Couldn't get a wifi connection");
	}
	digitalWrite(blueLED_Xwing, HIGH); 
	digitalWrite(redLED_Bunker, HIGH); 
	digitalWrite(whiteLED_TIE, HIGH); 
	digitalWrite(whiteLED_Xwing, HIGH); 
}

// TODO:this probably needs to be extracted as soon as we add a non-wifi error status, as it will be a generic routine by then
void blinkError(ErrorLEDDisplay e) {
	if (cycleStart <= 0) {
		cycleStart = millis();
		switch (e) {
			case ErrorLEDDisplay.WiFi:
				cycleDuration = 1000; // one-second
				break;
			default:
				// programmer error, bail (new case inserted and loop not updated, initialization error, etc)
				return;
		}
	} else {
		if (millis - cycleStart > cycleDuration) { // more time elapsed than the blink window
			cycleDuration = millis();
			for (int ledToSwitchIndex = 0; ledToSwitchIndex < ledsPinsAvailable; ledToSwitchIndex++ ) {
				uint8_t ledToSwitch =  ledsPinsAvailable[ledToSwitchIndex);
				digitalWrite(ledToSwitch, 
						(digitalRead(ledToSwitch) == HIGH ? LOW : HIGH)); 
			}
		}
	}
}

void testConnection(bool log){

	// logging might not be necessary... if I ping my own already-logging server, for example.
	if (log) { 
		Serial.println("Connected to wifi");
		Serial.println("\nStarting connection...");
	}
	// if you get a connection, report back via serial:
	if (client.connect(server, 80)) {
		if (log) {   
			Serial.println("connected");
		}
		// Make a HTTP request:
		client.println("GET /is-alive HTTP/1.0");
		client.println();
	}
}
