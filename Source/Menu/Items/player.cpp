#include "Menu/Items/game_and_player_options.h"
#include "Common/aiprofile.h"
#include "Common/gameplay_settings.h"
#include "Common/sharedplayer.h"
#include "include_asm.h"
#include "Menu/menu_item_views.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/soundinfo.h"
#include "Common/snapshot_actor.h"
#include "System/sound_context_music_and_voice_control.h"
#include "../../../sdk/include/AUDIO/sprintf.H"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Engine/voice.h"
#include "Menu/player_status_text.h"
#include "Menu/bound.h"
#include "Common/particle_lighting.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Gobjinst/gobjinst_buildactortransform.h"
#include "Gobjinst/player_drawtintedplayer_data.h"
#include "Common/shared_optionsscreen.h"
#include "Common/player_message_menu.h"
#include "Menu/Items/player_openplayerdialog.h"
#include "Menu/Pak/timer_cancelpendingoperation.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Common/ballisticparams.h"
#include "Menu/built_menu.h"
#include "Common/respawn_menu_actor.h"
#include <platform_sdk.h>
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Common/weapon_screen_message_operations.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Ai/Player/player_placeplayerforround.h"
#include "Ovlgame/match.h"
#include "Render/playerai_toggleforcemarker.h"
#include "Common/game_session.h"
#include "Engine/defs.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/textlayermetrics.h"
#include "Common/pak_enter_player_options.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Common/player_getplayerindex.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/Items/Player/items_formatplayerresultscore_symbols.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/Items/Player/player_formatplayerrewardscore_symbols.h"
#endif
#include "../../../sdk/include/PFS/PLAYER_CONFIGUREPLAYERMENUFLAGS.H"
#include "Common/shared_worldfunc.h"
#include "Common/pak_preview_selection.h"
#include "../../../sdk/include/PFS/PLAYER_CONFIGUREANDPROBECONTROLLERPAK.H"
#include "Engine/control.h"
#include "Menu/Items/Player/player_configureandprobecontrollerpak_symbols.h"
#include "Menu/menu_event_handlers.h"
#include "Menu/Pak/pak_menu_entries.h"
#include "Menu/pak_action_prompt.h"
#include "Ovlgame/menu_handlesessionoptionpage.h"

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookOne(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookTwo(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookThree(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookFour(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookFive(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookSix(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_PartnerStatusZeroHookSeven(void) {
    return 0;
}

/* Calls SoundElement_DisableMusicGainOverride and passes what SoundVoicePool_GetGlobalState returns to SoundVoicePool_Resume; then, when g_controllerReturnPending
   is set, calls Menu_TryCreateMenu with the three arguments, otherwise Control_RestoreControllerSetup_FrontendDestroypausemenu. Returns one. */
struct SoundVoicePool;

s32 Player_RestoreControlsOrCreateMenu(void *first, void *second, void *third) {
    SoundElement_DisableMusicGainOverride();
    SoundVoicePool_Resume(SoundVoicePool_GetGlobalState());
    if (g_controllerReturnPending == 0) {
        Control_RestoreControllerSetup();
        return 1;
    }
    Menu_TryCreateMenu(first, second, third);
    return 1;
}


/* Formats a player's status line into a menu field's text through Libc_FormatString (sprintf): one message when the player is its own partner, otherwise a message chosen by the player's mode (0 to 6), naming the partner's character when there is a partner. */
typedef struct {
    char pad0[0x10];
    char **text;
} PartnerStatusDescriptor;

typedef struct {
    char pad0[0x18];
    PartnerStatusDescriptor *field;
} PartnerStatusItem;

typedef struct {
    char pad0[0x1C];
    Player *player;
} PartnerStatusMenuContext;

s32 Player_FormatPlayerPartnerStatus(PartnerStatusItem *item, PartnerStatusMenuContext *owner) {
    Player *player = owner->player;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    char *text = item->field->text[g_languageIndex];
#else
    char *text = *item->field->text;
#endif
    if (player->partner == player) {
        Libc_FormatString(text, playerStatusText(0));
    } else if (player->partner != 0) {
        switch (player->partnerStatus) {
        case 0: Libc_FormatString(text, playerStatusText(1), &((Shared_PlayerSettingsRecord *)player->partner->profile)->name); break;
        case 1: Libc_FormatString(text, playerStatusText(2), &((Shared_PlayerSettingsRecord *)player->partner->profile)->name); break;
        case 2: Libc_FormatString(text, playerStatusText(3), &((Shared_PlayerSettingsRecord *)player->partner->profile)->name); break;
        case 3: Libc_FormatString(text, playerStatusText(4), &((Shared_PlayerSettingsRecord *)player->partner->profile)->name); break;
        case 4: Libc_FormatString(text, playerStatusText(5), &((Shared_PlayerSettingsRecord *)player->partner->profile)->name); break;
        case 5: Libc_FormatString(text, playerStatusText(6), &((Shared_PlayerSettingsRecord *)player->partner->profile)->name); break;
        case 6: Libc_FormatString(text, playerStatusText(7), &((Shared_PlayerSettingsRecord *)player->partner->profile)->name); break;
        }
    } else {
        switch (player->partnerStatus) {
        case 0: Libc_FormatString(text, playerStatusText(8)); break;
        case 1: Libc_FormatString(text, playerStatusText(9)); break;
        case 2: Libc_FormatString(text, playerStatusText(10)); break;
        case 3: Libc_FormatString(text, playerStatusText(11)); break;
        case 4: Libc_FormatString(text, playerStatusText(12)); break;
        case 5: Libc_FormatString(text, playerStatusText(13)); break;
        case 6: Libc_FormatString(text, playerStatusText(14)); break;
        }
    }
    return 0;
}

#if defined(VERSION_DE)
const float k_ItemsHalfWords[1] = {
    0.5f,
};
#endif

#if defined(VERSION_DE)
char k_ItemsEncodedBytes[8] =
    "  %02d\000\000";
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
const char g_playerMenuValueFormat[8] =
    "%04d\000\000\000\000";
#endif
#if defined(VERSION_EU_X)
const char g_playerMenuValueFormat[5] =
    "%04d";
#endif
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
const float k_PlayerFormatplayerpartnerstatusHalfWords[1] = {
    0.5f,
};
#endif

#if defined(VERSION_EU)
unsigned int k_playerFormatPartnerStatusPackedWords[2] = {
    0x4BFF05AA, 0x4B0A6F45,
};
#endif

#if defined(VERSION_EU_X)
const float k_PlayerConstantHalf[1] = {
    0.5f,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_menuItemsPlayerConstantWords[2] = {
    0x0000005F, 0x0000002A,
};
#endif

#if defined(VERSION_US_REV1)
f32 Bound_ReadBoundValue(MenuBindingItemView *item) {
 Binding *v = item->binding;
 void *p = v->storage();
 switch(v->type) {
 default: return 0.0f;
 case 0: return *(f32 *)p;
 case 3: return *(s8 *)p;
 case 4: return *(s16 *)p;
 case 1: case 2: case 5: return *(s32 *)p;
 case 6: return *(u8 *)p;
 case 7: return *(u16 *)p;
 case 8: return *(u32 *)p;
 }
}
/* Writes a numeric menu value through its bound storage callback using the selected scalar type. */
void Bound_WriteBoundValue(MenuBindingItemView *item,float value) {
 float *storage;
 struct Binding *binding;
 unsigned int *word;
 binding=item->binding;
 storage=binding->storage();

 switch(binding->type) {
 case 0:*(float *)storage=value;return;
 case 3:*(signed char *)storage=(int)value;return;
 case 4:*(short *)storage=(int)value;return;
 case 1:case 2:case 5:*(int *)storage=(int)value;return;
 case 6:*(unsigned char *)storage=(unsigned int)value;return;
 case 7:*(unsigned short *)storage=(unsigned int)value;return;
 case 8:word=(unsigned int *)storage;*word=(unsigned int)value;return;
 }
}
#endif
/* Calls Gobjinst_DrawMaskedModelWithLighting with its three arguments and the table g_defaultParticleLighting as the fourth. */
#if defined(VERSION_US_REV1)
void Bound_DrawActorWithMenuLighting(void *first, void *second, void *third) {
    Gobjinst_DrawMaskedModelWithLighting(first, second, third, &g_defaultParticleLighting);
}
#endif

#if defined(VERSION_US_REV1)
void Bound_DrawActorWithRedMenuEffect(ObjectItemsDrawActorWithRedMenuEffect *object, void *context, void *lookup) {
 g_menuModelFillEnabled=3;
 object->view[g_lightingBufferIndex]=g_defaultParticleLighting;
 g_menuModelFillColor[0]=(255.0f);
 g_menuModelFillColor[1]=0;
 g_menuModelFillColor[2]=0;
 g_menuModelFillColor[4]=0;
 g_menuModelFillColor[3]=(float)(g_menuTintAlpha/2);
 Gobjinst_DrawActorModelWithViewEffects(object,context,lookup);
 g_menuModelFillEnabled=0;
}
#endif

/* Loads the owner in the second argument into g_playerViewRenderContext through Player_GetPlayerIndexDe,
   calls Timer_ClearTimerFlag, and hands the owner, its word at 0x698 and a zero with the resource
   g_playerMenuDialogRomResource to Menu_OpenDialog for the block 0x5DC bytes into g_playerViewRenderContext. Returns one. */
s32 Player_OpenPlayerDialog(void *entry, struct MenuItemOwnerLinkView *holder) {
    struct MenuItemControllerView *owner = holder->owner;

    Player_GetPlayerIndex(&g_playerViewRenderContext, owner);
    Timer_ClearTimerFlag();
    Menu_OpenDialog(&((Shared_MenuData *)&g_playerViewRenderContext)->dialogOwner, g_playerMenuDialogRomResource, owner, owner->value, 0);
    return 1;
}

/* Sets the flag of the leaf item reached through the second argument's middle record, and returns one. */
s32 Player_SetNestedItemFlag(void *entry, struct NestedPlayerMenuFlagContext *root) {
    root->middle->leaf->flag = 1;
    return 1;
}

s32 Player_RespawnItemPlayer(void *entry, PlayerRespawnMenuContext *menuState) {
    Player_PlacePlayerForRound(menuState->actor);
    return 1;
}

void Player_DrawPulsingMenuSprite(MenuBuildEntry *spriteState, CaptionEntry *caption, s32 unusedEventKind, MenuStyle *menuStyle) {
    s32 phase;
    s32 amount;
    s32 half;
    s32 drop;
    f32 scale;
    f32 sx;
    phase = spriteState->selection = (spriteState->selection + 20) % 512;
    if (phase >= 256) {
        amount = (s32) ((f32) (512 - phase) * menuStyle->alpha * menuStyle->fade);
    } else {
        amount = (s32) ((f32) phase * menuStyle->alpha * menuStyle->fade);
    }
    Onscrn_SetupSpriteMode(amount);
    drop = 80;
    half = caption->width >> 1;
    if (g_frontendCurrentVideoModeIndex == 0) {
        drop = 45;
    }
    sx = caption->scaleX;
    scale = *(&k_playerMenuSpriteScaleConstants + 1);
    OnScreen_DrawSpriteResource(spriteState->resource, 0, caption->x - (half * 8), caption->y + drop,
                  sx * scale, caption->scaleY * scale, 1);
}

int Player_ResumePlayerFromMenu(int entry, PlayerMenuResumeContext *player) {
    CGameStatus *sync = &g_gameSettings.counters;
    int team;

    if (sync->m_bFragTagOn != 0) {
        team = player->actor->info->fragTagEnabled;
        if (team == 1) {
            sync->m_FragTagMode = team;
        }
    }
    if (g_sessionOptionResetMode == 1) {
        Match_ResetMatchControllerState(&g_gameSession);
    } else {
        player->actor->waiting = 0;
    }
    return 1;
}

s32 Player_UpdatePlayerRespawnDelay(PlayerRespawnMenuContext *menuState) {
    CGameStatus *state;
    s32 respawnFrames;
    s32 roundFinished;
    PlayerRespawnMenuActor *player;
    player = menuState->actor;
    if ((player->computerControlled == 0) && (Playerai_IsPlayerInactive(player) != 0)) {
        respawnFrames = player->respawnDelayFrames + 1;
        player->respawnDelayFrames = respawnFrames;
        if (respawnFrames >= 76) {
            Player_PlacePlayerForRound(menuState->actor);
            return 1;
        }
    }
    roundFinished = 0;
    state = &g_gameSettings.counters;
    if (state->round || state->elapsed || state->state) roundFinished = 1;
    return roundFinished;
}

s32 Player_SelectFragTagLabel(struct PakActionLabelView *field) {
    if (g_gameSettings.counters.m_bFragTagOn != 0) {
        field->text = g_fragTagOnLabelText;
    } else {
        field->text = g_fragTagOffLabelText;
    }
    return 0;
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Player_FormatPlayerResultScore(LayeredText *field, struct MenuRules *holder) {
    Shared_MenuData *players = &g_playerViewRenderContext;
    s32 player = Player_GetPlayerIndex(players, holder->locked);
    s32 value = g_playerResultScoreFields[player * 75];
    char *text = field->text[players->game.language];
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Formats the halfword g_playerResultScoreFieldsDe holds for the player Player_GetPlayerIndexDe identifies from the owner of the second argument into a field's text with the
   format g_fmtDecPadLongDe into the last four characters of the field text (the length Menu_CountLineChars reports). Returns zero. */
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Player_FormatPlayerResultScore(LayeredText *field, struct MenuRules *holder) {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    struct LocalizedInputState *players = &g_playerViewRenderContext;
    s32 player = Player_GetPlayerIndex(players, holder->locked);
#else
    s32 player = Player_GetPlayerIndex(&g_playerViewRenderContext, holder->locked);
#endif

    s32 value = g_gameSettings.playerSettings[player].resultScore;
    char *text =

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text[players->language];
#else
        *field->text;
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
#else
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtDecPadLong, value);
#endif
    return 0;
}

#endif
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Player_FormatPlayerRewardScore(LayeredText *field, struct MenuRules *holder) {
    Shared_MenuData *players = &g_playerViewRenderContext;
    s32 player = Player_GetPlayerIndex(players, holder->locked);
    s32 value = g_playerRewardScoreFields[player * 75];
    char *text = field->text[players->game.language];
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Formats the halfword g_playerRewardScoreFieldsDe holds for the player Player_GetPlayerIndexDe identifies from the owner of the second argument into a field's text with the
   format g_fmtDecPadLongDe into the last four characters of the field text (the length Menu_CountLineChars reports). Returns zero. */
s32 Player_FormatPlayerRewardScore(LayeredText *field, struct Holder *holder) {
    s32 player = Player_GetPlayerIndex(&g_playerViewRenderContext, (u32)holder->owner);
    s32 value = g_gameSettings.playerSettings[player].score;
    char *text = *field->text;

    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtDecPadLong, value);
    return 0;
}
#endif

/* Formats the halfword g_playerResultHalfwordFields holds for the player Player_GetPlayerIndexDe identifies from the owner of the second argument into a field's text with the
   format g_fmtDecPadLongDe into the last four characters of the field text (the length Menu_CountLineChars reports). Returns zero. */
s32 Player_FormatPlayerResultHalfword(LayeredText *field, struct MenuRules *holder) {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    struct LocalizedInputState *players = &g_playerViewRenderContext;
    s32 player = Player_GetPlayerIndex(players, holder->locked);
#else
    s32 player = Player_GetPlayerIndex(&g_playerViewRenderContext, holder->locked);
#endif

    s32 value = g_gameSettings.playerSettings[player].unknown02;
    char *text =

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        field->text[players->language];
#else
        *field->text;
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
#else
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtDecPadLong, value);
#endif
    return 0;
}

/* Writes the selected player's total, padded to four digits, into the last four characters of the field text; returns 0. */
s32 Player_FormatPlayerFirstHalfword(Shared_DebugWidget *field, Shared_MenuHandle *holder) {
    s32 player = Player_GetPlayerIndex(&g_playerViewRenderContext, holder->owner);
    /* The field shows the player's total from the selection screen's per-player settings. */
    s32 value = ((CPlayerOptions *)g_playerSettings)[player].totalSuicide;
    char *text;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    text = field->inner->text[g_playerViewRenderContext.object.language];
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuValueFormat, value);
#else
    text = *field->inner->text;
    Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtDecPadLong, value);
#endif
    return 0;
}

/* Does nothing. Nothing in the cartridge image calls it or stores its address as a word. */
void Player_MenuFlagsNoOp(void) {
}

void Player_SetFragTagItemFlag(struct MenuPromptKindView *record) {
    if (g_gameSettings.counters.m_bFragTagOn != 0) {
        record->target->flags |= 0x01000000;
    } else {
        record->target->flags &= ~0x01000000;
    }
}

void Player_ConfigurePlayerMenuFlags(PlayerMenuFlagContext *object) {
 if(object->parent) object->parent->playerStateDirty=1;
 object->actor->flags1c0 |= 0x01800000;
 object->actor->flags1c0 &= 0xFEFFFFFF;
 object->actor->flags58 |= 0x01800000;
 object->actor->flags210 &= 0xFE7FFFFF;
 object->actor->flags238 &= 0xFE7FFFFF;
 object->actor->flags260 &= 0xFE7FFFFF;
 if(g_gameSettings.counters.m_bFragTagOn) {object->actor->flags120 |= 0x01000000; return;}
 object->actor->flags120 &= 0xFEFFFFFF;
}

/* Updates display flags and activates the selected resource. */

/* Updates object display flags and selects the requested resource. */

 /* const */
void Player_ConfigureAndProbeControllerPak(ControllerPakMenuContext *menuContext) {
    s32 playerId;
    s32 controllerIndex;
    ControllerPakMenuActorView *pakUnavailableWidgets;
    ControllerPakMenuActorView *pakAvailableWidgets;
    ControllerPakMenuActorView *profileWidgets;
    ControllerPakMenuActorView *transferWidgets;
    ControllerPakMenuActorView *secondaryWidgets;
    ControllerPakMenuActorView *headerWidgets;
    ControllerPakMenuActorView *statusWidgets;
    profileWidgets = menuContext->actor;
    profileWidgets->flags238 = (s32) (profileWidgets->flags238 | 0x01800000);
    transferWidgets = menuContext->actor;
    transferWidgets->flags260 = (s32) (transferWidgets->flags260 | 0x01800000);
    secondaryWidgets = menuContext->actor;
    secondaryWidgets->flags1c0 = (s32) (secondaryWidgets->flags1c0 & 0xFE7FFFFF);
    headerWidgets = menuContext->actor;
    headerWidgets->flags58 = (s32) (headerWidgets->flags58 & 0xFE7FFFFF);
    statusWidgets = menuContext->actor;
    statusWidgets->flags210 = (s32) (statusWidgets->flags210 & 0xFE7FFFFF);
    g_pakUseScannedChannel = 0;
    g_pakPlayerMessagePending = 0;
    controllerIndex = 0;
    if (g_gameSettings.counters.m_bFragTagOn != 0) {
        pakAvailableWidgets = menuContext->actor;
        pakAvailableWidgets->flags120 = (s32) (pakAvailableWidgets->flags120 | 0x01000000);
    } else {
        pakUnavailableWidgets = menuContext->actor;
        pakUnavailableWidgets->flags120 = (s32) (pakUnavailableWidgets->flags120 & 0xFEFFFFFF);
    }
    playerId = menuContext->playerAddress;
    if (playerId != 0) {
        controllerIndex = Player_GetPlayerIndex((s32 *)&g_playerViewRenderContext, playerId);
    }
    Control_EnableControllerPak(controllerIndex);
    Note_ProbeStatus(controllerIndex);
}

                          /* const */
void Player_ConfigureControllerPakMenu(ControllerPakMenuContext *menuContext) {
    s32 playerId;
    s32 controllerIndex;
    ControllerPakMenuActorView *pakUnavailableWidgets;
    ControllerPakMenuActorView *pakAvailableWidgets;
    ControllerPakMenuActorView *profileWidgets;
    ControllerPakMenuActorView *transferWidgets;
    ControllerPakMenuActorView *secondaryWidgets;
    ControllerPakMenuActorView *headerWidgets;
    ControllerPakMenuActorView *statusWidgets;

    playerId = menuContext->playerAddress;
    g_pakPlayerMessagePending = 0;
    controllerIndex = 0;
    if (playerId != 0) {
        controllerIndex = Player_GetPlayerIndex((s32 *)&g_playerViewRenderContext, playerId);
    }
    Control_EnableControllerPak(controllerIndex);
    profileWidgets = menuContext->actor;
    profileWidgets->flags238 = (s32) (profileWidgets->flags238 | 0x01800000);
    transferWidgets = menuContext->actor;
    transferWidgets->flags260 = (s32) (transferWidgets->flags260 | 0x01800000);
    secondaryWidgets = menuContext->actor;
    secondaryWidgets->flags1c0 = (s32) (secondaryWidgets->flags1c0 & 0xFE7FFFFF);
    headerWidgets = menuContext->actor;
    headerWidgets->flags58 = (s32) (headerWidgets->flags58 & 0xFE7FFFFF);
    statusWidgets = menuContext->actor;
    statusWidgets->flags210 = (s32) (statusWidgets->flags210 & 0xFE7FFFFF);
    if (g_gameSettings.counters.m_bFragTagOn != 0) {
        pakAvailableWidgets = menuContext->actor;
        pakAvailableWidgets->flags120 = (s32) (pakAvailableWidgets->flags120 | 0x01000000);
        return;
    }
    pakUnavailableWidgets = menuContext->actor;
    pakUnavailableWidgets->flags120 = (s32) (pakUnavailableWidgets->flags120 & 0xFEFFFFFF);
}

#if defined(VERSION_US)
/* Stale bytes 00000010 000B0000; no instruction reads it. */
unsigned char g_menuItemsPlayerStaleBytes[8] = { 0x00, 0x00, 0x00, 0x10, 0x00, 0x0B, 0x00, 0x00 };
#endif
