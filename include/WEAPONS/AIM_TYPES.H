#ifndef WEAPONS_AIM_TYPES_H
#define WEAPONS_AIM_TYPES_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"

typedef union AimOutput { CVector3 xyz; CQuatern full; Shared_Quad words; } AimOutput;

typedef struct AimActor {
    u8 kind; char pad1[7]; CVector3 pos; char pad14[0x5c];
    f32 height; char pad74[0x8c]; s32 flags; char pad104[0x144]; CVector3 focus;
} AimActor;

typedef struct AimController { char pad0[0x7e]; u8 active; } AimController;

typedef struct AimView {
    char pad0[0x24]; s32 mode; char pad28[0x100]; CVector3 origin;
    char pad134[0x2c]; f32 matrix[16];
} AimView;

typedef struct AimWeapon { char pad0[14]; s16 idle; s16 locked; } AimWeapon;

typedef struct AimHit { AimActor *actor; char pad4[0xe0]; CVector3 point; CVector3 normal; } AimHit;

typedef struct AimPlayer {
    s8 kind; char pad1[7]; CVector3 worldPosition; char pad14[8];
    CVector3 position; /* 0x1C: effect spawn position */
    char pad28[0x10]; u32 movementFlags; /* 0x38 */
    char pad3C[0xC8]; f32 animationTimer; /* 0x104 */
    char pad108[6]; u8 firing; /* 0x10E */
    char pad10F[0x37D]; s8 weaponKind; /* 0x48C */
    char pad48D[0x107]; s32 weaponActionMode;
    char pad598[4]; s32 shots; /* 0x59C */
    char pad5A0[0x34]; s32 playerIndex; /* 0x5D4 */
    AimController *controller; AimView *view;
    s32 equippedKind; /* 0x5E0 */
    char pad5E4[0x10]; s16 ammo[7]; /* 0x5F4 */
    s8 weapons[22][2]; /* 0x602: active flag and state */
    s16 selectedWeapon; char pad630[0x20]; u16 state; /* 0x650 */
    char pad652[0x136]; s32 lockState;
    f32 lockTimer; char pad790[4]; AimActor *lockedTarget; s32 aimModelResource;
    CVector3 out; CVector3 velocity; AimActor *candidateTarget; s32 lockedAimModelResource; char pad7BC[4];
    CVector3 smooth; CVector3 smoothVelocity; CQuatern rotation; s32 alternateAimMode;
    char pad7EC[0x80]; s32 animation; /* 0x86C */
    char pad870[0x9A0]; s32 enabled;
    char pad1214[0x23C]; s32 controlled; /* 0x1450 */
    char pad1454[4]; CVector3 aim; CVector3 aim2; CVector3 normal; AimActor *target;
} AimPlayer;

#endif
