#include "Weapons/pitch_translation_and_spin_actions.h"
#include "Data/rest_source_records.h"
#include "Data/Ovl1_f/weapon_charge_callback_address.h"
#include "Data/Weapon_event_callbacks/weaponai_tryenteralternateammomode.h"
#include "Data/Weapon_event_callbacks/weapon_request_release_on_enabled_event_address.h"
#include "Data/Weapon_event_callbacks/resource_callback_labels.h"
#include "Data/Weapon_event_callbacks/addrlow_weapon_updatealternatetriggercompletion.h"
#include "Data/Weapon_event_callbacks/weaponai_tryenterchargedalternatemode.h"
#include "Data/Weapon_event_callbacks/weapon_event_callback_address.h"
#include "Data/Weapon_event_callbacks/weapon_force_marker_address.h"
#include "include_asm.h"
#include "Data/Weapon_event_callbacks/weapon_initializefirestatecallbacks_label.h"
#include "Weapon_state_tables/weapon_state_tables.h"
#include "Common/runtime_declarations.h"

/* WEAPON_STATE_TABLES.CPP */
#if defined(VERSION_US_REV1)
WeaponStateScriptTable g_weaponStateScripts = {
    { 0, 0, 0, 0, 0, 0,
      0, (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0,
      0, 0, 0 },
    {
        { 2, (unsigned int)addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant2,
          (unsigned int)Weaponai_TryEnterAlternateAmmoMode, 0x00000000, 20100, 1.0f, 0, 0 },
        { 3, 0x00000000, (unsigned int)Weaponai_TryEnterAlternateAmmoMode, 0x00000000, 20110, 1.0f, 0, 0 },
        { 5, 0x00000000, (unsigned int)Weapon_RequestReleaseOnEnabledEvent, 0x00000000, 20200, 1.0f, 3, 0 },
    },
    -1,
    { 0, 0, 0, 0, 0, 0,
      0, (void *)((char *)&g_weaponChargeSpinTarget + 804), 0, 0, 0, 0,
      0, 0, 0 },
    {
        { 5, (unsigned int)Weapon_PlayStartupCue80C,
          (unsigned int)Weapon_UpdateAlternateTriggerCompletion, 0x00000000, 20200, 1.0f, 3, 0 },
    },
    -1,
    {
        { 0, 0, 0, 0, 0, 0, 0 },
        3e+01f,
        { (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0, 0, 0, 0 },
    },
    {
        { 2, 0x00000000, (unsigned int)Weaponai_TryEnterChargedAlternateMode, 0x00000000, 20100, 1.0f, 0, 0 },
        { 3, 0x00000000, (unsigned int)Weaponai_TryEnterChargedAlternateMode, 0x00000000, 20110, 1.0f, 0, 0 },
        { 5, 0x00000000, (unsigned int)Weapon_ApproachSpinPhaseAndRelease, 0x00000000, 20100, 1.0f, 3, 0 },
    },
    -1,
    { 0, 0, 0, 0, 0, 0,
      0, (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0,
      0, 0, 0 },
    {
        { 2, 0x00000000, (unsigned int)Weaponai_UpdateForceMarkerTrigger, 0x00000000, 20100, 1.0f, 0, 0 },
        { 3, 0x00000000, (unsigned int)Weaponai_UpdateForceMarkerTrigger, 0x00000000, 20110, 1.0f, 0, 0 },
    },
    -1,
    { 0, 0, 0, 0, 0, 0,
      0, (void *)&Weapon_InitializeFireStateCallbacks, 0 },
};

#endif
