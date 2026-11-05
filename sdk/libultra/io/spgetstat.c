#include "include_asm.h"
#include <platform_sdk.h>
#include <PR/os_internal_rsp.h>

/** Read the SP status register. */
unsigned int __osSpGetStatus(void) {
    return *(volatile unsigned int *)0xA4040010;
}

