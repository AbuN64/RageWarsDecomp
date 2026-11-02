#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "TYPES.H"
#include "../../../sdk/include/AUDIO/sprintf.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "ENGINE/AUDIO/CHANNEL.H"

/** Start the actor effect and attach optional source-specific resources; the European cartridges pick
    each resource from a per-language table. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)




extern void *g_playerSourceEffectStartMessage[];
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern void *g_playerSourceEffectOwnerFormatEuropean[];
#else
extern void *g_playerSourceEffectOwnerFormat[];
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern void *g_playerSourceEffectFinalMessageEuropean[];
#else
extern void *g_playerSourceEffectFinalMessage[];
#endif
#else
extern void *g_playerSourceEffectStartMessage;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern void *g_playerSourceEffectOwnerFormatEuropean;
#else
extern void *g_playerSourceEffectOwnerFormat;
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern void *g_playerSourceEffectFinalMessageEuropean;
#else
extern void *g_playerSourceEffectFinalMessage;
#endif
#endif







void Player_StartSourceEffect(void *actor, void *effectSource) {
    Shared_ActorView *state = actor;
    Shared_ActorView *source = effectSource;
    void *owner;
    void *payload;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    MenuMatchGlobals *game;
    MenuSettings *settings;
#endif

    if (state->pending != 0.0f) {
        return;
    }

    SoundElement_PlayFlatSound(2885);
    state->pending = g_playerSourceEffectDuration;
    state->parent = source;
    owner = state->message;
    if (owner == 0) {
        return;
    }

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    game = &g_frontendScreenStatus;
    settings = &game->settings;
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Camera_PostScreenMessage(game, owner, g_playerSourceEffectStartMessage[settings->language]);
#else
    Camera_PostScreenMessage(&g_frontendScreenStatus, owner, g_playerSourceEffectStartMessage);
#endif
    if (source == 0) {
        return;
    }
    if (((LevelActor *)source)->kind != 1) {
        return;
    }
    if ((((LevelActor *)source)->flags & 0x300000) == 0) {
        return;
    }

    payload = state->effectPayload;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Libc_FormatString(payload, g_playerSourceEffectOwnerFormatEuropean[settings->language],
#else
    Libc_FormatString(payload, g_playerSourceEffectOwnerFormatEuropean,
#endif
#else
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Libc_FormatString(payload, g_playerSourceEffectOwnerFormat[settings->language],
#else
    Libc_FormatString(payload, g_playerSourceEffectOwnerFormat,
#endif
#endif
                  source->controls->pad84);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Camera_PostScreenMessage(game, state->message, payload);
#else
    Camera_PostScreenMessage(&g_frontendScreenStatus, state->message, payload);
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Camera_PostScreenMessage(game, state->message, g_playerSourceEffectFinalMessageEuropean[settings->language]);
#else
    Camera_PostScreenMessage(&g_frontendScreenStatus, state->message, g_playerSourceEffectFinalMessageEuropean);
#endif
#else
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Camera_PostScreenMessage(game, state->message, g_playerSourceEffectFinalMessage[settings->language]);
#else
    Camera_PostScreenMessage(&g_frontendScreenStatus, state->message, g_playerSourceEffectFinalMessage);
#endif
#endif
}
