/*   Diagrama de estados para conexión a una red LoRaWAN
 *   ---------------------------------------------------
 *
 * El hardware utilizado es la placa de desarrollo ESAAIOTV2
 * de la empresa Elemon: 
 * 
 * Repositorio:
 *===========================================================
 */

//LIBRERIAS
#include "config.h"
#include "lorawan-keys.h"
#include "Lora.h"

// CONSTANTES
const char BAND[6] = "AU915";
const char DEVEUI[APPEUI_LEN+1] = OTAA_DEVEUI;
const char APPEUI[APPEUI_LEN+1] = OTAA_APPEUI;
const char APPKEY[APPKEY_LEN+1] = OTAA_APPKEY;
const uint8_t JOINEDMASK[STATUS_EESAMR34_LEN] = {0x01, 0x00, 0x00, 0x00};
const uint8_t ADRMASK[STATUS_EESAMR34_LEN] = {0x40, 0x00, 0x00, 0x00};
static const String OKEY = "ok";
static const String JOINACCEPTED = "accepted";
static const String MACSENDED = "mac_tx_ok";
static const String JOINDENIED = "denied";
//static const String STATUS = "status";
// Utilizadas en estado DEBUG
const String EXITDEBUG = "exit debug";
const String INITDEBUG = "init debug";
const String ESTADO = "estado";

// Objetos
Lora lora; // Objeto para comunicación con EESAMR34

// VARIABLES
static uint8_t statusEESAMR34[STATUS_EESAMR34_LEN] = {0x00, 0x00, 0x00, 0x00};
static char response[RESPONSE_LEN];
static int loraTimeout = LORA_TIMEOUT;
//static size_t readed = 0;
//static char responses[MAX_RESPONSES][RESPONSE_LEN];
char command [COMMAND_LEN];
//static int sleepTime = 10000;

// Variables utilizadas para indicar estados de trabajo y medición
//----------------------------------------------------------------
enum estados{ //Definimos los estados en que puede trabajar el nodo e intervalos de medicion
  CONEXION_OTAA = 0,
  LECTURA_SENSORES, ENVIO_DATOS, DEBUG
};
static volatile enum estados state;
static volatile enum estados stateBefore; // para guardar estando anterior al entrar en DEBUG

//Variables a utilizar para la medición del sensor
//--------------------------------------------

//Variales para entrar a modo DEBUG
//--------------------------------------------
int adqDebug = 20;
static char debugCommand[RESPONSE_LEN];


/* _____________________________________________________________________ 
  |                                                                     |
  |                             SETUP                                   |
  | ____________________________________________________________________| 
*/

void setup(){
  
  //Inicio de los puertos serie a utilizar con sus respectivos Baudrates
  loraSerial.begin(115200,SERIAL_8N1, LORA1_SERIAL_RX_PIN, LORA1_SERIAL_TX_PIN);
  pinMode(LORA_RESET_PIN, OUTPUT);
  digitalWrite(LORA_RESET_PIN, HIGH);
  vTaskDelay(100);
  digitalWrite(LORA_RESET_PIN, LOW);
  //while(waitResponse(2000));
  debugSerial.begin(9600);
  delay(3000); //[3 s]
  debugSerial.println("************************************************");
  debugSerial.println("*                                              *");
  debugSerial.println("*          Proyecto IoT LoRaWAN IFTS24         *");
  debugSerial.println("*                                              *");
  debugSerial.println("************************************************");

  debugSerial.println("\n ::     Estado INICIO      ::\n"); // DEBUG
  
  // versión del firmware LoRaWAN en el chip EESAMR34
  debugSerial.println("::     Versión firmware LoRaWAN      ::");
  lora.sendCommand("sys get ver", loraTimeout, 1);

  // INFO DE CONFIGURACION
  // Algunos parámetros pueden ser de fábrica, pero otros pueden
  // estar guardados en la EEPROM desde la última configuración.

  // ¡¡¡ Para resetear de fábrica descomentar la siguiente línea !!!
  // lora.sendCommand("sys factoryRESET", loraTimeout, 1);
  lora.getMacParameters();

  // se configuran lo parámetros regionales
  snprintf(command, COMMAND_LEN, "mac reset %s", BAND);
  lora.sendCommand(command, loraTimeout, 1);

  // se cargan appeui, appkey y joineui desde archivo lorawan-keys.h
  snprintf(command, COMMAND_LEN, "mac set deveui %s", DEVEUI);
  lora.sendCommand(command, loraTimeout, 1);
  
  snprintf(command, COMMAND_LEN, "mac set appkey %s", APPKEY);  
  lora.sendCommand(command, loraTimeout, 1);

  snprintf(command, COMMAND_LEN, "mac set joineui %s", OTAA_JOINEUI);  
  lora.sendCommand(command, loraTimeout, 1);  

}//Fin del Setup

/* _____________________________________________________________________ 
  |                                                                     |
  |                              LOOP                                   |
  | ____________________________________________________________________| 
*/

void loop(){
  switch (state) {
    case CONEXION_OTAA:       
      // Aquí se intenta conectar a la red cuando se enciende por 1era vez
      // ó cuando se detecta una desconexión.
      // Se pasa al próximo estado LECTURA_SENSORES cuando se detecta 
      // conexión exitosa a la red.
      // También se cargan configuraciones adicionales (adr, rxdelay, etc) 

      debugSerial.println("\n ::     Estado CONEXION OTAA      ::\n"); // DEBUG

      // Envío de comando para conexión
      lora.sendCommand("mac join otaa", loraTimeout, 2);
      delay(15000);

      // Verificación estado de conexión
      if(!nextState(JOINEDMASK, LECTURA_SENSORES, CONEXION_OTAA));
        debugSerial.println("(((-- Intentando conectar por OTAA --)))");  
	  
      // Configuraciones adicionales (adr, rxdelay1)
      configInit(); 
   
    break;

    case LECTURA_SENSORES:
      
      debugSerial.println("\n ::     Estado LECTURA SENSORES      ::\n");

      delay(random(30000,90000));
/*
    *******************************************************************
   **                                                                 **
  **      ESPACIO PARA ADQUIRIR LOS DATOS DEL SENSOR                   **
   **                                                                 **
    ******************************************************************* 
*/
       
      if ( !nextState(JOINEDMASK, ENVIO_DATOS, CONEXION_OTAA) )  
        debugSerial.println("XXX--- DESCONEXION DETECTADA ---XXX");
      
    break;

    case ENVIO_DATOS:

      debugSerial.println("\n ::     Estado ENVIO DATOS      ::\n");

      sendMeasures(random(9999));

      state = LECTURA_SENSORES;

    break;

    case DEBUG:
      if (debugSerial.available()>0){
      //leo los datos desde el puerto debug 
	      getSerialBuffer();
        if (EXITDEBUG.equals(debugCommand)){
          debugSerial.println("Cambiando a estado anterior....");
          state = stateBefore;
        }
        else if (ESTADO.equals(debugCommand)) lora.statusView(true);  
        else{ 
        // envio los datos al modulo Lora y muestro por puerto debug
        // hasta 2 respuestas
          lora.sendCommand(debugCommand, loraTimeout, 2);
        }  
      }
	    // si luego de esperar 2 respuestas desde LN2903 apararecen 
	    // nuevos en el buffer
      if (loraSerial.available()>0) lora.waitResponse(1000);
      if (loraSerial.available()>0) lora.waitResponse(1000);

    break;
  
  }//Fin switch

  // fuera del switch verificamos si hay datos disponibles en el
  // buffer del puerto 'debugSerial' y si coincide con el comando para
  // entrar en modo debug "init debug".
  if (state != DEBUG && debugSerial.available()>0){
    getSerialBuffer();  // guarda los datos del buffer en debugCommand
    if (INITDEBUG.equals(debugCommand)){
      stateBefore = state;
      state = DEBUG;
      debugSerial.println("\n::::     EN DEBUG: Programa Principal Detenido    :::\n");
    }
  }

}//Fin del Loop
