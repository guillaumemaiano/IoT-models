#include "ModelWifi.h"
#include "Lights.h" // Needed so I can blink the LED

unsigned long cycleDuration = 0;
unsigned long cycleStart = 0;

bool wifiErrorSignalActive = false;

void signalConnectionFailure(bool log){
	wifiErrorSignalActive = true;
	if (log) {
		Serial.println("Couldn't get a wifi connection");
	}
	for (int ledToSwitchIndex = 0; ledToSwitchIndex < ledsPinsAvailable; ledToSwitchIndex++ ) {
		uint8_t ledToSwitch =  ledPins[ledToSwitchIndex);
		digitalWrite(ledToSwitch, 
				LOW); 
	}
}

// TODO:this probably needs to be extracted as soon as we add a non-wifi error status, as it will be a generic routine by then
void blinkError(ErrorLEDDisplay e) {
	if (cycleStart <= 0) {
		cycleStart = millis();
		switch (e) {
			// ErrorLEDDisplay.WiFi:
			case LEDWiFiError:
				cycleDuration = 1000; // one-second
				break;
			default:
				// programmer error, bail (new case inserted and loop not updated, initialization error, etc)
				return;
		}
	} else {
		if (millis() - cycleStart > cycleDuration) { // more time elapsed than the blink window
			cycleDuration = millis();
			for (int ledToSwitchIndex = 0; ledToSwitchIndex < ledsPinsAvailable; ledToSwitchIndex++ ) {
				uint8_t ledToSwitch =  ledPins[ledToSwitchIndex);
				digitalWrite(ledToSwitch, 
						(digitalRead(ledToSwitch) == HIGH ? LOW : HIGH)); 
			}
		}
	}
}

void setupWiFi(bool log) {
	int statusWiFiConnection = WiFi.begin(ssid, pass);
	if (statusWiFiConnection != WL_CONNECTED) {
		//  turn the routines off to make the signal be 100% a warning sign
		//  Maybe add a pushbutton to bypass this later - would cycle to automatic "all routines on" mode
		deactivateRoutines();
		signalConnectionFailure(log);
	} else {
		testConnection(log);
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
