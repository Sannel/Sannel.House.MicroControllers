/*
 * Project ParticleWeather
 * Description:
 * Author:
 * Date:
 */
#define DEBUG
#include "SannelDefines.h"
#include "LocalDefines.h"
#include "WeatherWrapper.h"
#include "TemperatureSensorWrapper.h"
#include "Particle.h"

TCPClient client;
WeatherWrapper wrapper;
TemperatureSensorWrapper sensor(11, wrapper);
IPAddress broadcast(BROADCASTIP_FIRST, BROADCASTIP_SECOND, BROADCASTIP_THIRD, BROADCASTIP_FORTH);


// setup() runs once, when the device is first turned on.
void setup() {
    Particle.publish("started", "started");
	// Put initialization like pinMode and begin functions here.
    sensor.initialize();
    sensor.begin();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
	// The core of your code will likely live here.
    sensor.prepareAndSendPacket(client, broadcast);
	delay(900000);
}
