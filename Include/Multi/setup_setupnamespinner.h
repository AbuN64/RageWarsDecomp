#ifndef MULTI_SETUP_SETUPNAMESPINNER_H
#define MULTI_SETUP_SETUPNAMESPINNER_H
#include "Common/pak_enter_player_options.h"
#include "Common/aiprofile.h"
struct NameSlotModel;
struct NameSpinnerEntry;
struct NameSpinnerMenu;
struct Player;
/* Name-slot model a spinner menu points at: four 0x28-byte part records from +0x30, each with
   display flags at +0 (0x1800000 marks the highlighted slot). */
typedef struct NameSlotPart {
    u32 flags;
    char pad4[0x24];
} NameSlotPart;
typedef struct NameSlotModel {
    char pad0[0x30];
    NameSlotPart part[4];
} NameSlotModel;
struct NameSpinnerMenu {
    s16 state;
    char pad2[0xA];
    struct NameSlotModel *model;
    char pad10[0xC];
    s32 id;
    s32 input;
};
struct PlayerOptionsEntry {
    s16 state;
    char pad2[0xA];
    struct ActorPakEnterPlayerOptions *actor;
};
struct StyleMultiDrawNameCursor {
    char pad0[0x1C];
    s32 id;
    char pad20[0x10];
    f32 alpha;
    f32 fade;
};
struct NameSpinnerEntry {
    s32 value;
    f32 timer;
    s32 count;
    u8 text[12];
};
struct NameEditMenuContext {
    char pad[0x1C];
    struct Player *profileOwner;
};
/* The eight name entry states: cursor position, blink timer, character count and the text being typed. */
extern struct NameSpinnerEntry g_multiplayerNameEntryStates[8];
extern void Setup_SetupNameSpinner(struct NameSpinnerMenu *menu);
#endif
