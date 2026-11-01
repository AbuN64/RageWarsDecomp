#ifndef PERIPHERAL_PORT_BYTE_VIEWS_H
#define PERIPHERAL_PORT_BYTE_VIEWS_H
#include "TYPES.H"






struct PeripheralPortStatusByteView;
typedef struct PeripheralPortStatusByteView PeripheralPortStatusByteView;





struct ReadWordByte;
typedef struct ReadWordByte ReadWordByte;






struct ReadWordByte;
struct ReadWordByte {
    s32 word;
    u8 byte;
    u8 value;
};




struct PeripheralPortStatusByteView;
struct PeripheralPortStatusByteView {
    unsigned char padding_0[1];
    u8 statusByte;
};
#endif
