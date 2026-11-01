#include "include_asm.h"
#include "COMMON/MENURECAT20V1.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "../../../sdk/include/AUDIO/sprintf.H"
#if defined(VERSION_US_REV1)
s32 Pak_ToggleTextChoice(void) {
    g_modelEditorApplyToAllRecords ^= 1;
    return 0;
}
/* Points a field's text at g_modelEditorApplyToAllEnabledText when the option g_modelEditorApplyToAllRecords is set and at g_modelEditorApplyToAllDisabledText otherwise, and returns
   zero: the label an option menu shows for that option. */
extern char g_modelEditorApplyToAllEnabledText[];
extern char g_modelEditorApplyToAllDisabledText[];
s32 Pak_UpdateChoiceText(struct PakActionLabelView *field) {
    if (g_modelEditorApplyToAllRecords != 0) {
        field->text = g_modelEditorApplyToAllEnabledText;
    } else {
        field->text = g_modelEditorApplyToAllDisabledText;
    }
    return 0;
}
/* Keeps an option field and the remembered byte g_playerModelLighting[index] in step, giving a field still at -1 the remembered value and otherwise remembering the field low byte, then mirrors it into g_savedPlayerModelLighting[index] and formats it into the field text with s_menuByteOptionValueFormat three bytes before the length Menu_CountLineChars reports, returning zero. Adapted from Pak_SyncSecondaryByteOptionTwo with the fixed byte slots replaced by the tables g_playerModelLighting and g_savedPlayerModelLighting indexed by the second argument. */
extern u8 g_playerModelLighting[];
extern u8 g_savedPlayerModelLighting[];
extern char s_menuByteOptionValueFormat[];
extern s32 Menu_CountLineChars(struct Field *);
s32 Pak_SyncPrimaryByteOption(struct Field *field, s32 index) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_playerModelLighting[index];
    } else {
        g_playerModelLighting[index] = ((u8 *) &field->value)[3];
    }
    g_savedPlayerModelLighting[index] = g_playerModelLighting[index];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_playerModelLighting[0] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedPlayerModelLighting[0] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncPrimaryByteOptionZero(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_playerModelLighting[0];
    } else {
        g_playerModelLighting[0] = ((u8 *) &field->value)[3];
    }
    g_savedPlayerModelLighting[0] = g_playerModelLighting[0];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_playerModelLighting[1] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedPlayerModelLighting[1] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncPrimaryByteOptionOne(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_playerModelLighting[1];
    } else {
        g_playerModelLighting[1] = ((u8 *) &field->value)[3];
    }
    g_savedPlayerModelLighting[1] = g_playerModelLighting[1];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_playerModelLighting[2] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedPlayerModelLighting[2] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncPrimaryByteOptionTwo(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_playerModelLighting[2];
    } else {
        g_playerModelLighting[2] = ((u8 *) &field->value)[3];
    }
    g_savedPlayerModelLighting[2] = g_playerModelLighting[2];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_secondaryMenuByteOptions[index] in step, giving a field still at -1 the remembered value and otherwise remembering the field low byte, then mirrors it into g_savedSecondaryMenuByteOptions[index] and formats it into the field text with s_menuByteOptionValueFormat three bytes before the length Menu_CountLineChars reports, returning zero. Adapted from Pak_SyncSecondaryByteOptionTwo with the fixed byte slots replaced by the tables g_secondaryMenuByteOptions and g_savedSecondaryMenuByteOptions indexed by the second argument. */
extern u8 g_secondaryMenuByteOptions[];
extern u8 g_savedSecondaryMenuByteOptions[];
s32 Pak_SyncSecondaryByteOption(struct Field *field, s32 index) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_secondaryMenuByteOptions[index];
    } else {
        g_secondaryMenuByteOptions[index] = ((u8 *) &field->value)[3];
    }
    g_savedSecondaryMenuByteOptions[index] = g_secondaryMenuByteOptions[index];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_secondaryMenuByteOptions[0] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedSecondaryMenuByteOptions[0] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncSecondaryByteOptionZero(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_secondaryMenuByteOptions[0];
    } else {
        g_secondaryMenuByteOptions[0] = ((u8 *) &field->value)[3];
    }
    g_savedSecondaryMenuByteOptions[0] = g_secondaryMenuByteOptions[0];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_secondaryMenuByteOptions[1] in step: a field still at -1 takes the
   remembered value, otherwise the field's low byte is remembered; the value is mirrored into
   g_savedSecondaryMenuByteOptions[1] and formatted into the field's text with s_menuByteOptionValueFormat, three bytes before the length
   Menu_CountLineChars reports. Returns zero. */
s32 Pak_SyncSecondaryByteOptionOne(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_secondaryMenuByteOptions[1];
    } else {
        g_secondaryMenuByteOptions[1] = ((u8 *) &field->value)[3];
    }
    g_savedSecondaryMenuByteOptions[1] = g_secondaryMenuByteOptions[1];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
/* Keeps an option field and the remembered byte g_secondaryMenuByteOptionTwo[0] in step, giving a field still at -1 the remembered value and otherwise remembering the field's low byte, then mirrors it into g_savedSecondaryMenuByteOptionTwo[0] and formats it into the field's text with s_menuByteOptionValueFormat three bytes before the length Menu_CountLineChars reports, returning zero. Adapted from Pak_SyncPrimaryByteOptionZero. */
extern u8 g_secondaryMenuByteOptionTwo[];
extern u8 g_savedSecondaryMenuByteOptionTwo[];
s32 Pak_SyncSecondaryByteOptionTwo(struct Field *field) {
    char *text = *field->text;

    if (field->value == -1) {
        field->value = g_secondaryMenuByteOptionTwo[0];
    } else {
        g_secondaryMenuByteOptionTwo[0] = ((u8 *) &field->value)[3];
    }
    g_savedSecondaryMenuByteOptionTwo[0] = g_secondaryMenuByteOptionTwo[0];
    Libc_FormatString(text + (Menu_CountLineChars(field) - 3), s_menuByteOptionValueFormat, field->value);
    return 0;
}
#endif
