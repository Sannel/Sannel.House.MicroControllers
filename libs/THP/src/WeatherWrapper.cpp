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