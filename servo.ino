#include <Servo.h>

Servo servo1;
Servo servo2;

bool reverse = false;

unsigned long lastServoTime = 0;
unsigned long nextLedTime = 0;

int servoPos = 0;

int servoPin1 = 5;
int servoPin2 = 6;
int ledPin = 11;

int randomness = 180; // 0-255. Variansen i LED-flammandet

int forwardDelay = 40; // Hur många ms varje steg framåt ska ta
int reverseDelay = 5; // Motsvarande fast bakåt

void moveServos(int pos) {
  servo1.write(pos);
  servo2.write(pos);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  
  moveServos(0); // Flytta servos till startposition
  
  delay(2000);
}

void loop() {
  if (servoPos == 180) {
    reverse = true;
  }
  if (servoPos == 0) {
    reverse = false;
  }

  // Dessa if-satser flyttar servon bakåt eller framåt beroende på vilket håll den är på väg åt,
  // men bara om det har gått tillräckligt lång tid sedan den flyttades senast
  if (reverse && millis() - lastServoTime >= reverseDelay) {
    servoPos -= 1;
    lastServoTime = millis();
    moveServos(servoPos);
  } else if (!reverse && millis() - lastServoTime >= forwardDelay) {
    servoPos += 1;
    lastServoTime = millis();
    moveServos(servoPos);
  }

  if (millis() >= nextLedTime) {
    analogWrite(ledPin, random(randomness) + 255 - randomness);

    nextLedTime = millis() + random(100);
  }
}
