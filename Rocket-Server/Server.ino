#include<Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
//#include <Adafruit_MPU6050.h>

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

#include "ESPAsyncWebServer.h"

Adafruit_BME280 bme;
MPU6050 mpu;

#define MPU6050_ACCEL_OFFSET_X -773
#define MPU6050_ACCEL_OFFSET_Y 3278
#define MPU6050_ACCEL_OFFSET_Z 1660
#define MPU6050_GYRO_OFFSET_X  -24
#define MPU6050_GYRO_OFFSET_Y  -62
#define MPU6050_GYRO_OFFSET_Z  -6
#define SEALEVELPRESSURE_HPA (30.08)


const char *ssid = "Goldwinger-ESP";
const char *password = "j4mesbondFiends";

AsyncWebServer server(80);

int16_t ax, ay, az;
int16_t gx, gy, gz;

int accelgyro(int id)
{
  int response = 0;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  case 1:
  response = ax;
  break;

  case 2:
  response = ay;
  break;

  case 3:
  response = az;
  break;

  case 4:
  response = gx;
  break;

  case 5:
  response = gy;
  break;

  case 6:
  response = gz;
  break;

  return response;
}




}


void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Wire.begin();
  mpu.initialize();
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  //acc.init();         // weird accelerometer (just for testing)
  if(!bme.begin(0x76)){   // our bmp sensor
    Serial.println("I2C sensors not found");

  mpu.setXAccelOffset(MPU6050_ACCEL_OFFSET_X);
  mpu.setYAccelOffset(MPU6050_ACCEL_OFFSET_Y);
  mpu.setZAccelOffset(MPU6050_ACCEL_OFFSET_Z);
  mpu.setXGyroOffset(MPU6050_GYRO_OFFSET_X);
  mpu.setYGyroOffset(MPU6050_GYRO_OFFSET_Y);
  mpu.setZGyroOffset(MPU6050_GYRO_OFFSET_Z);

  }


  Serial.println(WiFi.softAPIP());

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.print("Temperature: ");
    Serial.println(bme.readTemperature());
    request->send_P(200, "text/plain", String(bme.readTemperature()).c_str());
    });

   server.on("/altitude", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(bme.readAltitude(SEALEVELPRESSURE_HPA)).c_str());
    });

   server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(bme.readPressure()).c_str());
    });

   server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(bme.readHumidity()).c_str());
    });

  server.on("/rx", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(accelgyro(1)).c_str();
    });

   server.on("/ry", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(accelgyro(2).c_str());
    });

   server.on("/rz", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(accelgyro(3).c_str());
    });

    server.on("/ax", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(accelgyro(4).c_str());
    });

   server.on("/ay", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(accelgyro(5).c_str());
    });

   server.on("/az", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(accelgyro(6).c_str());
    });

    server.begin();
}


void loop() {

/* this is for testing the i2c string transmission between the esp and rpi
  Serial.print("yo :dfdj` ");
  Serial.println(4);
  //Serial. println("hello: 8");
  */
}
