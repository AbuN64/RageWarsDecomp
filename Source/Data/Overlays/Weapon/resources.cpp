#include "Weapons/charge_and_linked_actor_handles.h"
#include "types.h"
#include "Data/Overlays/encoded_callback.h"
#include "Data/Ovl1_f/weapon_charge_callback_address.h"
#include "Data/Weapon_callbacks/weapon_updatenormalfireaction_address.h"
#include "Data/Weapon_callbacks/secondary_actor_callback_labels.h"
#include "Data/Weapon_callbacks/weaponai_updatechargeandrepeatcue_address.h"
#include "Resources/weapon_slot_behavior_words.h"

/* WEAPON_FIRE_AND_CHARGE_RESOURCES.CPP */
#if defined(VERSION_US_REV1)
#include "Common/runtime_declarations.h"
void * k_weaponResourceBehaviorPointers[8] = {
    (void *)&g_weaponFireStateCallbackTable, 0, 0, 0,
    0, 0, 0, 0,
};

struct {
    s32 id;
    void * callback;
} g_weaponReleaseLinkedActorHandlesCallback __attribute__((aligned(4))) = {
    2,
    (void *)ENCODED_CALLBACK_ADDRESS(Weapon_ReleaseLinkedActorHandles)
};
typedef char g_weaponReleaseLinkedActorHandlesCallbackSizeCheck[(sizeof(g_weaponReleaseLinkedActorHandlesCallback) == 8) ? 1 : -1];

void * g_weaponUpdateNormalFireActionCallback[2] = {
    (void *)&Weapon_UpdateNormalFireAction_Address, 0
};

struct {
    s32 animation;
    f32 scale;
    s32 parameter;
    u32 flags;
} g_weaponNormalFireAnimation __attribute__((aligned(4))) = {
    20100,
    1.0f,
    0,
    0x0
};
typedef char g_weaponNormalFireAnimationSizeCheck[(sizeof(g_weaponNormalFireAnimation) == 16) ? 1 : -1];

struct {
    s32 id;
    void * callback;
} g_weaponNormalFireEmptyCallbackSlot __attribute__((aligned(4))) = {
    3,
    0
};
typedef char g_weaponNormalFireEmptyCallbackSlotSizeCheck[(sizeof(g_weaponNormalFireEmptyCallbackSlot) == 8) ? 1 : -1];

void * g_weaponUpdateNormalFireActionAddressCallback[2] = {
    (void *)&Weapon_UpdateNormalFireAction_Address, 0
};

struct {
    s32 animation;
    f32 scale;
    s32 parameter;
    u32 flags;
} g_weaponNormalFireAddressAnimation __attribute__((aligned(4))) = {
    20100,
    1.0f,
    0,
    0x0
};
typedef char g_weaponNormalFireAddressAnimationSizeCheck[(sizeof(g_weaponNormalFireAddressAnimation) == 16) ? 1 : -1];

struct {
    s32 id;
    void * callback;
} g_weaponInitializeChargeAndStartupCuesAddressCallback __attribute__((aligned(4))) = {
    4,
    (void *)&Weapon_InitializeChargeAndStartupCues_Address
};
typedef char g_weaponInitializeChargeAndStartupCuesAddressCallbackSizeCheck[(sizeof(g_weaponInitializeChargeAndStartupCuesAddressCallback) == 8) ? 1 : -1];

void * g_weaponaiUpdateChargeAndRepeatCueAddressCallback[2] = {
    (void *)&Weaponai_UpdateChargeAndRepeatCue_Address, 0
};

struct {
    s32 animation;
    f32 scale;
    s32 parameter;
    u32 flags;
} g_weaponChargeRepeatCueAnimation __attribute__((aligned(4))) = {
    20200,
    1.0f,
    3,
    0x0
};
typedef char g_weaponChargeRepeatCueAnimationSizeCheck[(sizeof(g_weaponChargeRepeatCueAnimation) == 16) ? 1 : -1];

struct {
    s32 endState;
} g_weaponChargeRepeatCueEndState __attribute__((aligned(4))) = {
    -1
};
typedef char g_weaponChargeRepeatCueEndStateSizeCheck[(sizeof(g_weaponChargeRepeatCueEndState) == 4) ? 1 : -1];
#endif
