#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "ENGINE/SETN64.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* The EU builds pick the text for the current menu language. */
#define LINES_TEXT g_introTextLinesByLanguage[g_languageIndex]
#else
#define LINES_TEXT g_introTextLines
#endif
void SetN64_DrawCenteredIntroText(void *state) {
    SetN64_DrawTextLines(state, 1, LINES_TEXT, g_hudReferenceViewportWidth / 2, 5, 10, 0.75f, 1.0f);
}
