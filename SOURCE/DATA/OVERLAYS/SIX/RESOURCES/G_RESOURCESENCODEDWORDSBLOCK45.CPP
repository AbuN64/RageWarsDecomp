#include "TYPES.H"

#include "DATA/OVL1_F/WEAPON_CHARGE_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_UPDATENORMALFIREACTION_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/SECONDARY_ACTOR_CALLBACK_LABELS.H"
#include "DATA/WEAPON_CALLBACKS/OVERLAY_SIX_SECOND_CALLBACK_ROM_ENTRY.H"

/* 800CF51C.CPP */
#if defined(VERSION_US_REV1)
extern char g_weaponFireStateCallbackTable[];
void * k_ResourcesEncodedWordsBlock3[8] = {
    (void *)&g_weaponFireStateCallbackTable, 0, 0, 0,
    0, 0, 0, 0,
};
#endif

/* 800CF51C_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D013C_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * callback;
} g_ResourcesEncodedWordsBlock8 __attribute__((aligned(4))) = {
    2,
    (void *)&addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant2
};
typedef char g_ResourcesEncodedWordsBlock8SizeCheck[(sizeof(g_ResourcesEncodedWordsBlock8) == 8) ? 1 : -1];
#endif
#endif

/* 800CF544.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF51C_unclaimed_D0144 */
#if defined(VERSION_US_REV1)
void * g_ResourcesEncodedWordsBlock33[2] = {
    (void *)&Weapon_UpdateNormalFireAction_Address, 0
};
#endif

#if defined(VERSION_US_REV1)
struct {
    s32 animation;
    f32 scale;
    s32 parameter;
    u32 flags;
} g_ResourcesEncodedWordsBlock72 __attribute__((aligned(4))) = {
    20100,
    1.0f,
    0,
    0x0
};
typedef char g_ResourcesEncodedWordsBlock72SizeCheck[(sizeof(g_ResourcesEncodedWordsBlock72) == 16) ? 1 : -1];
#endif
#endif

/* 800CF55C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D015C_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * callback;
} g_ResourcesEncodedWordsBlock25 __attribute__((aligned(4))) = {
    3,
    0
};
typedef char g_ResourcesEncodedWordsBlock25SizeCheck[(sizeof(g_ResourcesEncodedWordsBlock25) == 8) ? 1 : -1];
#endif
#endif

/* 800CF564.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF51C_unclaimed_D0144_unclaimed_D015C_unclaimed_D0164 */
#if defined(VERSION_US_REV1)
void * g_ResourcesEncodedWordsBlock21[2] = {
    (void *)&Weapon_UpdateNormalFireAction_Address, 0
};
#endif
#endif

/* 800CF564_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D016C_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 animation;
    f32 scale;
    s32 parameter;
    u32 flags;
} g_ResourcesEncodedWordsBlock36 __attribute__((aligned(4))) = {
    20100,
    1.0f,
    0,
    0x0
};
typedef char g_ResourcesEncodedWordsBlock36SizeCheck[(sizeof(g_ResourcesEncodedWordsBlock36) == 16) ? 1 : -1];
#endif
#endif

/* 800CF57C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D017C_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * callback;
} g_ResourcesEncodedWordsBlock45 __attribute__((aligned(4))) = {
    4,
    (void *)&Weapon_InitializeChargeAndStartupCues_Address
};
typedef char g_ResourcesEncodedWordsBlock45SizeCheck[(sizeof(g_ResourcesEncodedWordsBlock45) == 8) ? 1 : -1];
#endif
#endif

/* 800CF584.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF51C_unclaimed_D0144_unclaimed_D015C_unclaimed_D0164_unclaimed_D017C_unclaimed_D0184 */
#if defined(VERSION_US_REV1)
void * g_ResourcesEncodedWordsBlock57[2] = {
    (void *)&Weaponai_UpdateChargeAndRepeatCue_Address, 0
};
#endif

#if defined(VERSION_US_REV1)
struct {
    s32 animation;
    f32 scale;
    s32 parameter;
    u32 flags;
} g_ResourcesEncodedWordsBlock74 __attribute__((aligned(4))) = {
    20200,
    1.0f,
    3,
    0x0
};
typedef char g_ResourcesEncodedWordsBlock74SizeCheck[(sizeof(g_ResourcesEncodedWordsBlock74) == 16) ? 1 : -1];
#endif
#endif

/* 800CF59C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D019C_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 endState;
} g_ResourcesEncodedWordsBlock43 __attribute__((aligned(4))) = {
    -1
};
typedef char g_ResourcesEncodedWordsBlock43SizeCheck[(sizeof(g_ResourcesEncodedWordsBlock43) == 4) ? 1 : -1];
#endif
#endif

/* 800CF5A0.CPP */

