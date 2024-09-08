#include <Servo.h>

int servoPin = 3;
Servo Servo1;
int rotationCounter = 0;

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

const int ledPins[] = {2, 3, 4, 5, 6};
int pwmValues[3] = {0, 0, 0};

void setup() {
  Servo1.attach(servoPin);

  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);
  }

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  pwmValues[0] = getPW(S2, S3);
  pwmValues[1] = getPW(S2, S3);
  pwmValues[2] = getPW(S2, S3);

  Serial.print("Red PW = ");
  Serial.print(pwmValues[0]);
  Serial.print(" - Green PW = ");
  Serial.print(pwmValues[1]);
  Serial.print(" - Blue PW = ");
  Serial.println(pwmValues[2]);

  if (rotationCounter % 2 == 0 && pwmValues[0] >= 15 && pwmValues[0] <= 28 && pwmValues[1] >= 24 && pwmValues[1] <= 38 && pwmValues[2] >= 20 && pwmValues[2] <= 31) {
    rotation(rotationCounter + 1);
    rotationCounter++;
  } else if (rotationCounter % 2 != 0 && pwmValues[0] >= 0 && pwmValues[0] <= 5 && pwmValues[1] >= 0 && pwmValues[1] <= 5 && pwmValues[2] >= 0 && pwmValues[2] <= 5) {
    rotation(rotationCounter + 1);
    rotationCounter++;
  }
  
  delay(1000);
}

void rotation(int angle) {
  Servo1.write(angle % 2 == 0 ? 180 : 0);
  delay(1000);
}

int getPW(int s2State, int s3State) {
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  return pulseIn(sensorOut, LOW);
}