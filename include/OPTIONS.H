#ifndef OPTIONS_H
#define OPTIONS_H
#include "TYPES.H"




extern s32 CTrialCatalogue_DispatchOptionsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);

struct MatchOptionsScreen;
struct MatchOptionsScreen {
    s32 transition[7];
    void *selectWidget;
    void *cursorWidget;
    void *widget24;
    void *widget28;
    void *widget2C;
    void *widget30;
    void *widget34;
    s32 countCap;
    s32 countDefault;
};

extern u8*g_optionsPrimaryLocalizedLabels[1];
extern u8*g_optionsSecondaryLocalizedLabels;
#endif
