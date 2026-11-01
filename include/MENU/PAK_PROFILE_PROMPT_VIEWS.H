#ifndef MENU_PAK_PROFILE_PROMPT_VIEWS_H
#define MENU_PAK_PROFILE_PROMPT_VIEWS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
struct PakPromptContext {
    char pad0[0x1C];
    struct PlayerMessageMenuView *player;
    PakMenuSlot *slot;
    char *prompt;
};
struct PakNoteBrowserContext {
    char pad0[0x1C];
    SharedPlayer *player;
    PakMenuSlot *slot;
};
struct PlayerPakTimerView {
    unsigned char padding_0[1548];
    s32 trailerValue;
};
struct PakNoteTextEntry {
    s32 id;
    char pad4[0x10];
    u8 **text;
};
struct MenuPakBeginProfileLoad {
    s16 state;
    char pad2[0xA];
    struct OwnerPakBeginProfileLoad *owner;
    char pad10[4];
    char *dialogData; /* 0x14 */
    char pad18[4];
    ActorOwnerView *player;
    PakMenuSlot *slot;
    struct Dialog *prompt; /* 0x24: dialog resource */
};
struct MenuPakConfirmProfileOrDeleteNote {
    char pad0[0x1C];
    SharedPlayer *player;
    PakMenuSlot *slot;
    char *prompt;
};
struct Digits {
    char c[4];
};
#endif
