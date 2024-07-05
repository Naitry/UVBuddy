# UVBuddy, Embedded Final - Jeepers Creepers 
- [Project Proposal](https://iowa-my.sharepoint.com/:w:/r/personal/glflores_uiowa_edu/Documents/___Current%20Class%20Notes___/Embedded%20Systems/Final%20Project/Project%20Proposal.docx?d=w1a164883213d411382a67cb6917169d1&csf=1&web=1&e=GEbP55) (update link?)
- [Project Parts List](https://iowa-my.sharepoint.com/:x:/r/personal/tstffn_uiowa_edu/Documents/UVBuddy%20Parts.xlsx?d=we03a8d23e8b14841ab5d910d4a1e777e&csf=1&web=1&e=9zfQYW) (update link?)

## Table of Contents
- [Project Status](#project-status)
- [Overview](#overview)
- [Developer Documentation](#developer-documentation)
- [Results](#results) (needs updating)
- [Presentation](#presentation)
- [Next Steps](#next-steps) 

## Project Status 
This project achieved minimum viable results. [Next Steps](#next-steps) are listed below.

## Overview 
The UVBuddy is a personal UV broad spectrum sensor designed to give users real-time feedback about the UV light they are being exposed to. The exposure data will be provided through LEDs as well as collected over time into an output file.

## Developer Documentation 
The main logic for UVBuddy is located in the [`uvbuddy/arduinoSketch/main.io`](https://github.com/Naitry/UVBuddy/blob/main/uvbuddy/arduinoSketch/main.ino) file. 

Every 30 seconds, the main loop reads the UV index from the sensor, logs it in an SD card, and lights up the corresponding LEDs. 

```
void loop() 
{
  float uvIndex = readUVIndex();
  if(count % 300 == 0) { logData(count / 300, uvIndex); }
  lightUpLEDs(uvIndex);
  Serial.println("UV Index: " + String(uvIndex));  // serial debugging
  delay(10);
  count++;
}
```

The UV index is calculated by reading the voltage from the [sensor's] analog pin. Then, the voltage value linearly mapped to the correct UV index based off the graph in the sensor's datasheet.

![image](https://github.com/Naitry/UVBuddy/assets/124198528/a170f490-aa2f-482a-b860-27515e62f609)

The data of UV indexes at every 30 second time stepped is logged in an [SD card] using the [library].

## Results 
(needs updating) See [Presentation](#presentation). 

## Presentation
- [Youtube Video](https://www.youtube.com/watch?v=eEAE1UoE34o&t=2s)

![Picture1](https://github.com/Naitry/UVBuddy/assets/124198528/778416e9-3bb4-41ad-8dfc-6aa972a2244e)

## Next Steps 
- catalogue total UV exposure over a specific time period
- bluetooth integration for recording data 
- develop a wearable prototype
- develop an app for easy data access 
