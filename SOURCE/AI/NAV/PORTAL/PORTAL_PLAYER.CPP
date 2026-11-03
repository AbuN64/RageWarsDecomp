#include "include_asm.h"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/INTEGERSTATE2C.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AI/NAV/PORTAL_LINKNAVIGATIONOBJECTS.H"
#include "COMMON/LISTHEADER.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "PORTAL/PORTAL__PLAYER.H"

/* 800C6E58.CPP */
#if !(defined(VERSION_US_REV1))
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Portal_SearchRelatedGoalPathConstantWords_us_rev1_Portal.c */
#endif

/* 800C6E60.CPP */
/* ROM-grounded data: src/g_Portal_FindPortalRouteConstantWords_Portal.c */

/* 800C6E64.CPP */
/* ROM-grounded data: src/g_Portal_SearchPortalRouteConstantWords_Portal.c */

/* 800C6E68.CPP */
#if !(defined(VERSION_US_REV1))
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Portal_EstimateGoalDistanceConstantWords_us_rev1_Portal.c */
#endif

/* 800C6E70.CPP */
/* ROM-grounded data: src/g_Portal_SearchPathConstantWords_Portal.c */

/* 800C6E7C.CPP */
/* ROM-grounded data: src/g_Portal_InitSearchNodeConstantWords_Portal.c */

/* 800C6E84_6.CPP */
/* ROM-grounded data: src/g_Portal_IsNodeMovementBlockedConstantWords_Portal.c */

/* 80208000_6.CPP */
/** Returns the difference between the constant after g_actionSettingsRandomRange and Scaled_GetDifficultyEngagementAdjustment's result, scaled by g_portalEngagementScale. */

extern f32 Scaled_GetDifficultyEngagementAdjustment(AiController *controller);

extern f32 g_portalEngagementBase;

/* Find the nearest world object matching each active target ID, clearing its active flag when no object is close enough. */

f32 Graphu64_GetPointDistance(f32 *a, f32 *b);

int Scene_GetModelIdAtIndex(void *world, int modelIndex);

/* Preserve the owning controller passed in a0 by the original MIPS. */
f32 Portal_GetEngagementDistance(AiController *controller) {
    return (g_portalEngagementBase - Scaled_GetDifficultyEngagementAdjustment(controller)) * g_portalEngagementScale;
}


extern char *Scene_GetPlatformRoute(void *world, s32 index);
extern void *Scene_GetPlatformRoutePoint(void *a, s32 b, s32 c);
/* Give every platform-flagged (0x200) search node the nearest moving platform (object 0x642) and the
 * nearest point on it: a route platform (mode 4) offers each of its route points, any other platform
 * its base and its top (base + height, pushed out by radius along heading when radial). A node with
 * no platform loses its 0x200 flag. */

typedef struct NavigationCollisionQuery { s32 flags, word4, word8, wordC, word10, word14, word18; } NavigationCollisionQuery;
extern NavigationCollisionQuery g_portalDefaultCollisionQuery, g_portalModeCollisionQuery, g_portalNoModelFlagCollisionQuery, g_portalAlternateCollisionQuery;
int InstHdr_GetActorMotionState(void *levelActor);
int Insthdr_GetModelCollisionFlag1(void *actorStorage);
s32 Insthdr_IsInactiveOrCollisionOption4(void *actor);
int Insthdr_GetModelCollisionFlag8(void *actorStorage);
s32 Unicol_MoveActorWithCollision(Player *, CVector3, NavigationCollisionQuery *);
void Graphu64_SubtractVectors(struct CVector3_t *difference, struct CVector3_t *leftVector, struct CVector3_t *rightVector);

/* Collisions the actor would meet moving to a point (61.44 above it), without committing the move: the actor's 0x50-byte header is saved and
 * restored around the trial move. */
/* Collects the points one portal away from a point, with the portal joining each; returns how many. */
/* Picks the controller's next point: follows a queued point when the actor may take it, otherwise the nearest reachable neighbour
 * (special portals and drops first while within the starting height). */
