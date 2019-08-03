#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

void setup() {
  // put your setup code here, to run once:
  
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
