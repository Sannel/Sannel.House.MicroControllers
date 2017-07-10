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
#ifndef _TEMPERATURESENSORWRAPPER_
#define _TEMPERATURESENSORWRAPPER_

#include "ITHPSensor.h"
#include <SensorPacket.h>
#ifdef ESP8266
#include <WiFiUdp.h>
#else
#include "Particle.h"
#endif

using namespace Sannel::House::Sensor;

class TemperatureSensorWrapper
{
public:
	TemperatureSensorWrapper(int deviceId, ITHPSensor* sensor);

	/// <summary>
	/// Initializes this instance using settings defined for the sensor
	/// </summary>
	void initialize();
	
	/// <summary>
	/// Begins this instance.
	/// </summary>
	void begin();

	/// <summary>
	/// Gets the pressure.
	/// </summary>
	/// <returns></returns>
	double getPressure();
	/// <summary>
	/// Gets the humidity.
	/// </summary>
	/// <returns></returns>
	double getHumidity();
	/// <summary>
	/// Gets the temperature in Celsius
	/// </summary>
	/// <returns></returns>
	double getTemperature();

#ifdef ESP8266
	void prepareAndSendPacket(WiFiUDP* udp, IPAddress *broadcast);
#else
	void prepareAndSendPacket(UDP* udp, IPAddress *broadcast);
#endif


private:
	SensorPacketUnion packet;
	int deviceId;
	ITHPSensor* sensor;

	void printPacket();
};

#endif