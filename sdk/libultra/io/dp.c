#include "../../include/libgultra.h"
#include "COMMON/CONTREADFORMAT.H"

/* 802B7488_9.CPP */

/* dp.c */
int __osDpDeviceBusy(void) {
    int flag = *(volatile int *)0xA410000C & 0x100;
    return flag != 0;
}
