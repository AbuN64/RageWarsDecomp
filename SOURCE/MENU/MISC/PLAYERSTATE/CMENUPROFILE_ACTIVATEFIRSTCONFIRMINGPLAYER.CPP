#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "MENU/PLAYERSETTINGS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "MENU/MISC/CMENUPROFILE_ACTIVATEFIRSTCONFIRMINGPLAYER.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"
#include "RENDER/CONTROL_CYCLEACTORSNAPSHOTMODE.H"

/* Clears eight player active flags, then marks the first settings slot whose controller profile is active. */
extern struct ConfirmingControllerStatusView g_gameSettingsRecordActiveFlagBase[];

extern PlayerSettings g_playerSettings[];

extern unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);

/* Finds the first of the four slots in g_controllerProfiles that Control_IsAButtonPressed_Character accepts, writing its index to out and returning it, or writing -1 and returning NULL when none does. */


extern unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);

/** Count how many of the 4 flagged entries in g_controllerProfiles also have a nonzero flag in the
 *  matching g_gameSettings record, returning 0 early on the first flagged entry that does not. */



/* Advances the frame timer g_profileConfirmationElapsedTime by g_frameElapsedTime and, once it reaches
   threshold g_profileGameSpeedPreview, clears a flag at g_matchRoundCounters+0x24 and reports the
   round over through Playerai_EndRound on the world 0x1860 bytes before it. */




void Playerai_EndRound(void *roundContext);

/* Sets labelItem's label field to the address of g_profileFirstConfirmationLabel and returns 0. */




/* Sets labelItem's label field to the address of g_profileSecondConfirmationLabel and returns 0. */




/* Clears g_fragTagSelectionState, runs Control_DisableControllerPakDe on the value at 0x4 of the menu's widget and then Control_ResetControllerPakDe and Control_SetProfileModeDe(widget, 1) on the widget itself, clears the flag at 0x85C of the owner at 0x1C, and returns 1. */








extern void Control_DisableControllerPak(int controllerPort);




/** Report whether the tutorial-progress flags (at 0x1c, 0x20, 0x28) hold any nonzero bit. */




/** Runs Menu_AdjustValue on a byte in menuContext->owner->controls[0x83] and writes the result back into that byte. */



void CMenuProfile_ActivateFirstConfirmingPlayer(void) {
    StatusStep *status;
    PlayerSettings *settings;
    s32 i;
    s32 active;
    i = 7;
    status = g_gameSettingsRecordActiveFlagBase;
    for (; i >= 0; i--) {
        ((StatusView *)status)->active = 0;
        status--;
    }
    i = 0;
    active = 1;
    settings = g_playerSettings;
    for (; i < 4; i++) {
        if (Control_IsAButtonPressed(&g_controllerProfiles[i]) != 0) {
            settings[i].active = active;
            settings[i].selected = i;
            break;
        }
    }
}

ControllerProfile *CMenuProfile_FindConfirmingController(s32 *out) {
    s32 i;
    ControllerProfile *s;
    i = 0;
    s = g_controllerProfiles;
    while (i < 4) {
        if (Control_IsAButtonPressed(s) != 0) {
            *out = i;
            return s;
        }
        i++;
        s++;
    }
    *out = -1;
    return 0;
}

s32 CMenuProfile_CountReadyConnectedPlayers(void) {
    char *rosterRecord;
    s32 controllerIndex;
    s32 connectedCount;
    s32 controllerOffset;

    connectedCount = 0;
    controllerIndex = 0;
    rosterRecord = (char *)&g_gameSettings;
    controllerOffset = 0;
loop_1:
    if (*(s32 *) ((char *) g_controllerProfiles + controllerOffset) != 0) {
        connectedCount += 1;
        if (((FlaggedRosterView *)rosterRecord)->flag == 0) {
            return 0;
        }
    }
    rosterRecord += sizeof(Shared_PlayerSettingsRecord);
    controllerIndex += 1;
    controllerOffset += 548;
    if (controllerIndex >= 4) {
        return connectedCount;
    }
    goto loop_1;
}

/** Clears the global counter/flag g_profileConfirmationElapsedTime. */
void CMenuProfile_ResetRoundEndDelay(void) {
    g_profileConfirmationElapsedTime = 0;
}

s32 CMenuProfile_UpdateRoundEndDelay(void) {
    f32 time;
    CGameStatus *base;

    time = g_profileConfirmationElapsedTime + g_frameElapsedTime;
    g_profileConfirmationElapsedTime = time;
    if ((120.0f) <= time) {
        base = &g_gameSettings.counters;
        base->teams = 0;
        Playerai_EndRound((void *) ((char *) base - ((char *)&((Shared_MenuData *)0)->game.counters - (char *)0)));
        return 1;
    }
    return 0;
}

s32 CMenuProfile_SetFirstResultLabel(MenuLabelPointerView *labelItem) {
    labelItem->label = &g_profileFirstConfirmationLabel;
    return 0;
}

s32 CMenuProfile_SetSecondResultLabel(MenuLabelPointerView *labelItem) {
    labelItem->label = &g_profileSecondConfirmationLabel;
    return 0;
}

/* Always returns 0. */

s32 CMenuProfile_ControllerSelectionReturnZero(void) {
    return 0;
}

/** True if any of three flags inside the g_matchRoundCounters record are set. */
s32 CMenuProfile_HasRoundProgress(void) {
    CGameStatus *base = &g_gameSettings.counters;
    s32 result;

    result = 0;
    if ((base->round != 0) || (base->elapsed != 0) || (base->state != 0)) {
        result = 1;
    }
    return result;
}

s32 CMenuProfile_ResetPlayerControllerProfile(s32 unused0, PlayerProfileMenuContext *menu) {
    PakMenuSlot **slot;

    g_gameSettings.counters.m_FragTagMode = 0;
    slot = &menu->widget;
    Control_DisableControllerPak((*slot)->controllerPort);
    Control_ResetControllerPak(*slot);
    Control_SetProfileMode(*slot, 1);
    menu->owner->playerStateDirty = 0;
    return 1;
}

s32 CMenuProfile_HasSavedRoundProgress(void) {
    s32 hasProgress;
    CGameStatus *state;

    state = &g_gameSettings.counters;
    hasProgress = 0;
    if ((state->round != 0) || (state->elapsed != 0) || (state->state != 0)) {
        hasProgress = 1;
    }
    return hasProgress;
}

s32 CMenuProfile_AdjustControllerSelection(void *menuItem, void *menuContext) {
    Shared_ActorView *p;
    u8 *bytep;
    s32 result;

    p = (void *)((PlayerProfileMenuContext *)menuContext)->owner;
    bytep = &p->controls->selection;
    result = Menu_AdjustValue(menuContext, *bytep, 1, 0, 10, 0);
    *bytep = (u8)result;
    return 0;
}
