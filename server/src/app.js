import express from "express";
import { MqttHandelr } from "./mqtt_handler";
import cors from "cors";

const app = express();
app.use(cors({ origin: "*" }));
const PORT = process.env.PORT || 4000;

const mqttClient = new MqttHandelr();
mqttClient.connect();

app.get("/", (_, res) => {
  res.json({ msg: "Hello friend" });
});

app.listen(PORT, () => console.log(""));
