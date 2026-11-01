#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/WORLD.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ACTIVE.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "TYPES.H"
#include "FRONTEND/RANDOM_CHOOSERANDOMCHARACTER.H"
#include "UI/X_FILES/X_PLUS.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Returns 0xBC2 plus ten times either the halfword at offset 2 of what Scene_GetBlLevelData finds for
   g_selectedLevelId in g_world_AchieveUpdateresultsscreen, when the option byte g_gameControllerMode is one, or g_selectedLevelId itself. */



extern struct StateFlags *Scene_GetBlLevelData(void *, s32);

s32 Random_GetStageTransitionResource(void) {
    return (g_gameSettings.controllerMode == 1 ? Scene_GetBlLevelData(&g_world, g_selectedLevelId)->flags : g_selectedLevelId) * 10 + 3010;
}

extern Shared_PlayerSettingsRecord g_playerSettings[];


/* Characters 0 and 5 may appear only once among the eight enabled players. */
static inline s32 characterAvailable(s32 character, s32 firstUniqueCharacter, s32 secondUniqueCharacter) {
    s32 available;
    s32 i;
    Shared_PlayerSettingsRecord *players = g_playerSettings;
    if (character == firstUniqueCharacter || character == secondUniqueCharacter) {
        for (available = 1, i = 0; i < 8; i++) {
            if (players[i].enabled && players[i].character == character) {
                available = 0;
            }
        }
    } else {
        available = 1;
    }
    return available;
}

s32 Random_ChooseRandomCharacter(void) {
    s32 character;
    do {
        character = Graphu64_NextRandom() % 11;
    } while (!characterAvailable(character, 0, 5));
    return character;
}

