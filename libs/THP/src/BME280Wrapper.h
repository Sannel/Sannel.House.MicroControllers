#pragma once

#include "ITHPSensor.h"
#include <SparkFunBME280.h>

class BME280Wraper : public ITHPSensor
{
public:
	/// address can be 0x76 or 0x77
	BME280Wraper(short mode, int addressOrPin);

	// Inherited via ITHPSensor
	virtual void initialize() override;
	virtual void begin() override;
	virtual double getTemperature() override;
	virtual double getHumidity() override;
	virtual double getPresure() override;
	SensorSettings getSettings();

private:
	BME280 sensor;
};