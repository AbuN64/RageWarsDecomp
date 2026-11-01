#ifndef COMMON_ACTIVE_H
#define COMMON_ACTIVE_H
#include "TYPES.H"
struct Active;
typedef struct Active Active;



struct PlayerNameProfileRecord;
struct PlayerNameProfileRecord {
    char name[393];
    u8 profile[5];
    char pad18E[2];
};

extern void Random_StartCaptureTheFlagMatch(void);


extern void Random_StartTeamMatch(void);


struct Active;
struct Active {
    u8 recorded; /* +0x00: nonzero when finishing the level is recorded per save slot */
    char pad1[0x21 - 1];
    u8 score;
    u8 limit;
    u8 other;
    u8 time;
};

extern void Random_StartFragTagMatch(void);

extern void Random_StartIndividualMatch(void);



struct MatchPlayerStatus;
struct MatchPlayerStatus {
    char pad0[0x78];
    u8 joined;
    u8 profileThird;
    u8 profileFourth;
    u8 profileFirst;
    char pad7C;
    u8 profileSecond;
    char pad7E[2];
    s8 kind;
    char pad81;
    u8 profileFifth;
    char pad83;
    char name[0x91 - 0x84];
    u8 computer;
    u8 team;
    char pad93;
    u8 lives;
    u8 score;
};
#endif
