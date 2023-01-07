#include <esp_now.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include "html510.h"
#include "vive510.h"

void pingstaff() {
  uint8_t teamNum = 5;
  esp_now_send(staffcomm.peer_addr, &teamNum, 1);     
}

void sendXY() {
  char msg[13];
  sprintf(msg,"%2d:%4d,%4d",TEAMNUM, vx1, vx2);
  esp_now_send(staffcomm.peer_addr, (uint8_t *) msg, 13);
}