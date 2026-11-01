#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(Rnc_DecodeMethod1)
    addi    v1, zero, -0x1
    andi    v1, v1, 0xFF
    sll     a0, v1, 24
    sll     a1, v1, 31
    srl     a3, a1, 16
    nor     a2, zero, v1
    add     s5, s1, s3
    add     s6, s0, s2
    addu    s3, s0, zero
    addu    s4, s1, zero
    addi    sp, sp, -0x180
    addu    s2, sp, zero
    lbu     t6, 0x1(s3)
    lbu     AT, 0(s3)
    addu    t7, zero, zero
    sll     t6, t6, 8
    or      t6, t6, AT
    addi    t0, zero, 0x2
    addu    t8, ra, zero
    jal     Rnc_ReadBits
    addi    t1, zero, 0x2
    addu    ra, t8, zero
1:
    addi    sp, sp, -0x8
    sw      ra, 0(sp)
    jal     Rnc_BuildHuffmanTable
    addu    s0, s2, zero
    jal     Rnc_BuildHuffmanTable
    addi    s0, s2, 0x80
    jal     Rnc_BuildHuffmanTable
    addi    s0, s2, 0x100
    addi    t0, zero, -0x1
    jal     Rnc_ReadBits
    addi    t1, zero, 0x10
    lw      ra, 0(sp)
    addi    sp, sp, 0x8
    addu    t4, t0, zero
    addi    AT, zero, -0x1
    srl     AT, AT, 16
    addi    t4, t4, -0x1
    j       4f
    and     t4, AT, t4
2:
    addi    s0, s2, 0x80
    addu    t8, ra, zero
    jal     Rnc_ReadHuffmanValue
    addu    t0, zero, zero
    negu    t0, t0
    add     s1, s4, t0
    addi    s1, s1, -0x1
    jal     Rnc_ReadHuffmanValue
    addi    s0, s2, 0x100
    addu    ra, t8, zero
    addi    s4, s4, 0x1
    lbu     AT, 0(s1)
    addi    s1, s1, 0x1
    sb      AT, -0x1(s4)
3:
    addi    s4, s4, 0x1
    lbu     AT, 0(s1)
    addi    s1, s1, 0x1
    sb      AT, -0x1(s4)
    bnez    t0, 3b
    addi    t0, t0, -0x1
4:
    addu    t8, ra, zero
    jal     Rnc_ReadHuffmanValue
    addu    s0, s2, zero
    addu    ra, t8, zero
    addi    t0, t0, -0x1
    bltz    t0, 6f
    nop
5:
    lbu     AT, 0(s3)
    addi    s3, s3, 0x1
    sb      AT, 0(s4)
    addi    s4, s4, 0x1
    bnez    t0, 5b
    addi    t0, t0, -0x1
    lbu     AT, 0x1(s3)
    lbu     t0, 0(s3)
    sll     AT, AT, 8
    or      t0, AT, t0
    sllv    t0, t0, t7
    addi    t1, zero, 0x1
    sllv    t1, t1, t7
    addiu   t1, t1, -0x1
    and     t6, t6, t1
    or      t6, t0, t6
6:
    bnez    t4, 2b
    addi    t4, t4, -0x1
    sub     AT, s3, s6
    bltz    AT, 1b
    nop
    jr      ra
    addi    sp, sp, 0x180
END(Rnc_DecodeMethod1)

LEAF(Rnc_ReadHuffmanValue)
1:
    lhu     t0, 0(s0)
    addi    s0, s0, 0x2
    and     t0, t0, t6
    lhu     AT, 0(s0)
    addi    s0, s0, 0x2
    sub     t0, t0, AT
    bnez    t0, 1b
    nop
    lbu     t1, 0x3C(s0)
    nop
    sub     t7, t7, t1
    bgez    t7, 2f
    nop
    addu    t9, ra, zero
    jal     Rnc_RefillBitBuffer
    nop
    addu    ra, t9, zero
2:
    srlv    t6, t6, t1
    lbu     t0, 0x3D(s0)
    nop
    addi    AT, t0, -0x2
    bltz    AT, 4f
    nop
    addi    t0, t0, -0x1
    addu    t1, t0, zero
    addu    t2, t0, zero
    lhu     t0, 0x3E(s0)
    sub     t7, t7, t1
    and     t0, t0, t6
    bgez    t7, 3f
    nop
    addu    t9, ra, zero
    jal     Rnc_RefillBitBuffer
    nop
    addu    ra, t9, zero
3:
    srlv    t6, t6, t1
    addi    AT, zero, 0x1
    sllv    AT, AT, t2
    or      t0, AT, t0
4:
    jr      ra
    nop
END(Rnc_ReadHuffmanValue)
