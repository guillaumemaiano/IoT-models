#include "Arduino.h"
#include "ESP8266WiFi.h"

// WiFi Multi allows multiple access points. We probably don't need that yet.
//#include <ESP8266WiFiMulti.h>

// HTTP CLient allows (obviously) HTTP clients to be built. We might need that later.
//#include "ESP8266HTTPClient.h"

// will be replaced before build by Makefile
#define SERVER_NAME "SERVER-NAME"
#define SERVER_IP "SERVER_IP"
#define WIFI_SSID "WiFi-NAME"
#define WIFI_PASS "WiFi-PASSWORD"

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;

int statusWifiConnection;

WiFiClient wifiClient;

#ifdef __cplusplus
extern "C" {
#endif
	void signalConnectionFailure(bool log);
	void testConnection();
#ifdef __cplusplus
} 
#endif
