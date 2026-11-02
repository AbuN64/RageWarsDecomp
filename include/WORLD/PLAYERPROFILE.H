#ifndef WORLD_PLAYERPROFILE_H
#define WORLD_PLAYERPROFILE_H
#include "COMMON/RESOURCELOADSTATE.H"
#include "WORLD/PLAYERAI_RESPAWNFRAGTAGPLAYER.H"
extern unsigned char Player_GetProfileValue16(struct Profile *object);
extern unsigned char Player_GetProfileValue14(struct Profile *player);
extern unsigned int Player_GetProfileProgress(struct Profile *object);
extern unsigned char Player_GetProfileValue15(struct Profile *player);
#endif
