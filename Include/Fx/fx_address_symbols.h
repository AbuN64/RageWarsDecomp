#include "Placeplayerlight/placeplayerlight.h"
#ifndef FX_ADDRESS_SYMBOLS_H
#define FX_ADDRESS_SYMBOLS_H
#include "Pickup/pickup_trailing_text.h"
#include "Ai/player_symbols.h"
#include "Common/triple.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/effectcontribution.h"
/* Symbols that exist only at a fixed ROM address; each is referenced through its address. */
extern f32 g_cameraVolumeBoundsMinZ;
/* The particle quad render setup display list (eu-x defines its words in fx.cpp). */
struct ParticleQuadRenderSetup;
extern struct ParticleQuadRenderSetup g_particleQuadRenderSetup;
extern s32 g_menuModelFillEnabled;
extern char g_artsendNextTextureHoldCount[];
extern char g_artsendToggleButtonHeld[];
extern char g_pakNoteTypeTelsetLabelCell[];
extern char g_pakNoteTypeTelsetLabelText[];
extern char g_pickupAmmoDefinitions[];
#include "Common/screenmessagesubstitution.h"
extern char g_artsendPreviousPageHoldCount[];
extern char g_artsendPreviousTextureHoldCount[];
extern char addrLow_Pickup_ApplySpecialPickupEntryVariant1[];
extern char addrLow_Pickup_HandlePowerWeaponPickupEntryVariant1[];
extern char addrLow_Pickup_ApplyAmmoEntryVariant1[];
extern char addrLow_Pickup_ApplyHealthEntryVariant1[];
extern char g_Pickup_ApplyLifePointsEncodedCallbackEntry_de[];
extern char addrLow_Pickup_ApplyAmmoBundleEntryVariant1[];
extern char addrLow_Pickup_ApplySpecialPickupEntryVariant3[];
extern char addrLow_Pickup_HandlePowerWeaponPickupEntryVariant3[];
extern char addrLow_Pickup_ApplyAmmoEntryVariant3[];
extern char addrLow_Pickup_ApplyHealthEntryVariant3[];
extern char g_Pickup_ApplyLifePointsEncodedCallbackEntry_eu_x[];
extern char addrLow_Pickup_ApplyAmmoBundleEntryVariant3[];
extern char addrLow_Pickup_ApplySpecialPickupEntryVariant2[];
extern char addrLow_Pickup_HandlePowerWeaponPickupEntryVariant2[];
extern char addrLow_Pickup_ApplyAmmoEntryVariant2[];
extern char addrLow_Pickup_ApplyHealthEntryVariant2[];
extern char g_Pickup_ApplyLifePointsEncodedCallbackEntry_eu[];
extern char addrLow_Pickup_ApplyAmmoBundleEntryVariant2[];
extern s32 *g_backdropTextLinesByLanguage[];
extern u8 *g_weaponLockedNoticeTextEuX[];
extern f32 g_effectContributionInitialScale[];
#endif
