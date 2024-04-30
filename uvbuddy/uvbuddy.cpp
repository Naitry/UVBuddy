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

void lightUpLEDs(int uvIndex) {
  // Determine which LED(s) to light up based on UV index value
  if (uvIndex >= 12) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, HIGH)
    digitalWrite(LED_6, HIGH)
    digitalWrite(LED_7, HIGH)
    digitalWrite(LED_8, HIGH)
    digitalWrite(LED_9, HIGH)
    digitalWrite(LED_10, HIGH)
    digitalWrite(LED_11, HIGH)
    digitalWrite(LED_12, HIGH)
  } else if (uvIndex >= 11) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, HIGH)
    digitalWrite(LED_6, HIGH)
    digitalWrite(LED_7, HIGH)
    digitalWrite(LED_8, HIGH)
    digitalWrite(LED_9, HIGH)
    digitalWrite(LED_10, HIGH)
    digitalWrite(LED_11, HIGH)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 10) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, HIGH)
    digitalWrite(LED_6, HIGH)
    digitalWrite(LED_7, HIGH)
    digitalWrite(LED_8, HIGH)
    digitalWrite(LED_9, HIGH)
    digitalWrite(LED_10, HIGH)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 9) {
  digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, HIGH)
    digitalWrite(LED_6, HIGH)
    digitalWrite(LED_7, HIGH)
    digitalWrite(LED_8, HIGH)
    digitalWrite(LED_9, HIGH)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 8) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, HIGH)
    digitalWrite(LED_6, HIGH)
    digitalWrite(LED_7, HIGH)
    digitalWrite(LED_8, HIGH)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 7) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, HIGH)
    digitalWrite(LED_6, HIGH)
    digitalWrite(LED_7, HIGH)
    digitalWrite(LED_8, LOW)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 6) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, HIGH)
    digitalWrite(LED_6, HIGH)
    digitalWrite(LED_7, LOW)
    digitalWrite(LED_8, LOW)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 5) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, HIGH)
    digitalWrite(LED_6, LOW)
    digitalWrite(LED_7, LOW)
    digitalWrite(LED_8, LOW)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 4) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, HIGH)
    digitalWrite(LED_5, LOW)
    digitalWrite(LED_6, LOW)
    digitalWrite(LED_7, LOW)
    digitalWrite(LED_8, LOW)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 3) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, HIGH)
    digitalWrite(LED_4, LOW)
    digitalWrite(LED_5, LOW)
    digitalWrite(LED_6, LOW)
    digitalWrite(LED_7, LOW)
    digitalWrite(LED_8, LOW)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 2) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH)
    digitalWrite(LED_3, LOW)
    digitalWrite(LED_4, LOW)
    digitalWrite(LED_5, LOW)
    digitalWrite(LED_6, LOW)
    digitalWrite(LED_7, LOW)
    digitalWrite(LED_8, LOW)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else if (uvIndex >= 1) {
    digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, LOW)
    digitalWrite(LED_3, LOW)
    digitalWrite(LED_4, LOW)
    digitalWrite(LED_5, LOW)
    digitalWrite(LED_6, LOW)
    digitalWrite(LED_7, LOW)
    digitalWrite(LED_8, LOW)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  } else {
    digitalWrite(LED_1, LOW)
    digitalWrite(LED_2, LOW)
    digitalWrite(LED_3, LOW)
    digitalWrite(LED_4, LOW)
    digitalWrite(LED_5, LOW)
    digitalWrite(LED_6, LOW)
    digitalWrite(LED_7, LOW)
    digitalWrite(LED_8, LOW)
    digitalWrite(LED_9, LOW)
    digitalWrite(LED_10, LOW)
    digitalWrite(LED_11, LOW)
    digitalWrite(LED_12, LOW)
  }
}