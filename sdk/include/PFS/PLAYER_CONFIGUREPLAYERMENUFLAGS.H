#ifndef PFS_PLAYER_CONFIGUREPLAYERMENUFLAGS_H
#define PFS_PLAYER_CONFIGUREPLAYERMENUFLAGS_H
#include "Common/respawn_menu_actor.h"
extern void Player_MenuFlagsNoOp(void);
extern void Player_ConfigurePlayerMenuFlags(PlayerMenuFlagContext *object);
extern void Player_SetFragTagItemFlag(struct MenuPromptKindView *record);
#endif
