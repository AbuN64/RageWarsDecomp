#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#if defined(VERSION_EU_X)
#include "TYPES.H"
extern char *g_menuToggleRow2EnabledText;
extern char *g_menuToggleRow2DisabledText;
extern char *g_menuToggleRow3EnabledText;
extern char *g_menuToggleRow3DisabledText;
extern char *g_menuToggleRow4EnabledText;
extern char *g_menuToggleRow4DisabledText;
extern char *g_menuToggleRow5EnabledText;
extern char *g_menuToggleRow5DisabledText;
extern char *g_menuToggleRow6EnabledText;
extern char *g_menuToggleRow6DisabledText;
extern char *g_menuToggleRow7EnabledText;
extern char *g_menuToggleRow7DisabledText;
extern char *g_menuToggleRow8EnabledText;
extern char *g_menuToggleRow8DisabledText;
extern char *g_menuToggleRow9EnabledText;
extern char *g_menuToggleRow9DisabledText;
/* Picks the label of option row 2..9 from its on/off flag (the eu-x twin of Items_SelectOptionRowLabel, without the language table). */
typedef struct { s32 id; u8 pad4[0x10]; char **text; } OptionRowEux;
s32 Menu_UpdateOptionToggleLabel(OptionRowEux *row) {
    switch (row->id) {
    case 2:
    default:
        if (g_gameSettings.menuToggles[0] != 0) {
            row->text = &g_menuToggleRow2EnabledText;
        } else {
            row->text = &g_menuToggleRow2DisabledText;
        }
        break;
    case 3:
        if (g_gameSettings.menuToggles[1] != 0) {
            row->text = &g_menuToggleRow3EnabledText;
        } else {
            row->text = &g_menuToggleRow3DisabledText;
        }
        break;
    case 4:
        if (g_gameSettings.menuToggles[2] != 0) {
            row->text = &g_menuToggleRow4EnabledText;
        } else {
            row->text = &g_menuToggleRow4DisabledText;
        }
        break;
    case 5:
        if (g_gameSettings.menuToggles[3] != 0) {
            row->text = &g_menuToggleRow5EnabledText;
        } else {
            row->text = &g_menuToggleRow5DisabledText;
        }
        break;
    case 6:
        if (g_gameSettings.menuToggles[4] != 0) {
            row->text = &g_menuToggleRow6EnabledText;
        } else {
            row->text = &g_menuToggleRow6DisabledText;
        }
        break;
    case 7:
        if (g_gameSettings.menuToggles[5] != 0) {
            row->text = &g_menuToggleRow7EnabledText;
        } else {
            row->text = &g_menuToggleRow7DisabledText;
        }
        break;
    case 8:
        if (g_gameSettings.menuToggles[6] != 0) {
            row->text = &g_menuToggleRow8EnabledText;
        } else {
            row->text = &g_menuToggleRow8DisabledText;
        }
        break;
    case 9:
        if (g_gameSettings.menuToggles[8] != 0) {
            row->text = &g_menuToggleRow9EnabledText;
        } else {
            row->text = &g_menuToggleRow9DisabledText;
        }
        break;
    }
    return 0;
}
#endif
