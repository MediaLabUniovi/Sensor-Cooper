/*

Credentials file

*/

#pragma once

// Only one of these settings must be defined
//#define USE_ABP
#define USE_OTAA

#ifdef USE_ABP

// UPDATE WITH YOUR TTN KEYS AND ADDR.
//static const PROGMEM u1_t NWKSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//static const u1_t PROGMEM APPSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//static const u4_t DEVADDR = 0x26010000 ; // <-- Change this address for every node!

#endif

#ifdef USE_OTAA

    // This EUI must be in little-endian format, so least-significant-byte
    // first. When copying an EUI from ttnctl output, this means to reverse
    // the bytes. For TTN issued EUIs the last bytes should be 0x00, 0x00,
    // 0x00.
    static const u1_t PROGMEM APPEUI[8]  = { 0x33, 0x33, 0x22, 0x22, 0x11, 0x11, 0x00, 0x00 };

    // This should also be in little endian format, see above. (least-significant-byte
    // first)
    static const u1_t PROGMEM DEVEUI[8]  = { 0xB5, 0xFC, 0x05, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };

    // This key should be in big endian format (or, since it is not really a
    // number but a block of memory, endianness does not really apply). In
    // practice, a key taken from ttnctl can be copied as-is.
    // The key shown here is the semtech default key.
    static const u1_t PROGMEM APPKEY[16] = { 0xB5, 0xCF, 0x5E, 0x61, 0xAA, 0xC4, 0xAE, 0x2A, 0x96, 0x43, 0xF7, 0xC6, 0x41, 0x87, 0x00, 0xF3 };

#endif
