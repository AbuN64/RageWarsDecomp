#include "TYPES.H"

#if defined(VERSION_DE)
extern s32 g_pakUseDefaultPreviewLabels;
extern char g_pakDefaultPreviewNameLabel[];
extern char g_pakPreviewNameLabelBuffer[];
extern u8 g_pakDisplayNameLastByte[];
extern u8 g_pakDisplayNameBytes[];
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

#if defined(VERSION_DE)
extern char g_pakDefaultPreviewTypeLabel[];
extern char g_pakPreviewTypeLabelBuffer[];
extern char *g_pakNoteTypeDefaultLabel, *g_pakNoteTypeFiveLabel, *g_pakNoteTypeThreeLabel, *g_pakNoteTypeTwoLabel, *g_pakNoteTypeFourteenLabel;
extern s8 g_pakPreviewNoteType[];
typedef struct { char pad0[0x14]; char **text; } NoteTypeLabelView;
/* Copies the 14-byte label chosen by g_pakPreviewNoteType (default g_pakNoteTypeDefaultLabel) into the text 6 bytes in, or points the text at g_pakDefaultPreviewTypeLabel when g_pakUseDefaultPreviewLabels is set; returns zero. */
s32 Menu_FormatNoteTypeLabel(NoteTypeLabelView *labelWidget) {
    char *src;
    char *dst;
    s32 i;
    if (g_pakUseDefaultPreviewLabels != 0) {
        labelWidget->text = (char **)g_pakDefaultPreviewTypeLabel;
    } else {
        labelWidget->text = (char **)g_pakPreviewTypeLabelBuffer;
        switch (g_pakPreviewNoteType[0]) {
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
            src = g_pakNoteTypeFiveLabel;
            break;
        case 3:
            src = g_pakNoteTypeThreeLabel;
            break;
        case 2:
            src = g_pakNoteTypeTwoLabel;
            break;
        case 14:
            src = g_pakNoteTypeFourteenLabel;
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
