#include <esp_now.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include "html510.h"
#include "vive510.h"

void handleUDPServer() {
   const int UDP_PACKET_SIZE = 14; // can be up to 65535          
   uint8_t packetBuffer[UDP_PACKET_SIZE];

   int cb = UDPServer.parsePacket(); // if there is no message cb=0
   if (cb) {
      int x,y;
      packetBuffer[13]=0; // null terminate string

      UDPServer.read(packetBuffer, UDP_PACKET_SIZE);

      if(*packetBuffer != '0' || *(packetBuffer+1) != '0'){
        Serial.println("exiting in my condition");
        return;
      }

      px = atoi((char *)packetBuffer+3); // ##,####,#### 2nd indexed char
      py = atoi((char *)packetBuffer+8); // ##,####,#### 7th indexed char

      Serial.print("Police Car Coords ");
      Serial.println(px);
      Serial.println(py);
   } else{
     Serial.println("no packets receiverd");
   }
}