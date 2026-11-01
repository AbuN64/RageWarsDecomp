#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(__osSetSR)
    mtc0    a0, C0_SR
    nop
    jr      ra
    nop
END(__osSetSR)
