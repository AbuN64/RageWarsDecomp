#ifndef COMMON_SHARED_MENUREPLY_H
#define COMMON_SHARED_MENUREPLY_H
#include "Common/world.h"
#include "types.h"
#include "Common/shared_optionsscreen.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/ballisticparams.h"
#include "Common/screen.h"
#include "Common/globals.h"
#include "Common/animation.h"

struct Shared_MenuReply;
struct Shared_OptionsScreen;
int Cinema_IsSequenceInWindow(void);
void Cache_SetResourceActivityState(unsigned int);
void Menu_SetFocusedElement(s32);
void Tsmos_ActivateControllerState(void);
#include "Smp/smp_flicker.h"
s32 Frontend_GetMenuImageState(s32 *record);
struct CPlayerPool_t;
void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
void Pools_ResetActorPools(struct ScreenMessageOwner *owner, s32 actorCount);
void SmXlate_SwitchScreen(s32);

extern struct Shared_MenuReply g_selectionMessageReply;

extern struct Shared_OptionsScreen *g_optionsShortcutScreen;

/* Advances the menu transition and dispatches the selected level once its animations finish. */
#endif
