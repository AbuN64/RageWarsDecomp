#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(osWritebackDCacheAll)
    lui     t0, 0x8000
    li      t2, 0x2000
    addu    t1, t0, t2
    addiu   t1, t1, -0x10
1:
    cache   (C_IINV | CACH_PD), 0(t0)
    sltu    AT, t0, t1
    bnez    AT, 1b
    addiu   t0, t0, 0x10
    jr      ra
    nop
END(osWritebackDCacheAll)
