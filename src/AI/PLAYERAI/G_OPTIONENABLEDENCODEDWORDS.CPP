#include "TYPES.H"

/* Leading word of the target-facing distance limit pair (read as f32[], symbol_addrs name); Playerai_UpdateTargetFacing
   (PLAYERAI_INITIALIZEPLAYERHEALTH.CPP) only reads element [1], the f32 1024.0f right after it. */
s32 g_playerTargetFacingDistanceLimits = 1024;
