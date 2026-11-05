#ifndef ACHIEVE_ACHIEVE_MATCH_SETUP_H
#define ACHIEVE_ACHIEVE_MATCH_SETUP_H
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
#include "Common/characterselectionroot.h"
#include "Common/weapon_unlock_presets.h"
struct MatchMenuApplySlotValueGfx {
    char pad00[0xD];
    unsigned char mode;
    char pad0E[0x16];
    s8 matchQualifierFirst;
    s8 matchQualifierSecond;
    char pad26[0xAA];
    RosterSlot slots[8];
};
struct PlayerLoadoutSelectionView {
    char pad[0x5D8];
    struct PlayerLoadoutInfo *info;
    char pad5DC[0x26];
    struct {
        unsigned char flag;
        unsigned char value;
    } options[22];
};
#include "Weapons/player_inventory.h"
extern s32 Achieve_MatchQualifies(void);
struct PlayerLoadoutSelectionView;
void Achieve_ApplyPlayerOptionOverrides(struct PlayerLoadoutSelectionView *p);
struct WeaponPlayer;
void Achieve_EnableLevelWeapons(struct WeaponPlayer *player);
#endif
