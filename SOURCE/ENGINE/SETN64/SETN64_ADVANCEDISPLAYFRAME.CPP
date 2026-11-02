#include "thread_queue.h"
#include "COMMON/SESSIONHANDLERROW.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ENGINE/SETN64.H"
#include "UI/X_FILES/X_PLUS.H"














/* Advances the frame ring and alternates the color and depth buffer pointers for the next frame. */


extern unsigned int g_gameFrameCounter;

extern int g_gameLoopFrameCount;


void SetN64_StartBootstrapThread(void) {
    XPlus_FillMemory((s32)g_bootstrapThreadStack, 0, 128);
    osCreateThread((s32)g_bootstrapThread, 0, g_SetN64_RunBootstrapThreadPackedAddress24, 0, (s32)(g_bootstrapThreadStack + 0x80), g_bootstrapThreadPriority);
    osStartThread(g_bootstrapThread);
}

void SetN64_StartGameThreadAndIdle(s32 *gameSession, s32 threadArgument) {
    XPlus_FillMemory((s32)g_gameThreadStack, 1, 0x8000);
    osCreateThread((s32)g_gameThread, 1, g_SetN64_RunGameThreadPackedAddress24, threadArgument, (s32)g_schedulerThreadStack, g_gameThreadPriority);
    osStartThread(g_gameThread);
    {
        s32 schedulingPriority = g_videoFrameSchedulingMode;
        ((GameSession *)gameSession)->enabled = 0;
        osSetThreadPri(0, schedulingPriority);
    }
loop_1:
    goto loop_1;
}

void SetN64_AdvanceDisplayFrame(Display *display) {
 unsigned int index; Frame *frame;
 index=++g_gameFrameCounter%g_renderFrameBufferCount;
 g_gameLoopFrameCount++;
 g_lightingBufferIndex^=1;
 display->current=&display->frames[index];
 display->current->commands = g_lightingBufferIndex ? g_displayListBufferOne : g_displayListBufferZero;
 frame = display->current;
 frame->secondCommands = g_lightingBufferIndex ? g_secondaryDisplayListBufferZero : g_secondaryDisplayListBufferOne;
}
