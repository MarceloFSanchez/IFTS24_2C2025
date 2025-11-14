/*******************************************************************************
 *
 *  File:          lorawan-keys_example.h
 * 
 *  Function:      Example for lorawan-keys.h
 *
 ******************************************************************************/

#ifndef LORAWAN_KEYS_H_
#define LORAWAN_KEYS_H_

// Keys required for OTAA activation:

// End-device Identifier in msb format
#define OTAA_DEVEUI "f3f40ba56e175c53"

// Application Identifier  in msb format
#define OTAA_APPEUI "123456789ABCDEF"

// Application Key in msb format
#define OTAA_APPKEY "00001111122222333334444455555666"

// Application Key in msb format
#define OTAA_JOINEUI "0011223344556677"

// -----------------------------------------------------------------------------

// #define ABP_DEVICEID "<deviceid>"

// Keys required for ABP activation:

// End-device Address (u4_t) in uint32_t format. 
// Note: The value must start with 0x (current version of TTN Console does not provide this).
// #define ABP_DEVADDR 0x00000000

// Network Session Key (u1_t[16]) in msb format
// #define ABP_NWKSKEY 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

// Application Session K (u1_t[16]) in msb format
// #define ABP_APPSKEY 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00


#endif  // LORAWAN_KEYS_H_ 
