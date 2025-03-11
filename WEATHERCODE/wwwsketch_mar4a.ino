#include <Bridge.h>
#include <HttpClient.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <ArduinoJson.h>

// Initialize the Grove LCD RGB Backlight with the I2C address (usually 0x3E for Grove LCD)
rgb_lcd lcd;

String city = "Sligo";  // City for weather
String apiKey = "7ecbb0c17a028641084777254799ed61";  // Replace with your OpenWeatherMap API key

void setup() {
    // Set up the LCD and Serial Monitor
    Bridge.begin();
    Serial.begin(9600);
    lcd.begin(16, 2);  // Initialize the LCD (16x2 screen)
    
    // Set backlight color to green (RGB color values: R, G, B)
    lcd.setRGB(0, 255, 0);  // Green color for the backlight
    
    lcd.setCursor(0, 0);
    lcd.print("Weather Fetcher");
    delay(2000);
}

void loop() {
    HttpClient client;
    String url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";

    Serial.println("Requesting weather data...");
    client.get(url);

    String response = "";
    while (client.available()) {
        char c = client.read();
        response += c;  // Read the response
    }

    // Print the raw API response to the Serial Monitor
    Serial.println(response);  // Debugging: print the raw response

    // Parse the JSON response from the API
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, response);

    if (error) {
        Serial.print("failed: ");
        Serial.println(error.f_str());
        return;  // Exit the loop early if JSON deserialization fails
    }

    float temperature = doc["main"]["temp"];  // Extract temperature

    if (isnan(temperature)) {
        Serial.println("Failed ttemperature.");
        return;  // Exit the loop if the temperature is invalid
    }

    // Display the temperature on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    Serial.println("-----");

    // Delay for 60 seconds before requesting again
    delay(60000);  // Fetch weather every 60 seconds