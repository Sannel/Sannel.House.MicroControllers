/*
 * Project ParticleWeather
 * Description:
 * Author:
 * Date:
 */
#define DEBUG
#include "Particle.h"
#include "SannelDefines.h"
#include "LocalDefines.h"
#include "SensorStore.h"
//#include "WeatherWrapper.h"
//#include "TemperatureSensorWrapper.h"


using namespace Sannel::House::Sensor;

TCPClient client;
SensorStore store(1);
IPAddress broadcast(BROADCASTIP_FIRST, BROADCASTIP_SECOND, BROADCASTIP_THIRD, BROADCASTIP_FORTH);


// setup() runs once, when the device is first turned on.
void setup() {
  WiFi.on();
  Particle.publish("started", "started");
	// Put initialization like pinMode and begin functions here.
  byte mac[6];
  WiFi.macAddress(mac);
  store.SetMacAddress(mac);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
}
