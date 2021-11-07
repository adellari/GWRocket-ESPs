#include<Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
//#include <Adafruit_MPU6050.h>
#include "MMA7660.h"

#include "ESPAsyncWebServer.h"

Adafruit_BMP280 bme;
MMA7660 acc;

const char *ssid = "Goldwinger-ESP";
const char *password = "j4mesbondFiends";

AsyncWebServer server(80);

String readRotation(int axis)
{

  int8_t x, y, z;
  acc.getXYZ(&x,&y,&z);

  String response = "--";


  switch(axis){
  case 1:
  response = String(x);
  break;

  case 2:
  response = String(y);
  break;

  case 3:
  response = String(z);
  break;


  return(response);
}



}

String readAcceleration(int axis)
{

  float ax,ay,az;
  String response = "--";

  if(acc.getAcceleration(&ax,&ay,&az))
{
  switch(axis){
    case 1:
    response = String(ax);
    break;

    case 2:
    response = String(ay);
    break;

    case 3:
    response = String(az);
    break;

  }

  return(response);
}

int8_t x, y, z;
 
acc.getXYZ(&x,&y,&z);

}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  acc.init();         // weird accelerometer (just for testing)
  if(!bme.begin()){   // our bmp sensor
    Serial.println("I2C sensors not found");
  }

  Serial.println(WiFi.softAPIP());

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(bme.readTemperature()).c_str());
    });

   server.on("/altitude", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(bme.readAltitude()).c_str());
    });

   server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(bme.readPressure()).c_str());
    });

  server.on("/rx", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readRotation(1).c_str());
    });

   server.on("/ry", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readRotation(2).c_str());
    });

   server.on("/rz", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readRotation(3).c_str());
    });

    server.on("/ax", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readAcceleration(1).c_str());
    });

   server.on("/ay", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readAcceleration(2).c_str());
    });

   server.on("/az", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readAcceleration(3).c_str());
    });

    server.begin();
}


void loop() {
  
}
