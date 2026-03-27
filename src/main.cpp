#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>
const int xpin = A0;
const int ypin = A1;
int x_neutral;
int y_neutral;
int x;
int y;
int motorSpeed = 10; // RPM
Stepper s1(2048,2,4,5,7);
Servo myservo;
int pos = 0;
int spd = 2;

void setup() {
  Serial.begin(9600);
  s1.setSpeed(motorSpeed);
  s1.step(512);
  myservo.attach(6);
  x_neutral = analogRead(xpin);
  y_neutral = analogRead(ypin);
  myservo.write(pos);

}

void loop() {
  x = analogRead(xpin);
  y = analogRead(ypin); //max 822
  Serial.print("x: ");
  Serial.println(x);
  Serial.print("y: ");
  Serial.println(y);
    if (x-x_neutral < -100){
    s1.step(50);
  }
  else if (x - x_neutral > 100) {
    s1.step(-50);
  }

  if (y-y_neutral < -100){
    pos += spd;
    myservo.write(pos);
  }
    else if (y - y_neutral > 100) {
      pos -= spd;
    myservo.write(pos);
  }


  
}
