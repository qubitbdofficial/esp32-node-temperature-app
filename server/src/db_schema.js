import mongoose from "mongoose";

const TemparetureSchema = mongoose.Schema(
  {
    tempareture: {
      type: Number,
    },
  },
  { timestamps: true }
);

// making the mogoose model
const Tempareture = mongoose.model("Tempareture", TemparetureSchema);

export default Tempareture;
