#include <Bridge.h>
#include <Process.h>  // For running Linux commands

const char* apiKey="7ecbb0c17a028641084777254799ed61";
const char* city="Sligo,IE";

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);

  while (!Serial);

  Serial.println("Wifi Connected");

  }

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("\nFetching Weather Date...");
  getWeatherData();
  delay(60000);

}

void getWeatherData()
{
  Process p;
  String apiUrl="http://api.openweathermap.org/data/2.5/weather?q=" ;
  apiUrl+= city;
  apiUrl+= "&APPID=";
  apiUrl+= apiKey;
  apiUrl+= "&units=metric";

  Serial.print("Requesting URL:");
  Serial.println(apiUrl);

  p.runShellCommand("curl -s\""+apiUrl+"\"");
   //run
   p.begin("curl");
  p.addParameter("-s");
  p.addParameter(apiUrl);

  p.run();
  String weatherData="";

  while (p.available())
  {
    char c=p.read();
    weatherData+=c;
  }

  Serial.println("\nRaw API Response:");
  Serial.println(weatherData);
  

  String extractedCity = extractValue(weatherData, "\"name\":\"","\"");
  String extractedTemp = extractValue(weatherData, "\"temp\":",",");

  Serial.print("City:");
  Serial.println(extractedCity);

  Serial.print("Temperature:");
  Serial.print(extractedTemp);
  Serial.println("C");

 


}
 String extractValue(String data, String key, String delimiter)
  {
  
    int start =data.indexOf(key);
    if (start== -1) return "N/A";
    start +=key.length();
    int end =data.indexOf(delimiter, start);
    if(end==-1) end =data.length();
    return data.substring(start, end);
  

  }
  
