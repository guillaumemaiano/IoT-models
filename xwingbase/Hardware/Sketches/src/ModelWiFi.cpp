#include "ModelWifi.h"
#include "Lights.h" // Needed so I can blink the LED

unsigned long cycleDuration = 0;
unsigned long cycleStart = 0;

bool wifiErrorSignalActive = false;

// Hit an Amazon server for a 40X. They can afford it.
IPAddress server = IPAddress(205,251,242,103);
/*
   Little note: sscanf pulls some libs, but esp has place, so if needed this is an interesting option.
   const char * str = "192.168.1.2";
   uint8_t ip[4];
   sscanf(str, "%u.%u.%u.%u", &ip[0], &ip[1], &ip[2], &ip[3]);
   */
char serverName[] = SERVER_NAME;

WiFiClient wifiClient;

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;

void signalConnectionFailure(bool log){
	wifiErrorSignalActive = true;
	if (log) {
		Serial.println("Couldn't get a wifi connection");
	}
	for (int ledToSwitchIndex = 0; ledToSwitchIndex < ledsPinsAvailable; ledToSwitchIndex++ ) {
		uint8_t ledToSwitch =  ledPins[ledToSwitchIndex];
		digitalWrite(ledToSwitch, HIGH);
	}
}

// TODO:this probably needs to be extracted as soon as we add a non-wifi error status, as it will be a generic routine by then
void blinkError(ErrorLEDDisplay e) {
	if (cycleStart <= 0) {
		cycleStart = millis();
		switch (e) {
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
				uint8_t ledToSwitch =  ledPins[ledToSwitchIndex];
				digitalWrite(ledToSwitch,
						(digitalRead(ledToSwitch) == HIGH ? LOW : HIGH));
			}
		}
	}
}

void setupWiFi(bool log) {
	WiFi.mode(WIFI_STA);
	int statusWiFiConnection = WiFi.begin(ssid, pass);
	if (log) {
		Serial.println(ssid);
		Serial.println(pass);
	}
	int retries = 10;
	int retry_delay = 500;
	for ( int attempt = 0; attempt < retries; attempt++) {
		if (WiFi.status() == WL_CONNECTED ) {
			statusWiFiConnection = WiFi.status();
			break;
		}
		delay(retry_delay);
	}
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
	if (wifiClient == -1) {
		if (log) {
			Serial.println("WiFi client not initialized.");
		}
		// bail!
		return;
	}
	// if server name not defined, use the IP fallback
	bool connectAttempt;
	if (serverName != 0) {
		connectAttempt = wifiClient.connect(serverName, 80);
	} else {
		connectAttempt = wifiClient.connect(server, 80);
	}
	// if you get a connection, report back via serial if available:
	if (connectAttempt) {
		if (log) {
			Serial.println("connected");
		}
		// Make a HTTP request:
		wifiClient.println("GET /is-alive HTTP/1.0");
		wifiClient.println();
	}
}
