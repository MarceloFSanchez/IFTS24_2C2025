#include <Arduino.h>
#include "Lora.h"

// Constructores

Lora::Lora(){
  // Se llenan con 0s_ascii = 48_dec los vectores 
  memset(_command,48,sizeof(_command)-1);
  memset(_response,48,sizeof(_response)-1);
  _timeout = LORA_TIMEOUT;
  _numResp = 1;
  _read = 0;
  memset(_statusEESAMR34,0x00,sizeof(_statusEESAMR34));
}	

// Métodos

void Lora::clearReadBuffer(){
/*
   Vacia el buffer de recepcion desde el modulo LoRa
*/

  while (loraSerial.available())
    loraSerial.read();
}

void Lora::getMacParameters(){

  // versión del firmware EESAMR34
  sendCommand("sys get ver", _timeout, 1);

// Returns the preprogrammed EUI node address.
  sendCommand("sys get hweui", _timeout, 1);

// Gets the current stored unique network device address for that
// specific end device.
  sendCommand("mac get devaddr", _timeout, 1);

// Gets the current stored globally unique identifier for that
// specific end device.
  sendCommand("mac get deveui", _timeout, 1);

// Gets the application identifier for the end device.
  sendCommand("mac get joneui", _timeout, 1);

// Gets the data rate to be used for the next transmission.
  sendCommand("mac get dr", _timeout, 1);

// Gets the output power index value.
  sendCommand("mac get pwridx", _timeout, 1);

// Gets the state of adaptive data rate for the device.
  sendCommand("mac get adr", _timeout, 1);

// Gets the number of retransmissions to be used for an uplink
// confirmed packet.
  sendCommand("mac get retx", _timeout, 1);

//Gets the interval value stored for rxdelay1.
  sendCommand("mac get rxdelay1", _timeout, 1);

// Gets the interval value stored for rxdelay2.
  sendCommand("mac get rxdelay2", _timeout, 1);

// Gets the state of the automatic reply.
  sendCommand("mac get ar", _timeout, 1);

// Gets the data rate and frequency used for the second Receive window.
  sendCommand("mac get rx2", _timeout, 1);  

// Gets the duty cycle prescaler which can only be configured by
//  the server.
  sendCommand("mac get dcycleps", _timeout, 1);

// Gets the demodulation margin as received in the last Link Check
//  Answer frame.
  sendCommand("mac get mrgn", _timeout, 1);

// Gets the number of gateways that successfully received the last
//  Link Check Request frame.
  sendCommand("mac get gwnb", _timeout, 1);

// Gets the current status of the RN2903 module.
  sendCommand("mac get status", _timeout, 1);

// Returns the current synchronization word.
  sendCommand("mac get sync", _timeout, 1);

// Returns the current uplink counter.
  sendCommand("mac get upctr", _timeout, 1);

// Returns the current downlink counter.
  sendCommand("mac get dnctr", _timeout, 1);

  delay(3000);

}


void Lora::sendCommand(const char *command, int timeout, int numResp){
/*
   Envia un comando al modulo LoRa y espera la respuesta
*/
  clearReadBuffer();
  debugSerial.println(command);
  loraSerial.println(command);
  for (int i = 0; i < numResp; i++){
    waitResponse(timeout);
  }	 
  
}

void Lora::sendCommand(const char *command, int numResp){
/*
   Envia un comando al modulo LoRa y espera la respuesta
*/
  clearReadBuffer();
  debugSerial.println(command);
  loraSerial.println(command);
  for (int i = 0; i < numResp; i++){
    waitResponse(_timeout);
  }	 
  
}

void Lora::sendCommand(int numResp){
/*
   Envia un comando al modulo LoRa y espera la respuesta
*/
  clearReadBuffer();
  debugSerial.println(_command);
  loraSerial.println(_command);
  for (int i = 0; i < numResp; i++){
    waitResponse(_timeout);
  }	 
  
}

void Lora::waitResponse(int timeout){
/*
   Espera la respuesta del modulo LoRa y la imprime en el puerto de debug
*/
  _read = 0;

  loraSerial.setTimeout(timeout);

  _read = loraSerial.readBytesUntil('\n', _response, sizeof(_response)); //RESPONSE_LEN);
  if (_read > 0) {
    _response[_read - 1] = '\0'; // set \r to \0
    debugSerial.println(_response);
  }
  else
    debugSerial.println("Response timeout");
}

bool Lora::isResponse(const String& expected){
  return expected.equals(_response);
}

void Lora::statusView(bool showTable){
// https://www.ibm.com/docs/es/aix/7.1?topic=adapters-ascii-decimal-hexadecimal-octal-binary-conversion-table

  sendCommand("mac get status", _timeout, 1);

  char *pointer = _response; //guardo el inicio del vector en un puntero
  int i, b; // iteradores
  int iterations = STATUS_EESAMR34_LEN;
  uint8_t byteAux1;
  uint8_t byteAux2;

  // recorrido del registro de estados 
  //---------------------------------------------------------- 
  for (i=0; i < iterations ; i++){
    byteAux1 = *pointer++;
    byteAux2 = *pointer++;
    // 0b01000000 funciona como máscara para identificar si es
    // mayor o igual a 65 = letra A en ascii
    // luego se resta 7 para que queden los ultimos 4 digitos
    // del byte en Hexa. 
    if(byteAux1 & 0b01000000) byteAux1 -= 7; 
    if(byteAux2 & 0b01000000) byteAux2 -= 7; 
    byteAux1 = byteAux1 & 0x0f; //descarto los primeros 4 bits
    byteAux2 = byteAux2 & 0x0f;
    _statusEESAMR34[iterations-i-1] =  (byteAux1<<4 | byteAux2);
  }

  // Se imprime tabla con resultados por puerto serie
  //---------------------------------------------------------------
  if (_read = 9 & showTable){ // Hardcodeado, si no es 9 es porque no devuelve
                             // el registro sino otro mensaje
    debugSerial.println("Registro de estados del chip EESAMR34:");
    debugSerial.println("+-------------------------------------------------------+");
    debugSerial.print("| ");
    // bits 31 a 18 ---------------------------------
    for (b = 7; b >= 0; b--){
    debugSerial.print(bitRead(_statusEESAMR34[3], b));
    debugSerial.print(" | ");
    }
    for (b = 7; b >= 2; b--){
      debugSerial.print(bitRead(_statusEESAMR34[2], b));
      debugSerial.print(" | ");
    }
    debugSerial.print("\n");
    debugSerial.println("+---+---+---+---+---+---+---+---+---+---+---+---+---+---+");
    debugSerial.println("|                       RFU                             |");
    debugSerial.println("+-----------------------------------------------------------------------+");
    debugSerial.print("| ");
    // bits 17 a 0 ----------------------------------
    for (b = 1; b >= 0; b--){
    debugSerial.print(bitRead(_statusEESAMR34[2], b));
    debugSerial.print(" | ");
    }
    for (b = 7; b >= 0; b--){
      debugSerial.print(bitRead(_statusEESAMR34[1], b));
      debugSerial.print(" | ");
    }
    for (b = 7; b >= 0; b--){
      debugSerial.print(bitRead(_statusEESAMR34[0], b));
      debugSerial.print(" | ");
    }
    debugSerial.println("");
    byteAux1 = _statusEESAMR34[0] & 0x0f; //descarto los primeros 4 bits
    //-------------------|17 |16 |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    debugSerial.println("+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+-----------+");
      debugSerial.print("| M | R | R | R | P | N | O | C | L | R | M | S | A | A |     M     | J | MAC state (DEC): "); 
    debugSerial.println(byteAux1, DEC);
    debugSerial.println("| u | e | X | X | r | b | u | h | i | x | a | i | D | u |     A     | o | ===================");
    debugSerial.println("| l | j |   | 2 | e | R | t | a | n |   | c | l | R | t |     C     | i | 0 – Idle (transmissions are possible)");
    debugSerial.println("| t | o | T |   | s | e | p | n | k | D |   | e |   | o |           | n | 1 – Transmission occurring");
    debugSerial.println("| i | i | i | p | c | p | u | n |   | o | P | n | s | m |     s     |   | 2 – Before the opening of Receive window 1");
    debugSerial.println("| c | n | m | a | a |   | t | e | c | n | a | t | t |   |     t     | s | 3 – Receive window 1 is open");
    debugSerial.println("| a |   | i | r | l | u |   | l | h | e | u |   | a | R |     a     | t | 4 – Between Receive window 1 and Receive window 2");
    debugSerial.println("| s | N | n | a | e | p | P | s | e |   | s | i | t | e |     t     | a | 5 – Receive window 2 is open");
    debugSerial.println("| t | e | g | m | r | d | o |   | c | S | e | n | u | p |     e     | t | 6 – Retransmission delay - used for ADR_ACK delay");
    debugSerial.println("|   | e |   |   |   | a | w | U | k | t |   | m | s | l |           | u |     FSK can occur");
    debugSerial.println("| s | d | u | u | u | t |   | p |   | a | s | e |   | y |           | s | 7 – APB_delay");
    debugSerial.println("| t | e | p | p | p | e | u | d | s | t | t |   |   |   |           |   |");
    debugSerial.println("| a | d | d | d | d | d | p | a | t | u | a | s |   | s |           |   |");
    debugSerial.println("| t |   | a | a | a |   | d | t | a | s | t | t |   | t |           |   |");
    debugSerial.println("| u |   | t | t | t |   | a | e | t |   | u | a |   | a |           |   |");
    debugSerial.println("| s |   | e | e | e |   | t | d | u |   | s | t |   | t |           |   |");
    debugSerial.println("|   |   | d | d | d |   | e |   | s |   |   | u |   | u |           |   |");
    debugSerial.println("|   |   |   |   |   |   | d |   |   |   |   | s |   | s |           |   |");
    debugSerial.println("+-----------------------------------------------------------------------+");
    
  }
}

void Lora::getStatusVector(uint8_t *statusAux){
  
  for (int i = 0; i < sizeof(_statusEESAMR34); i++){
    statusAux[i] = _statusEESAMR34[i];
  }
}
