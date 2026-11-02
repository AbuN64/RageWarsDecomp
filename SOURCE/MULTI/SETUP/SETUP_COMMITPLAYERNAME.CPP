#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "include_asm.h"

#include "COMMON/MENURECAT20V1.H"
#include "MULTI/SETUP_SETUPNAMESPINNER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "MULTI/SETUP_HASACTIVEGAMECOUNTERS.H"

/* Deletes the final character of the selected player's text entry: resets its cursor and, when the entry holds characters, decrements the count and length and clears the character at the new end. */







extern PlayerNameTextEntry g_multiplayerNameEntryStates[];

/* Copies a player label with spaces for empty characters and refreshes the entry. */




#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern void Menu_TryCreateMenu(s32,NameEditMenuContext *,s32), Items_CopyDefaultLocalizedPlayerName(void *);
#else
extern void Menu_TryCreateMenu(s32,NameEditMenuContext *,s32), Items_SetDefaultPlayerName(void *);
#endif

extern s32 Player_GetPlayerIndex(void *table, void *player);
extern u8 g_playerViewRenderContext[];
/* Returns 1 when any of the words at 0x28, 0x1C or 0x20 of g_matchRoundCounters is nonzero, else 0. */




s32 Setup_DeleteNameCharacter(s32 unused, NameEditMenuContext *menuEntry) {
    s32 i;
    s32 count;

    i = Player_GetPlayerIndex(g_playerViewRenderContext, menuEntry->profileOwner);
    count = g_multiplayerNameEntryStates[i].count;
    g_multiplayerNameEntryStates[i].cursor = 0;
    if (count == 0) {
        return 0;
    }
    g_multiplayerNameEntryStates[i].count = count - 1;
    g_multiplayerNameEntryStates[i].length--;
    g_multiplayerNameEntryStates[i].text[g_multiplayerNameEntryStates[i].length] = 0;
    return 0;
}

s32 Setup_CommitPlayerName(s32 first, NameEditMenuContext *second, s32 third) {
    s32 playerIndexResult;
    s32 characterIndex;
    s32 nonemptyCharacters;
    u8 *sourceName;
    u8 *destinationName;
    u8 character;
    PlayerNameProfileView *player;

    player = second->profileOwner;
    playerIndexResult = Player_GetPlayerIndex(g_playerViewRenderContext, player);
    sourceName = (playerIndexResult * sizeof(SavedPlayerName)) + g_multiplayerSavedPlayerNames;
    destinationName = (playerIndexResult * sizeof(Shared_PlayerSettingsRecord)) + (g_playerViewRenderContext + ((char *)&((Shared_MenuData *)0)->game.playerSettings[0].name - (char *)0));
    nonemptyCharacters = 0;
    characterIndex = 0;
    do {
        character = *sourceName;
        sourceName += 1;
        if (character == 0) {
            character = 32;
        } else {
            nonemptyCharacters += 1;
        }
        *destinationName = character;
        characterIndex += 1;
        destinationName += 1;
    } while (characterIndex < 8);
    *destinationName = 0;
    if (nonemptyCharacters == 0) {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
Items_CopyDefaultLocalizedPlayerName
#else
Items_SetDefaultPlayerName
#endif
(player->profile);
    }
    Menu_TryCreateMenu(first, second, third);
    return 1;
}

s32 Setup_HasActiveGameCounters(void) {
    CGameStatus *s = &g_gameSettings.counters;
    s32 ret;

    ret = 0;
    if (s->round != 0 || s->elapsed != 0 || s->state != 0) {
        ret = 1;
    }
    return ret;
}
