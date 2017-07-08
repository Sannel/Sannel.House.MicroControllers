#include "BME280Wrapper.h"

BME280Wraper::BME280Wraper(short mode, int addressOrPin) 
{
	//commInterface can be I2C_MODE or SPI_MODE
	if (mode == I2C_MODE)
	{
		//specify chipSelectPin using arduino pin names
		//specify I2C address.  Can be 0x77(default) or 0x76
		sensor.settings.commInterface = I2C_MODE;
		sensor.settings.I2CAddress = addressOrPin;
	}
	else if (mode == SPI_MODE)
	{
		//For I2C, enable the following and disable the SPI section
		//For SPI enable the following and dissable the I2C section
		sensor.settings.commInterface = SPI_MODE;
		sensor.settings.chipSelectPin = addressOrPin;
	}
}

SensorSettings BME280Wraper::getSettings()
{
	return sensor.settings;
}

void BME280Wraper::initialize()
{
	//***Operation settings*****************************//

	//renMode can be:
	//  0, Sleep mode
	//  1 or 2, Forced mode
	//  3, Normal mode
	sensor.settings.runMode = 3;
	//tStandby can be:
	//  0, 0.5ms
	//  1, 62.5ms
	//  2, 125ms
	//  3, 250ms
	//  4, 500ms
	//  5, 1000ms
	//  6, 10ms
	//  7, 20ms
	sensor.settings.tStandby = 0;
	//filter can be off or number of FIR coefficients to use:
	//  0, filter off
	//  1, coefficients = 2
	//  2, coefficients = 4
	//  3, coefficients = 8
	//  4, coefficients = 16
	sensor.settings.filter = 3;
	//tempOverSample can be:
	//  0, skipped
	//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
	sensor.settings.tempOverSample = 1;
	//pressOverSample can be:
	//  0, skipped
	//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
	sensor.settings.pressOverSample = 1;
	//humidOverSample can be:
	//  0, skipped
	//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
	sensor.settings.humidOverSample = 1;
}

void BME280Wraper::begin()
{
	sensor.begin();
}

double BME280Wraper::getTemperature()
{
	return sensor.readTempC();
}

double BME280Wraper::getHumidity()
{
	return sensor.readFloatHumidity();
}

double BME280Wraper::getPresure()
{
	return sensor.readFloatPressure();
}
