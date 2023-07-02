To include HTML, CSS, and JS files in an ESP8266 web server from a folder, you can follow these steps:

1. Connect the ESP8266 to your computer and set up the necessary development environment and libraries.

2. Create a folder on your computer that contains the HTML, CSS, and JS files you want to serve from the ESP8266.

3. Upload the HTML, CSS, and JS files to the ESP8266 using a file transfer method, such as the Arduino IDE or a tool like ESP8266FS. This will store the files in the flash memory of the ESP8266.

4. In your Arduino sketch, include the necessary libraries for setting up the web server:

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
```

5. Set up the WiFi connection:

```cpp
const char* ssid = "YourNetworkSSID";
const char* password = "YourNetworkPassword";

void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}
```

Replace `"YourNetworkSSID"` and `"YourNetworkPassword"` with your actual WiFi network credentials.

6. Create an instance of the `ESP8266WebServer` class:

```cpp
ESP8266WebServer server(80);
```

7. In the `setup()` function, start the server and define the routes to handle different URLs:

```cpp
void handleRoot() {
  server.send(200, "text/html", getFileContent("/index.html"));
}

void handleCSS() {
  server.send(200, "text/css", getFileContent("/style.css"));
}

void handleJS() {
  server.send(200, "application/javascript", getFileContent("/script.js"));
}

void setup() {
  Serial.begin(115200);

  setupWiFi();

  server.on("/", handleRoot);
  server.on("/style.css", handleCSS);
  server.on("/script.js", handleJS);

  server.begin();
  Serial.println("HTTP server started");
}
```

The `handleRoot()`, `handleCSS()`, and `handleJS()` functions are route handlers that serve the corresponding files. The `getFileContent()` function reads the file content from the flash memory and returns it as a `String`. You'll need to implement the `getFileContent()` function yourself, using the appropriate method to read the file from the flash memory.

8. In the `loop()` function, handle client requests:

```cpp
void loop() {
  server.handleClient();
}
```

9. Upload the sketch to the ESP8266 and open the Serial Monitor to check the connection status.

Once the ESP8266 is connected to the WiFi network, it will start serving the HTML, CSS, and JS files from the flash memory when the corresponding URLs are requested. For example, accessing `http://<ESP8266_IP>/` will serve the `index.html` file, `http://<ESP8266_IP>/style.css` will serve the `style.css` file, and `http://<ESP8266_IP>/script.js` will serve the `script.js` file. Replace `<ESP8266_IP>` with the IP address of your ESP8266 on the network.

Make sure to adapt the code to your specific file and folder structure and adjust the content types (`text/html`, `text/css`, `application/javascript`) as needed.