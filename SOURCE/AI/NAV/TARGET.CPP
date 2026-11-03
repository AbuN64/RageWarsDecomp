#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "FX/TARGET.H"
#include "TYPES.H"
#include <ultra64.h>
#include "AI/PLAYER/SCALED_UPDATETARGETPITCH.H"

/* TARGET.CPP */


extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);

static inline AiTarget *setSelectedTarget(AiController *controller, AiTarget *target) {
    controller->target = target;
    return target;
}

/* Drops the current target when its player is dead, stunned or (in team play) on our team, then picks the
   preferred candidate, the nearest candidate or keeps the current one, and copies its position. */
s32 Target_UpdateTargetSelection(void *object) {
    AiController *controller = object;
    CVector3 *position;
    Player *linked;
    Player *alternate;
    f32 linkedDistance;
    f32 alternateDistance;
    s32 index;
    AiTarget *target;

    position = Scaled_GetControllerPosition(controller);
    if (controller->target != NULL) {
        linked = controller->target->player;
        if (linked->health == 0) {
            controller->target = NULL;
        }
        if (linked->reactionFlags & 0x20) {
            controller->target = NULL;
        }
        if (g_gameSettings.counters.teams != 0) {
            if (controller->player->profile->team == linked->profile->team) {
                controller->target = NULL;
            }
        }
        if (controller->target != NULL) {
            linked = controller->target->player;
            linkedDistance = Graphu64_GetPointDistance(&position->x, &linked->pos.x);
        } else {
            linked = NULL;
            linkedDistance = 0.0f;
        }
    } else {
        linked = NULL;
        linkedDistance = 0.0f;
    }
    if (controller->preferred != NULL && (controller->preferred->flags & 0x300000)) {
        alternate = controller->preferred->player;
        alternateDistance = Graphu64_GetPointDistance(&position->x, &alternate->pos.x);
    } else {
        alternate = NULL;
        alternateDistance = 0.0f;
    }
    if (Scaled_MatchesBehaviorStateFilter(controller) == 0 || linked == NULL) {
        if (Target_CountAcceptedTargets(controller) == 0) {
            controller->target = NULL;
            return 1;
        }
        if (alternate != NULL && Target_IsPreferredTargetAccepted(controller) != 0) {
            controller->target = (AiTarget *)alternate;
            controller->targetPosition.x = alternate->pos.x;
            target = (AiTarget *)alternate;
        } else {
            index = Target_FindNearestFlaggedTarget(controller);
            target = setSelectedTarget(controller, controller->candidates[index]);
            controller->targetPosition.x = target->position.x;
        }
    } else if (alternate != NULL && alternateDistance <= linkedDistance) {
        controller->target = (AiTarget *)alternate;
        controller->targetPosition.x = alternate->pos.x;
        target = (AiTarget *)alternate;
    } else {
        index = Target_FindNearestFlaggedTarget(controller);
        if (index != -1 && (f32)controller->candidateDistances[index] < linkedDistance) {
            target = setSelectedTarget(controller, controller->candidates[index]);
            controller->targetPosition.x = target->position.x;
        } else if (controller->state == 1 && 3072.0f < linkedDistance) {
            controller->target = NULL;
            return 1;
        } else {
            target = controller->target;
            controller->targetPosition.x = target->position.x;
        }
    }
    controller->targetPosition.y = target->position.y;
    controller->targetPosition.z = target->position.z;
    return 1;
}

/* Returns 1 when the preferred target is one of the accepted candidates. */
s32 Target_IsPreferredTargetAccepted(AiController *controller) {
    s32 i;

    if (controller->preferred == NULL) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (controller->candidates[i] == controller->preferred && controller->candidateAccepted[i] != 0) {
            return 1;
        }
    }
    return 0;
}

/* Counts the candidate slots that hold a target and are accepted. */
s32 Target_CountAcceptedTargets(AiController *controller) {
    s32 count;
    s32 i;

    count = 0;
    if (controller->candidateCount == 0) {
        return 0;
    }
    i = 0;
    do {
        if (controller->candidates[i] != NULL && controller->candidateAccepted[i] != 0) {
            count += 1;
        }
        i += 1;
    } while (i < 10);
    return count;
}

/* Returns the index of the nearest accepted candidate whose flags allow targeting, or -1. */
s32 Target_FindNearestFlaggedTarget(AiController *controller) {
    f32 distance;
    f32 unset;
    f32 nearest;
    s32 count;
    s32 mask;
    s32 found;
    s32 i;

    found = -1;
    nearest = -1.0f;
    i = 0;
    if (controller->candidateCount > 0) {
        mask = 0x300000;
        unset = nearest;
        count = controller->candidateCount;
        do {
            if ((controller->candidates[i]->flags & mask) &&
                ((distance = (f32)controller->candidateDistances[i], distance < nearest) || (nearest == unset)) &&
                (controller->candidateAccepted[i] != 0)) {
                nearest = distance;
                found = i;
            }
            i += 1;
        } while (i < count);
    }
    return found;
}

/* SETSELECTEDTARGET.CPP */
/* 800C6E84_13.CPP */
#if defined(VERSION_US)
unsigned int k_SetselectedtargetEncodedWords[2] = {
    0x08000000, 0x00001043,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_SetselectedtargetEncodedWordsBlock3[2] = {
    0x3FE52EDF, 0x3FE52EDF,
};
#endif

#if defined(VERSION_EU)
unsigned int k_SetselectedtargetEncodedWordsBlock2[2] = {
    0x00000000, 0x90420000,
};
#endif

#if defined(VERSION_DE)
unsigned int k_SetselectedtargetEncodedWordsBlock1[2] = {
    0x3F800000, 0x42A00000,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Target_FindNearestFlaggedTargetLiteralWord.c */
#endif

/* 800C7008.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C7008 */
unsigned int g_Target_FindNearestFlaggedTargetConstantWords[2] = {
    0x3DCCCCCD, 0x3C8EFA36,
};
#endif
