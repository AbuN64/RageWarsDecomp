#include "include_asm.h"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView ((u8 *)&g_gameSettings)

extern char *g_pakDefaultNoteNameFixed;

extern char s_pakNoteSizeFormatEuropean[];

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char s_pakNoteExtendedLabelFormatEuropean[], s_pakNoteLabelFormatEuropean[];
#else
extern const unsigned char g_noteInfoIntFormat[];

#endif
extern s32 Note_ReadNoteInfo(s32, s32, s32 *, char *, u8 *, s32 *, char *, char *);
extern s32 Note_ContainsInvalidNameByte(u8 *text, s32 count);
extern u8 *XPlus_CopyString(u8 *destination, u8 *source);
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);
extern s32 Note_GetFreePages(s32, s32 *);
extern u32 Note_BytesToPakPages(u32);
extern void PAKInterface_RefreshPlayerPanel(s32, s32);
extern void PAKInterface_ScrollNoteList(s32, s32);

/* Builds a player's controller pak note list: each of the sixteen notes gets its name (a default when unnamed), its size and a numbered label with the extension when it has one, or empty entries once the pak cannot be read; then the free and used page counts are formatted into their menu items, and on any read failure the slot is marked failed instead of opening the note menu. */
#if defined(VERSION_DE)
enum { PAK_RESOURCE_2D7 = 750, PAK_RESOURCE_2D8 = 749, PAK_RESOURCE_2DB = 746, PAK_RESOURCE_2DC = 745, PAK_RESOURCE_2DD = 747 };
#elif defined(VERSION_EU)


extern char *g_pakDefaultNoteNamesLocalized[];
extern void *g_slotSelectionTextReferenceShared7[];
enum { PAK_RESOURCE_2D7 = 727, PAK_RESOURCE_2D8 = 728, PAK_RESOURCE_2DB = 731, PAK_RESOURCE_2DC = 732, PAK_RESOURCE_2DD = 733 };
#elif defined(VERSION_EU_X)


extern char *g_pakUnnamedNoteTextsEuX[];
extern void *g_slotSelectionTextReferenceShared6[];

enum { PAK_RESOURCE_2D7 = 753, PAK_RESOURCE_2D8 = 751, PAK_RESOURCE_2DB = 754, PAK_RESOURCE_2DC = 755, PAK_RESOURCE_2DD = 756 };
#else
enum { PAK_RESOURCE_2D7 = 727, PAK_RESOURCE_2D8 = 728, PAK_RESOURCE_2DB = 731, PAK_RESOURCE_2DC = 732, PAK_RESOURCE_2DD = 733 };
#endif

#if !defined(VERSION_EU) && !defined(VERSION_EU_X)
static const char controller_pak_note_label_format[] = "%d.%s.%s";
#endif

void PAKInterface_LoadNoteList(s32 player)
{
    char name[24];
    u8 ext[8];
    char extra1[8];
    char extra2[8];
    s32 status;
    s32 size;
    s32 failed;
    s32 i;
    Label *item;
    s32 note_status;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    GameLocalizationState *settings;

#else
#endif
    failed = 0;
    for (i = 0; i < 16 && failed == 0; i++) {
        note_status = Note_ReadNoteInfo(player, i, &status, name, ext, &size, extra1, extra2);

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        settings = (GameLocalizationState *)g_gameSettingsView;

#else
#endif
        if (note_status == 0) {
            if (status == 1) {
                if (Note_ContainsInvalidNameByte(name, 16) == 1) {
#if defined(VERSION_EU)
                    XPlus_CopyString(name, ((g_pakDefaultNoteNamesLocalized)[settings->language]));
#elif defined(VERSION_EU_X)
                    XPlus_CopyString(name, ((g_pakUnnamedNoteTextsEuX)[settings->language]));
#else
                    XPlus_CopyString(name, (g_pakDefaultNoteNameFixed));
#endif
                }
                XPlus_CopyString(g_pakProfileScreenState->players[player].noteTexts[i].name, name);
                XStdio_FormatBuffer(g_pakProfileScreenState->players[player].noteTexts[i].size,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteSizeFormatEuropean,
#else
g_noteInfoIntFormat,
#endif
 size);
                if (ext[0] != 0) {
                    XStdio_FormatBuffer(g_pakProfileScreenState->players[player].noteTexts[i].label,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteExtendedLabelFormatEuropean,
#else
controller_pak_note_label_format,
#endif
 i + 1,
                                  g_pakProfileScreenState->players[player].noteTexts[i].name, ext);
                    continue;
                }
                goto numbered;
            }
        } else {
            failed = 1;
        }
#if defined(VERSION_EU)
        XPlus_CopyString(g_pakProfileScreenState->players[player].noteTexts[i].name, ((g_slotSelectionTextReferenceShared7)[settings->language]));
#elif defined(VERSION_EU_X)
        XPlus_CopyString(g_pakProfileScreenState->players[player].noteTexts[i].name, ((g_slotSelectionTextReferenceShared6)[settings->language]));
#else
        XPlus_CopyString(g_pakProfileScreenState->players[player].noteTexts[i].name, ((char *)g_slotSelectionTextReferenceShared1[0]));
#endif
        XStdio_FormatBuffer(g_pakProfileScreenState->players[player].noteTexts[i].size,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteSizeFormatEuropean,
#else
g_noteInfoIntFormat,
#endif
 0);
    numbered:
        XStdio_FormatBuffer(g_pakProfileScreenState->players[player].noteTexts[i].label,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteLabelFormatEuropean,
#else
s_pakNoteSizeFormatEuropean,
#endif
 i + 1,
                      g_pakProfileScreenState->players[player].noteTexts[i].name);
    }
    if (failed == 0) {
        /* the hub EC30 returns the item view; Label is this unit's text-bearing view of it */
        item = (Label *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2D8);
        if (Note_GetFreePages(player, &size) == 0) {
            XStdio_FormatBuffer(g_pakProfileScreenState->players[player].freeText,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteSizeFormatEuropean,
#else
g_noteInfoIntFormat,
#endif
 size);
            item->text = g_pakProfileScreenState->players[player].freeText;
            item = (Label *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2D7);
            size = PAKInterface_GetRecordsNoteSize();
            XStdio_FormatBuffer(g_pakProfileScreenState->players[player].usedText,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteSizeFormatEuropean,
#else
g_noteInfoIntFormat,
#endif
 Note_BytesToPakPages(size));
            item->text = g_pakProfileScreenState->players[player].usedText;
        } else {
            failed = 1;
        }
    }
    if (failed == 1) {
        g_pakProfileScreenState->players[player].state = failed;
        PAKInterface_RefreshPlayerPanel(player, PAK_RESOURCE_2DB);
        return;
    }
    g_pakProfileScreenState->players[player].slot = -1;
    g_pakProfileScreenState->players[player].scroll = 0;
    g_pakProfileScreenState->players[player].labels[0] = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2DB);
    g_pakProfileScreenState->players[player].labels[1] = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2DC);
    g_pakProfileScreenState->players[player].labels[2] = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2DD);
    PAKInterface_ScrollNoteList(player, 1);
}
