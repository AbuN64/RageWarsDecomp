#include "COMMON/OBJRECAT20V1.H"
#include "ENGINE/SETN64.H"
#include "include_asm.h"

/* 802909E0_6.CPP */
#if defined(VERSION_US_REV1)
void SetN64_EmptySessionHookRev1A(void) {
}

void SetN64_EmptySessionHookRev1B(void) {
}

void SetN64_EmptySessionHookRev1C(void) {
}

#endif

/* 802909E0_7.CPP */
#if defined(VERSION_DE)
void SetN64_EmptySessionHookDeA(void) {

}

/* Alignment fill to the next 16-byte object boundary. */
unsigned char g_SessionRetainedStorageTrailingBytesBlock1AlignmentPad[8] = { 0x03, 0xE0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 };
#endif

/* 80290A80.CPP */
#if defined(VERSION_DE)
/** Perform no operation. */
void SetN64_EmptySessionHookDeB(void) {
}
#endif
