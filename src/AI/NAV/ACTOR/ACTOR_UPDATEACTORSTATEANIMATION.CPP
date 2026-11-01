#include "include_asm.h"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"


extern s32 Defs_IsAddressInCodeRanges(StateCallback);
extern s32 Defs_IsAddressInStaticRanges(u32);
extern void *Gobjinst_ChooseAvailableAnimationKind(void *, void *, s32);
extern s32 Gobjinst_ChooseAnimationVariant(void *, s32, s32);


void Actor_UpdateActorStateAnimation(Source110 *src, Dest *dst) {
    StateEntry *entry;
    StateCallback callback;
    f32 factor;

    entry = dst->entry;
    if (entry != 0) {
        if (dst->old_state != dst->state) {
            if (entry->scale >= 0.0f) {
                dst->entry_scale = entry->scale;
            }
            dst->old_entry_flags = dst->entry_flags;
            dst->entry_flags = entry->flags;
            src->state_changed = 0;
            callback = entry->callback;
            if (callback != 0) {
                if (Defs_IsAddressInCodeRanges(callback) != 0) {
                    callback = callback(src, dst);
                } else if (Defs_IsAddressInStaticRanges((u32)callback) != 0) {
                    callback = (StateCallback)Gobjinst_ChooseAvailableAnimationKind(src, callback, dst->state_result);
                }
                if (callback != 0) {
                    if (callback != (StateCallback)-1) {
                        dst->state_result = Gobjinst_ChooseAnimationVariant(src, (s32)callback, dst->state_result);
                        dst->result = (s16)callback;
                        if (src->current_state == dst->state_result) {
                            src->limit = 0.0f;
                        }
                    }
                    dst->count = 0;
                    dst->flags &= ~1U;
                }
            }
            dst->old_state = (u8)dst->state;
        } else if ((dst->state_result == -1) || (dst->result == -1)) {
            dst->count++;
            dst->flags |= 1;
        } else if (src->current_state == dst->state_result) {
            if (!(dst->flags & 1)) {
                s32 difference = src->counter - entry->threshold;
                double converted = difference;
                if (difference < 0) {
                    converted += g_actorAnimationUnsignedConversionBias;
                }
                if ((f32)converted <= src->limit) {
                    dst->count++;
                    dst->flags |= 1;
                }
            }
            if (src->state_changed != 0) {
                src->state_changed = 0;
                if (!(dst->flags & 1)) {
                    dst->count++;
                }
                dst->flags &= ~1U;
            }
        }

        if (dst->entry_flags & 0x10) {
            factor = dst->entry_scale;
        } else {
            factor = dst->scale * dst->entry_scale;
        }
        g_frameElapsedTime *= factor;
        Gobjinst_RequestAnimationIndex(src, dst->state_result, (dst->entry_flags >> 5) & 1);
        if ((dst->state_result != -1) && (src->previous_state != dst->state_result)) {
            dst->count = 0;
            dst->flags &= ~1U;
            src->state_changed = 0;
        }
        if (src->flags & 0x08000000) {
            dst->count++;
        }
    }
}

#include "COMMON/WORLD.H"
#include "COMMON/WORLD.H"
extern void Barrel_StopActorLoopingSound(void *, void *);

s32 Actor_RequestActorState(void *actor, void *stateController, s32 action) {
    struct ActorStateTable *node;
    StateEntry *entry;
    StateEntry *scan;
    s32 flags;

    if (g_world.mode == 2) {
        return 1;
    }
    if (g_world.mode == 4) {
        ((Source110 *)actor)->flags |= 0x100;
    }

    ((Dest *)stateController)->requestedState = ((Dest *)stateController)->state;
    ((Source110 *)actor)->animationChanged = 1;
    ((Source110 *)actor)->stateChanged = 1;
    if ((((Dest *)stateController)->entry != 0) && (((Dest *)stateController)->state == action)) {
        return 1;
    }

    node = ((Dest *)stateController)->table;
    entry = 0;
    ((Dest *)stateController)->state = action;
    ((Dest *)stateController)->stateTimer = 0;
    while (node != 0) {
        scan = node->entries;
        if (scan->id != -1) {
            while (scan->id != -1) {
                if (scan->id == action) {
                    entry = scan;
                    node = 0;
                    break;
                }
                scan = scan + 1;
            }
        }
        if (node != 0) {
            node = node->next;
        }
    }

    if (entry == 0) {
        return 0;
    }

    ((Dest *)stateController)->entry = entry;
    ((Source110 *)actor)->renderFlags &= 0x1F80007F;
    if ((((Source110 *)actor)->flags & 0x08000000) == 0) {
        ((Dest *)stateController)->count = 0;
        ((Dest *)stateController)->flags &= ~1U;
    }
    if (((Dest *)stateController)->sound != 0) {
        Barrel_StopActorLoopingSound(actor, stateController);
    }
    if (entry->enter != 0) {
        entry->enter(actor, stateController);
    }
    flags = entry->flags;
    ((Dest *)stateController)->entry_flags = flags;
    if (flags & 4) {
        ((Source110 *)actor)->velocity.x = 0;
        ((Source110 *)actor)->velocity.y = 0;
        ((Source110 *)actor)->velocity.z = 0;
    }
    return ((Dest *)stateController)->state == action;
}
