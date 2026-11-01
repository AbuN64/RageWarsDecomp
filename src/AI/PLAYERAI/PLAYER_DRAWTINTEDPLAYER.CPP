#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/MODEL_RENDER.H"
#include <ultra64.h>
#include "COMMON/OBJRECV5.H"
#include <PR/abi.h>
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MESSAGESEMAPHORE.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "RESMGR/resmgr_string_memory.H"
#include "AI/PLAYER_DRAWTINTEDPLAYER.H"
#include "COMMON/PLAYERPROFILES.H"

const float k_PlayerDrawtintedplayerEncodedWords[14] = {
    0.06666667f, 0.016666668f, 6e+01f, 1.0f,
    3e+01f, 0.5f, 0.8f, 1e+01f,
    0.5f, 2e+01f, 0.5f, 7.0f,
    6.0f, 12.0f,
};

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const float g_forceMarkerDurationEuropean = 150.0f;
#endif

const float k_PlayerDrawtintedplayerEncodedWordsBlock1[4] = {
    1.0f, 1.0e-05f, 100000000.0f, 0.5f,
};

/* Draws an actor's player model with its status tint: sets the other-mode lighting command and render
   mode 2, gives the model the team colour byte (the match rule g_matchRoundCounters's colour at 0x73 when team
   colours apply to the player, else the model's own at 0xE), and by the player's tint mode at 0x1238
   sets a colour override (flag g_menuModelFillEnabled, colour g_menuModelFillColor) that fades with the tint time at 0x1230:
   mode 0 draws through Gobjinst_DrawActorPartsWithViewEffects in yellow fading from full alpha and then draws the second pass
   through Geometry_DrawOwnerFilteredPass with 255 less twice that alpha, mode 1 draws only the second pass in fading
   yellow starting at alpha 128, and mode 3 draws through Gobjinst_DrawActorPartsWithViewEffects with an alpha rising with the
   time; the override is switched off afterwards. */
extern Gfx *g_displayListCursor;
extern RulesWeaponsDrawTintedPlayer g_matchRoundCounters[];
extern s32 g_lightingBufferIndex;
extern void Geometry_SetCombineMode(u32);
extern void Gobjinst_DrawActorPartsWithViewEffects(LevelActor *, PlayerControllerView *, s32, Draw *);

void Player_DrawTintedPlayer(LevelActor *actor, s32 animationContext, Draw *draw) {
    PlayerControllerView *player;
    Gfx *gfx;

    if (actor != 0) {
        player = actor->controller;
        if (player != 0) {
            gDPSetRenderMode(g_displayListCursor++, 0xC4404B50, 0);
            Geometry_SetCombineMode(2);
            if (g_matchRoundCounters->teams != 0 && player->controls->fragTagEnabled != 0) {
                actor->team = g_matchRoundCounters->colour;
            } else {
                actor->team = (u8)actor->definition->first;
            }
            if (player->tintMode == 0) {
                CQuatern *colour;

                g_menuModelFillEnabled = 1;
                colour = (CQuatern *)g_menuModelFillColor;
                colour->x = ((255.0f - player->tintTime * 17.0f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 17.0f));
                colour->y = ((255.0f - player->tintTime * 17.0f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 17.0f));
                colour->z = 0.0f;
                colour->w = ((255.0f - player->tintTime * 8.533334f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 8.533334f));
                Gobjinst_DrawActorPartsWithViewEffects(actor, player, animationContext, draw);
                colour->w = ((255.0f - colour->w * 2.0f) < 0.0f ? 0.0f : (255.0f - colour->w * 2.0f));
                Geometry_DrawOwnerFilteredPass(draw->model, player, actor->animationMatrices, 1,
                              &actor->lighting[g_lightingBufferIndex], 0, -1);
            } else if (player->tintMode == 1) {
                CQuatern *colour;

                g_menuModelFillEnabled = 1;
                colour = (CQuatern *)g_menuModelFillColor;
                colour->x = ((255.0f - player->tintTime * 17.0f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 17.0f));
                colour->y = ((255.0f - player->tintTime * 17.0f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 17.0f));
                colour->z = 0.0f;
                colour->w = ((128.0f - player->tintTime * 8.533334f) < 0.0f ? 0.0f : (128.0f - player->tintTime * 8.533334f));
                Geometry_DrawOwnerFilteredPass(draw->model, player, actor->animationMatrices, 1,
                              &actor->lighting[g_lightingBufferIndex], 0, -1);
            } else if (player->tintMode == 3) {
                g_menuModelFillEnabled = 1;
                g_menuModelFillColor[3] = ((player->tintTime * 0.425f) < 0.0f ? 0.0f : (player->tintTime * 0.425f));
                Gobjinst_DrawActorPartsWithViewEffects(actor, player, animationContext, draw);
            }
            g_menuModelFillEnabled = 0;
        }
    }
}

extern void Barrel_FillDamagePacket(void *packet, s32 damageSource, s32 damage, f32 radius, s32 damageFlags, s32 shield);
extern void Playerai_ApplyDamagePacket(void *attacker, void *damageState, void *packet);

extern ScalarFloatView g_frameElapsedTime;
void Playerai_UpdateDamageTimers(void *actor) {
    Slot damage;
    f32 scaledTotalDamage;
    f32 damageProgressValue;
    f32 damageUnitScale;
    f32 remainingFrames;
    f32 frameDamage;
    f32 zero;
    s32 damageEffectOffset;
    s32 i;
    void *damageSource;
    void *damageEffect;

    zero = 0.0f;
    damageUnitScale = g_playerDamageTimerConstants[1];
    i = 0;
    damageEffectOffset = 4680;
    do {
        damageEffect = (char *)actor + damageEffectOffset;
        remainingFrames = ((CPlayerDamageOverTime *)(damageEffect))->m_FramesRemaining;
        if (remainingFrames > zero) {
            damageProgressValue = g_frameElapsedTime.value;
            frameDamage = *(f32 *)damageEffect * damageProgressValue;
            damageProgressValue = remainingFrames - damageProgressValue;
            frameDamage *= damageUnitScale;
            ((CPlayerDamageOverTime *)(damageEffect))->m_FramesRemaining = damageProgressValue;
            damageProgressValue = ((CPlayerDamageOverTime *)(damageEffect))->m_DamageIssued + (f32)(s32)frameDamage;
            ((CPlayerDamageOverTime *)(damageEffect))->m_DamageIssued = damageProgressValue;
            if (((CPlayerDamageOverTime *)(damageEffect))->m_FramesRemaining <= zero) {
                scaledTotalDamage = ((CPlayerDamageOverTime *)(damageEffect))->m_TotalDamage * damageUnitScale;
                if (damageProgressValue < scaledTotalDamage) {
                    frameDamage += scaledTotalDamage - damageProgressValue;
                }
            }
            damageSource = ((CPlayerDamageOverTime *)(damageEffect))->m_pDamageSource;
            if (damageSource != 0 && *(u8 *)damageSource == 1 &&
                (((DamageSourceFlagsView *)(damageSource))->flags & 0x300000) &&
                (((DamageSourceFlagsView *)(damageSource))->statusFlags & 0x200)) {
                frameDamage *= g_playerDamageTimerFrameScale.value;
            }
            if (((CPlayerDamageOverTime *)(damageEffect))->m_bIsInflator != 0) {
                Playerai_AddReactionReserve(actor, 0.0933333337f, ((CPlayerDamageOverTime *)(damageEffect))->m_pDamageSource);
                if ((f32)((PlayerDamageVisualState *)(actor))->health <= frameDamage) {
                    frameDamage = g_playerDamageTimerFrameDefault.value;
                }
            }
            Barrel_FillDamagePacket((void *)&damage, (s32)((CPlayerDamageOverTime *)(damageEffect))->m_pDamageSource,
                          (s32)frameDamage, 25.599998f, 0x100080, 0);
            Playerai_ApplyDamagePacket(actor, &((PlayerDamageVisualState *)(actor))->damageState, (void *)&damage);
        }
        i++;
        damageEffectOffset += 24;
    } while (i < 5);
}

/* Transfers a randomly selected inventory quantity into an empty recipient slot. */

s32 Graphu64_NextRandom(void); /* extern */

void Player_TransferRandomInventoryItems(Inventory *inventory, Receiver *receiver) {
 s32 amount;
 s32 index;
 s32 value;
 void *scan;
 if (receiver->amount == 0) {
  amount=15;
  index=Graphu64_NextRandom()%3;
  value=inventory->items[index];
  if(value<16) amount=value;
  if(amount==0) {
   Graphu64_NextRandom();
   scan=inventory;
   for(index=0;index<3;index++) {
    s16 item=inventory->items[index];
    if(item>0) { s32 v=item; if(amount<v) v=amount; amount=v; }
   }
   index=2;
  }
  if(amount!=0) {
   inventory->items[index]-=amount;
   receiver->index=index;
   receiver->amount=amount;
  }
 }
}

/* Gives a player an amount of one ammunition type and announces it: the count at 0x5F4 of that type
   rises by the amount up to the type's maximum (none for type -1, the character's table at 0x108 in
   multiplayer, otherwise g_baseAmmoCapacities plus the profile's bonus bytes in g_localPlayerProfiles unless ammunition is
   unlimited at 0x1450), and the message "<amount> <type name>" with a plural suffix for more than one
   is built and shown through Playerai_PostMessageHistoryEntry. */

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);
extern u8 *XPlus_AppendString(u8 *destination, u8 *source);
extern char *Weapon_GetIndexedTableValue(s32);
extern void Playerai_PostMessageHistoryEntry(SharedPlayer *, char *, f32);

static inline s32 max_ammo(SharedPlayer *player, s32 type) {
    s32 max;

    if (type == -1) {
        return 0;
    }
    if (g_gameSettings.controllerMode != 1) {
        max = player->views18.view18_4.character->caps[type];
    } else {
        max = g_baseAmmoCapacities[type];
        if (player->views1450.view1450_3.unlimited == 0) {
            if (type == 0) {
                max += g_localPlayerProfiles[player->views1C.view5D4_47.profile].bonus0;
            } else if (type == 1) {
                max += g_localPlayerProfiles[player->views1C.view5D4_47.profile].bonus1;
            } else if (type == 2) {
                max += g_localPlayerProfiles[player->views1C.view5D4_47.profile].bonus2;
            }
        }
    }
    return max;
}

void Player_GiveAmmoWithMessage(SharedPlayer *player, s32 type, s32 amount) {
    char number[8];
    char message[32];

    if (amount != 0) {
        player->views5E8.view5F4_12.ammo[type] = ((player->views5E8.view5F4_12.ammo[type] + amount) < (max_ammo(player, type)) ? (player->views5E8.view5F4_12.ammo[type] + amount) : (max_ammo(player, type)));
        XPlus_FormatDecimalInteger(amount, number);
        XPlus_CopyString(message, number);
        XPlus_AppendString(message, s_ammoPickupMessageSeparator);
        XPlus_AppendString(message, Weapon_GetIndexedTableValue(type));
        if (amount >= 2) {
            XPlus_AppendString(message, s_ammoPickupPluralSuffix);
        }
        Playerai_PostMessageHistoryEntry(player, message, 1.0f);
    }
}

/* ROM-grounded data: src/k_PlayerDrawtintedplayerEncodedWordsBlock2_PlayerDrawtintedplayer.c */
const float k_PlayerDrawtintedplayerEncodedWordsBlock2[3] = {
    256.0f, 11.0f, 255744.0f,
};
