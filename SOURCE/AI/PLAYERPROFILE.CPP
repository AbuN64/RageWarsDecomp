#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "WORLD/PLAYERAI_RESPAWNFRAGTAGPLAYER.H"
#include "TYPES.H"
#include "UI/X_FILES/X_PLUS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "WORLD/PLAYERPROFILE.H"
#include "include_asm.h"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "WEAPONS/PLAYER_BUILDWEAPONHANDTRANSFORM.H"
#include "DATA/WEAPON_CALLBACKS/ADDRLOW_WEAPONAI_INITIALIZESWITCHFORSINGLEROUND.H"
#include "DATA/WEAPON_CALLBACKS/G_WEAPON_RESETCONTROLLERANDSPINENCODEDCALLBACK.H"
#include "DATA/WEAPON_CALLBACKS/ADDRLOW_WEAPON_RELEASEHANDLESANDEXITSTATE39.H"
#include "DATA/WEAPON_CALLBACKS/PLAYER_HEALTH_CALLBACK_LABELS.H"
#include "DATA/OVL1_F/WEAPON_CHARGE_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/OVERLAY_SIX_FIRST_CALLBACK_ROM_ENTRY.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_UPDATE_TRIGGER_RELEASE_STATE_ADDRESS.H"
#include "DATA/OVL1_D/WEAPON_CHARGE_FIVE_CALLBACK_ADDRESS.H"
#include "DATA/OVL1_F/WEAPON_UPDATE_HELD_FIRE_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_STATE_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_STARTUP_CUE_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/ADDRLOW_WEAPON_ADVANCESPINANDTRIGGERMODE.H"
#include "DATA/WEAPON_CALLBACKS/WEAPONAI_SELECTRELEASEDFIRESTATE_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_FIRE_STATE_TABLE.H"

/* PLAYERPROFILE.CPP */
void Player_InitializeProfile(void *profileStorage) {
    u8 *object = (u8 *)profileStorage;
    s32 i;
    u8 *cursor;

    XPlus_FillMemory(object, 0, 8);
    object[14] = 0;
    Player_SetProfileValue14(object, 0);
    Player_SetProfileValue15(object, 0);
    Player_SetProfileValue16(object, 0);
    Player_SetProfileProgress(object, 0);
    Player_SetProfileSlotValue(object, 0, 2);
    Player_SetProfileSlotValue(object, 1, 2);
    Player_SetProfileSlotValue(object, 2, 2);
    Player_SetProfileSlotValue(object, 3, 2);
    Player_SetProfileSlotValue(object, 4, 2);
    Player_SetProfileSlotValue(object, 5, 2);
    Player_SetProfileSlotValue(object, 6, 2);
    Player_SetProfileSlotValue(object, 7, 2);
    Player_SetProfileSlotValue(object, 8, 2);
    Player_SetProfileSlotValue(object, 9, 2);
    Player_SetProfileSlotValue(object, 10, 2);
    Player_SetProfileSlotValue(object, 17, 2);
    Player_SetProfileSlotValue(object, 18, 2);
    object[23] = 0;
    object[15] = 0;
    ((PlayerProfileStorage *)object)->totals[2] = 0;
    ((PlayerProfileStorage *)object)->totals[0] = 0;
    ((PlayerProfileStorage *)object)->totals[1] = 0;
    object[37] = 0;
    ((PlayerProfileStorage *)object)->state = 0;
    object[12] = 0;
    ((PlayerProfileStorage *)object)->resetSentinelByte = -1;
    XPlus_FillMemory(((Profile *)object)->plays, 0, 36);
    XPlus_FillMemory(&((Profile *)object)->groupFlags, 0, 1);
    XPlus_FillMemory(&((Profile *)object)->achievementFlags[7], 0, 3);
    XPlus_FillMemory(((Profile *)object)->slotLevels, 0, 100);
    Player_SetAchievementFlag7((s32)object, 0);
    Player_SetAchievementFlag7((s32)object, 5);
    Player_SetAchievementFlag7((s32)object, 7);
    XPlus_FillMemory(&((Profile *)object)->kindFlags[3], 0, 20);
    XPlus_FillMemory(((Profile *)object)->kindFlags, 0, 3);
    XPlus_FillMemory(((Profile *)object)->achievementFlags, 0, 7);
    XPlus_FillMemory(&((PlayerProfileStorage *)object)->pad78, 0, 1);
    XPlus_FillMemory(((PlayerProfileStorage *)object)->sensitivity, 0, 2);
    Player_SetAchievementFlag2F((s32)object, 0);
    Player_SetAchievementFlag2F((s32)object, 2);
    Player_SetAchievementFlag2F((s32)object, 3);
    Player_SetAchievementFlag2F((s32)object, 4);
    XPlus_FillMemory(((PlayerProfileStorage *)object)->controlRemap, 0, 2);
    XPlus_FillMemory(((Profile *)object)->levelFlags[0], 0, 5);
    XPlus_FillMemory(((Profile *)object)->levelFlags[2], 0, 5);
    XPlus_FillMemory(((Profile *)object)->levelFlags[3], 0, 5);
    XPlus_FillMemory(((Profile *)object)->levelFlags[1], 0, 5);
    i = 35;
    do {
        ((PlayerProfileStorage *)object)->counters[i] = 0;
        i--;
    } while (i >= 0);
    XPlus_FillMemory(&((Profile *)object)->trackFlags, 0, 1);
    object[394] = 1;
    object[395] = 134;
    object[393] = 0;
    object[396] = 132;
    object[397] = 0;
}

extern u8 g_localPlayerProfiles[];
extern u8 g_profileSlotResetWord[];
extern s8 g_profileSlotResetFlags[];
extern s8 g_profileSlotIndices[];
extern s8 g_profileSlotEnabledFlags[];
extern s8 g_profileSlotSettingsByte7B[];
extern s8 g_profileSlotSettingsByte7D[];
extern s8 g_profileSlotSettingsByte79[];
extern s8 g_profileSlotSettingsByte7A[];
extern s8 g_profileSlotSettingsByte82[];
extern u8 g_playerSettings[];
extern s32 g_profileSlotNameFormat;

extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);

void Player_InitializeProfileSlot(s32 profileSlot) {
    s32 offset;
    u8 *entry;
    u8 *config;

    offset = profileSlot * 400;
    entry = g_localPlayerProfiles + offset;
    Player_InitializeProfile(entry);
    *(s32 *)(g_profileSlotResetWord + offset) = 0;
    g_profileSlotIndices[offset] = profileSlot;
    g_profileSlotResetFlags[offset] = 0;
    g_profileSlotEnabledFlags[offset] = 1;
    XStdio_FormatBuffer(entry, g_profileSlotNameFormat, profileSlot + 1);
    config = g_playerSettings + profileSlot * sizeof(Shared_PlayerSettingsRecord);
    g_profileSlotSettingsByte7B[offset] = config[123];
    g_profileSlotSettingsByte7D[offset] = config[125];
    g_profileSlotSettingsByte79[offset] = config[121];
    g_profileSlotSettingsByte7A[offset] = config[122];
    g_profileSlotSettingsByte82[offset] = config[130];
}

void Player_SetProfileValue14(void *profileStorage, unsigned char value) {
    ((PlayerProfileStorage *)profileStorage)->value14 = value;
}

/** Advance the byte at offset 0x14 by ten. */
void Player_AddTenToProfileValue14(void *object) {
    ((PlayerProfileStorage *)object)->value14 += 10;
}

/** Read the byte at object offset 0x14. */
unsigned char Player_GetProfileValue14(PlayerProfileStorage *profileStorage) {
    return profileStorage->value14;
}

/** Store a byte in the object field at offset 0x15. */
void Player_SetProfileValue15(void *object, unsigned char value) {
    ((PlayerProfileStorage *)object)->value15 = value;
}

int Player_AddFiftyToProfileValue15(void *player) {
    int v = ((PlayerProfileStorage *)player)->value15 + 50;
    ((PlayerProfileStorage *)player)->value15 = (unsigned char)v;
    return v;
}

unsigned char Player_GetProfileValue15(PlayerProfileStorage *profileStorage) {
    return profileStorage->value15;
}

/** Store the supplied byte at offset 0x16. */
void Player_SetProfileValue16(void *object, unsigned char value) {
    ((PlayerProfileStorage *)object)->value16 = value;
}

int Player_AddFiftyToProfileValue16(void *player) {
    int v = ((PlayerProfileStorage *)player)->value16 + 50;
    ((PlayerProfileStorage *)player)->value16 = (unsigned char)v;
    return v;
}

/** Read the object byte at offset 0x16. */
unsigned char Player_GetProfileValue16(PlayerProfileStorage *object) {
    return object->value16;
}

void Player_SetProfileProgress(void *profileStorage, int progress) {
    ((PlayerProfileStorage *)profileStorage)->progress = progress;
}

/** Advance the word at offset 0x10 by 0x500. */
void Player_AdvanceProfileProgress(void *object) {
    ((PlayerProfileStorage *)object)->progress += 1280;
}

/** Return the word stored at offset 0x10. */
unsigned int Player_GetProfileProgress(PlayerProfileStorage *object) {
    return object->progress;
}

/* Stores a byte into the object's slot table at 0x18: indices 0 to 10 directly, 17 and 18 into
   slots 11 and 12, and other indices are ignored. */

void Player_SetProfileSlotValue(PlayerProfileStorage *obj, int index, char value) {
    if (index == 17) {
        goto is17;
    }
    if (index < 18) {
        goto below18;
    }
    if (index == 18) {
        goto is18;
    }
    return;
below18:
    if (index >= 11) {
        return;
    }
    if (index < 0) {
        return;
    }
    goto store;
is18:
    index = 12;
    goto store;
is17:
    index = 11;
store:
    obj->slots[index] = value;
}

/* Increments the object's byte counter for a slot in the table at 0x18: indices 0 to 10 directly,
   17 and 18 as slots 11 and 12, and other indices are ignored. */

void Player_IncrementLevelProgress(Profile *obj, int index) {
    if (index == 17) {
        goto is17;
    }
    if (index < 18) {
        goto below18;
    }
    if (index == 18) {
        goto is18;
    }
    return;
below18:
    if (index >= 11) {
        return;
    }
    if (index < 0) {
        return;
    }
    goto store;
is18:
    index = 12;
    goto store;
is17:
    index = 11;
store:
    obj->levelProgress[index]++;
}

s32 Player_GetLevelProgress(Profile *obj, s32 index) {
    if (index == 17) {
        goto slot17;
    }
    if (index < 18) {
        goto lower;
    }
    if (index == 18) {
        goto slot18;
    }
    goto invalid;
lower:
    if (index >= 11) { goto invalid; }
    if (index < 0) { goto invalid; }
    goto load;
slot17:
    index = 11;
    goto load;
slot18:
    index = 12;
    goto load;
invalid:
    return 2;
load:
    return obj->levelProgress[index];
}

extern void Graphu64_ScaleVector(void *, void *, f32);

extern void Graphu64_BuildScaleMatrix(void *, f32, f32, f32);

extern void Graphu64_GetMatrixTranslation(char *, f32 *);

extern void Player_BuildPlayerViewTransform(char *, Matrix *);

extern void Player_BuildPlayerOrientation(char *object, CQuatern *output);

extern void MatrixFromQuaternion(f32 *q, f32 *m);

extern void TranslateMatrix(char *, f32, f32, f32);

extern void SwapMatrixUpForward(void *);

extern void Graphu64_MultiplyAffineMatrices(void *, void *, void *);

extern s32 Defs_TestBit(void *, s32);
extern void Defs_SetBitValue(u8 *, s32, s32);
void Player_SetAchievementFlag2F(Profile *player, s32 achievementIndex) {
    Defs_SetBitValue(player->unlockFlags, achievementIndex, 1);
}

s32 Player_HasProfileUnlockFlag(u8 *profileBytes, s32 unlockIndex)
{
  if (unlockIndex == 16)
  {
    return 1;
  }
  if (unlockIndex == 17)
  {
    if (unlockIndex || profileBytes)
    {
      return 1;
    }
    else
    {
      return 1;
    }
  }
  return Defs_TestBit(((Profile *)profileBytes)->unlockFlags, unlockIndex);
}

void Player_SetAchievementFlagByIndex(Profile *player, s32 achievementIndex) {
    u8 *achievementBits;
    s32 mappedAchievementIndex = achievementIndex;

    switch (mappedAchievementIndex) {
    case 16:
        achievementBits = &player->achievementFlags[46];
        mappedAchievementIndex = 0;
        break;
    case 17:
        achievementBits = &player->achievementFlags[46];
        mappedAchievementIndex = 1;
        break;
    default:
        achievementBits = &player->achievementFlags[49];
        break;
    }
    Defs_SetBitValue(achievementBits, mappedAchievementIndex, 1);
}

s32 Player_GetProfileAchievementFlag(Profile *profile, s32 achievementIndex) {
    u8 *achievementBits;
    s32 index = achievementIndex;

    switch (index) {
    case 16:
        achievementBits = &profile->achievementFlags[46];
        index = 0;
        break;
    case 17:
        achievementBits = &profile->achievementFlags[46];
        index = 1;
        break;
    default:
        achievementBits = &profile->achievementFlags[49];
        break;
    }
    return Defs_TestBit(achievementBits, index);
}

void Player_SetAchievementFlag7(Profile *record, s32 achievementIndex) {
    Defs_SetBitValue(&record->achievementFlags[7], achievementIndex, 1);
}

/** Tests bit index of the profile achievement flags at +7 (the character unlocks). */
s32 Player_TestAchievementFlag7(Profile *record, s32 index) {
    return Defs_TestBit(&record->achievementFlags[7], index);
}

void Player_BuildWeaponHandTransform(char *weaponActor) {
    CVector3 position;
    Matrix worldMatrix;
    CVector3 scaledOffset;
    CVector3 handOffset;
    Matrix offsetMatrix;
    Matrix viewMatrix;
    CQuatern viewOrientation;
    char *object;
    char *orientation;

    object = ((PlayerProfileAttachmentView *)(weaponActor))->owner;
    handOffset = ((struct WeaponHandOffsetView *) g_weaponInfoByType[((PlayerProfileWeaponView *) object)->selectedAction])->handOffset;
    if (g_weaponHandMirrorX != 0) {
        handOffset.x = -handOffset.x;
    }
    if (g_weaponHandMirrorY != 0) {
        handOffset.y = -handOffset.y;
    }
    if (g_weaponHandMirrorZ != 0) {
        handOffset.z = -handOffset.z;
    }
    Graphu64_ScaleVector(&scaledOffset, &((PlayerProfileAttachmentView *)(weaponActor))->scale, 0.1f);
    Graphu64_BuildScaleMatrix(&offsetMatrix, scaledOffset.x, scaledOffset.y, scaledOffset.z);
    Graphu64_ScaleVector(&handOffset, &handOffset, -10.24f);
    if (((PlayerProfileWeaponView *)(object))->camera.v0 != 0) {
        Graphu64_GetMatrixTranslation(&((GameplayCamera *)((PlayerProfileWeaponView *)object)->camera.v1)->viewOrient, &position);
        MatrixFromQuaternion((CQuatern *)(&((GameplayCamera *)((PlayerProfileWeaponView *)object)->camera.v1)->orientation),
                      &worldMatrix);
    } else {
        Player_BuildPlayerViewTransform(object, &viewMatrix);
        Player_BuildPlayerOrientation(object, &viewOrientation);
        Graphu64_GetMatrixTranslation((char *)&viewMatrix, &position);
        MatrixFromQuaternion(&viewOrientation, &worldMatrix);
    }
    orientation = (char *)&((LevelActor *)weaponActor)->transform;
    TranslateMatrix(&offsetMatrix, handOffset.x, handOffset.y, handOffset.z);
    SwapMatrixUpForward(&offsetMatrix);
    Graphu64_MultiplyAffineMatrices((Matrix *)orientation, &offsetMatrix, &worldMatrix);
    TranslateMatrix((Matrix *)orientation, position.x, position.y, position.z);
}

/* PLAYERAI_INITIALIZEPLAYERHEALTH_DATA__PLAYERPROFILE.CPP */
#if defined(VERSION_US_REV1)
extern char addrLow_Weapon_ReleaseLinkedActorHandles[];

/* Rates read by Playerai_UpdateTargetFacing and Playerai_UpdateReactionReserve. */

/* Linker fill between the rate and the next constant: no instruction reads it and the other builds hold other words here. */

/* Mirror flags read by Player_BuildWeaponHandTransform, followed by two unused zero words. */
s32 g_weaponHandMirrorX = 0;
s32 g_weaponHandMirrorY = 0;
s32 g_weaponHandMirrorZ = 0;
s32 g_weaponHandMirrorPad[2] = { 0, 0 };

f32 k_PlayeraiInitializeplayerhealthNegativeThree = -3.0f;

/* Base state table of the weapon fire state machine (Weapon_InitializeFireStateCallbacks installs it). */

/* Spin weapon states searched before the base table. */

/* Trigger release weapon states searched before the base table. */
#endif
