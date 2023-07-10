#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

IPAddress apIP(42, 42, 42, 42); // Defining a static IP address: local & gateway
// Default IP in AP mode is 192.168.4.1

/* WiFi access point settings */
const char* ssid = "ESP8266_Pass:88888888";
const char* password = "88888888";

// Define a web server at port 80 for HTTP
ESP8266WebServer server(80);

const int servoPin = D0; // Pin connected to the servo
Servo myservo; // Servo object for controlling the servo motor

int servoPosition = 90; // Initial position of the servo motor
bool servoStopped = false; //  to stop the servo rotation

void handleRoot() {
  digitalWrite(LED_BUILTIN, HIGH); // Turn the built-in LED on

  if (server.hasArg("position")) {
    servoPosition = server.arg("position").toInt();
    servoPosition = constrain(servoPosition, 0, 180); // Constrain the position value between 0 and 180
    myservo.write(servoPosition); // Set the servo position
  }

  if (server.hasArg("stop")) {
    servoStopped = true;
    myservo.detach(); // Detach the servo to stop it
  }

  if (server.hasArg("slider")) {
    servoPosition = server.arg("slider").toInt();
    servoPosition = constrain(servoPosition, 0, 180); // Constrain the position value between 0 and 180
    if (!servoStopped) {
      myservo.attach(servoPin); // Attach the servo if it was stopped
    }
    myservo.write(servoPosition); // Set the servo position
  }

  char html[1000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  // A HTML page to display on the web-server root address
  snprintf(html, 1000,
           "<html>\
            <head>\
              <meta http-equiv='refresh' content='10'/>\
              <title>ESP8266 WiFi Network</title>\
              <style>\
                body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
                h1 { Color: #AA0000; }\
              </style>\
            </head>\
            <body>\
              <h1>ESP8266 Wi-Fi Access Point and Web Server Demo</h1>\
              <p>Uptime: %02d:%02d:%02d</p>\
              <p>Servo Position: %d degrees</p>\
              <form action='/' method='get'>\
                <input type='number' name='position' min='0' max='180' value='%d'>\
                <input type='submit' value='Set Position'>\
              </form>\
              <form action='/' method='get'>\
                <input type='checkbox' name='stop' value='1'> Stop Servo\
              </form>\
              <form action='/' method='get'>\
                <input type='range' name='slider' min='0' max='180' value='%d'>\
                <input type='submit' value='Set Position'>\
              </form>\
              <p>This page refreshes every 10 seconds. Click <a href=\"javascript:window.location.reload();\">here</a> to refresh the page now.</p>\
            </body>\
          </html>",
           hr, min % 60, sec % 60,
           servoPosition,
           servoPosition,
           servoPosition);

  server.send(200, "text/html", html);
  digitalWrite(LED_BUILTIN, LOW); // Turn the built-in LED off
}

void handleNotFound() {
  digitalWrite(LED_BUILTIN, HIGH); // Turn the built-in LED on

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, LOW); // Turn the built-in LED off
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // Set up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // Subnet FF FF FF 00

  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  myservo.attach(servoPin); // Attach the servo to the specified pin

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
