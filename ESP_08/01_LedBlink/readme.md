# Program to blink led on esp8266/ESP32 boards

### PlatformIO configuration

*platfformio.ini*

```ini
[env:nodemcu]
platform = espressif8266
board = nodemcu
framework = arduino
monitor_speed = 115200

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

[env:uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 9600
```

### Main program or Arduino sketch

*main.cpp*

```cpp
#include <Arduino.h>

#define LED LED_BUILTIN
#ifdef esp32dev
  #include <ESP32WiFi.h>
  #include <ESP32WebServer.h>
#else
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>

#endif


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
```

### Code Description

Arduino is an open-source electronics platform widely used for creating interactive projects. It comes with a programming language and a set of functions that make it easy to control various hardware components. Here are explanations and usage examples of some common Arduino functions:

1. `pinMode()`: This function is used to set the mode of a pin as either input or output. It takes two parameters: the pin number and the mode (INPUT or OUTPUT).
   
   ```cpp
   pinMode(13, OUTPUT);   // Sets pin 13 as output
   pinMode(2, INPUT);     // Sets pin 2 as input
   ```

2. `digitalWrite()`: This function is used to write a digital value (HIGH or LOW) to a specified pin. It is typically used to control LEDs, relays, and other digital output devices.
   
   ```cpp
   digitalWrite(13, HIGH);   // Sets pin 13 to HIGH (ON)
   digitalWrite(8, LOW);     // Sets pin 8 to LOW (OFF)
   ```

3. `digitalRead()`: This function reads the digital value (HIGH or LOW) from a specified pin. It is commonly used to read the state of buttons, switches, or digital sensors.
   
   ```cpp
   int buttonState = digitalRead(2);   // Reads the state of pin 2 and stores it in 'buttonState'
   ```

4. `analogWrite()`: This function is used to write a PWM (Pulse Width Modulation) value to a pin. It can be used to control the intensity of an LED or the speed of a motor.
   
   ```cpp
   analogWrite(9, 128);   // Writes PWM value 128 (50% duty cycle) to pin 9
   ```

5. `analogRead()`: This function reads the analog value (0 to 1023) from an analog pin. It is used to read values from sensors such as temperature sensors, light sensors, etc.
   
   ```cpp
   int sensorValue = analogRead(A0);   // Reads the analog value from pin A0 and stores it in 'sensorValue'
   ```

6. `delay()`: This function pauses the program for a specified number of milliseconds. It is used to introduce delays in the program flow.
   
   ```cpp
   delay(1000);   // Delays the program execution for 1 second (1000 milliseconds)
   ```

7. `Serial.begin()`: This function initializes the serial communication between the Arduino board and a computer. It sets the data rate in bits per second (baud rate).
   
   ```cpp
   Serial.begin(9600);   // Initializes serial communication at 9600 baud rate
   ```

8. `Serial.print()`: This function is used to send data to the computer over the serial connection. It can be used to display information, debug messages, or sensor readings.
   
   ```cpp
   int sensorValue = analogRead(A0);
   Serial.print("Sensor Value: ");
   Serial.println(sensorValue);   // Prints the sensor value to the serial monitor
   ```


