#include "COMMON/ACTORRECAT260.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/RECORDRECATCV1.H"
#include "../../../../sdk/include/PFS/PLAYER_CONFIGUREANDPROBECONTROLLERPAK.H"

/* Updates display flags and activates the selected resource. */
s32 Player_GetPlayerIndex(s32 *, s32);

 /* extern */


 /* extern */

 /* extern */


extern s32 g_pakUseScannedChannel[];

/* Updates object display flags and selects the requested resource. */


s32 Player_GetPlayerIndex(int *, s32);

                               /* extern */

 /* const */
extern void Control_EnableControllerPak(s32 kind);
extern s32 g_pakPlayerMessagePending[];
void Player_ConfigureAndProbeControllerPak(ControllerPakMenuContext *menuContext) {
    s32 playerId;
    s32 controllerIndex;
    ControllerPakMenuActorView *pakUnavailableWidgets;
    ControllerPakMenuActorView *pakAvailableWidgets;
    ControllerPakMenuActorView *profileWidgets;
    ControllerPakMenuActorView *transferWidgets;
    ControllerPakMenuActorView *secondaryWidgets;
    ControllerPakMenuActorView *headerWidgets;
    ControllerPakMenuActorView *statusWidgets;
    profileWidgets = menuContext->actor;
    profileWidgets->flags238 = (s32) (profileWidgets->flags238 | 0x01800000);
    transferWidgets = menuContext->actor;
    transferWidgets->flags260 = (s32) (transferWidgets->flags260 | 0x01800000);
    secondaryWidgets = menuContext->actor;
    secondaryWidgets->flags1c0 = (s32) (secondaryWidgets->flags1c0 & 0xFE7FFFFF);
    headerWidgets = menuContext->actor;
    headerWidgets->flags58 = (s32) (headerWidgets->flags58 & 0xFE7FFFFF);
    statusWidgets = menuContext->actor;
    statusWidgets->flags210 = (s32) (statusWidgets->flags210 & 0xFE7FFFFF);
    g_pakUseScannedChannel[0] = 0;
    g_pakPlayerMessagePending[0] = 0;
    controllerIndex = 0;
    if (g_gameSettings.counters.m_bFragTagOn != 0) {
        pakAvailableWidgets = menuContext->actor;
        pakAvailableWidgets->flags120 = (s32) (pakAvailableWidgets->flags120 | 0x01000000);
    } else {
        pakUnavailableWidgets = menuContext->actor;
        pakUnavailableWidgets->flags120 = (s32) (pakUnavailableWidgets->flags120 & 0xFEFFFFFF);
    }
    playerId = menuContext->playerAddress;
    if (playerId != 0) {
        controllerIndex = Player_GetPlayerIndex((s32 *)&g_playerViewRenderContext, playerId);
    }
    Control_EnableControllerPak(controllerIndex);
    Note_ProbeStatus(controllerIndex);
}

                          /* const */

void Player_ConfigureControllerPakMenu(ControllerPakMenuContext *menuContext) {
    s32 playerId;
    s32 controllerIndex;
    ControllerPakMenuActorView *pakUnavailableWidgets;
    ControllerPakMenuActorView *pakAvailableWidgets;
    ControllerPakMenuActorView *profileWidgets;
    ControllerPakMenuActorView *transferWidgets;
    ControllerPakMenuActorView *secondaryWidgets;
    ControllerPakMenuActorView *headerWidgets;
    ControllerPakMenuActorView *statusWidgets;

    playerId = menuContext->playerAddress;
    g_pakPlayerMessagePending[0] = 0;
    controllerIndex = 0;
    if (playerId != 0) {
        controllerIndex = Player_GetPlayerIndex((s32 *)&g_playerViewRenderContext, playerId);
    }
    Control_EnableControllerPak(controllerIndex);
    profileWidgets = menuContext->actor;
    profileWidgets->flags238 = (s32) (profileWidgets->flags238 | 0x01800000);
    transferWidgets = menuContext->actor;
    transferWidgets->flags260 = (s32) (transferWidgets->flags260 | 0x01800000);
    secondaryWidgets = menuContext->actor;
    secondaryWidgets->flags1c0 = (s32) (secondaryWidgets->flags1c0 & 0xFE7FFFFF);
    headerWidgets = menuContext->actor;
    headerWidgets->flags58 = (s32) (headerWidgets->flags58 & 0xFE7FFFFF);
    statusWidgets = menuContext->actor;
    statusWidgets->flags210 = (s32) (statusWidgets->flags210 & 0xFE7FFFFF);
    if (g_gameSettings.counters.m_bFragTagOn != 0) {
        pakAvailableWidgets = menuContext->actor;
        pakAvailableWidgets->flags120 = (s32) (pakAvailableWidgets->flags120 | 0x01000000);
        return;
    }
    pakUnavailableWidgets = menuContext->actor;
    pakUnavailableWidgets->flags120 = (s32) (pakUnavailableWidgets->flags120 & 0xFEFFFFFF);
}
