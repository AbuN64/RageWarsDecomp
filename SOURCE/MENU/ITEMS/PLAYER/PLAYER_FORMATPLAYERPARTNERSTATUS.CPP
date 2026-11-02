#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "include_asm.h"
#include "MENU/OBJECT1C8.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SOUNDINFO.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "../../../../sdk/include/AUDIO/sprintf.H"

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookOne(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookTwo(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookThree(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookFour(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookFive(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookSix(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookSeven(void) {
    return 0;
}

/* Calls SoundElement_DisableMusicGainOverride and passes what SoundVoicePool_GetGlobalState returns to SoundVoicePool_Resume; then, when g_controllerReturnPending
   is set, calls Menu_TryCreateMenu with the three arguments, otherwise Control_RestoreControllerSetup_FrontendDestroypausemenu. Returns one. */
extern s32 SoundVoicePool_GetGlobalState();
struct SoundVoicePool;
extern void SoundVoicePool_Resume(struct SoundVoicePool *);
extern void Menu_TryCreateMenu(void *, void *, void *);

s32 Player_RestoreControlsOrCreateMenu(void *first, void *second, void *third) {
    SoundElement_DisableMusicGainOverride();
    SoundVoicePool_Resume(SoundVoicePool_GetGlobalState());
    if (g_controllerReturnPending == 0) {
        Control_RestoreControllerSetup();
        return 1;
    }
    Menu_TryCreateMenu(first, second, third);
    return 1;
}

#include "MENU/PLAYER_STATUS_TEXT.H"
#include "TYPES.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#undef playerStatusText0
#define playerStatusText0() g_playerStatusMessage0Translations[g_languageIndex]
#undef playerStatusText1
#define playerStatusText1() g_playerStatusMessage1Translations[g_languageIndex]
#undef playerStatusText2
#define playerStatusText2() g_playerStatusMessage2Translations[g_languageIndex]
#undef playerStatusText3
#define playerStatusText3() g_playerStatusMessage3Translations[g_languageIndex]
#undef playerStatusText4
#define playerStatusText4() g_playerStatusMessage4Translations[g_languageIndex]
#undef playerStatusText5
#define playerStatusText5() g_playerStatusMessage5Translations[g_languageIndex]
#undef playerStatusText6
#define playerStatusText6() g_playerStatusMessage6Translations[g_languageIndex]
#undef playerStatusText7
#define playerStatusText7() g_playerStatusMessage7Translations[g_languageIndex]
#undef playerStatusText8
#define playerStatusText8() g_playerStatusMessage8Translations[g_languageIndex]
#undef playerStatusText9
#define playerStatusText9() g_playerStatusMessage9Translations[g_languageIndex]
#undef playerStatusText10
#define playerStatusText10() g_playerStatusMessage10Translations[g_languageIndex]
#undef playerStatusText11
#define playerStatusText11() g_playerStatusMessage11Translations[g_languageIndex]
#undef playerStatusText12
#define playerStatusText12() g_playerStatusMessage12Translations[g_languageIndex]
#undef playerStatusText13
#define playerStatusText13() g_playerStatusMessage13Translations[g_languageIndex]
#undef playerStatusText14
#define playerStatusText14() g_playerStatusMessage14Translations[g_languageIndex]
#endif
/* Formats a player's status line into a menu field's text through Libc_FormatString (sprintf): one message when the player is its own partner, otherwise a message chosen by the player's mode at 0x12F0 (0 to 6), naming the partner's character from 0x84 of its record at 0x5D8 when there is a partner. */
typedef struct StatusPlayer {
    char pad0[0x5D8];
    char *record;
    char pad5DC[0x12EC - 0x5DC];
    struct StatusPlayer *partner;
    unsigned int mode;
} StatusPlayer;

typedef struct {
    char pad0[0x10];
    char **text;
} Field;

typedef struct {
    char pad0[0x18];
    Field *field;
} Item;

typedef struct {
    char pad0[0x1C];
    StatusPlayer *player;
} Owner;


s32 Player_FormatPlayerPartnerStatus(Item *item, Owner *owner) {
    StatusPlayer *player = owner->player;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    char *text = item->field->text[g_languageIndex];
#else
    char *text = *item->field->text;
#endif
    if (player->partner == player) {
        Libc_FormatString(text, playerStatusText0());
    } else if (player->partner != 0) {
        switch (player->mode) {
        case 0: Libc_FormatString(text, playerStatusText1(), &((Shared_PlayerSettingsRecord *)player->partner->record)->name); break;
        case 1: Libc_FormatString(text, playerStatusText2(), &((Shared_PlayerSettingsRecord *)player->partner->record)->name); break;
        case 2: Libc_FormatString(text, playerStatusText3(), &((Shared_PlayerSettingsRecord *)player->partner->record)->name); break;
        case 3: Libc_FormatString(text, playerStatusText4(), &((Shared_PlayerSettingsRecord *)player->partner->record)->name); break;
        case 4: Libc_FormatString(text, playerStatusText5(), &((Shared_PlayerSettingsRecord *)player->partner->record)->name); break;
        case 5: Libc_FormatString(text, playerStatusText6(), &((Shared_PlayerSettingsRecord *)player->partner->record)->name); break;
        case 6: Libc_FormatString(text, playerStatusText7(), &((Shared_PlayerSettingsRecord *)player->partner->record)->name); break;
        }
    } else {
        switch (player->mode) {
        case 0: Libc_FormatString(text, playerStatusText8()); break;
        case 1: Libc_FormatString(text, playerStatusText9()); break;
        case 2: Libc_FormatString(text, playerStatusText10()); break;
        case 3: Libc_FormatString(text, playerStatusText11()); break;
        case 4: Libc_FormatString(text, playerStatusText12()); break;
        case 5: Libc_FormatString(text, playerStatusText13()); break;
        case 6: Libc_FormatString(text, playerStatusText14()); break;
        }
    }
    return 0;
}
