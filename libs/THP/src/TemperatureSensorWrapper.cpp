#include "TemperatureSensorWrapper.h"
#include <SannelDefines.h>


TemperatureSensorWrapper::TemperatureSensorWrapper(int deviceId, ITHPSensor* sensor)
{
	this->deviceId = deviceId;
	this->sensor = sensor;
}

void TemperatureSensorWrapper::prepareAndSendPacket(WiFiUDP* udp, IPAddress* broadcast)
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