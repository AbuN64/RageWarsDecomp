#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(osUnmapTLB)
    mfc0    t0, C0_ENTRYHI
    mtc0    a0, C0_INX
    lui     t1, 0x8000
    mtc0    t1, C0_ENTRYHI
    mtc0    zero, C0_ENTRYLO0
    mtc0    zero, C0_ENTRYLO1
    nop
    tlbwi
    nop
    nop
    nop
    nop
    mtc0    t0, C0_ENTRYHI
    jr      ra
    nop
END(osUnmapTLB)
