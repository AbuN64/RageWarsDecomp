#ifndef COMMON_RG_H
#define COMMON_RG_H
#include "TYPES.H"
struct MenuOptionLabel;
struct MenuOptionLabel {
    s8 pad0[8];
    s32 flags;
    s8 padC[8];
    s32 *text;
};


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
#endif
