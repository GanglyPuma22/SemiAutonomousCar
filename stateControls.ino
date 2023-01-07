void handleWall(){

  int target;

  switch(wallState){
    case RIGHT:
      target = 90;
      break;
    case FORWARD:
      target = 180 * (heading > 0 ? 1 : -1);
      break;
    case BACKWARD:
      target = 0;
      break;
    case LEFT:
      target = -90;
      break;
  }

  readSonics();

  if(leftSonicDist < WALL_DIST_TOLERANCE){
    handleLFH();
    handleRS();
    return;
  }

  if(leftSonicDist > MAX_WALL_DIST_TOLERANCE){
    handleRF();
    handleLFH();
    return;
  }

  if(frontSonicDist < MAX_WALL_DIST_TOLERANCE/2 + 3){
    while(frontSonicDist < 3 * MAX_WALL_DIST_TOLERANCE){
      handleLF();
      handleRB();
      readSonics();
      delay(50);
    }
    delay(500);
    handleLF();
    handleRF();
    delay(500);
  }

  handleLF();
  handleRF();

}

int sonicState = 0;

void readSonics(){
  digitalWrite(SONIC_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SONIC_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONIC_TRIGGER_PIN, LOW);

  if(sonicState % 2 == 0) leftSonicDist = (float)pulseIn(LEFT_SONIC_PIN, HIGH) * MACH / 2;
  if(sonicState % 2 == 1)  frontSonicDist = (float)pulseIn(FRONT_SONIC_PIN, HIGH) * MACH / 2;
  Serial.print(frontSonicDist);
  sonicState++;
}

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {            
  uint32_t duty =  SERVO_RESOLUTION * min(value, valueMax) / valueMax;   
  ledcWrite(channel, duty);  // write duty to LEDC 
}

//Seperate pins based on side if necessary
int irDetected() {
  //Read IR Pins
  //return digitalRead(IR_PIN_1) || digitalRead(IR_PIN_2);
  return digitalRead(IR_PIN_1);
}

int circleMode = 0;
int oldValue = 0;
uint32_t us;

void handleTower() {
  
  if (!circleMode) {
      handleLF();
      handleRF();
      delay(5000); //Configure time to reach trophy
      circleMode = 1;
      return;
  }

  us = micros();
  handleLF();
  Serial.print(digitalRead(IR_PIN_1));

  static int oldValue;
  static uint32_t oldTime;
  if (digitalRead(IR_PIN_1) != oldValue) {
    int per = us-oldTime;
    if (per>PERIOD-NOISE && per<PERIOD+NOISE) {
      Serial.print(digitalRead(IR_PIN_1));
    }
    oldValue = digitalRead(IR_PIN_1);
    oldTime = us;
    handleRF();
  }

  // while(!circleDone) {
  //     //Start clockwise circle
  //     //handleLF();
  //     //If IR detected go straight towards source
  //     if(irDetected()){
  //       handleRF();
  //     }
  //     //Stop circle after 10 seconds of no detection
  //     // if (millis() - time / 1000 > 10) {
  //     //   circleDone = 1;
  //     // }

  //   }
}


// void handleTower() {
//   int circleDone = 0;
//   readSonics();
//   delay(50);

//   if (!circleMode) {
//     //Go forward until 1m from back wall
//     while (frontSonicDist > 40) {
//       handleLF();
//       handleRF();
//       readSonics();
//       delay(10);
//     }
//     circleMode = 1;
//     //Stop
//     handleStop();
//   } else {
//      double time = millis();
//      handleLF();
//     //Check for IR during circle
//     while(!circleDone) {
//       //Start clockwise circle
//       //handleLF();
//       //If IR detected go straight towards source
//       if(irDetected()){
//         handleRF();
//       }
//       //Stop circle after 10 seconds of no detection
//       // if (millis() - time / 1000 > 10) {
//       //   circleDone = 1;
//       // }

//     }
//     circleMode = 0;
//     //Stop
//     handleStop();
//   }



 
  // while (!circleDone) {
  //   //Go forward a bit
  //   handleLF();
  //   handleRF();
  //   delay(1000);

  //   //Save start position from vive
  //   int[] startCoords = [];
  //   //Start clockwise circle 
  //   handleLF();

  //   //Check for IR and interrupt if it is detected
  //   if (irDetected()) {
  //     //Stop
  //     handleSS();

  //     //Go straight
  //     handleLF();
  //     handleRF();
  //       //Go straight while IR detected
  //       while(irDetected()) {
  //       }

  //     //Stop moving
  //     handleSS();
      
  //     //Ir stopped being detected, either reached the object or lost track
  //     //How to distinguish both cases? //Flex sensor

  //     //If sensor not valid restart circle process
  //     //Wiggle a bit to see if you can find it ?
  //     //If you cant end
  //     circleDone = 1;

  //   } else {
  //     //Check from vive when coords become the same as start to complete circle within some tolerance
  //     if (coords == startCoords) {
  //       circleDone = 1;
  //     }
  //   }

    
  // }

// }

void handlePolice(){
  handleUDPServer();

  if(heading > ANGULARTOLERANCE_POLICE){
    handleLF();
    handleRS();
    return;
  }

  if(heading > ANGULARTOLERANCE_POLICE){
    handleLS();
    handleRF();
    return;
  }

  if(vx1 - px > XTOLERANCE_POLICE){
    handleLF();
    handleRF();
    return;
  }

  if(px - vx1 < XTOLERANCE_POLICE){
    handleLB();
    handleRB();
    return;
  }

  if(py < vy1){
    handleLeft();
    return;
  }

  if(py >= vy1){
    handleLeft();
    return;
  }

  handleRF();
  handleLF();
}

void handleStop() {
  handleSS();
}