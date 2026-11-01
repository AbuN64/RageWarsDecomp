#include "include_asm.h"
#include "COMMON/LONE/CONTROLLER_RUMBLE_POOL.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/WORLD.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "ENGINE/CONTROL.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "RENDER/SETN64_UPDATEFADETRANSITION.H"
#include "RENDER/CONTROL_CYCLEACTORSNAPSHOTMODE.H"

/* 80263760_8.CPP */
extern void Rumble_FreeAllPoolNodes(s32 *);

/* Advances the replay mode: when replays are possible (SetN64_IsModeThirteen, g_sessionOptionResetMode and the handle table) it
 * cycles the mode 0 -> 1 -> 2 -> 0, snapshots the actors and records the camera target, promoting mode 1
 * to 2 when the player's target changed or the player is in states 0x16 to 0x21 and recording the player's
 * target instead; otherwise the mode is cleared. An active mode arms the 240-frame timer. */

extern s32 g_activeActorKind;

extern void *Playerai_GetFirstPlayer(void *);

/** Return the global word at g_controllerActorSnapshotSavedActorId. */

/** Clear the global word at VRAM 0x8010FC40. */

/* Restores every actor from the global replay table: copies its 0x70-byte block back to 0x5E0 and, when
 * the table's mode is 1, also restores its position, its value at 0x6C and its identifier resolved from the
 * saved handle through Scene_GetModelSectionTwoRecord. Adapted from the snapshot writer Control_SaveActorSnapshot, reading both tables
 * through local pointers and re-taking the actor list address in the loop increment. */

extern s32 Scene_GetModelSectionTwoIndex(Shared_World *table, s32 id);

const float k_ControlCycleactorsnapshotmodeEncodedWords[3] = {
    1.0f, 1.0f, 0.003921569f,
};
void Control_SetProfileMode(ControllerProfile *slot, s32 profileMode) {
    slot->mode = profileMode;
    if (profileMode == 0) {
        Control_ResetControllerPak(slot);
    }
}

void Control_ResetControllerProfiles(void) {
    ControllerProfile *slot;
    s32 i;

    i = 0;
    slot = g_controllerProfiles;
    do {
        Control_ResetControllerPak(slot);
        i += 1;
        slot += 1;
    } while (i < 4);
}

void Control_SetControllerMode(s32 a) {
    ControllerProfile *slot;
    s32 i;

    i = 0;
    slot = g_controllerProfiles;
    do {
        slot->mode = a;
        if (a == 0) {
            Control_ResetControllerPak(slot);
        }
        i += 1;
        slot += 1;
    } while (i < 4);
    if (a == 0) {
        Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
    }
}

void Control_SaveControllerSetup(void)
{
  s32 savedValueOffset;
  s32 profileValue;
  s32 profileIndex;
  s32 profileByteOffset;
  s32 profilesReset;
  ControllerProfile *profileCursor;
  profileIndex = 0;
  profileByteOffset = 0;
  do
  {
    profileValue = *((s32 *) ((&g_controllerProfileModeBase) + profileByteOffset));
 do { savedValueOffset = profileIndex * 4; profileIndex += 1; *((s32 *) (((u8 *) g_controllerSnapshotProfileValues) + savedValueOffset)) = profileValue; profileByteOffset += 548; } while (0);
  }
  while (profileIndex < 4);
  profilesReset = 0;
  Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
  profileCursor = g_controllerProfiles;
  do
  {
    Control_ResetControllerPak(profileCursor);
    profilesReset += 1;
    profileCursor += 1;
  }
  while (profilesReset < 4);
  g_controllerSetupSaved = 1;
}

void Control_RestoreControllerSetup(void) {
    ControllerProfile *slot;
    s32 i;
    s32 j;
    s32 profileByteOffset;
    s32 savedProfileValue;

    if (g_controllerSetupSaved != 0) {
        i = 0;
        slot = g_controllerProfiles;
        do {
            Control_ResetControllerPak(slot);
            i += 1;
            slot += 1;
        } while (i < 4);
        j = 0;
        profileByteOffset = 0;
        do {
            savedProfileValue = g_controllerSnapshotProfileValues[j];
            j += 1;
            *(s32 *)(&g_controllerProfileModeBase + profileByteOffset) = savedProfileValue;
            profileByteOffset += 548;
        } while (j < 4);
        Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
        g_controllerSetupSaved = 0;
    }
}

void Control_ClearMenuControlFlag(void) {
    g_controlMenuControlFlag = 0;
}

void Control_SetMenuControlFlag(void) {
    g_controlMenuControlFlag = 1;
}

void Control_CycleActorSnapshotMode(void) {
    Snapshot *snapshot;
    void *player;
    s32 enabled;
    Shared_Game *options;

    enabled = SetN64_IsModeThirteen() != 0;
    snapshot = &g_controllerActorSnapshot;
    if (g_sessionOptionResetMode == 0) {
        enabled = 0;
    }
    if (&g_world.mode == 0) {
        enabled = 0;
    }
    if (enabled) {
        switch (snapshot->mode) {
        case 0:
            snapshot->mode = 1;
            break;
        case 1:
            snapshot->mode = 2;
            break;
        case 2:
        default:
            snapshot->mode = 0;
            break;
        }
        Control_SaveActorSnapshot();
        snapshot->savedActorId = g_activeActorKind;
        options = &g_playerViewRenderContext.game;
        if (options->local == 0) {
            player = Playerai_GetFirstPlayer(&g_playerViewRenderContext);
            if (player != 0) {
                if (snapshot->mode == 1 &&
                    (g_activeActorKind != ((Shared_ActorView *)player)->spawn ||
                     (u16)(((Shared_ActorView *)player)->action - 22) < 12)) {
                    snapshot->mode = 2;
                }
                snapshot->savedActorId = ((Shared_ActorView *)player)->spawn;
            }
        }
    } else {
        snapshot->mode = 0;
    }
    if (snapshot->mode != 0) {
        snapshot->countdown = 240;
        snapshot->active = 1;
    } else {
        snapshot->countdown = 0;
        snapshot->active = 0;
    }
}

void Control_ResetActorSnapshot(void) {
    g_controllerActorSnapshot.active = 0;
    g_controllerActorSnapshot.mode = 0;
    g_controllerActorSnapshot.countdown = 0;
}

s32 Control_GetSnapshotActorId(void) {
    return g_controllerActorSnapshot.savedActorId;
}

int Control_IsSnapshotActive(void) {
    return g_controllerActorSnapshot.active;
}

void Control_DeactivateActorSnapshot(void) {
    g_controllerActorSnapshot.active = 0;
}

void Control_RestoreActorSnapshot(void) {
    s32 i;
    SnapshotActorView *actor;
    Snapshot *snapshot;
    ActorList *list;

    list = (ActorList *)&g_playerViewRenderContext;
    snapshot = &g_controllerActorSnapshot;
    for (i = 0; i < list->count; i++, list = (ActorList *)&g_playerViewRenderContext) {
        actor = &list->actors[i];
        actor->block = snapshot->blocks[i];
        if (snapshot->mode == 1) {
            actor->position = snapshot->positions[i];
            actor->yaw = snapshot->values[i];
            actor->id = Scene_GetModelSectionTwoRecord(&g_world, snapshot->handles[i]);
        }
    }
}

void Control_TickSnapshotCountdown(void) {
    Snapshot *p = &g_controllerActorSnapshot;
    s32 v = p->countdown;
    if (v != 0) {
        v = v - 1;
        p->countdown = v;
        if (v == 0) {
            p->mode = 0;
        }
    }
}

void Control_SaveActorSnapshot(void) {
    s32 i;
    SnapshotActorView *actor;
    Snapshot *snapshot;
    ActorList *list;

    list = (ActorList *)&g_playerViewRenderContext;
    snapshot = &g_controllerActorSnapshot;
    for (i = 0; i < list->count; i++) {
        actor = &list->actors[i];
        snapshot->blocks[i] = actor->block;
        snapshot->positions[i] = actor->position;
        snapshot->values[i] = actor->yaw;
        snapshot->handles[i] = Scene_GetModelSectionTwoIndex(&g_world, actor->id);
        list = (ActorList *)&g_playerViewRenderContext;
    }
}

/** Initialize a three-word record with a value and two zero words. */
void Control_InitializeCurvePlayer(unsigned int *record, unsigned int value) {
    record[0] = value;
    record[1] = 0;
    record[2] = 0;
}

s32 Control_AdvanceEffectCurve(void *curvePlayer) {
    SampledEffectCurveState *player = curvePlayer;
    f32 advancedTime;
    f32 remainingTime;
    s32 type;
    SampledCurve *curve;

    curve = player->curve;
    type = curve->type;
    switch (type) {
    case 0: {
        f32 divisor = g_displayedFramebufferAndRefreshRate[1];
        advancedTime = player->time + (g_controllerEffectTimeAdvanceScale.value / divisor);
        player->time = advancedTime;
        if (curve->length <= advancedTime) {
            return 1;
        }
        goto block_7;
    }
    case 1: {
        RandomCurve *random = (void *)curve;
        f32 divisor = g_displayedFramebufferAndRefreshRate[1];
        remainingTime = player->time - (g_controllerEffectTimeRetreatScale.value / divisor);
        player->time = remainingTime;
        if (remainingTime <= 0.0f) {
            player->time =
                remainingTime + random->period;
            player->value = Graphu64_RandomBetween(
                (f32)random->minimum * g_controllerEffectRandomRangeScale.value,
                (f32)random->maximum * g_controllerEffectRandomRangeScale.value);
        }
        goto block_7;
    }
    default:
block_7:
        return 0;
    }
}

/* Samples a curve at the player's time: a byte-sample curve (type 0) indexes its samples by time times 16 over the curve length and scales the byte to 0..1, a constant curve (type 1) returns the player's value, and any other type yields zero. */

float Control_SampleEffectCurve(SampledEffectCurveState *p) {
    SampledCurve *c = p->curve;

    switch (c->type) {
    case 0:
        return c->samples[(int)(p->time * 16.0f / c->length)] * (1.0f / 255.0f);
    case 1:
        return p->value;
    }
    return 0.0f;
}



/* 800C9400.CPP */
