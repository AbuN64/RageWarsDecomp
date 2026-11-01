#include "../../../sdk/include/LIBC.H"
#include "COMMON/LISTNODE.H"
#include "AUDIO/LIST_AND_CHANNEL_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "TEXTURE/SOUND_UPDATEAUDIOCONTEXT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "ENGINE/AUDIO/AUDIOWORLD.H"
#include "VOICE/VOICE.H"


/* Starts a sound instance from a description: when the scene's free node list is not empty it takes the
 * first node under the audio lock (Sound_AcquireContextLock/Sound_ReleaseContextLock), unlinks it, gives it the next handle, the
 * volume, sample, priority, pan and pitch fields decoded from the description, full gain, the scene frame
 * and the position, prepares its channel through Audio_SetVoiceTrackId and Audio_InitializeVoiceParameters and inserts it into the
 * active list ahead of the first lower-priority node; returns the handle or -1 when no node is free. */











extern void Audio_InitializeVoiceParameters(void *, void *, s32);


extern s8 SoundInfo_GetPriority(void *);


extern u8 SoundInfo_GetPan(void *);

extern s16 SoundInfo_GetFlags(void *);


/* Services the pending glyph requests of a text cache: each request still counting down its delay is ticked and, when it reaches zero, stamped with the current frame and the next sequence number; a request older than sixteen frames is moved to the done list, otherwise it reserves a cell for its glyph and a texture for its bitmap, stopping when none is free, copies itself into the cell, uploads the cell through Sound_UpdateSoundSlot and moves to the done list. The slot address is written as the doubled slot plus the table address because the cartridge adds the scaled index first; array indexing puts the table first (1 word). */






















extern void Sound_UpdateSoundSlot(SoundContext *, s32, s32, char *);

static inline void append(ListHead *head, EntryAudioWorldDispatchPendingSounds *entry) {
    entry->prev = head->prev;
    entry->next = (EntryAudioWorldDispatchPendingSounds *)head;
    head->prev->next = entry;
    head->prev = entry;
}

s32 AudioWorld_QueuePrioritizedSound(AudioPriorityQueueManagerView *manager, void *desc, Vec3Words *position, s32 volume, s32 extra) {
    AudioQueuedSoundNode *node;
    AudioQueuedSoundNode *first;
    AudioQueuedSoundNode *at;
    s32 *scene;
    s32 priority;

    if (manager->free.next != (AudioQueuedSoundNode *)&manager->free) {
        Sound_AcquireContextLock(manager->scene);
        first = manager->free.next;
        first->prev->next = first->next;
        first->next->prev = first->prev;
        scene = manager->scene;
        node = first;
        node->handle = ((GameAudioContext *)scene)->soundCounter;
        ((GameAudioContext *)scene)->soundCounter = node->handle + 1;
        node->volume = volume;
        node->voice = -1;
        node->volume16 = volume;
        node->group = SoundInfo_GetGroup(desc);
        node->priority = SoundInfo_GetPriority(desc);
        node->sample = SoundInfo_GetSample(desc);
        node->pan = SoundInfo_GetPan(desc);
        node->flags = SoundInfo_GetFlags(desc);
        node->pitch = SoundInfo_GetPitch(desc);
        node->gainB = 32000;
        node->gainA = 32000;
        node->time = 0;
        node->frame = ((GameAudioContext *)manager->scene)->frame;
        node->position = *position;
        node->pad58 = 0;
        node->padB4 = 0;
        Audio_SetVoiceTrackId(node->channel, ((struct GameAudioContext *)manager->scene)->selectedSound);
        node->mix = ((GameAudioContext *)manager->scene)->voiceMixValue;
        Audio_InitializeVoiceParameters(node->channel, desc, extra);
        at = manager->active.next;
        priority = node->priority;
        while (at != (AudioQueuedSoundNode *)&manager->active) {
            if (at->priority < priority) {
                break;
            }
            at = at->next;
        }
        node->prev = at->prev;
        node->next = at;
        at->prev->next = node;
        at->prev = node;
        Sound_ReleaseContextLock(manager->scene);
        return node->handle;
    }
    return -1;
}

void AudioWorld_DispatchPendingSounds(Cache *cache) {
    s16 *slots;
    char *textures;
    Glyphs *glyphs;
    EntryAudioWorldDispatchPendingSounds *entry;
    EntryAudioWorldDispatchPendingSounds *next;
    s32 slot;
    s16 *cursor;
    s32 free;
    AudioSoundCell *cell;

    Sound_AcquireContextLock(cache->context);
    slots = cache->context->slots;
    textures = cache->context->textures;
    glyphs = cache->context->font->glyphs;
    for (entry = cache->pending.next; entry != (EntryAudioWorldDispatchPendingSounds *)&cache->pending; entry = next) {
        next = entry->next;
        if (entry->delay != 0) {
            if (--entry->delay == 0) {
                entry->frame = cache->context->frame;
                entry->sequence = cache->context->sequence++;
                entry->reservedWordA8 = 0;
            }
            continue;
        }
        if (cache->context->frame - entry->frame >= 16) {
            entry->prev->next = next;
            entry->next->prev = entry->prev;
            append(&cache->done, entry);
            continue;
        }
        slot = Channel_SelectVoiceSlot((struct RecordD90 *)cache->context->cells, entry->style, entry->font, entry->glyph, 0);
        if (slot == -1 || slot == 16) {
            break;
        }
        cursor = (s16 *)((slot << 1) + (u32)slots);
        free = *cursor;
        if (free != -1) {
            break;
        }
        *cursor = alSndpAllocate(textures, glyphs->bitmaps[entry->font]);
        if (*cursor == free) {
            break;
        }
        cell = (AudioSoundCell *)(cache->context->cells + 4 + slot * sizeof(AudioSoundCell));
        Libc_CopyBytes(cell, entry->body, 204);
        cell->sequence = entry->sequence;
        cell->texture = *cursor;
        cell->frame = cache->context->frame;
        cell->index = slot;
        Sound_UpdateSoundSlot(cache->context, cell->sequence, 0, cell->data);
        entry->sequence = free;
        entry->glyph = free;
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
        append(&cache->done, entry);
    }
    Sound_ReleaseContextLock(cache->context);
}

void AudioWorld_InitializeVoiceListSentinel(void *sentinel, s32 owner) {
    (((struct AudioVoiceListLinks *) ((s8 *) sentinel))->next) = sentinel;
    (((struct AudioVoiceListLinks *) ((s8 *) sentinel))->prev) = sentinel;
    Audio_InitializeVoiceRecord(sentinel + 8, owner, -1);
}

void *AudioWorld_UnlinkChannelNode(LinkPair *channelNode) {
    channelNode->first[1] = (void *) channelNode->second;
    channelNode->second[0] = (void *) channelNode->first;
    return channelNode;
}


static inline void AudioWorld_InitializeListLink(ListLink *link) {
    link->prev = link;
    link->next = link;
}

static inline void AudioWorld_InsertLinkAfter(ListLink *at, ListLink *link) {
    link->next = at->next;
    link->prev = at;
    at->next->prev = link;
    at->next = link;
}

static inline void AudioWorld_InitializePoolVoice(AudioChannelVoiceNode *voice, s32 owner) {
    AudioWorld_InitializeListLink(&voice->link);
    Audio_InitializeVoiceRecord(&voice->header, owner, -1);
}

/* Starts a copy of a sound table entry when that entry is idle: takes the first node of the free list at
 * 0xD8, copies the 0xCC-byte entry into it, sets its owner value and position, clears its timer and
 * inserts it into the active list at 0x4 ahead of the first node with lower priority; the scene's
 * current selection fields are then reset. */














/* Initialises a channel set: records the owner, sets up its free and active lists with headers, and appends 32 initialised voices to the active list. */
void AudioWorld_InitializePendingSoundPool(ChannelSet *set, s32 owner) {
    s32 i;

    set->owner = owner;
    AudioWorld_InitializeListLink(&set->free);
    Audio_InitializeVoiceRecord(&set->freeHeader, owner, -1);
    AudioWorld_InitializeListLink(&set->active);
    Audio_InitializeVoiceRecord(&set->activeHeader, owner, -1);
    for (i = 0; i < 32; i++) {
        AudioWorld_InitializePoolVoice(&set->voices[i], owner);
        AudioWorld_InsertLinkAfter(set->active.prev, &set->voices[i].link);
    }
}

void AudioWorld_StartSpatialVoice(AudioSpatialVoiceManagerView *manager, s32 index, s32 owner, CVector3 *position) {
    AudioDispatchBusySlot *entry;
    AudioPrioritizedSoundNode *node;
    AudioPrioritizedSoundNode *at;
    AudioPrioritizedSoundNode *first;
    s32 priority;

    entry = &manager->scene->entries[index];
    if (entry->busy != 0) {
        return;
    }
    first = manager->free.next;
    if (first != (AudioPrioritizedSoundNode *)&manager->free) {
        first->prev->next = first->next;
        first->next->prev = first->prev;
        node = first;
        Libc_CopyBytes(node->pad8, entry, 204);
        node->owner = owner;
        node->position.x = position->x;
        node->position.y = position->y;
        node->position.z = position->z;
        node->timer = 0;
        at = manager->active.next;
        priority = node->priority;
        while (at != (AudioPrioritizedSoundNode *)&manager->active) {
            if (at->priority < priority) {
                break;
            }
            at = at->next;
        }
        node->prev = at->prev;
        node->next = at;
        at->prev->next = node;
        at->prev = node;
    }
    manager->scene->activeSelection = 0;
    manager->scene->pendingSelection = -1;
    manager->scene->previousSelection = -1;
    manager->scene->selection = -1;
}

void AudioWorld_RecyclePendingSoundsByIdentifier(ChannelSet *channelSet, s32 soundId) {
    NodeAudioWorldRecyclePendingSoundsByIdentifier *node;
    NodeAudioWorldRecyclePendingSoundsByIdentifier *next;
    NodeAudioWorldRecyclePendingSoundsByIdentifier *end;
    NodeAudioWorldRecyclePendingSoundsByIdentifier *initial_end;
    NodeAudioWorldRecyclePendingSoundsByIdentifier *tail_end;

    node = (NodeAudioWorldRecyclePendingSoundsByIdentifier *)channelSet->free.prev;
    tail_end = (NodeAudioWorldRecyclePendingSoundsByIdentifier *)&channelSet->active;
    initial_end = (NodeAudioWorldRecyclePendingSoundsByIdentifier *)&channelSet->free;
    if (node != initial_end) {
        end = initial_end;
        do {
            next = node->next;
            if (node->value == soundId) {
                node->prev->next = next;
                node->next->prev = node->prev;
                node->prev = (NodeAudioWorldRecyclePendingSoundsByIdentifier *)channelSet->active.next;
                node->next = tail_end;
                ((NodeAudioWorldRecyclePendingSoundsByIdentifier *)channelSet->active.next)->next = node;
                channelSet->active.next = (ListLink *)node;
            }
            node = next;
        } while (node != end);
    }
}

/* Moves nodes whose key differs from retainedKey (or every node when retainedKey is -1) from the active list to the tail of the list rooted at offset 0xD8. Adapted from AudioWorld_RecyclePendingSoundsByKey, with the match test inverted, a -1 wildcard added, and the tail insertion written as a do-while(0) list macro. */


void AudioWorld_RecyclePendingSoundsExceptKey(AudioPendingSoundListOwner *channelOwner, s32 retainedKey) {
    NodeAudioWorldRecyclePendingSoundsExceptKey *node;
    NodeAudioWorldRecyclePendingSoundsExceptKey *next;
    node = channelOwner->activeNext;
    while (node != (NodeAudioWorldRecyclePendingSoundsExceptKey *) &channelOwner->activePrev) {
        next = node->next;
        if (retainedKey == -1 || node->key != retainedKey) {
            node->prev->next = next;
            node->next->prev = node->prev;
            do { NodeAudioWorldRecyclePendingSoundsExceptKey *tail_ = (channelOwner)->otherPrev; (node)->next = (NodeAudioWorldRecyclePendingSoundsExceptKey *) &(channelOwner)->otherPrev; (node)->prev = tail_; (channelOwner)->otherPrev->next = (node); (channelOwner)->otherPrev = (node); } while (0);
        }
        node = next;
    }
}

/* Move nodes with the requested key from the active list to the other list. */
void AudioWorld_RecyclePendingSoundsByKey(void *channelOwner, s32 matchingKey)
{
    AudioPendingSoundListOwner *owner = channelOwner;
    NodeAudioWorldRecyclePendingSoundsExceptKey *node = owner->activeNext;
    NodeAudioWorldRecyclePendingSoundsExceptKey *head = (NodeAudioWorldRecyclePendingSoundsExceptKey *)&owner->activePrev;
    NodeAudioWorldRecyclePendingSoundsExceptKey *other = (NodeAudioWorldRecyclePendingSoundsExceptKey *)&owner->otherPrev;

    if (node != head) {
        NodeAudioWorldRecyclePendingSoundsExceptKey *sentinel = head;
        do {
            NodeAudioWorldRecyclePendingSoundsExceptKey *next = node->next;
            if (node->key == matchingKey) {
                NodeAudioWorldRecyclePendingSoundsExceptKey *tail;
                node->prev->next = next;
                node->next->prev = node->prev;
                tail = owner->otherPrev;
                node->next = other;
                node->prev = tail;
                owner->otherPrev->next = node;
                owner->otherPrev = node;
            }
            node = next;
        } while (node != sentinel);
    }
}

void AudioWorld_RecyclePendingSoundsByTrack(AudioPendingSoundListOwner *listNode, s32 matchingValue) {
    ListNode *node;
    ListNode *next;
    ListNode *sentinel;
    ListNode *loop_sentinel;
    ListNode *append_sentinel;
    ListNode *tail;

    node = (ListNode *)listNode->activeNext;
    sentinel = (ListNode *)&listNode->activePrev;
    append_sentinel = (ListNode *)&listNode->otherPrev;
    if (node != sentinel) {
        loop_sentinel = sentinel;
        do {
            next = node->next;
            if (node->valueBC == matchingValue) {
                node->prev->next = next;
                node->next->prev = node->prev;
                tail = (ListNode *)listNode->otherPrev;
                node->next = append_sentinel;
                node->prev = tail;
                ((ListNode *)listNode->otherPrev)->next = node;
                listNode->otherPrev = (NodeAudioWorldRecyclePendingSoundsExceptKey *)node;
            }
            node = next;
        } while (node != loop_sentinel);
    }
}

void AudioWorld_RecyclePendingSoundsByFlags(Lists *lists, s32 matchingFlags) {
    AudioPendingFlagsNode *channelCursor;
    AudioPendingFlagsNode *next;
    AudioPendingFlagsNode *sourceSentinel;
    AudioPendingFlagsNode *iterationSentinel;
    AudioPendingFlagsNode *destinationSentinel;

    channelCursor = lists->first.next;
    sourceSentinel = &lists->first;
    if (channelCursor != sourceSentinel) {
        destinationSentinel = &lists->second;
        iterationSentinel = sourceSentinel;
        do {
            next = channelCursor->next;
            if ((channelCursor->flags & matchingFlags) != 0) {
                AudioPendingFlagsNode *prev;

                channelCursor->prev->next = next;
                channelCursor->next->prev = channelCursor->prev;
                prev = lists->second.prev;
                channelCursor->next = destinationSentinel;
                channelCursor->prev = prev;
                lists->second.prev->next = channelCursor;
                lists->second.prev = channelCursor;
            }
            channelCursor = next;
        } while (channelCursor != iterationSentinel);
    }
}

int AudioWorld_HasPendingSoundWithKey(void *channelOwner, int wantedKey) {
    struct AudioPendingSoundListOwner *owner = channelOwner;
    struct NodeAudioWorldRecyclePendingSoundsExceptKey *node = owner->activeNext;
    void *sentinel = &owner->activePrev;
    if (node != sentinel) {
        do {
            int value = node->key;
            node = node->next;
            if (value == wantedKey) {
                return 1;
            }
        } while (node != sentinel);
    }
    return 0;
}
