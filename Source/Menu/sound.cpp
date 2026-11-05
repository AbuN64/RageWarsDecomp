#include "Common/menuselectionmessage.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Common/menulistscreen.h"
#include "Menu/menu_createsoundoptionsscreen.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Ui/smp_slider.h"
#include "Common/animation.h"
#include "Common/runtime_declarations.h"
#include "Common/selectionscreenstate.h"
#include "types.h"
#include "Common/menuselectionmessage.h"
#include "Common/screen.h"
#include "Common/shared_menureply.h"
#include "Common/menu_screen_elements.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/cache_freememory.h"
#include "Menu/menu_advancefademeter.h"
#include "Common/aiprofile.h"
#include "Common/menu_overlay.h"
#include "Menu/menu_dispatchsoundoptionsevent.h"
#include "Menu/Sound/menu_applysoundsliders_symbols.h"
#include <PR/abi.h>
#include "Common/audio_callbacks.h"
#include "Common/measured.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/argb_color.h"
#include <platform_sdk.h>
#include "Common/shared_optionsscreen.h"
#include "Common/multiplayeroptions.h"
#include "Common/loadout.h"
#include "Common/virtual_pager.h"
#include "Common/group.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/manager.h"
#include "Common/cartridgereadworker.h"
#include "Common/audio_voice_slots.h"
#include "Common/soundvoicepool.h"
#include "Common/lightdata.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/mtx.h"
#include "Common/particle_attachment_and_owner_views.h"
#include "Common/colorentry.h"
#include "Common/worldsortentry.h"
#include "Common/results.h"
#include "Common/round_session.h"
#include "Common/hud_effects.h"
#include "Common/albank_s.h"
#include "Common/sequence_timing.h"
#include "Common/alparam_s.h"
#include "Common/audio_effect_chain.h"
#include "Common/ospihandle_s.h"
#include "Common/osviscale.h"
#include "Common/ctx.h"
#include "Common/audio_loaddecodedsamples.h"
#include "Common/cheatcode.h"
#include "Common/note_state.h"
#include "Common/frontend_video_mode.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Common/label.h"
#include "Common/player_join_requests.h"
#include "Common/characterselectionroot.h"
#include "Common/numberpadscreen.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/weapon_unlock_presets.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/match_settings.h"
#include "Common/menu_model_preview.h"
#include "Common/player_item_inventory.h"
#include "Common/objb.h"
#include "Frontend/menu_dispatchsoundsliderevent.h"
#include "Menu/Sound/menu_dispatchsoundsliderevent_symbols.h"
#include "Frontend/frontend.h"

#if defined(VERSION_DE) || defined(VERSION_EU_X)

s32 Menu_CreateSoundOptionsScreen(void) {
    s32 cue;
    void *memory;
    memory = Cache_AllocateMemory(28);
    g_soundOptionsScreen = memory;
#if defined(VERSION_DE)
    g_soundOptionsScreen->handle = SmpFade_CreateFadeWidget(106, 107);
    cue = SmpSlider_CreateSliderWidget(109, 110, 0xFF);
#elif defined(VERSION_EU_X)
    g_soundOptionsScreen->handle = SmpFade_CreateFadeWidget(112, 113);
    cue = SmpSlider_CreateSliderWidget(115, 116, 0xFF);
#else
    g_soundOptionsScreen->handle = SmpFade_CreateFadeWidget(108, 109);
    cue = SmpSlider_CreateSliderWidget(111, 112, 0xFF);
#endif
    g_soundOptionsScreen->cue0 = cue;
    SmpSlider_SetSliderItem(cue, g_gameSettings.volume[0]);
#if defined(VERSION_DE)
    cue = SmpSlider_CreateSliderWidget(111, 112, 0xFF);
#elif defined(VERSION_EU_X)
    cue = SmpSlider_CreateSliderWidget(117, 118, 0xFF);
#else
    cue = SmpSlider_CreateSliderWidget(113, 114, 0xFF);
#endif
    g_soundOptionsScreen->cue1 = cue;
    SmpSlider_SetSliderItem(cue, g_gameSettings.volume[1]);
#if defined(VERSION_DE)
    SmpButton_WrapButtonWidget(113);
    cue = SmpFlicker_CreateFlickerWidget(108, 110);
#elif defined(VERSION_EU_X)
    SmpButton_WrapButtonWidget(119);
    cue = SmpFlicker_CreateFlickerWidget(114, 110);
#else
    SmpButton_WrapButtonWidget(115);
    cue = SmpFlicker_CreateFlickerWidget(110, 110);
#endif
    g_soundOptionsScreen->state = 3;
    g_soundOptionsScreen->ambient = cue;
    g_soundOptionsScreen->reserved14 = -1;
    return 0;
}
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* Phase1 source candidate; contract holds and immutable inputs in per-function JSON. */

/* Allocates the HUD-cue object g_soundOptionsScreen, opens its handle for 0x6C/0x6D, starts its two timed cues at the volumes in g_gameSettingsVolumeBytes and its ambient loop, then arms state 3; returns 0. */
s32 Menu_CreateSoundOptionsScreen(void) {
    s32 cue;

    /* the hub's allocation helper returns its SelectionScreenState view; this unit keeps its own HudCue view */
    g_soundOptionsScreen = (struct HudCue *) Cache_AllocateMemory(28);
    g_soundOptionsScreen->handle = SmpFade_CreateFadeWidget(108, 109);
    cue = SmpSlider_CreateSliderWidget(111, 112, 0xFF);
    g_soundOptionsScreen->cue0 = cue;
    SmpSlider_SetSliderItem(cue, g_gameSettings.volume[0]);
    cue = SmpSlider_CreateSliderWidget(113, 114, 0xFF);
    g_soundOptionsScreen->cue1 = cue;
    SmpSlider_SetSliderItem(cue, g_gameSettings.volume[1]);
    SmpButton_WrapButtonWidget(115);
    cue = SmpFlicker_CreateFlickerWidget(110, 110);
    g_soundOptionsScreen->state = 3;
    g_soundOptionsScreen->ambient = cue;
    g_soundOptionsScreen->reserved14 = -1;
    return 0;
}
#endif

/* Calls MarkMenuEventHandled; when Menu_GetFocusedElementId reports 0x73, sets a field of the object
   g_soundOptionsScreen points to to -1 and calls SmpSlider_SetTransitionMode on its first word with 2. Returns zero. */
s32 Menu_FreeSoundOptionsScreen(void) {
    Cache_FreeMemory(g_soundOptionsScreen);
    g_soundOptionsScreen = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Menu_SoundOptionsReturnZero(void) {
    return 0;
}

s32 Menu_UpdateSoundOptionsScreen(void) {
    u8 *options;
    s32 value;
    s32 track;

    switch (SmpSlider_GetTransitionMode(((struct SoundOptionsScreen *)g_soundOptionsScreen)->menu)) {
    case 3:
        break;
    case 4:
        MarkMenuEventHandled();
        if (((struct SoundOptionsScreen *)g_soundOptionsScreen)->target != -1) {
            SmXlate_SwitchScreen(((struct SoundOptionsScreen *)g_soundOptionsScreen)->target);
            return 0;
        }
        Menu_ReturnToPreviousScreen();
        return 0;
    }
    value = SmpSlider_GetSliderItem(((struct SoundOptionsScreen *)g_soundOptionsScreen)->effects);
    options = &g_gameSettings.volume[1];
    if (value != options[0]) {
        options[0] = value;
        SoundElement_PlayFlatSound(1120);
    }
    value = SmpSlider_GetSliderItem(((struct SoundOptionsScreen *)g_soundOptionsScreen)->music);
    if (value != options[-1]) {
        options[-1] = value;
        track = 0;
        if ((u8)value >= 5) {
            if (SoundElement_GetMusicPlaybackEnabled() != 0) {
                return 0;
            }
            track = 52;
        }
        SoundElement_SetMusicPlaybackEnabled(track);
    }
    return 0;
}

s32 Menu_ConfirmSoundOptionsScreen(void) {
    struct SoundOptionsScreen *state;
    MarkMenuEventHandled();
#if defined(VERSION_DE)
    if (Menu_GetFocusedElementId() == 113) {
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    if (Menu_GetFocusedElementId() == 115) {
#elif defined(VERSION_EU_X)
    if (Menu_GetFocusedElementId() == 119) {
#endif
        state = g_soundOptionsScreen;
        state->target = -1;
        SmpSlider_SetTransitionMode((s32)state->menu, 2);
    }
    return 0;
}

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_soundOptionsEventIds, an actor kind at g_soundOptionsEventKinds and a handler at g_soundOptionsEventHandlers: the first row whose event equals event and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */


/* Updates the two menu options and plays their change sounds. */
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
    MenuWidget *actor;

    if (g_soundOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_soundOptionsEventHandlers;
        index = 0;
        do {
            if (g_soundOptionsEventIds[index].value == event) {
                actor = eventTarget;
                actor_kind = actor->resource;
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

/* Stores the two sound slider positions as the volume options: a changed effects volume plays a confirmation sound; a changed
   music volume below 5 stops music playback and otherwise starts it when it is not already playing. Returns zero. */
int Menu_ApplySoundSliders(void) {
 int value;
 value=SmpSlider_GetSliderItem(g_soundOptionSliders[1]);
 if(value!=g_soundEffectsVolumeOption[0]){g_soundEffectsVolumeOption[0]=value;SoundElement_PlayFlatSound(1120);}
 value=SmpSlider_GetSliderItem(g_soundOptionSliders[0]);
 if(value!=g_gameSettingsVolumeBytes[0]){
  g_gameSettingsVolumeBytes[0]=value;
  if((unsigned char)value<5) SoundElement_SetMusicPlaybackEnabled(0);
  else if(SoundElement_GetMusicPlaybackEnabled()==0) SoundElement_SetMusicPlaybackEnabled(52);
 }
 return 0;
}

/* Calls MarkMenuEventHandled, then passes -1 to Random_SetMenuChoiceResult when Menu_GetPreviousScreenOwner reports 0x16 for zero
   and 0xB otherwise, then calls Menu_ReturnToPreviousScreen. Returns zero. */
s32 Menu_ConfirmSoundSliderPopup(void) {
    MarkMenuEventHandled();
#if defined(VERSION_DE)
    if (Menu_GetFocusedElementId() == 463) {
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    if (Menu_GetFocusedElementId() == 467) {
#elif defined(VERSION_EU_X)
    if (Menu_GetFocusedElementId() == 476) {
#endif
        Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 11);
        Menu_ReturnToPreviousScreen();
    }
    return 0;
}

s32 Menu_CancelSoundSliderPopup(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 11);
    Menu_ReturnToPreviousScreen();
    return 0;
}

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_soundSliderEventIds, an actor kind at g_soundSliderEventKinds and a handler at g_soundSliderEventHandlers: the first row whose event equals event and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */


s32 Menu_DispatchSoundSliderEvent(void *eventTarget, s32 event, s32 itemId, s32 value, s32 context) {
    SoundSliderEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_soundSliderEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_soundSliderEventHandlers;
        index = 0;
        do {
            if (g_soundSliderEventIds[index].value == event) {
                actor = eventTarget;
                actor_kind = actor->resource;
                table_kind = g_soundSliderEventKinds[index].value;
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
