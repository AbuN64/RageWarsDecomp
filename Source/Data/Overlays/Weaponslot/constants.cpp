#include "Gfxdata/audio_decodeframe_data.h"
#include "types.h"
#include "include_asm.h"
#include "Ammo/ammo.h"
#include "Common/runtime_declarations.h"
#include "Data/rest_source_records.h"
#include "Weapon_state_tables/weapon_state_tables.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Weapons/pitch_translation_and_spin_actions.h"
#include "Data/Overlays/Weaponslot/weapon_slot_block.h"
#include "Data/Overlays/Weaponslot/constants_addresses.h"
#include "Menu_label_slots/menu_label_slots.h"
#include "Data/Weapon_event_translation/weaponai_initializeswitchandrequestidle_data.h"

/* OVERLAY_SEVEN_THREE_THEN_ZERO_FLOATS.CPP */
#if defined(VERSION_DE)
const float g_weaponSlotXOffsetVector[4] __attribute__((aligned(4))) = { 3.0f, 0.0f, 0.0f, 0.0f };
#endif
#if defined(VERSION_EU)
const float g_weaponSlotXOffsetVector[4] __attribute__((aligned(4))) = { 3.0f, 0.0f, 0.0f, 0.0f };
#endif
#if defined(VERSION_EU_X)
const float g_weaponSlotXOffsetVector[4] __attribute__((aligned(4))) = { 3.0f, 0.0f, 0.0f, 0.0f };
#endif
#if defined(VERSION_US)
const float g_weaponSlotXOffsetVector[4] __attribute__((aligned(4))) = { 3.0f, 0.0f, 0.0f, 0.0f };
#endif
#if defined(VERSION_US_REV1)
const float g_weaponSlotXOffsetVector[4] __attribute__((aligned(4))) = { 3.0f, 0.0f, 0.0f, 0.0f };
#endif

/* G_OVERLAYSSEVENCONSTANTSRETAINEDWORDS6.CPP */
#if defined(VERSION_US_REV1)

void * g_weaponAmmoRequirementPairPointers[7] = {
    0, (void *)&g_weaponAmmoRequirementPairs[50], (void *)&g_weaponAmmoRequirementPairs[52], 0,
    (void *)&g_weaponAmmoRequirementPairs[108], (void *)&g_weaponAmmoRequirementPairs[110], 0,
};
#endif

/* WEAPON_SLOT_BLOCK.CPP */
#if defined(VERSION_US_REV1)
/* us-rev1 rom 0xD0F84-0xD1110: four weapon slots (stride 0x60) and the
   view offset that opens the next slot. Rows were 26 per-row globals. */
WeaponSlotBlock g_weaponSlotBlock __attribute__((aligned(4))) = {
    {
        {
            { 6.0f, 7.0f, 1.0e+01f },
            { 0, 0, 1.0f, 1.0f, (void *)&g_weaponStateScripts.chargedAlternateFireState.callbacks[0],
              (void *)&Weapon_TranslateEventSixByPitch, 0 },
            { (unsigned int)&g_backdropTextLines[204], { 0x04D5, 0x0BC8 } },
            { 0, -1 },
            { { 0xFFFF, 0x02C6, 0x02C7, 0x0000 }, 0x00000003 },
            4.0f,
            { 0.785398245f, (void *)&g_weaponAmmoRequirementPairs[54], 0, 0,
              (void *)&g_weaponAmmoRequirementPairs[112], 0, 0 },
        },
        {
            { 6.0f, 7.0f, 1.0e+01f },
            { 0, 0, 1.0f, 1.0f, (void *)&g_weaponFireStateCallbackTable, 0, 0 },
            { (unsigned int)&g_backdropTextLines[208], { 0x04D6, 0x0BC9 } },
            { 0, -1 },
            { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
            0.0f,
            { 0.0f, (void *)&g_weaponAmmoRequirementPairs[114], 0, 0,
              (void *)&g_weaponAmmoRequirementPairs[56], 0, 0 },
        },
        {
            { 6.0f, 7.0f, 1.0e+01f },
            { 0, 0, 1.0f, 1.0f, (void *)&g_weaponFireStateCallbackTable, 0, 0 },
            { (unsigned int)&g_backdropTextLines[212], { 0x04D7, 0x0BCA } },
            { 0, -1 },
            { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
            0.0f,
            { 0.0f, (void *)&g_weaponAmmoRequirementPairs[60], 0, 0,
              (void *)&g_weaponAmmoRequirementPairs[118], 0, 0 },
        },
        {
            { 6.0f, 7.0f, 1.0e+01f },
            { 0, 0, 1.0f, 1.0f, (void *)&g_weaponFireStateCallbackTable, 0, 0 },
            { (unsigned int)&g_backdropTextLines[220], { 0x04D9, 0x0BCC } },
            { 0, -1 },
            { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
            0.0f,
            { 0.0f, (void *)&g_weaponAmmoRequirementPairs[58], 0, 0,
              (void *)&g_weaponAmmoRequirementPairs[116], 0, 0 },
        },
    },
    { 6.0f, 7.0f, 1.0e+01f },
};
typedef char g_weaponSlotSizeCheck[(sizeof(WeaponSlot) == 0x60) ? 1 : -1];
typedef char g_weaponSlotBlockSizeCheck[(sizeof(WeaponSlotBlock) == 0x18C) ? 1 : -1];
#endif

/* WEAPONAI_INITIALIZESWITCHANDREQUESTIDLE_DATA.CPP */
#if defined(VERSION_US_REV1)
struct {
    void * reserved0;
    void * reserved1;
    f32 scale;
    f32 speed;
    void * states;
    void * enter;
    void * update;
} g_weaponaiInitializeSwitchAndRequestIdleData __attribute__((aligned(4))) = {
    0,
    0,
    1.0f,
    1.0f,
    (void *)&g_weaponFireStateCallbackTable,
    0,
    0
};
typedef char g_weaponaiInitializeSwitchAndRequestIdleDataSizeCheck[
    (sizeof(g_weaponaiInitializeSwitchAndRequestIdleData) == 28) ? 1 : -1];

void * g_weaponResourceDirectory[22] = {
    (void *)&g_weaponSecondaryPresentationLabel, (void *)&g_weaponSlotRecords.linkedSlots[0].head.presentation,
    (void *)&g_weaponSlotRecords.linkedSlots[1].head.presentation, (void *)&g_weaponSlotRecords.linkedSlots[2].head.presentation,
    (void *)&g_weaponSlotRecords.linkedSlots[3].head.presentation, (void *)&g_weaponSlotRecords.linkedSlots[4].head.presentation,
    (void *)&g_weaponSlotRecords.linkedSlots[5].head.presentation, (void *)&g_weaponSlotRecords.lastSlot.presentation,
    (void *)&g_weaponSlotPresentationRows[0].presentation, (void *)&g_weaponSlotPresentationRows[1].presentation,
    (void *)&g_weaponSlotPresentationRows[2].presentation, (void *)&g_weaponSlotPresentationRows[3].presentation,
    (void *)&g_weaponSlotPresentationRows[4].presentation, (void *)&g_weaponSlotPresentationRows[5].presentation,
    (void *)&g_weaponSlotPresentationRows[6].presentation, (void *)&g_weaponSlotPresentationRows[7].presentation,
    (void *)&g_weaponPrimaryPresentationLabel, (void *)&g_weaponSlotRecords.firstSlot.presentation,
    (void *)&g_weaponSlotBlock.slots[0].presentationDescriptor, (void *)&g_weaponSlotBlock.slots[1].presentationDescriptor,
    (void *)&g_weaponSlotBlock.slots[2].presentationDescriptor, (void *)&g_weaponSlotBlock.slots[3].presentationDescriptor,
};

struct {
    u32 previousReserved;
    s16 ammoClassIconIds[8];
    void * indexedValues[7];
    s32 indexedSentinel;
    s32 cameraModes[3];
    void * cameraCallback;
} g_weaponAmmoClassIconAndCameraModeRecord __attribute__((aligned(4))) = {
    0x0,
    { 3050, 3051, 3052, -1, 3053, 3054, 3055, 3056 },
    { (void *)&g_itemLabelSlots, &g_itemLabelSlots[1], &g_itemLabelSlots[2], &g_itemLabelSlots[3], &g_itemLabelSlots[4],
    &g_itemLabelSlots[5], &g_itemLabelSlots[6] },
    -1,
    { 1, 1, 0 },
    (void *)&g_Gsky_FloorSurfaceNoOpAddress
};
typedef char g_weaponAmmoClassIconAndCameraModeRecordSizeCheck[
    (sizeof(g_weaponAmmoClassIconAndCameraModeRecord) == 68) ? 1 : -1];
#endif
