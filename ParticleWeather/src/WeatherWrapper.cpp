#include "WeatherWrapper.h"

WeatherWrapper::WeatherWrapper(){

}

void WeatherWrapper::initialize(){

}

void WeatherWrapper::begin(){
    //Initialize the I2C sensors and ping them
    weather.begin();

    /*You can only receive accurate barometric readings or accurate altitude
    readings at a given time, not both at the same time. The following two lines
    tell the sensor what mode to use. You could easily write a function that
    takes a reading in one made and then switches to the other mode to grab that
    reading, resulting in data that contains both accurate altitude and barometric
    readings. For this example, we will only be using the barometer mode. Be sure
    to only uncomment one line at a time. */
    weather.setModeBarometer();//Set to Barometer Mode
    //sensor.setModeAltimeter();//Set to altimeter Mode

    //These are additional MPL3115A2 functions that MUST be called for the sensor to work.
    weather.setOversampleRate(7); // Set Oversample rate
    //Call with a rate from 0 to 7. See page 33 for table of ratios.
    //Sets the over sample rate. Datasheet calls for 128 but you can set it
    //from 1 to 128 samples. The higher the oversample rate the greater
    //the time between data samples.


    weather.enableEventFlags(); //Necessary register calls to enble temp, baro and alt
}

double WeatherWrapper::getTemperature(){
    return (double)weather.getTemp();
}

double WeatherWrapper::getHumidity(){
    return (double)weather.getRH();
}

double WeatherWrapper::getPresure(){
    return (double)weather.readPressure();
}
