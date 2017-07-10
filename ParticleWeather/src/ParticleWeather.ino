/*
 * Project ParticleWeather
 * Description:
 * Author:
 * Date:
 */
#define DEBUG
#include "SparkFun_Photon_Weather_Shield_Library.h"
#include "SannelDefines.h"

// setup() runs once, when the device is first turned on.
void setup() {
	// Put initialization like pinMode and begin functions here.
    Particle.publish("test", SENSOR_BROADCAST_PORT);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
	// The core of your code will likely live here.

}
