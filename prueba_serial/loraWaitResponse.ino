void loraWaitResponse(int timeout){
/*
   Espera la respuesta del modulo LoRa y la imprime en el puerto de debug
*/
  //size_t readed = 0;

  loraSerial.setTimeout(timeout);

  readed = loraSerial.readBytesUntil('\n', response, 1000); //RESPONSE_LEN);
  if (readed > 0) {
    response[readed - 1] = '\0'; // set \r to \0
    debugSerial.println(response);
  }
  else
    debugSerial.println("Response timeout");
}
