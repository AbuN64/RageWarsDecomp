#ifndef GFX_PLAYER_UPDATEFRAGTAGSELECTION_DATA_H
#define GFX_PLAYER_UPDATEFRAGTAGSELECTION_DATA_H
#include "types.h"
#include "Common/mtx.h"
#include "Common/runtime_declarations.h"
struct Player1680 {
    char pad0[0x5DC];
    struct GameplayCamera *mount;
    char pad5E0[0x1640 - 0x5E0];
    CMatrix4 views[1];
};
#endif
