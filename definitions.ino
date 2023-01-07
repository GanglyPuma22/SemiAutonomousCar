#define UDPPORT 2510

#define XTOLERANCE_POLICE 500
#define ANGULARTOLERANCE_POLICE 10
#define WALL_DIST_TOLERANCE 5
#define MAX_WALL_DIST_TOLERANCE 20
#define ANGULARTOLERANCE_WALL 30
#define TOWERANGULARTOLERANCE 10

//inches per second
#define MACH 0.034

//FRONT LEFT = 1, FRONT RIGHT = 2, BACK LEFT = 3, BACK RIGHT = 4

//NOTE: vive 1 should be the vive at the front of the robot
#define VIVE_PIN 38
#define VIVE_PIN_2 39
#define FRONT_LEFT_MOTOR_PIN 4
#define FRONT_RIGHT_MOTOR_PIN 5  //TODO SELECT ALL APPROPRIATE PINS
#define BACK_LEFT_MOTOR_PIN 6
#define BACK_RIGHT_MOTOR_PIN 15

#define FRONT_LEFT_MOTOR_SWITCH_ONE 16
#define FRONT_LEFT_MOTOR_SWITCH_TWO 17
#define FRONT_RIGHT_MOTOR_SWITCH_ONE 8
#define FRONT_RIGHT_MOTOR_SWITCH_TWO 18
#define BACK_LEFT_MOTOR_SWITCH_ONE 12
#define BACK_LEFT_MOTOR_SWITCH_TWO 11
#define BACK_RIGHT_MOTOR_SWITCH_ONE 10
#define BACK_RIGHT_MOTOR_SWITCH_TWO 9

#define LEFT_SONIC_PIN 35
#define RIGHT_SONIC_PIN 36
#define FRONT_SONIC_PIN 34
#define BACK_SONIC_PIN 37
#define SONIC_TRIGGER_PIN 33
#define MAX_SONIC_DISTANCE 5000

#define FRONT_LEFT_MOTOR_CHANNEL 0
#define FRONT_RIGHT_MOTOR_CHANNEL 1
#define BACK_LEFT_MOTOR_CHANNEL 2
#define BACK_RIGHT_MOTOR_CHANNEL 3

#define TEAMNUM 21

#define SERVO_CHANNEL       0 // use first channel of 16  
#define SERVO_RESOLUTION_BITS  14
#define SERVO_RESOLUTION  ((1<<SERVO_RESOLUTION_BITS)-1) 
#define SERVO_FREQ_HZ     60
#define SERVO_PIN        23
#define SERVO_SCAN       6   // can increase this to have wider sweep
#define FULLBACK  SERVO_RESOLUTION*(15-SERVO_SCAN)*60/10000 
#define SERVOOFF  SERVO_RESOLUTION*15*60/10000   // center servo (1.5ms pulse)
#define FULLFRONT SERVO_RESOLUTION*(15+SERVO_SCAN)*60/10000
#define SERVOTODEG(x) ((x)*(int8_t)90*10000)/(12*SERVO_RESOLUTION*60)

#define SAMPLEFREQ 15   // TOF can use 30, Ultrasonic maybe 15
#define SCANSPEED 40
#define SCANSIZE 45
#define ARRAYMAX SCANSIZE*2 // needs to be bigger than scansize

#define IR_PIN_1 19 //TODO Change pin values
#define IR_PIN_2 0
#define PERIOD 0.00143 //700 Hz signal period 1/700 -> On half the time so * 2
#define NOISE 0.0167 

enum states {
  REST, POLICE, TOWER, WALL
};

enum wallStates {
  LEFT, RIGHT, FORWARD, BACKWARD
};