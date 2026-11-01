#ifndef COMMON_GAMEPLAY_REACTION_RULES_H
#define COMMON_GAMEPLAY_REACTION_RULES_H
#include "TYPES.H"
typedef struct Shared_MatchRules Shared_MatchRules;
struct Shared_MatchRules {
    char pad0[0x20];
    s32 hideHud;        /* +0x20: src/Player_DrawHeadsUpDisplay_GameplayReactionRules.c */
    s32 teams;          /* +0x24: src/Player_DrawHeadsUpDisplay_GameplayReactionRules.c */
    char pad28[0x4];
    s32 teamScores[5];  /* +0x2C: src/Player_DrawHeadsUpDisplay_GameplayReactionRules.c */
    s32 squadScores[5]; /* +0x40: src/Player_DrawHeadsUpDisplay_GameplayReactionRules.c */
    s32 countRule;      /* +0x54: src/Player_DrawHeadsUpDisplay_GameplayReactionRules.c */
    char pad58[0x1B];
    u8 teamColour; /* 0x73: player render palette */
    char pad74[4];
    s32 squads;         /* +0x78: src/Player_DrawHeadsUpDisplay_GameplayReactionRules.c */
    char pad7C[0x1C];
    s32 markers;        /* +0x98: src/Player_DrawHeadsUpDisplay_GameplayReactionRules.c */
};
/* Match-rule fields from src/Player_DrawHeadsUpDisplay_GameplayReactionRules.c. */
#endif
