#include "Common/ballisticparams.h"
#include "Common/reserved_shared_declarations.h"
#include "Common/Lone/resident_choice_screen.h"
#include "types.h"
#include "Scene/cache_freememory.h"
#include "Common/gameplay_camera.h"
#include "Common/shared_optionsscreen.h"
#include "Common/screen.h"
#include "Common/menu_match_globals.h"
#include "Common/world.h"
#include "Frontend/menuimage.h"
#include "Frontend/menu_image.h"
#include "Common/shared_menureply.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Common/statepair.h"
#include "Cache/cache_allocresourceblock.h"
#include "Common/game_session.h"
#include "Frontend/screen.h"
#include "include_asm.h"
#include "Common/aiprofile.h"
#include "Frontend/frontend_dispatchresidentactorevent.h"
#include "Common/selectionscreenstate.h"
#include "Common/runtime_declarations.h"
#include "Scenariosetupscreen/scenariosetupscreen.h"
#include "Frontend/frontend_address_symbols.h"

/* unit FRONTEND_FREEPAGE67SCREEN.CPP */
/* Releases the object g_residentChoiceScreen holds through Cache_FreeMemory, clears g_residentChoiceScreen, calls Tsmos_SetMenuModelFlag with 2
   and returns zero. */
s32 Frontend_FreePage67Screen(void) {
    Cache_FreeMemory(g_residentChoiceScreen);
    g_residentChoiceScreen = 0;
    Tsmos_SetMenuModelFlag(2);
    return 0;
}

/* unit FRONTEND_UPDATEPAGE67EXIT.CPP */
/* Calls Tsmos_SetMenuModelFlag with 2 and returns zero. */
s32 Frontend_ClearPage67ModeFlag(void) {
    Tsmos_SetMenuModelFlag(2);
    return 0;
}

/* Event callback for screen g_residentChoiceScreen: on event 1 while Frontend_GetMenuImageState reports the screen in state
   1 it advances the screen through Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition, and when that leaves it in
   state 2 it calls MarkMenuEventHandled, clears the pause word g_simpleObjectPauseState (0x180C past the match objects
   at g_frontendScreenStatus), stops those objects and the ones 0x48 bytes before them, releases resource 0x24
   of g_world_AchieveUpdateresultsscreen, restarts Cache_SetResourceActivityState when Cache_GetResourceActivityState reports it idle, and calls
   SoundElement_DisableMusicGainOverride and Stage_StartConfiguredMatch. Returns zero. */
s32 Frontend_UpdatePage67Exit(s32 element, s32 eventId, s32 event) {
    s32 *pause;
    if (event == 1) {
        if (Frontend_GetMenuImageState(g_residentChoiceScreen) != 1) {
            return 0;
        }
        Frontend_DrawMenuImage(g_residentChoiceScreen);
        Frontend_AdvanceMenuImageTransition(g_residentChoiceScreen);
        if (Frontend_GetMenuImageState(g_residentChoiceScreen) != 2) {
            return 0;
        }
        MarkMenuEventHandled();
        pause = &g_playerViewRenderContext.pause;
        *pause = 0;
        Pools_ResetActorPools(&g_playerViewRenderContext.object, 0);
        Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
        Scene_LoadLevelResources(&g_world, 36, 0);
        if (Cache_GetResourceActivityState() == 0) {
            Cache_SetResourceActivityState(1);
        }
        SoundElement_DisableMusicGainOverride();
        Stage_StartConfiguredMatch();
    }
    return 0;
}

/* unit FRONTEND_HANDLEPAGE67CHOICE.CPP */
/* Event handler placeholder: ignores the event and returns zero. */
s32 Frontend_IgnorePage67Event(void) {
    return 0;
}

/* Calls MarkMenuEventHandled with the arguments it was given and returns zero. */
s32 Frontend_AcknowledgePage67Event(void) {
    MarkMenuEventHandled();
    return 0;
}

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x3D8 clears g_simpleObjectPauseState, calls Tsmos_DeactivateControllerState, then calls Frontend_StartMenuImageTransition on g_residentChoiceScreen when ScenarioSetup_StartRandomCupStage reports non-zero or else Frontend_RequestScreenMode_AchieveUpdateresultsscreen with zero and SmXlate_SwitchScreen with 0x14; 0x3D9 calls SmXlate_SwitchScreen with one. Returns zero. */

#if defined(VERSION_DE)
enum { MENU_PAGE67_START_RANDOM_CUP_STAGE = 978, MENU_PAGE67_SWITCH_SCREEN = 979 };
#elif defined(VERSION_EU_X)
enum { MENU_PAGE67_START_RANDOM_CUP_STAGE = 988, MENU_PAGE67_SWITCH_SCREEN = 989 };
#else
enum { MENU_PAGE67_START_RANDOM_CUP_STAGE = 984, MENU_PAGE67_SWITCH_SCREEN = 985 };
#endif

s32 Frontend_HandlePage67Choice(void) {
    MarkMenuEventHandled();
    switch (Menu_GetFocusedElementId()) {
    case MENU_PAGE67_SWITCH_SCREEN:
        SmXlate_SwitchScreen(1);
        return 0;
    case MENU_PAGE67_START_RANDOM_CUP_STAGE:
        g_gameSession.clockPaused = 0;
        Tsmos_DeactivateControllerState();
        if (ScenarioSetup_StartRandomCupStage() == 0) {
            Frontend_RequestScreenMode(0);
            SmXlate_SwitchScreen(20);
        } else {
            Frontend_StartMenuImageTransition(g_residentChoiceScreen);
        }
        return 0;
    }
    return 0;
}

#if !(defined(VERSION_US))
/* Calls the handler registered for eventKind (tables g_residentEventEntries, g_residentActorEventKinds, g_residentActorEventHandlers). A row matches when its event equals eventKind and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */


s32 Frontend_DispatchResidentActorEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    ResidentActorEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_residentActorEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_residentActorEventHandlers;
        index = 0;
        do {
            if (g_residentEventEntries[index].value == eventKind) {
                actor = menuActor;
                actor_kind = actor->resource;
                table_kind = g_residentActorEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(menuActor, eventKind, eventDataOne, eventDataTwo, eventDataThree);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
#endif

/* unit FRONTEND_DISPATCHRESIDENTACTORTABLEEVENT.CPP */
#if defined(VERSION_US)
#include "Common/resident_event_handler.h"
#include "Common/multiplayeroptions.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"

s32 Frontend_DispatchResidentActorTableEvent(ActorDefinitionHeader *actor, s32 event, s32 eventArg2, s32 eventArg3, s32 eventArg4) {
    s32 index;
    index = 0;
    if (g_residentEventEntries[index].handler != 0) {
        do {
            if (g_residentEventEntries[index].event == event) {
                if (g_residentEventEntries[index].actorKind == actor->character || g_residentEventEntries[index].actorKind == 30000) {
                    return g_residentEventEntries[index].handler(actor, event, eventArg2, eventArg3, eventArg4);
                }
            }
            index++;
        } while (g_residentEventEntries[index].handler != 0);
    }
    return 0;
}
#endif
