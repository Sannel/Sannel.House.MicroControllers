/* Copyright 2017 Sannel Software, L.L.C.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.*/
#include "TemperatureSensorWrapper.h"
#include <SannelDefines.h>
#include <Arduino.h>


TemperatureSensorWrapper::TemperatureSensorWrapper(int deviceId, ITHPSensor& sensor)
{
	this->deviceId = deviceId;
	this->sensor = &sensor;
}

#ifdef ESP8266
void TemperatureSensorWrapper::prepareAndSendPacket(WiFiClient &client, IPAddress &address)
#else
void TemperatureSensorWrapper::prepareAndSendPacket(UDP* udp, IPAddress* broadcast)
#endif
{
	ResetSensorPacket(packet);
	packet.Values[0] = getTemperature();
	packet.Values[1] = getHumidity();
	packet.Values[2] = getPressure();
	packet.DeviceId = deviceId;
	packet.MillsOffset = 0;
	packet.SensorType = SensorTypes::TemperatureHumidityPresure;

	Serial.println("Sending Packet");
	this->printPacket();

	if (client.connect(address, SENSOR_BROADCAST_PORT)) 
	{
		client.write(1);
		writeValue(client, packet.DeviceId);
		writeValue(client, packet.SensorType);
		writeValue(client, packet.MillsOffset);

		for (unsigned char i=0; i < 9; i++)
		{
			writeValue(client, packet.Values[i]);
		}
		client.flush();
		client.stop();
	}
}

void TemperatureSensorWrapper::printPacket()
{
	Serial.print("Packet ");
	printValue(Serial, packet.DeviceId);
	printValue(Serial, packet.SensorType);
	printValue(Serial, packet.MillsOffset);
	for (unsigned char i=0; i < 9; i++) 
	{
		printValue(Serial, packet.Values[i]);
	}
	Serial.println();
	Serial.println();
}

void TemperatureSensorWrapper::initialize()
{
	sensor->initialize();
}

void TemperatureSensorWrapper::begin()
{
	sensor->begin();
}

double TemperatureSensorWrapper::getTemperature()
{
	return sensor->getTemperature();
}

double TemperatureSensorWrapper::getHumidity()
{
	return sensor->getHumidity();
}

double TemperatureSensorWrapper::getPressure()
{
	return sensor->getPresure();
}