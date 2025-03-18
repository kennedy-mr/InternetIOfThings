#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;	//LCD PORT 12c
#define button 4  	//d4
#define BUZZER 6  //d6
	
#define LED 7 

int alarm_clock_time_hours = 7;
int alarm_clock_time_minutes = 23;
int time_hours = 7; 
int time_minutes = 21; 
int button_state = 0;  
int k=0;
int last_button_state = 0;  // To store the previous button state
int colorR = 255;
int colorG = 51;
int colorB = 204;

void setup() 
{
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  
  // Set up the buzzer pin:
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);

  // Set the button pin as input:
  pinMode(button, INPUT);
  pinMode(LED,OUTPUT);    //Sets the pinMode to Output 
}
 
void loop() 
{
  // Read the button state:
  button_state = digitalRead(button);

  // Check if the alarm time matches the current time:
  if ((alarm_clock_time_hours == time_hours) && (alarm_clock_time_minutes == time_minutes)&&k==0) 
  {
    tone(BUZZER, 15); // Play the tone (alarm sound)    
  }

  // If the button is pressed, stop the buzzer:
  if (button_state == HIGH && last_button_state == LOW) // Detecting button press
  {
    noTone(BUZZER); // Stop the buzzer sound
    digitalWrite(LED, LOW);  //Sets the voltage to low
    delay(100); // Small delay to debounce the button press
  }

  // Update last button state:
  last_button_state = button_state;

  // Display the time on the LCD in HH:MM format:
  lcd.setCursor(0, 1);
  lcd.print("Time: ");  
  if (time_hours < 10) { // Add leading zero for single-digit hours
    lcd.print("0");
  }
  lcd.print(time_hours);  
  lcd.print(":");
  if (time_minutes < 10) { // Add leading zero for single-digit minutes
    lcd.print("0");
  }
  lcd.print(time_minutes);

  // Wait for 1 second before updating the time:
  delay(1000);
  if ((alarm_clock_time_hours == time_hours) && (alarm_clock_time_minutes-1 == time_minutes)&&k==0) 
  {
    
    digitalWrite(LED, HIGH); //Sets the voltage to high
  }

  // Increment the time:
  k++;
  if (k == 60) 
  {
    time_minutes++;
    k = 0;
  }

  if (time_minutes == 60) 
  {
    time_hours++;
    time_minutes = 0;
  }

  // Wrap the time back to 1:00 if it exceeds 12:59:
  if (time_hours == 24) 
  {
    time_hours = 0;
    time_minutes = 0;
  }
  }

