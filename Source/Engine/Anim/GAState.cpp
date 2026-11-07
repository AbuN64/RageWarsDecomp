#include "Common/localdecoderange.h"
#include "System/polytrak2_decodescalarsamples_data.h"
#include "Common/sharedplayer.h"
#include "Common/resident_event_handler.h"
#include "Common/approachlocation.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/mtx.h"
#include "types.h"
#include "Engine/Instance/gastate_advancerootmotion_data.h"
#include "Game/builddirectionmatrix.h"
#include "Scene/cache_requestresource.h"
#include "System/polytrak2_interpolatejointquaternion.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/Anim/BitArray.h"
#include "Engine/session.h"
#include "Engine/Anim/GAState.h"
#include "Engine/Anim/compressed_motion.h"
#include "Common/actorresourceheader.h"
#include "Common/runtime_declarations.h"
#include "Common/packedmeshmaterial.h"
#include "Scene/cache_allocatememory.h"
#include "Common/animation_pool.h"
#include "Common/manager.h"
#include "Scene/cache_allocateresourceat.h"
#include "Common/aiprofile.h"
#include "include_asm.h"
#include "Common/stream.h"
#include "Game/soundinfo.h"
#include "Common/results.h"

/* GASTATE.CPP */

/* Switches an animation track to its pending clip when asked and the clip differs: keeps a copy of the track, loads the pending clip's resource and, when it is ready, reads its frame count and length, hands the old state to the previous track slot, restarts the track on the new clip and reports the switch; otherwise, or when not switching, it reloads the current clip and reports no switch. */

static inline s32 load(Anim *anim, s32 table, s32 key, s32 id) {
    s32 size;
    s32 clip;
    void *header;

    if (id == -1) {
        anim->resource = 0;
        return 0;
    }
    clip = SetN64_LocatePackSection(table, key, id, &size);
    anim->resource = Cache_RequestResource(0, clip, clip, size, 4, anim, &Gastate_AnimationResourceCallbackEntry, &g_animationText, 0);
    if (Gastate_IsAnimationResourceRetained(anim) == 0) {
        return 0;
    }
    header = Polytrak2_GetResidentResource(anim);
    anim->frames = ((u16 *)SetN64_GetPackSection(header, 0))[3];
    anim->current = id;
    anim->length = ((u16 *)SetN64_GetPackSection(SetN64_GetPackSection(header, 3), 0))[1];
    return 1;
}


static __inline__ f64 unsignedDouble(u32 value,const f64 *bias) {
    f64 result=(f64)(s32)value;
    if ((s32)value<0) result+=*bias;
    return result;
}

static __inline__ f32 wrapAngle(CGameAnimateState_t *anim,f32 time) {
    s16 *keys;
    s32 first,next,last;
    keys=((AngleKeys *)SetN64_GetPackSection(Polytrak2_GetResidentResource(anim),0))->keys;
    first=(s32)time;
    next=first+1;
    last=anim->frames-1;
    if(next<last) last=next;
    return Graphu64_InterpolateWrappedValue(time-(f32)first,(f32)keys[first]*g_rootMotionWrappedAngleScale,(f32)keys[last]*g_rootMotionWrappedAngleScale);
}

void Gastate_SwitchRequestedAnimation(Anim *anim, s32 table, s32 key, s32 blend, s32 *switched, Anim *previous) {
    s32 current;
    s32 next;
    Anim saved;

    current = anim->current;
    next = anim->next;
    if (next != current && blend != 0) {
        anim->active = 1;
        saved = *anim;
        if (load(anim, table, key, next)) {
            if (previous != 0) {
                *previous = saved;
                previous->current = current;
                previous->next = current;
                previous->active = 1;
            }
            anim->current = next;
            anim->next = next;
            anim->time = 0;
            anim->blending = 0;
            anim->active = 1;
            if (switched != 0) {
                *switched = 1;
            }
            return;
        }
        if (switched != 0) {
            *switched = 0;
        }
        load(anim, table, key, current);
        return;
    }
    if (switched != 0) {
        *switched = 0;
    }
    load(anim, table, key, current);
}

void Gastate_AdvanceRootMotion(CGameAnimateState_t *animationChannel, CVector3 *translationDeltaOut, f32 *angleDeltaOut, RootActor *rootMotionActor) {
    CVector3 startRootPosition;
    CVector3 endRootPosition;
    f32 angleSample;
    f32 lastFramePosition;
    f32 angleScale;
    f32 forcedEndFrame;
    f32 wrappedFramePosition;
    f32 previousFramePosition;
    f32 startRootAngle;
    f64 unusedFloat;
    f64 clampedLoopStart;
    f64 eventLoopStart;
    f64 positionLoopStart;
    f64 loopStartDouble;
    s32 followingAngleFrame;
    s32 followingEndAngleFrame;
    s32 unusedValue;
    s32 followingCurrentAngleFrame;
    s16 *startAngleKeys;
    s16 *endAngleKeys;
    s16 *unusedPointer;
    s16 *currentAngleKeys;
    s32 startAngleFrame;
    s32 endAngleFrame;
    s32 unusedValue1;
    s32 currentAngleFrame;
    s32 nextStartAngleFrame;
    s32 nextEndAngleFrame;
    s32 unusedValue2;
    s32 nextCurrentAngleFrame;
    RootClip *rootMotionClip;
    u16 loopStartFrame;
    u32 restartFrame;
    s32 lastFrameIndex;

    void *header;
    header = Polytrak2_GetResidentResource(animationChannel);
    translationDeltaOut->x = 0.0f;
    translationDeltaOut->y = 0.0f;
    translationDeltaOut->z = 0.0f;
    *angleDeltaOut = 0.0f;
    if (rootMotionActor->flags & 0x08000000) {
        forcedEndFrame = (f32) (animationChannel->frames - 1);
        animationChannel->time = forcedEndFrame;
        Gobjinst_DispatchAnimationIntervalEvents(rootMotionActor, animationChannel, 0.0f, forcedEndFrame);
        rootMotionActor->flags = (s32) (rootMotionActor->flags & 0xF7FFFFFF);
    }
    rootMotionClip = SetN64_GetPackSection(header,3);
    rootMotionClip = SetN64_GetPackSection(rootMotionClip,0);
    Polytrak2_SampleVectorTrack(animationChannel, 0, animationChannel->time, &startRootPosition);
    angleSample = animationChannel->time;
    startAngleKeys = ((AngleKeys *)SetN64_GetPackSection(Polytrak2_GetResidentResource(animationChannel), 0))->keys;
    nextStartAngleFrame = animationChannel->frames - 1;
    startAngleFrame = (s32) angleSample;
    followingAngleFrame = startAngleFrame + 1;
    if (followingAngleFrame < nextStartAngleFrame) {
        nextStartAngleFrame = followingAngleFrame;
    }
    angleScale = g_rootMotionAngleScale[0];
    startRootAngle = Graphu64_InterpolateWrappedValue(angleSample - (f32) startAngleFrame, (f32) startAngleKeys[startAngleFrame] * angleScale, (f32) startAngleKeys[nextStartAngleFrame] * angleScale);
    previousFramePosition = animationChannel->time;
    if (!(rootMotionActor->flags & 0x08000000)) {
        animationChannel->time = (f32) (previousFramePosition + (g_frameElapsedTime * rootMotionClip->rate * g_rootMotionFrameAdvanceScale));
    }
    Gobjinst_DispatchAnimationIntervalEvents(rootMotionActor, animationChannel, previousFramePosition, animationChannel->time);
    lastFrameIndex = animationChannel->frames - 1;
    lastFramePosition = (f32) lastFrameIndex;
    if (lastFramePosition < animationChannel->time) {
        Polytrak2_SampleVectorTrack(animationChannel, 0, lastFramePosition, &endRootPosition);
        endAngleKeys = ((AngleKeys *)SetN64_GetPackSection(Polytrak2_GetResidentResource(animationChannel), 0))->keys;
        endAngleFrame = (s32) lastFramePosition;
        followingEndAngleFrame = endAngleFrame + 1;
        nextEndAngleFrame = animationChannel->frames - 1;
        if (followingEndAngleFrame < nextEndAngleFrame) {
            nextEndAngleFrame = followingEndAngleFrame;
        }
        angleSample = Graphu64_InterpolateWrappedValue(lastFramePosition - (f32) endAngleFrame, (f32) endAngleKeys[endAngleFrame] * angleScale, (f32) endAngleKeys[nextEndAngleFrame] * angleScale);
        Graphu64_AddVec3(translationDeltaOut, translationDeltaOut, &endRootPosition);
        Graphu64_SubtractVectors(translationDeltaOut, translationDeltaOut, &startRootPosition);
        *angleDeltaOut += Graphu64_GetWrappedDifference(angleSample, startRootAngle);
        loopStartFrame = rootMotionClip->loopStart;
        restartFrame = 0;
        if (loopStartFrame != 0xFFFF) {
            restartFrame = loopStartFrame;
        }
        loopStartDouble = unsignedDouble(restartFrame, g_rootMotionRestartUnsignedBias);
        wrappedFramePosition = ((f32) loopStartDouble + animationChannel->time) - lastFramePosition;
        animationChannel->time = wrappedFramePosition;
        if (lastFramePosition < wrappedFramePosition) {
            clampedLoopStart = unsignedDouble(restartFrame, &g_rootMotionClampedRestartUnsignedBias);
            animationChannel->time = (f32) clampedLoopStart;
        }
        if ((restartFrame >= (u32)lastFrameIndex) && (animationChannel->current == animationChannel->next) && (Gastate_GetAnimationEventCount(animationChannel) == 0)) {
            animationChannel->blending = 0;
        }
        eventLoopStart = unsignedDouble(restartFrame, &g_rootMotionEventRestartUnsignedBias);
        Gobjinst_DispatchAnimationIntervalEvents(rootMotionActor, animationChannel, (f32) eventLoopStart, animationChannel->time);
        positionLoopStart = unsignedDouble(restartFrame, &g_rootMotionPositionRestartUnsignedBias);
        Polytrak2_SampleVectorTrack(animationChannel, 0, (f32) positionLoopStart, &startRootPosition);
        startRootAngle = wrapAngle(animationChannel,(f32)unsignedDouble(restartFrame,&g_rootMotionAngleRestartUnsignedBias));
        animationChannel->active = 1;
    }
    Polytrak2_SampleVectorTrack(animationChannel, 0, animationChannel->time, &endRootPosition);
    angleSample = animationChannel->time;
    currentAngleKeys = ((AngleKeys *)SetN64_GetPackSection(Polytrak2_GetResidentResource(animationChannel), 0))->keys;
    nextCurrentAngleFrame = animationChannel->frames - 1;
    currentAngleFrame = (s32) angleSample;
    followingCurrentAngleFrame = currentAngleFrame + 1;
    if (followingCurrentAngleFrame < nextCurrentAngleFrame) {
        nextCurrentAngleFrame = followingCurrentAngleFrame;
    }
    angleSample = Graphu64_InterpolateWrappedValue(angleSample - (f32) currentAngleFrame, (f32) currentAngleKeys[currentAngleFrame] * g_rootMotionCurrentAngleScale, (f32) currentAngleKeys[nextCurrentAngleFrame] * g_rootMotionCurrentAngleScale);
    Graphu64_AddVec3(translationDeltaOut, translationDeltaOut, &endRootPosition);
    Graphu64_SubtractVectors(translationDeltaOut, translationDeltaOut, &startRootPosition);
    *angleDeltaOut += Graphu64_GetWrappedDifference(angleSample, startRootAngle);
}

/* GASTATE_PREPAREANIMATIONFRAMES.CPP */

typedef struct PolytrakScalarSampleMetadata AnimationFramePreparationState;

void Gastate_PrepareAnimationFrames(AnimationFramePreparationState *state, AnimInfo *frames) {
    f32 frameScale;
    f32 scaledCurrentLoopStart;
    f32 scaledNextLoopStart;
    f32 framePosition;
    f32 frameCount;
    f32 floorFramePosition;
    s32 **animationHandle;
    s32 *resource;
    s32 *channels;
    s32 nextRotationLoopStart;
    s32 truncatedBlendFrame;
    s32 truncatedUnloopedFrame;
    s32 truncatedLoopedFrame;
    s32 truncatedTranslationFrame;
    s32 truncatedCurrentLoopStart;
    s32 truncatedNextLoopStart;
    s32 currentRotationLoopStart;
    s32 currentFrame;
    s32 loopStart;
    s32 resourceReady;
    s32 floorFrameIndex;
    s32 nextFrame;
    StridedTable *positions;
    StridedTable *section;

    animationHandle = state->animationHandle;
    if (animationHandle == 0) {
        resourceReady = 0;
    } else {
        resourceReady = Cache_IsResourceRetained(animationHandle) != 0;
    }
    if (resourceReady != 0) {
        resource = *state->animationHandle;
        positions = SetN64_GetPackSection(resource, 1);
        channels = SetN64_GetPackSection(resource, 5);
        SetN64_GetPackSection(channels, 0);
        loopStart = state->loopStart;
        framePosition = state->framePosition;
        frameCount = (f32) state->frameCount;
        frames->boneIndexPairs = positions->data;
        section = SetN64_GetPackSection(resource, 2);
        frames->initialOrientations = section->data;
        frames->translationFrames = SetN64_GetPackSection(channels, 1);
        frameScale = 1.0f;
        frames->rotationFrames = SetN64_GetPackSection(channels, 2);
        if (framePosition >= 0.0f) {
            floorFrameIndex = (s32) framePosition;
            goto block_8;
        }
        truncatedBlendFrame = (s32) framePosition;
        floorFramePosition = (f32) truncatedBlendFrame;
        if (floorFramePosition != framePosition) {
            floorFrameIndex = truncatedBlendFrame - 1;
block_8:
            floorFramePosition = (f32) floorFrameIndex;
        }
        frames->frameBlend = (f32) (framePosition - floorFramePosition);
        if (loopStart == 0xFFFF) {
            loopStart = 0;
            if (framePosition >= 0.0f) {
                currentFrame = (s32) framePosition;
            } else {
                truncatedUnloopedFrame = (s32) framePosition;
                currentFrame = ((f32) truncatedUnloopedFrame == framePosition) ? 0 : 1;
                currentFrame = truncatedUnloopedFrame - currentFrame;
            }
            if (frameCount <= (f32) currentFrame) {
                currentFrame = 0;
            }
            nextFrame = currentFrame + 1;
            if (frameCount <= (f32) nextFrame) {
                nextFrame = 0;
            }
        } else {
            if (framePosition >= 0.0f) {
                currentFrame = (s32) framePosition;
            } else {
                truncatedLoopedFrame = (s32) framePosition;
                currentFrame = ((f32) truncatedLoopedFrame == framePosition) ? 0 : 1;
                currentFrame = truncatedLoopedFrame - currentFrame;
            }
            if ((frameCount - 1.0f) <= (f32) currentFrame) {
                currentRotationLoopStart = state->loopStart;
                if (((f32) (u32) currentRotationLoopStart * frameScale) <= 0.0f) {
                    currentFrame = (s32) ((f32) (u32) currentRotationLoopStart * frameScale);
                } else {
                    currentFrame = ((f32) (s32) ((f32) (u32) currentRotationLoopStart * frameScale) == ((f32) (u32) currentRotationLoopStart * frameScale)) ? 0 : 1;
                    currentFrame = currentFrame + (s32) ((f32) (u32) currentRotationLoopStart * frameScale);
                }
            }
            nextFrame = currentFrame + 1;
            if ((frameCount - 1.0f) <= (f32) nextFrame) {
                nextRotationLoopStart = state->loopStart;
                if (((f32) (u32) nextRotationLoopStart * frameScale) <= 0.0f) {
                    nextFrame = (s32) ((f32) (u32) nextRotationLoopStart * frameScale);
                } else {
                    nextFrame = ((f32) (s32) ((f32) (u32) nextRotationLoopStart * frameScale) == ((f32) (u32) nextRotationLoopStart * frameScale)) ? 0 : 1;
                    nextFrame = nextFrame + (s32) ((f32) (u32) nextRotationLoopStart * frameScale);
                }
            }
        }
        frames->rotationFirst = (s32) (currentFrame * 4);
        frames->rotationNext = (s32) (nextFrame * 4);
        if (framePosition >= 0.0f) {
            currentFrame = (s32) framePosition;
        } else {
            truncatedTranslationFrame = (s32) framePosition;
            currentFrame = ((f32) truncatedTranslationFrame == framePosition) ? 0 : 1;
            currentFrame = truncatedTranslationFrame - currentFrame;
        }
        if (frameCount <= (f32) currentFrame) {
            scaledCurrentLoopStart = (f32) loopStart * frameScale;
            if (scaledCurrentLoopStart <= 0.0f) {
                currentFrame = (s32) scaledCurrentLoopStart;
                nextFrame = currentFrame + 1;
            } else {
                truncatedCurrentLoopStart = (s32) scaledCurrentLoopStart;
                currentFrame = ((f32) truncatedCurrentLoopStart == scaledCurrentLoopStart) ? 0 : 1;
                currentFrame = currentFrame + truncatedCurrentLoopStart;
                nextFrame = currentFrame + 1;
            }
        } else {
            nextFrame = currentFrame + 1;
        }
        if (frameCount <= (f32) nextFrame) {
            scaledNextLoopStart = (f32) loopStart * frameScale;
            if (scaledNextLoopStart <= 0.0f) {
                nextFrame = (s32) scaledNextLoopStart;
                frames->translationFirst = currentFrame * 4;
            } else {
                truncatedNextLoopStart = (s32) scaledNextLoopStart;
                nextFrame = ((f32) truncatedNextLoopStart == scaledNextLoopStart) ? 0 : 1;
                nextFrame = nextFrame + truncatedNextLoopStart;
                        goto block_75;
            }
        } else {
block_75:
            frames->translationFirst = currentFrame * 4;
        }
        frames->translationNext = (s32) (nextFrame * 4);
    }
}

/* GOBJINST_BUILDACTORPOSE_DATA.CPP */

/** Initialize the compact record fields written by the pose builder leaf. */
void Gastate_ResetAnimationReference(void *record) {
    Anim *record_record = record;
    record_record->current = -1;
    record_record->next = 0;
    record_record->time = 0;
    record_record->frames = 0;
    record_record->blending = 0;
    record_record->active = 1;
    record_record->resource = 0;
}

void Gastate_ReleaseAnimationResource(struct AnimationResourceHandleView *animationState) {
    Cache_UnlockResource(0, (struct CacheResourceNode *)(((struct Anim *) ((s8 *) animationState))->resource));
    (((struct Anim *) ((s8 *) animationState))->resource) = 0;
}

s32 Gastate_IsAnimationResourceRetained(void *animationState) {
    Anim *animationRecord = animationState;
    void *animationResourceHandle = animationRecord->resource;
    if (animationResourceHandle == 0) {
        return 0;
    }
    return Cache_IsResourceRetained(animationResourceHandle) != 0;
}

void Gastate_CopyAnimationSectionSix(void *animationState, Six *recordOut) {
    Six *result = (Six *)SetN64_GetPackSection((void *)Polytrak2_GetResidentResource(animationState), 6);

    *recordOut = *result;
}

char *Gastate_GetAnimationPoseSection(void *animationState) {
    return SetN64_GetPackSection(SetN64_GetPackSection(Polytrak2_GetResidentResource(animationState), 3), 0);
}

s32 Gastate_GetAnimationEventEntries(void *animationState) {
    return SetN64_GetPackSection(Polytrak2_GetResidentResource(animationState), 4) + 8;
}

s32 Gastate_GetAnimationEventCount(void *animationState) {
    return (((struct ResourceKeyView *)(SetN64_GetPackSection(Polytrak2_GetResidentResource(animationState), 4)))->key);
}





void Gastate_InterpolateFrameAngles(AnimRef *animationState, f32 framePosition) {
    s16 *base;
    s32 count;
    s32 currentAngleFrame;
    s32 followingAngleFrame;
    s32 nextAngleFrame;
    f32 bTerm;
    f32 eTerm;

    base = (s16 *)((ResidentDataChunk *)SetN64_GetPackSection(Polytrak2_GetResidentResource(animationState), 0))->data;
    count = (s16)animationState->count;
    nextAngleFrame = count - 1;
    currentAngleFrame = (s32) framePosition;
    followingAngleFrame = currentAngleFrame + 1;
    if (followingAngleFrame < nextAngleFrame) {
        nextAngleFrame = followingAngleFrame;
    }
    bTerm = (f32) base[currentAngleFrame] * g_animationFrameAngleScale[0];
    eTerm = (f32) base[nextAngleFrame] * g_animationFrameAngleScale[0];
    Graphu64_InterpolateWrappedValue(framePosition - (f32) currentAngleFrame, bTerm, eTerm);
}

s32 Gastate_RequestAnimationResource(AnimRef *animationState, s32 resourceTable, s32 resourceGroup, s32 animationId) {
    AnimRef *out = animationState;
    void *resource;
    ResourceEntry *entry;
    u16 value;
    s32 key;
    s32 resourceBytes;

    if (animationId == -1) {
        out->data = 0;
        return 0;
    }

    key = SetN64_LocatePackSection(resourceTable, resourceGroup, animationId, &resourceBytes);
    resource = Cache_RequestResource(0, key, key, resourceBytes, 4, animationState,
                            &Gastate_AnimationResourceCallbackEntry, g_animationText, 0);
    out->data = resource;
    if (!Gastate_IsAnimationResourceRetained(animationState)) {
        return 0;
    }

    resource = Polytrak2_GetResidentResource(animationState);
    entry = SetN64_GetPackSection(resource, 0);
    value = entry->count;
    out->id = animationId;
    out->count = value;
    resource = SetN64_GetPackSection(resource, 3);
    out->span = ((ResourceEntry *)SetN64_GetPackSection(resource, 0))->span;
    return 1;
}

/* BITARRAY.CPP */
const char g_animationText[10] = "animation";

/* GASTATE_ADVANCEROOTMOTION_DATA.CPP */

const float g_rootMotionAngleScale[2] = {
    9.587673e-05f, 0.06666667f,
};

/* GASTATE_DATA.CPP */

/* 2^32, added when an unsigned frame converts to double, once per conversion site. */
const double g_rootMotionRestartUnsignedBias[5] = {
    4294967296.0, 4294967296.0, 4294967296.0, 4294967296.0, 4294967296.0,
};

const float g_rootMotionWrappedAngleScale = 9.587673e-05f;
const float g_rootMotionCurrentAngleScale = 9.587673e-05f;

/* ANIMSTATE_PREPAREANIMATIONFRAMES.CPP */

const float g_animationFrameAngleScale[1] = {
    9.587673e-05f,
};
