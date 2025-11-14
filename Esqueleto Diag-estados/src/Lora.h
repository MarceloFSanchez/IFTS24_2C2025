#ifndef Lora_h
#define Lora_h
#include <Arduino.h>
#include "config.h"


class Lora{
  private:
	char _command[COMMAND_LEN+1];
	char _response[RESPONSE_LEN+1];
    int _timeout;
	int _numResp;
	size_t _read;
	uint8_t _statusEESAMR34[STATUS_EESAMR34_LEN];
  public:
	Lora();
	void clearReadBuffer();
	void getMacParameters();
	void sendCommand(const char *command, int timeout, int numResp);
  void sendCommand(const char *command, int numResp);
  void sendCommand(int numResp);
	void waitResponse(int timeout);
	bool isResponse(const String& expected);
  void statusView(bool showTable);
  void getStatusVector(uint8_t *statusAux);
};

#endif
