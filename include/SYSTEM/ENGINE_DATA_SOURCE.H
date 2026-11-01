#ifndef SYSTEM_ENGINE_DATA_SOURCE_H
#define SYSTEM_ENGINE_DATA_SOURCE_H

#include "TYPES.H"
#include "COMMON/MEMORY_STREAM_BUFFER.H"

/* Records behind the engine's public per-mode callback views. */
typedef void (*EngineSessionCallback)(void *);
typedef struct EngineSessionHandlers {
    EngineSessionCallback initialize;
    EngineSessionCallback update;
    EngineSessionCallback draw;
} EngineSessionHandlers;

typedef struct EngineVoiceScaleEntry {
    f32 soundId;
    f32 scale;
} EngineVoiceScaleEntry;

typedef struct EngineSchedulerState {
    f32 taskDuration;
    f32 audioDuration;
    f32 elapsedFrameDuration;
    f32 frameBuildSeconds;
    f32 tickScale;
    s32 enabled;
    s32 screenImageResourcesEnabled;
    void *taskBuffer;
    s32 taskBufferBytes;
    s32 modeFourFrameCounter;
    s32 frontendScreenInitialized;
    s32 expansionMemoryIntroEnabled;
    s32 introExitPending;
    s32 creditsReturnToFrontend;
    s32 creditsSelectSpawnOnExit;
} EngineSchedulerState;

typedef struct EngineRenderState {
    u32 maximumDisplayListBytes;
    u8 alignmentPad[8];
    s32 textureCacheResource;
    s32 texturePaletteOverrideEnabled;
    u8 trailingAlignmentPad[8];
} EngineRenderState;

typedef struct EnginePreviewRenderState {
    u32 maximumDisplayListBytes;
    u8 alignmentPad[8];
    s32 textureVariationBypassEnabled;
    s32 previousTextureHeld;
    s32 nextTextureHeld;
    s32 previousFrameHeld;
    s32 nextFrameHeld;
    s32 previousPageHeld;
    s32 nextPageHeld;
    s32 toggleButtonHeld;
    s32 textureCacheResource;
    s32 texturePaletteOverrideEnabled;
    u8 trailingAlignmentPad[8];
} EnginePreviewRenderState;

typedef struct EngineGeometryState {
    u32 previousModePreset;
    s32 previousCombineMode;
    s32 modeEnabled;
    s32 combineEnabled;
    s32 antialiasingEnabled;
    s32 frontendVideoModeVariantBit;
    s32 textureFilterOverride;
    s32 texturePerspectiveOverride;
    s32 fogEffectEnabled;
    u32 effectGeometryMode;
    u32 opaqueRenderMode;
    u32 translucentRenderMode;
    s32 menuModelFillEnabled;
    f32 menuModelFillColor[5];
    u8 primitiveColorOverride[4];
    u8 primitiveAlphaOverrideEnabled;
    u8 primitiveAlphaOverride;
    u8 alignmentPad[2];
} EngineGeometryState;

typedef struct EngineRuntimeIoState {
    s32 randomState;
    u8 randomAlignmentPad[12];
    s32 resourceOpenCount;
    u32 resourceReadyCookie;
    s32 formattedLength;
    s32 scratchCallback;
    s32 argumentWriteCallback;
    void *openCallback;
    void *closeCallback;
    void *readCallback;
    void *writeCallback;
    void *seekCallback;
    void *tellCallback;
    void *endCallback;
    MemoryStreamBuffer resourceStream;
    u8 streamAlignmentPad[12];
    s32 frameHeapsAllocated;
    s32 frameHeapBuffers[2];
    f32 frameHeapFreeByteStats[3];
    f32 frameHeapLowUsageStats[3];
    f32 frameHeapHighUsageStats[3];
    u32 numericWidgetClipLeft;
    u32 numericWidgetClipTop;
    u32 numericWidgetClipRight;
    u32 numericWidgetClipBottom;
} EngineRuntimeIoState;

typedef struct EngineStdioCarriageReturn {
    u8 leadingAlignmentPad[8];
    char carriageReturn;
    u8 trailingAlignmentPad[15];
} EngineStdioCarriageReturn;

/* PakModelDefinition consumed by Menu_DrawMenuModel. */
typedef struct EngineMenuModelDefinition {
    s32 kind, model, variant;
    f32 offset[3], scale[3];
    u8 reserved24[8];
    f32 rotationSpeed;
} EngineMenuModelDefinition;

#endif
