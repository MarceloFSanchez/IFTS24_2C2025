//MACROS
//Definición de los puertos serie a utilizar
//--------------------------------------------
#define debugSerial Serial
#define loraSerial Serial2
#define LORA1_SERIAL_TX_PIN   17
#define LORA1_SERIAL_RX_PIN   16
#define LORA1_RESET_PIN       15
#define LORA1_RESPONSE_LEN    256
#define STATUS_EESAMR34_LEN 4 //longitud en Hex del registro de estado
static uint8_t statusEESAMR34[STATUS_EESAMR34_LEN] = {0x00, 0x00, 0x00, 0x00};

//Definición de constantes a utilizar con el módulo LoRa
//--------------------------------------------
#define COMMAND_LEN 50
#define RESPONSE_LEN  100
static char debugCommand[RESPONSE_LEN];
const String EXITDEBUG = "exit debug";
const String INITDEBUG = "init debug";
const String ESTADO = "estado";
static int loraTimeout = 10000; // [ms] -- 10 segundos
static char response[RESPONSE_LEN];
static size_t readed = 0;

void setup() {

  //Iniciamos los puertos serie a utilizar con sus respectivos Baudrates
  loraSerial.begin(115200,SERIAL_8N1, LORA1_SERIAL_RX_PIN, LORA1_SERIAL_TX_PIN);
  debugSerial.begin(9600);
  delay(3000); //[3 s]
  debugSerial.println("::     Programa prueba_serial      ::");
  debugSerial.println("=====================================");
  // versión del firmware LoRaWAN en el chip EESAMR34
  debugSerial.println("::     Versión firmware LoRaWAN      ::");
  loraSendCommand("sys get ver", loraTimeout, 1);

}

void loop() {

  if (debugSerial.available()>0){
  //leo los datos desde el puerto debug 
    getSerialBuffer();  
    if (EXITDEBUG.equals(debugCommand)){
      debugSerial.println("Cambiando a estado anterior....");
      //state = stateBefore;
    }
    else if (ESTADO.equals(debugCommand)){ //statusViewer(true);  
      statusViewer(true);
    }
    else{ 
      debugSerial.println("Enviando comando al chip LoRaWAN....");
      loraSendCommand(debugCommand, loraTimeout, 2);
    }
  }
  delay(3000);
}
