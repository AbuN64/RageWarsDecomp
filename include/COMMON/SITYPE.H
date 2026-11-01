#ifndef COMMON_SITYPE_H
#define COMMON_SITYPE_H
#include "TYPES.H"
#include "COMMON/AUDIO_CALLBACKS.H"

/* The conversion helpers this cartridge keeps in one code group at 0x802C074C. Each helper owns its
 * own bytes; only the ones written as C need a declaration here. */
double Libc_SignedLongLongToDoubleUsRev1(long long u);

typedef int SItype;
typedef long long DItype;
typedef double DFtype;
#endif
