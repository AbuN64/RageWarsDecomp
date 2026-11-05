#ifndef FRONTEND_PLAYER_MENU_RECORDS_H
#define FRONTEND_PLAYER_MENU_RECORDS_H
#include "types.h"

struct MenuFrontendUpdatePlayModeMenu {
    char pad[0x44];
    struct MenuWidget *list;
};

struct ControllerPortView {
    u8 pad0[4];
    s8 controllerPort;
};

struct ControllerInitStatusBytes {
    u16 id;
    u8 team;
    u8 slot;
};

typedef struct ControllerInitStatusBytes ControllerInitStatusBytes;

struct FrontendKeySlotEntry {
    s32 key;
    char pad[0x70 - 4];
};

struct PlayerFrontendCountOpenPlayerSlots {
    char pad0[0x78];
    u8 active;
    char pad79[0x96 - 0x79];
};

struct PlayerRecord {
    char data[400];
};

typedef struct PlayerRecord PlayerRecord;

struct RecordCMenuProfileUpdateProfileModeLabel {
    char pad[0x7B];
    s8 mode;
};

struct OwnerCMenuProfileUpdateProfileModeLabel {
    char pad[0x5D8];
    struct RecordCMenuProfileUpdateProfileModeLabel *record;
};

#endif
