#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(__osGetSR)
    mfc0    v0, C0_SR
    jr      ra
    nop
END(__osGetSR)
