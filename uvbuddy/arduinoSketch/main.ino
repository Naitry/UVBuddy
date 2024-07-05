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

void logData(int timestampIter, float uvIndex);

// UV sensor pin assignments   
const int UV_SENSE = 36;// gpio 36

// LED pin assignments 
const int LED_1 = 27;   // gpio 27
const int LED_2 = 16;   // gpio 16
const int LED_3 = 5;    // gpio 5
const int LED_4 = 19;   // gpio 19
const int LED_5 = 3;    // gpio 3
const int LED_6 = 22;   // gpio 22

const int LED_7 = 0;    // gpio 0
const int LED_8 = 17;   // gpio 17 
const int LED_9 = 18;   // gpio 18
const int LED_10 = 21;  // gpio 21
const int LED_11 = 1;   // gpio 1 
const int LED_12 = 23;  // gpio 23

const int ledPins[12] = {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6,
                         LED_7, LED_8, LED_9, LED_10, LED_11, LED_12};

const char* outFile = "/data.csv"; 

int count;
#endif

void setup() 
{
  count = 0;
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
  pinMode(LED_1, OUTPUT);  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);  digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT);  digitalWrite(LED_3, LOW);
  pinMode(LED_4, OUTPUT);  digitalWrite(LED_4, LOW);
  pinMode(LED_5, OUTPUT);  digitalWrite(LED_5, LOW);
  pinMode(LED_6, OUTPUT);  digitalWrite(LED_6, LOW);
  pinMode(LED_7, OUTPUT);  digitalWrite(LED_7, LOW); 
  pinMode(LED_8, OUTPUT);  digitalWrite(LED_8, LOW);
  pinMode(LED_9, OUTPUT);  digitalWrite(LED_9, LOW);
  pinMode(LED_10, OUTPUT); digitalWrite(LED_10, LOW);
  pinMode(LED_11, OUTPUT); digitalWrite(LED_11, LOW);
  pinMode(LED_12, OUTPUT); digitalWrite(LED_12, LOW);

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
  if(count % 300 == 0) { logData(count / 300, uvIndex); }
  lightUpLEDs(uvIndex);
  Serial.println("UV Index: " + String(uvIndex));  // serial debugging
  delay(10);
  count++;
}

// Source: https://learn.sparkfun.com/tutorials/ml8511-uv-sensor-hookup-guide/all 
float readUVIndex() 
{
  // 0 - 4096 (12 bit adc)
  float uvValue = analogRead(UV_SENSE);
  // map input adc value to uv index
  float uvIntensity = mapfloat(uvValue, 0.0, 1900, 0.0, 12.0);
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
void logData(int timestampIter, float uvIndex) 
{
  String dataString = String(timestampIter) + "," + String(uvIndex)+ "\n";
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
  File file = fs.open(path, FILE_APPEND);
  if (!file) { Serial.println("Failed to open file for appending"); }
  else if (!file.print(message)) { Serial.println("Append failed"); }
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
    bool ledStates[12] = {0}; // Array to store the state of each LED (on or off)

    // Determine the initial state for each LED based on UV index
    for (int i = 0; i < 12; i++) 
    {
      ledStates[i] = (i < uvIndex);
    }

    // Apply the module-specific rule
    for (int i = 0; i < 6; i++) 
    {  // Only need to loop through the first 6 LEDs
        int higherIndex = i + 6;   // Corresponding higher LED in the same module
        if (ledStates[higherIndex]) 
        {
          ledStates[i] = false;  // Turn off the lower-numbered LED if the higher is ON
        }
    }

    // Now, apply the determined states to the actual LED pins
    for (int i = 0; i < 12; i++) 
    {
      pinMode(ledPins[i], OUTPUT); digitalWrite(ledPins[i], ledStates[i] ? HIGH : LOW);
    }
}
