#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
extern u8 *g_playerPartnerSuffixByLanguage[];
extern u8 *g_playerNamePrefixByLanguage[];
extern u8 *g_localizedPlayerNameSuffixes[];
extern u8 *g_playerNameSuffixByLanguage[];

/* Fills the record's eight-byte name from the language table the record's slot selects: slots 0 (and any
   slot out of range) to 3 pick the partner suffix, name prefix, localized suffix and name suffix tables; slots 4 to 7 leave the name alone. */
void Items_CopyDefaultLocalizedPlayerName(Shared_PlayerSettingsRecord *record) {
    s32 i;
    Shared_Game *game;

    switch ((s8)record->slot) {
    default:
    case 0:
        i = 0;
        game = &g_gameSettings;
        do {
            record->name[i] = g_playerPartnerSuffixByLanguage[game->language][i];
            i++;
        } while (i < 8);
        break;
    case 1:
        i = 0;
        game = &g_gameSettings;
        do {
            record->name[i] = g_playerNamePrefixByLanguage[game->language][i];
            i++;
        } while (i < 8);
        break;
    case 2:
        i = 0;
        game = &g_gameSettings;
        do {
            record->name[i] = g_localizedPlayerNameSuffixes[game->language][i];
            i++;
        } while (i < 8);
        break;
    case 3:
        i = 0;
        game = &g_gameSettings;
        do {
            record->name[i] = g_playerNameSuffixByLanguage[game->language][i];
            i++;
        } while (i < 8);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    }
}
#endif
