#include <SPI.h>
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define WATER_TEMP 5
const int chipSelect = 4;
const int Min_Temp = 5; //Arbitrary value in which the heater is going to turn ON
const int Max_Temp = 8; //Arbitrary value in which the heater is going to turn OFF

OneWire oneWire(WATER_TEMP);
// BUS
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(6, OUTPUT); //Configure PIN 6 as Trigger for the HEATER
  pinMode(7, OUTPUT); //Configure PIN 7 as Trigger for the CIRCULATOR MOTOR 
  pinMode(5, OUTPUT); //Configure PIN 5 as Trigger for the AERATOR MOTOR 
  SD.begin(chipSelect);
  File logFile = SD.open("logger.txt", FILE_WRITE);

  if (!logFile) {
    Serial.println("SD Failed");
  }
}

void loop() {
  float celsius;
  // put your main code here, to run repeatedly:
  celsius=getWaterTemp();//Temperature is read from the sensor
  // Condition to switch the motor and heater state
  if (celsius <= Min_Temp) { 
    Turn_Heater_ON();
  }
  else if (celsius >= Max_Temp) {
    Turn_Heater_OFF();
  }
}

void logData(String data) {
  logFile.write(data);
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


void Turn_Heater_ON() {
  digitalWrite(6, HIGH); //Trigger the signal for HEATER ON
  digitalWrite(7, LOW); //Trigger the signal for CIRCULATOR MOTOR OFF
  digitalWrite(5, LOW); //Trigger the signal for AERATOR MOTOR OFF
}

void Turn_Heater_OFF() {
  digitalWrite(6, LOW); //Trigger the signal for HEATER OFF
  digitalWrite(7, HIGH); //Trigger the signal for CIRCULATOR MOTOR ON
  digitalWrite(5, LOW); //Trigger the signal for AERATOR MOTOR ON
}
