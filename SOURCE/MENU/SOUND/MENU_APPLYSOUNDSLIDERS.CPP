#include "COMMON/MENUSELECTIONMESSAGE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "TYPES.H"
extern struct SoundOptionsScreen *g_soundOptionsScreen;
extern void **g_soundOptionSliders;
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/MENU_DISPATCHSOUNDOPTIONSEVENT.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* Calls MarkMenuEventHandled, then sets the word at offset 0x14 of the object g_soundOptionsScreen points to to -1 and
   calls SmpSlider_SetTransitionMode on the object's first word with 2, returning zero. */



extern void MarkMenuEventHandled();

extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_soundOptionsEventIds, an actor kind at g_soundOptionsEventKinds and a handler at g_soundOptionsEventHandlers: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*SoundOptionsEventHandler)(void *, s32, s32, s32, s32);



extern SoundOptionsEventHandler g_soundOptionsEventHandlers;

/* Builds a two-slider menu: allocates eight bytes into g_soundOptionSliders through Cache_AllocateMemory, creates the
   sliders VALUE_1D5/VALUE_1D5+1 and VALUE_1D5+2/VALUE_1D5+3 through SmpSlider_CreateSliderWidget, stores them in the block and sets them
   to the option bytes g_gameSettingsVolumeBytes[0] and [1] through SmpSlider_SetSliderItem, then calls SmpButton_WrapButtonWidget with
   VV_01D3. Returns zero. */



extern struct Record *Cache_AllocateMemory(s32 size);

extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);

extern void SmpSlider_SetSliderItem(struct Scroll *scroll, s32 item);

/* Releases the object g_soundOptionSliders holds through Cache_FreeMemory, clears g_soundOptionSliders and returns zero. */



/* Updates the two menu options and plays their change sounds. */




extern s32 SmpSlider_GetSliderItem(s32 *record);



s32 Menu_CancelSoundOptionsScreen(void) {
    struct SoundOptionsScreen *state;

    MarkMenuEventHandled();
    state = g_soundOptionsScreen;
    state->target = -1;
    SmpSlider_SetTransitionMode(state->menu, 2);
    return 0;
}

s32 Menu_DispatchSoundOptionsEvent(void *eventTarget, s32 event, s32 itemId, s32 value, s32 context) {
    SoundOptionsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_soundOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_soundOptionsEventHandlers;
        index = 0;
        do {
            if (g_soundOptionsEventIds[index].value == event) {
                actor = eventTarget;
                actor_kind = actor->input;
                table_kind = g_soundOptionsEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, event, itemId, value, context);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

s32 Menu_CreateSoundSliders(void) {
    u8 *options;
    void *slider;
    g_soundOptionSliders = Cache_AllocateMemory(8);
#if defined(VERSION_DE)
    slider = SmpSlider_CreateSliderWidget(465, 465 + 1, 0xFF);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    slider = SmpSlider_CreateSliderWidget(469, 469 + 1, 0xFF);
#elif defined(VERSION_EU_X)
    slider = SmpSlider_CreateSliderWidget(472, 472 + 1, 0xFF);
#endif
    options = g_gameSettings.volume;
    g_soundOptionSliders[0] = slider;
    SmpSlider_SetSliderItem(slider, options[0]);
#if defined(VERSION_DE)
    slider = SmpSlider_CreateSliderWidget(465 + 2, 465 + 3, 0xFF);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    slider = SmpSlider_CreateSliderWidget(469 + 2, 469 + 3, 0xFF);
#elif defined(VERSION_EU_X)
    slider = SmpSlider_CreateSliderWidget(472 + 2, 472 + 3, 0xFF);
#endif
    g_soundOptionSliders[1] = slider;
    SmpSlider_SetSliderItem(slider, options[1]);
#if defined(VERSION_DE)
    SmpButton_WrapButtonWidget(463);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    SmpButton_WrapButtonWidget(467);
#elif defined(VERSION_EU_X)
    SmpButton_WrapButtonWidget(476);
#endif
    return 0;
}

s32 Menu_FreeSoundSliders(void) {
    Cache_FreeMemory(g_soundOptionSliders);
    g_soundOptionSliders = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Menu_SoundSliderReturnZero(void) {
    return 0;
}

extern unsigned char g_soundEffectsVolumeOption[]; /* MIXED Menu_ApplySoundSliders */
int Menu_ApplySoundSliders(void) {
 int value;
 unsigned char *options;
 int sound;
 value=SmpSlider_GetSliderItem(g_soundOptionSliders[1]);
 options=g_soundEffectsVolumeOption;
 if(value!=options[0]){options[0]=value;SoundElement_PlayFlatSound(1120);}
 value=SmpSlider_GetSliderItem(g_soundOptionSliders[0]);
 if(value!=options[-1]){
  options[-1]=value;
  if((unsigned char)value<5) sound=0;
  else {if(SoundElement_GetMusicPlaybackEnabled()!=0)goto end; sound=52;}
  SoundElement_SetMusicPlaybackEnabled(sound);
 }
 end: return 0;
}
