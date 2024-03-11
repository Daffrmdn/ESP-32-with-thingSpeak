#include <WiFi.h>
#include "DHTesp.h"  
#include <HTTPClient.h>

HTTPClient httpKita;

const int DHT_PIN = 14; // Your pin in board ESP 32
DHTesp dhtSensor;  

float hum, temp ; 

#define ssid "Your ssid/wifi name"
#define password "pass wifi" 

String serverName = "Your API(GET) in thinSpeak";


void connectToWifi(){
    WiFi.begin(ssid, password); // connect to wifi ssid 
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("waiting process");
        delay(200);
    }
    Serial.println("ESP telah terkoneksi");
}

void setup() {
    Serial.begin(115200);
    Serial.println("Hello, ESP 32");
    WiFi.mode(WIFI_STA);
    connectToWifi();

    // Inisialisasi sensor DHT
    dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  hum = data.humidity;
  temp = data.temperature; 

  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(hum); 

  // req to server 
  String url = serverName + "&field1=" + String(temp) + "&field2=" + String(hum);
  httpKita.begin(url.c_str());
  int httpResponseCode = httpKita.GET(); 
  if (httpResponseCode > 0){
    Serial.println("ESP telah mengirim data"); 
  } 
  else {
    Serial.println("Server error");
  }

  httpKita.end();

  delay(500); 
}
