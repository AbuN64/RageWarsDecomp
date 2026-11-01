#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(__osProbeTLB)
    mfc0    t0, C0_ENTRYHI
    nop
    andi    t1, t0, 0xFF
    li      AT, -0x2000
    and     t2, a0, AT
    or      t1, t1, t2
    mtc0    t1, C0_ENTRYHI
    nop
    nop
    nop
    tlbp
    nop
    nop
    mfc0    t3, C0_INX
    nop
    lui     AT, 0x8000
    and     t3, t3, AT
    bnez    t3, 3f
    nop
    tlbr
    nop
    nop
    nop
    mfc0    t3, C0_PAGEMASK
    nop
    addi    t3, t3, 0x2000
    srl     t3, t3, 1
    and     t4, t3, a0
    bnez    t4, 1f
    addi    t3, t3, -0x1
    mfc0    v0, C0_ENTRYLO0
    bgez    zero, 2f
    nop
1:
    mfc0    v0, C0_ENTRYLO1
2:
    nop
    andi    t5, v0, 0x2
    beqz    t5, 3f
    nop
    lui     AT, 0x3FFF
    ori     AT, AT, 0xFFC0
    and     v0, v0, AT
    sll     v0, v0, 6
    and     t5, a0, t3
    add     v0, v0, t5
    bgez    zero, 4f
    nop
3:
    li      v0, -0x1
4:
    mtc0    t0, C0_ENTRYHI
    jr      ra
    nop
END(__osProbeTLB)
