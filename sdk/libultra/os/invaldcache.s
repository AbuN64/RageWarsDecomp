#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(osInvalDCache)
    blez    a1, 3f
    nop
    li      t3, 0x2000
    sltu    AT, a1, t3
    beqz    AT, 4f
    addu    t0, a0, zero
    addu    t1, a0, a1
    sltu    AT, t0, t1
    beqz    AT, 3f
    addiu   t1, t1, -0x10
    andi    t2, t0, 0xF
    beqz    t2, 1f
    subu    t0, t0, t2
    cache   (C_HWBINV | CACH_PD), 0(t0)
    sltu    AT, t0, t1
    beqz    AT, 3f
    addiu   t0, t0, 0x10
1:
    andi    t2, t1, 0xF
    beqz    t2, 2f
    subu    t1, t1, t2
    cache   (C_HWBINV | CACH_PD), 0x10(t1)
    sltu    AT, t1, t0
    bnez    AT, 3f
2:
    cache   (C_HINV | CACH_PD), 0(t0)
    sltu    AT, t0, t1
    bnez    AT, 2b
    addiu   t0, t0, 0x10
3:
    jr      ra
    nop
4:
    lui     t0, 0x8000
    addu    t1, t0, t3
    addiu   t1, t1, -0x10
5:
    cache   (C_IINV | CACH_PD), 0(t0)
    sltu    AT, t0, t1
    bnez    AT, 5b
    addiu   t0, t0, 0x10
    jr      ra
    nop
END(osInvalDCache)
