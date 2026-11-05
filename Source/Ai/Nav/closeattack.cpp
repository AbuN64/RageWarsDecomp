#include "include_asm.h"
#include "types.h"
#include "Common/brain.h"
#include "Ai/Player/scaled_updatetargetpitch.h"
#include "Attack/attack.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/portal_isnodemovementblocked.h"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
unsigned int k_CloseattackData[3] = {
    0x00804021, 0x00854821, 0x0109082B,
};
#endif
#if defined(VERSION_EU_X)
unsigned int k_CloseattackData[3] = {
    0x3FE52EDF, 0x3F800000, 0x3FE52EDF,
};
#endif
#endif

/* Route-following check for a computer driver's brain: when it has a target, it calls UpdateCloseAttack if
 * Nav_CheckTarget_de reports the target reached, and again when its route node (unless -1) lies closer than 100
 * to the position Scaled_GetControllerPosition gives; always returns one. */


struct Player;
