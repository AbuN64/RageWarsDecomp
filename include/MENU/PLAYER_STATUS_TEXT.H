#ifndef MENU_PLAYER_STATUS_TEXT_H
#define MENU_PLAYER_STATUS_TEXT_H
#include "TYPES.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_playerStatusMessage0Translations[];
extern char *g_playerStatusMessage1Translations[];
extern char *g_playerStatusMessage2Translations[];
extern char *g_playerStatusMessage3Translations[];
extern char *g_playerStatusMessage4Translations[];
extern char *g_playerStatusMessage5Translations[];
extern char *g_playerStatusMessage6Translations[];
extern char *g_playerStatusMessage7Translations[];
extern char *g_playerStatusMessage8Translations[];
extern char *g_playerStatusMessage9Translations[];
extern char *g_playerStatusMessage10Translations[];
extern char *g_playerStatusMessage11Translations[];
extern char *g_playerStatusMessage12Translations[];
extern char *g_playerStatusMessage13Translations[];
extern char *g_playerStatusMessage14Translations[];
#else
extern char *g_playerStatusMessage0;
extern char *g_playerStatusMessage1;
extern char *g_playerStatusMessage2;
extern char *g_playerStatusMessage3;
extern char *g_playerStatusMessage4;
extern char *g_playerStatusMessage5;
extern char *g_playerStatusMessage6;
extern char *g_playerStatusMessage7;
extern char *g_playerStatusMessage8;
extern char *g_playerStatusMessage9;
extern char *g_playerStatusMessage10;
extern char *g_playerStatusMessage11;
extern char *g_playerStatusMessage12;
extern char *g_playerStatusMessage13;
extern char *g_playerStatusMessage14;
#endif
static inline char *playerStatusText0(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage0Translations[g_languageIndex];
#else
    return g_playerStatusMessage0;
#endif
}
static inline char *playerStatusText1(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage1Translations[g_languageIndex];
#else
    return g_playerStatusMessage1;
#endif
}
static inline char *playerStatusText2(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage2Translations[g_languageIndex];
#else
    return g_playerStatusMessage2;
#endif
}
static inline char *playerStatusText3(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage3Translations[g_languageIndex];
#else
    return g_playerStatusMessage3;
#endif
}
static inline char *playerStatusText4(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage4Translations[g_languageIndex];
#else
    return g_playerStatusMessage4;
#endif
}
static inline char *playerStatusText5(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage5Translations[g_languageIndex];
#else
    return g_playerStatusMessage5;
#endif
}
static inline char *playerStatusText6(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage6Translations[g_languageIndex];
#else
    return g_playerStatusMessage6;
#endif
}
static inline char *playerStatusText7(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage7Translations[g_languageIndex];
#else
    return g_playerStatusMessage7;
#endif
}
static inline char *playerStatusText8(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage8Translations[g_languageIndex];
#else
    return g_playerStatusMessage8;
#endif
}
static inline char *playerStatusText9(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage9Translations[g_languageIndex];
#else
    return g_playerStatusMessage9;
#endif
}
static inline char *playerStatusText10(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage10Translations[g_languageIndex];
#else
    return g_playerStatusMessage10;
#endif
}
static inline char *playerStatusText11(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage11Translations[g_languageIndex];
#else
    return g_playerStatusMessage11;
#endif
}
static inline char *playerStatusText12(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage12Translations[g_languageIndex];
#else
    return g_playerStatusMessage12;
#endif
}
static inline char *playerStatusText13(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage13Translations[g_languageIndex];
#else
    return g_playerStatusMessage13;
#endif
}
static inline char *playerStatusText14(void) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    return g_playerStatusMessage14Translations[g_languageIndex];
#else
    return g_playerStatusMessage14;
#endif
}
#endif
