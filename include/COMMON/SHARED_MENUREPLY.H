#ifndef COMMON_SHARED_MENUREPLY_H
#define COMMON_SHARED_MENUREPLY_H
#include "COMMON/WORLD.H"
#include "TYPES.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SCREEN.H"
#include "COMMON/GLOBALS.H"
#include "COMMON/ANIMATION.H"

int Cinema_IsSequenceInWindow(void);
void Cache_SetResourceActivityState(unsigned int);
void Menu_SetFocusedElement(s32);
void Tsmos_ActivateControllerState(void);
void SmpFlicker_StartFlicker(struct FlickerStartView *object, s32 count);
s32 Frontend_GetMenuImageState(s32 *record);
void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);
void Scene_LoadLevelResources(void *, s32, s32);
void SmXlate_SwitchScreen(s32);

extern Shared_MenuReply g_selectionMessageReply;

extern Shared_OptionsScreen *g_optionsShortcutScreen;

/* Advances the menu transition and dispatches the selected level once its animations finish. */
#endif
