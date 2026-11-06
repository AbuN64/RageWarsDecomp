#include "Fx/fx_address_symbols.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/Lone/g_pakdefaultpreviewtypelabel.h"
#include "Menu/Paktext/menu_formatnotetypelabel_symbols.h"
#include "include_asm.h"
#include "Common/Lone/g_languageindex.h"
#include "Menu/menu_action_text_tables.h"
#include "Menu/Pak/profile_preview_and_line_text.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/menu_createmenufromparameters.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Common/effectrender.h"
#endif
#include "Common/frontend_video_mode.h"
#include "Common/frontend_resource_load_state.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/Pak/profile.h"
#include "Menu/menu_event_handlers.h"
#endif

#if defined(VERSION_DE)
typedef struct { char pad0[0x14]; char **text; } RightAlignedNameLabelView;
/* Shows the eight-character name g_pakDisplayNameBytes in the field 0xC bytes into the text (right aligned, blank padded after trimming trailing blanks), or points the text at g_pakDefaultPreviewNameLabel when g_pakUseDefaultPreviewLabels is set; returns zero. */
s32 Menu_FormatRightAlignedName(RightAlignedNameLabelView *labelWidget) {
    u8 *last;
    char *dst;
    char *fill;
    s32 n;
    s32 i;
    s32 blank;
    n = 8;
    if (g_pakUseDefaultPreviewLabels != 0) {
        labelWidget->text = (char **)g_pakDefaultPreviewNameLabel;
    } else {
        last = g_pakDisplayNameLastByte;
        labelWidget->text = (char **)g_pakPreviewNameLabelBuffer;
        if (*last == 32) {
            last--;
            for (;;) {
                if (n != 0) {
                    n--;
                    if (*last-- == 32) {
                        continue;
                    }
                }
                break;
            }
        }
        dst = (char *)*labelWidget->text;
        dst += 0xC;
        blank = 32;
        fill = dst + 7;
        for (i = 7; i >= 0; i--) {
            *fill-- = blank;
        }
        dst = &dst[8 - n];
        for (i = 0; i < n; i++) {
            *dst++ = g_pakDisplayNameBytes[i];
        }
    }
    return 0;
}
#endif

/* g_pakPreviewNoteType is read through a struct view so the compiler keeps the load behind the preceding store. */
typedef struct { s8 value; } PakModeByte;

#if defined(VERSION_DE)
typedef struct { char pad0[0x14]; char **text; } NoteTypeLabelView;
/* Copies the 14-byte label chosen by g_pakPreviewNoteType (default g_pakNoteTypeDefaultLabel) into the label's text after its fixed prefix, or points the text at g_pakDefaultPreviewTypeLabel when g_pakUseDefaultPreviewLabels is set; returns zero. */
s32 Menu_FormatNoteTypeLabel(NoteTypeLabelView *labelWidget) {
    char *src;
    char *dst;
    s32 i;
    if (g_pakUseDefaultPreviewLabels != 0) {
        labelWidget->text = (char **)&g_pakDefaultPreviewTypeLabel;
    } else {
        labelWidget->text = (char **)g_pakPreviewTypeLabelBuffer;
        switch (((PakModeByte *)&g_pakPreviewNoteType)->value) {
        case 0:
        case 1:
        case 4:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        default:
            src = g_pakNoteTypeDefaultLabel;
            break;
        case 5:
            src = g_pakNoteTypeAdonLabel;
            break;
        case 3:
            src = g_pakNoteTypeFirebornLabel;
            break;
        case 2:
            src = g_pakNoteTypeCampaignerLabel;
            break;
        case 14:
            src = *(char **)g_pakNoteTypeTelsetLabelText;
            break;
        }
        dst = (char *)*labelWidget->text;
        dst += 6;
        for (i = 0; i < 14; i++) {
            *dst++ = *src++;
        }
    }
    return 0;
}
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
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
            src = g_pakStatusAdonTexts[g_languageIndex];
            break;
        case 3:
            src = g_pakStatusFirebornTexts[g_languageIndex];
            break;
        case 2:
            src = g_pakStatusCampaignerTexts[g_languageIndex];
            break;
        case 14:
            src = g_pakStatusTelsetTexts[g_languageIndex];
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

#if defined(VERSION_EU)
/* Points a field's text at the pak action label for the frontend resource load stage: stages 1 and 2
   use the alternate label, every other stage uses the default label. Returns zero. */
s32 Menu_SelectEuropeanPakActionLabel(struct PakActionLabelView *field) {
    u32 state = g_frontendResourceLoadStage;

    if (state >= 5) {
        goto state_other;
    }
    switch (state) {
        case 0: goto state_other;
        case 1: goto case_3;
        case 2: goto case_3;
        case 3: goto case_1;
        case 4: goto case_2;
        }
state_other:
    field->text = s_nodeDefaultFieldText;
    goto done;
case_1:
    field->text = s_nodeDefaultFieldText;
    goto done;
case_2:
    field->text = s_nodeDefaultFieldText;
    goto done;
case_3:
    field->text = s_nodeAlternateFieldText;
done:
    return 0;
}
#endif

#if defined(VERSION_EU)
const unsigned int k_widgetPackedHalfwords[1] = {
    0x00330034,
};
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
typedef struct { u8 pad0[0x14]; char **text; } PakRangeTextEu;

/* Pak size line: picks the 11-character text for the value range g_pakProfileRankScore falls in (the bands end at 0x32, 0x96, 0x12C, 0x1F4,
   0x320, 0x514, 0x7D0, 0xBB8, 0x1194, 0x1964, 0x270F) in the current language and copies it onto the entry's line. */
s32 Menu_FormatLocalizedPakSizeRange(PakRangeTextEu *entry) {
    u32 v = g_pakProfileRankScore;
    char *src = 0;
    char *dst;
    s32 i;

    if (v < 50) src = g_pakRankSizeTexts[0][g_languageIndex];
    else if (v - 50 < 100) src = g_pakRankSizeTexts[1][g_languageIndex];
    else if (v - 150 < 150) src = g_pakRankSizeTexts[2][g_languageIndex];
    else if (v - 300 < 200) src = g_pakRankSizeTexts[3][g_languageIndex];
    else if (v - 500 < 300) src = g_pakRankSizeTexts[4][g_languageIndex];
    else if (v - 800 < 500) src = g_pakRankSizeTexts[5][g_languageIndex];
    else if (v - 1300 < 700) src = g_pakRankSizeTexts[6][g_languageIndex];
    else if (v - 2000 < 1000) src = g_pakRankSizeTexts[7][g_languageIndex];
    else if (v - 3000 < 1500) src = g_pakRankSizeTexts[8][g_languageIndex];
    else if (v - 4500 < 2000) src = g_pakRankSizeTexts[9][g_languageIndex];
    else if (v - 6500 < 3499) src = g_pakRankSizeTexts[10][g_languageIndex];
    else if ((s32)v >= 9999) src = g_pakRankSizeTexts[11][g_languageIndex];
    dst = entry->text[g_languageIndex];
    dst += Menu_CountLineChars(entry) - 11;
    if (src != 0) {
        for (i = 0; i < 11; i++) {
            *dst++ = *src++;
        }
    }
    return 0;
}
#endif
