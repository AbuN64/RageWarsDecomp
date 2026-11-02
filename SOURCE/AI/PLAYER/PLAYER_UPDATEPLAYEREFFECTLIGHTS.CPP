#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/GAMEPLAY_MOVEMENT.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"

extern u8 g_playerAimHudEnabled; /* MIXED Playerai_DrawAimHud */
void Playerai_DrawAimHud(SharedPlayer *player, void *view) {
    s32 icon;
    s32 show;
    f32 scale;

    player->views5E8.view7BC_102.timer += g_frameElapsedTime;
    if (player->views5E8.view788_94.icons == 0) {
        return;
    }
    if (player->views5D8.view5D8_9.profile->remote == 1 && g_gameSettings.counters.m_bFragTagOn != 0) {
        return;
    }
    if (player->views5E8.view650_17.action == 39) {
        return;
    }
    if (player->views1C.view594_40.mode == 2 && player->views5E8.view62E_14.weapon == 3) {
        return;
    }
    if (Tsmos_IsFrontendActive() != 0) {
        return;
    }
    if (player->views5E8.view798_96.carried == 730) {
        if (player->views1C.view594_40.mode == 1) {
            if (player->views1C.viewE4_7.kind != g_playerSpecialModelIds[0] && player->views1C.viewE4_7.kind != g_playerSpecialModelIds[1]) {
                player->views5E8.view798_96.carried = 751;
                if ((u8) player->views1C.view48C_35.state - 2U < 2) {
                    player->views5E8.view7BC_102.timer = 0.0f;
                } else if (player->views1C.view523_37.busy != 0) {
                    player->views5E8.view7BC_102.timer = 0.0f;
                } else {
                    player->views5E8.view7BC_102.timer = 1.0f;
                }
            }
        } else if (player->views1C.viewE4_7.kind != g_playerSpecialModelIds[0] && player->views1C.viewE4_7.kind != g_playerSpecialModelIds[1]) {
            player->views5E8.view798_96.carried = 753;
            if (player->views5E8.view62E_14.weapon == 9 && player->views1C.view5A0_42.charge > 0.0f) {
                player->views5E8.view7BC_102.timer = 1.0f;
            } else if (player->views1C.view48C_35.state == 11 || player->views1C.view48C_35.state == 3 || player->views1C.view48C_35.state == 2) {
                player->views5E8.view7BC_102.timer = 0.0f;
            } else if (player->views1C.view523_37.busy != 0) {
                player->views5E8.view7BC_102.timer = 0.0f;
            } else {
                player->views5E8.view7BC_102.timer = 1.0f;
            }
        } else {
            player->views5E8.view798_96.carried = 770;
            player->views5E8.view7BC_102.timer = 0.0f;
        }
    }
    Onscrn_SetupSpriteMode(0xFF);

    icon = player->views5E8.view7B8_100.target;
    show = 1;
    if (icon == 730 && g_frontendScreenStatus.settings.local != 0) {
        show = g_playerAimHudEnabled;
    }
    if (icon != -1) {
        switch (icon) {
        case 730:
        case 751:
        case 752:
            scale = 8.0f;
            break;
        case 700:
        case 740:
        case 753:
        case 754:
        case 770:
        case 800:
        case 810:
        case 811:
        case 860:
        case 861:
            scale = 32.0f;
            break;
        default:
            scale = 16.0f;
            break;
        }
        if (show) {
            Playerai_DrawProjectedAimIcon(view, &player->views5E8.view7C0_104.targetPosition, icon, player->views5E8.view7BC_102.timer, scale, 1.0f);
        }
    }

    icon = player->views5E8.view798_96.carried;
    show = 1;
    if (icon == 730 && g_frontendScreenStatus.settings.local != 0) {
        show = g_playerAimHudEnabled;
    }
    if (icon != -1) {
        switch (icon) {
        case 730:
        case 751:
        case 752:
            scale = 8.0f;
            break;
        case 700:
        case 740:
        case 753:
        case 754:
        case 770:
        case 800:
            scale = 32.0f;
            break;
        case 755:
        case 756:
        default:
            scale = 16.0f;
            break;
        }
        if (show) {
            Playerai_DrawProjectedAimIcon(view, &player->views5E8.view79C_98.carriedPosition, icon, player->views5E8.view7BC_102.timer, scale, 1.0f);
        }
    }
}

#include "COMMON/AIPROFILE.H"
struct PlayerEffectLight {
    u8 pad0[8];
    void *pattern;
    f32 radius;
    s16 x, y, z;
    s16 active;
};
#if defined(VERSION_US)
#define PLAYER_SECOND_LIGHT_RADIUS g_playerSecondLightRadiusUs
#else
#define PLAYER_SECOND_LIGHT_RADIUS g_playerSecondLightRadius
#endif
extern f32 PLAYER_SECOND_LIGHT_RADIUS;
#if defined(VERSION_DE)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternGerman
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternGerman
#elif defined(VERSION_EU)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternEuropean
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternEuropean
#elif defined(VERSION_EU_X)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternWords
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternEuropeanX
#elif defined(VERSION_US)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternUs
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternUs
#elif defined(VERSION_US_REV1)
#define PLAYER_EFFECT_LIGHT_PATTERN g_playerEffectLightPatternUsRev1
#define PLAYER_MODE_LIGHT_PATTERN g_playerModeLightPatternUsRev1
#endif
extern char PLAYER_EFFECT_LIGHT_PATTERN[], g_playerSecondaryLightPattern[], PLAYER_MODE_LIGHT_PATTERN[], g_playerAlternateModeLightPattern[];
extern void *Gdynlight_AllocateLightNode(void *, void *);
#include "ENGINE/INSTANCE/GOBJINST_GETACTOROFFSETPOSITIONANDMODEL.H"
/* Position one effect light, reading its scale and radius at their use sites. */
static inline void placePlayerLight(struct Player *player, struct PlayerEffectLight *light,
                                    f32 offsetZ, const f32 *heightScale, const f32 *radius) {
    CVector3 offset;
    CVector3 position;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = offsetZ;
    Gobjinst_TransformVectorByActorAim(&position, player, offset);
    Graphu64_AddVec3(&position, &position, &player->pos);
    light->active = 1;
    light->x = (s16)position.x;
    light->y = (s16)(position.y + Gobjinst_GetActorHeight(player) * *heightScale);
    light->z = (s16)position.z;
    light->radius = *radius;
}
/* Keep the timer lights and the special-mode light in step with player state. */
void Player_UpdatePlayerEffectLights(struct Player *player) {
    struct PlayerEffectLight *light;
    s32 flicker;
    if (g_gameSettings.flags & 0x4000) {
        player->rangeTimer = 0.0f;
    } else if (player->rangeNodes[2] != 0) {
        Gdynlight_ReleaseLight(&g_dynamicLightPool, (s32)player->rangeNodes[2]);
        player->rangeNodes[2] = 0;
    }
    if (player->rangeTimer != 0.0f) {
        light = (struct PlayerEffectLight *)player->rangeNodes[0];
        if (light == 0) {
            light = Gdynlight_AllocateLightNode(&g_dynamicLightPool, PLAYER_EFFECT_LIGHT_PATTERN);
        }
        if (light != 0) {
            player->rangeNodes[0] = (struct RangeNode *)light;
            placePlayerLight(player, light, g_playerFirstLightForwardOffset, &g_playerFirstLightHeight, &g_playerFirstLightRadius);
        }
        light = (struct PlayerEffectLight *)player->rangeNodes[1];
        if (light == 0) {
            light = Gdynlight_AllocateLightNode(&g_dynamicLightPool, g_playerSecondaryLightPattern);
        }
        if (light != 0) {
            player->rangeNodes[1] = (struct RangeNode *)light;
            placePlayerLight(player, light, g_playerSecondLightForwardOffset, &g_playerSecondLightHeight, &PLAYER_SECOND_LIGHT_RADIUS);
        }
        if (player->rangeTimer < g_playerRangeLightFirstInterval) {
            flicker = 1;
            if (player->rangeTimer < g_playerRangeLightSecondInterval) {
                flicker ^= (Graphu64_NextRandom() % 100) < 50;
            } else {
                if ((Graphu64_NextRandom() % 100) < 15) {
                    flicker = 0;
                }
            }
            if (player->rangeNodes[0] != 0) {
                ((struct PlayerEffectLight *)player->rangeNodes[0])->active = flicker;
            }
            if (player->rangeNodes[1] != 0) {
                ((struct PlayerEffectLight *)player->rangeNodes[1])->active = flicker;
            }
        }
    } else {
        if (player->rangeNodes[0] != 0) {
            Gdynlight_ReleaseLight(&g_dynamicLightPool, (s32)player->rangeNodes[0]);
            player->rangeNodes[0] = 0;
        }
        if (player->rangeNodes[1] != 0) {
            Gdynlight_ReleaseLight(&g_dynamicLightPool, (s32)player->rangeNodes[1]);
            player->rangeNodes[1] = 0;
        }
    }
    if (g_gameSettings.flags & 0x4000) {
        light = (struct PlayerEffectLight *)player->rangeNodes[2];
        if (light == 0) {
            light = Gdynlight_AllocateLightNode(&g_dynamicLightPool, PLAYER_MODE_LIGHT_PATTERN);
        }
        if (light != 0) {
            player->rangeNodes[2] = (struct RangeNode *)light;
            placePlayerLight(player, light, 0.0f, &g_playerRangeLightHeight, &g_playerRangeLightRadius);
        }
        if ((player->actionFlags & 0x20) && player->rangeNodes[2] != 0) {
            struct PlayerEffectLight *entry = (struct PlayerEffectLight *)player->rangeNodes[2];
            if (entry->pattern == PLAYER_MODE_LIGHT_PATTERN) {
                entry->pattern = g_playerAlternateModeLightPattern;
            } else {
                entry->pattern = PLAYER_MODE_LIGHT_PATTERN;
            }
        }
    }
}
