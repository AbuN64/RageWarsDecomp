#ifndef COMMON_INTEGERSTATE1250_H
#define COMMON_INTEGERSTATE1250_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
extern f32 g_playerDamageTimerDurationScale;

struct PlayerForceMarkerStateView;
typedef struct PlayerForceMarkerStateView PlayerForceMarkerStateView;

struct PlayerTintBlendStateView;
typedef struct PlayerTintBlendStateView PlayerTintBlendStateView;


extern int Playerai_HasForceMarker(char *object);


struct ScoredPlayerRecord;
typedef struct ScoredPlayerRecord ScoredPlayerRecord;

struct PlayerForceMarkerCounterView;

extern int Playerai_GetPlayerCount(void);





struct Timer;
typedef struct Timer Timer;

struct ScoreTable;
struct ScoreTable {
    u8 pad00[0x3C];
    short value[8];
};
struct ScoredPlayerRecord;
struct ScoreTable;
struct ScoredPlayerRecord {
    u8 pad0000[0x5D8];
    struct ScoreTable *scores;
    u8 pad05DC[0x16E0 - 0x5DC];
    struct ScoredPlayerRecord *next;
    u8 pad16E4[4];
};

struct PlayerTintBlendStateView;

struct PlayerForceMarkerHandleView;
typedef struct PlayerForceMarkerHandleView PlayerForceMarkerHandleView;

struct Timer;
struct Timer {
    float m_DamagePerFrame;
    float m_FramesRemaining;
    int kind;
    float m_TotalDamage;
    float m_DamageIssued;
    int m_bIsInflator;
};

struct PlayerEffectTimerSet;


struct PlayerAlternateFireStateView;


struct PlayerWeaponDelayStateView;



struct PlayerForceMarkerHandleView;


extern void Playerai_DrawForceMarker(char *player);

struct PlayerForceMarkerCounterView;
typedef struct PlayerForceMarkerCounterView PlayerForceMarkerCounterView;

struct PlayerEffectTimerSet;
typedef struct PlayerEffectTimerSet PlayerEffectTimerSet;

struct PlayerWeaponTransitionParameterView;



struct PlayerForceMarkerMatrixView;

struct PlayerForceMarkerOwnerView;

struct Context;
struct ScoredPlayerRecord;
struct Context {
    u8 pad00[4];
    struct ScoredPlayerRecord *base;
    u8 pad08[0x18];
    struct ScoredPlayerRecord *head;
};


struct PlayerForceMarkerOwnerView;
typedef struct PlayerForceMarkerOwnerView PlayerForceMarkerOwnerView;

extern float g_playerImpulseScale;

struct PlayerLoopingSoundHandleView;

struct PlayerWeaponDelayStateView;
typedef struct PlayerWeaponDelayStateView PlayerWeaponDelayStateView;

struct Context;
typedef struct Context Context;

extern void *Playerai_FindHighestScoringOtherPlayer(Context *context);


struct PlayerWeaponTransitionParameterView;
typedef struct PlayerWeaponTransitionParameterView PlayerWeaponTransitionParameterView;


struct PlayerForceMarkerMatrixView;
typedef struct PlayerForceMarkerMatrixView PlayerForceMarkerMatrixView;




struct PlayerForceMarkerStateView;


struct PlayerAlternateFireStateView;
typedef struct PlayerAlternateFireStateView PlayerAlternateFireStateView;



struct PlayerLoopingSoundHandleView;
typedef struct PlayerLoopingSoundHandleView PlayerLoopingSoundHandleView;

#endif
