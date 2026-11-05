#ifndef DATA_WEAPON_CALLBACKS_WEAPON_FIRE_STATE_TABLE_H
#define DATA_WEAPON_CALLBACKS_WEAPON_FIRE_STATE_TABLE_H
#include "types.h"
#include "Actor/actor_updateactorstateanimation.h"

/* One candidate of an animation choice list: Gobjinst_ChooseAvailableAnimationKind walks pairs of
   (animation, weight) until the animation is -1 and picks one by weight. */
struct WeaponAnimationChoice {
    s16 animation;
    s16 weight;
};

/* One state of a weapon fire state table. Actor_RequestActorState searches the tables for id and calls enter
   (offset 4); Actor_UpdateActorStateAnimation reads animation, scale, threshold and flags (offsets 16 to 28)
   as StateEntry callback, scale, threshold and flags. animation is an animation id or the address of a
   WeaponAnimationChoice list; update (offset 8) holds the per-frame callback and offset 0xC is unused. */
struct WeaponStateEntry {
    s32 id;
    void *enter;
    void *update;
    void *reservedHandler;
    u32 animation;
    f32 scale;
    s32 threshold;
    u32 flags;
};

/* A state table: the next table to search when id is not found (the entries end with id -1), seven words that
   Actor_RequestActorState and the state walkers never read (zero in every table), then the entries. */
struct WeaponStateTable {
    struct WeaponStateTable *next;
    u32 reservedWords[7];
    struct WeaponStateEntry entries[1];
};

#define WEAPON_STATE_TABLE(count) \
    struct { struct WeaponStateTable *next; u32 reservedWords[7]; struct WeaponStateEntry entries[count]; }

/* Base state table of the weapon fire state machine: eight entries. */
typedef WEAPON_STATE_TABLE(8) WeaponFireStateCallbackTable;
extern WeaponFireStateCallbackTable g_weaponFireStateCallbackTable;
#endif
