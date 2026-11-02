#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_DISPATCHOPTIONSPAGEEVENT.H"

/* Dispatches event eventKind through this file's 12-byte handler table, whose rows hold an event at g_gameOptionsEventKinds, an actor kind at g_gameOptionsActorKinds and a handler at g_gameOptionsEventHandlers: the first row whose event equals eventKind and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*GameOptionsEventHandler)(void *, s32, s32, s32, s32);


extern GameOptionsEventHandler g_gameOptionsEventHandlers;




s32 Frontend_DispatchOptionsPageEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    GameOptionsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_gameOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_gameOptionsEventHandlers;
        index = 0;
        do {
            if (g_gameOptionsEventKinds[index].value == eventKind) {
                actor = menuActor;
                actor_kind = actor->input;
                table_kind = g_gameOptionsActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(menuActor, eventKind, eventDataOne, eventDataTwo, eventDataThree);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "FRONTEND/GAME_OPTIONS_LABELS.H"
#include "FRONTEND/OPTIONS_LIST_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView (*(SliderSettings *)&g_gameSettings)

/* Builds screen state g_gameOptionsScreenState: allocates its 0x10 bytes, registers resources (0x1BD - OPTIONS_RESOURCE_SHIFT) and (0x1C2 - OPTIONS_RESOURCE_SHIFT),
   creates list 0x1BB/0x1BC at 0x4 with the three texts gameOptionsLabel(0), gameOptionsLabel(1) and gameOptionsLabel(2) and
   selects byte 0x1B of the settings g_gameSettings, creates list (0x1BE - OPTIONS_RESOURCE_SHIFT)/(0x1BF - OPTIONS_RESOURCE_SHIFT) at 0x8 with gameOptionsLabel(3),
   plus gameOptionsLabel(4) and gameOptionsLabel(5) unless Defs_GetMemorySize reports 0x400000, and selects settings byte
   0x580, creates the 0x80-step slider (0x1C0 - OPTIONS_RESOURCE_SHIFT)/(0x1C1 - OPTIONS_RESOURCE_SHIFT) at 0x0 set to the settings word at 0x10,
   registers (0x1C3 - OPTIONS_RESOURCE_SHIFT) and (0x1C4 - OPTIONS_RESOURCE_SHIFT), clears the word at 0xC, resets through Tsmos_DeactivateControllerState and returns
   zero. */
struct SliderScreen {
    s32 slider;
    struct MenuListWidget *first_list;
    struct MenuListWidget *second_list;
    s32 state;
};

extern struct CompactOptionsCommitContext *g_gameOptionsScreenState;
typedef struct SliderSettings { char pad0[0x10]; s32 value; char pad14[7]; u8 first; char pad1C[0x564]; u8 second; } SliderSettings;
extern struct Record *Cache_AllocateMemory(s32 size);
extern void SmpButton_WrapButtonWidget(s32);
extern s32 Defs_GetMemorySize(void);
extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);
extern void SmpSlider_SetSliderItem(struct Scroll *scroll, s32 item);
extern void Tsmos_DeactivateControllerState(void);


s32 Frontend_CreateGameOptionsScreen(void) {

    SliderSettings *settings;
    struct MenuListWidget *list;
    s32 slider;

    g_gameOptionsScreenState = Cache_AllocateMemory(16);
    SmpButton_WrapButtonWidget((445 - OPTIONS_RESOURCE_SHIFT));
    SmpButton_WrapButtonWidget((450 - OPTIONS_RESOURCE_SHIFT));
    if (OPTIONS_HAS_FIRST_LIST) {
    list = SmpButton_CreateListWidget(443, 444);
    {struct MenuListWidget **handle = &g_gameOptionsScreenState->first_list; *handle = list;}
    SmpButton_AppendListText(g_gameOptionsScreenState->first_list, gameOptionsLabel(0));
    SmpButton_AppendListText(g_gameOptionsScreenState->first_list, gameOptionsLabel(1));
    SmpButton_AppendListText(g_gameOptionsScreenState->first_list, gameOptionsLabel(2));
    settings = &g_gameSettingsView;
    SmpButton_SelectListEntry(g_gameOptionsScreenState->first_list, settings->first);
    }
    list = SmpButton_CreateListWidget((446 - OPTIONS_RESOURCE_SHIFT), (447 - OPTIONS_RESOURCE_SHIFT));
    {struct MenuListWidget **handle = &g_gameOptionsScreenState->second_list; *handle = list;}
    SmpButton_AppendListText(g_gameOptionsScreenState->second_list, gameOptionsLabel(3));
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_gameOptionsScreenState->second_list, gameOptionsLabel(4));
        SmpButton_AppendListText(g_gameOptionsScreenState->second_list, gameOptionsLabel(5));
    }
    if (!OPTIONS_HAS_FIRST_LIST) settings = &g_gameSettingsView;
    SmpButton_SelectListEntry(g_gameOptionsScreenState->second_list, settings->second);
    slider = SmpSlider_CreateSliderWidget((448 - OPTIONS_RESOURCE_SHIFT), (449 - OPTIONS_RESOURCE_SHIFT), 128);
    g_gameOptionsScreenState->slider = slider;

    SmpSlider_SetSliderItem(slider, settings->value);
    SmpButton_WrapButtonWidget((451 - OPTIONS_RESOURCE_SHIFT));
    SmpButton_WrapButtonWidget((452 - OPTIONS_RESOURCE_SHIFT));
    g_gameOptionsScreenState->state = 0;
    Tsmos_DeactivateControllerState();
    return 0;
}
#endif
