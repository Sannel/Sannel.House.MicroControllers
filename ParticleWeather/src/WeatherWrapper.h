#ifndef _WEATHERWRAPPER_
#define _WEATHERWRAPPER_

#include "ITHPSensor.h"
#include "SparkFun_Photon_Weather_Shield_Library.h"

class WeatherWrapper : public ITHPSensor{
public:
    WeatherWrapper();
	virtual void initialize() override;
	virtual void begin() override;
	virtual double getTemperature() override;
	virtual double getHumidity() override;
	virtual double getPresure() override;

private:
    Weather weather;
};

#endif
