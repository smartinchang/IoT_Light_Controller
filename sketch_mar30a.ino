#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "TEKY OFFICE";
const char* password = "Teky@2018";
WiFiClient client;

// ThingSpeak Settings
unsigned long ChannelNumber = 1673641;
const char * ReadAPIKey = "X96PCNXEHWISWVKL";
const int FieldNumber = 1;
int statusCode;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\r\nWiFi connected");
  ThingSpeak.begin(client);
}

void loop() {
  long data = ThingSpeak.readFloatField(ChannelNumber, FieldNumber, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200) {
    Serial.println("Data read from ThingSpeak: " + String(data, 9));
    if (data == 0) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  } else {
    Serial.println("Unable to read channel/No internet connection");
  }
  delay(1000);
}
