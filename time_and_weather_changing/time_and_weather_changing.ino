#include <Wire.h>
#include "rgb_lcd.h"
#include <Bridge.h>
#include <HttpClient.h>
#include <ArduinoJson.h>

// Initialize the LCD
rgb_lcd lcd;

// Button and buzzer setup
#define button 4    
#define BUZZER 6  

// Alarm and time variables
int alarm_clock_time_hours = 7;
int alarm_clock_time_minutes = 23;
int time_hours = 23;
int time_minutes = 59;
int button_state = 0;  
int k = 0;
int last_button_state = 0;  

// LCD color (default white)
int colorR = 255, colorG = 255, colorB = 255;

// Weather API details
String city = "Sligo";  
String apiKey = "7ecbb0c17a028641084777254799ed61";  
float temperature = 0.0;  // Store fetched temperature
bool showTime = true;  // Toggle display between time and weather

void setup() {
    // Initialize LCD and Serial
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    Serial.begin(9600);
   
    // Button and buzzer setup
    pinMode(BUZZER, OUTPUT);
    pinMode(button, INPUT);

    // Initialize Bridge for API requests
    Bridge.begin();
}

void loop() {
    button_state = digitalRead(button);

    // Check if alarm time matches the current time
    if ((alarm_clock_time_hours == time_hours) && (alarm_clock_time_minutes == time_minutes) && k == 0) {
        tone(BUZZER, 1000);  // Play the alarm tone
    }

    // Stop the buzzer when button is pressed
    if (button_state == HIGH && last_button_state == LOW) {
        noTone(BUZZER);
        delay(100);  // Button debounce delay
    }
    last_button_state = button_state;

    // Toggle display every 10 seconds
    displayTime();
    delay(5000);
    
    fetchAndDisplayWeather();    

    delay(5000);  // Update every second   
    updateTime();
}

// Function to display time on LCD
void displayTime() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
   
    if (time_hours < 10) lcd.print("0");
    lcd.print(time_hours);
    lcd.print(":");
    if (time_minutes < 10) lcd.print("0");
    lcd.print(time_minutes);
}

// Function to update time every minute
void updateTime() {
    k=k+10;
    if (k == 60) {
        time_minutes++;
        k = 0;
    }

    if (time_minutes == 60) {
        time_hours++;
        time_minutes = 0;
    }

    if (time_hours == 24) {
        time_hours = 0;
        time_minutes = 0;
    }
}

// Function to fetch and display weather
void fetchAndDisplayWeather() {
lcd.clear();
lcd.print("Weather");
}
