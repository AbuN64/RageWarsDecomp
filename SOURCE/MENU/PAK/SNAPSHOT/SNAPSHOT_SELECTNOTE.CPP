#include "TYPES.H"
#include "RESMGR/resmgr_string_memory.H"
#include "MENU/PAK/SAVE_SNAPSHOT.H"
#include "COMMON/LONE/g_controllerPakReadyDialogResource.H"
#include "COMMON/LONE/g_pakProfileActionDialogResource.H"
#include "COMMON/SHAREDPLAYER.H"
#include "MENU/PAK_LOAD.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/CACHE_ALLOCATERESOURCE.H"
#include "COMMON/RESOURCELOCKSTATE.H"
#include "COMMON/MENURECAT24.H"
#include "UI/X_FILES/X_PLUS.H"

extern u8 *g_controllerPakSnapshotPayload;
extern s32 g_worldSnapshotNoteBytes;
extern s32 g_pakUseScannedChannel;
s32 Note_ReadNoteInfo(s32, s32, s32 *, u8 *, u8 *, s32 *, u8 *, u8 *);
s32 XPlus_StringLength(u8 *);
s32 Note_ReadNoteData(s32, s32, s32, s32);
u32 Note_Crc32(u8 *, u32, u32);
s32 Note_ContainsInvalidNameByte(u8 *, s32);
u8 *XPlus_CopyString(u8 *, u8 *);
void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);
s32 Snapshot_CheckStatusPrompt(void *, s32, s32);
static __inline__ s32 pak_note_has_game_id(u8 *company, u8 *code) { if ((XPlus_StringLength(code) == 4) && (XPlus_StringLength(company) == 2) && (XPlus_CompareStrings(code, rw_pak_game_code(&g_playerViewRenderContext.game)) == 0) && (XPlus_CompareStrings(company, rw_pak_company(&g_playerViewRenderContext.game)) == 0)) return 1; return 0; }
static __inline__ s32 pak_block_has_size(u8 *data,s32 expected) { return *(s32 *)data==expected; }
/* Load a Controller Pak note, validate its profile or save-block
 * checksum, and open the corresponding selection or error dialog. */
s32 Snapshot_SelectNote(s32 *selection, Shared_PakMenu *menu) {
    u8 extension[8];
    u8 company[8];
    u8 code[8];
    u8 name[16];
    s32 exists;
    s32 pages;
    s32 length;
    s32 noteIndex;
    s32 expectedSize;
    s32 status;
    s32 copying;
    s32 current;
    s32 allocationSize;
    u8 *text;
    char *messageExtra;
    s32 readError;
    s32 blockState;
    s32 profileMatches;
    s32 channel;
    s32 result;
    s32 gameNote;
    s32 i;
    struct Dialog *dialog;
    struct CacheResourceBlockView *handle;
    struct CacheResourceBlockView *handle2;
    u8 *payload;
    u8 *payload2;

    readError = 0;
    noteIndex = *selection - 3;
    expectedSize = g_worldSnapshotNoteBytes + 1552;
    if (g_pakUseScannedChannel != 0) {
        channel = g_introSelectedItem;
    } else {
        channel = menu->slot->controllerPort;
    }
    if (Snapshot_CheckStatusPrompt(menu, channel, 0) != 0) {
        g_pakMenuPromptAccepted = 1;
        return 1;
    }
    if (g_pakNoteSelectProbesNote != 0) {
        status = Note_ReadNoteInfo(channel, noteIndex, &exists, name, extension, &pages, company, code);
        if ((status == 0) && (exists == 0)) {
            menu->state = 20;
            Snapshot_MarkSaveNotes(menu);
            return 0;
        }
        gameNote = pak_note_has_game_id(company,code);
        if (gameNote != 0) {
            Shared_Game *settings = &g_playerViewRenderContext.game;
            profileMatches = XPlus_CompareStrings(name, rw_pak_profile_name(settings)) == 0;
            blockState = XPlus_CompareStrings(name, rw_pak_block_name(settings)) == 0;
        } else {
            profileMatches = 0;
            blockState = 0;
        }
        if ((status == 0) && (exists != 0)) {
            if (profileMatches != 0) {
                if (Note_ReadNoteData(channel, noteIndex, (s32)&g_pakControllerRecord, 24)!=0) {
                    profileMatches=0;
                    goto profile_failed;
                }
                if (Note_Crc32((u8 *)&g_pakControllerRecord,20,4)!=g_pakControllerRecord.checksum) {
                    profileMatches=0;
                    goto profile_failed;
                }
                    *rw_pak_loaded_profile() =g_pakControllerRecord;
                    g_controllerPakOverwriteNoteIndex=noteIndex;
                    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_selected_profile_dialog(), (s32)menu->player, (s32)menu->slot, (s32)menu->dialogData);
                    return 1;
profile_failed:
                readError=1;
            }
            if ((blockState != 0) && (readError == 0)) {
                blockState = pages;
                if (g_pakLoadedNoteResourceHandle != 0) {
                    Cache_DrainAndCompactResources(0);
                    Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
                }
                if (blockState != 0) blockState <<= 8;
                else {
                    blockState = g_worldSnapshotNoteBytes + 1552;
                }
                handle = Cache_AllocateResource(0, blockState, 51U, g_pakSingleSaveBlockName);
                payload = handle->data;
                g_pakLoadedNoteResourceHandle = handle;
                g_controllerPakSnapshotPayload = payload;
                XPlus_FillMemory(payload, 0, (u32) blockState);
                if (Note_ReadNoteData(channel, noteIndex, (s32)g_controllerPakSnapshotPayload, pages << 8)==0 &&
                    pak_block_has_size(g_controllerPakSnapshotPayload,expectedSize) &&
                    Note_Crc32(g_controllerPakSnapshotPayload,*(s32 *)g_controllerPakSnapshotPayload-4,11)==*(s32 *)(g_controllerPakSnapshotPayload+(*(s32 *)g_controllerPakSnapshotPayload-4)) &&
                    g_worldSnapshotNoteBytes==((s32 *)g_controllerPakSnapshotPayload)[1]) {
                    g_controllerPakOverwriteNoteIndex=noteIndex;
                    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_selected_block_dialog(), (s32)menu->player, (s32)menu->slot, (s32)menu->dialogData);
                    return 1;
                }
                blockState=0;
                readError=1;
            }
            if (profileMatches == 0) {
                if (blockState == 0) {
                    Shared_Game *settings = &g_playerViewRenderContext.game;
                    current = 0;
                    text = rw_pak_note_text(settings);
                    g_controllerPakOverwriteNoteIndex = noteIndex;
                    if (Note_ContainsInvalidNameByte(name, 16) != 0) {
                        XPlus_CopyString(name, (u8 *)rw_pak_invalid_name(settings));
                    }
                    copying = 1;
                    i = 0;
                    do {
                        if (copying != 0) {
                            current = (name)[i];
                        }
                        if (current == 0) {
                            copying = 0;
                            current = 32;
                        }
                        *text = current;
                        i += 1;
                        text += 1;
                    } while (i < 16);
                    copying = 1;
                    text += 1;
                    i = 0;
                    do {
                        if (copying != 0) {
                            current = (extension)[i];
                        }
                        if (current == 0) {
                            copying = 0;
                            current = 32;
                        }
                        *text = current;
                        i += 1;
                        text += 1;
                    } while (i < 4);
                    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_other_note_dialog(), (s32)menu->player, (s32)menu->slot, (s32)menu->dialogData);
                        return 1;
                }
            }
            goto done;
        }
        goto done;

    }
    if (g_pakProfileLoadActive != 0) {
        if ((g_pakProfileLoadMode_de != 0) && (readError == 0)) {
            if (((status=Note_ReadNoteInfo(channel, noteIndex, &exists, name, extension, &pages, company, code)) == 0) && (exists != 0)) {
                Shared_Game *settings = &g_playerViewRenderContext.game;
                if (XPlus_CompareStrings(name,rw_pak_profile_name(settings)) == 0) {
                if (Note_ReadNoteData(channel, noteIndex, (s32)&g_pakControllerRecord, 24)!=0) {
                    readError=1;
                    goto done;
                }
                if (Note_Crc32((u8 *)&g_pakControllerRecord,20,4)!=g_pakControllerRecord.checksum) {
                    readError=1;
                    goto done;
                }
                    *rw_pak_loaded_profile() =g_pakControllerRecord;
                    Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_loaded_profile_dialog(), (s32)menu->player, (s32)menu->slot, 0);
                    return 1;
                }
            }
            goto done;
        }
        if ((g_pakProfileLoadActive != 0) && (g_pakProfileLoadMode_de == 0)) {
            if (readError != 0) goto show_error;
            {
                if (((status=Note_ReadNoteInfo(channel, noteIndex, &exists, name, extension, &pages, company, code)) == 0) && (exists != 0) && (XPlus_CompareStrings(name, rw_pak_block_name(&g_playerViewRenderContext.game)) == 0)) {
                    allocationSize = pages;
                    if (g_pakLoadedNoteResourceHandle != 0) {
                        Cache_DrainAndCompactResources(0);
                        Cache_ReleaseResource(0, g_pakLoadedNoteResourceHandle);
                    }
                    if (allocationSize != 0) allocationSize <<= 8;
                    else {
                        allocationSize = g_worldSnapshotNoteBytes + 1552;
                    }
                    handle2 = Cache_AllocateResource(0, allocationSize, 51U, g_pakSingleSaveBlockName);
                    payload2 = handle2->data;
                    g_pakLoadedNoteResourceHandle = handle2;
                    g_controllerPakSnapshotPayload = payload2;
                    XPlus_FillMemory(payload2, 0, (u32) allocationSize);
                    if (Note_ReadNoteData(channel, noteIndex, (s32)g_controllerPakSnapshotPayload, pages << 8) == 0) {
                        length = *(s32 *)g_controllerPakSnapshotPayload;
                        if ((length == expectedSize) && (Note_Crc32(g_controllerPakSnapshotPayload, length - 4, 11U) == *(s32 *)(g_controllerPakSnapshotPayload+(*(s32 *)g_controllerPakSnapshotPayload-4))) && (g_worldSnapshotNoteBytes == ((s32 *)g_controllerPakSnapshotPayload)[1])) {
                            Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, rw_pak_loaded_block_dialog(), (s32)menu->player, (s32)menu->slot, 0);
                        return 1;
                        }
                    }
                    readError = 1;
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
                    goto done;
                }
                goto done;
            }
            goto show_error;
        }
        goto done;
    }
done:
    result = 0;
    if (readError != 0) {
show_error:
        if (g_pakProfileLoadMode_de != 0) messageExtra = g_pakProfileActionDialogResource;
        else messageExtra = g_controllerPakReadyDialogResource;
        dialog = rw_pak_load_error_dialog();
        g_controllerPakSelectedNoteIndex = noteIndex;
        Menu_OpenDialog(&g_playerViewRenderContext.dialogOwner, dialog, (s32)menu->player, (s32)menu->slot, (s32)messageExtra);
        result = 1;
    }
    return result;
}
