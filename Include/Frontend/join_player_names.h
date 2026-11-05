#ifndef FRONTEND_JOIN_PLAYER_NAMES_H
#define FRONTEND_JOIN_PLAYER_NAMES_H
#include "Data/Character_preview/character_preview.h"
#include "types.h"
#include "Common/Lone/g_languageindex.h"
struct JoinNameEntry;
typedef struct JoinNameEntry { u8 **names; s32 pad; } JoinNameEntry;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern u8 *g_characterNamesLocalized[], *g_slotRankNamePointers_Symbiont[];
extern struct JoinNameEntry g_joinPlayerNamesLocalized[];
#else
extern struct JoinNameEntry g_joinPlayerNamesDefault[];
extern char g_playerNamesSymbiontToClaw[];
#endif
static inline u8 *joinName15(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_characterNamesLocalized[g_languageIndex];
#else
    return *(u8 **)g_characterNames;
#endif
}
static inline u8 *joinName16(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_slotRankNamePointers_Symbiont[g_languageIndex];
#else
    return *(u8 **)g_playerNamesSymbiontToClaw;
#endif
}
static inline u8 *joinTeamName(s32 index) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_joinPlayerNamesLocalized[index].names[g_languageIndex];
#else
    return *g_joinPlayerNamesDefault[index].names;
#endif
}
#endif
