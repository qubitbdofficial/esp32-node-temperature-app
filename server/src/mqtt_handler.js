import mqtt from "mqtt";
import Tempareture from "./db_schema";

export class MqttHandelr {
  constructor() {
    this.mqttClient = null;
    this.host = process.env.MQTT_HOST;
  }

  connect() {
    this.mqttClient = mqtt.connect(this.host, {
      username: process.env.MQTT_USERNAME,
      password: process.env.MQTT_PASSWORD,
    });

    // Mqtt error calback
    this.mqttClient.on("error", (err) => {
      console.log(err);
      this.mqttClient.end();
    });

    // Connection callback
    this.mqttClient.on("connect", () => {
      // console.log(`mqtt client connected`);
    });

    this.mqttClient.subscribe("roomTemp", (err) => {
      console.log(err);
    });

    this.mqttClient.subscribe("reconnect", (err) => {
      console.log(err);
    });

    // When a message arrives, do magic
    this.mqttClient.on("message", async (topic, message) => {
      switch (topic) {
        case "roomTemp":
          try {
            // Save the record to mongodb
            await Tempareture.create({
              tempareture: message,
            });
          } catch (error) {
            console.log(`${error}`.bgRed);
          }

          break;
        default:
          break;
      }
    });

    this.mqttClient.on("close", () => {
      console.log(`mqtt client disconnected`);
    });
  }

  // Sends a mqtt message to topic: mytopic
  sendMessage(message) {
    this.mqttClient.publish("mytopic", message);
  }
}
