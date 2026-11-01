#ifndef COMMON_UNSIGNED_QUOTIENT_H
#define COMMON_UNSIGNED_QUOTIENT_H
#include "TYPES.H"
/* ROM normalized unsigned division: O32 a0:a1 and a2:a3 operands,
 * v0:v1 quotient. The divisor must be nonzero. */
u64 __udivdi3(u64 numerator, u64 divisor);
#endif
