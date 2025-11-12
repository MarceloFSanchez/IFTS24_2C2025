void configInit(){
// Carga de configuración inicial en estado INIT
  loraSendCommand("mac set adr on", loraTimeout, 1);
  if (OK.equals(response))
    debugSerial.println("Adaptive Data Rate activado");
  loraSendCommand("mac set rxdelay1 5000", loraTimeout, 1);
  if (OK.equals(response))
    debugSerial.println("Rxdelay1 configurado en 5 segundos");

}
