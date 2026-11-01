#include "COMMON/WORLD.H"
#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RECORDRECATCV1.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "MENU/PAK_LOAD.H"
#include "MENU/PAK/PAK_APPLYSTAGEDPLAYERPROFILE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENURECAT24.H"

/* 80409A88_2.CPP */
/* Copies the saved controller settings block g_pakControllerRecord into the settings the object at offset 0x5D8
   of an owner holds: the four halfwords, the flag byte into offset 0x80 and the eight bytes after it
   into offset 0x84. */

void Pak_ApplyStagedPlayerProfile(struct PlayerSavedProfileOwner *owner) {
    struct PakStatusProfile *settings = owner->settings;
    s32 i;

    settings->flags = g_pakControllerRecord.flag;
    settings->words[0] = g_pakControllerRecord.values[0];
    settings->words[1] = g_pakControllerRecord.values[1];
    settings->words[2] = g_pakControllerRecord.values[2];
    settings->words[3] = g_pakControllerRecord.values[3];
    for (i = 0; i < 8; i++) {
        settings->name[i] = g_pakControllerRecord.bytes[i];
    }
}

typedef struct SavedPlayer { s32 data[28]; } SavedPlayer;
typedef struct SavedSettings { s32 data[353]; } SavedSettings;
typedef struct SavedState {
    char pad0[8]; f32 rules[4]; SavedPlayer player; SavedSettings settings;
    u8 table[1];
} SavedState;
typedef struct RestorePlayer { char pad0[0x5E0]; SavedPlayer saved; } RestorePlayer;
extern SavedState *g_controllerPakSnapshotPayload;
extern s32 g_persistedOptionUnlockFlags[]; /* an array: its store may alias the loads through g_controllerPakSnapshotPayload, so it stays after them */
extern u8 g_frontendSavedVideoModeIndex;
extern u8 g_worldSnapshotNoteData[];
void Pak_RestoreSavedSession(RestorePlayer *player) {
    Shared_World *world = &g_world;
    s32 i;
    u8 *from, *to;
    u8 saved = g_frontendSavedVideoModeIndex;
    player->saved = g_controllerPakSnapshotPayload->player;
    *(SavedSettings *)&g_gameSettings = g_controllerPakSnapshotPayload->settings;
    g_gameSettings.counters.m_GameTimeFifteenth = g_controllerPakSnapshotPayload->rules[0];
    g_gameSettings.counters.m_GameTimeSeconds = g_controllerPakSnapshotPayload->rules[1];
    g_gameSettings.counters.m_GameTimeMinutes = g_controllerPakSnapshotPayload->rules[2];
    g_gameSettings.counters.m_GameTimeHours = g_controllerPakSnapshotPayload->rules[3];
    g_persistedOptionUnlockFlags[0] = ((SavedSettings *)&g_gameSettings)->data[1];
    g_gameSettings.resolution = saved;
    from = g_controllerPakSnapshotPayload->table;
    to = g_worldSnapshotNoteData;
    for (i = 0; i < world->noteCount; i++) *to++ = *from++;
}

/* 80409A88_3.CPP */
/* Returns g_introSelectedItem when g_pakUseScannedChannel is set, otherwise the signed byte at offset 4 of the object
   at offset 0x20 of a record. */

extern s32 g_pakUseScannedChannel;

s32 Pak_GetMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}
