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


TemperatureSensorWrapper::TemperatureSensorWrapper(int deviceId, ITHPSensor* sensor)
{
	this->deviceId = deviceId;
	this->sensor = sensor;
}

#ifdef ESP8266
void TemperatureSensorWrapper::prepareAndSendPacket(WiFiUDP* udp, IPAddress* broadcast)
#else
void TemperatureSensorWrapper::prepareAndSendPacket(Udp* udp, IPAddress* broadcast)
#endif
{
	ResetSensorPacketUnion(&(this->packet));
	this->packet.Packet.Values[0] = this->getTemperature();
	this->packet.Packet.Values[1] = this->getHumidity();
	this->packet.Packet.Values[2] = this->getPressure();
	this->packet.Packet.DeviceId = this->deviceId;
	this->packet.Packet.SensorType = SensorTypes::TemperatureHumidityPresure;

	Serial.println("Sending Packet");
	this->printPacket();

	udp->beginPacket(*broadcast, SENSOR_BROADCAST_PORT);
	udp->write(this->packet.Data, sizeof(this->packet.Data));
	udp->endPacket();
}

void TemperatureSensorWrapper::printPacket()
{
	int i = 0;
	Serial.print("Packet ");
	for (i = 0; i < sizeof(packet.Data); i++)
	{
		Serial.printf("%i ", packet.Data[i]);
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