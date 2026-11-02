#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "TYPES.H"
#include <ultra64.h>
#include "FRONTEND/FRONTEND_CHECKOWNEDPROFILEIDS.H"

/* Checks that every active player on the selected team has the configured value. */
extern s32 g_profileSlotResetWord[]; extern s8 g_profileSlotIndices[];
extern s32 g_profileSlotResetWord[]; extern s8 g_profileSlotEnabledFlags[];
s32 Frontend_CheckOwnedProfileIds(s32 player) {
    s32 profileOffset;
    s32 profileIndex;
    s32 allMatch;
    allMatch = 1;
    profileIndex = 0;
    profileOffset = 0;
    do {
        if ((*(g_profileSlotEnabledFlags + profileOffset) == 0) && (*(g_profileSlotIndices + profileOffset) == player) && (*(s32 *)((char *)g_profileSlotResetWord + profileOffset) != g_pakProfileScreenState->players[player].profile)) {
            allMatch = 0;
        }
        profileIndex += 1;
        profileOffset += 400;
    } while (profileIndex < 4);
    return allMatch;
}
