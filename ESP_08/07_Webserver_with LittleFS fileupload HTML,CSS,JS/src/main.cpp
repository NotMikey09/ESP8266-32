#include <Arduino.h>
#define LED LED_BUILTIN
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <ESP8266mDNS.h>

// #include <FS.h>
#include <LittleFS.h>  // Include the LittleFS library
IPAddress    apIP(42, 42, 42, 42);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1

/* This are the WiFi access point settings. Update them to your likin */
const char *ssid = "ESP8266_Pass:88888888";
const char *password = "88888888";

// Define a web server at port 80 for HTTP
ESP8266WebServer server(80);

const int ledPin = LED; // an LED is connected to NodeMCU pin D1 (ESP8266 GPIO5) via a 1K Ohm resistor

bool ledState = false;

String readFile(const char* path) {
  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.printf("\n %s", path);
    Serial.println("file not found");
    return String();
  }

  String content;
  
    Serial.println("reading file");
  while (file.available()) {
    Serial.print(".");
    content += file.readStringUntil('\n');
  }
  file.close();

  return content;
}

void mdnsStart(){
  Serial.println("Starting mDNS...");
    if (MDNS.begin("esp8266")) {  //Start mDNS with name esp8266
      Serial.println("mDNS responder started at esp8266.local");
      Serial.println("MDNS started");
    }
  }

void handleIndex() {
String html = readFile("/index.html");
  Serial.print("html");
  server.send(200, "text/html", html);}

void handleCSS() {
  String css = readFile("/style.css");
  server.send(200, "text/css", css);}

void handleJS() {
  String js = readFile("/script.js");
  server.send(200, "application/javascript", js);
}


void handleLED() {
String state = server.arg("state");
  Serial.print("server.arg(\"state\"): ");
  Serial.println(state);
  Serial.println("LED state changing...");

  if (state == "on" || state == "ON" || state == "On") {
    digitalWrite(ledPin, LOW);  // Turn the LED on
  } else if (state == "off" || state == "OFF" || state == "Off") {
    digitalWrite(ledPin, HIGH);  // Turn the LED off
  }
  server.send(200, "text/plain", "LED state changed");
}


void setup() {
  
	Serial.begin(115200);
  LittleFS.begin();  // Initialize the LittleFS file system
  pinMode ( ledPin, OUTPUT );
  digitalWrite ( ledPin, 0 );
	
	delay(1000);
	Serial.println();
	Serial.println("Configuring access point...");

  //set-up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
	
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
 



  if(WiFi.status() == WL_CONNECTED) //If WiFi connected to hot spot then start mDNS
  {
    MDNS.begin("esp8266");
    mdnsStart();
  }


  server.on("/", handleIndex);
  server.on("/index.html", handleIndex);
  server.on("/style.css", handleCSS);
  server.on("/script.js", handleJS);


  server.on("/led", handleLED);

  server.onNotFound ( handleIndex );
	
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
  MDNS.update();
}