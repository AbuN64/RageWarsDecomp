#include "include_asm.h"
#include <platform_sdk.h>
#include <PR/os_internal_rsp.h>

/** Write a word to the SP status register. */
void __osSpSetStatus(unsigned int statusCommand) {
    *(volatile unsigned int *)0xA4040010 = statusCommand;
}

