#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "RENDER/PLAYER_CONTROLLER_RESET_VIEWS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <PR/gbi.h>
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/WORLD.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"




extern f32 Gobjinst_GetActorHeight(void *actor);

extern void Scene_SampleWorldLighting(void *world, void *position, void *lighting);

extern void Gobjinst_DrawVisibleCachedActor(void *actor, void *view);

extern void Player_DrawRedMarkerPrism(void *player, void *unusedView);


#include "COMMON/GAME_SESSION.H"

extern void SetN64_ClearDepthRect(void *unused, s32 left, s32 right, s32 top,
                          s32 bottom, s32 interlaced);

void Player_DrawPlayerModel(void *player, void *camera) {
    CVector3 pos;
    s32 value;
    Gfx *cmd;

    pos = ((LevelActor *)player)->position0;
    pos.y += ((LevelActor *)player)->eyeHeight;
    pos.y += Gobjinst_GetActorHeight(player) * ((ScalarPair *)&g_playerHeightScalePair_us)->second;
    Scene_SampleWorldLighting(&g_world, &pos,
                  &((LevelActor *)player)->lighting[g_lightingBufferIndex]);

    value = 102;
    if (g_gameSettings.local != 0) {
        if ((g_resultExitPending != 0) &&
            (((Shared_ActorView *)player)->controls->transientFlag != 0)) {
            value = g_fragTagModelId;
        } else {
            value = g_characterModelIds[((MovementDescriptor *)((LevelActor *)player)->definition)->body.header.character];
            ((LevelActor *)player)->renderPass =
                ((Shared_ActorView *)player)->controls->playerId;
        }
    }
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, player, value,
                  ((Shared_ActorView *)player)->effectId);

    cmd = g_displayListCursor++;
    gDPPipeSync(cmd);
    cmd = g_displayListCursor++;
    gDPSetCycleType(cmd, G_CYC_2CYCLE);
    cmd = g_displayListCursor++;
    gSPGeometryMode(cmd, 0, G_FOG);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 4, 2);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 12, 2);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 20, 0xFFFE);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 28, 0xFFFE);

    Gobjinst_DrawVisibleCachedActor(player, camera);
    if (((Shared_ActorView *)player)->targeting != 0) {
        Player_DrawRedMarkerPrism(player, camera);
    }
}

void Player_DrawHeldWeapon(void *player, WeaponMenuView *camera) {
    WeaponInfo *entry;
    f32 *rect;
    f32 x;
    f32 y;
    f32 left;
    f32 right;
    f32 top;
    f32 bottom;

    if ((((Shared_ActorView *)player)->selectedAction != -1) &&
        (((Shared_ActorView *)player)->lives != 0)) {
        gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
        gDPSetTexturePersp(g_displayListCursor++, G_TP_PERSP);
        Geometry_InvalidateMaterialKeys();

        entry = g_weaponInfoByType[((Shared_ActorView *)player)->selectedAction];
        rect = camera->viewport;
        x = rect[0];
        y = rect[1];
        left = entry->scopeBounds[0] * x + rect[2];
        right = entry->scopeBounds[2] * x + rect[2];
        top = entry->scopeBounds[1] * y + rect[3];
        bottom = entry->scopeBounds[3] * y + rect[3];
        SetN64_ClearDepthRect(&g_gameSession, (s32)left, (s32)right, (s32)top,
                      (s32)bottom, camera->clipMode);

        gSPGeometryMode(g_displayListCursor++, 0, G_FOG);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, 4, 1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, 12, 1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, 20, 0xFFFF);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, 28, 0xFFFF);
        Geometry_BeginModelBatch();
        Gobjinst_DrawVisibleCachedActor(&((Shared_ActorView *)player)->weapon, camera);
        Geometry_FlushModelBatch();
    }
}
