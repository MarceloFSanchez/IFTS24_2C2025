/*
   Vacia el buffer de recepcion desde el modulo LoRa
*/
void loraClearReadBuffer()
{
  while (loraSerial.available())
  loraSerial.read();
}
