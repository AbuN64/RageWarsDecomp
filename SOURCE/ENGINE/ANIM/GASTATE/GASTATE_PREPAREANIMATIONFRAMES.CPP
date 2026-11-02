#include "COMMON/ACTORRESOURCEHEADER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "SYSTEM/POLYTRAK2_DECODESCALARSAMPLES_DATA.H"
#include "COMMON/PACKEDMESHMATERIAL.H"
#include "COMMON/LOCALDECODERANGE.H"
#include "SCENE/CACHE_ALLOCATEMEMORY.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

typedef struct PolytrakScalarSampleMetadata AnimationFramePreparationState;
typedef StridedTable ObjRecV1;

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
    ObjRecV1 *positions;
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
