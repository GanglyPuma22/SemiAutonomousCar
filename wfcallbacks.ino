void handleRoot() {
  h.sendhtml(body);
}

//state transitions
void handleStateR(){
  pingstaff();
  state = REST;
  h.sendhtml(body);
}
void handleStateT(){
  pingstaff();
  state = TOWER;
  h.sendhtml(body);
}
void handleStateW(){
  pingstaff();
  wallState = LEFT;
  state = WALL;
  h.sendhtml(body);
}
void handleStateP(){
  pingstaff();
  state = POLICE;
  h.sendhtml(body);
}

//helpers
void handleForwards(int p1, int p2) {
  digitalWrite(p1, HIGH);
  digitalWrite(p2, LOW);
  h.sendhtml(body);
}

void handleBackwards(int p1, int p2) {
  digitalWrite(p1, LOW);
  digitalWrite(p2, HIGH);
  h.sendhtml(body);
}

//single side controls
void handleLF() {
  handleForwards(FRONT_LEFT_MOTOR_SWITCH_ONE, FRONT_LEFT_MOTOR_SWITCH_TWO);
  handleForwards(BACK_LEFT_MOTOR_SWITCH_ONE, BACK_LEFT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_LEFT_MOTOR_CHANNEL, 16384);
  ledcWrite(BACK_LEFT_MOTOR_CHANNEL, 16384);
  h.sendhtml(body);
}

void handleLFH() {
  handleForwards(FRONT_LEFT_MOTOR_SWITCH_ONE, FRONT_LEFT_MOTOR_SWITCH_TWO);
  handleForwards(BACK_LEFT_MOTOR_SWITCH_ONE, BACK_LEFT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_LEFT_MOTOR_CHANNEL, 16384/2);
  ledcWrite(BACK_LEFT_MOTOR_CHANNEL, 16384/2);
  h.sendhtml(body);
}

void handleLB() {
  handleBackwards(FRONT_LEFT_MOTOR_SWITCH_ONE, FRONT_LEFT_MOTOR_SWITCH_TWO);
  handleBackwards(BACK_LEFT_MOTOR_SWITCH_ONE, BACK_LEFT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_LEFT_MOTOR_CHANNEL, 16384);
  ledcWrite(BACK_LEFT_MOTOR_CHANNEL, 16384);
  h.sendhtml(body);
}

void handleRF() {
  handleForwards(FRONT_RIGHT_MOTOR_SWITCH_ONE, FRONT_RIGHT_MOTOR_SWITCH_TWO);
  handleForwards(BACK_RIGHT_MOTOR_SWITCH_ONE, BACK_RIGHT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_RIGHT_MOTOR_CHANNEL, 16384);
  ledcWrite(BACK_RIGHT_MOTOR_CHANNEL, 16384);
  h.sendhtml(body);
}

void handleRFH() {
  handleForwards(FRONT_RIGHT_MOTOR_SWITCH_ONE, FRONT_RIGHT_MOTOR_SWITCH_TWO);
  handleForwards(BACK_RIGHT_MOTOR_SWITCH_ONE, BACK_RIGHT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_RIGHT_MOTOR_CHANNEL, 16384/2);
  ledcWrite(BACK_RIGHT_MOTOR_CHANNEL, 16384/2);
  h.sendhtml(body);
}

void handleRB() {
  handleBackwards(FRONT_RIGHT_MOTOR_SWITCH_ONE, FRONT_RIGHT_MOTOR_SWITCH_TWO);
  handleBackwards(BACK_RIGHT_MOTOR_SWITCH_ONE, BACK_RIGHT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_RIGHT_MOTOR_CHANNEL, 16384);
  ledcWrite(BACK_RIGHT_MOTOR_CHANNEL, 16384);
  h.sendhtml(body);
}

//single side stops
void handleLS() {
  ledcWrite(FRONT_LEFT_MOTOR_CHANNEL, 0);
  ledcWrite(BACK_LEFT_MOTOR_CHANNEL, 0);
  h.sendhtml(body);
}

void handleRS() {
  ledcWrite(FRONT_RIGHT_MOTOR_CHANNEL, 0);
  ledcWrite(BACK_RIGHT_MOTOR_CHANNEL, 0);
  h.sendhtml(body);
}

void handleLFC(){
  pingstaff();
  handleLF();
}

void handleLBC(){
  pingstaff();
  handleLB();
}

void handleLSC(){
  pingstaff();
  handleLS();
}

void handleRFC(){
  pingstaff();
  handleRF();
}

void handleRBC(){
  pingstaff();
  handleRB();
}

void handleRSC(){
  pingstaff();
  handleRS();
}

//mechanum sideways
void handleLeft() {
  handleBackwards(FRONT_RIGHT_MOTOR_SWITCH_ONE, FRONT_RIGHT_MOTOR_SWITCH_TWO);
  handleForwards(BACK_RIGHT_MOTOR_SWITCH_ONE, BACK_RIGHT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_RIGHT_MOTOR_CHANNEL, 16384);
  ledcWrite(BACK_RIGHT_MOTOR_CHANNEL, 16384);

  handleForwards(FRONT_LEFT_MOTOR_SWITCH_ONE, FRONT_LEFT_MOTOR_SWITCH_TWO);
  handleBackwards(BACK_LEFT_MOTOR_SWITCH_ONE, BACK_LEFT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_LEFT_MOTOR_CHANNEL, 16384);
  ledcWrite(BACK_LEFT_MOTOR_CHANNEL, 16384);
  h.sendhtml(body);
}

void handleRight() {
  handleForwards(FRONT_RIGHT_MOTOR_SWITCH_ONE, FRONT_RIGHT_MOTOR_SWITCH_TWO);
  handleBackwards(BACK_RIGHT_MOTOR_SWITCH_ONE, BACK_RIGHT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_RIGHT_MOTOR_CHANNEL, 16384);
  ledcWrite(BACK_RIGHT_MOTOR_CHANNEL, 16384);

  handleBackwards(FRONT_LEFT_MOTOR_SWITCH_ONE, FRONT_LEFT_MOTOR_SWITCH_TWO);
  handleForwards(BACK_LEFT_MOTOR_SWITCH_ONE, BACK_LEFT_MOTOR_SWITCH_TWO);
  ledcWrite(FRONT_LEFT_MOTOR_CHANNEL, 16384);
  ledcWrite(BACK_LEFT_MOTOR_CHANNEL, 16384);
  h.sendhtml(body);
}

//full stop
void handleSS() {
  ledcWrite(FRONT_LEFT_MOTOR_CHANNEL, 0);
  ledcWrite(BACK_LEFT_MOTOR_CHANNEL, 0);
  ledcWrite(FRONT_RIGHT_MOTOR_CHANNEL, 0);
  ledcWrite(BACK_RIGHT_MOTOR_CHANNEL, 0);
  h.sendhtml(body);
}
