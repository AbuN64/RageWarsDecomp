#include "Common/shared_gameslot.h"
#include "Common/game_session.h"
#include "Common/round_session.h"
#include "Render/sequence_prompt_state_views.h"
#include "types.h"
#include "Render/resident_texture_menu_views.h"
#include "Common/Lone/controller_rumble_pool.h"
#include "Common/residentstate.h"
#include "Engine/rumble.h"
#include "Engine/geometry.h"
#include "Engine/session.h"
#include "Common/sessionhandlerrow.h"
#include "engine.h"
#include "Engine/Cinema/cinema.h"
#include "Ai/player.h"

/* SIMPPOOL.CPP */

/* Opens the idle-time prompt when allowed and reports whether the pause input remains active. */


#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)

s32 Simppool_CheckSequencePromptRequest(struct SequencePromptRequestView *request) {
    s32 unusedInteger1;
    Prompt *prompt;

    if ((Menu_CountLiveNodes(&g_gameSession.match.messages.head) == 0) && (Cinema_IsSequenceInWindow() != 0)) {
        if (Cinema_GetSequenceRequest() == 120) {
            prompt = &((struct SequencePromptStateView *)&g_gameSession.match)->prompt;
            if (prompt->opened == 0) {
                if (request->suppressPrompt == 0) {
                    prompt->opened = 1;
                    Track_RequestCameraRefresh();
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

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
void Simppool_ResetEffectsAndControllers(void) {
    Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
    Playerai_ResetPlayerControllers(&g_playerViewRenderContext);
}
#endif
