#pragma once

// BEGIN Configuration
#define DEBUG // undefine this to use production settings
// END Configuration

#ifdef ESP8266
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#endif

#include "LocalDefines.h"
#include <SannelDefines.h>
#include <TemperatureSensorWrapper.h>