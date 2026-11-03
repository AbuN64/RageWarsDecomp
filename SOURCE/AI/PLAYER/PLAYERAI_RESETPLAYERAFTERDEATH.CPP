#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "TYPES.H"
#include "AI/PLAYER/PLAYER_PLACEPLAYERFORROUND.H"
#include "AI/PLAYER/PLAYER_STARTPLAYERANIMATION.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

/* Handles a player's death: stops the body's motion at 0x1C to 0x24 and runs Player_ReleaseObjectHandles_PlayeraiResetplayerafterdeath; in a
   single player game (g_motionVisibilitySettings) a player with limited lives at 0x1450 gets the death menu for its
   profile slot 0 to 3 on its view, and when g_selectedProfileHealthOptionEnabled asks and the player is out of a team game, once
   every active player among the first eight is out the team is revived through Player_PlacePlayerForRound (every
   active player in mode 2 when the mode 14 leader is down, and the leader in modes below 3); in
   multiplayer the view shows the respawn menu, g_playerRespawnCountDialog when the player has a respawn count at 0x5EA
   or g_playerRespawnDialog otherwise. */









extern char g_playerRespawnCountDialog_de;
extern char g_playerRespawnDialog;
extern char g_playerDeathDialogSlotFirst;
extern char g_playerDeathDialogSlotSecond;
extern char g_playerDeathDialogSlotThird;
extern char g_playerDeathDialogSlotFourth;
extern char g_playerViewRenderContext;



extern SharedPlayer *Playerai_GetPlayerByIndex(char *, s32);


void Playerai_ResetPlayerAfterDeath(SharedPlayer *player, PlayerRespawnBodyView *body) {
    SharedPlayer *other;
    SharedPlayer *leader;
    s32 i;
    s32 active;
    s32 out;

    body->motion[0] = 0;
    body->motion[1] = 0;
    body->motion[2] = 0;
    Player_ReleaseObjectHandles(player);
    if (g_gameSettings.local != 0) {
        if (player->views1450.view1450_2.infinite == 0) {
            switch (player->views1C.view5D4_46.slot) {
            case 0:
                Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, &g_playerDeathDialogSlotFirst, player, player->views5E8.view698_36.controller, 0);
                break;
            case 1:
                Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, &g_playerDeathDialogSlotSecond, player, player->views5E8.view698_36.controller, 0);
                break;
            case 2:
                Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, &g_playerDeathDialogSlotThird, player, player->views5E8.view698_36.controller, 0);
                break;
            case 3:
                Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, &g_playerDeathDialogSlotFourth, player, player->views5E8.view698_36.controller, 0);
                break;
            }
        }
        if (g_gameSettings.counters.enabled != 0 && player->views5D8.view5D8_2.controls->team == 0 && player->views5D8.view5D8_2.controls->active != 0) {
            active = 0;
            out = 0;
            leader = 0;
            for (i = 0; i < 8; i++) {
                other = Playerai_GetPlayerByIndex(&g_playerViewRenderContext, i);
                if (other != 0) {
                    if (other->views5D8.view5D8_2.controls->active != 0) {
                        active++;
                        if (other->views5E4.view5E4_3.alive == 0) {
                            out++;
                        }
                    }
                    if (other->views5D8.view5D8_2.controls->mode == 14) {
                        leader = other;
                    }
                }
            }
            if (out == active) {
                if (g_gameSettings.counters.m_nTalsetLives == 2 && leader->views5E4.view5E4_3.alive == 0) {
                    for (i = 0; i < 8; i++) {
                        other = Playerai_GetPlayerByIndex(&g_playerViewRenderContext, i);
                        if (other != 0 && other->views5D8.view5D8_2.controls->active != 0) {
                            Player_PlacePlayerForRound(other);
                        }
                    }
                }
                if (g_gameSettings.counters.m_nTalsetLives < 3) {
                    Player_PlacePlayerForRound(leader);
                }
            }
        }
    } else if (player->views5DC.view5DC_2.view != 0) {
        if (player->views5E8.view5EA_3.respawns != 0) {
            Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, &g_playerRespawnCountDialog_de, player, player->views5E8.view698_36.controller, 0);
        } else {
            Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, &g_playerRespawnDialog, player, player->views5E8.view698_36.controller, 0);
        }
    }
}

extern s32 g_playerSequenceCompletionPending;
extern s32 g_playerSequenceWindowEnabled;
extern u8 g_playerSequenceSavedViewBytes[];


extern char g_playerSequenceCallbacks;


extern s32 CCinema_RequestTrackWithCallbacks(s32 requestId, void *requestContextCallback, VoidCallback completionCallback);
extern void *Scene_FindActorDefinition(Shared_World *world, s32 selection, s32 modelKind);






void Playerai_TryStartPlayerSequence(PlayerSequenceActorView *playerActor, void *bodyActor, s32 sequenceType)
{
    s32 enabled;
    u32 resource_flags;
    void *resource;
    s32 i;

    enabled = 1;
    resource_flags = 0;

    if (playerActor->modelRecordIndexPointer != 0) {
        resource = Scene_GetModelRecordByIndexPointer(&g_world, playerActor->modelRecordIndexPointer);
        if (resource != 0) {
            resource_flags = ((PlayerSequenceResourceView *)(resource))->resourceFlagBits;
        }
    }

    if (g_world.visibilityEnabled != 0) {
        enabled = 0;
    }
    if (playerActor->stateFlags & 0x8000) {
        enabled = 0;
    }
    if (g_world.visibilityEnabled != 0) {
        enabled = 0;
    }
    if (g_playerCount >= 2) {
        enabled = 0;
    }
    if (sequenceType == 12) {
        enabled = 0;
    }
    if (playerActor->stateFlags & 0x8000) {
        enabled = 0;
    }
    if (resource_flags & 0x1000000) {
        enabled = 0;
    }
    if ((resource_flags & 0x80000) &&
        (sequenceType != 20) && (sequenceType != 40) && (sequenceType != 30)) {
        enabled = 0;
    }

    playerActor->sequenceEnabled = enabled;
    if (enabled != 0) {
        if (sequenceType == 50) {
            void *data;

            data = playerActor->view;
            g_playerSequenceCompletionPending = 1;
            if (data != 0) {
                for (i = 0; i < 4; i++) {
                    g_playerSequenceSavedViewBytes[i] = ((struct PlayerViewSavedBytes *) (((u8 *) playerActor->view) + i))->savedByte;
                }
            }
        }
        g_playerSequenceWindowEnabled = 0;
        g_playerSequenceActor = (Player *)playerActor;
        CCinema_RequestTrackWithCallbacks(sequenceType, 0, (VoidCallback)&g_playerSequenceCallbacks);
    }

    resource = Scene_FindActorDefinition(&g_world, -1, 3141);
    if (resource != 0) {
        playerActor->scaleX = ((PlayerSequenceResourceView *)(resource))->scaleX;
        playerActor->scaleY = ((PlayerSequenceResourceView *)(resource))->scaleY;
        playerActor->scaleZ = ((PlayerSequenceResourceView *)(resource))->scaleZ;
    }
}
