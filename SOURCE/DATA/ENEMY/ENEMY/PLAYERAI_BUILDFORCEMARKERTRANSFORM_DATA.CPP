#include "include_asm.h"

/* ROM-grounded data: rodata/shared/800D0EF8 */
/* Light colour bytes (r, g, b, pad): bytes so every host reads the same colour. */
const char k_PlayeraiBuildforcemarkertransformEncodedBytes[4] = "888";

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char k_playeraiForceMarkerLightColorWord[4] = "888";
#endif
