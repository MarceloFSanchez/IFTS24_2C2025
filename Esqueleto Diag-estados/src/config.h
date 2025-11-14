// MACROS
// Definición de los puertos serie a utilizar
//--------------------------------------------
#define debugSerial Serial
#define loraSerial Serial2
#define LORA1_SERIAL_TX_PIN   17
#define LORA1_SERIAL_RX_PIN   16

// Definiciones para utilizar con el módulo LoRa
//------------------------------------------------------
// LORA_RST
// Pin de la placa para el reseteo de la EESAMR34 (modulo LoRa)
#define LORA_RESET_PIN 15

// MAX_RESPONSES
#define MAX_RESPONSES  10

// LORA_TIMEOUT
// Controla el tiempo de espera del MCU para respuesta por parte del chip LoRaWAN 
// para comandos de configuración, No para envío de mensajes.
#define LORA_TIMEOUT 5000  // [ms]

// COMMAND_LEN
// Define el máximo tamaño para los comandos enviados al chip LoRaWAN
#define COMMAND_LEN 70 

// Define el máximo tamaño esperado del mensaje de respuesta desde
// el chip LoRaWAN
#define RESPONSE_LEN  70


// STATUS_EESAMR34_LEN ¡¡¡ Recomendación - NO Modificar !!!
// Longitud en Hex del registro de estado
#define STATUS_EESAMR34_LEN 4 

// ¡¡¡  NO CONFIGURABLES - DEJAR LOS VALORES POR DEFECTO  !!!
// ==========================================================
//
// Longitud de la clave APPEUI (Por defecto = 16)
#define APPEUI_LEN 16

// Longitud de la clave APPKEY (Por defecto = 32)
#define APPKEY_LEN 32

// Longitud del vector Tiempo en formato Unix/Epoch (Por defecto = 8)
// El valor representa la cantidad de dígitos en Hexa.
#define DATETIME_LEN 8 

// Longitud del vector para guardar el dato de la medición (Por defecto = 4)
#define MEDICION_LEN 4

// Parámetros configurables para utilización del nodo
//---------------------------------------------------
// Tx1 Delay [LoRaWAN]
// Indica el tiempo en que la 1er ventana (Tx1) debe comenzar a escuchar
// un mensaje de recepción de por parte del servidor de red.
// La misma permanece abierta por 1 seg luego se apaga por un seg y 
// se abra la 2da ventana (Tx2) por 1 seg más.
// ¡¡¡ Importante !!!
// Sirve para los primeros mensajes, unión por OTTA por ejemplo, si se
// conoce la configuración actual del servidor de red (NS).
// Ya que el NS puede tener una configuración diferente
// o cambiar en el futuro. En cualquiera de los casos este parámetro 
// va a ser configurado remotamente por el NS. 
#define TX1_DELAY 5000  // [ms]

// RetxNb [LoRaWAN]
// Indica Número de retransmisiones si no se recibe un Ack por parte del NS,
// cuando se envían paquetes "uplink confirmed".
#define LORA_RETXNB 3

// LORA_MSG_TIMEOUT ¡¡¡ Recomendación: NO Modificar !!!
// Controla el tiempo que debe esperar el MCU para recibir una respuesta desde el 
// chip LoRaWAN (LN2903A actualmente), cuando se envía un mensaje. 
// Está directamente relacionada con la cantidad Nbret y Tx1 Delay.
// Por ello no es recomendable modificar este parámetro.
#define LORA_MSG_TIMEOUT (TX1_DELAY+3000)*LORA_RETXNB+5000 // [ms]

// Tiempo de guarda para el envío consecutivo de mensajes.
// Se utiliza cuando se tiene que programar la próxima 
// alarma para envío de mensajes. Define el mínimo tiempo 
// en segundos de la cota inferior del intervalo a calcular
// aleatoriamente. La cota superior se define en el vector
// de tiempos "_timesMsg".
#define TIME_MSG_GUARD 20 // [segundos]

// Número de intentos.
// Define el número de intentos dentro de los 10 minutos 
// disponibles para envío de mensajes en caso que no se 
// haya recibido ack desde el servidor.
#define MSG_ATTEMPS 3
