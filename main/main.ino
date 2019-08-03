#include <SPI.h>
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define WATER_TEMP 5
const int chipSelect = 4;

OneWire oneWire(WATER_TEMP);
// BUS
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  
  SD.begin(chipSelect);
  File logFile = SD.open("logger.txt", FILE_WRITE);

  if (!logFile) {
    Serial.println("SD Failed");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

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
