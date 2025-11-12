void sendMeasures(int milimsAcumulados){
  //measure = milimsAcumulados;

  if(milimsAcumulados < 10)
    sprintf(command, "mac tx cnf 1 000%i", milimsAcumulados);
  else if(milimsAcumulados < 100)
    sprintf(command, "mac tx cnf 1 00%i", milimsAcumulados);
  else if(milimsAcumulados < 1000)
    sprintf(command, "mac tx cnf 1 0%i", milimsAcumulados);
  else
    sprintf(command, "mac tx cnf 1 %i", milimsAcumulados);



  debugSerial.println("Enviando mensaje.....:");
  loraSendCommand(command , loraTimeout, 2);
  delay(3000);
}
