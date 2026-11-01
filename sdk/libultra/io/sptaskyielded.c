#include "include_asm.h"
#include "COMMON/AIPROFILE.H"
#include <ultra64.h>
#include <PR/os_internal_rsp.h>


OSYieldResult osSpTaskYielded(OSTask *tp)
{
    s32 selected_bit;
    u32 status;

    status = __osSpGetStatus();
    selected_bit = status >> 8;
    selected_bit = selected_bit & 1;
    if (status & 0x80) {
        tp->t.flags = (tp->t.flags | selected_bit) & ~2;
    }
    return selected_bit;
}

