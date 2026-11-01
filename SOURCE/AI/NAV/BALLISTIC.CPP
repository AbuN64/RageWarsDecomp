#include "include_asm.h"
#include "COMMON/LONE/PARTICLE_COLLISION_PROBE_RESULT.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/ACTORREC.H"
#include "TYPES.H"
#include "ENGINE/DEFS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "MATH/DOUBLEBITS.H"

f32 Rumble_SamplePackedFloatRange(s32 packedRange);

extern World *g_collisionCurrentActor;

extern s32 CCollision_SweepPoint(InstanceHdr *actorStorage, CVector3 current, CVector3 desired,
                          void *collisionInfo);

s32 Nav_IsBallisticArcObstructed(ActorRec *actor, f32 scale, f32 lateral);

/* BALLISTIC.CPP */
/* Refine a launch angle by testing a ballistic arc against the destination.
 * State 0 initializes the bounds; later calls bisect the chosen quadrant. */
s32 Nav_RefineBallisticAim(ActorRec *actor) {
    CVector3 current;
    CVector3 delta;
    s32 first, last;
    s32 keyCount;
    BallisticInstance *instance;
    BallisticInstance *activeInstance;
    f32 angleCosineSquared;
    f32 horizontalDistance;
    f32 heightDelta;
    f32 scale;
    f32 deltaX;
    f32 lateral;
    f32 angleCosine;
    f32 deltaZ;
    f32 trajectoryHeight;
    f32 initialHeightDelta;
    f32 currentDeltaZ;
    f32 fallbackPitch;
    f32 initialDeltaX;
    f32 currentDeltaY;
    f32 secondaryPitch;
    s32 trajectoryMode;
    s32 *ballisticResource;
    s32 obstructedQuadrant;
    s32 iterationState;
    s32 nextIteration;
    s32 initialQuadrant;
    s32 secondaryQuadrant;
    s32 fallbackQuadrant;
    BallisticResourceKeys *resourceKeys;
    u32 resourceKey;
    BallisticParamsHolder *parameterRecord;
    BallisticParams *speedParameters;
    BallisticParams *gravityParameters;

    trajectoryMode = actor->instance->trajectoryMode;
    resourceKey = 0;
    if (trajectoryMode != actor->trajectoryMode) {
        actor->trajectoryInitialized = 0;
        actor->trajectoryMode = (s32) trajectoryMode;
    }
    if (actor != 0) {
        iterationState = actor->trajectoryInitialized;
        if (iterationState == 0) {
            instance = actor->instance;
            current = instance->header.spatial.position;
            delta = actor->destination;
            initialDeltaX = delta.x - current.x;
            initialHeightDelta = delta.y - current.y;
            deltaZ = delta.z - current.z;
            delta.x = initialDeltaX;
            delta.y = initialHeightDelta;
            delta.z = deltaZ;
            actor->trajectoryDistance = Gu_Sqrtf((initialDeltaX * initialDeltaX) + (initialHeightDelta * initialHeightDelta) + (deltaZ * deltaZ));
            heightDelta = delta.y;
            delta.y = 0;
            horizontalDistance = Gu_Sqrtf((delta.x * delta.x) + (delta.z * delta.z));
            {
                switch (trajectoryMode) {
                case 10:
                case 12:
                    actor->trajectoryInitialized = 1;
                    actor->trajectoryPending = 1;
                    actor->trajectoryComplete = 0;
                    break;
                case 6:
                case 8:
                    actor->trajectoryInitialized = 11;
                    actor->trajectoryPending = 0;
                    actor->trajectoryComplete = 1;
                    break;
                case 9:
                    actor->trajectoryInitialized = 1;
                    actor->trajectoryPending = 1;
                    actor->trajectoryComplete = 1;
                    break;
                default:
                case 7:
                case 11:
                if (horizontalDistance == 0.0f) {
                    if (heightDelta < 0.0f) {
                        actor->initialPitch = (f32) -90.0f;
                    } else {
                        actor->initialPitch = (f32) 90.0f;
                    }
                } else {
                    actor->initialPitch = (f32) (XMath_EvaluateArcTangentTwo(heightDelta, horizontalDistance) * 57.2957764f);
                }
                actor->trajectoryPending = 0;
                actor->trajectoryComplete = 0;
                actor->previousPitch = actor->initialPitch;
                actor->previousPitchDelta = actor->pitchDelta = 0.0f;
                return 1;
                }
                    if (horizontalDistance == 0.0f) {
                        if (heightDelta < 0.0f) {
                            actor->targetPitch = -90.0f;
                        } else {
                            actor->targetPitch = 90.0f;
                        }
                    } else {
                        actor->targetPitch = XMath_EvaluateArcTangentTwo(heightDelta, horizontalDistance) * 57.2957764f;
                    }
                    actor->previousPitch = actor->targetPitch;
                    if (45.0f < actor->targetPitch) {
                        actor->pitchSearchStep = 0;
                    } else {
                        initialQuadrant = 1;
                        if (!(actor->targetPitch > 0.0f)) {
                            initialQuadrant = 2;
                            if (!(-45.0f < actor->targetPitch)) {
                                initialQuadrant = 3;
                            }
                        }
                        actor->pitchSearchStep = initialQuadrant;
                    }
                    actor->upperPitchBound = 90.0f - ((f32) actor->pitchSearchStep * 45.0f);
                    actor->lowerPitchBound = actor->targetPitch;
                    actor->targetPitch = (actor->upperPitchBound + actor->lowerPitchBound) * 0.5f;
                    if (actor->trajectoryPending != 0) {
                        actor->previousPitch = actor->targetPitch;
                    }
                    return 0;
            }
        } else {
            if (iterationState < 11) {
                switch (trajectoryMode) {
                case 2: resourceKey = 302; break;
                case 9: resourceKey = 302; break;
                case 10: resourceKey = 302; break;
                case 12: resourceKey = 302; break;
                }
            } else if (iterationState < 21) {
                actor->trajectoryPending = 0;
                switch (trajectoryMode) {
                case 6: resourceKey = 302; break;
                case 8: resourceKey = 302; break;
                case 9: resourceKey = 302; break;
                }
            } else {
                goto block_88;
            }
            {
block_43:
                if (actor->trajectoryInitialized < 21) {
                    ballisticResource = g_ballisticParameterResource;
                    resourceKeys = (void *)SetN64_GetPackSection(ballisticResource, 1);
                    keyCount = resourceKeys->count;
                    if (Defs_FindSortedGroupRange(resourceKeys->keys, keyCount, resourceKey, &first, &last) == 0) {
                        actor->trajectoryPending = 0;
                        actor->trajectoryComplete = 0;
                        actor->trajectoryInitialized = 0;
                        return 1;
                    }
                    {
                        BallisticResourceRecords *records = (void *)SetN64_GetPackSection(ballisticResource, 2);
                        parameterRecord = records->records;
                        parameterRecord += first;
                    }
                    speedParameters = parameterRecord->parameters;
                    scale = Rumble_SamplePackedFloatRange((speedParameters->speedHi << 16) | speedParameters->speedLo);
                    gravityParameters = parameterRecord->parameters;
                    lateral = Rumble_SamplePackedFloatRange((gravityParameters->gravityHi << 16) | gravityParameters->gravityLo);
                    activeInstance = actor->instance;
                    current = activeInstance->header.spatial.position;
                    delta = actor->destination;
                    deltaX = delta.x - current.x;
                    currentDeltaY = delta.y - current.y;
                    currentDeltaZ = delta.z - current.z;
                    delta.x = deltaX;
                    delta.y = currentDeltaY;
                    delta.z = currentDeltaZ;
                    actor->trajectoryDistance = Gu_Sqrtf((deltaX * deltaX) + (currentDeltaY * currentDeltaY) + (currentDeltaZ * currentDeltaZ));
                    heightDelta = delta.y;
                    delta.y = 0;
                    horizontalDistance = Gu_Sqrtf((delta.x * delta.x) + (delta.z * delta.z));
                    angleCosine = Math_Cosf(actor->targetPitch * 0.0174532942f);
                    angleCosineSquared = angleCosine * angleCosine;
                    trajectoryHeight = (XMath_EvaluateTangent(actor->targetPitch * 0.0174532942f) * horizontalDistance) + ((lateral * (horizontalDistance * horizontalDistance)) / (2.0f * (scale * scale) * angleCosineSquared));
                    if (((heightDelta - 1.0f) <= trajectoryHeight) && (trajectoryHeight <= (heightDelta + 1.0f))) {
                        if (Nav_IsBallisticArcObstructed(actor, scale, lateral) != 0) {
                            obstructedQuadrant = actor->pitchSearchStep;
                            if (obstructedQuadrant > 0) {
                                actor->pitchSearchStep--;
                                actor->upperPitchBound = (f32) (90.0f - ((f32) actor->pitchSearchStep * 45.0f));
                                actor->lowerPitchBound = (f32) (45.0f - ((f32) actor->pitchSearchStep * 45.0f));
                                if (actor->trajectoryPending != 0) {
                                    actor->trajectoryInitialized = 1;
                                } else {
                                    actor->trajectoryInitialized = 11;
                                }
block_54:
                                return 0;
                            }
                        }
                        if ((actor->trajectoryPending != 0) && (actor->trajectoryComplete != 0)) {
                            actor->trajectoryInitialized = 11;
                            actor->trajectoryPending = 0;
                            actor->pitchDelta = (f32) (actor->targetPitch - actor->initialPitch);
                            secondaryPitch = actor->previousPitch;
                            if (45.0f < secondaryPitch) {
                                actor->pitchSearchStep = 0;
                            } else {
                                secondaryQuadrant = 1;
                                if (!(secondaryPitch > 0.0f)) {
                                    secondaryQuadrant = 2;
                                    if (!(-45.0f < secondaryPitch)) {
                                        secondaryQuadrant = 3;
                                    }
                                }
                                actor->pitchSearchStep = secondaryQuadrant;
                            }
                            actor->upperPitchBound = (f32) (90.0f - ((f32) actor->pitchSearchStep * 45.0f));
                            actor->lowerPitchBound = (f32) (45.0f - ((f32) actor->pitchSearchStep * 45.0f));
                            return 0;
                        }
                        actor->trajectoryPending = 0;
                        actor->trajectoryComplete = 0;
                        actor->trajectoryInitialized = (s32) (actor->trajectoryInitialized + 1);
                        actor->pitchDelta = (f32) (actor->targetPitch - actor->initialPitch);
                        return 1;
                    }
                    nextIteration = actor->trajectoryInitialized + 1;
                    if (nextIteration == 11) {
                        fallbackPitch = actor->previousPitch;
                        actor->trajectoryPending = 0;
                        actor->trajectoryInitialized = (s32) (actor->trajectoryInitialized + 1);
                        actor->pitchDelta = (f32) (actor->targetPitch - actor->initialPitch);
                        if (45.0f < fallbackPitch) {
                            actor->pitchSearchStep = 0;
                        } else {
                            fallbackQuadrant = 1;
                            if (!(fallbackPitch > 0.0f)) {
                                fallbackQuadrant = 2;
                                if (!(-45.0f < fallbackPitch)) {
                                    fallbackQuadrant = 3;
                                }
                            }
                            actor->pitchSearchStep = fallbackQuadrant;
                        }
                        actor->upperPitchBound = (f32) (90.0f - ((f32) actor->pitchSearchStep * 45.0f));
                        actor->lowerPitchBound = (f32) (45.0f - ((f32) actor->pitchSearchStep * 45.0f));
                        if (actor->trajectoryComplete == 0) {
                            actor->trajectoryInitialized = 0;
                        }
                        return actor->trajectoryComplete == 0;
                    }
                    if (nextIteration >= 21) {
                        actor->trajectoryPending = 0;
                        actor->trajectoryComplete = 0;
                        actor->trajectoryInitialized = (s32) (actor->trajectoryInitialized + 1);
                        actor->previousPitchDelta = (f32) (actor->targetPitch - actor->previousPitch);
                        return 1;
                    }
                    if (trajectoryHeight < (heightDelta - 1.0f)) {
                        switch (actor->pitchSearchStep) {
                        case 0: actor->upperPitchBound = actor->targetPitch; break;
                        case 1: case 2: case 3: actor->lowerPitchBound = actor->targetPitch; break;
                        }
                    } else {
                        switch (actor->pitchSearchStep) {
                        case 0: actor->lowerPitchBound = actor->targetPitch; break;
                        case 1: case 2: case 3: actor->upperPitchBound = actor->targetPitch; break;
                        }
                    }
                    actor->trajectoryInitialized = (s32) (actor->trajectoryInitialized + 1);
                    actor->targetPitch = (actor->upperPitchBound + actor->lowerPitchBound) * 0.5f;
                    return 0;
                }
                goto block_88;
            }
block_88:
            actor->trajectoryInitialized = 0;
            actor->trajectoryPending = 0;
            actor->trajectoryComplete = 0;
            /* Duplicate return node #89. Try simplifying control flow for better match */
            return 1;
        }
    } else {
        return 1;
    }
}

s32 Nav_IsBallisticArcObstructed(ActorRec *actor, f32 scale, f32 lateral) {
    CVector3 current;
    CVector3 desired;
    CVector3 delta;
    CVector3 acceleration;
    f32 invDuration;
    f32 total;
    f32 segment;
    f32 elapsed;
    f32 accelScale;
    f32 accelX;
    f32 accelY;
    f32 accelZ;
    s32 count;
    s32 i;

    if (actor == 0 || actor->trajectoryDistance == 0.0f) {
        return 0;
    }

    invDuration = g_ballisticInverseDistanceScale / actor->trajectoryDistance;
    delta.x = (actor->destinationX - actor->instance->header.spatial.position.x) * invDuration;
    delta.x *= scale * Math_Cosf(actor->targetPitch);
    delta.z = (actor->destinationZ - actor->instance->header.spatial.position.z) * invDuration;
    delta.z *= scale * Math_Cosf(actor->targetPitch);
    delta.y = scale * Gu_Sinf(actor->targetPitch);

    acceleration.x = 0.0f;
    acceleration.y = lateral;
    acceleration.z = 0.0f;

    total = (scale * Math_Cosf(actor->targetPitch)) / actor->trajectoryDistance;
    if (total == 0.0f) {
        return 0;
    }
    count = (s32)(total * g_ballisticArcSampleRate);
    if (count == 0) {
        return 0;
    }

    segment = total / (f32)count;
    current = actor->instance->header.spatial.position;
    accelScale = segment * segment * g_ballisticAccelerationScale;
    accelX = acceleration.x * accelScale;
    accelY = acceleration.y * accelScale;
    accelZ = acceleration.z * accelScale;

    desired.x = current.x + delta.x * segment + accelX;
    desired.y = current.y + delta.y * segment + accelY;
    desired.z = current.z + delta.z * segment + accelZ;

    elapsed = segment;

    if (CCollision_SweepPoint(&actor->instance->header, current, desired, &g_particleCollisionProbeResult) != 0 &&
        (unsigned)(g_collisionCurrentActor->state - 7) >= 2) {
        return 1;
    }

    i = 0;
    delta.x += acceleration.x * elapsed;
    delta.y += acceleration.x * elapsed;
    delta.z += acceleration.x * elapsed;
    elapsed += segment;

    while (i < count) {
        current = desired;
        desired.x = current.x + delta.x * elapsed + accelX;
        desired.y = current.y + delta.y * elapsed + accelY;
        desired.z = current.z + delta.z * elapsed + accelZ;

        if (CCollision_SweepPoint(&actor->instance->header, current, desired, &g_particleCollisionProbeResult) != 0 &&
            (unsigned)(g_collisionCurrentActor->state - 7) >= 2) {
            return 1;
        }

        delta.x += acceleration.x * elapsed;
        delta.y += acceleration.x * elapsed;
        delta.z += acceleration.x * elapsed;
        elapsed += segment;
        i++;
    }
    return 0;
}

/* NAV_ISBALLISTICARCOBSTRUCTED_DATA.CPP */
#if defined(VERSION_US)
unsigned int k_NavIsballisticarcobstructedEncodedWordsBlock1[1] = {
    0x52000000,
};
#endif

#if defined(VERSION_DE)
unsigned int k_NavIsballisticarcobstructedEncodedWordsBlock2[1] = {
    0x10400002,
};
#endif

/* G_NAVENCODEDWORDSBLOCK2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C6F3C */
extern char g_Playerai_ApplyLinkedProjectileStatusAddressUsRev1[];
void *g_NavEncodedWordsBlock2[1] = {
    (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressUsRev1 + 2276),
};
#endif

/* NAV_ISBALLISTICARCOBSTRUCTED_DATA.CPP */
const float k_NavIsballisticarcobstructedEncodedWords[3] = {
    1.0f, 1.3333334f, 0.5f,
};
