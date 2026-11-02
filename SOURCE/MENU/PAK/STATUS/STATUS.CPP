#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/ITEMRECAT24.H"
#include <ultra64.h>
#include "MENU/MENU_ACTION_TEXT_TABLES.H"
#include "MENU/PAK/PROFILE_PREVIEW_AND_LINE_TEXT.H"
#include "COMMON/MENU_TEXT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"

#if !defined(VERSION_DE)
/* Select the status text and right-align its nonblank characters. */
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
 /* const */
 /* const */
s32 Status_FormatRightAlignedPreviewName(struct Field *item) {
    s8 *outputCursor;
    s8 *unusedTextCursor;
    s32 nameLength;
    s32 clearIndex;
    s32 space;
    s32 copyIndex;
    s8 *clearCursor;
    u8 *nameTail;
    u8 *unusedNameCursor;
    u8 nameCharacter;
    nameLength = 8;
    if (g_pakUseDefaultPreviewLabels != 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        item->text = g_pakDefaultPreviewNameTexts_eu;
#else
        item->text = &g_pakDefaultPreviewNameText;
#endif
    } else {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        item->text = g_pakPreviewNameTexts_eu;
#else
        item->text = &g_pakPreviewNameText;
#endif
        nameTail = &g_controllerPakPreviewNameLastCharacter;
        while (*nameTail-- == 32 && nameLength != 0) nameLength--;
        outputCursor = RW_LOCALIZED_TEXT(*item->text, item->text, item->text, g_languageIndex);
        outputCursor = outputCursor + (Menu_CountLineChars(item) - 8);
        space = 32;
        clearIndex = 7;
        clearCursor = outputCursor + 7;
        do {
            *clearCursor = space;
            clearIndex -= 1;
            clearCursor -= 1;
        } while (clearIndex >= 0);
        outputCursor = outputCursor + (8 - nameLength);
        copyIndex = 0;
        if (nameLength > 0) {
            do {
                nameCharacter = g_controllerPakPreviewName[copyIndex];
                copyIndex += 1;
                *(u8 *)outputCursor = nameCharacter;
                outputCursor += 1;
            } while (copyIndex < nameLength);
        }
    }
    return 0;
}
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* g_pakPreviewNoteType is read through a struct view so the compiler keeps the load behind the preceding store. */
typedef struct { s8 value; } PakModeByte;
extern char *g_pakStatusLabelTemplate, *g_pakDefaultPreviewTypeLabel;
extern char *g_pakDefaultStatusText, *g_pakStatusFiveText, *g_pakStatusThreeText, *g_pakStatusTwoText, *g_pakStatusFourteenText;
/* Select the pak status label and right-align its eleven characters. */
s32 Status_UpdateStatusText(struct Field *item) {
    char *src;
    char *dst;
    s32 i;
    if (g_pakUseDefaultPreviewLabels != 0) {
        item->text = &g_pakDefaultPreviewTypeLabel;
    } else {
        item->text = &g_pakStatusLabelTemplate;
        i = ((PakModeByte *)&g_pakPreviewNoteType)->value;
        switch (i) {
        case 0:
        case 1:
        case 4:
        default:
            src = g_pakDefaultStatusText;
            break;
        case 5:
            src = g_pakStatusFiveText;
            break;
        case 3:
            src = g_pakStatusThreeText;
            break;
        case 2:
            src = g_pakStatusTwoText;
            break;
        case 14:
            src = g_pakStatusFourteenText;
            break;
        }
        dst = *item->text;
        dst += Menu_CountLineChars(item) - 11;
        for (i = 0; i < 11; i++) {
            *dst++ = *src++;
        }
    }
    return 0;
}
#endif
