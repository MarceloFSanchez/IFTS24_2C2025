void loraSendCommand(char *command, int timeout, int numResp){
/*
   Envia un comando al modulo LoRa y espera la respuesta
*/
  loraClearReadBuffer();
  debugSerial.println(command);
  loraSerial.println(command);
  for (int i = 0; i < numResp; i++){
    loraWaitResponse(timeout);
  }	 
  
}
