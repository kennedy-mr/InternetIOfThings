# InternetOfThings
# Screen time reducing alarm clock
## Table of contents
* [Description](#Description)
* [Features](#Features)
* [Hardware Requirements](#Hardware-Requirements)
* [Code Overview](#Code-Overview)
  1. [Alarm Clock Code](#Alarm-Clock-Code)
  2. [Weather API Integration](#Weather-API-Integration)
* [Usage](#Usage)
* [Contact](#Contact)
  
## Description
This project is a screen-time reducing alarm clock that is designed to encourage healthier sleep habits. The device features an LCD display, a buzzer for alarms, and integrates with a weather API to display real-time temperature updates.
## Features
* LCD display to show the current time and temperature
* Alarm clock with buzzer alert
* Button to stop the alarm
* Real-time weather updates, using OpenWeatherMap API
## Hardware Requirements
* Arduino board
* Grove LCD RGB Backlight Display
* Button module
* Buzzer
* Internet connectivity for API access
## Code Overview
### Alarm Clock Code
The alarm clock module uses an LCD screen to display the time and a buzzer that alerts the user when the alarm goes off. There is a button connected that allows the user to turn the alarm off.
```
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;  // LCD PORT I2C
#define button 4    
#define BUZZER 6  

int alarm_clock_time_hours = 7;
int alarm_clock_time_minutes = 23;
int time_hours = 23;
int time_minutes = 59;
int button_state = 0;  
int k = 0;
int last_button_state = 0;  // To store the previous button state

void setup()
{
  lcd.begin(16, 2);
  lcd.setRGB(255, 255, 255);
  pinMode(BUZZER, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop()
{
  button_state = digitalRead(button);

  if ((alarm_clock_time_hours == time_hours) && (alarm_clock_time_minutes == time_minutes) && k == 0)
  {
    tone(BUZZER, 15); // Play alarm
  }

  if (button_state == HIGH && last_button_state == LOW)
  {
    noTone(BUZZER); // Stop alarm
    delay(100);
  }

  last_button_state = button_state;
  lcd.setCursor(0, 1);
  lcd.print("Time: ");  
  lcd.print(time_hours < 10 ? "0" : "");
  lcd.print(time_hours);  
  lcd.print(":");
  lcd.print(time_minutes < 10 ? "0" : "");
  lcd.print(time_minutes);

  delay(1000);
  k++;
  if (k == 60) { time_minutes++; k = 0; }
  if (time_minutes == 60) { time_hours++; time_minutes = 0; }
  if (time_hours == 24) { time_hours = 0; time_minutes = 0; }
}
```
### Weather API Integration
This fetches real-time weather data and will display it on the LCD screen.
```
#include <Bridge.h>
#include <HttpClient.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <ArduinoJson.h>

rgb_lcd lcd;
String city = "Sligo";
String apiKey = "YOUR_API_KEY";

void setup() {
    Bridge.begin();
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.setRGB(0, 255, 0);
    lcd.setCursor(0, 0);
    lcd.print("Weather Fetcher");
    delay(2000);
}

void loop() {
    HttpClient client;
    String url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";
    client.get(url);

    String response = "";
    while (client.available()) {
        char c = client.read();
        response += c;
    }

    StaticJsonDocument<1024> doc;
    deserializeJson(doc, response);
    float temperature = doc["main"]["temp"];

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");
    
    delay(60000);
}
```
## Usage
Upload the code provided to your Arduino board and ensure all the hardware is connected properly. The device will then display the current time, an alarm that sounds at the correct time and will also fetch weather updates periodically.
## Contact
This is a college project, please feel free to contact us through Github.
