#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"

#if defined(VERSION_EU_X)
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
extern char *g_optionsLocalizedShortcutText[];
extern void MarkMenuEventHandled(void *);
extern void *Node_FindWidgetByResourceId(void *, s32);
extern s32 SoundElement_PlayFlatSound(s32);
typedef struct { u8 pad0[0x38]; char *text; } LangItemEu;
/* Language selector, previous entry: on the confirm press (press == 1) steps the language byte down (0 wraps to 2), shows the
   new language's label in item 0x5E and plays sound 0xE81. */
s32 Frontend_SelectPreviousLanguage(void *window, s32 b, s32 c, s32 press) {
    MarkMenuEventHandled(window);
    if (press != 1) {
        return 0;
    }
    {
        Shared_Game *g = &g_gameSettings;
        if (g->language == 0) g->language = 2; else g->language--;
    }
    ((LangItemEu *)Node_FindWidgetByResourceId(window, 94))->text = g_optionsLocalizedShortcutText[g_languageIndex];
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif

#if defined(VERSION_EU_X)
/* Language selector, next entry: as Frontend_SelectPreviousLanguage but steps the language byte up (2 wraps to 0). */
s32 Frontend_SelectNextLanguage(void *window, s32 b, s32 c, s32 press) {
    MarkMenuEventHandled(window);
    if (press != 1) {
        return 0;
    }
    {
        Shared_Game *g = &g_gameSettings;
        if (g->language == 2) g->language = 0; else g->language++;
    }
    ((LangItemEu *)Node_FindWidgetByResourceId(window, 94))->text = g_optionsLocalizedShortcutText[g_languageIndex];
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif
