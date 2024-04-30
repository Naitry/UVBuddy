#ifndef UVB_BUDDY_H
#define UVB_BUDDY_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// UV sensor pin assignments 
#define UV_SENSE = 13     // pin 13
#define SENSE_EN = 14     // pin 14 

// SD card pin assignments (???)
#define SD_CLK = 30   // pin 30
#define SD_MOSI = 37  // pin 37
#define SD_MISO = 31  // pin 31 

// LED pin assignments 
#define LED_1 = 8   // pin 8
#define LED_2 = 36  // pin 36
#define LED_3 = 11  // pin 11
#define LED_4 = 12  // pin 12
#define LED_5 = 29  // pin 29
#define LED_6 = 24  // pin 24
#define LED_7 = 9   // pin 9
#define LED_8 = 10  // pin 10 
#define LED_9 = 33  // pin 33
#define LED_10 = 16 // pin 16
#define LED_11 = 23 // pin 23 
#define LED_12 = 26 // pin 26

// Function prototypes (???)
int readUVIndex();
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
void logData(int uvIndex);
void lightUpLEDs(int uvIndex);

#endif // UVB_BUDDY_H