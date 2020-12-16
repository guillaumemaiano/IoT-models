#include "Arduino.h"
#include "ESP8266WiFi.h"

// WiFi Multi allows multiple access points. We probably don't need that yet.
//#include <ESP8266WiFiMulti.h>

// HTTP CLient allows (obviously) HTTP clients to be built.
#include "ESP8266HTTPClient.h"

// will be replaced before build by Makefile
#define SERVER_NAME "SERVER-NAME"
#define WIFI_SSID "WiFi-NAME"
#define WIFI_PASS "WiFi-PASSWORD"

void setupWiFi(bool log);

#ifdef __cplusplus
extern "C" {
#endif
	void signalConnectionFailure(bool log);
	void testConnection(bool log);
#ifdef __cplusplus
} 
#endif
