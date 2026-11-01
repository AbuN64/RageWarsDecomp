#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(Rnc_BuildHuffmanTable)
    addi    t0, zero, 0x1F
    addu    t8, ra, zero
    jal     Rnc_ReadBits
    addi    t1, zero, 0x5
    addu    ra, t8, zero
    addi    t0, t0, -0x1
    bltz    t0, 7f
    nop
    addu    t2, t0, zero
    addu    t3, t0, zero
    addi    sp, sp, -0x10
    addu    s1, sp, zero
1:
    addi    t0, zero, 0xF
    addu    t8, ra, zero
    jal     Rnc_ReadBits
    addi    t1, zero, 0x4
    addu    ra, t8, zero
    sb      t0, 0(s1)
    addi    s1, s1, 0x1
    bnez    t2, 1b
    addi    t2, t2, -0x1
    addu    t0, a1, zero
    addi    t1, zero, 0x1
    addu    t2, zero, zero
    addi    sp, sp, -0x10
    sw      t5, 0(sp)
    sw      t6, 0x4(sp)
    sw      t7, 0x8(sp)
2:
    addu    t4, t3, zero
    addi    s1, sp, 0x10
3:
    lbu     AT, 0(s1)
    addi    s1, s1, 0x1
    bne     t1, AT, 6f
    nop
    addi    t5, zero, 0x1
    sllv    t5, t5, t1
    addi    t5, t5, -0x1
    sh      t5, 0(s0)
    addi    s0, s0, 0x2
    addu    t5, t2, zero
    sll     AT, t5, 16
    srl     t5, t5, 16
    or      t5, t5, AT
    addu    t7, t1, zero
    addi    t7, t7, -0x1
4:
    addi    AT, zero, -0x1
    srl     AT, AT, 16
    and     t6, AT, t6
    and     AT, t5, a3
    sll     t5, t5, 1
    srl     t6, t6, 1
    beqz    AT, 5f
    nop
    or      t6, t6, a3
5:
    bnez    t7, 4b
    addi    t7, t7, -0x1
    addi    t5, zero, 0x10
    sub     t5, t5, t1
    srlv    t6, t6, t5
    sh      t6, 0(s0)
    addi    s0, s0, 0x2
    sb      t1, 0x3C(s0)
    addu    t5, t3, zero
    subu    t5, t5, t4
    sb      t5, 0x3D(s0)
    addi    t6, zero, 0x1
    addiu   t5, t5, -0x1
    sllv    t6, t6, t5
    addiu   t6, t6, -0x1
    sh      t6, 0x3E(s0)
    addu    t2, t2, t0
6:
    bnez    t4, 3b
    addi    t4, t4, -0x1
    srl     t0, t0, 1
    addi    t1, t1, 0x1
    addi    AT, zero, 0x11
    bne     t1, AT, 2b
    nop
    lw      t5, 0(sp)
    lw      t6, 0x4(sp)
    lw      t7, 0x8(sp)
    addi    sp, sp, 0x10
    addi    sp, sp, 0x10
7:
    jr      ra
    nop
END(Rnc_BuildHuffmanTable)
