#ifndef FRONTEND_JOIN_PLAYER_NAMES_H
#define FRONTEND_JOIN_PLAYER_NAMES_H
#include "TYPES.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
typedef struct JoinNameEntry { u8 **names; s32 pad; } JoinNameEntry;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern u8 *g_characterPreviewTextReferenceEu1[], *g_slotSelectionTextReferenceEu4[];
extern JoinNameEntry g_joinPlayerNamesLocalized[];
#else
extern u8 *g_characterPreviewTextReferenceShared1[], *g_slotSelectionTextReferenceShared3[];
extern JoinNameEntry g_joinPlayerNamesDefault[];
#endif
static inline u8 *joinName15(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_characterPreviewTextReferenceEu1[g_languageIndex];
#else
    return g_characterPreviewTextReferenceShared1[0];
#endif
}
static inline u8 *joinName16(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_slotSelectionTextReferenceEu4[g_languageIndex];
#else
    return g_slotSelectionTextReferenceShared3[0];
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
