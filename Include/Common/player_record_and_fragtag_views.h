#ifndef COMMON_PLAYER_RECORD_AND_FRAGTAG_VIEWS_H
#define COMMON_PLAYER_RECORD_AND_FRAGTAG_VIEWS_H
struct PlayerFragTagSelectionView;
struct ScreenRectangle;
#ifndef PLAYERAI_RECORD_AND_HUD_DECLARATIONS_H
#define PLAYERAI_RECORD_AND_HUD_DECLARATIONS_H
#include "types.h"
#include "Common/frag_tag_scores.h"
extern void *Playerai_ResetProfileState(void *actorObject);


extern float g_playerHudSpriteMetrics[5];

struct Player;
extern int Playerai_SelectedWeaponUsesAmmo(struct Player *actor);

struct FragTagMatchRulesView;
typedef struct FragTagMatchRulesView FragTagMatchRulesView;








extern void *Playerai_GetEligiblePlayerByIndex(void *playerWorld, u32 eligiblePlayerIndex);

extern void Playerai_UpdateCountdown(void *player);

extern void Playerai_DrawHudSprite1FB(void *unusedPlayer, struct ScreenRectangle *viewport);


struct FragTagMatchRulesView;
struct FragTagMatchRulesView {
    char pad0[0xD];
    unsigned char mode;
    char padE[0x1D - 0xE];
    unsigned char started;
};

struct PlayerDamageOverTimeView;
typedef struct PlayerDamageOverTimeView PlayerDamageOverTimeView;





struct PlayerTimedPowerupView;
struct PlayerTimedPowerupView {
    unsigned char padding_0[1656];
    f32 countdownSeconds;
};

extern float g_playerJumpInputDelayLimit;

extern int Player_IsClockPaused(void);

extern float g_playerModelBlendRate;









struct PlayerTimedPowerupView;
typedef struct PlayerTimedPowerupView PlayerTimedPowerupView;

struct PlayerDamageOverTimeView;
struct PlayerDamageOverTimeView {
    char pad0[0x840];
    s32 effectTimer;
};


struct PlayerFragTagSelectionView;
typedef struct PlayerFragTagSelectionView PlayerFragTagSelectionView;


struct PlayerFragTagSelectionView;
struct PlayerFragTagSelectionView {
    char pad0[0x5D4];
    int character;
    struct AiProfile *info;
    char pad5DC[0x5EA - 0x5DC];
    short state;
    char pad5EC[0x133C - 0x5EC];
    int lives;
    char pad1340[0x13C8 - 0x1340];
    int timer;
    char pad13CC[0x1450 - 0x13CC];
    int isBot;
};


struct Player;
extern void Playerai_UpdateHeldWeaponModel(struct Player *actor);



extern void Playerai_InitializeLivesAndRespawn(struct PlayerFragTagSelectionView *player);





extern void Player_InitRecordDefaults(void * record);

typedef struct PlayerRecordDefaultsView {
    int firstKey;
    int secondKey;
    int resetState;
    char padC[0x90 - 0xC];
    float initialVectorX;
    float initialVectorY;
    float initialVectorZ;
    int vectorState;
    float scalarValue;
    int scalarState;
    int reservedState;
    float defaultFirstFloat;
    float defaultSecondFloat;
    int reservedStateOne;
    int reservedStateTwo;
} PlayerRecordDefaultsView;

extern void Playerai_ApplyDamageOverTime(struct Player *player, void *source);

extern s32 Playerai_IsRoundEndState(void *);

extern int g_playerEyeMarkerAngle;

#endif
#endif
