#include "uvb_logger.h"

void setup() {
  Serial.begin(9600); // ???

  // Initialize I/O
  pinMode(UV_SENSE, INPUT)      // uv sensor as input 
  pinMode(SENSE_EN, OUTPUT)     // sensor enable as output 
  // initialize LEDs 

  // Initialize states 
  digitalWrite(SENSE_EN, HIGH)  // set sensor enable high 
  // initialize LEDs 

  // Initialize SD card
  if (!SD.begin(UV_SENSE)) { // if card is not present / can't be initialized 
    Serial.println("Error initializing SD card.");
    while (true); // loop indefinitely if SD card initialization fails
  }
  Serial.println("SD card initialized."); // print to Arduino serial monitor 

  // open csv log 
  // dataFile = SD.open("UV_Log.csv", FILE_WRITE);
  // if (dataFile) {
  //   dataFile.println("Timestamp,UV Index");
  //   dataFile.close();
  //   Serial.println("Data log created.");
  // } else {
  //   Serial.println("Error opening data log!");
  // }
}

void loop() {
  int uvIndex = readUVIndex();  // get UV index 
  logData(uvIndex);             // log UV index 

  Serial.println("UV Index: " + String(uvIndex));
}

int readUVIndex() {
  int uvValue = analogRead(UV_SENSE_PIN);
  // Convert analog reading to UV index (you'll need to calibrate this based on your sensor's specifications)
  int uvIndex = map(uvValue, 0, 1023, 0, 15);
  return uvIndex;
}

// void logData(int uvIndex) {
//   String dataString = getTimeStamp() + "," + String(uvIndex);
//   dataFile = SD.open("UV_Log.csv", FILE_WRITE);
//   if (dataFile) {
//     dataFile.println(dataString);
//     dataFile.close();
//   } else {
//     Serial.println("Error opening data log!");
//   }
// }

// String getTimeStamp() {
//   String timeStamp = "";
//   // Get current time (you may need to add a real-time clock module for accurate timekeeping)
//   // Example format: "YYYY-MM-DD HH:MM:SS"
//   timeStamp += "YYYY-MM-DD HH:MM:SS";
//   return timeStamp;
// }

// light up LEDs 