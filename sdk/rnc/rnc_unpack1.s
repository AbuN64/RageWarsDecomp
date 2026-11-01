#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(Rnc_UnpackMethod1)
    addi    sp, sp, -0x28
    sw      s0, 0(sp)
    sw      s1, 0x4(sp)
    sw      s2, 0x8(sp)
    sw      s3, 0xC(sp)
    sw      s4, 0x10(sp)
    sw      s5, 0x14(sp)
    sw      s6, 0x18(sp)
    sw      s7, 0x1C(sp)
    sw      ra, 0x20(sp)
    addu    s0, a0, zero
    addu    s1, a1, zero
    addu    s2, a2, zero
    addu    s3, a3, zero
    jal     Rnc_DecodeMethod1
    nop
    lw      s0, 0(sp)
    lw      s1, 0x4(sp)
    lw      s2, 0x8(sp)
    lw      s3, 0xC(sp)
    lw      s4, 0x10(sp)
    lw      s5, 0x14(sp)
    lw      s6, 0x18(sp)
    lw      s7, 0x1C(sp)
    lw      ra, 0x20(sp)
    addi    sp, sp, 0x28
    jr      ra
    nop
END(Rnc_UnpackMethod1)
