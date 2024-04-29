#ifndef UVB_LOGGER_H
#define UVB_LOGGER_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

// Constants for pin assignments
const int ADC_PIN = A0;

// LED pin assignments 
const int LED_1 = 8   // pin 8
const int LED_2 = 36  // pin 36
const int LED_3 = 11  // pin 11
const int LED_4 = 12  // pin 12
const int LED_5 = 29  // pin 29
const int LED_6 = 24  // pin 24
const int LED_7 = 9   // pin 9
const int LED_8 = 10  // pin 10 
const int LED_9 = 33  // pin 33
const int LED_10 = 16 // pin 16
const int LED_11 = 23 // pin 23 
const int LED_12 = 26 // pin 26



// Function prototypes
void setupSDCard();
void setupLCD();
int getDangerRating(float uvbIndex);
void updateRGBLED(int dangerRating);
void logData(float voltage, float uvbIndex, int dangerRating);

#endif // UVB_LOGGER_H