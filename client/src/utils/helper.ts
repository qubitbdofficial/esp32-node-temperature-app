export function padTo2Digits(num: number) {
  return String(num).padStart(2, "0");
}

export const hoursAndMinutes = (date: Date) =>
  padTo2Digits(date.getHours()) + ":" + padTo2Digits(date.getMinutes());

console.log(hoursAndMinutes); // 👉️ 08:09
