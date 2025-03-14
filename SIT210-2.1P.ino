#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>           // For ESP32 (use <ESP8266WiFi.h> for ESP8266)
#include <ThingSpeak.h>     // ThingSpeak library

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Quang Huy";          //  Wi-Fi SSID
const char* password = "Danang040903";  //  Wi-Fi password

// ThingSpeak API credentials
unsigned long myChannelNumber = 2873932; //  ThingSpeak Channel ID
const char* myWriteAPIKey = "V5SAY84HH3R25CVX"; //  Write API Key

WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
  Serial.println("DHT22 test nâng cao!");
  dht.begin();
}

void loop() {  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Lỗi đọc cảm biến!");
    return;
  }
  
  // Write data to ThingSpeak
  ThingSpeak.setField(1, t); // Field 1: Temperature
  ThingSpeak.setField(2, h);    // Field 2: Humidity

  int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (statusCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.print("Error sending data. HTTP error code: ");
    Serial.println(statusCode);
  }

  delay(15000);
}