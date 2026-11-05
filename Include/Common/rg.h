#ifndef COMMON_RG_H
#define COMMON_RG_H
#include "types.h"
struct MenuOptionLabel;
struct MenuOptionLabel {
    s8 pad0[8];
    s32 flags;
    s8 padC[8];
    s32 *text;
};


extern char *g_menuToggleChargeDartRifleEnabledText;
extern char *g_menuToggleChargeDartRifleDisabledText;
extern char *g_menuToggleFirestormEnabledText;
extern char *g_menuToggleFirestormDisabledText;
extern char *g_menuToggleAssaultRifleEnabledText;
extern char *g_menuToggleAssaultRifleDisabledText;
extern char *g_menuTogglePlasmaRifleEnabledText;
extern char *g_menuTogglePlasmaRifleDisabledText;
extern char *g_menuToggleCerebralBoreEnabledText;
extern char *g_menuToggleCerebralBoreDisabledText;
extern char *g_menuToggleGrenadeLauncherEnabledText;
extern char *g_menuToggleGrenadeLauncherDisabledText;
extern char *g_menuToggleScorpionLauncherEnabledText;
extern char *g_menuToggleScorpionLauncherDisabledText;
extern char *g_menuToggleTorpedoLauncherEnabledText;
extern char *g_menuToggleTorpedoLauncherDisabledText;
#endif
