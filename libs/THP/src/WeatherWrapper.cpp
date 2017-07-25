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
#ifdef SUPPORT_PARTICLE_SPARKFUN_WEATHER
#include "WeatherWrapper.h"

WeatherWrapper::WeatherWrapper(Weather &weather)
{
	this->weather = &weather;
}

void WeatherWrapper::initialize()
{

}

void WeatherWrapper::begin()
{
	this->weather->begin();

	this->weather->setModeBarometer();

	this->weather->setOversampleRate(7);

	this->weather->enableEventFlags();
}

double WeatherWrapper::getHumidity()
{
	return (double)this->weather->getRH();
}

double WeatherWrapper::getTemperature()
{
	return (double)this->weather->getTemp();
}

double WeatherWrapper::getPresure()
{
	return (double)this->weather->readPressure();
}

#endif