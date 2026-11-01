#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
.set noreorder
.set noat

LEAF(__osSetFpcCsr)
    cfc1    v0, $31
    ctc1    a0, $31
    jr      ra
    nop
END(__osSetFpcCsr)
