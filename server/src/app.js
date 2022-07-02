import express from "express";
import { MqttHandelr } from "./mqtt_handler";

const app = express();
const PORT = process.env.PORT || 4000;

const mqttClient = new MqttHandelr();
mqttClient.connect();

app.post("/send-mqtt", (req, res) => {
  mqttClient.sendMessage(req.body.message);
  res.status(200).send("Message sent to mqtt");
});

app.listen(PORT, () => console.log("App running"));
