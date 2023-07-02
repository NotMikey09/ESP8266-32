# Program an ESP8266/ESP32 as a WiFi Station (STA):

*platformio.ini*

```ini
[env:nodemcuv2]
platform = espressif8266
board = nodemcuv2
framework = arduino
monitor_speed = 115200
```

*main.cpp*

```cpp
#include <Arduino.h>


#include <ESP8266WiFi.h>

/* Your WiFi Soft Access Point settings */
const char* ssid = "ESP8266 Pass:88888888"; //replace this with your WiFi network name
const char* password = "88888888"; //replace this with your WiFi network password

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Configuring WiFi access point...");
  
  /* You can remove the password parameter if you want the AP to be open. */
  boolean result = WiFi.softAP(ssid, password);
  if(result==true) {
    IPAddress myIP = WiFi.softAPIP();
  
    Serial.println("done!");
    Serial.println("");
    Serial.print("WiFi network name: ");
    Serial.println(ssid);
    Serial.print("WiFi network password: ");
    Serial.println(password);
    Serial.print("Host IP Address: ");
    Serial.println(myIP);
    Serial.println("");
  }

  else {
    Serial.println("error! Something went wrong...");
  }
}

void loop() {
  Serial.printf("Number of connected devices (stations) = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
```

## Now let's go through the different parts of the code:

This code sets up an ESP8266 board as a WiFi Soft Access Point (AP) and provides information about the access point. Let's go through it step by step:

1. Including the necessary libraries:
   
   ```cpp
   #include <Arduino.h>
   #include <ESP8266WiFi.h>
   ```
   
   The code includes the necessary libraries for the Arduino and ESP8266WiFi.

2. Defining the Access Point (AP) credentials:
   
   ```cpp
   const char* ssid = "ESP8266 Pass:88888888";
   const char* password = "88888888";
   ```
   
   These variables define the SSID (WiFi network name) and password for the Access Point. You can replace these values with your desired network name and password.

3. The `setup()` function:
   
   ```cpp
   void setup() {
     delay(1000);
     Serial.begin(115200);
     Serial.println();
     Serial.println();
     Serial.print("Configuring WiFi access point...");
   
     boolean result = WiFi.softAP(ssid, password);
     if(result == true) {
       IPAddress myIP = WiFi.softAPIP();
   
       Serial.println("done!");
       Serial.println("");
       Serial.print("WiFi network name: ");
       Serial.println(ssid);
       Serial.print("WiFi network password: ");
       Serial.println(password);
       Serial.print("Host IP Address: ");
       Serial.println(myIP);
       Serial.println("");
     }
     else {
       Serial.println("error! Something went wrong...");
     }
   }
   ```
   
   - `delay(1000);` introduces a delay of 1 second before starting the setup process.
   - `Serial.begin(115200);` initializes the serial communication at a baud rate of 115200 to allow communication with your computer via the serial monitor.
   - `Serial.println();` prints a blank line to the serial monitor.
   - `Serial.print("Configuring WiFi access point...");` displays a message indicating the configuration of the WiFi access point.
   - `boolean result = WiFi.softAP(ssid, password);` creates the WiFi Soft Access Point using the specified SSID and password.
   - `if(result == true)` checks if the creation of the access point was successful.
   - `IPAddress myIP = WiFi.softAPIP();` retrieves the IP address assigned to the Access Point.
   - The following lines of code display information about the access point, including the SSID, password, and IP address.
   - If the access point creation was not successful, an error message is displayed.

4. The `loop()` function:
   
   ```cpp
   void loop() {
     Serial.printf("Number of connected devices (stations) = %d\n", WiFi.softAPgetStationNum());
     delay(3000);
   }
   ```
   
   - `Serial.printf("Number of connected devices (stations) = %d\n", WiFi.softAPgetStationNum());` prints the number of connected devices (stations) to the access point.
   - `delay(3000);` introduces a delay of 3 seconds before repeating the loop.

When you upload and run this code on your ESP8266 board, it will create a WiFi Soft Access Point with the specified SSID and password. The access point's information, including the SSID, password, and IP address, will be printed to the serial monitor. The number of connected devices to the access point will also be displayed continuously in the loop.

* *Please note that the code assumes you have the necessary libraries installed and configured properly in your Arduino IDE for the ESP8266 board.*
