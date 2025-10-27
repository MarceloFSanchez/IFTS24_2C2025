/**
 * EESA-IOT 5.0 V2
 * Modulo de LoRa para SAMR34 con interprete de comandos
 */
#include <Arduino.h>
#include "lora1.h"
#include <stdio.h>

// Variables privadas

static char response[LORA1_RESPONSE_LEN];

// Prototipos priveados

static bool waitResponse(int timeout);

/**
 * Inicializacion del HW
 */
void LORA1_init(void)
{
  LORA1_SERIAL.begin(115200,SERIAL_8N1, LORA1_SERIAL_RX_PIN, LORA1_SERIAL_TX_PIN);
  pinMode(LORA1_RESET_PIN, OUTPUT);
  digitalWrite(LORA1_RESET_PIN, HIGH);
  vTaskDelay(100);
  digitalWrite(LORA1_RESET_PIN, LOW);
  while(waitResponse(2000));
}

/**
 * Vacia el buffer de recepcion desde el modulo LoRa
 */
static void rxFlush(void)
{
  while(LORA1_SERIAL.available())
    LORA1_SERIAL.read();
}

/**
 * Espera la respuesta del modulo LoRa y la imprime en el puerto de debug
 */
static bool waitResponse(int timeout)
{
  size_t read = 0;

  LORA1_SERIAL.setTimeout(timeout);

  read = LORA1_SERIAL.readBytesUntil('\n', response, LORA1_RESPONSE_LEN);
  if (read > 0) {
    vTaskDelay(100);
    response[read - 1] = '\0'; // set \r to \0
    Serial.println(response);
    return true;
  }
  else {
    Serial.println("Response timeout");
    response[0] = '\0';
    return false;
  }
}

/**
 * Envia un comando al modulo LoRa y espera la respuesta
 */
static bool sendCommand(char *command, int timeout)
{
  rxFlush();
  Serial.println(command);
  LORA1_SERIAL.println(command);
  return waitResponse(timeout);
}

/**
 * Envia un comando al modulo LoRa y espera la respuesta OK
 */
static bool sendCommandOk(char *command, int timeout)
{
  if (!sendCommand(command, timeout))
    return false;
  if (strstr(response, "ok"))
    return true;
  return false;
}

bool LORA1_command(char *cmd, int timeout)
{
  return sendCommandOk(cmd, timeout);
}
/**
 * Resetea el stack LoRaWan
 */
bool LORA1_resetLorawan(char *band, int sband)
{
  char cmd[30];
  int i;

  sprintf(cmd, "mac reset %s", band);

  if (!sendCommandOk(cmd, 1000))
    return false;

  for (i=1; i<=8; i++) {
    if (i == sband)
      sprintf(cmd, "mac set subband status %d on", i);
    else
      sprintf(cmd, "mac set subband status %d off", i);
    if (!sendCommandOk(cmd, 1000))
      return false;
  }

  return sendCommandOk("mac set joinbackoffenable off", 1000);
}

/**
 * setea un parametro con un solo valor
 */
static bool setMacparam1(char *param, char *value)
{
  char cmd[100];

  sprintf(cmd, "mac set %s %s", param, value);
  return sendCommandOk(cmd, 1000);
}


bool LORA1_setDeveui(char *eui)
{
  return setMacparam1("deveui", eui);
}

bool LORA1_setJoineui(char *eui)
{
  return setMacparam1("joineui", eui);
}

bool LORA1_setAppkey(char *key)
{
  return setMacparam1("appkey", key);
}

bool LORA1_join(char *mode)
{
  char cmd[30];

  sprintf(cmd, "mac join %s", mode);
  if (!sendCommandOk(cmd, 1000))
    return false;
  if (!waitResponse(20000))
    return false;
  if (strstr(response, "accepted"))
    return true;
  return false;
}

static bool procRx(void)
{
  int p = -1;
  char *d;

  sscanf(response+7, "%d", &p);
  if (p < 1 || p > 999)
    return false;

  if (p > 99)     d = response + 11;
  else if (p > 9) d = response + 10;
  else            d = response + 9;

  LORA1_rxCb(p, d);
  return true;
}

bool LORA1_tx(char *mode, int port, uint8_t *data, int len)
{
  char cmd[100];
  int i, j;
  
  j = sprintf(cmd, "mac tx %s %d ", mode, port);

  for (i=0; i<len; i++, j+=2) {
    sprintf(cmd+j, "%2.2X", data[i]);
  }

  if (!sendCommandOk(cmd, 1000))
    return false;
  if (!waitResponse(20000))
    return false;
  if (strstr(response, "mac_tx_ok"))
    return true;
  if (strstr(response, "mac_rx"))
    return procRx();
  return false;  
}
