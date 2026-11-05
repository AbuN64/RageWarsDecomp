#include "include_asm.h"
#include "../../include/EXTERNS.H"
#include "Common/lldivresult.h"
#include "types.h"

void lldiv(LldivResult *result, s64 numerator, s64 denominator) {
    result->quot = Libc_SignedDivide(numerator, denominator);
    result->rem = Libc_SignedRemainder(numerator, denominator);
}

