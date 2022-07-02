#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// MQTT Broker
const char *mqtt_broker = "broker.hivemq.com";
const char *topic = "mytopic";
const char *mqtt_username = "rafSync_Ad27";
const char *mqtt_password = "12345678";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient mqttclient(espClient);

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

void reconnect() {
    while (!mqttclient.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (mqttclient.connect("ESP32_clientID", mqtt_username, mqtt_password)) {
            Serial.println("connected");

            float roomTemperatureInDegree = dht.readTemperature();
            char temString[8];
            dtostrf(roomTemperatureInDegree, 1, 2, temString);
            mqttclient.publish("roomTemp", temString);

        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttclient.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void connectmqtt() {
    mqttclient.connect("ESP32_clientID", mqtt_username, mqtt_password); // ESP will connect to mqtt broker with clientID
    {
        Serial.println("connected to MQTT");

        float roomTemperatureInDegree = dht.readTemperature();
        char temString[8];
        dtostrf(roomTemperatureInDegree, 1, 2, temString);
        mqttclient.publish("roomTemp", temString);

        if (!mqttclient.connected()) {
            reconnect();
        }
    }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    initWifi();
    dht.begin();

    mqttclient.setServer(mqtt_broker, mqtt_port);
    mqttclient.setCallback(mqttCallback);
    connectmqtt();
}

void loop() {
    if (!mqttclient.connected()) {
        reconnect();
    }
    mqttclient.loop();
}
