//#if defined SparkFun_Photon_Weather_Shield_Library_h
#ifndef _WEATHERWRAPPER_
#define _WEATHERWRAPPER_

#include "ITHPSensor.h"
#include "Arduino.h"

class Weather {
public:
	virtual void  begin() = 0;

	// Si7021 & HTU21D Public Functions
	virtual float getRH() = 0;
	virtual float readTemp() = 0;
	virtual float getTemp() = 0;
	virtual float readTempF() = 0;
	virtual float getTempF() = 0;
	virtual void  heaterOn() = 0;
	virtual void  heaterOff() = 0;
	virtual void  changeResolution(uint8_t i) = 0;
	virtual void  reset() = 0;
	virtual uint8_t  checkID() = 0;

	//MPL3115A2 Public Functions
	virtual float readAltitude() = 0; // Returns float with meters above sealevel. Ex: 1638.94
	virtual float readAltitudeFt() = 0; // Returns float with feet above sealevel. Ex: 5376.68
	virtual float readPressure() = 0; // Returns float with barometric pressure in Pa. Ex: 83351.25
	virtual float readBaroTemp() = 0; // Returns float with current temperature in Celsius. Ex: 23.37
	virtual float readBaroTempF() = 0; // Returns float with current temperature in Fahrenheit. Ex: 73.96
	virtual void setModeBarometer() = 0; // Puts the sensor into Pascal measurement mode.
	virtual void setModeAltimeter() = 0; // Puts the sensor into altimetery mode.
	virtual void setModeStandby() = 0; // Puts the sensor into Standby mode. Required when changing CTRL1 register.
	virtual void setModeActive() = 0; // Start taking measurements!
	virtual void setOversampleRate(byte) = 0; // Sets the # of samples from 1 to 128. See datasheet.
	virtual void enableEventFlags() = 0; // Sets the fundamental event flags. Required during setup.
};

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
//#endif