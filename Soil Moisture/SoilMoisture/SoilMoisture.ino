#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "LocalDefines.h"
#include <SannelCommon.h>

// From http://iotfrog.com/en/articles/article/227

IPAddress ipBroadCast(192, 168, 1, 255);
unsigned int udpRemotePort = 8172;
unsigned int udplocalPort = 2390;
const int UDP_PACKET_SIZE = 48;
uint8 udpBuffer[UDP_PACKET_SIZE];
WiFiUDP udp;
//================================================================
// Setup hardware, serial port, and connect to wifi.
//================================================================

void setup() {
	Serial.begin(115200);
	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(SSID);

	//  Try to connect to wifi access point
	WiFi.begin(SSID, SSIDPWD);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println("Starting UDP");

	// set udp port for listen
	udp.begin(udplocalPort);
	Serial.print("Local port: ");
	Serial.println(udp.localPort());
}
//================================================================
// Function to send udp message
//================================================================
void fncUdpSend()
{
	Serial.println("Sending packet");
	std::fill_n(udpBuffer, sizeof(udpBuffer), 0);

	int q =  20110;
	TypeHelper::AddToArray(udpBuffer, q);
	Serial.printf("id - %i %i %i %i\n", udpBuffer[0], udpBuffer[1], udpBuffer[2], udpBuffer[3]);

	TypeHelper::AddToArray(udpBuffer, SensorTypes::Test, 4);

	Serial.printf("s - %i %i %i %i\n", udpBuffer[4], udpBuffer[5], udpBuffer[6], udpBuffer[7]);

	Serial.println(sizeof(double));
	double d = 324;// (double)random(1, 500);
	Serial.println(d);

	TypeHelper::AddToArray(udpBuffer, d, 8);

	Serial.printf("d - %i %i %i %i %i %i %i %i\n", udpBuffer[8], udpBuffer[9], udpBuffer[10], udpBuffer[11], udpBuffer[12], udpBuffer[13], udpBuffer[14], udpBuffer[15]);

	udp.beginPacket(ipBroadCast, udpRemotePort);
	udp.write(udpBuffer, sizeof(udpBuffer));
	udp.endPacket();
	Serial.print(millis());
	Serial.println(" packet sent");
}
//================================================================
// LOOP MAIN
//================================================================
// send udp packet each 5 secconds

void loop() {
	delay(5000);
	fncUdpSend();
}

