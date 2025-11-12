void loraWaitResponse(int timeout)
/*
   Espera la respuesta del modulo LoRa y la imprime en el puerto de debug
*/
{
  read = 0;

  loraSerial.setTimeout(timeout);

  read = loraSerial.readBytesUntil('\n', response, 1000); //RESPONSE_LEN);
  if (read > 0) {
    response[read - 1] = '\0'; // set \r to \0
    debugSerial.println(response);
  }
  else
    debugSerial.println("Response timeout");
}
