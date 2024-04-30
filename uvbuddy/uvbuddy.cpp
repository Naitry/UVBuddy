#include "uvbuddy.h"

void setup() {
  Serial.begin(9600); // ???

  // Initialize I/O
  pinMode(UV_SENSE, INPUT)      // uv sensor as input 
  pinMode(SENSE_EN, OUTPUT)     // uv sensor enable as output 
  // initialize LEDs 

  // Initialize states 
  digitalWrite(SENSE_EN, HIGH)  // set uv sensor enable high 

  // initialize LEDs 

  // Initialize SD card
  if (!SD.begin(UV_SENSE)) { // if card is not present / can't be initialized 
    Serial.println("Error initializing SD card.");
    while (true); // loop indefinitely if SD card initialization fails
  }
  Serial.println("SD card initialized."); // debugging 

  // Create data log 
  dataFile = SD.open("UV_Log.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Timestamp,UV Index");
    dataFile.close();
    Serial.println("Data log created.");        // debugging 
  } else {
    Serial.println("Error opening data log!");  // debugging 
  }
}

void loop() {
  int uvIndex = readUVIndex();  // get UV index 
  logData(uvIndex);             // log UV index 

  Serial.println("UV Index: " + String(uvIndex)); // debugging 
}

// https://learn.sparkfun.com/tutorials/ml8511-uv-sensor-hookup-guide/all
int getUVIndex() {
  int uvValue = analogRead(UV_SENSE);
  int refLevel = analogRead(3V3)        // analog read? I/O?
  uvVoltage / uvValue = 3.3 / refLevel` // solves? 
  float uvIntensity = mapfloat(uvVoltage, 0.99, 2.8, 0.0, 15.0); // convert the voltage to a UV intensity level
  return uvIntensity 
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void logData(int uvIndex) {
  String dataString = "timestamp_placeholder," + String(uvIndex);
  dataFile = SD.open("UV_Log.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  } else {
    Serial.println("Error opening data log!");  // debugging 
  }
}

// String getTimeStamp() {
//   String timeStamp = "";
//   // Get current time (you may need to add a real-time clock module for accurate timekeeping)
//   // Example format: "YYYY-MM-DD HH:MM:SS"
//   timeStamp += "YYYY-MM-DD HH:MM:SS";
//   return timeStamp;
// }

// light up LEDs 