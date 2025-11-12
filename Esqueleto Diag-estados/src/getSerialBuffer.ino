void getSerialBuffer(){

  size_t read = 0;

  read = debugSerial.readBytesUntil('\n', debugCommand, RESPONSE_LEN);
  if (read > 0) {
    debugCommand[read] = '\0'; // set \r to \0
    debugSerial.println(debugCommand);
  }

}
