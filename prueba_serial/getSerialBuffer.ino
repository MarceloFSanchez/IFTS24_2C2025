void getSerialBuffer(){

  //size_t readed = 0;

  readed = debugSerial.readBytesUntil('\n', debugCommand, RESPONSE_LEN);
  if (readed > 0) {
    debugCommand[readed] = '\0'; // set \r to \0
    debugSerial.println(debugCommand);
  }

}
