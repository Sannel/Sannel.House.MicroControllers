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
#include <Stream.h>
#ifdef ESP8266
#include <WiFiClient.h>
#else
#include "Particle.h"
#endif

using namespace Sannel::House::Sensor;

class TemperatureSensorWrapper
{
public:
	TemperatureSensorWrapper(int deviceId, ITHPSensor& sensor);

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
	void prepareAndSendPacket(WiFiClient &udp, IPAddress &broadcast);
#else
	void prepareAndSendPacket(UDP* udp, IPAddress *broadcast);
#endif


private:
	SensorPacket packet;
	int deviceId;
	ITHPSensor* sensor;

	template<typename T>
	void writeValue(Stream &stream, T &value)
	{
		int size = sizeof(T);
		unsigned char* ptr = (unsigned char*)&value;
		for (int i = 0; i < size; i++)
		{
			stream.write(ptr[i]);
		}
	};
	template<typename T>
	void printValue(Print &print, T &value) 
	{
		print.printf("value = %i", value);
		print.println();
		int size = sizeof(T);
		unsigned char* ptr = (unsigned char*)&value;
		for (int i = 0; i < size; i++)
		{
			print.printf("%i ", ptr[i]);
		}
		print.println();
	};
	void printPacket();
};

#endif