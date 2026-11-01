#ifndef COMMON_SESSION_STATE_H
#define COMMON_SESSION_STATE_H
#include "TYPES.H"

struct CMenu_t;
typedef struct MessageList {
    struct CMenu_t *head;
    char pad04[0x10 - 0x4];
    s32 flag;
    s16 rotation; /* 0x14 */
} MessageList;

typedef struct RosterEntry {
    char pad0[0x78];
    u8 active;
    char pad79[0x92 - 0x79];
    u8 team;
    char pad93[0x96 - 0x93];
} RosterEntry;

typedef struct Settings580 {
    char pad0[0xD];
    u8 trialKind;
    char padE[0x1D - 0xE];
    u8 allowed;
    char pad1E[0xD0 - 0x1E];
    RosterEntry roster[8];
} Settings580;

/* Rules and running match state inside the owning GameSession. */
struct GameRules;
typedef struct GameRules GameRules;
struct GameRules {
    char pad0[0x14];
    f32 timeLimit;
    s32 scoreLimit;
    s32 locked;
    char pad20[0x24 - 0x20];
    s32 teams;
    char pad28[0x40 - 0x28];
    s32 teamPoints[5];
    s32 sudden;
    s32 totalScoreTarget;
    char pad5C[0x78 - 0x5C];
    s32 teamRule;
    s32 pointTarget;
    char pad80[0x9C - 0x80];
    s32 rounds;
    char padA0[0xA8 - 0xA0];
    s32 humanWon;
};
struct GameSessionState;
typedef struct GameSessionState GameSessionState;
struct GameSessionState {
    MessageList messages;
    char pad18[0xCAC - sizeof(MessageList)];
    Settings580 settings;
    char pad122C[0x1278 - 0x122C];
    char reserved1278[4]; /* GameSession.clockPaused owns this word. */
    char pad127C[0x1284 - 0x127C];
    GameRules rules[1];
};
#endif
