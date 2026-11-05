#ifndef COMMON_BRAIN_H
#define COMMON_BRAIN_H
#include "types.h"

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
    s32 recentNodes[4]; /* 0x14: previously visited route nodes, -1 when unset */
    char pad24[4];
    s32 pickupGoal; /* 0x28: -1 when no pickup is chosen */
    s32 goalCounters[3]; /* 0x2C */
    s32 searchEnabled; /* 0x38: set again on every reset */
    s32 goalHistory[10]; /* 0x3C */
    struct Actor *target; /* 0x64 */
    s32 targetAux; /* 0x68 */
    s32 goalSlotsA[10]; /* 0x6C */
    s32 goalSlotsB[10]; /* 0x94 */
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
    s32 waitingFlag; /* 0x23C: alternating-action burst is waiting */
    s32 pursuitEndedFlag; /* 0x240: pursuit wait ran out */
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
