#ifndef DATA_OVERLAYS_ENCODED_CALLBACK_H
#define DATA_OVERLAYS_ENCODED_CALLBACK_H

/* Overlay callback tables store a function address with the KSEG0 bit (0x80000000) cleared. */
#define ENCODED_CALLBACK_ADDRESS(function) ((unsigned int)(function) - 0x80000000u)

#endif
