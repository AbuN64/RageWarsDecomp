#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SELF.H"
#include "TYPES.H"
#include "include_asm.h"

typedef s32 (*Handler)(void *aiController);

extern Handler *g_aiCharacterBehaviorTables[];




void Nav_RunBehaviorHandler(void *aiController) {
    s32 origIdx;
    s32 idx;
    s32 idx2;
    Handler *table;
    Handler fn;
    s32 result;

    origIdx = ((AiController *)aiController)->state;
    if ((u32)origIdx >= 14) {
        ((AiController *)aiController)->state = 0;
    }
    idx = ((AiController *)aiController)->state;
    table = g_aiCharacterBehaviorTables[idx];
    if (table != 0) {
        idx2 = ((AiController *)aiController)->handlerIndex;
        fn = table[idx2];
        if (fn == 0) {
            ((AiController *)aiController)->handlerIndex = 0;
            fn = table[0];
        }
        if (fn != 0) {
            result = fn(aiController);
            if (result != 0) {
                ((AiController *)aiController)->handlerIndex = ((AiController *)aiController)->handlerIndex + 1;
            }
            if (((AiController *)aiController)->state != origIdx) {
                ((AiController *)aiController)->handlerIndex = 0;
            }
        }
    }
}

/* Resets a player's eight pairs of levels at offsets 0x1D0 and 0x1F0 to g_behaviorInitialPlayerDistance, clears the word
   at 0x1CC, sets 0x288 and loads 0x210 with g_behaviorInitialPlayerLevel, when the player exists and is active. */





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


