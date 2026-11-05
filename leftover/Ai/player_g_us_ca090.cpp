#include "Data/rest_source_records.h"
#include "include_asm.h"

#if defined(VERSION_US) || defined(VERSION_US_REV1)
float g_playerMovementTuningProfileTwo_us_CA090[8] = {
    5.12f, 15.36f, 3.84f, 5.12f,
    17.92f, 3.84f, 0.0f, 0.0f,
};
#endif

#if defined(VERSION_US_REV1)
u16 g_playerMovementTuningZeroHalfwordsAlternate_usrev1_CF3E0[2] = {
    0, 0,
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
float g_playerViewTuningProfileOne_usrev1_CF3E4[6] = {
    0.25f, 0.9f, 0.6f, 0.3f,
    -1.5707965f, 1.5707965f,
};
#endif

#if defined(VERSION_US_REV1)
float g_playerViewTuningProfileTwo_usrev1_CF3FC[6] = {
    0.25f, 0.9f, 0.6f, 0.3f,
    -0.78539824f, 1.5707965f,
};
#endif

#if defined(VERSION_US_REV1)
float g_playerViewTuningTail_usrev1_CF414[6] = {
    0.0f, 0.0f, 0.5f, 0.25f,
    -0.06981318f, 1.5707965f,
};
#endif
