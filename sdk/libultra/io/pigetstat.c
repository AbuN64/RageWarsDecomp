#include "TYPES.H"
#include <ultra64.h>

#if defined(VERSION_US_REV1)
/** Read the PI status register at 0xA4600010. */
unsigned int osPiGetStatus(void) {
    return *(volatile unsigned int *)0xA4600010;
}
#endif
