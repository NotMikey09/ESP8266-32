#include <Arduino.h>
#define LED LED_BUILTIN
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "htmlcssjs.h"

String htmlstr = MAIN_page; //Read HTML contents define in htmlcssjs.h file

IPAddress apIP(42, 42, 42, 42);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1

/* This are the WiFi access point settings. Update them to your likin */
const char *ssid = "ESP8266_Pass:88888888";
const char *password = "88888888";

// Define a web server at port 80 for HTTP
ESP8266WebServer server(80);

const int ledPin = LED; // an LED is connected to NodeMCU pin D1 (ESP8266 GPIO5) via a 1K Ohm resistor

bool ledState = false;

void handleRoot() {
  // digitalWrite (LED, 0); //turn the built in LED on pin DO of NodeMCU on
int status=server.arg("led").toInt();
if(status==0){
  digitalWrite (ledPin, HIGH);
}
else{
  digitalWrite(ledPin,LOW);
}
  
  ledState = digitalRead(ledPin);

 /* Dynamically generate the LED toggle link, based on its current state (on or off)*/
  char ledText[80];
  if (ledState) {
    strcpy(ledText, "LED is OFF. <a href=\"/?led=1\">Turn it ON!</a>");
  }

  else {
    strcpy(ledText, "LED is ON. <a href=\"/?led=0\">Turn it OFF!</a>");
  }
 
  ledState = digitalRead(ledPin);

  char html[1000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  // int brightness = analogRead(A0);
  // brightness = (int)(brightness + 5) / 10; //converting the 0-1024 value to a (approximately) percentage value


// Build an HTML page to display on the web-server root address
// char *htmlstring =;




  snprintf ( html, 1000,"<html>\
  <head>\
    <meta http-equiv='refresh' content='10'/>\
    <title>ESP8266 WiFi Network</title>\
    <style>\
      body {Color: #fff; background-color: #222; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; }\
          a:link,a:visited{\
            color:aqua;\
          }\
          </style>\
  </head>\
  <body>\
    <h1>ESP8266</h1><h2>Web Server button to control pins status</h2>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <p>%s<p>\
    <p>This page refreshes every 10 seconds. Click <a href=\"javascript:window.location.reload();\">here</a> to refresh the page now.</p>\
  </body>\
</html>",

    hr, min % 60, sec % 60,
    ledText
  );
  server.send ( 200, "text/html", html );
  // digitalWrite ( LED_BUILTIN, 1 );
}

void handleNotFound() {
  // digitalWrite ( LED_BUILTIN, 0 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  // digitalWrite ( LED_BUILTIN, 1 ); //turn the built in LED on pin DO of NodeMCU off
}

void setup() {
  pinMode ( ledPin, OUTPUT );
  digitalWrite(ledPin,LOW);
  // digitalWrite ( ledPin, 0 );
	
	delay(1000);
	Serial.begin(115200);
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
 MDNS.begin("esp8266");
  server.on ( "/", handleRoot );
  server.on ( "/led=1", handleRoot);
  server.on ( "/led=0", handleRoot);
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
	
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
  MDNS.update();
}