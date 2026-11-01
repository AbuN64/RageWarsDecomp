#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#if defined(VERSION_EU)
/* 8043EA40.CPP */
extern u8 g_europeanMenuToggleRow2;
extern u8 g_europeanMenuToggleRow3;
extern u8 g_europeanMenuToggleRow4;
extern u8 g_europeanMenuToggleRow5;
extern u8 g_europeanMenuToggleRow6;
extern u8 g_europeanMenuToggleRow7;
extern u8 g_europeanMenuToggleRow8;
extern u8 g_europeanMenuToggleRow9;
extern char *g_europeanMenuToggleRow2EnabledText[];
extern char *g_europeanMenuToggleRow2DisabledText[];
extern char *g_europeanMenuToggleRow3EnabledText[];
extern char *g_europeanMenuToggleRow3DisabledText[];
extern char *g_europeanMenuToggleRow4EnabledText[];
extern char *g_europeanMenuToggleRow4DisabledText[];
extern char *g_europeanMenuToggleRow5EnabledText[];
extern char *g_europeanMenuToggleRow5DisabledText[];
extern char *g_europeanMenuToggleRow6EnabledText[];
extern char *g_europeanMenuToggleRow6DisabledText[];
extern char *g_europeanMenuToggleRow7EnabledText[];
extern char *g_europeanMenuToggleRow7DisabledText[];
extern char *g_europeanMenuToggleRow8EnabledText[];
extern char *g_europeanMenuToggleRow8DisabledText[];
extern char *g_europeanMenuToggleRow9EnabledText[];
extern char *g_europeanMenuToggleRow9DisabledText[];
/* Picks the label for each of the eight option rows (ids 2..9): the first text when the row's flag is set, else the second. */
typedef struct { s32 id; u8 pad4[0x10]; char ***text; } OptionRowEu;
s32 Items_SelectOptionRowLabel(OptionRowEu *row) {
    switch (row->id) {
    default:
    case 2:
        if (g_europeanMenuToggleRow2) {
            row->text = g_europeanMenuToggleRow2EnabledText;
        } else {
            row->text = g_europeanMenuToggleRow2DisabledText;
        }
        break;
    case 3:
        if (g_europeanMenuToggleRow3) {
            row->text = g_europeanMenuToggleRow3EnabledText;
        } else {
            row->text = g_europeanMenuToggleRow3DisabledText;
        }
        break;
    case 4:
        if (g_europeanMenuToggleRow4) {
            row->text = g_europeanMenuToggleRow4EnabledText;
        } else {
            row->text = g_europeanMenuToggleRow4DisabledText;
        }
        break;
    case 5:
        if (g_europeanMenuToggleRow5) {
            row->text = g_europeanMenuToggleRow5EnabledText;
        } else {
            row->text = g_europeanMenuToggleRow5DisabledText;
        }
        break;
    case 6:
        if (g_europeanMenuToggleRow6) {
            row->text = g_europeanMenuToggleRow6EnabledText;
        } else {
            row->text = g_europeanMenuToggleRow6DisabledText;
        }
        break;
    case 7:
        if (g_europeanMenuToggleRow7) {
            row->text = g_europeanMenuToggleRow7EnabledText;
        } else {
            row->text = g_europeanMenuToggleRow7DisabledText;
        }
        break;
    case 8:
        if (g_europeanMenuToggleRow8) {
            row->text = g_europeanMenuToggleRow8EnabledText;
        } else {
            row->text = g_europeanMenuToggleRow8DisabledText;
        }
        break;
    case 9:
        if (g_europeanMenuToggleRow9) {
            row->text = g_europeanMenuToggleRow9EnabledText;
        } else {
            row->text = g_europeanMenuToggleRow9DisabledText;
        }
        break;
    }
    return 0;
}
#endif
#if defined(VERSION_EU_X)
#include "TYPES.H"
#endif
