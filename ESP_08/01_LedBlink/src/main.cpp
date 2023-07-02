#include <Arduino.h>


#define LED LED_BUILTIN


int toggle(int, int);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

}

void loop() {
  toggle(LED, 1000);
}

int toggle(int pin,int delayTime=1000){
  bool toggleTo=!digitalRead(pin);
  Serial.print("LED toggeling to ");
  Serial.println(toggleTo);
  digitalWrite(pin, toggleTo);
  delay(delayTime);
  return 0;
}

