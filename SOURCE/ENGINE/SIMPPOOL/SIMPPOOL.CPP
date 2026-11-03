#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "RENDER/SEQUENCE_PROMPT_STATE_VIEWS.H"
#include "TYPES.H"
#include "RENDER/RESIDENT_TEXTURE_MENU_VIEWS.H"
#include "COMMON/LONE/CONTROLLER_RUMBLE_POOL.H"
#include "COMMON/RESIDENTSTATE.H"
#include "ENGINE/RUMBLE.H"

/* Opens the idle-time prompt when allowed and reports whether the pause input remains active. */


s32 Cinema_IsSequenceInWindow();                                /* extern */
unsigned int Cinema_GetPlaybackPauseState(void);                                /* extern */
s32 Cinema_GetSequenceRequest(void);                                /* extern */
void Track_RequestCameraRefresh(void *);                            /* extern */
int Menu_CountLiveNodes(struct CMenu_t **head);


extern SequencePromptStateView g_matchEndingTeamWheelClose;
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)

s32 Simppool_CheckSequencePromptRequest(SequencePromptRequestView *request) {
    s32 unusedInteger1;
    Prompt *prompt;

    if ((Menu_CountLiveNodes(&g_matchEndingTeamWheelClose) == 0) && (Cinema_IsSequenceInWindow() != 0)) {
        if (Cinema_GetSequenceRequest() == 120) {
            prompt = &g_matchEndingTeamWheelClose.prompt;
            if (prompt->opened == 0) {
                if (request->suppressPrompt == 0) {
                    prompt->opened = 1;
                    Track_RequestCameraRefresh(prompt);
                }
                goto block_6;
            }
            goto block_7;
        }
    }
block_6:
    if (g_gameSettings.counters.first != 0) {
block_7:
        if (Cinema_GetPlaybackPauseState() != 0) return 1;
    }
    return 0;
}
#endif
struct Context;
void Playerai_ResetPlayerControllers(struct Context *);

extern char g_playerViewRenderContext;
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
void Simppool_ResetEffectsAndControllers(void) {
    Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
    Playerai_ResetPlayerControllers(&g_playerViewRenderContext);
}
#endif
