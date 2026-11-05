#include "include_asm.h"

/* VISDATA.CPP */

#if defined(VERSION_US)
/** Perform no operation. */
void Visdata_EmptyInitializeHookUs(void) {
}
#endif

#if defined(VERSION_US)
/** Perform no operation. */
void Visdata_EmptyInitializeHookSecondUs(void) {
}
#endif


#if defined(VERSION_EU)
void Visdata_EmptyHookEu(void) {}
#endif

#if defined(VERSION_EU_X)
/** Perform no operation. */
void Visdata_EmptyHookEuX(void) {
}
#endif

#if defined(VERSION_US)
/** Perform no operation. */
void Visdata_EmptyReleaseHookUs(void) {
}
#endif

#if defined(VERSION_US)
/** Perform no operation. */
void Visdata_EmptyReleaseHookSecondUs(void) {
}
#endif
