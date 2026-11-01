/* Encoded_HandleUnlockedLevelSelection, shared by the DE and the other versions' units; the includer defines levelBit() first. */
#include "COMMON/SHARED_MENUSELECTION.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAME_SESSION.H"
#include "OVLGAME/SHAREDRECAT224.H"

extern unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);

struct GameSession;
extern void SetN64_SelectSpawnAndStartSession(struct GameSession *menu, s32 target);
extern s32 SetN64_IsModeThirteen(void);

extern void Scene_SetSelection(void *menu, s32 target, s32 mode);

static inline s32 findUnlocked(s32 level, s32 step) {
    s32 i;

    for (i = 0; i < 11; i++) {
        level += step;
        if (level >= 11) {
            level = 0;
        } else if (level < 0) {
            level = 10;
        }
        if (g_gameSettings.unlockedLevels & levelBit(level)) {
            return level;
        }
    }
    return -1;
}

s32 Encoded_HandleUnlockedLevelSelection(s32 levelId, Shared_MenuInput *pad) {
    s32 target;
    Shared_Game *rules;

    switch (g_encodedSelectedLevelIndex) {
    default:
    case 0:
        target = 1000;
        break;
    case 1:
        target = 2000;
        break;
    case 2:
        target = 3000;
        break;
    case 3:
        target = 4000;
        break;
    case 4:
        target = 5000;
        break;
    case 5:
        target = 6000;
        break;
    case 6:
        target = 7401;
        break;
    case 7:
        target = 7501;
        break;
    case 8:
        target = 7601;
        break;
    case 9:
        target = 7602;
        break;
    case 10:
        target = 8000;
        break;
    }

    if (Control_IsAButtonPressed(pad->buttons) != 0) {
        if (target == 8000) {
            g_gameSettings.mode1E = 1;
            Confirming_SelectConfirmingController(pad);
            SetN64_SetTransitionTarget(&g_gameSession, 17);
            return 1;
        }
        if (SetN64_IsModeThirteen() != 0) {
            Scene_SetSelection(&g_world, target, 2);
            return 0;
        }
        rules = &g_gameSettings;
        rules->local = 0;
        rules->mode1E = 1;
        Confirming_SelectConfirmingController(pad);
        SetN64_SelectSpawnAndStartSession(&g_gameSession, target);
        return 1;
    }

    if (((s32 (*)(s32))Control_IsLeftPressed)(pad->buttons) != 0) {
        g_encodedSelectedLevelIndex = findUnlocked(g_encodedSelectedLevelIndex, -1);
    } else if (((s32 (*)(s32))Control_IsRightPressed)(pad->buttons) != 0) {
        g_encodedSelectedLevelIndex = findUnlocked(g_encodedSelectedLevelIndex, 1);
    }
    return 0;
}
