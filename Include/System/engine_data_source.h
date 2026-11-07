#ifndef SYSTEM_ENGINE_DATA_SOURCE_H
#define SYSTEM_ENGINE_DATA_SOURCE_H

#include "types.h"
#include "Common/memory_stream_buffer.h"

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

/* The scheduler words after its four leading floats (g_schedulerTaskDuration .. rwFrameBuildSeconds, scalar globals). */
typedef struct EngineSchedulerState {
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
extern EngineSchedulerState g_schedulerState;

/* Audio_UpdateVoicePool stores the active voice count in the first word; the words each version holds after it up
   to the next object follow. */
typedef struct AudioVoicePoolState {
    s32 activeVoiceCount;
#if defined(VERSION_EU)
    unsigned int word1;
    char text1[12];
    unsigned int words[10];
#else
    unsigned int words[14];
#endif
} AudioVoicePoolState;
extern AudioVoicePoolState g_audioPitchRatioCurveZeroWords;

/* The words after g_maximumDisplayListBytes (the largest display list SetN64_BuildAndSubmitSessionFrame built, its own scalar global). */
typedef struct EngineRenderState {
    u8 leadingStaleBytes[8];
#if defined(VERSION_US_REV1)
    s32 textureVariationBypassEnabled;
    s32 previousTextureHeld;
    s32 nextTextureHeld;
    s32 previousFrameHeld;
    s32 nextFrameHeld;
    s32 previousPageHeld;
    s32 nextPageHeld;
    s32 toggleButtonHeld;
#endif
    s32 textureCacheResource;
    s32 texturePaletteOverrideEnabled;
    u8 trailingStaleBytes[8];
} EngineRenderState;
extern EngineRenderState g_sessionFrameRenderState;

/* The geometry state after g_geometryPreviousModePreset and g_geometryPreviousCombineMode (scalar globals). */
typedef struct EngineGeometryState {
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
/* Geometry_SetCombineMode caches the last combine mode preset in the first word. */
extern EngineGeometryState g_geometryPreviousModePresetBlock;

typedef struct EngineRuntimeIoState {
    s32 randomState;
    u8 randomStaleBytes[12];
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
    u8 streamStaleBytes[12];
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
    u8 leadingStaleBytes[8];
    char carriageReturn;
    u8 trailingStaleBytes[15];
} EngineStdioCarriageReturn;

/* PakModelDefinition consumed by Menu_DrawMenuModel. */
typedef struct EngineMenuModelDefinition {
    s32 kind, model, variant;
    f32 offset[3], scale[3];
    u8 reserved24[8];
    f32 rotationSpeed;
} EngineMenuModelDefinition;

#endif
