/*
 Name:		TemperatureHumidityPressure.ino
 Created:	7/7/2017 12:57:15 PM
 Author:	holts
*/

// the setup function runs once when you press reset or power the board
#include "Defines.h"

#include <BME280Wrapper.h>

WiFiUDP udp;
BME280Wraper temp(I2C_MODE, 0x76);
TemperatureSensorWrapper sensor(10, &temp);
IPAddress broadcast(BROADCASTIP_FIRST, BROADCASTIP_SECOND, BROADCASTIP_THIRD, BROADCASTIP_FORTH);

void setup() 
{
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.begin(115200);
	delay(250);
	Serial.println();
	Serial.println();
#ifdef DEBUG
	Serial.println("Debug");
#endif
	Serial.print("Connecting to ");
	Serial.println(SSID);
	WiFi.begin(SSID, SSIDPWD);
	while (WiFi.status() != WL_CONNECTED) 
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(250);
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(150);
		Serial.print(".");
	}

	digitalWrite(LED_BUILTIN, LOW);
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());


	Serial.print("Broadcast Port ");
	Serial.println(SENSOR_BROADCAST_PORT);

	sensor.initialize();
	sensor.begin();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	sensor.prepareAndSendPacket(&udp, &broadcast);
	delay(900000);
	//ESP.deepSleep(10000000);
}
