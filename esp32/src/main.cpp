#include <Arduino.h>
#include <WiFi.h>

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
}

void loop() {
    delay(200);
}