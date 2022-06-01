#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

const int left_ir = 4;
const int right_ir = 5;
const int VCC1 = 12;
const int VCC2 = 13;
const int VCC3 = 8;
const int GND1 = 7;
const int GND2 = 9;
const int trigPin = 3;
const int echoPin = 2;
const int max_dis = 100;
unsigned int distance;
unsigned int left;
unsigned int right;
const int button = 10;
const int led = 6;
int buttonState;
int lastState = HIGH;
bool flag = 0;
const int DUTY = 20;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *BL = AFMS.getMotor(1);
Adafruit_DCMotor *BR = AFMS.getMotor(2);
Adafruit_DCMotor *FR = AFMS.getMotor(3);
Adafruit_DCMotor *FL = AFMS.getMotor(4);

NewPing sonar(trigPin, echoPin, max_dis);

int checkButtonPress() {
    buttonState = digitalRead(button);
    if(buttonState != lastState) {
        lastState = buttonState;
        if(buttonState == HIGH){
            return HIGH;
        }
    }
    return LOW;
}

typedef struct task
{
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);
} task;

const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum CAR_States {STOP, DRIVE, LEFT, RIGHT, PARK};
enum Switch {ON, OFF};

int CAR_Tick(int state) {
  switch (state) {
    case STOP:
      if(distance > 5 && distance <= 30){
        state = DRIVE;
      }else if(right == 0 && left == 1){
        state = RIGHT;
      }else if(right == 1 && left == 0){
        state = LEFT;
      }else{
        state = STOP;
      }
      break;
    case DRIVE:
      if(distance > 30){
        state = STOP;
      }else
      if(right == 0 && left == 1){
        state = RIGHT;
      }else if(right == 1 && left == 0){
        state = LEFT;
      }else{
        state = DRIVE;
      }
      break;
    case LEFT:
      if(right == 0 && left == 0){
        state = DRIVE;
      }else if(right == 0 && left == 1){
        state = RIGHT;
      }else if(right == 1 && left == 1){
        state = STOP;
      }else{
        state = LEFT;
      }
      break;
    case RIGHT:
      if(right == 0 && left == 0){
        state = DRIVE;
      }else if(right == 1 && left == 0){
        state = LEFT;
      }
      else if(right == 1 && left == 1){
        state = STOP;
      }else{
        state = RIGHT;
      }
      break;
     case PARK:
      state = PARK;
      break;
    default:
      state = STOP;
      break;
  }
  switch (state) {
    case STOP:
      BL->setSpeed(0);
      BR->setSpeed(0);
      FR->setSpeed(0);
      FL->setSpeed(0);
      BL->run(RELEASE);
      BR->run(RELEASE);
      FR->run(RELEASE);
      FL->run(RELEASE);
      break;
    case DRIVE:
      BL->setSpeed(130);
      BR->setSpeed(130);
      FR->setSpeed(130);
      FL->setSpeed(130);
      BL->run(FORWARD);
      BR->run(FORWARD);
      FR->run(FORWARD);
      FL->run(FORWARD);
      break;
    case LEFT:
      BL->setSpeed(130);
      BR->setSpeed(150);
      FR->setSpeed(150);
      FL->setSpeed(130);
      BL->run(BACKWARD);
      BR->run(FORWARD);
      FR->run(FORWARD);
      FL->run(BACKWARD);
      break;
    case RIGHT:
      BL->setSpeed(150);
      BR->setSpeed(130);
      FR->setSpeed(130);
      FL->setSpeed(150);
      BL->run(FORWARD);
      BR->run(BACKWARD);
      FR->run(BACKWARD);
      FL->run(FORWARD);
      break;
     case PARK:
      BL->setSpeed(0);
      BR->setSpeed(0);
      FR->setSpeed(0);
      FL->setSpeed(0);
      BL->run(RELEASE);
      BR->run(RELEASE);
      FR->run(RELEASE);
      FL->run(RELEASE);
      break;
  }
  return state;
}

int Switch_Tick(int state){
  switch (state) {
    case ON:
      if(checkButtonPress()){
        state = OFF;     
      }
      break;
    case OFF:
      if(checkButtonPress()){
        state = ON;
        flag = 0;    
      }
      break;
  }
  switch (state) {
    case ON:
      if(!flag){
        tasks[0].state = STOP;
        flag = !flag;
      }      
      analogWrite(led, DUTY);
      break;
    case OFF:
      tasks[0].state = PARK;
      digitalWrite(led, LOW);
      break;
  }
  return state;
}

void setup() {
  Serial.begin(9600);
  pinMode(left_ir, INPUT);
  pinMode(right_ir, INPUT);
  pinMode(VCC1, OUTPUT);
  digitalWrite(VCC1, HIGH);
  pinMode(VCC2, OUTPUT);
  digitalWrite(VCC2, HIGH);
  pinMode(VCC3, OUTPUT);
  digitalWrite(VCC3, HIGH);
  pinMode(GND1, OUTPUT);
  digitalWrite(GND1, LOW);
  pinMode(GND2, OUTPUT);
  digitalWrite(GND2, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  AFMS.begin();
  unsigned char i = 0;
  tasks[i].state = DRIVE;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &CAR_Tick;
  i++;
  tasks[i].state = OFF;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Switch_Tick;
}

void loop() {
  distance = sonar.ping_cm();
  left = digitalRead(left_ir);
  right = digitalRead(right_ir);
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}
