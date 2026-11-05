#ifndef COMMON_TIMING_WORLD_H
#define COMMON_TIMING_WORLD_H
#include "types.h"
#include "Common/gameplay_camera.h"
#include "Common/textlayermetrics.h"
#include "Common/sessionhandlerrow.h"
typedef struct TimingWorld {
 char pad0[0x255C8];
 ScreenMessageOwner viewport;
 char padAfterViewport[0x26DB0 - 0x255C8 - sizeof(ScreenMessageOwner)]; f32 elapsedTime;
 s32 previousMode; u32 currentMode,pendingMode;
 u8 fadeFast; u8 fadeMode;
 char padAfterFadeMode[2]; f32 fade;
 char padAfterFade[0xC]; s32 menuNodeCount;
} TimingWorld;
/* Drawing callback followed by the remaining two state-dispatch slots. */
typedef struct FrameCallback {
 void (*draw)(struct TimingWorld *);
 void (*auxiliary0)(struct TimingWorld *);
 void (*auxiliary1)(struct TimingWorld *);
} FrameCallback;
#endif
