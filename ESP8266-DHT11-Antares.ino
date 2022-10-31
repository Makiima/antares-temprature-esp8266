#include <AntaresESP8266HTTP.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11


#define ACCESSKEY "b8b807bc6c73e929:b26675f82ac3bfae"
#define projectName "TubesPPI78"
#define deviceName "FireDHT11"

#define WIFISSID "queue"
#define PASSWORD "lolololololol"

DHT dht(DHTPIN, DHTTYPE);

AntaresESP8266HTTP antares(ACCESSKEY);


void setup()
{
  Serial.begin(115200); 
  WiFi.begin(WIFISSID, PASSWORD);
  pinMode(14, OUTPUT);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println("Connected");

  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);

  dht.begin();
  
}

void loop()
{
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  String ON = "Kipas Menyala";
  String OFF = "Kipas Mati";
  Serial.print("Suhu : ");
  Serial.println(temp);
  antares.add("Temperature", temp);
  if (temp > 34){
     digitalWrite(14, LOW);
     delay(5000);
     antares.add("Status", ON);
  }
  else {
     digitalWrite(14, HIGH);
     antares.add("Status", OFF);
  }

  //Variabel data untuk antares

  //kirim data
  antares.send(projectName, deviceName);
  delay(5000);
  
}
