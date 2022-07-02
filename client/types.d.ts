interface Responsedata {
  success: boolean;
  data?: IData[];
}

interface IData {
  _id: string;
  createdAt: string;
  tempareture: number;
  updatedAt: string;
}
