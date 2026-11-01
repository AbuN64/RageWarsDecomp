#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/BRAIN.H"

/* CLOSEATTACK__CLOSEATTACK.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
#endif
#if defined(VERSION_EU_X)
#endif
#endif

/* Route-following check for a computer driver's brain: when it has a target at 0x64, it calls UpdateCloseAttack if Nav_CheckTarget_de reports the target reached, and again when its route node at 0xC (unless -1) lies closer than 100 to the position Scaled_GetControllerPosition gives; always returns one. */

extern char g_navigationGraph[];

struct Player; extern s32 Scaled_HasLineOfSight(struct Player **fromRef, struct Player *target);
extern void UpdateCloseAttack(Brain *brainAddress);
extern void *Scaled_GetControllerPosition(Brain *controller);
extern void *Portal_GetGraphPoint(char *, s32);
extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);

s32 Nav_CheckCloseAttackRoute(Brain *brain) {
    void *pos;

    if (brain->target == 0) {
        return 1;
    }
    if (Scaled_HasLineOfSight(brain, brain->target) != 0) {
        UpdateCloseAttack(brain);
    }
    if (brain->destination == -1) {
        return 1;
    }
    pos = Scaled_GetControllerPosition(brain);
    if (Graphu64_GetPointDistance(pos, Portal_GetGraphPoint(g_navigationGraph, brain->destination)) < 100.0f) {
        UpdateCloseAttack(brain);
    }
    return 1;
}

/* K_NAVENCODEDWORDSBLOCK6__CLOSEATTACK.CPP */
/* 800C6E84_15.CPP */
#if defined(VERSION_US)
#endif

#if defined(VERSION_EU_X)
#endif

/* 800C6E84_5.CPP */
#if defined(VERSION_EU)
unsigned int k_NavEncodedWordsBlock5[3] = {
    0x00000000, 0x03E00008, 0x00000000,
};
#endif

/* G_NAV_EVALUATEATTACKTARGETCONSTANTWORDS.CPP */
#if defined(VERSION_DE)
float g_Nav_EvaluateAttackTargetConstantWords[3] = {
    921.6f, 512.0f, 0.78539824f,
};
#endif

/* K_NAVCHECKCLOSEATTACKROUTEWORDSUS__CLOSEATTACK.CPP */
/* 800C1E68_2.CPP */
#if defined(VERSION_US)
unsigned int k_NavCheckCloseAttackRouteWordsUs[3] = {
    0x00000800, 0x11000000, 0x0000086D,
};
#endif
/* 800C2298.CPP */
#if defined(VERSION_EU)
/* ROM-grounded data for eu; supplied-list member has no us-rev1 placement. */
#endif

/* 80208000_28.CPP */
#if defined(VERSION_EU_X)
#endif

/* NAV_CHECKCLOSEATTACKROUTE_ENCODED_WORDS_US_REV1.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C7034 */
float g_NavCheckcloseattackrouteEncodedWordsBlock1[3] = {
    1.0f, 1.0f, 25.0f,
};
#endif
