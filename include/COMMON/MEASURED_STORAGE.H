#ifndef COMMON_MEASURED_STORAGE_H
#define COMMON_MEASURED_STORAGE_H
#include "TYPES.H"

/* Shared storage-access views. Each describes one measured field, not an object stride. */
struct ItemValueBindingView { unsigned char padding[20]; void * value; };
struct RegionFreeBlockSizeView { unsigned char padding[20]; s32 value; };
struct WorldResourceKeyView { unsigned char padding[12]; s32 value; };
struct RegionAllocatedBlockSizeView { unsigned char padding[16]; s32 value; };
struct WorldResourceHandleView { unsigned char padding[20]; void * * value; };
struct PlayerWeaponClassView { unsigned char padding[1582]; s16 value; };
struct WeaponActorStateView { unsigned char padding[472]; void * value; };
struct PlayerHeldWeaponView { unsigned char padding[1688]; void * value; };
struct WeaponSpinRateView { unsigned char padding[360]; f32 value; };
struct WeaponAttackPhaseView { unsigned char padding[316]; s32 value; };
struct CollisionPlaneEnabledView { unsigned char padding[8]; s32 value; };
struct CollisionPlaneNormalXView { unsigned char padding[72]; f32 value; };
struct CollisionPlaneNormalZView { unsigned char padding[80]; f32 value; };
#endif
