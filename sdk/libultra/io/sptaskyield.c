#include "include_asm.h"
#include <platform_sdk.h>
#include <PR/os_internal_rsp.h>

void osSpTaskYield(void) { __osSpSetStatus(0x400U); }



