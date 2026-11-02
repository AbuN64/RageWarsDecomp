#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/DESCRIPTORRECAT29.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "SCHED/SKY_POSTSCREENMESSAGE.H"
#include "ENGINE/CACHE/LIST.H"

/* 8023A284_37.CPP */
#if defined(VERSION_DE)
unsigned int k_SkyPostscreenmessageQuarterWords[1] = {
    0x3E800000,
};
#endif

/* 8023A284.CPP */
f32 Gsky_StepValueTowardTarget(s32 unused0, f32 value, f32 target, f32 step) {
    if (Control_IsSnapshotActive() != 0) {
        value = target;
    }
    if (value < target) {
        value += step;
        g_cameraFramingTransitionTimer = k_screenMessageValueIncreaseMarker;
        if (target < value) {
            value = target;
        }
    } else if (target < value) {
        value -= step;
        g_cameraFramingTransitionTimer = k_screenMessageValueDecreaseMarker;
        if (value < target) {
            value = target;
        }
    }
    return value;
}

/* Posts a text as on-screen messages, one per line, with the given kind, target and size: the text (or
 * g_screenMessageSubstitutionReplacement when given g_screenMessageSubstitutionSource) is split at newlines and for each non-empty line the oldest message node
 * of the owner's list at 0xF24 is recycled (cleared through Gsky_ClearScreenMessage, unlinked, and pushed onto the free
 * list at 0xE40 of the pool) and set up as a message centred horizontally 80 pixels above the bottom of the
 * screen, scaled by the given size. Returns the last message node. */

extern u8 *g_screenMessageSubstitutionReplacement;

extern u8 *g_screenMessageSubstitutionSource;

static inline CCameraText *recycle(void *owner, void *pool) {
    struct ScreenMessageOwner *messageOwner = owner;
    struct ScreenMessagePool *messagePool = pool;
    CCameraText *oldest;

    oldest = messageOwner->activeMessages.head;
    if (oldest != 0) {
        Gsky_ClearScreenMessage(oldest);
        List_RemoveIntrusive(&messageOwner->activeMessages, oldest);
        List_AppendIntrusive(&messagePool->freeMessages, oldest);
    }
    return oldest;
}

CCameraText *Sky_PostScreenMessage(void *owner, void *pool, u8 *text, s32 kind, f32 size, s32 target) {
    CCameraText *message;
    u8 *line;
    u8 *p;
    s32 height;

    message = 0;
    if (pool == 0) {
        return message;
    }
    if (text == g_screenMessageSubstitutionSource) {
        text = g_screenMessageSubstitutionReplacement;
    }
    p = text;
    line = p;
    while (*p != 0) {
        p++;
        if (*p == '\n' || *p == 0) {
            if (line != p) {
                message = recycle(owner, pool);
                if (message != 0) {
                    message->kind = kind;
                    message->text = line;
                    message->m_nAlpha = 0;
                    message->alpha = 1.0f;
                    message->target = target;
                    message->pad20 = 0;
                    message->m_ModeTime = 0;
                    message->pad2C = 0;
                    message->m_XScale = 1.0f;
                    message->m_YScale = 1.0f;
                    height = g_hudReferenceViewportHeight;
                    message->x = g_hudReferenceViewportWidth / 2;
                    message->y = height - 80;
                    message->m_DisplayTime = size * 15.0f;
                }
                line = p + 1;
            }
        }
    }
    return message;
}
