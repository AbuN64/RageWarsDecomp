#ifndef AI_AI_SHARED_SYMBOLS_H
#define AI_AI_SHARED_SYMBOLS_H
#include "Common/ccollisionsetup_t.h"
#include "Engine/geometry.h"
#include "Engine/Instance/gobjinst.h"
#include "types.h"
#include "Common/frag_tag_scores.h"
#include "Common/vector4f.h"
struct Game;
struct WeaponActionRecord;
/* Globals and functions placed by the symbol map; no C definition exists. */
extern struct CollisionInfo g_defaultProbeMotionSettings;
extern struct Game g_gameplayRoundState;
extern struct CollisionQuery g_portalDefaultCollisionQuery;
extern struct WeaponActionRecord g_weaponActionRecords[];
extern char g_Player_UpdateFloatingStateAddress_us_us_rev1[];
extern char g_Player_UpdateFlyModeAddress_us_us_rev1[];
extern char g_Player_UpdateStandingStateAddress_us_us_rev1[];
extern char g_Player_UpdateSwimmingStateAddress_us_us_rev1[];
extern char g_Player_UpdateWadingStateAddress_us_us_rev1[];
extern char addrLow_Playerai_UpdateWalkingMovement_us[];
extern char g_actorParticleEffectSystem[];
extern s32 g_gameLoopFrameCount;
extern s32 g_playerSpecialAnimationTable;
extern s32 g_playerWeaponClassMode;
extern u8 g_playerAimHudEnabled;
extern u8 g_gameControllerMode;
extern u8 g_playerHudSpriteMode;
/* Data rows and code labels inside larger symbol-map objects, named by the symbol map. */
extern char g_navBehaviorCallbackRows[][0x50]; /* 14 nav behaviour callback rows of 0x50 bytes inside g_actorRadialDirections */
extern char g_deviceDrawRomDamageEntry[];
#endif
