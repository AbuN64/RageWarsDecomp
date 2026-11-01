#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/GAMEPLAY_REACTION_RULES.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ACTORREC.H"
#include "TYPES.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/NAV/NAV_EVALUATECAPTUREFLAGMARKERSEARCH.H"
#include "include_asm.h"

/* TEAMMARKER__TEAMMARKER.CPP */
extern f32 Scaled_GetScaledAggression(void *controller);

extern s32 g_matchRoundCounters;

s32 Nav_ShouldSeekUnclaimedTeamMarker(void **controller) {
    char *base;
    f32 seekThreshold;

    base = (char *)&g_matchRoundCounters;
    if (((Shared_MatchRules *)base)->squads == 0) {
        return 0;
    }
    if (((Shared_ActorView *)*controller)->controls->transientFlag != 0) {
        return 0;
    }
    if (Playerai_FindPlayerWithMarker(base - ((char *)&((Shared_MenuData *)0)->game.counters - (char *)0)) != 0) {
        return 0;
    }
    seekThreshold = Scaled_GetScaledAggression(controller) * g_teamMarkerAggressionScale + g_teamMarkerSeekBaseThreshold;
    if (seekThreshold < Graphu64_RandomBetween(0.0f, g_teamMarkerSeekRandomRange)) {
        return 1;
    }
    return 0;
}

s32 Nav_EvaluateCaptureFlagMarkerSearch(void **controller) {
    if (g_gameSettings.counters.m_bCTFOn != 0) {
        Nav_ShouldSeekUnclaimedTeamMarker(controller);
    }
    return 1;
}

/* ROM-grounded data: src/Nav_ShouldSeekUnclaimedTeamMarkerConstantWords.c */
const float g_Nav_ShouldSeekUnclaimedTeamMarkerConstantWords[3] = {
    0.6f, 0.2f, 1.0f,
};

#if defined(VERSION_US)
unsigned int k_TeammarkerEncodedWords[1] = {
    0x4353776F,
};
#endif

#if defined(VERSION_EU_X)
extern char g_Playerai_ApplyLinkedProjectileStatusAddressEuX[];
void *k_TeammarkerEncodedWordsBlock2[1] = {
    (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressEuX + 2276),
};
#endif

#if defined(VERSION_DE)
extern char addrLow_Nav_RebuildRequestedGoalRoute[];
void *k_TeammarkerEncodedWordsBlock1[1] = {
    (void *)(addrLow_Nav_RebuildRequestedGoalRoute + 544),
};
#endif

/* G_NAVENCODEDWORDSBLOCK5.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C6F4C */
extern char g_Playerai_ApplyLinkedProjectileStatusAddressUsRev1[];
void *g_NavEncodedWordsBlock5[1] = {
    (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressUsRev1 + 2276),
};
#endif
