#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "MENU/MENU_ACTION_TEXT_TABLES.H"
#include "MENU/PAK/PROFILE_PREVIEW_AND_LINE_TEXT.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "TYPES.H"
/* g_pakPreviewNoteType is read through a struct view so the compiler keeps the load behind the preceding store. */
typedef struct { s8 value; } PakModeByte;
extern s8 g_pakPreviewNoteType;
extern u8 *g_localizedPakStatusHeading[];
extern char *g_pakStatusDefaultText[];
extern char *g_pakStatusStateOneText[];
extern char *g_pakStatusStateTwoText[];
extern char *g_pakStatusStateThreeText[];
extern char *g_pakStatusStateFourText[];
/* Pak status line: picks the 11-character status text for the state g_pakPreviewNoteType in the current language and copies it into
   the entry's line; with g_pakUseDefaultPreviewLabels set it only selects the heading table. */
s32 Menu_FormatLocalizedPakStatus(struct Field *entry) {
    char *src;
    char *dst;
    s32 i;

    if (g_pakUseDefaultPreviewLabels != 0) {
        entry->text = g_localizedPakStatusHeading;
    } else {
        entry->text = g_localizedPakStatusLines;
        i = ((PakModeByte *)&g_pakPreviewNoteType)->value;
        switch (i) {
        case 0:
        case 1:
        case 4:
        default:
            src = g_pakStatusDefaultText[g_languageIndex];
            break;
        case 5:
            src = g_pakStatusStateOneText[g_languageIndex];
            break;
        case 3:
            src = g_pakStatusStateTwoText[g_languageIndex];
            break;
        case 2:
            src = g_pakStatusStateThreeText[g_languageIndex];
            break;
        case 14:
            src = g_pakStatusStateFourText[g_languageIndex];
            break;
        }
        dst = entry->text[g_languageIndex];
        dst += Menu_CountLineChars(entry) - 11;
        for (i = 0; i < 11; i++) {
            *dst++ = *src++;
        }
    }
    return 0;
}
#endif
