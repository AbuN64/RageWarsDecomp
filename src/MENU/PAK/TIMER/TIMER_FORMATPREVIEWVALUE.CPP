#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "TYPES.H"
#include "COMMON/MENURECAT20V1.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RECORDRECATCV1.H"
#include "ENGINE/DEFS.H"
#include "MENU/PAK/TIMER.H"

/* Formats the halfword at offset 0x22 of the structure g_controllerPakSnapshotPayload points to into a field's text
   (the current menu language's text in the EU builds) with the format string, two bytes before
   the length Menu_CountLineChars reports, and returns zero. */

struct PreviewTextValue { char pad[0x22]; s16 value; };

extern struct PreviewTextValue *g_controllerPakSnapshotPayload;
extern s32 Menu_CountLineChars(struct Field *);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define PREVIEW_VALUE_FORMAT g_pakFormatInt2
#else
#define PREVIEW_VALUE_FORMAT g_pakFormatInt2_TimerFormatpreviewvalue
#endif

s32 Timer_FormatPreviewValue(struct Field *field) {
    s32 value = g_controllerPakSnapshotPayload->value;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    char *text = field->text[g_languageIndex];
#else
    char *text = *field->text;
#endif

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), PREVIEW_VALUE_FORMAT, value);
    return 0;
}
