#include <PR/gbi.h>
#include "Common/effectcontribution.h"
#include "Data/rest_source_records.h"
#include "Data/Ovl1_d/weapon_charge_and_loop_sound_callback_address.h"
#include "Weapon/weapon.h"

/* PLAYER_RESETPLAYERFORROUND_DATA_DATA.CPP */
const float g_roundResetQuarterScaleConstant[1] = {
    0.25f,
};

/* FX_DRAWBOUNDEDPARTICLEQUADS_DATA.CPP */
#if defined(VERSION_EU)
Gfx g_boundedParticleQuadDisplayListsEu[36] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSPEndDisplayList(),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTextureL(0x8000, 0x8000, 0, 0xFF, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104E50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPEndDisplayList(),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSPEndDisplayList(),
    gsDPNoOp(),
};
#endif

/* PLAYER_VIEW_TUNING_PROFILES_US.CPP */
#if defined(VERSION_US)
float g_playerViewTuningProfilesUs[19] = {
    0.0f, 0.25f, 0.9f, 0.6f,
    0.3f, -1.5707965f, 1.5707965f, 0.25f,
    0.9f, 0.6f, 0.3f, -0.78539824f,
    1.5707965f, 0.0f, 0.0f, 0.5f,
    0.25f, -0.06981318f, 1.5707965f,
};
#endif

/* BARREL_SPAWNFLAGGEDEFFECTS_DATA.CPP */
#if defined(VERSION_US_REV1)
s32 g_flaggedActorEffectStateWords[2] = {
    1, 2200,
};
#endif

/* WEAPON_CONTROLLER_AND_MOVEMENT_TUNING.CPP */
#if defined(VERSION_US_REV1)
WeaponControllerAndMovementTuningUsRev1Layout g_weaponControllerAndMovementTuningUsRevision = {
    { 0, 8 },
    (void *)&Weapon_InitializeChargeAndLoopSound,
    { 65536, 327680, 262144, 786432, 524288, 655360, 131072, 196608 },
    { 3e+01f, 48.0f, 1.3e+02f }
};
#endif

/* PLAYER_MOVEMENT_TUNING_AND_LOOKUP.CPP */
#if defined(VERSION_US_REV1)
PlayerMovementTuningAndLookupUsRev1Layout g_playerMovementTuningAndLookupUsRevision = {
    { 0.09f, 0.05f, 0.5f },
    { 0x00000000, 0x00010000, 0x00050000, 0x00040000, 0x000C0000, 0x00080000, 0x000A0000, 0x00020000, 0x00030000 },
    { 3e+01f, 48.0f, 1.3e+02f },
};
#endif

/* PLAYER_MOVEMENT_SCALE_CONSTANTS.CPP */
#if defined(VERSION_US_REV1)
float g_playerMovementScaleConstantsUsRevision[4] = {
    0.09f, 0.05f, 0.5f, 0.0f,
};
#endif
