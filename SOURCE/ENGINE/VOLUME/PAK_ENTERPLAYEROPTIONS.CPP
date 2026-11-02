#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENURECAT20V1.H"
#include "MULTI/SETUP_SETUPNAMESPINNER.H"
#include "TYPES.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "MENU/PAK/pak_menu_entries.H"
#include "ENGINE/VOLUME.H"

/* Sets a player state to 2, then in multiplayer (g_motionVisibilitySettings) clears and otherwise sets bit 0x800000 in both of its actor's visibility masks at 0x80 and 0xA8, and refreshes the audio state through SoundVoicePool_GetGlobalState and SoundVoicePool_Pause with that mask. */





extern s32 SoundVoicePool_GetGlobalState(s32 mask);
extern void SoundVoicePool_Pause(s32 value);

void Pak_EnterPlayerOptions(PlayerOptionsEntry *player) {
    s32 mask;

    player->state = 2;
    Control_SaveControllerSetup();
    mask = 0x800000;
    if (g_gameSettings.local != 0) {
        mask = 0xFF7FFFFF;
        player->actor->mask80 &= mask;
        player->actor->maskA8 &= mask;
    } else {
        player->actor->mask80 |= mask;
        player->actor->maskA8 |= mask;
    }
    SoundVoicePool_Pause(SoundVoicePool_GetGlobalState(mask));
}

/* Calls Control_RestoreControllerSetup_FrontendDestroypausemenu and nothing else. */

void Pak_RestoreControllerSetup(void) {
    Control_RestoreControllerSetup();
}

/* Calls Menu_DrawMenuEntries and nothing else. */

void Pak_RenderMenuEntryCallback(struct MenuStyle *menu, s8 *member) {
    Menu_DrawMenuEntries(menu, member);
}


