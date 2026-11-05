#include "Common/legacy_collision_actor.h"
#include "Ai/nav_symbols.h"
#include "Ai/ai_shared_symbols.h"
#include "include_asm.h"
#include "Data/Ovl4dat/k_noderesourceandcollisionlinkencodedwords_noderesourceandcollisionlinkdata.h"

/* unit NODE_RESOURCE_AND_COLLISION_LINK_DATA.CPP */
#if defined(VERSION_EU)
#include "Common/ccollisionsetup_t.h"
/* The collision setup table CCollision_Initialize hands to CCollision_ApplySetupTable (through its KUSEG alias
 * g_collisionSetupTableResource): one row per collision info, ended by an empty row. */
/* ROM row targets use byte offsets: secondary slots 1/2/3/5/0/6/4 and
 * supporting-platform slots 1/4/3/2/0 are spaced 0x20 bytes apart. */
CCollisionSetup_t g_collisionSetupTable[36] = {
    { (CCollisionInfo2_t *)0x8010A458 /* eu-x g_secondaryCollisionContext + 0x20 */, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A358 /* eu-x g_supportingPlatformCollisionQuery + 0x20 */, 0x3C552B, 5, 2, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A190 /* eu-x g_collisionSurfaceExcludedFromTrace + 0x20 */, 0x3C5529, 2, 2, 2, -2100.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A2F8 /* eu-x g_particleOwnerEffectFlags + 0x8 */, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A3B8 /* eu-x g_supportingPlatformCollisionQuery + 0x80 */, 0x3C5729, 5, 2, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x80109FB0 /* eu-x g_pagerPageCounters + 0x10 */, 0x3C5D29, 5, 2, 2, -69.119995f, 0.0f, 0.0f, 0.0f, 0.08f },
    { (CCollisionInfo2_t *)0x8010A1B0 /* eu-x g_collisionSurfaceExcludedFromTrace + 0x40 */, 0x3C5529, 5, 2, 2, 0.0f, 0.0f, 0.9f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A418 /* eu-x g_globalGameplayFlags + 0x0 */, 0x2C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A010 /* eu-x g_portalDefaultCollisionQuery + 0x20 */, 0x3C5729, 5, 2, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A130 /* eu-x g_playerCollisionProbe + 0x40 */, 0x3C5309, 5, 6, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A398 /* eu-x g_supportingPlatformCollisionQuery + 0x60 */, 0x3C5729, 0, 0, 2, -2303.9998f, 0.0f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A318 /* eu-x g_particleOwnerEffectFlags + 0x28 */, 0x3C5308, 5, 3, 2, -2303.9998f, 0.3f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A110 /* eu-x g_playerCollisionProbe + 0x20 */, 0x3C5308, 5, 3, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A478 /* eu-x g_secondaryCollisionContext + 0x40 */, 0x3C5108, 5, 2, 2, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A378 /* eu-x g_supportingPlatformCollisionQuery + 0x40 */, 0x3C5109, 5, 2, 2, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A150 /* eu-x g_playerCollisionProbe + 0x60 */, 0x3C5309, 5, 6, 2, -2303.9998f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A498 /* eu-x g_secondaryCollisionContext + 0x60 */, 0x3C5108, 5, 2, 2, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A4D8 /* eu-x g_secondaryCollisionContext + 0xA0 */, 0x344108, 0, 3, 3, -1235.4816f, 0.5f, 0.25f, 0.0f, 0.25f },
    { (CCollisionInfo2_t *)0x8010A090 /* eu-x g_effectRenderDefaults + 0x0 */, 0x110108, 1, 3, 3, -4941.9263f, 0.7083334f, 0.1f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A438 /* eu-x g_secondaryCollisionContext + 0x0 */, 0x345309, 0, 3, 3, -1535.9999f, 0.6f, 1.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A3F8 /* eu-x g_primaryCollisionContext + 0x0 */, 0x305109, 0, 3, 3, 0.0f, 0.6f, 1.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A4F8 /* eu-x g_secondaryCollisionContext + 0xC0 */, 0x10, 0, 0, 0, 0.0f, 0.3f, 0.7f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A0D0 /* eu-x g_portalAlternateCollisionQuery + 0x0 */, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A070 /* eu-x g_portalNoModelFlagCollisionQuery + 0x0 */, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A050 /* eu-x g_portalModeCollisionQuery + 0x0 */, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x80109FF0 /* eu-x g_portalDefaultCollisionQuery + 0x0 */, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x80109FD0 /* eu-x g_particleCollisionProbeResult + 0x0 */, 0x1C000, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A0F0 /* eu-x g_playerCollisionProbe + 0x0 */, 0x204408, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A030 /* eu-x g_defaultProbeMotionSettings + 0x0 */, 0x1C000, 1, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A1D0 /* eu-x g_collisionNoDetachSettingsAlternate + 0x0 */, 0x0, 0, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A170 /* eu-x g_collisionSurfaceExcludedFromTrace + 0x0 */, 0x0, 0, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A0B0 /* eu-x g_effectRenderDefaults + 0x20 */, 0x341508, 2, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A3D8 /* eu-x g_defaultActorCollisionInfo + 0x0 */, 0x141508, 2, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A4B8 /* eu-x g_secondaryCollisionContext + 0x80 */, 0x101508, 1, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (CCollisionInfo2_t *)0x8010A338 /* eu-x g_supportingPlatformCollisionQuery + 0x0 */, 0x105529, 5, 1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0 },
};
#endif

#if defined(VERSION_EU_X)
#include "types.h"
#include "Frontend/frontend_address_symbols.h"
/* The retained resource link ends at the next function.
 * The two trailing words have no evidenced consumer semantics. */
typedef struct NodeResourceLinkTail {
    const char *resource;
    u32 retainedWords[2];
} NodeResourceLinkTail;
typedef char NodeResourceLinkTailSize[(sizeof(NodeResourceLinkTail) == 12) ? 1 : -1];
NodeResourceLinkTail g_nodeResourceLinkTailEuX = {
    g_cheatModeActivatedMessageTableEuX + 8, { 128, 1 },
};
#endif
