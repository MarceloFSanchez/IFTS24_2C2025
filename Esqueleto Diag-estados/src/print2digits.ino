void print2digits(int number) {
  if (number < 10) {
    debugSerial.print("0"); // print a 0 before if the number is < than 10
  }
  debugSerial.print(number);
}