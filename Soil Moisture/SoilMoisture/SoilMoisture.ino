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
#include "Defines.h"

using namespace Sannel::House::Sensor;

// From http://iotfrog.com/en/articles/article/227

IPAddress ipBroadCast(192, 168, 1, 255);
unsigned int udpRemotePort = 8172;
unsigned int udplocalPort = 2390;
SensorPacketUnion packet;
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
void printPacket()
{
	int i = 0;
	for (i = 0; i < 16; i++) 
	{
		Serial.printf("%i ", packet.Data[i]);
	}
	Serial.println();
}
//================================================================
// Function to send udp message
//================================================================
void fncUdpSend()
{
	Serial.println("Sending packet");
	printPacket();

	ResetSensorPacketUnion(&packet);
	printPacket();

	packet.Packet.DeviceId = random(1, 70000);
	packet.Packet.SensorType = SensorTypes::Test;
	packet.Packet.Values[0] = (double)random(2, 200) + ((double)random(400, 700) / 1000);
	Serial.println(packet.Packet.Values[0]);


	printPacket();

	udp.beginPacket(ipBroadCast, udpRemotePort);
	udp.write(packet.Data, sizeof(packet));
	udp.endPacket();
	Serial.print(millis());
	Serial.println(" packet sent");
}
//================================================================
// LOOP MAIN
//================================================================
// send udp packet each 5 secconds

void loop() {
	fncUdpSend();
	delay(5000);
}

