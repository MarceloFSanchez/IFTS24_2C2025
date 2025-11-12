void statusViewer(bool showTable){
// https://www.ibm.com/docs/es/aix/7.1?topic=adapters-ascii-decimal-hexadecimal-octal-binary-conversion-table

  loraSendCommand("mac get status", loraTimeout, 1);

  char *pointer = response; //guardo el inicio del vector en un puntero
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
    statusEESAMR34[iterations-i-1] =  (byteAux1<<4 | byteAux2);
  }

  // Se imprime tabla con resultados por puerto serie
  //---------------------------------------------------------------
  if (readed = 9 & showTable){ // Hardcodeado, si no es 9 es porque no devuelve
                             // el registro sino otro mensaje
    debugSerial.println("Registro de estados del chip EESAMR34:");
    debugSerial.println("+-------------------------------------------------------+");
    debugSerial.print("| ");
    // bits 31 a 18 ---------------------------------
    for (b = 7; b >= 0; b--){
      debugSerial.print(bitRead(statusEESAMR34[3], b));
      debugSerial.print(" | ");
    }
    for (b = 7; b >= 2; b--){
      debugSerial.print(bitRead(statusEESAMR34[2], b));
    debugSerial.print(" | ");
    }
    debugSerial.print("\n");
    debugSerial.println("+---+---+---+---+---+---+---+---+---+---+---+---+---+---+");
    debugSerial.println("|                       RFU                             |");
    debugSerial.println("+-----------------------------------------------------------------------+");
    debugSerial.print("| ");
    // bits 17 a 0 ----------------------------------
    for (b = 1; b >= 0; b--){
      debugSerial.print(bitRead(statusEESAMR34[2], b));
    debugSerial.print(" | ");
    }
    for (b = 7; b >= 0; b--){
      debugSerial.print(bitRead(statusEESAMR34[1], b));
    debugSerial.print(" | ");
    }
    for (b = 7; b >= 0; b--){
      debugSerial.print(bitRead(statusEESAMR34[0], b));
    debugSerial.print(" | ");
    }
    debugSerial.println("");
    byteAux1 = statusEESAMR34[0] & 0x0f; //descarto los primeros 4 bits
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
