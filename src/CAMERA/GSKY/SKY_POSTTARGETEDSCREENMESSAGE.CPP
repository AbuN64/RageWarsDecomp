#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "COMMON/DESCRIPTORRECAT29.H"

/* Posts a text as on-screen messages for a target: the target's messages still in the pool's list at 0xE40
 * are unlinked and returned to the owner's list at 0xF24, then the text (or g_screenMessageSubstitutionReplacement when given g_screenMessageSubstitutionSource)
 * is split at newlines and for each non-empty line the oldest message node of the owner's list is recycled
 * and set up as a kind 2 message for the target, centred horizontally 80 pixels above the bottom of the
 * screen and scaled by the given size. Returns the last message node. */




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

extern void *g_gameplayCameraList;

extern void Pool_InitEntryPool(int a);

extern u32 Weapon_UpdateShakeAxis(s32);

CCameraText *Gsky_PostTargetedScreenMessage(void *owner, void *pool, u8 *text, s32 target, f32 size) {
    CCameraText *pending;
    CCameraText *next;

    if (pool == 0) {
        return 0;
    }
    for (pending = ((struct ScreenMessagePool *)pool)->freeMessages.head; pending != 0; pending = next) {
        next = pending->next;
        if (pending->target == target) {
            List_RemoveIntrusive(&((struct ScreenMessagePool *)pool)->freeMessages, pending);
            List_PrependIntrusive(&((struct ScreenMessageOwner *)owner)->activeMessages, pending);
        }
    }
    pending = post_lines(owner, pool, text, 2, size, target);
    return pending;
}

void Gsky_ActivateMessagePool(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool) {
    NodeGskyActivateMessagePool *message;
    NodeGskyActivateMessagePool *nextMessage;
    void *freeList;

    if (pool != 0) {
        message = pool->freeMessages.tail;
        freeList = &pool->freeMessages;
        if (message != 0) {
            do {
                nextMessage = message->next;
                List_RemoveIntrusive(freeList, message);
                List_PrependIntrusive(&owner->activeMessages, message);
                message = nextMessage;
                freeList = &pool->freeMessages;
            } while (message != 0);
        }
    }
}

void Gsky_ActivateAllMessagePools(s32 messageOwner) {
    NodeGskyActivateMessagePool *next;
    NodeGskyActivateMessagePool *nextPooledMessage;
    NodeGskyActivateMessagePool *embeddedMessage;
    NodeGskyActivateMessagePool *pooledMessage;
    void *embeddedPool;
    void *poolCursor;

    embeddedPool = (void *)(messageOwner + 64);
    if (embeddedPool != 0) {
        embeddedMessage = ((struct ScreenMessagePool *)embeddedPool)->freeMessages.tail;
        if (embeddedMessage != 0) {
            do {
                next = embeddedMessage->next;
                List_RemoveIntrusive(&((struct ScreenMessagePool *)embeddedPool)->freeMessages, embeddedMessage);
                List_PrependIntrusive(&((struct ScreenMessageOwner *)messageOwner)->activeMessages, embeddedMessage);
                embeddedMessage = next;
            } while (embeddedMessage != 0);
        }
    }

    poolCursor = g_gameplayCameraList;
    if (poolCursor != 0) {
        do {
            pooledMessage = ((struct ScreenMessagePool *)poolCursor)->freeMessages.tail;
            if (pooledMessage != 0) {
                do {
                    nextPooledMessage = pooledMessage->next;
                    List_RemoveIntrusive(&((struct ScreenMessagePool *)poolCursor)->freeMessages, pooledMessage);
                    List_PrependIntrusive(&((struct ScreenMessageOwner *)messageOwner)->activeMessages, pooledMessage);
                    pooledMessage = nextPooledMessage;
                } while (pooledMessage != 0);
            }
            poolCursor = ((struct ScreenMessagePool *)poolCursor)->next;
        } while (poolCursor != 0);
    }
}

/** Thin wrapper forwarding an offset argument to Pool_InitEntryPool_SkyPosttargetedscreenmessage. */
void Gsky_InitializeMessageEntryPool(int viewAddress) {
    Pool_InitEntryPool((char *)&((GameplayCamera *)viewAddress)->sceneEffects);
}

void *Gsky_RecycleFirstScreenMessage(void *screenMessageOwner, struct ScreenMessagePool *screenMessagePool) {
    struct ScreenMessageOwner *owner = screenMessageOwner;
    struct ScreenMessagePool *pool = screenMessagePool;
    void *message;

    message = owner->activeMessages.head;
    if (message != 0) {
        Gsky_ClearScreenMessage(message);
        List_RemoveIntrusive(&owner->activeMessages, message);
        List_AppendIntrusive(&pool->freeMessages, message);
    }
    return message;
}

void Gsky_ActivateScreenMessage(s32 destinationOwner, s32 sourcePool, s32 messageNode) {
    List_RemoveIntrusive(sourcePool + 3648, messageNode);
    List_PrependIntrusive(destinationOwner + 3876, messageNode);
}

void Gsky_ClearScreenMessage(void *screenMessage) {
    struct CCameraText_t *message = screenMessage;
    message->kind = 0;
    message->target = 0;
}

/** Clear four consecutive object words beginning at offset 4. */
void Gsky_InitializeShakeChannel(void *channelStorage) {
    struct Channel *channel = channelStorage;
    channel->level = 0.0f;
    channel->state[0] = 0;
    channel->state[1] = 0;
    channel->state[2] = 0;
}

/** Stores the float argument scaled by k_screenMessageWaveLevelScale at 0x4 of the object and the int argument at 0x0. */




void Gsky_SetShakeChannel(struct Channel *channel, float inputLevel, int waveMode) {
    channel->level = inputLevel * (k_screenMessageWaveLevelScale);
    channel->mode = waveMode;
}

/* Evaluates a wave: kind 1 returns Gu_Sinf_SkyPosttargetedscreenmessage of the phase at 0x10 scaled by k_screenMessageWavePhaseScale, times
   the amplitude at 0xC; kind 0 returns Graphu64_RandomBetween over minus to plus the amplitude; any other
   kind returns zero. */






f32 Gsky_SampleShakeWave(struct Wave *wave) {
    switch (wave->kind) {
    case 1:
        return Gu_Sinf(wave->phase * k_screenMessageWavePhaseScale) * wave->amplitude;
    case 0:
        return Graphu64_RandomBetween(-wave->amplitude, wave->amplitude);
    }
    return 0.0f;
}

/** Zero the object's vector fields and reset the scale field to the default. */
void Gsky_InitializeShakeRecord(void *channelRecord) {
    struct CameraShakeRecordView *o = channelRecord;
    struct Channel *channel0;
    struct Channel *channel1;
    struct Channel *channel2;
    f32 diag;

    diag = k_screenMessageWaveDefault;
    channel0 = &o->channels[0];
    o->triple.x = 0;
    o->triple.y = 0;
    o->triple.z = 0;
    o->value = diag;
    channel0->level = 0;
    channel0->state[0] = 0;
    channel0->state[1] = 0;
    channel0->state[2] = 0;
    channel1 = &o->channels[1];
    channel2 = &o->channels[2];
    channel1->level = 0;
    channel1->state[0] = 0;
    channel1->state[1] = 0;
    channel1->state[2] = 0;
    channel2->level = 0;
    channel2->state[0] = 0;
    channel2->state[1] = 0;
    channel2->state[2] = 0;
}

/* Configures a three-channel record: copies a by-value three-word block to offset 8 and a value to
   0x14, and gives each of the channels at 0x18, 0x2C and 0x40 the same mode word and a level scaled
   by the pooled constant k_screenMessageChannelLevelScale. */








void Gsky_SetShakeRecord(struct CameraShakeRecordView *record, f32 first, f32 second, f32 third, f32 value, s32 mode,
                   Triple triple) {
    record->triple = triple;
    record->value = value;
    record->channels[0].mode = mode;
    record->channels[1].mode = mode;
    record->channels[2].mode = mode;
    record->channels[0].level = first * k_screenMessageChannelLevelScale;
    record->channels[1].level = second * k_screenMessageChannelLevelScale;
    record->channels[2].level = third * k_screenMessageChannelLevelScale;
}

s32 Gsky_UpdateShakeRecord(s32 waveRecord) {
    s32 result;
    u32 secondChannelDone;
    u32 firstChannelDone;
    u32 thirdChannelDone;

    firstChannelDone = Weapon_UpdateShakeAxis(waveRecord + 24);
    secondChannelDone = Weapon_UpdateShakeAxis(waveRecord + 44);
    thirdChannelDone = Weapon_UpdateShakeAxis(waveRecord + 64);
    result = 0;
    if ((firstChannelDone != 0) && (secondChannelDone != 0)) {
        result = thirdChannelDone > 0U;
    }
    return result;
}
