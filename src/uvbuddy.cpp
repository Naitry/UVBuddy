#include "uvb_logger.h"

void setup() {
  Serial.begin(9600);

  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Error initializing SD card.");
    while (true); // Loop indefinitely if SD card initialization fails
  }

  Serial.println("SD card initialized.");

  // Initialize LCD display
  lcd.begin(16, 2); // Assuming a 16x2 LCD display
  lcd.setCursor(0, 0);
  lcd.print("UVB Index:");

  // Initialize RGB LED pins as outputs
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  Serial.println("Ready to log UVB Index data.");
}

void loop() {
  // Read analog voltage from ADC pin
  int adcValue = analogRead(ADC_PIN);

  // Convert ADC value to voltage (assuming 5V reference)
  float voltage = adcValue * (5.0 / 1023.0);

  // Convert voltage to UVB index (example conversion, adjust as needed)
  float uvbIndex = voltage * 10.0; // Example conversion factor

  // Update LCD display with UVB index and danger rating
  lcd.setCursor(0, 1);
  lcd.print(uvbIndex);
  lcd.print(" UVB");

  // Determine danger rating based on UVB index
  int dangerRating = getDangerRating(uvbIndex);

  // Light up RGB LED based on danger rating
  updateRGBLED(dangerRating);

  // Log UVB index data to SD card
  logData(voltage, uvbIndex, dangerRating);

  // Delay between readings (adjust as needed)
  delay(1000); // 1 second delay
}

int getDangerRating(float uvbIndex) {
  if (uvbIndex < 2.5) {
    return 1; // Low danger
  } else if (uvbIndex >= 2.5 && uvbIndex < 5.0) {
    return 2; // Moderate danger
  } else if (uvbIndex >= 5.0 && uvbIndex < 7.5) {
    return 3; // High danger
  } else {
    return 4; // Very high danger
  }
}

void updateRGBLED(int dangerRating) {
  // Turn off all LEDs initially
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);

  // Set LED color based on danger rating
  switch (dangerRating) {
    case 1: // Low danger
      digitalWrite(LED_GREEN_PIN, HIGH); // Green LED
      break;
    case 2: // Moderate danger
      digitalWrite(LED_GREEN_PIN, HIGH); // Green LED
      digitalWrite(LED_BLUE_PIN, HIGH);  // Blue LED
      break;
    case 3: // High danger
      digitalWrite(LED_RED_PIN, HIGH);   // Red LED
      digitalWrite(LED_GREEN_PIN, HIGH); // Green LED
      break;
    case 4: // Very high danger
      digitalWrite(LED_RED_PIN, HIGH);   // Red LED
      digitalWrite(LED_GREEN_PIN, HIGH); // Green LED
      digitalWrite(LED_BLUE_PIN, HIGH);  // Blue LED
      break;
    default: // Unknown danger rating
      break;
  }
}

void logData(float voltage, float uvbIndex, int dangerRating) {
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Voltage (V): ");
    dataFile.print(voltage);
    dataFile.print("\tUVB Index: ");
    dataFile.print(uvbIndex);
    dataFile.print("\tDanger Rating: ");
    dataFile.println(dangerRating);
    dataFile.close();
  } else {
    Serial.println("Error opening datalog.txt for logging.");
  }
}