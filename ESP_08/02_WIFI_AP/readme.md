# Program an ESP8266/ESP32 as a WiFi Access Point (AP):

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

#include <WiFi.h>

const char* ssid = "YourAPSSID";
const char* password = "YourAPPassword";

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Connect to WiFi network
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress ip = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(ip);
}

void loop() {
  // Code for the main program loop can be added here
}
```

Now let's go through the different parts of the code:

1. Including the necessary library:
   
   ```cpp
   #include <WiFi.h>
   ```
   
   This line includes the WiFi library, which provides the necessary functions to work with WiFi connections.

2. Defining the Access Point (AP) credentials:
   
   ```cpp
   const char* ssid = "YourAPSSID";
   const char* password = "YourAPPassword";
   ```
   
   Replace `"YourAPSSID"` with the desired name (SSID) for your access point and `"YourAPPassword"` with the password you want to set.

3. The `setup()` function:
   
   ```cpp
   void setup() {
     Serial.begin(115200);
     delay(2000);
   
     WiFi.mode(WIFI_AP);
     WiFi.softAP(ssid, password);
   
     IPAddress ip = WiFi.softAPIP();
     Serial.print("AP IP address: ");
     Serial.println(ip);
   }
   ```
   
   - `Serial.begin(115200);` initializes the serial communication at a baud rate of 115200 to allow communication with your computer via the serial monitor.
   
   - `delay(2000);` introduces a delay of 2 seconds to allow time for the serial monitor to initialize.
   
   - `WiFi.mode(WIFI_AP);` sets the WiFi mode to Access Point (AP) mode.
   
   - `WiFi.softAP(ssid, password);` creates the Access Point using the defined SSID and password.
   
   - `IPAddress ip = WiFi.softAPIP();` retrieves the IP address assigned to the Access Point.
   
   - `Serial.print("AP IP address: ");` prints a text message to the serial monitor.
   
   - `Serial.println(ip);` prints the IP address of the Access Point to the serial monitor.

4. The `loop()` function:
   
   ```cpp
   void loop() {
     // Code for the main program loop can be added here
   }
   ```
   
   The `loop()` function is where you can add your main program logic. This code will be executed repeatedly in an infinite loop once the initialization in the `setup()` function is completed.

After uploading this code to your ESP8266/ESP32 board, it will act as a WiFi Access Point with the specified SSID and password. You can connect to this access point using a device (such as a smartphone or another computer) and access the network provided by the ESP8266/ESP32.

Remember to adjust the baud rate (`Serial.begin()`) and the delay in `setup()` according to your requirements. Additionally, you can add more code in the `loop()` function to implement further functionality based on your project's needs.
