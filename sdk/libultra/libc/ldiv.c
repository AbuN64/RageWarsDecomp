#include "include_asm.h"
#include "../../include/EXTERNS.H"
#include "COMMON/LLDIVRESULT.H"
#include "TYPES.H"

void lldiv(LldivResult *result, s64 numerator, s64 denominator) {
    result->quot = Libc_SignedDivide(numerator, denominator);
    result->rem = Libc_SignedRemainder(numerator, denominator);
}

