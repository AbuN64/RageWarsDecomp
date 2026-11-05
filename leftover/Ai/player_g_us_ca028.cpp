#include "include_asm.h"
#include "Data/rest_source_records.h"

const float g_playerMountedMovementSpeedConstantsUsRevisionOne[1] = {
    34.559998f,
};

#if defined(VERSION_US_REV1)
float g_playerTuningFloatTriplesUsRevisionOne[16] = {
    1.7280002f, 2.7648f, 20.736f, 1.0368001f, 0.0f, 0.0f,
    0.0f, 2.88f, 21.599998f, 1.08f, 1.7280002f, 12.960001f,
    0.64800006f, 0.0f, 0.0f, 0.0f,
};
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
float g_playerMovementTuningProfileOneUsRevisionOne[8] = {
    10.24f, 30.72f, 13.44f, 10.24f,
    35.84f, 13.44f, 0.0f, 0.0f,
};
#endif

#if defined(VERSION_US_REV1)
u16 g_playerMovementTuningZeroHalfwordsUsRevisionOne[2] = {
    0, 0,
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif
