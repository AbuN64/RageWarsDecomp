#ifndef GFX_PLAYER_UPDATEFRAGTAGSELECTION_DATA_H
#define GFX_PLAYER_UPDATEFRAGTAGSELECTION_DATA_H
#include "TYPES.H"
#include "COMMON/MTX.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
struct Player1680 {
    char pad0[0x5DC];
    PlayerEyePositionView *mount;
    char pad5E0[0x1640 - 0x5E0];
    CMatrix4 views[1];
};
#endif
