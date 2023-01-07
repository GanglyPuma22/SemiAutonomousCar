#include <esp_now.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include "html510.h"
#include "vive510.h"

void setup() {
  Serial.begin(115200);
  pinMode(FRONT_LEFT_MOTOR_PIN, OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(FRONT_LEFT_MOTOR_SWITCH_ONE, OUTPUT);
  pinMode(FRONT_LEFT_MOTOR_SWITCH_TWO, OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR_SWITCH_ONE, OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR_SWITCH_TWO, OUTPUT);

  pinMode(BACK_LEFT_MOTOR_PIN, OUTPUT);
  pinMode(BACK_RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(BACK_LEFT_MOTOR_SWITCH_ONE, OUTPUT);
  pinMode(BACK_LEFT_MOTOR_SWITCH_TWO, OUTPUT);
  pinMode(BACK_RIGHT_MOTOR_SWITCH_ONE, OUTPUT);
  pinMode(BACK_RIGHT_MOTOR_SWITCH_TWO, OUTPUT);
  
  //TODO missing lots of sets here
  pinMode(LEFT_SONIC_PIN, INPUT);
  pinMode(RIGHT_SONIC_PIN, INPUT);
  pinMode(BACK_SONIC_PIN, INPUT);
  pinMode(FRONT_SONIC_PIN, INPUT);
  pinMode(SONIC_TRIGGER_PIN, OUTPUT);
  pinMode(IR_PIN_1, INPUT);
  pinMode(IR_PIN_2, INPUT);

  WiFi.begin(ssid, password);
  WiFi.config( myIP,        // Device IP address
      IPAddress(192, 168, 1, 1),   // gateway (not important for 5100)
      IPAddress(255, 255, 255, 0)); // net mask 
  
  UDPServer.begin(UDPPORT);  // 2510 forgame  arbitrary UDP port# need to use same one   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);    Serial.print(".");
  }
  Serial.printf("WiFi connected to %s\n", ssid);
  Serial.print("Using static IP "); Serial.print(myIP); 
  Serial.print(" and UDP port "); Serial.println(UDPPORT);

  ledcSetup(FRONT_LEFT_MOTOR_CHANNEL, 30, 14);
  ledcSetup(FRONT_RIGHT_MOTOR_CHANNEL, 30, 14);
  ledcAttachPin(FRONT_LEFT_MOTOR_PIN, FRONT_LEFT_MOTOR_CHANNEL);
  ledcAttachPin(FRONT_RIGHT_MOTOR_PIN, FRONT_RIGHT_MOTOR_CHANNEL);

  ledcSetup(BACK_LEFT_MOTOR_CHANNEL, 30, 14);
  ledcSetup(BACK_RIGHT_MOTOR_CHANNEL, 30, 14);
  ledcAttachPin(BACK_LEFT_MOTOR_PIN, BACK_LEFT_MOTOR_CHANNEL);
  ledcAttachPin(BACK_RIGHT_MOTOR_PIN, BACK_RIGHT_MOTOR_CHANNEL);

  // ledcSetup(SERVO_CHANNEL, 60, SERVO_RESOLUTION_BITS); // channel, freq, bits
  // ledcAttachPin(SERVO_PIN, SERVO_CHANNEL);
  // ledcAnalogWrite(SERVO_CHANNEL, SERVOOFF, SERVO_RESOLUTION); 

  vive.begin();
  vive2.begin();

  h.begin();
  // h.attachHandler("/H",handleDutyCycleChange);
  // h.attachHandler("/L",handleFreqChange);
  h.attachHandler("/ ", handleRoot);
  h.attachHandler("/LB ", handleLBC);
  h.attachHandler("/LF ", handleLFC);
  h.attachHandler("/RB ", handleRBC);
  h.attachHandler("/RF ", handleRFC);
  h.attachHandler("/LS ", handleLSC);
  h.attachHandler("/RS ", handleRSC);
  h.attachHandler("/LEFT ", handleLeft);
  h.attachHandler("/RIGHT ", handleRight);
  h.attachHandler("/SS ", handleSS);
  h.attachHandler("/REST ", handleStateR);
  h.attachHandler("/TOWER ", handleStateT);
  h.attachHandler("/WALL ", handleStateW);
  h.attachHandler("/POLICE ", handleStateP);

  esp_now_init();      
  esp_now_add_peer(&staffcomm); 
  // h.attachHandler("/H?val=",handleLeftChange);
  // h.attachHandler("/L?val=",handleRightChange);
}

void loop() {
  if (vive.status() == VIVE_RECEIVING) {
    vx1a[i%20] = vive.xCoord();
    vy1a[i%20] = vive.yCoord();
    //Serial.printf("X %d Y %d\n", vive.xCoord(), vive.yCoord());
  } else {
    vive.sync(15);
  }

  if (vive2.status() == VIVE_RECEIVING) {
    vx2a[i%20] = vive2.xCoord();
    vy2a[i%20] = vive2.yCoord();
    //Serial.printf("eriojerijoeriuoiuoeriuo X %d Y %d\n", vive2.xCoord(), vive2.yCoord());
  } else {
    vive2.sync(15);
  }

  vx1 = naiveMedian(vx1a);
  vy1 = naiveMedian(vy1a);
  vx2 = naiveMedian(vx2a);
  vy2 = naiveMedian(vy2a);  

  heading = atan2(vy1-vy2, vx1-vx2) * 360 / (2*PI);
  //Serial.println(heading);

  //TODO SEND PING EVERY TIME WE RECIEVE A PACKET pingstaff();

  h.serve();

  // handleLB();
  // delay(10000);
  // handleLF();
  // handleRF();
  // // delay(10000);
  // // handleLS();
  // // delay(10000);
  // // handleRB();
  // // delay(10000);
  // delay(10000);
  // handleRS();
  // delay(10000);

  //handleRight();
  //delay(250);
  //readSonics();

  // digitalWrite(FRONT_LEFT_MOTOR_SWITCH_ONE, HIGH);
  // digitalWrite(FRONT_LEFT_MOTOR_SWITCH_TWO, LOW);
  // ledcWrite(FRONT_LEFT_MOTOR_CHANNEL, 16384);
  // digitalWrite(FRONT_RIGHT_MOTOR_SWITCH_ONE, HIGH);
  // digitalWrite(FRONT_RIGHT_MOTOR_SWITCH_TWO, LOW);
  // ledcWrite(FRONT_RIGHT_MOTOR_CHANNEL, 16384);
  //handleSS();
  //delay(500);

  //secondly
  if(i%10){
    sendXY();
  }

  switch(state){
    case POLICE:
      handlePolice();
      break;
    case WALL:
       handleWall();
      break;
    case TOWER:
      handleTower();
      break;
    case REST:
      handleStop();
      break;
  }

  delay(100);

  i++;
}