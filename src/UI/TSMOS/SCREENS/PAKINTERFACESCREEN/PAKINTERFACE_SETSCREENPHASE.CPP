#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "FRONTEND/PAKINTERFACE_SETSCREENPHASE.H"

/* Stores its argument in g_pakProfileRequestedPhase. */


void PAKInterface_SetScreenPhase(s32 value) {
    g_pakProfileRequestedPhase = value;
}
