#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const float g_pointCentroidUnitScale = 1.0f;
#endif


#if defined(VERSION_DE)
extern char addrLow_Nav_RefineBallisticAim[];
void *k_NavComputescaledpointcentroidEncodedWords[1] = {
    (void *)(addrLow_Nav_RefineBallisticAim + 336),
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_pointCentroidUnitScale_us_rev1.c */

/* ROM-grounded data: src/g_Nav_ComputeScaledPointCentroidConstantWords_NavComputescaledpointcentroidData.c */
const float g_Nav_ComputeScaledPointCentroidConstantWords[1] = {
    1.0f,
};
#endif
