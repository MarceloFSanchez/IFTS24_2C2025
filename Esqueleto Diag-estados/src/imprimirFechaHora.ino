void imprimirFechaHora(){
  //Imprimimos la fecha
  print2digits(rtc.getDay());
  debugSerial.print("/");
  print2digits(rtc.getMonth());
  debugSerial.print("/");
  print2digits(rtc.getYear());
  debugSerial.print(" ");

  //Imprmimos la hora
  print2digits(rtc.getHours());
  debugSerial.print(":");
  print2digits(rtc.getMinutes());
  debugSerial.print(":");
  print2digits(rtc.getSeconds());
  debugSerial.println();

  delay(1000);
}