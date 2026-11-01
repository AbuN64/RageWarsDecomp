#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(Libgultra_SetWatchpoint)
    sll     a0, a0, 4
    srl     a0, a0, 4
    addi    v0, zero, -0x8
    and     a0, v0, a0
    andi    a1, a1, 0x3
    or      a0, a1, a0
    mtc0    a0, C0_WATCHLO
    nop
    nop
    nop
    nop
    mfc0    zero, C0_WATCHHI
    nop
    nop
    nop
    jr      ra
    nop
END(Libgultra_SetWatchpoint)
