#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include "FRONTEND/MENU_COMMITOPTIONSPAGE.H"

/* Refreshes the option block g_gameSettings from the menu g_optionsPage points to: the bytes at 0x1B, 0x1F
   and 0x580 from the selections SmpButton_GetListSelection reports for its items at 0xC, 0x10 and 0x14, and the
   word at 0x10 from the position SmpSlider_GetSliderItem reports for its item at 8. */





extern OptionsCommitContext *g_optionsPage;

extern s32 SmpButton_GetListSelection(s32 *record);

extern s32 SmpSlider_GetSliderItem(s32 *record);

/* Refreshes the option block g_gameSettings from the menu g_gameOptionsScreenState points to: the bytes at 0x1B and 0x580
   from the selections SmpButton_GetListSelection reports for its items at 4 and 8, and the word at 0x10 from
   the position SmpSlider_GetSliderItem reports for its item at 0. */







extern CompactOptionsCommitContext *g_gameOptionsScreenState;

/* Refreshes the option block g_gameSettings from the menu g_optionsShortcutScreen points to: the bytes at 0x1B and 0x580
   from the selections SmpButton_GetListSelection reports for its items at 0x54 and 0x58, and the word at 0x10 from
   the position SmpSlider_GetSliderItem reports for its item at 0x50. */







extern struct Shared_OptionsScreen *g_optionsShortcutScreen;

void Menu_CommitOptionsPage(void) {
    Shared_Game *options;
    s32 value;

#if defined(VERSION_DE)
    value = SmpButton_GetListSelection(g_optionsPage->twoPlayerScreenList);
    options = &g_gameSettings;
    options->twoPlayerScreenPreference = value;
#else
    value = SmpButton_GetListSelection(g_optionsPage->bloodModeList);
    options = &g_gameSettings;
    options->bloodMode = value;
    options->twoPlayerScreenPreference = SmpButton_GetListSelection(g_optionsPage->twoPlayerScreenList);
#endif
    options->resolution = SmpButton_GetListSelection(g_optionsPage->resolutionList);
    options->lightingGamma = SmpSlider_GetSliderItem(g_optionsPage->gammaSlider);
}

void Menu_CommitCompactOptionsPage(void) {
    Shared_Game *options;
    s32 value;

#if defined(VERSION_DE)
    value = SmpButton_GetListSelection(g_gameOptionsScreenState->resolutionList);
    options = &g_gameSettings;
    options->resolution = value;
#else
    value = SmpButton_GetListSelection(g_gameOptionsScreenState->bloodModeList);
    options = &g_gameSettings;
    options->bloodMode = value;
    options->resolution = SmpButton_GetListSelection(g_gameOptionsScreenState->resolutionList);
#endif
    options->lightingGamma = SmpSlider_GetSliderItem(g_gameOptionsScreenState->gammaSlider);
}

void Menu_CommitTabOptionsPage(void) {
    Shared_Game *options;
    s32 value;

#if defined(VERSION_DE)
    value = SmpButton_GetListSelection(g_optionsShortcutScreen->resolutionList);
    options = &g_gameSettings;
    options->resolution = value;
#else
    value = SmpButton_GetListSelection(g_optionsShortcutScreen->bloodModeList);
    options = &g_gameSettings;
    options->bloodMode = value;
    options->resolution = SmpButton_GetListSelection(g_optionsShortcutScreen->resolutionList);
#endif
    options->lightingGamma = SmpSlider_GetSliderItem(g_optionsShortcutScreen->gammaSlider);
}
