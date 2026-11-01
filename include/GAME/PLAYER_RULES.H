#ifndef GAME_PLAYER_RULES_H
#define GAME_PLAYER_RULES_H
#include "TYPES.H"
typedef struct Rules Rules;
struct Rules {
    char pad0[0x24];
    s32 teams;
    char pad28[0x78 - 0x28];
    s32 teamRule;
};
#endif
