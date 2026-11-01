#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(osWritebackDCache)
    blez    a1, 2f
    li      t3, 0x2000
    sltu    AT, a1, t3
    beqz    AT, 3f
    addu    t0, a0, zero
    addu    t1, a0, a1
    sltu    AT, t0, t1
    beqz    AT, 2f
    addiu   t1, t1, -0x10
    andi    t2, t0, 0xF
    subu    t0, t0, t2
1:
    cache   (C_HWB | CACH_PD), 0(t0)
    sltu    AT, t0, t1
    bnez    AT, 1b
    addiu   t0, t0, 0x10
2:
    jr      ra
    nop
3:
    lui     t0, 0x8000
    addu    t1, t0, t3
    addiu   t1, t1, -0x10
4:
    cache   (C_IINV | CACH_PD), 0(t0)
    sltu    AT, t0, t1
    bnez    AT, 4b
    addiu   t0, t0, 0x10
    jr      ra
    nop
END(osWritebackDCache)
