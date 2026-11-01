#ifndef COMMON_BRAIN_H
#define COMMON_BRAIN_H
#include "TYPES.H"

struct SharedPlayer;
struct Actor;
struct Behaviour;

/* Computer-player state shared by the frame, pursuit and close-attack updates. */
typedef struct Brain {
    struct SharedPlayer *player;
    s32 start; /* 0x4 */
    s32 route; /* 0x8 */
    s32 destination; /* 0xC */
    s32 node; /* 0x10 */
    s32 w14;
    char pad18[0x64 - 0x18];
    struct Actor *target; /* 0x64 */
    char pad68[0xBC - 0x68];
    s32 routeState; /* 0xBC */
    char padC0[0x1BC - 0xC0];
    s32 stage; /* 0x1BC: pickup route stage number (Nav pickup selection) */
    char pad1C0[8];
    s32 matches; /* 0x1C8: kind-6 nodes matching the selection id */
    char pad1CC[0x1F0 - 0x1CC];
    f32 clearance[8];
    char pad210[8];
    struct Behaviour *behaviour; /* 0x218 */
    char pad21C[4];
    s32 state; /* 0x220: close-attack state */
    s32 patrolRoute; /* 0x224: Nav_UpdatePatrolRoute */
    s32 patrolPosition; /* 0x228: Nav_UpdatePatrolRoute */
    char pad22C[4];
    s32 combat;
    char pad234[4];
    s32 arrived; /* 0x238: object-chase arrival */
    s32 w23C;
    s32 w240;
    f32 tracking[8]; /* 0x244..0x260: reset together */
    char pad264[0x28C - 0x264];
    s32 preferred; /* 0x28C: preferred target, an AiTarget in AiController */
    char pad290[0x2D8 - 0x290];
    s32 timer;
    s32 pattern;
    s32 distance;
    s32 actionDelay; /* 0x2E4 */
    s32 actionDuration; /* 0x2E8 */
    s32 alternateCountdown; /* 0x2EC */
    char pad2F0[0x318 - 0x2F0];
    s32 frames;
    s32 visible;
    s32 fireTimer;
    s32 cooldown; /* 0x324 */
    s32 lastAttacker; /* 0x328: Player in AiController */
    s32 previousPortalLink; /* 0x32C */
} Brain;
#endif
