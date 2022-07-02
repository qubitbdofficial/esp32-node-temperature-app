import express from "express";
import cors from "cors";
import dotenv from "dotenv";
import { MqttHandelr } from "./mqtt_handler";
import { connectDB } from "../config/db";

dotenv.config();

const app = express();
app.use(cors({ origin: "*" }));
const PORT = process.env.PORT || 4000;

const mqttClient = new MqttHandelr();
mqttClient.connect();

app.get("/", (_, res) => {
  res.json({ msg: "Hello friend" });
});

connectDB().then(() => {
  app.listen(PORT, () => console.log(""));
});
