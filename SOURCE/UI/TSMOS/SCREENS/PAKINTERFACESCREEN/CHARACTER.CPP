#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/RG.H"
#if defined(VERSION_DE)
typedef struct { char pad0[0x80]; s8 choice; } CharacterPreviewChoiceView;
typedef struct { char pad0[0x5D8]; CharacterPreviewChoiceView *slot; s32 pad5DC; s32 style; } CharacterPreviewPlayerView;
typedef struct { char pad0[0x1C]; CharacterPreviewPlayerView *rec; struct ControllerProfile *player; } CharacterPreviewMenuContext;
#endif
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_US)
s32 Items_SelectToggleRowTextGerman(TextBoundsText *textRow) {
    s32 toggleRow;

    toggleRow = textRow->value;
    switch (toggleRow) {
    case 2:
    default:
        if (g_gameSettings.menuToggles[0] != 0) {
            textRow->text = &g_menuToggleRow2EnabledText;
        } else {
            textRow->text = &g_menuToggleRow2DisabledText;
        }
        break;
    case 3:
        if (g_gameSettings.menuToggles[1] != 0) {
            textRow->text = &g_menuToggleRow3EnabledText;
        } else {
            textRow->text = &g_menuToggleRow3DisabledText;
        }
        break;
    case 4:
        if (g_gameSettings.menuToggles[2] != 0) {
            textRow->text = &g_menuToggleRow4EnabledText;
        } else {
            textRow->text = &g_menuToggleRow4DisabledText;
        }
        break;
    case 5:
        if (g_gameSettings.menuToggles[3] != 0) {
            textRow->text = &g_menuToggleRow5EnabledText;
        } else {
            textRow->text = &g_menuToggleRow5DisabledText;
        }
        break;
    case 6:
        if (g_gameSettings.menuToggles[4] != 0) {
            textRow->text = &g_menuToggleRow6EnabledText;
        } else {
            textRow->text = &g_menuToggleRow6DisabledText;
        }
        break;
    case 7:
        if (g_gameSettings.menuToggles[5] != 0) {
            textRow->text = &g_menuToggleRow7EnabledText;
        } else {
            textRow->text = &g_menuToggleRow7DisabledText;
        }
        break;
    case 8:
        if (g_gameSettings.menuToggles[6] != 0) {
            textRow->text = &g_menuToggleRow8EnabledText;
        } else {
            textRow->text = &g_menuToggleRow8DisabledText;
        }
        break;
    case 9:
        if (g_gameSettings.menuToggles[8] != 0) {
            textRow->text = &g_menuToggleRow9EnabledText;
        } else {
            textRow->text = &g_menuToggleRow9DisabledText;
        }
        break;
    }
    return 0;
}
#endif
#endif
