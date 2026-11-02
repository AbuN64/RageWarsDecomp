#include "include_asm.h"
#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "TYPES.H"
#include "COMMON/MENURECAT24.H"
#include "MENU/PAK/SAVE_SNAPSHOT.H"
#include "MENU/PAK_PROFILE_PROMPT_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include <ultra64.h>
#include "MENU/PAK/PROFILE_SAVE_BLOCKS.H"
#include "UI/X_FILES/X_PLUS.H"

/* 80405DC0_15.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
extern char *g_pakLegacySnapshotGameNames[];
extern char *g_pakCompanyCodes[];

s32 Timer_MatchesGameIdentity(char *code, char *name) {
    Shared_Game *settings;
    if (XPlus_StringLength((u8 *)name) == 4 && XPlus_StringLength((u8 *)code) == 2) {
        settings = &g_gameSettings;
        if (XPlus_CompareStrings(name, g_pakLegacySnapshotGameNames[settings->language]) == 0 &&
            XPlus_CompareStrings(code, g_pakCompanyCodes[settings->language]) == 0) {
            return 1;
        }
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Reports whether the two-character code code and the four-character name name are the pair g_pakCompanyCodeFixed and g_pakLegacySnapshotGameNameFixed, measuring them with XPlus_StringLength and comparing them with XPlus_CompareStrings; returns one on a match and zero otherwise. */

extern char *g_pakLegacySnapshotGameNameFixed;

extern s32 XPlus_StringLength(u8 *);

s32 Timer_MatchesGameIdentity(char *code, char *name) {
    if (XPlus_StringLength((u8 *)name) == 4 && XPlus_StringLength((u8 *)code) == 2 &&
        XPlus_CompareStrings(name, g_pakLegacySnapshotGameNameFixed) == 0 && XPlus_CompareStrings(code, g_pakCompanyCodeFixed) == 0) {
        return 1;
    }
    return 0;
}
#endif

/* 80405DC0_16.CPP */
extern void Cache_ReleaseResource(void *cache, void *resource);

/* Returns the address of block n, n times 256; block zero is the area 0x610 bytes into the
   buffer g_worldSnapshotNoteBytes points to. */
extern char *g_worldSnapshotNoteBytes;

extern void Cache_DrainAndCompactResources(s32 a);

extern void **Cache_AllocateResource(s32, s32, s32, char *);

/* Releases the two active resources and clears their associated state. */

 /* extern */

 /* extern */

extern s32 g_controllerPakSnapshotPayload;

/* Saves the settings the object at offset 0x5D8 of an owner holds into the block g_pakControllerRecord: the
   flag byte, the four halfwords, three cleared bytes after the flag and the eight bytes at 0x84. */

extern struct Saved g_pakControllerRecord;

char *Timer_GetSaveBlockByteCount(s32 block) {
    if (block == 0) {
        return g_worldSnapshotNoteBytes + sizeof(SaveSnapshot);
    }
    return (char *) (block << 8);
}

void Timer_SetSaveTrailerValue(s32 offset, s32 value) {
    ((struct PlayerPakTimerView *) (g_worldSnapshotNoteBytes + offset))->trailerValue = value;
}

/* Returns the last word of a self-sized block: the first word holds the block's byte length and
   the result is the word just before that many bytes from the start. */
s32 Timer_GetSaveTrailerValue(s32 *block) {
    return ((struct AnimationEventMaskView *) (block[0] + (s32) block))[-1].value;
}

void Timer_AllocateSaveBlock(void ***handle, void **data, s32 units) {
    void **block;
    void *first;

    if (*handle != 0) {
        Cache_DrainAndCompactResources(0);
        Cache_ReleaseResource(0, *handle);
    }
    if (units != 0) {
        units <<= 8;
    } else {
        units = (s32)(g_worldSnapshotNoteBytes + sizeof(SaveSnapshot));
    }
    block = Cache_AllocateResource(0, units, 51, g_pakSingleSaveBlockName);
    *handle = block;
    first = *block;
    *data = first;
    XPlus_FillMemory(first, 0, units);
}

void Timer_ReleaseSaveBlocks(void) {
    if ((g_pakSnapshotResourceHandle != 0) || (g_pakLoadedNoteResourceHandle != 0)) {
        Cache_DrainAndCompactResources(0);
    }
    if (g_pakSnapshotResourceHandle != 0) {
        Cache_ReleaseResource(0, g_pakSnapshotResourceHandle);
    }
    if (g_pakLoadedNoteResourceHandle != 0) {
        Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
    }
    g_pakSnapshotResourceHandle = 0;
    g_pakLoadedNoteResourceHandle = 0;
    g_pakSaveSnapshot = 0;
    g_controllerPakSnapshotPayload = 0;
}

void Timer_CapturePlayerProfile(struct PlayerSavedProfileOwner *owner) {
    struct PakStatusProfile *settings = owner->settings;
    s32 i;

    g_pakControllerRecord.flag = settings->flags;
    g_pakControllerRecord.values[0] = settings->words[0];
    g_pakControllerRecord.values[1] = settings->words[1];
    g_pakControllerRecord.values[2] = settings->words[2];
    g_pakControllerRecord.values[3] = settings->words[3];
    g_pakControllerRecord.pad[0] = 0;
    g_pakControllerRecord.pad[1] = 0;
    g_pakControllerRecord.pad[2] = 0;
    for (i = 0; i < 8; i++) {
        g_pakControllerRecord.bytes[i] = settings->name[i];
    }
}
