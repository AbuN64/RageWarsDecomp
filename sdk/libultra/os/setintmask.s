#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(osSetIntMask)
    mfc0    t4, C0_SR
    lui     t0, %hi(__OSGlobalIntMask)
    addiu   t0, t0, %lo(__OSGlobalIntMask)
    andi    v0, t4, 0xFF01
    lw      t3, 0(t0)
    nop
    li      AT, -0x1
    xor     t0, t3, AT
    andi    t0, t0, 0xFF00
    or      v0, v0, t0
    lui     t2, %hi(MI_INTERRUPT_MASK_REGISTER)
    lw      t2, %lo(MI_INTERRUPT_MASK_REGISTER)(t2)
    nop
    beqz    t2, 1f
    srl     t1, t3, 16
    li      AT, -0x1
    xor     t1, t1, AT
    andi    t1, t1, 0x3F
    or      t2, t2, t1
1:
    sll     t2, t2, 16
    or      v0, v0, t2
    lui     AT, 0x3F
    and     t0, a0, AT
    and     t0, t0, t3
    srl     t0, t0, 15
    lui     AT, %hi(g_interruptMaskCommandTable)
    addu    AT, AT, t0
    lhu     t2, %lo(g_interruptMaskCommandTable)(AT)
    lui     AT, %hi(MI_INTERRUPT_MASK_REGISTER)
    sw      t2, %lo(MI_INTERRUPT_MASK_REGISTER)(AT)
    andi    t0, a0, 0xFF01
    andi    t1, t3, 0xFF00
    and     t0, t0, t1
    lui     AT, 0xFFFF
    ori     AT, AT, 0xFF
    and     t4, t4, AT
    or      t4, t4, t0
    mtc0    t4, C0_SR
    nop
    nop
    jr      ra
    nop
END(osSetIntMask)
