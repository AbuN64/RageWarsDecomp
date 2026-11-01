#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/BRAIN.H"


#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
unsigned int k_CloseattackEncodedWords[3] = {
    0x00804021, 0x00854821, 0x0109082B,
};
#endif
#if defined(VERSION_EU_X)
unsigned int k_CloseattackEncodedWords[3] = {
    0x3FE52EDF, 0x3F800000, 0x3FE52EDF,
};
#endif
#endif

/* Route-following check for a computer driver's brain: when it has a target at 0x64, it calls UpdateCloseAttack if Nav_CheckTarget_de reports the target reached, and again when its route node at 0xC (unless -1) lies closer than 100 to the position Scaled_GetControllerPosition gives; always returns one. */



extern s32 Scaled_HasLineOfSight(Brain *, void *);
extern void UpdateCloseAttack(Brain *brainAddress);
extern void *Scaled_GetControllerPosition(Brain *controller);
extern void *Portal_GetGraphPoint(char *, s32);
extern f32 Graphu64_GetPointDistance(void *, void *);

