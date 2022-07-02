#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
void initWifi() {
    const char *ssid = "Imposter";
    const char *password = "rrrrrrrr";
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    };
    Serial.println(WiFi.localIP());
};

void setup() {
    Serial.begin(115200);
    initWifi();
    dht.begin();
}

void loop() {

    float f = dht.readTemperature(true);
    Serial.println(f);
    delay(200);
}