#include <SPI.h>
#include <SD.h>
#include <OneWire.h>
#include "DallasTemperature.h"

#define WATER_TEMP 5
const int chipSelect = 4;
const int Min_Temp = 5; //Arbitrary value in which the heater is going to turn ON
const int Max_Temp = 8; //Arbitrary value in which the heater is going to turn OFF

OneWire oneWire(WATER_TEMP);
// BUS
DallasTemperature sensors(&oneWire);

File logFile;
File readFile;

void setup() {
  
  Serial.println("Init\n");
  
  Serial.begin(9600);
  pinMode(6, OUTPUT); //Configure PIN 6 as Trigger for the HEATER
  pinMode(7, OUTPUT); //Configure PIN 7 as Trigger for the CIRCULATOR MOTOR 
  pinMode(5, OUTPUT); //Configure PIN 5 as Trigger for the AERATOR MOTOR 
  SD.begin(chipSelect);
  
  logFile = SD.open("logger.txt", FILE_WRITE);
  if (!logFile) {
    Serial.println("SD-Failed");
  }
}

void loop() {
  float celsius;
  // temperature is read from the sensor
  celsius = getWaterTemp();
  
  // condition to switch the motor and heater state
  if (celsius <= Min_Temp) { 
    turnHeaterON();
  } else if (celsius >= Max_Temp) {
    turnHeaterOFF();
  }
}

void logData(String data) {
  if (logFile) {
     logFile.println(data);
  } else {
    Serial.println("SD Failed to write");
  }
}

void readData() {
  logFile.close();
  
  readFile = SD.open("logger.txt");
  
  if(readFile) {
    Serial.println("Reading...\n");

    while(readFile.available()) {
      Serial.write(readFile.read());
    }
    readFile.close();
  } else {
    Serial.println("Failed to read");
  }
}

float getWaterTemp() {
  float temp;
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  return temp;
}

float getAirTemp() {
  float temp;
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(1);
  return temp;
}

void turnHeaterON() {
  // trigger the signal for HEATER ON
  digitalWrite(6, HIGH); 
  // trigger the signal for CIRCULATOR MOTOR OFF
  digitalWrite(7, LOW);
  // trigger the signal for AERATOR MOTOR OFF
  digitalWrite(5, LOW); 
}

void turnHeaterOFF() {
  // trigger the signal for HEATER OFF
  digitalWrite(6, LOW); 
  // trigger the signal for CIRCULATOR MOTOR ON
  digitalWrite(7, HIGH); 
  // trigger the signal for AERATOR MOTOR ON
  digitalWrite(5, LOW); 
}
