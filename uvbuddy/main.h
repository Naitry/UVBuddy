#ifndef UVB_LOGGER_H
#define UVB_LOGGER_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

// Constants for pin assignments
const int ADC_PIN = A0;
const int SD_CS_PIN = 10;
const int LED_RED_PIN = 2;
const int LED_GREEN_PIN = 3;
const int LED_BLUE_PIN = 4;
const int LCD_RS_PIN = 7;
const int LCD_EN_PIN = 8;
const int LCD_D4_PIN = 9;
const int LCD_D5_PIN = 11;
const int LCD_D6_PIN = 12;
const int LCD_D7_PIN = 13;

// Function prototypes
void setupSDCard();
void setupLCD();
int getDangerRating(float uvbIndex);
void updateRGBLED(int dangerRating);
void logData(float voltage, float uvbIndex, int dangerRating);

#endif // UVB_LOGGER_H