#ifndef COMMON_DISPLAY_H
#define COMMON_DISPLAY_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/vector.h"
#include <platform_sdk.h>
#include <PR/sched.h>
struct Frame;
/* One frame of the three-frame display ring, 0x140 bytes: its RSP task (and a second one when dual), the message
   the scheduler sends back when the frame is done, its color image and its display lists. */
typedef struct Frame Frame;
struct Frame {
    char pad0[0x14];
    CVector3 direction; /* 0x014: SetN64_SetFrameDirection */
    OSScTask task; /* 0x020 */
    OSScTask secondTask; /* 0x088 */
    OSScMsg done; /* 0x0F0: type 2 */
    void *colorImage; /* 0x110 */
    Gfx *commands; /* 0x114 */
    Gfx *secondCommands; /* 0x118 */
    u32 commandBytes; /* 0x11C */
    u32 secondCommandBytes; /* 0x120 */
    u32 ticks; /* 0x124: retrace count when the frame was built */
    s32 dual; /* 0x128: the frame also sends secondTask */
    struct Frame *previous; /* 0x12C */
    struct Frame *next; /* 0x130 */
    char pad134[0xC];
};
/* The frame ring at the start of the game session g_gameSession. */
typedef struct Display Display;
struct Display {
    Frame frames[3];
    struct Frame *current; /* 0x3C0 */
};
/* g_currentRenderFrame is the session's ring.current (g_gameSession + 0x3C0 in every version). Code reads it as
 * g_gameSession.ring.current; this scalar name stays only where the ROM schedules the load as a plain scalar
 * (MIXED: Camera_DrawActiveViews, SetN64_DrawIntroBackdrop, SetN64_DrawSplashImage move it across Gfx stores). */
extern struct Frame *g_currentRenderFrame;
extern struct Frame *g_currentTaskFrame; /* the frame being built */
extern Gfx *g_displayListBuffers[2]; /* command buffers, alternating per frame */
extern Gfx *g_secondaryDisplayListBufferAlternate, *g_secondaryDisplayListBufferZero; /* second command buffers */
extern u64 *g_graphicsMicrocodeDataSize; /* RSP output buffer */
extern s32 g_graphicsMicrocodeTextSize; /* its size */
extern struct Frame *g_schedulerFramebufferSchedule[]; /* built frames waiting for their buffer swap */
#endif
