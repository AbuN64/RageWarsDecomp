#include "COMMON/VIEWFLAGS.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "COMMON/DESCRIPTORRECAT29.H"
extern void Graphu64_SubtractVectors(CVector3 *out, CVector3 *a, CVector3 *b);

/* Spawns an emitter record: takes the head of the free list at 0x11D8 into the active list at 0x11EC (or reuses the record at 0x11F0 when none is free) and fills its position, scale, shared value and three rates converted by k_cameraFadeResetValue. */



extern f32 k_cameraFadeResetValue[];


static inline void set_emitter(CShake *node, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos)
{
    node->m_vPos = pos;
    node->m_Radius = scale;
    node->x.mode = value;
    node->x.value = a;
    node->y.mode = value;
    node->y.value = b;
    node->z.mode = value;
    node->z.value = c;
}

extern s32 Graphu64_LimitVectorLength(f32 *vectorComponents, f32 maximumLength);

extern f32 Gu_Sqrtf(f32);

/* Posts a text as on-screen messages, one per line: the text (or g_screenMessageSubstitutionReplacement when given g_screenMessageSubstitutionSource) is split
 * at newlines and for each non-empty line the oldest message node of the owner's list at 0xF24 is recycled
 * (cleared through Gsky_ClearScreenMessage, unlinked, and pushed onto the free list at 0xE40 of the pool) and set up
 * as a kind 2 message centred horizontally 80 pixels above the bottom of the screen, scaled by the given
 * size. Returns the last message node. */




extern ScreenMessageTextView g_screenMessageSubstitutionReplacement;

extern ScreenMessageTextView g_screenMessageSubstitutionSource;

extern s32 g_hudReferenceViewportWidth;


static inline CCameraText *recycle(void *owner, void *pool) {
    CCameraText *oldest;

    oldest = ((struct ScreenMessageOwner *)owner)->activeMessages.head;
    if (oldest != 0) {
        Gsky_ClearScreenMessage(oldest);
        List_RemoveIntrusive(&((struct ScreenMessageOwner *)owner)->activeMessages, oldest);
        List_AppendIntrusive(&((struct ScreenMessagePool *)pool)->freeMessages, oldest);
    }
    return oldest;
}

static inline CCameraText *post_lines(void *owner, void *pool, u8 *text, s32 kind, f32 size, s32 target) {
    CCameraText *message;
    s32 height;
    u8 *line;
    u8 *p;

    message = 0;
    if (pool == 0) {
        return message;
    }
    if (text == g_screenMessageSubstitutionSource.text) {
        text = g_screenMessageSubstitutionReplacement.text;
    }
    p = text;
    line = p;
    while (*p != 0) {
        p++;
        if (*p == '\n' || *p == 0) {
            if (line != p) {
                message = recycle(owner, pool);
                if (message != 0) {
                    s32 half = g_hudReferenceViewportWidth / 2;
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
                    message->x = half;
                    message->y = height - 80;
                    message->m_DisplayTime = size * 15.0f;
                }
                line = p + 1;
            }
        }
    }
    return message;
}

void Gsky_StartEmitter(char *obj, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos)
{
    RaceViewportState *state = (void *)obj;
    CShake *node = state->freeEffects.head;
    f32 k;

    if (node != 0) {
        List_RemoveIntrusive(&state->freeEffects, node);
        List_PrependIntrusive(&state->activeEffects, node);
    } else {
        node = state->activeEffects.tail;
    }
    k = k_cameraFadeResetValue[1];
    set_emitter(node, a * k, b * k, c * k, scale, value, pos);
}

void *Gsky_FindNearestCamera(MenuMatchGlobals *menuMatchGlobals, CVector3 *zero) {
    CVector3 position;
    GameplayCamera *node;
    void *bestNode;
    f32 bestDist;
    f32 distSq;

    Graphu64_LimitVectorLength(&zero->x, 20000.0f);
    if (menuMatchGlobals->useFallbackCamera != 0) {
        return &menuMatchGlobals->fallbackCamera;
    }
    node = menuMatchGlobals->cameras;
    bestDist = k_screenMessageInitialNearestDistance;
    bestNode = 0;
    if (node != 0) {
        do {
            Graphu64_SubtractVectors(&position, zero, &node->position);
            distSq = (position.x * position.x) +
                     (position.y * position.y) +
                     (position.z * position.z);
            if (distSq < bestDist) {
                bestNode = node;
                bestDist = distSq;
            }
            node = node->next;
        } while (node != 0);
    }
    if (bestNode == 0) {
        return &menuMatchGlobals->fallbackCamera;
    }
    return bestNode;
}

f32 Gsky_GetMeanViewDistance(Race *viewOwner, void *targetPosition) {
    CVector3 position;
    f32 sum;
    RacerViewport *node;
    f64 divisor;
    s32 count;

    if (viewOwner->header.views.count == 0) {
        return 0.0f;
    }
    node = viewOwner->header.views.head;
    sum = 0.0f;
    if (node != 0) {
        do {
            Graphu64_SubtractVectors(&position, &((GameplayCamera *)node)->position, targetPosition);
            sum += Gu_Sqrtf(
                (position.x * position.x) +
                (position.y * position.y) +
                (position.z * position.z));
            node = node->next;
        } while (node != 0);
    }
    count = viewOwner->header.views.count;
    divisor = (f64)count;
    if (count < 0) {
        divisor += k_screenMessageScaleDivisorStep;
    }
    return sum / (f32)divisor;
}

void *Gsky_PostFlaggedScreenMessage(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool, u8 *text) {
    struct CCameraText_t *message = Camera_PostScreenMessage(owner, pool, text);
    if (message != 0) {
        message->pad20 = 1;
    }
    return message;
}

CCameraText *Gsky_PostScaledScreenMessage(void *owner, void *pool, u8 *text, f32 size) {
    return post_lines(owner, pool, text, 2, size, -1);
}
