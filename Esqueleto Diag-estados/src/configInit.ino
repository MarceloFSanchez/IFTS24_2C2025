void configInit(){
// Carga de configuración inicial en estado INIT
  
  uint32_t aux = TX1_DELAY;
  debugSerial.print("TX1_DELAY: "); debugSerial.println(aux);
  aux = LORA_RETXNB; 
  debugSerial.print("LORA_RETXNB: "); debugSerial.println(aux);
  aux = LORA_MSG_TIMEOUT; 
  debugSerial.print("LORA_MSG_TIMEOUT: "); debugSerial.println(aux);
  aux = TIME_MSG_GUARD; 
  debugSerial.print("TIME_MSG_GUARD: "); debugSerial.println(aux);
  aux = MSG_ATTEMPS; 
  debugSerial.print("MSG_ATTEMPS: "); debugSerial.println(aux);

  int Tx1delay = TX1_DELAY;
  int RetxNb = LORA_RETXNB;
  
  lora.sendCommand("mac set adr on", loraTimeout, 1);
  if (lora.isResponse(OKEY))
    debugSerial.println("Adaptive Data Rate activated");
    
  snprintf(command, sizeof(command), "mac set rxdelay1 %i", Tx1delay);
  lora.sendCommand(command, loraTimeout, 1);
  if (lora.isResponse(OKEY)){
    debugSerial.print("Rxdelay1 configurada en ");
    debugSerial.print(Tx1delay/1000, DEC);
  debugSerial.println(" segundos");
  }
  
  snprintf(command, sizeof(command), "mac set retx %i", RetxNb);
  lora.sendCommand(command, loraTimeout, 1);
  if (lora.isResponse(OKEY)){
    debugSerial.print("Nb Retransmitions seteado en ");
    debugSerial.println(RetxNb);
  }

}
