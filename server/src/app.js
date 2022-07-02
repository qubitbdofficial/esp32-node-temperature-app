import express from "express";
import { MqttHandelr } from "./mqtt_handler";
import cors from "cors";

const app = express();
app.use(cors({ origin: "*" }));
const PORT = process.env.PORT || 4000;

const mqttClient = new MqttHandelr();
mqttClient.connect();

app.get("/", (req, res) => {
  res.json({ msg: "hi" });
});

app.post("/send-mqtt", (req, res) => {
  mqttClient.sendMessage(req.body.message);
  res.status(200).send("Message sent to mqtt");
});

app.listen(PORT, () => console.log("App running"));
