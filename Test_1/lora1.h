/**
 * EESA-IOT 5.0 V2
 * Modulo de LoRa para SAMR34 con interprete de comandos
 */
#ifndef __LORA1_H
#define __LORA1_H

// Macros

#define LORA1_SERIAL          Serial2
#define LORA1_SERIAL_TX_PIN   17
#define LORA1_SERIAL_RX_PIN   16
#define LORA1_RESET_PIN       15
#define LORA1_RESPONSE_LEN    256

// Prototipos
void LORA1_init(void);
bool LORA1_command(char *cmd, int timeout);
bool LORA1_resetLorawan(char *band, int sband);
bool LORA1_setDeveui(char *eui);
bool LORA1_setJoineui(char *eui);
bool LORA1_setAppkey(char *eui);
bool LORA1_join(char *mode);
bool LORA1_tx(char *mode, int port, uint8_t *data, int len);
void LORA1_rxCb(int port, char *data);

#endif
