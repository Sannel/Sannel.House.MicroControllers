#if defined SparkFun_Photon_Weather_Shield_Library_h
#ifndef _WEATHERWRAPPER_
#define _WEATHERWRAPPER_

#include "ITHPSensor.h"


class WeatherWrapper : public ITHPSensor
{
public:
	WeatherWrapper(Weather &weather);

	// Inherited via ITHPSensor
	virtual void initialize() override;
	virtual void begin() override;
	virtual double getTemperature() override;
	virtual double getHumidity() override;
	virtual double getPresure() override;

private:
	Weather* weather;
};

#endif
#endif