#ifndef _WEATHERWRAPPER_
#define _WEATHERWRAPPER_

//#include "ITHPSensor.h"
#include "SparkFun_Photon_Weather_Shield_Library.h"

class WeatherWrapper{
public:
    WeatherWrapper();
	void initialize();
  void begin();
	 double getTemperature() ;
	 double getHumidity() ;
	 double getPresure() ;

private:
    Weather weather;
};

#endif
