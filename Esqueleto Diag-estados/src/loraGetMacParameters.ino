void loraGetMacParameters(){

  // versión del firmware RN2903A
  loraSendCommand("sys get ver", loraTimeout, 1);

// Gets the current stored unique network device address for that
// specific end device.
  loraSendCommand("mac get devaddr", loraTimeout, 1);

// Gets the current stored globally unique identifier for that
// specific end device.
  loraSendCommand("mac get deveui", loraTimeout, 1);

// Gets the application identifier for the end device.
  loraSendCommand("mac get appeui", loraTimeout, 1);

// Gets the data rate to be used for the next transmission.
  loraSendCommand("mac get dr", loraTimeout, 1);

// Gets the output power index value.
  loraSendCommand("mac get pwridx", loraTimeout, 1);

// Gets the state of adaptive data rate for the device.
  loraSendCommand("mac get adr", loraTimeout, 1);

// Gets the number of retransmissions to be used for an uplink
// confirmed packet.
  loraSendCommand("mac get retx", loraTimeout, 1);

//Gets the interval value stored for rxdelay1.
  loraSendCommand("mac get rxdelay1", loraTimeout, 1);

// Gets the interval value stored for rxdelay2.
  loraSendCommand("mac get rxdelay2", loraTimeout, 1);

// Gets the state of the automatic reply.
  loraSendCommand("mac get ar", loraTimeout, 1);

// Gets the data rate and frequency used for the second Receive window.
  loraSendCommand("mac get rx2", loraTimeout, 1);  

// Gets the duty cycle prescaler which can only be configured by
//  the server.
  loraSendCommand("mac get dcycleps", loraTimeout, 1);

// Gets the demodulation margin as received in the last Link Check
//  Answer frame.
  loraSendCommand("mac get mrgn", loraTimeout, 1);

// Gets the number of gateways that successfully received the last
//  Link Check Request frame.
  loraSendCommand("mac get gwnb", loraTimeout, 1);

// Gets the current status of the RN2903 module.
  loraSendCommand("mac get status", loraTimeout, 1);

// Returns the current synchronization word.
  loraSendCommand("mac get sync", loraTimeout, 1);

// Returns the current uplink counter.
  loraSendCommand("mac get upctr", loraTimeout, 1);

// Returns the current downlink counter.
  loraSendCommand("mac get dnctr", loraTimeout, 1);

// Gets parameters related information which pertains to channel
//  operation and behaviors.
//  loraSendCommand("mac get ch", loraTimeout, 1);




}
