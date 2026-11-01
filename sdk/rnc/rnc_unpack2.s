#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(Rnc_UnpackMethod2)
    addi    sp, sp, -0x48
    sw      a0, 0(sp)
    sw      a1, 0x4(sp)
    sw      a2, 0x8(sp)
    sw      a3, 0xC(sp)
    sw      t0, 0x10(sp)
    sw      t1, 0x14(sp)
    sw      t2, 0x18(sp)
    sw      t3, 0x1C(sp)
    sw      t4, 0x20(sp)
    sw      t5, 0x24(sp)
    sw      t6, 0x28(sp)
    sw      t7, 0x2C(sp)
    sw      s0, 0x30(sp)
    sw      s1, 0x34(sp)
    sw      s2, 0x38(sp)
    sw      s3, 0x3C(sp)
    sw      ra, 0x40(sp)
    lui     t4, %hi(Rnc_UnpackMethod2CallKuseg)
    addiu   t4, t4, %lo(Rnc_UnpackMethod2CallKuseg)
    nop
    jalr    t4
    nop
    lw      a0, 0(sp)
    lw      a1, 0x4(sp)
    lw      a2, 0x8(sp)
    lw      a3, 0xC(sp)
    lw      t0, 0x10(sp)
    lw      t1, 0x14(sp)
    lw      t2, 0x18(sp)
    lw      t3, 0x1C(sp)
    lw      t4, 0x20(sp)
    lw      t5, 0x24(sp)
    lw      t6, 0x28(sp)
    lw      t7, 0x2C(sp)
    lw      s0, 0x30(sp)
    lw      s1, 0x34(sp)
    lw      s2, 0x38(sp)
    lw      s3, 0x3C(sp)
    lw      ra, 0x40(sp)
    addi    sp, sp, 0x48
    jr      ra
    addu    t6, a0, zero
END(Rnc_UnpackMethod2)
