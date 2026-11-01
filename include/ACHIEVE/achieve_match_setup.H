#ifndef ACHIEVE_ACHIEVE_MATCH_SETUP_H
#define ACHIEVE_ACHIEVE_MATCH_SETUP_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/STATERECAT91.H"
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
#include "WEAPONS/PLAYER_INVENTORY.H"
extern s32 Achieve_MatchQualifies(void);
#endif
