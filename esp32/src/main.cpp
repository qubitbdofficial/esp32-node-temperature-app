#include <Arduino.h>
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
PubSubClient client(espClient);

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
    while (!client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (client.connect("ESP32_clientID", mqtt_username, mqtt_password)) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("outTopic", "Nodemcu connected to MQTT");
            // ... and resubscribe
            client.subscribe("inTopic");

        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void connectmqtt() {
    client.connect("ESP32_clientID", mqtt_username, mqtt_password); // ESP will connect to mqtt broker with clientID
    {
        Serial.println("connected to MQTT");
        // Once connected, publish an announcement...

        // ... and resubscribe
        client.subscribe("inTopic"); // topic=Demo
        client.publish("outTopic", "connected to MQTT");

        if (!client.connected()) {
            reconnect();
        }
    }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    // for (int i = 0; i < length; i++) {
    //     Serial.print((char)payload[i]);
    // }
    // if ((char)payload[0] == 'O' && (char)payload[1] == 'N') {
    //     // on
    //     Serial.println("on");
    //     client.publish("outTopic", "LED turned ON");
    // } else if ((char)payload[0] == 'O' && (char)payload[1] == 'F' && (char)payload[2] == 'F') {
    //     // off
    //     Serial.println(" off");
    //     client.publish("outTopic", "LED turned OFF");
    // }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    initWifi();
    dht.begin();

    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(mqttCallback);
    connectmqtt();
    // publish and subscribe
    client.publish("mytopic", "Hi EMQX I'm ESP32 ^^");
    client.subscribe("message");
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    float f = dht.readTemperature(true);
}
