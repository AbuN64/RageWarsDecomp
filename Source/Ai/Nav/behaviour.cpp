#include "Data/rest_source_records.h"
#include "Data/rom_callback_word.h"
#include "Common/ai_behaviour_types.h"
#include "Common/self.h"
#include "types.h"
#include "include_asm.h"
#include "Behaviour/behaviour.h"
#include "Ai/nav_symbols.h"

void Nav_RunBehaviorHandler(void *aiController) {
    s32 originalState;
    s32 stateIndex;
    s32 handlerIndex;
    RomCallbackWord *table;
    Handler handler;
    s32 handlerFinished;

    originalState = ((AiController *)aiController)->state;
    if ((u32)originalState >= 14) {
        ((AiController *)aiController)->state = 0;
    }
    stateIndex = ((AiController *)aiController)->state;
#if defined(VERSION_US)
    table = k_playerNavDirectionAndHandlerTable.behaviorRows[stateIndex];
#else
    table = g_aiCharacterBehaviorTables[stateIndex];
#endif
    if (table != 0) {
        handlerIndex = ((AiController *)aiController)->handlerIndex;
        handler = (Handler)table[handlerIndex].address;
        if (handler == 0) {
            ((AiController *)aiController)->handlerIndex = 0;
            handler = (Handler)table[0].address;
        }
        if (handler != 0) {
            handlerFinished = handler(aiController);
            if (handlerFinished != 0) {
                ((AiController *)aiController)->handlerIndex = ((AiController *)aiController)->handlerIndex + 1;
            }
            if (((AiController *)aiController)->state != originalState) {
                ((AiController *)aiController)->handlerIndex = 0;
            }
        }
    }
}

/* Resets a player's eight pairs of levels to g_behaviorInitialPlayerDistance, clears the word
  , sets 0x288 and loads 0x210 with g_behaviorInitialPlayerLevel, when the player exists and is active. */


void Nav_ResetWheelProbeState(struct WheelProbeState *player) {
    u32 i;

    if (player != 0 && player->active != 0) {
        for (i = 0; i < 8; i++) {
            player->first[i] = g_behaviorInitialPlayerDistance;
            player->second[i] = g_behaviorInitialPlayerDistance;
        }
        player->timer = 0;
        player->ready = 1;
        player->level = g_behaviorInitialPlayerLevel;
    }
}
