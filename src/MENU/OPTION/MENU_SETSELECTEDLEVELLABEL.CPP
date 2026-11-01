#include "COMMON/CHEATCODE.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"

extern s32 g_gameSettings[];

extern s32 g_selectedLevel0Label;

extern s32 g_selectedLevel1Label;

extern s32 g_selectedLevel2Label;

extern s32 g_selectedLevel3Label;

extern s32 g_selectedLevel4Label;

extern s32 g_selectedLevel5Label;

extern s32 g_selectedLevel7Label;

extern s32 g_selectedLevel6Label;

extern s32 g_selectedLevel8Label;

extern s32 g_selectedLevel9Label;

extern s32 g_selectedLevel10Label;

extern char *g_unlockedLevelResultLabel[];

/* Toggles the bits optionMask names in the settings flag word g_gameSettings and returns 0. */
s32 Menu_ToggleGameOptionBits(s32 unused0, s32 optionMask) {
    s32 *flags = g_gameSettings;

    *flags ^= optionMask;
    return 0;
}

s32 Menu_SetSelectedLevelLabel(SelectedLevelLabelItem *label) {
    switch (g_encodedSelectedLevelIndex) {
    default:
        label->value = &g_unlockedLevelResultLabel;
        break;
    case 0:
        label->value = &g_selectedLevel0Label;
        break;
    case 1:
        label->value = &g_selectedLevel1Label;
        break;
    case 2:
        label->value = &g_selectedLevel2Label;
        break;
    case 3:
        label->value = &g_selectedLevel3Label;
        break;
    case 4:
        label->value = &g_selectedLevel4Label;
        break;
    case 5:
        label->value = &g_selectedLevel5Label;
        break;
    case 6:
        label->value = &g_selectedLevel6Label;
        break;
    case 7:
        label->value = &g_selectedLevel7Label;
        break;
    case 8:
        label->value = &g_selectedLevel8Label;
        break;
    case 9:
        label->value = &g_selectedLevel9Label;
        break;
    case 10:
        label->value = &g_selectedLevel10Label;
        break;
    }
    return 0;
}
