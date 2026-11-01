#ifndef WEAPONS_PLAYER_INVENTORY_H
#define WEAPONS_PLAYER_INVENTORY_H
#include "TYPES.H"
typedef struct WeaponStatus {
    u8 pad[0x78];
    u8 active;
    u8 pad79[0x8F - 0x79];
    u8 flag8F;
    u8 pad90;
    u8 out;
} WeaponStatus;
typedef struct WeaponPlayer {
    u8 pad0[0x5D8];
    WeaponStatus *status;
    u8 pad5DC[0x5F6 - 0x5DC];
    s16 ammo;
    u8 pad5F8[0x602 - 0x5F8];
    u8 weapons[22][2];
    s16 mode;
    u8 pad630[0x6AC - 0x630];
    s32 flags6AC;
    u8 pad6B0[0x788 - 0x6B0];
    s32 state788;
    u8 pad78C[0x11B4 - 0x78C];
    s32 busy;
    u8 pad11B8[0x11D8 - 0x11B8];
    f32 recoil;
} WeaponPlayer;
#endif
