#ifndef UVB_BUDDY_H
#define UVB_BUDDY_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// UV sensor pin assignments   
const int UV_SENSE = 14;// gpio 14

// LED pin assignments 
const int LED_1 = 32;   // gpio 32
const int LED_2 = 22;   // gpio 22
const int LED_3 = 26;   // gpio 26
const int LED_4 = 27;   // gpio 27
const int LED_5 = 5;    // gpio 5
const int LED_6 = 2;    // gpio 2

const int LED_7 = 33;   // gpio 33
const int LED_8 = 25;   // gpio 25 
const int LED_9 = 21;   // gpio 21
const int LED_10 = 13;  // gpio 13
const int LED_11 = 15;  // gpio 15 
const int LED_12 = 4;   // gpio 4

// SD card pin assignments 
const int SD_CLK = 18;  // gpio 18
const int SD_CS = 20; // gpio 19 
const int SD_MOSI = 23; // gpio 23
const int SD_MISO = 19; // gpio 19 

void setup() {
  Serial.begin(9600); // ... 

  // Initialize I/O
  pinMode(UV_SENSE, INPUT);     // input from uv sensor 
  pinMode(LED_1, OUTPUT);       // output to all LEDs
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  pinMode(LED_8, OUTPUT);
  pinMode(LED_9, OUTPUT);
  pinMode(LED_10, OUTPUT);
  pinMode(LED_11, OUTPUT);
  pinMode(LED_12, OUTPUT);
  
  // Initialize states 
  digitalWrite(SENSE_EN, HIGH); // set high uv sensor enable
  digitalWrite(LED_1, LOW);     // set low all LEDs 
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
  digitalWrite(LED_6, LOW);
  digitalWrite(LED_7, LOW);
  digitalWrite(LED_8, LOW);
  digitalWrite(LED_9, LOW);
  digitalWrite(LED_10, LOW);
  digitalWrite(LED_11, LOW);
  digitalWrite(LED_12, LOW);

  // Initialize SD card (???)
  if (!SD.begin(SD_CS)) { // if card is not present / can't be initialized (???)
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

// Main loop to read UV index, log it, and light up LEDs 
void loop() {
  int uvIndex = readUVIndex();  // read and calculate UV index 
  logData(uvIndex);             // log UV index in csv file 
  lightUpLeds(uvIndex);

  Serial.println("UV Index: " + String(uvIndex)); // debugging 
  delay(1000); // replace with data logging interval (...)
}

// -- I don't fully understand this -- 
// Returns UV intensity value in mW/cm^2
// Source: https://learn.sparkfun.com/tutorials/ml8511-uv-sensor-hookup-guide/all 
int readUVIndex() {
  int uvValue = analogRead(UV_SENSE);
  int refLevel = analogRead(3V3);       
  uvVoltage / uvValue = 3.3 / refLevel;
  float uvIntensity = mapfloat(uvVoltage, 0.99, 2.8, 0.0, 15.0); // convert the voltage to a UV intensity (mW/cm^2)
  return uvIntensity; 
}

// The Arduino Map function but for floats 
// Linearly maps value x from input range to output range
// From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Function to log a timestamp and UV index to a csv file 
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

// Function to determine which LED(s) to light up based on UV index value
void lightUpLEDs(int uvIndex) {
  if (uvIndex >= 12) {            // if >= 12, light up 1-12 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_9, HIGH);
    digitalWrite(LED_10, HIGH);
    digitalWrite(LED_11, HIGH);
    digitalWrite(LED_12, HIGH);
  } else if (uvIndex >= 11) {     // if <12 and >=11, light up 1-11 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_9, HIGH);
    digitalWrite(LED_10, HIGH);
    digitalWrite(LED_11, HIGH);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 10) {     // if <11 and >=10, light up 1-10 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_9, HIGH);
    digitalWrite(LED_10, HIGH);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 9) {      // if <10 and >=9, light up 1-9 LEDs 
  digitalWrite(LED_1, HIGH)
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_9, HIGH);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 8) {      // if <9 and >=8, light up 1-8 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 7) {      // if <8 and >=7, light up 1-7 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 6) {      // if <7 and >=6, light up 1-6 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 5) {      // if <6 and >=5, light up 1-5 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 4) {      // if <5 and >=4, light up 1-4 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 3) {      // if <4 and >=3, light up 1-3 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 2) {      // if <3 and >=2, light up 1-2 LEDs 
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else if (uvIndex >= 1) {      // if <2 and >=1, light up 1 LED
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  } else {                        // if <1, light up 0 LEDs 
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
    digitalWrite(LED_10, LOW);
    digitalWrite(LED_11, LOW);
    digitalWrite(LED_12, LOW);
  }
}