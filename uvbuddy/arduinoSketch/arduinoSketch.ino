#ifndef UVB_BUDDY
#define UVB_BUDDY

#include <Arduino.h>
#include "FS.h"
#include "SD_MMC.h"

#define ONE_BIT_MODE true

// forward function declarations

// LED functions
void lightUpLEDs(int uvIndex);

// SD card functions
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void createDir(fs::FS &fs, const char * path);
void removeDir(fs::FS &fs, const char * path);
void readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void renameFile(fs::FS &fs, const char * path1, const char * path2);
void deleteFile(fs::FS &fs, const char * path);


// UV sensor pin assignments   
const int UV_SENSE = 36;// gpio 14

// LED pin assignments 
const int LED_1 = 32;   // gpio 32
const int LED_2 = 22;   // gpio 22
const int LED_3 = 26;   // gpio 26
const int LED_4 = 27;   // gpio 27
const int LED_5 = 5;    // gpio 17
const int LED_6 = 0;    // gpio 2

const int LED_7 = 33;   // gpio 33
const int LED_8 = 25;   // gpio 25 
const int LED_9 = 21;   // gpio 21
const int LED_10 = 9;  // gpio 13
const int LED_11 = 19;  // gpio 15 
const int LED_12 = 4;   // gpio 4
const int ledPins[12] = {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6,
                         LED_7, LED_8, LED_9, LED_10, LED_11, LED_12};

const char* outFile = "/data.csv"; 
#endif

void setup() 
{
  Serial.begin(9600); // ... 

  // Initialize I/O
  pinMode(UV_SENSE, INPUT);     // input from uv sensor 
  
  // Set pinmodes for SD communication
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  
  // Loop through the array and set each LED's pinmode and initial state to low
  for (int i = 0; i < 12; i++) 
  {
      pinMode(ledPins[i], OUTPUT);
      digitalWrite(ledPins[i], LOW);
  }

  if(!SD_MMC.begin("/sdcard",
                   ONE_BIT_MODE))
  {
      Serial.println("Card Mount Failed");
      return;
  }
  uint8_t cardType = SD_MMC.cardType();
  
  if(cardType == CARD_NONE)
  {
      Serial.println("No SD_MMC card attached");
      return;
  }
  
  Serial.print("SD_MMC Card Type: ");
  if (cardType == CARD_MMC) { Serial.println("MMC"); } 
  else if (cardType == CARD_SD) { Serial.println("SDSC"); } 
  else if (cardType == CARD_SDHC) { Serial.println("SDHC"); } 
  else { Serial.println("UNKNOWN"); }

  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);
}

// Main loop to read UV index, log it, and light up LEDs 
void loop() 
{
  float uvIndex = readUVIndex();
  logData(uvIndex);               
  lightUpLEDs(uvIndex);  

  Serial.println("UV Index: " + String(uvIndex)); // debugging
  delay(1000);
}

// -- I don't fully understand this -- 
// Returns UV intensity value in mW/cm^2
// Source: https://learn.sparkfun.com/tutorials/ml8511-uv-sensor-hookup-guide/all 
float readUVIndex() 
{
  float uvValue = analogRead(UV_SENSE);
  float uvIntensity = mapfloat(uvValue, 0.99, 2.8, 0.0, 15.0); // convert the voltage to a UV intensity (mW/cm^2)
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
void logData(float uvIndex) 
{
  String dataString = "timestamp_placeholder," + String(uvIndex)+ "\n";
  appendFile(SD_MMC, outFile, dataString.c_str());
}


void listDir(fs::FS &fs, const char * dirname, uint8_t levels)
{
  Serial.printf("Listing directory: %s\n", dirname);
  
  File root = fs.open(dirname);
  if (!root)
  {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory())
  {
    Serial.println("Not a directory");
    return;
  }
  
  File file = root.openNextFile();
  while (file)
  {
    if (file.isDirectory())
    {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) { listDir(fs, file.path(), levels -1); }
    } 
    else 
    {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char * path)
{
  Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path)) { Serial.println("Dir created"); } 
  else { Serial.println("mkdir failed"); }
}

void removeDir(fs::FS &fs, const char * path)
{
  Serial.printf("Removing Dir: %s\n", path);
  if (fs.rmdir(path)) { Serial.println("Dir removed"); } 
  else { Serial.println("rmdir failed"); }
}

void readFile(fs::FS &fs, const char * path)
{
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.print("Read from file: ");
  while (file.available()) { Serial.write(file.read()); }
}

void writeFile(fs::FS &fs, const char * path, const char * message)
{
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) { Serial.println("Failed to open file for writing"); }
  else if (file.print(message)) { Serial.println("File written"); } 
  else { Serial.println("Write failed"); }
}

void appendFile(fs::FS &fs, const char * path, const char * message)
{
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) { Serial.println("Failed to open file for appending"); }
  else if (file.print(message)) { Serial.println("Message appended"); } 
  else { Serial.println("Append failed"); }
}

void renameFile(fs::FS &fs, const char * path1, const char * path2)
{
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) { Serial.println("File renamed"); } 
  else { Serial.println("Rename failed"); }
}

void deleteFile(fs::FS &fs, const char * path)
{
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) { Serial.println("File deleted"); } 
  else { Serial.println("Delete failed"); }
}

// String getTimeStamp() 
//{
//   String timeStamp = "";
//   // Get current time (you may need to add a real-time clock module for accurate timekeeping)
//   // Example format: "YYYY-MM-DD HH:MM:SS"
//   timeStamp += "YYYY-MM-DD HH:MM:SS";
//   return timeStamp;
// }

/**
 * @brief Activates a number of LEDs corresponding to the UV index level.
 * @param uvIndex The current UV index, determining how many LEDs to activate.
 */
void lightUpLEDs(int uvIndex) 
{
    // Loop through the array and set each LED's state based on the UV index
    for (int i = 0; i < 12; i++) 
    {
        digitalWrite(ledPins[i], i < uvIndex ? HIGH : LOW);
    }
}
