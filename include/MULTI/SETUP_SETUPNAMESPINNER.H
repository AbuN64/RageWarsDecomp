#ifndef MULTI_SETUP_SETUPNAMESPINNER_H
#define MULTI_SETUP_SETUPNAMESPINNER_H
#include "COMMON/MENURECAT20V1.H"
#include "COMMON/AIPROFILE.H"
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
    NameSlotModel *model;
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
    PlayerNameProfileView *profileOwner;
};
struct Spinner {
    s32 value;
    f32 timer;
    s32 max;
    char name[12];
};
struct PlayerNameTextEntry {
    s32 length;
    s32 cursor;
    s32 count;
    char text[12];
};
extern void Setup_SetupNameSpinner(NameSpinnerMenu *menu);
#endif
