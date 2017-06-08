#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "LocalDefines.h"

// From http://iotfrog.com/en/articles/article/227

const char* ssid     = SSID;
const char* password = SSIDPWD;
IPAddress ipBroadCast(192, 168, 2, 255);
unsigned int udpRemotePort=2391;
unsigned int udplocalPort=2390;
const int UDP_PACKET_SIZE = 48;
char udpBuffer[ UDP_PACKET_SIZE];
WiFiUDP udp;
//================================================================
// Setup hardware, serial port, and connect to wifi.
//================================================================
 
void setup() {
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  //  Try to connect to wifi access point
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
 
  // set udp port for listen
  udp.begin(udplocalPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}
//================================================================
// Function to send udp message
//================================================================
void fncUdpSend()
{
  strcpy(udpBuffer, "hello testing message"); 
  udp.beginPacket(ipBroadCast, udpRemotePort);
  udp.write(udpBuffer, sizeof(udpBuffer));
  udp.endPacket();
  }
//================================================================
// LOOP MAIN
//================================================================
// send udp packet each 5 secconds
 
void loop() {
    delay (5000);
   fncUdpSend();
}

