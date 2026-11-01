#ifndef COMMON_GAMEPLAY_MOVEMENT_H
#define COMMON_GAMEPLAY_MOVEMENT_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
/* Shared records retained from origin/legacy include/shared and Player_UpdateBodyMovementAndActions_GameplayMovement.c. */

typedef struct Shared_Model Shared_Model;
struct Shared_Model {
    u16 reservedWord; /* +0x0: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    u16 flags; /* +0x2: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};


#include "COMMON/LEVEL_PLACEMENT.H"


#include "COMMON/SHARED_SCRATCH.H"


typedef struct Shared_StateInfo Shared_StateInfo;
struct Shared_StateInfo {
    s32 reservedWord; /* +0x0: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    void (*update)(void *, void *); /* +0x4: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s32 * flags; /* +0x8: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s32 pad0C[3]; /* +0xC: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};


typedef struct Shared_Surface Shared_Surface;
struct Shared_Surface {
    char pad0[0x28];
    f32 timer; /* +0x28: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    char pad2C[0x18];
    s32 flags; /* +0x44: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    char pad48[0x4];
    u16 item; /* +0x4C: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    u16 pad4E; /* +0x4E: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    u16 sound; /* +0x50: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    u16 flags52; /* 0x52 */
};


typedef struct Shared_PickupDef Shared_PickupDef;
struct Shared_PickupDef {
    s32 pad0; /* +0x0: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s32 flags; /* +0x4: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    char pad8[0x10];
    f32 radius; /* +0x18: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s32 pad1C; /* +0x1C: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s32 item; /* +0x20: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};


typedef struct Shared_Pickup Shared_Pickup;
struct Shared_Pickup {
    char pad0[0x8];
    CVector3 pos; /* +0x8: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s32 pad14; /* +0x14: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    struct Shared_PickupDef * def; /* +0x18: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};


typedef struct Shared_CharInfo Shared_CharInfo;
struct Shared_CharInfo {
    s32 pad0; /* +0x0: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    u16 sound; /* +0x4: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s16 pad6; /* +0x6: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s16 ammo; /* +0x8: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    s16 padA; /* +0xA: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    union {
        struct {
            s16 next_s; /* +0xC: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
        } viewC_0;
        struct {
            u16 next_u; /* +0xC: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
        } viewC_1;
    } viewsC;
    char padE[0x2];
};


typedef struct Shared_Floor Shared_Floor;
struct Shared_Floor {
    char pad0[0xE8];
    f32 y; /* +0xE8: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};


typedef struct Shared_Profile Shared_Profile;
struct Shared_Profile {
    char pad0[0x81];
    u8 team; /* +0x81: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    u8 controllerFlag; /* 0x82 */
    u8 quantity; /* 0x83: menu player quantity */
    char pad84[0xB];
    u8 remote; /* +0x8F: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    char pad90[0x4];
    u8 counts; /* +0x94: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};


typedef struct Shared_Hud Shared_Hud;
struct Shared_Hud {
    char pad0[0x120];
    s32 score; /* +0x120: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    u16 pad124; /* +0x124: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
    u16 bonus; /* +0x126: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};


typedef struct Shared_Shadow Shared_Shadow;
struct Shared_Shadow {
    char pad0[0x8];
    CVector3 pos; /* +0x8: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};


typedef struct Shared_Voice Shared_Voice;
struct Shared_Voice {
    char pad0[0x10];
    s32 bank; /* +0x10: src/Player_UpdateBodyMovementAndActions_GameplayMovement.c */
};




/* The per-character stride sound halfword has distinct auto symbols in each ROM. */
#if defined(VERSION_DE)
extern s16 g_strideSoundHalfwords_de[];
#elif defined(VERSION_EU)
extern s16 g_strideSoundHalfwords_eu[];
#elif defined(VERSION_EU_X)
extern s16 g_strideSoundHalfwords_eu_x[];
#elif defined(VERSION_US)
extern s16 g_strideSoundHalfwords_us[];
#else
extern s16 g_strideSoundHalfwords_us_rev1[];
#endif
static inline s32 strideSound(s32 index) {
#if defined(VERSION_DE)
    return (s16)((s32 *)((char *)g_strideSoundHalfwords_de - 2))[index];
#elif defined(VERSION_EU)
    return (s16)((s32 *)((char *)g_strideSoundHalfwords_eu - 2))[index];
#elif defined(VERSION_EU_X)
    return (s16)((s32 *)((char *)g_strideSoundHalfwords_eu_x - 2))[index];
#elif defined(VERSION_US)
    return (s16)((s32 *)((char *)g_strideSoundHalfwords_us - 2))[index];
#else
    return (s16)((s32 *)((char *)g_strideSoundHalfwords_us_rev1 - 2))[index];
#endif
}

#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#endif
