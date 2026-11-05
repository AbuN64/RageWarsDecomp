#ifndef ACHIEVE_ACHIEVE_ADVANCERESULTMODELPREVIEW_H
#define ACHIEVE_ACHIEVE_ADVANCERESULTMODELPREVIEW_H
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
struct SelectionMessageScreen {
    MenuRules rules;
    char pad20[0x24 - 0x20];
    void *item;
    char pad28[0x90 - 0x28];
    s32 started;
    char pad94[0x9C - 0x94];
    s32 first;
    char padA0[0xB0 - 0xA0];
    s32 second;
    char padB4[0x188 - 0xB4];
    s32 third;
    char pad18C[0x1C0 - 0x18C];
    s32 busy;
};
extern void Achieve_AdvanceResultModelPreview(void);
#endif
