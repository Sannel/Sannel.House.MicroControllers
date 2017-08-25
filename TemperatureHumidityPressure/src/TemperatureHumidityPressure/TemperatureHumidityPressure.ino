/*
 Name:		TemperatureHumidityPressure.ino
 Created:	7/7/2017 12:57:15 PM
 Author:	holts
*/

// the setup function runs once when you press reset or power the board
#include "Defines.h"

#include <BME280Wrapper.h>
#include <SensorStore.h>
#include <ITHPSensor.h>

using namespace Sannel::House::Sensor;

WiFiClient client;
SensorStore store(1);
BME280Wraper wrapper(I2C_MODE, 0x76);
ITHPSensor *temp = &wrapper;
IPAddress broadcast(BROADCASTIP_FIRST, BROADCASTIP_SECOND, BROADCASTIP_THIRD, BROADCASTIP_FORTH);
SensorPacket packet;

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

	uint8_t mac[6];
	WiFi.macAddress(mac);

	store.SetMacAddress(mac);


	Serial.print("Broadcast Port ");
	Serial.println(SENSOR_BROADCAST_PORT);

	uint8_t macAddress[6];

	Serial.println(WiFi.macAddress());

	WiFi.macAddress(macAddress);

	temp->initialize();
	temp->begin();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	ResetSensorPacket(packet);
	packet.SensorType = SensorTypes::TemperatureHumidityPressure;
	packet.Offset = 0;
	packet.Values[0] = temp->getTemperature();
	packet.Values[1] = temp->getHumidity();
	packet.Values[2] = temp->getPresure();

	if (store.AddReading(packet))
	{
		Serial.println("Store full sending packets");
		if (client.connect(broadcast, SENSOR_BROADCAST_PORT))
		{
			Serial.println("Connected writing packets");
			store.WritePackets(client);
			store.Reset();
			client.flush();
			client.stop();
			Serial.println("packets written");
		}
		else 
		{
			Serial.println("Unable to connect to remote computer");
			Serial.println(client.status());
		}
	}

	delay(900000);
	//ESP.deepSleep(10000000);
}
