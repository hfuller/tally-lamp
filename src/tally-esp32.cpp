#include <Arduino.h>

#include "WiFi.h"

void setup()
{
	Serial.begin(115200);
	Serial.println("setup()");

	Serial.print("Setting up Wi-Fi");
	WiFi.mode(WIFI_STA);
	//WiFi.begin(cWifiSsid, cWifiPsk);
	WiFi.begin();
	while ( WiFi.status() != WL_CONNECTED ) {
		Serial.print(".");
		delay(250);
	}
	Serial.print(" ");
	Serial.println(WiFi.localIP());

	Serial.println("setup() complete");
}

void loop() {
	WiFiClient client;
	const int iPort = 5763;
	if ( ! client.connect("192.168.1.178", iPort) ) {
		Serial.println("TCP connection failed");
		return;
	}

	client.print("Hello");

	while ( client.connected() ) {
		if ( client.available() ) {
			while ( client.available() ) {
				String sLine = client.readStringUntil('\n');
				Serial.println(sLine);
			}
		} else {
			delay(75);
		}
	}

	delay(1000);

}
