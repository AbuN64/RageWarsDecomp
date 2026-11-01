#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(osMapTLB)
    lw      t8, 0x10(sp)
    addi    t0, zero, 0x7
    lw      t9, 0x14(sp)
    addi    t7, zero, -0x1
    and     t9, t9, t0
    and     t1, a3, t8
    beq     t1, t7, osUnmapTLB
    ori     t9, t9, 0x18
    mfc0    t0, C0_ENTRYHI
    mtc0    a0, C0_INX
    mtc0    a1, C0_PAGEMASK
    mtc0    a2, C0_ENTRYHI
    beq     a3, t7, 1f
    addi    t6, zero, 0x1
    srl     t5, a3, 6
    or      t5, t5, t9
    b       2f
    mtc0    t5, C0_ENTRYLO0
1:
    mtc0    t6, C0_ENTRYLO0
2:
    beq     t8, t7, 3f
    mtc0    t6, C0_ENTRYLO1
    srl     t5, t8, 6
    or      t5, t5, t9
    mtc0    t5, C0_ENTRYLO1
3:
    tlbwi
    nop
    nop
    nop
    nop
    mtc0    t0, C0_ENTRYHI
    jr      ra
    nop
END(osMapTLB)
