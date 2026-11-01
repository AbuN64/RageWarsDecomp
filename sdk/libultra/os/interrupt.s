#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(__osDisableInt)
    mfc0    t0, C0_SR
    li      AT, -0x2
    and     t1, t0, AT
    mtc0    t1, C0_SR
    andi    v0, t0, 0x1
    nop
    jr      ra
    nop
END(__osDisableInt)

LEAF(__osRestoreInt)
    mfc0    t0, C0_SR
    or      t0, t0, a0
    mtc0    t0, C0_SR
    nop
    nop
    jr      ra
    nop
END(__osRestoreInt)
