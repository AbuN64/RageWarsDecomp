#include "MENU/PLAYERSETTINGS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/CMENUPROFILE_OPENTIMEDPLAYERDIALOG.H"
#include "COMMON/SHARED_DEBUGFIELD.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "MENU/MISC/CMENUPROFILE_OPENTIMEDPLAYERDIALOG.H"

extern s32 Menu_AdjustValue(struct MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap);

extern void *Menu_AllocateMenu(struct MenuCreationOwnerView *owner, struct ParamsPakAllocateMenu *params, struct Dialog *list);

/* Points modeLabel's label field at g_profileModeZeroLabel or g_profileModeOneLabel when the mode byte at 0x7B of the owner's record is 0 or 1, and returns 0. */











/* Forwards pakMenu->widget->controllerPort to Control_EnableControllerPak_CmenuprofileOpentimedplayerdialog and clears g_pakPlayerMessagePending. */



extern s32 g_pakPlayerMessagePending;

extern void Control_EnableControllerPak(s32 kind);

/* Returns whether any of the words at offsets 0x28, 0x1C and 0x20 of g_matchRoundCounters is set. */



/* Restarts a round for the player passed in menuContext: clears the world timer flag g_pakPlayerMessagePending via
   Timer_ClearTimerFlag, cancels the active countdown sound through SoundElement_StopAudioExceptKey, then reallocates a
   fresh scoreboard entry via Menu_OpenDialog using menuContext's fields at 0x1C and 0x20, and always
   reports success. */

extern s32 g_matchEndingTeamWheelClose;

extern char g_pakProfileActionDialogResource[];

void Timer_ClearTimerFlag(void);

void *Menu_OpenDialog(void *parent, struct Dialog *list, s32 player, s32 controller, s32 d);

/** Runs a target's animation/state transition through Menu_AdjustValue and stores the new state. */
s32 CMenuProfile_ToggleProfileMode(void *menuItem, ProfileModeMenuContext *menuContext) {
    ProfileOptions *profileOptions;

    profileOptions = menuContext->selectionPlayer->characterKindView;
    profileOptions->profileMode = Menu_AdjustValue(menuContext, profileOptions->profileMode, 1, 0, 1, 1);
    return 0;
}

/** Forwards menuOwner through and menuContext as the first parameter, adding the g_profilePrimaryMenuResource record. */
s32 CMenuProfile_OpenPrimaryProfileMenu(void *unused0, void *menuOwner, void *menuContext) {
    Menu_AllocateMenu(menuContext, menuOwner, &g_profilePrimaryMenuResource);
    return 1;
}

s32 CMenuProfile_BindSelectedDebugField(Shared_DebugWidget *widget, Shared_MenuHandle *handle) {
    widget->field = g_profileSelectionResources[handle->selection->index];
    return 0;
}

/* Forwards menuOwner through and menuContext as the first parameter, adding the g_profileSecondaryMenuResource record. */
s32 CMenuProfile_OpenSecondaryProfileMenu(void *unused0, void *menuOwner, void *menuContext) {
    Menu_AllocateMenu(menuContext, menuOwner, &g_profileSecondaryMenuResource);
    return 1;
}

s32 CMenuProfile_UpdateProfileModeLabel(MenuLabelPointerView *modeLabel, MenuCMenuProfileUpdateProfileModeLabel *menu) {
    switch (menu->owner->record->mode) {
    case 0:
        modeLabel->label = &g_profileModeZeroLabel;
        break;
    case 1:
        modeLabel->label = &g_profileModeOneLabel;
        break;
    }
    return 0;
}

/** Forwards the pointed-to inner byte field on to Control_EnableControllerPak_CmenuprofileOpentimedplayerdialog. */
void CMenuProfile_EnableOwnerControllerPak(ControllerPortOwnerView *menuOwner) {
    Control_EnableControllerPak(menuOwner->controller->controllerPort);
}

void CMenuProfile_EnableControllerPakAndClearState(struct Shared_PakMenu *pakMenu) {
    Control_EnableControllerPak(pakMenu->owner->controllerPort);
    g_pakPlayerMessagePending = 0;
}

s32 CMenuProfile_HasProfileRoundProgress(void) {
    CGameStatus *state = &g_gameSettings.counters;

    return state->round != 0 || state->elapsed != 0 || state->state != 0;
}

s32 CMenuProfile_OpenTimedPlayerDialog(void *unused0, Arg1Struct *menuContext) {
    s32 val1C;

    val1C = menuContext->player;
    Timer_ClearTimerFlag();
    ((s32 (*)(s32))SoundElement_StopAudioExceptKey)(-1);
    Menu_OpenDialog(&g_matchEndingTeamWheelClose, &g_pakProfileActionDialogResource, val1C, menuContext->controller, 0);
    return 1;
}

/** Return 0. */
s32 CMenuProfile_ProfileModeReturnZero(void) {
    return 0;
}
