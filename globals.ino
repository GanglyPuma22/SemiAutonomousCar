#include <esp_now.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include "html510.h"
#include "vive510.h"
//#include "NewPing.h"

states state = REST;
wallStates wallState = FORWARD;

HTML510Server h(80);
WiFiUDP UDPServer;
IPAddress myIP(192, 168, 1, 152);
// const char* ssid = "Mateo's iPhone";
// const char* password = "mathesonisbitch";
const char* ssid     = "TP-Link_05AF";
const char* password = "47543454";
//const char* ssid     = "TP-Link_E0C8";
//const char* password = "52665134";
//const char* ssid     = "TP-Link_FD24"; 
//const char* password = "65512111";

Vive510 vive(VIVE_PIN);
Vive510 vive2(VIVE_PIN_2);

//coords of vehicle (vive 1 is front vive 2 is back)
int vx1 = 0;
int vx2 = 0;
int vy1 = 0;
int vy2 = 0;
int vx1a[20];
int vy1a[20];
int vx2a[20];
int vy2a[20];

int naiveMedian(int* x){
  for(int* curr = x; curr < x + 20; curr++){
    int lt = 0;

    for(int* iter = x; iter < x + 20; iter++){
      if(*iter <= *curr){
        lt++;
      }

      if(lt >= 10){
        return *curr;
      }
    }
  }

  return -1;
}

double heading = 0;

//police x and y
int px = 0;
int py = 0;

long leftSonicDist = 0;
long rightSonicDist = 0;
long frontSonicDist = 0;
long backSonicDist = 0;

//NewPing frontSonic(SONIC_TRIGGER_PIN, FRONT_SONIC_PIN, MAX_SONIC_DISTANCE);

//TODO CHECK HOW MANY PACKETS ARE BEING SENT
esp_now_peer_info_t staffcomm = {
  .peer_addr = {0x84,0xF7,0x03,0xA9,0x04,0x78}, 
  .channel = 1,             // channel can be 1 to 14, channel 0 means current channel.
  .encrypt = false,
};

//tick counter
int i = 0;

//servo scan vars
int scanR[ARRAYMAX];
int scanA[ARRAYMAX];
int scanoffset = SCANSIZE; // start at SCANSIZE so we don't endup negative mod