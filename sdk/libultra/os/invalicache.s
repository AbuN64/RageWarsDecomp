#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(osInvalICache)
    blez    a1, 2f
    li      t3, 0x4000
    sltu    AT, a1, t3
    beqz    AT, 3f
    addu    t0, a0, zero
    addu    t1, a0, a1
    sltu    AT, t0, t1
    beqz    AT, 2f
    addiu   t1, t1, -0x20
    andi    t2, t0, 0x1F
    subu    t0, t0, t2
1:
    cache   (C_HINV | CACH_PI), 0(t0)
    sltu    AT, t0, t1
    bnez    AT, 1b
    addiu   t0, t0, 0x20
2:
    jr      ra
    nop
3:
    lui     t0, 0x8000
    addu    t1, t0, t3
    addiu   t1, t1, -0x20
4:
    cache   (C_IINV | CACH_PI), 0(t0)
    sltu    AT, t0, t1
    bnez    AT, 4b
    addiu   t0, t0, 0x20
    jr      ra
    nop
END(osInvalICache)
