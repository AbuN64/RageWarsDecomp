#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MANAGER.H"
#include "TYPES.H"
#include "SCENE/CACHE_ALLOCATEMEMORY.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "SYSTEM/POLYTRAK2_INTERPOLATEJOINTQUATERNION.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/AIPROFILE.H"
#include "include_asm.h"
#include "COMMON/STREAM.H"
#include "GAME/SOUNDINFO.H"
#include "COMMON/RESULTS.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"

/* GASTATE_3.CPP */
/** Initialize the compact record fields written by the VRAM 0x802624A0 leaf. */
void Gastate_ResetAnimationReference(void *record) {
    AnimationPoseRecordView *record_record = record;
    record_record->id = -1;
    record_record->frame = 0;
    record_record->reservedWord = 0;
    record_record->count = 0;
    record_record->flag0 = 0;
    record_record->flag1 = 1;
    record_record->data = 0;
}

void Gastate_ReleaseAnimationResource(void *animationState) {
    Cache_UnlockResource(0, (struct CacheResourceNode *)(((struct AnimationResourceHandleView *) ((s8 *) animationState))->resourceHandle));
    (((struct AnimationResourceHandleView *) ((s8 *) animationState))->resourceHandle) = 0;
}

s32 Gastate_IsAnimationResourceRetained(void *animationState) {
    ResourceHandleLinkView *animationRecord = animationState;
    void *animationResourceHandle = animationRecord->resourceHandle;
    if (animationResourceHandle == 0) {
        return 0;
    }
    return Cache_IsResourceRetained(animationResourceHandle) != 0;
}

void Gastate_CopyAnimationSectionSix(void *animationState, Six *recordOut) {
    Six *result = (Six *)SetN64_GetPackSection((void *)Polytrak2_GetResidentResource(animationState), 6);

    *recordOut = *result;
}

/* GASTATE_4.CPP */
char *Gastate_GetAnimationPoseSection(void *animationState) {
    return SetN64_GetPackSection(SetN64_GetPackSection(Polytrak2_GetResidentResource(animationState), 3), 0);
}

s32 Gastate_GetAnimationEventEntries(void *animationState) {
    return SetN64_GetPackSection(Polytrak2_GetResidentResource(animationState), 4) + 8;
}

s32 Gastate_GetAnimationEventCount(void *animationState) {
    return (((struct ResourceKeyView *) ((s8 *) SetN64_GetPackSection(Polytrak2_GetResidentResource(animationState), 4)))->key);
}

/* GASTATE_5.CPP */
extern s32 SetN64_LocatePackSection(s32 directory, s32 bankOffset, s32 sectionIndex, s32 *sectionSizeOut);

extern ResourceEntry g_animationText[];

void Gastate_InterpolateFrameAngles(AnimRef *animationState, f32 framePosition) {
    s16 *base;
    s32 count;
    s32 currentAngleFrame;
    s32 followingAngleFrame;
    s32 nextAngleFrame;
    f32 b_term;
    f32 e_term;

    base = (s16 *)((ResidentDataChunk *)SetN64_GetPackSection(Polytrak2_GetResidentResource(animationState), 0))->data;
    count = (s16)animationState->count;
    nextAngleFrame = count - 1;
    currentAngleFrame = (s32) framePosition;
    followingAngleFrame = currentAngleFrame + 1;
    if (followingAngleFrame < nextAngleFrame) {
        nextAngleFrame = followingAngleFrame;
    }
    b_term = (f32) base[currentAngleFrame] * g_animationFrameAngleScale;
    e_term = (f32) base[nextAngleFrame] * g_animationFrameAngleScale;
    Graphu64_InterpolateWrappedValue(framePosition - (f32) currentAngleFrame, b_term, e_term);
}

s32 Gastate_RequestAnimationResource(void *animationState, s32 resourceTable, s32 resourceGroup, s32 animationId) {
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

