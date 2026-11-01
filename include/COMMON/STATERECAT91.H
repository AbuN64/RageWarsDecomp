#ifndef COMMON_STATERECAT91_H
#define COMMON_STATERECAT91_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
struct WeaponUnlockProfileView;
struct WeaponUnlockProfileView {
    char p[120];
    u8 present;
    char p2[6];
    s8 profileIndex;
    char p3[17];
    u8 locked;
};

struct PresetRow;
typedef struct PresetRow PresetRow;

struct Preset;
struct Preset {
    u8 bytes[42];
};

struct Preset;
typedef struct Preset Preset;

struct PresetRow;
struct PresetRow {
    Preset presets[20];
};

struct PresetTable;

struct WeaponUnlockPlayerView;
struct WeaponUnlockProfileView;



struct PresetTable;
typedef struct PresetTable PresetTable;

struct WeaponUnlockProfileView;
typedef struct WeaponUnlockProfileView WeaponUnlockProfileView;

struct PlayerLoadoutInfo;
struct PlayerLoadoutInfo {
    char pad[0x4C];
    unsigned char enabled[22];
    unsigned char values[22];
    unsigned char present;
    char pad79[0x18];
    unsigned char locked;
};
struct PlayerLoadoutInfo;
struct PlayerLoadoutSelectionView;

struct WeaponUnlockPlayerView;
typedef struct WeaponUnlockPlayerView WeaponUnlockPlayerView;

struct PlayerLoadoutSelectionView;
typedef struct PlayerLoadoutSelectionView PlayerLoadoutSelectionView;


#include "WEAPONS/PLAYER_INVENTORY.H"
#endif
