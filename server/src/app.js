import express from "express";
import cors from "cors";
import dotenv from "dotenv";
import { MqttHandelr } from "./mqtt_handler";
import { connectDB } from "../config/db";
import Tempareture from "./db_schema";

dotenv.config();

const app = express();
app.use(cors({ origin: "*" }));
const PORT = process.env.PORT || 4000;

const mqttClient = new MqttHandelr();
mqttClient.connect();

app.get("/", (_, res) => {
  res.json({ msg: "Hello friend" });
});

app.get("/temparetures", async (req, res) => {
  try {
    // get all the data from db
    const temparetureData = await Tempareture.find().sort({
      createdAt: "asc",
    });

    //   if there is no data then show success false
    if (!temparetureData) {
      res.json({
        success: false,
      });
    }

    // response with the correct data
    res.status(200).json({
      success: true,
      data: temparetureData,
    });
  } catch (error) {
    res.status(500).json({
      success: false,
      error: error.message,
    });
  }
});

connectDB().then(() => {
  app.listen(PORT, () => console.log(`🚀 App started`.bgYellow));
});
