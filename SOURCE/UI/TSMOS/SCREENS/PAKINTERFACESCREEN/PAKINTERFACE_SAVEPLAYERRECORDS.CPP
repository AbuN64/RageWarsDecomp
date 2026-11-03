#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/PAKMENU.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

#if defined(VERSION_DE)
enum { PAK_LIST_FIELD = 748 };
#elif defined(VERSION_EU_X)
enum { PAK_LIST_FIELD = 752 };
#else
enum { PAK_LIST_FIELD = 726 };
#endif

/* Moves player p's list cursor in the block g_pakProfileScreenState points to: direction 1 steps the cursor at
   0xAD8 of the player's 2920-byte record at 0x58 forward below 15 and scrolls the window at 0xADC
   so the cursor stays in the three visible rows (at most 13), any other direction steps both back
   while positive; then it sets the three row labels at 0xAE0 to alpha 0xFF with the texts of the
   70-byte name entries at 0x658 from the scroll position, and points item PAK_LIST_FIELD of the player's
   window at 0xC at the code at 0x3C of the entry under the cursor. */


void PAKInterface_ScrollNoteList(s32 player, s32 direction) {
    s32 i;
    s32 cursor;

    if (direction == 1) {
        if (g_pakProfileScreenState->players[player].slot < 15) {
            g_pakProfileScreenState->players[player].slot++;
            if (g_pakProfileScreenState->players[player].slot >= g_pakProfileScreenState->players[player].scroll + 3) {
                if (g_pakProfileScreenState->players[player].scroll + 3 < 15) {
                    g_pakProfileScreenState->players[player].scroll++;
                } else {
                    g_pakProfileScreenState->players[player].scroll = 13;
                }
            }
        }
    } else if (g_pakProfileScreenState->players[player].slot > 0) {
        g_pakProfileScreenState->players[player].slot--;
        if (g_pakProfileScreenState->players[player].scroll > 0 &&
            g_pakProfileScreenState->players[player].slot - g_pakProfileScreenState->players[player].scroll < 0) {
            g_pakProfileScreenState->players[player].scroll--;
        }
    }
    for (i = 0; i < 3; i++) {
        g_pakProfileScreenState->players[player].labels[i]->alpha = 0xFF;
        g_pakProfileScreenState->players[player].labels[i]->text =
            g_pakProfileScreenState->players[player].displayNames[g_pakProfileScreenState->players[player].scroll + i].text;
    }
    cursor = g_pakProfileScreenState->players[player].slot;
    Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_LIST_FIELD)->text =
        g_pakProfileScreenState->players[player].displayNames[cursor].code;
}

#include "COMMON/NAME.H"
#include "COMMON/PAK_SAVE_TEXT.H"
#include "MENU/PAK/pak_note_search.H"
#include "NOTE/NOTE_READNOTEINFO.H"
#include "NOTE/PAK_ALLOCATERENDERBUFFERS.H"
extern s32 Note_DeleteNote(s32, s32);
extern s32 Note_GetFreePages(s32, s32 *);
extern s32 Note_CountFreeNotes(s32, s32 *);
extern u32 Note_BytesToPakPages(u32);

extern u32 Note_Crc32(u8 *data, u32 byteCount, u32 initialCrc);
extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

extern void PAKInterface_RefreshPlayerPanel(s32);
/* The save view of the menu block: the four player records staged at 0x2E28, then the profile and
 * checksum stored behind them, written to the pak as one 0x648-byte note. */
static __inline__ PakMenuController *pakRecordSave(void) {
    return g_pakProfileScreenState;
}
/* The note's game code is read through the settings view in the PAL releases. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define RECORDS_NOTE_CODE (g_pakLegacySnapshotGameNames[rw_pak_settings()->language])
#else
#define RECORDS_NOTE_CODE RW_PAK_GAME_CODE
#endif
/* Replace or create the selected port's four-profile Controller Pak note: delete the old note if
 * there is one, else check that a free note and enough pages exist; then stage the port's records,
 * profile and CRC and save them. On failure the port's panel goes back to state 2. */
s32 PAKInterface_SavePlayerRecords(s32 channel)
{
    char extension[8];
    char name[16];
    struct { s32 note, fits, freePages, freeNotes; } space;
    s32 status, required;
    Profile *staged, *data;
    s32 i;
    u32 checksum;
    s32 success = 0;
    if (Note_FindNoteByName(rw_pak_save_name(), channel, &space.note) == 1) {
        success = Note_DeleteNote(channel, space.note) == 0;
    } else {
        space.fits = 0;
        status = Note_GetFreePages(channel, &space.freePages);
        if (status == 0) {
            status = Note_CountFreeNotes(channel, &space.freeNotes);
            if (status == 0) {
                required = Note_BytesToPakPages(PAKInterface_GetRecordsNoteSize());
                if (space.freeNotes == 0 || space.freePages < required) space.fits = 0;
                else space.fits = 1;
            }
        }
        /* Dead store kept from the original: flow deletes it, but it stops jump threading of
         * the two status tests above into the one below (ROM keeps both branches). */
        required = 0;
        if (status == 0 && space.fits == 1) success = 1;
    }
    if (success == 1) {
        success = 0;
        if (Note_FindFreeNoteExtension(channel, extension) == 0) {
            staged = pakRecordSave()->packet.saved;
            XPlus_CopyBytes(staged, pakRecordSave()->players[channel].records, 1600);
            pakRecordSave()->packet.savedProfile = pakRecordSave()->players[channel].profile;
            checksum = Note_Crc32(staged, 1600, 7);
            pakRecordSave()->packet.checksum = checksum;
            data = pakRecordSave()->packet.saved;
            for (i = 0; i < 16; i++) name[i] = 0;
            XPlus_CopyString(name, RW_PAK_RECORD_TITLE);
            if (Note_SaveNote(channel, 1608, data, name, extension, RECORDS_NOTE_CODE) == 0) success = 1;
        }
    }
    if (!success) {
        pakRecordSave()->players[channel].back = 2;
        pakRecordSave()->players[channel].state = 2;
        PAKInterface_RefreshPlayerPanel(channel);
    }
    return success;
}
