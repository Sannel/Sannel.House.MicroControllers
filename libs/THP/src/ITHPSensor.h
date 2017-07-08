#pragma once

class ITHPSensor
{
public:
	virtual void initialize() = 0;
	virtual void begin() = 0;
	virtual double getTemperature() = 0;
	virtual double getHumidity() = 0;
	virtual double getPresure() = 0;
};