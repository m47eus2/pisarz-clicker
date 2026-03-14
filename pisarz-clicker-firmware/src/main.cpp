#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  120 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  520 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver();

uint8_t servonum = 7;

void setup() {
    Serial.begin(9600);
    Serial.println("8 channel Servo test!");

    servoDriver.begin();
    servoDriver.setOscillatorFrequency(27000000);
    servoDriver.setPWMFreq(SERVO_FREQ);

    delay(10);
}

void loop() {
    // Drive each servo one at a time using setPWM()
    servoDriver.setPWM(servonum, 0, SERVOMIN);

    delay(1000);
  
    servoDriver.setPWM(servonum, 0, SERVOMAX);

    delay(1000);
}