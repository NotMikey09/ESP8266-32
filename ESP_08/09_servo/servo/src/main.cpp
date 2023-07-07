#include <Arduino.h>
#include <Servo.h>
//Simplest code to rotate the servo:
/*This will rotate a servo connected to D0(signal pin) drom 0to180 and vice versa*/
Servo myservo;

void setup() {
  myservo.attach(D0);//attach the sevo to D0 pin.

}

void loop() {
  //this loop will rotate the servo 0 to 180.
  for (int i = 0; i <= 180; i++) {
    myservo.write(i);
    delay(10);
  }//this loop will rotate from 180 to 0.
  for (int i = 180; i >= 0; i--) {
    myservo.write(i);
    delay(10);
  }
}
