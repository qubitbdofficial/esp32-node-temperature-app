import mqtt from "mqtt";

export class MqttHandelr {
  constructor() {
    this.mqttClient = null;
    this.host = "mqtt://broker.hivemq.com";
  }

  connect() {
    this.mqttClient = mqtt.connect(this.host, {
      username: "rafSync_Ad27",
      password: "12345678",
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
    this.mqttClient.on("message", function (topic, message) {
      switch (topic) {
        case "roomTemp":
          console.log(JSON.parse(message.toString()));
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
