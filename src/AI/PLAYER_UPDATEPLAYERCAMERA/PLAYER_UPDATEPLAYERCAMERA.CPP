#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/WORLD.H"
#include <ultra64.h>
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "COMMON/MATH_HELPERS.H"
#include "../../../sdk/include/AUDIO/sprintf.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/GAMEPLAY_MOVEMENT.H"
#include "RENDER/PLAYER_SPAWN_PLACEMENT.H"
#include "GFX/TEXT/PLAYER_CAMERA_CALLBACK.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PLAYER_ACTION_AND_POSE_VIEWS.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"
#include "AI/NAV/NAV_UPDATECOMPUTERPLAYERSTATUS.H"
#include "COMMON/LEVEL_TRACK.H"
#include "include_asm.h"
extern f32 g_playerGroundMovementSpeedLimits[];
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/ENTRYRECATE.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "COMMON/PLAYERPROFILES.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "AI/PLAYER_DRAWTINTEDPLAYER.H"
#include "ENGINE/AUDIO/T2SOUNDELEMENT/SOUND_CONTEXT_CONTROL.H"

extern s32 Player_TryEnterHitReactionState(void *, void *);
extern s32 Player_TryThrowSelectedActor(void *, void *, s32 *);

extern void *g_weaponInfoByType[];

/* 8021CD70_7.CPP */
/* Draws a player's HUD for one frame unless the game state is 8 or 11: ticks the HUD animations,
   draws the health counter and its hurt flash (four corner sprites in an environment colour that
   fades with the flash), the lives or trial counter, the score counter with its animated icon and
   the ticker of fading player names, the second counter (count rule) or the squad score, the
   power-up icon and status sprite, the zoom gauge, the ammo pips for weapon 12, and finally the
   team and squad overlays. */
extern Gfx *g_displayListCursor;

extern char g_actorParticleEffectSystem;
extern s32 g_playerWeaponClassMode;
void TeamSelect_DrawWeaponWheelSprites(void *, Shared_HudView *, Shared_HudPlayer *);
void TeamSelect_DrawTeamWheelSprites(void *, Shared_HudView *, Shared_HudPlayer *);
void Playerai_DrawAnimatedSprite(void *, Shared_HudView *);
void Playerai_DrawAimHud(Shared_HudPlayer *, Shared_HudView *);
void Playerai_DrawAmmoCounters(Shared_HudPlayer *, Shared_HudView *);
void Playerai_DrawHudSprite1FC(Shared_HudPlayer *, Shared_HudView *);
void Playerai_DrawHudSprite201(Shared_HudPlayer *, Shared_HudView *);
s32 Particle_CountOwnerListOneEffects(void *, Shared_HudPlayer *);
s16 **Scene_StartWorldEffect(void *, s32, s32, s32);
void ItemMenu_DrawEntries(void *, Shared_HudPlayer *);
void OnScreen_UpdateMoverScript(void *);

f32 Menu_MeasureLine(u8 *p, f32 sx, f32 sy);
static inline CGameStatus *hudRules(void) {
    return &g_gameSettings.counters;
}
void Player_DrawHeadsUpDisplay(Shared_HudPlayer *player, Shared_HudView *view) {
    char text[16];
    f32 sx;
    f32 sy;
    f32 kx;
    f32 ky;
    f32 scaleX;
    f32 scaleY;
    f32 x;
    f32 y;
    f32 flashFade;
    f32 fade;
    f32 flashFade2;
    f32 fade2;
    f32 textScale;
    f32 nameZoom;
    f32 iconFade;
    f32 icon;
    f32 status;
    f32 zoom;
    f32 step;
    f32 stepOut;
    f32 limit;
    s32 n;
    s32 i;
    s32 k;
    s32 ammo;
    s32 j;
    s32 r;
    s32 g;
    s32 b;
    s32 score;
    s32 frames;
    s16 **res;
    s32 indent;
    s32 left;
    s32 top;
    s32 w;
    s32 width;
    s32 level;
    if (g_gameSettings.state != 11 && g_gameSettings.state != 8) {
        OnScreen_UpdateMoverScript(player->anim0);
        OnScreen_UpdateMoverScript(player->anim1);
        OnScreen_UpdateMoverScript(player->anim2);
        OnScreen_UpdateMoverScript(player->anim3);
        OnScreen_UpdateMoverScript(&player->livesAnim);
        OnScreen_UpdateMoverScript(player->anim5);
        OnScreen_UpdateMoverScript(&player->scoreAnim);
        OnScreen_UpdateMoverScript(&player->countAnim);
        OnScreen_UpdateMoverScript(&player->squadAnim);
        Playerai_DrawAimHud(player, view);
        if (view->flags == 0) {
            Playerai_DrawAnimatedSprite(player->effect, view);
        }
        TeamSelect_DrawWeaponWheelSprites(player->strokes, view, player);
        TeamSelect_DrawTeamWheelSprites(player->trails, view, player);
        ItemMenu_DrawEntries(player->marks, player);
        Onscrn_SetupSpriteMode(g_gameSettings.hudFade);
        sx = view->width / (f32) g_hudReferenceViewportWidth;
        sy = view->height / (f32) g_hudReferenceViewportHeight;
        if (g_frontendCurrentVideoModeIndex == 0) {
            kx = ky = 1.0f;
        } else {
            kx = ky = 1.5f;
        }
        scaleX = sx * kx;
        scaleY = sy * ky;
        if (hudRules()->state == 0) {
            Playerai_DrawAmmoCounters(player, view);
        }
        n = (player->health + 0xFF) >> 8;
        x = player->healthX * scaleX + view->x;
        y = player->healthY * scaleY + view->y + view->height;
        if (hudRules()->state == 0) {
            OnScreen_DrawSpriteNumber(n, x - scaleX * 3.0f, y - scaleY * 4.0f, scaleX, scaleY, 1, 0, 0);
        }
        n = player->health;
        if (n != player->flashHealth) {
            if (n < player->flashHealth) {
                player->flashAlpha += ((player->flashHealth - n) >> 8) * 5;
                if (n == 0) {
                    player->flashAlpha = 255.0f;
                }
                if (player->flashAlpha < 50.0f) {
                    player->flashAlpha = 50.0f;
                }
                if (player->flashAlpha > 255.0f) {
                    player->flashAlpha = 255.0f;
                }
                player->flashState = 2;
            }
            player->flashHealth = n;
        }
        /* The two flash blocks keep the centre's x in y and its y in x. */
        if (player->hurt > 0.0f) {
            flashFade = player->flashAlpha - 12.0f;
            fade = (flashFade < 0.0f) ? 0.0f : flashFade;
            player->flashAlpha = fade;
            if (player->fxFlags & 0x4000) {
                if (fade != 0.0f) {
                    r = 253.0f - (128.0f - fade * 0.512f);
                    g = 198.0f - fade * 0.792f;
                    b = 34.0f - fade * 0.136f;
                } else {
                    r = 125;
                    g = 198;
                    b = 34;
                }
            } else {
                if (fade != 0.0f) {
                    r = fade * 1.012f;
                    g = 105.0f - fade * 0.42f;
                    b = 179.0f - fade * 0.716f;
                } else {
                    r = 0;
                    g = 105;
                    b = 179;
                }
            }
            y = view->x + view->width * 0.5f;
            x = view->y + view->height * 0.5f;
            Onscrn_SetupSpriteMode(250);
            gDPSetEnvColor(g_displayListCursor++, (r), (g), (b), 250);
            for (k = 0; k < 4; k++) {
                OnScreen_DrawSpriteResource(520, k, y + scaleX * g_hudSpriteVerticalOffsets[k + 4], x + scaleY * g_hudSpriteHorizontalOffsets[k + 4], sx,
                              scaleY * 1.5f, 1);
            }
            player->flashState = 0;
        }
        if (player->flashState == 2) {
            flashFade2 = player->flashAlpha - 12.0f;
            fade2 = (flashFade2 < 0.0f) ? 0.0f : flashFade2;
            player->flashAlpha = fade2;
            if (fade2 > 0.0f) {
                y = view->x + view->width * 0.5f;
                x = view->y + view->height * 0.5f;
                r = 253;
                g = 0;
                b = 0;
                gDPSetEnvColor(g_displayListCursor++, (r), (g), (b), (player->flashAlpha));
                for (k = 0; k < 4; k++) {
                    OnScreen_DrawSpriteResource(520, k, y + scaleX * g_hudSpriteVerticalOffsets[k + 4], x + scaleY * g_hudSpriteHorizontalOffsets[k + 4], sx,
                                  scaleY * 1.5f, 1);
                }
            } else {
                player->flashState = 0;
            }
        }
        if (g_frontendCurrentVideoModeIndex == 0) {
            kx = ky = 0.75f;
        } else {
            kx = ky = 1.0f;
        }
        scaleX = sx * kx;
        scaleY = sy * ky;
        if (g_gameSettings.local == 0) {
            n = player->lives;
            if (player->livesLast != n) {
                OnScreen_StartMoverScript(&player->livesAnim, &g_hudLivesMoverScript);
                player->livesLast = n;
            }
            if (player->livesAnim != 0 && player->livesShown != 0) {
                x = player->livesX * sx + view->x;
                y = player->livesY * sy + view->y;
                OnScreen_DrawSpriteResource(300, 0, x + sx * 18.0f, y + sy * 28.0f, sx, sy, 1);
                OnScreen_DrawSpriteResource(502, 0, x, y, sx, sy, 1);
                OnScreen_DrawSpriteNumber(player->lives, x + sx * 30.0f, y + sy * 24.0f, sx, sy, 1, 0, 0);
            }
        } else if ((g_gameSettings.controllerMode == 1 || g_gameSettings.controllerMode == 4) && player->hideLives == 0) {
            n = player->lifeCount - 1;
            if (n < 0) {
                n = 0;
            }
            x = player->livesX * scaleX + view->x;
            y = player->livesY * scaleY + view->y;
            Onscrn_SetupSpriteMode(player->alpha);
            OnScreen_DrawSpriteNumber(n, x, y + scaleY * 22.0f, scaleX, scaleY, 1, 0, 0);
            OnScreen_DrawSpriteResource(502, 0, x + scaleX * 20.0f, y + scaleY * 16.0f, scaleX, scaleY * 1.5f, 1);
            if (g_gameSettings.counters.enabled != 0) {
                OnScreen_DrawSpriteResource(515, 0, x + scaleX * 40.0f, y + scaleY * 11.0f, scaleX, scaleY * 1.5f, 1);
            }
        }
        if (hudRules()->state == 0 && g_gameSettings.local != 0) {
            if (hudRules()->teams != 0) {
                if (player->owner->team != 0xFF) {
                    score = hudRules()->scores[player->owner->team];
                } else {
                    score = 0;
                }
            } else {
                score = player->owner->score;
            }
            if (score < -99) {
                score = -99;
            }
            if (player->scoreLast != score) {
                OnScreen_StartMoverScript(&player->scoreAnim, &g_hudScoreMoverScript);
                player->scoreLast = score;
                player->scoreFrame = 0;
            }
            if (player->scoreState == 0) {
                player->scoreState = 1;
            }
            player->scoreAnim = 1;
            player->alpha = 255.0f;
            if (player->scoreAnim != 0 && player->scoreState != 0) {
                frames = 1;
                if (g_gameSettings.counters.teams != 0) {
                    res = Scene_StartWorldEffect(&g_world, 516, 0, 1);
                } else {
                    res = Scene_StartWorldEffect(&g_world, 506, 0, 1);
                }
                if (res != NULL) {
                    frames = (*res != NULL) ? **res : 1;
                    Cache_UnlockResource(0, res);
                }
                x = player->scoreX * scaleX + view->x + view->width;
                y = player->scoreY * scaleY + view->y;
                if (x > 200.0f) {
                    x -= 12.0f;
                }
                Onscrn_SetupSpriteMode(player->alpha);
                OnScreen_DrawSpriteNumber(player->scoreLast, x + scaleX * 48.0f, y + scaleY * 22.0f, scaleX, scaleY, 1, 0, 0);
                if (player->scoreState < 2) {
                    if (hudRules()->enabled != 0) {
                        OnScreen_DrawSpriteResource(514, 0, x, y + scaleY * 11.0f, scaleX, scaleY * 1.5f, 1);
                    }
                    if (hudRules()->teams != 0) {
                        OnScreen_DrawSpriteResource(516, 0, x + scaleX * 8.0f, y + scaleY * 16.0f, scaleX, scaleY * 1.5f, 1);
                    } else {
                        OnScreen_DrawSpriteResource(506, 0, x + scaleX * 8.0f, y + scaleY * 16.0f, scaleX, scaleY * 1.5f, 1);
                    }
                    player->nameHead = 0;
                    player->nameTail = 0;
                    for (i = 0; i < 8; i++) {
                        player->names[i] = NULL;
                        player->nameFades[i] = 0xFF;
                    }
                } else {
                    if (++player->scoreFrame >= frames * 4) {
                        player->scoreFrame = 0;
                        player->scoreState = 1;
                        player->nameHead = 0;
                        player->nameTail = 0;
                        for (i = 0; i < 8; i++) {
                            player->names[i] = NULL;
                            player->nameFades[i] = 0xFF;
                        }
                    }
                    if (hudRules()->enabled != 0) {
                        OnScreen_DrawSpriteResource(514, 0, x, y + scaleY * 11.0f, scaleX, scaleY * 1.5f, 1);
                    }
                    if (hudRules()->teams != 0) {
                        OnScreen_DrawSpriteResource(516, player->scoreFrame % frames, x + scaleX * 8.0f, y + scaleY * 16.0f,
                                      scaleX, scaleY * 1.5f, 1);
                    } else {
                        OnScreen_DrawSpriteResource(506, player->scoreFrame % frames, x + scaleX * 8.0f, y + scaleY * 16.0f,
                                      scaleX, scaleY * 1.5f, 1);
                    }
                    OnScreen_SetupTextRendering();
                    OnScreen_SetTextScale(1.0f, 1.0f);
                    if (g_gameSettings.counters.enabled == 0) {
                        /* Names scroll right to left, each fading out from 0xFF in steps of 6. */
                        for (i = player->nameHead; i >= player->nameTail; i--) {
                            if (player->names[i] != NULL) {
                                if (g_frontendCurrentVideoModeIndex == 0 && g_playerWeaponClassMode == 1) {
                                    nameZoom = 0.75f;
                                    indent = 15;
                                } else {
                                    nameZoom = 1.0f;
                                    indent = 0;
                                }
                                scaleX *= nameZoom;
                                Libc_FormatString(text, s_hudPlayerNameFormat, player->names[i]->owner->name);
                                OnScreen_SetTextColors(0, 0, 0, 1, 1, 1);
                                textScale = g_tutorialStatusBars.width * 0.5f * scaleX * OnScreen_GetGlyphWidth();
                                scaleY *= nameZoom;
                                w = Menu_MeasureLine(text, textScale, OnScreen_GetGlyphWidth());
                                player->nameWidths[i] = w;
                                width = w;
                                for (j = player->nameHead; i < j; j--) {
                                    width += player->nameWidths[j] + 8;
                                }
                                left = (x - 12.0f) + indent;
                                top = y + 4.0f;
                                Onscrn_DrawText(text, left - width + 2, (top + 2) + scaleY * 16.0f,
                                              player->nameFades[i], 0, 0, scaleX * 0.5f, scaleY);
                                if (player->names[i] == player) {
                                    OnScreen_SetTextColors(0xFF, 0, 0, 1, 1, 1);
                                } else {
                                    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 1, 1, 1);
                                }
                                Onscrn_DrawText(text, left - width, top + scaleY * 16.0f, player->nameFades[i], 0, 0,
                                              scaleX * 0.5f, scaleY);
                                player->nameFades[i] -= 6;
                                if (player->nameFades[i] < 0) {
                                    player->nameFades[i] = 0;
                                    player->nameTail = (player->nameTail + 1) % 8;
                                }
                                scaleX /= nameZoom;
                                scaleY /= nameZoom;
                            }
                        }
                    }
                }
            }
            if (hudRules()->m_bFragTagOn != 0) {
                n = player->owner->count;
                if (player->countLast != n) {
                    OnScreen_StartMoverScript(&player->countAnim, &g_hudCountMoverScript);
                    if (player->countLast == -1) {
                        player->countState = 1;
                    }
                    player->countLast = n;
                }
                if (player->countState == 0) {
                    player->countState = 1;
                }
                player->countAnim = 1;
                if (player->countState != 0) {
                    n = 1;
                    res = Scene_StartWorldEffect(&g_world, 509, 0, 1);
                    if (res != NULL) {
                        if (*res != NULL) {
                            n = **res;
                        }
                        Cache_UnlockResource(0, res);
                    }
                    x = player->countX * scaleX + view->x + view->width;
                    y = player->countY * scaleY + view->y;
                    if (x > 200.0f) {
                        x -= 12.0f;
                    }
                    Onscrn_SetupSpriteMode(player->alpha);
                    OnScreen_DrawSpriteNumber(player->owner->count, x + scaleX * 48.0f, y + scaleY * 20.0f, scaleX, scaleY, 1,
                                  0, 0);
                    if (player->countState < 2) {
                        OnScreen_DrawSpriteResource(509, 0, x + scaleX * 8.0f, y + scaleY * 16.0f, scaleX, scaleY, 1);
                    } else {
                        if (++player->countFrame >= n * 4) {
                            player->countFrame = 0;
                            player->countState = 1;
                        }
                        OnScreen_DrawSpriteResource(509, player->countFrame % n, x + scaleX * 8.0f, y + scaleY * 16.0f, scaleX,
                                      scaleY, 1);
                    }
                }
            } else if (hudRules()->m_bCTFOn != 0) {
                if (player->owner->team != 0xFF) {
                    score = hudRules()->counts[player->owner->team];
                } else {
                    score = 0;
                }
                if (player->squadLast != score) {
                    OnScreen_StartMoverScript(&player->squadAnim, &g_hudSquadMoverScript);
                    if (player->squadLast == -1) {
                        player->squadState = 1;
                    }
                    player->squadLast = score;
                }
                if (player->squadState == 0) {
                    player->squadState = 1;
                }
                player->squadAnim = 1;
                if (player->squadState != 0) {
                    frames = 1;
                    res = Scene_StartWorldEffect(&g_world, 513, 0, 1);
                    if (res != NULL) {
                        if (*res != NULL) {
                            frames = **res;
                        }
                        Cache_UnlockResource(0, res);
                    }
                    x = player->squadX * scaleX + view->x + view->width;
                    y = player->squadY * scaleY + view->y;
                    if (x > 200.0f) {
                        x -= 12.0f;
                    }
                    Onscrn_SetupSpriteMode(player->alpha);
                    OnScreen_DrawSpriteNumber(score, x + scaleX * 48.0f, y + scaleY * 20.0f, scaleX, scaleY, 1, 0, 0);
                    if (player->squadState < 2) {
                        OnScreen_DrawSpriteResource(513, 0, x + scaleX * 8.0f, y + scaleY * 16.0f, scaleX, scaleY * 1.5f, 1);
                    } else {
                        if (++player->squadFrame >= frames * 4) {
                            player->squadFrame = 0;
                            player->squadState = 1;
                        }
                        OnScreen_DrawSpriteResource(513, player->squadFrame % frames, x + scaleX * 8.0f, y + scaleY * 16.0f,
                                      scaleX, scaleY * 1.5f, 1);
                    }
                }
            }
        }
        if (player->fxFlags & 0x10000) {
            level = player->fxTime;
            if (level != player->iconLast) {
                player->iconState = 2;
                player->iconLast = level;
            }
            if (player->iconState == 2) {
                iconFade = player->fxTime * 5.0f;
                icon = (iconFade > 255.0f) ? 255.0f : iconFade;
                player->iconAlpha = icon;
                if (icon > 0.0f) {
                    x = view->x + view->width * 0.5f;
                    y = view->y + view->height * 0.5f;
                    Onscrn_SetupSpriteMode(icon);
                    OnScreen_DrawSpriteResource(521, 0, x - scaleX * 31.0f, y - scaleY * 32.0f, scaleX, scaleY, 1);
                } else {
                    player->iconState = 0;
                }
            }
        }
        if ((player->fxFlags != 0 && player->fxFlags < 0x2000) || player->boost > 0.0f) {
            level = player->fxTime;
            if (level != player->statusLast || player->boost > 0.0f) {
                player->statusState = 2;
                player->statusLast = level;
            }
            if (player->statusState == 2) {
                if (player->fxFlags & 0x20) {
                    if (player->fxStage == 2) {
                        status = 255.0f - player->fxTime * 1.7f;
                        if (status < 0.0f) {
                            status = 0.0f;
                        }
                        player->statusAlpha = status;
                    } else if (player->fxStage == 3) {
                        player->statusAlpha = 0.0f;
                    } else {
                        player->statusAlpha = 255.0f;
                    }
                } else if (player->fxTime > 0.0f) {
                    player->statusAlpha = (player->fxTime * 5.0f > 255.0f) ? 255.0f : player->fxTime * 5.0f;
                } else if (player->boost > 0.0f) {
                    player->statusAlpha = 255.0f;
                }
                if (player->statusAlpha > 0.0f) {
                    x = view->x + view->width;
                    y = view->y + view->height;
                    level = 0;
                    if (player->boost > 0.0f) {
                        level = 1;
                    }
                    Onscrn_SetupSpriteMode(player->statusAlpha);
                    OnScreen_DrawSpriteResource(524, level, x - scaleX * 70.0f, y - scaleY * 140.0f, scaleX, scaleY, 1);
                } else {
                    /* Clears the icon state, not the status state. */
                    player->iconState = 0;
                }
            }
        }
        zoom = player->zoom;
        if (zoom < 1.0f) {
            step = (1.0f - g_playerReserveBounds_de[1]) * 0.25f;
            y = view->y + view->height;
            x = view->x;
            limit = g_playerReserveBounds_de[1] + step;
            if (zoom < limit) {
                level = 3;
            } else if (zoom < (limit += step)) {
                level = 2;
            } else if (zoom < limit + step) {
                level = 1;
            } else {
                level = 0;
            }
            Onscrn_SetupSpriteMode(0xFF);
            OnScreen_DrawSpriteResource(523, level, x + scaleX * 10.0f, y - scaleY * 140.0f, scaleX, scaleY, 1);
        } else if (zoom > 1.0f) {
            stepOut = (g_playerReserveBounds_de[0] - 1.0f) * 0.25f;
            y = view->y + view->height;
            x = view->x;
            if (g_playerReserveBounds_de[0] - stepOut < zoom) {
                level = 3;
            } else if (g_playerReserveBounds_de[0] - (stepOut + stepOut) < zoom) {
                level = 2;
            } else if (g_playerReserveBounds_de[0] - (stepOut + stepOut + stepOut) < zoom) {
                level = 1;
            } else {
                level = 0;
            }
            Onscrn_SetupSpriteMode(0xFF);
            OnScreen_DrawSpriteResource(522, level, x + scaleX * 10.0f, y - scaleY * 140.0f, scaleX, scaleY, 1);
        }
        if (player->weapon == 12 && player->kind != g_fragTagModelId) {
            ammo = 3 - Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem, player);
            if (player->ammo < ammo) {
                ammo = player->ammo;
            }
            x = view->x + view->width * 0.5f;
            y = view->y + view->height * 0.5f;
            for (i = 0; i < 3; i++, ammo--) {
                Onscrn_SetupSpriteMode(ammo > 0 ? 0xFF : 64);
                OnScreen_DrawSpriteResource(756, 0, x + g_hudPlayerMarkerHorizontalOffsets[i] * scaleX, y + scaleY * 64.0f, scaleX, scaleY, 1);
            }
        }
        if (hudRules()->state == 0) {
            if (player->owner->active == 1 && hudRules()->m_bFragTagOn != 0) {
                Playerai_DrawHudSprite1FC(player, view);
            }
            if (hudRules()->state == 0 && hudRules()->m_bCTFOn != 0 && player->owner->active != 0) {
                Playerai_DrawHudSprite201(player, view);
            }
        }
    }
}
/* Aims a player's view camera and updates the player: with a view at 0x5DC, camera mode 1 at 0x5D0
   looks from the player's eye (the body position plus the eye offset at 0x73C, raised at least 40.96)
   along the body heading with the player's angles and sway and the aim zoom at 0x7EC, and mode 2 orbits the player at the angle
   g_playerDebugThrowHeadingOffset and distance g_playerDebugThrowDistance, which input bits 0x200 and 0x100 turn and 0x800 and 0x400 pull
   in and push out; the camera is set through Gsky_SetPlayerViewInputs and the view refreshed through
   Camera_UpdateViewProjectionAndEffects before the player is updated through Playerai_UpdateAimAndLockMarker. */
extern void Gsky_SetPlayerViewInputs(void *, s32, f32, f32, f32, f32, f32, f32, f32, f32, Shared_Quad, s32, f32, f32);
extern void Camera_UpdateViewProjectionAndEffects(void *);
extern void Playerai_UpdateAimAndLockMarker(PlayerWeaponsUpdatePlayerCamera *);

void Player_UpdatePlayerCamera(PlayerWeaponsUpdatePlayerCamera *player, BodyWeaponsUpdatePlayerCamera *body) {
    void *view;
    f32 angle;
    f32 x;
    view = player->view;
    if (view != 0) {
        if (player->cameraMode == 1) {
            Gsky_SetPlayerViewInputs(view, 0, body->heading, player->angles[0] + player->sway[0] - player->pitchBase,
                          player->angles[1] + player->sway[1], player->angles[2] + player->sway[2],
                          body->x + player->eye[0], body->y, body->z + player->eye[2],
                          ((player->eye[1] + player->eyeOffset - player->crouch - player->duck) < (40.96f) ? (40.96f) : (player->eye[1] + player->eyeOffset - player->crouch - player->duck)), body->rotation, body->room, player->zoom,
                          3.0f);
        } else if (player->cameraMode == 2) {
            if (player->input & 0x200) {
                g_playerDebugThrowHeadingOffset += 0.06981318f;
            } else if (player->input & 0x100) {
                g_playerDebugThrowHeadingOffset -= 0.06981318f;
            } else if (player->input & 0x800) {
                g_playerDebugThrowDistance -= 4.096f;
            } else if (player->input & 0x400) {
                g_playerDebugThrowDistance += 4.096f;
            }
            angle = body->heading + g_playerDebugThrowHeadingOffset;
            x = body->x + g_playerDebugThrowDistance * Gu_Sinf(angle);
            Gsky_SetPlayerViewInputs(view, 1, angle, 0.0f, 0.0f, 0.0f, x, body->y + 81.92f,
                          body->z + g_playerDebugThrowDistance * Math_Cosf(angle), 0.0f, body->rotation, body->room,
                          0.0f, 3.0f);
        }
        Camera_UpdateViewProjectionAndEffects(view);
    }
    Playerai_UpdateAimAndLockMarker(player);
}
/* Regenerates a player's health at 0x5E4 toward the cap from Player_GetMaxHealth_Player: under flag 4 at 0x122C it adds g_frameElapsedTime times gFastRegen's rate and mirrors the result to 0x174 and 0x45C, otherwise, while the flag byte at g_frontendScreenStatus.settings.local is set, the speed at 0x18's 0x24 meets g_movementHealthRegenerationSpeedThreshold's threshold, the health is nonzero and the word 0x60F past that flag byte does not hold it back, it adds the speed scaled by g_movementHealthRegenerationSpeedScale, g_frameElapsedTime and g_movementHealthRegenerationTuning's rate. */
extern s32 Player_GetMaxHealth(SharedPlayer *p);
void Player_UpdateHealthRegeneration(SharedPlayer *p) {
    f32 f0;
    f32 f20;
    f32 cur;
    s32 cap;
    s32 val;
    if ((p->views122C.view122C_1.flags & 4) && p->views5E4.view5E4_2.health > 0) {
        cap = Player_GetMaxHealth(p);
        f20 = p->views5E4.view5E4_2.health + g_frameElapsedTime * g_fastHealthRegenerationTuning.second;
        f0 = cap;
        if (!(f0 <= f20)) {
            f0 = f20;
        }
        val = f0;
        p->views5E4.view5E4_2.health = val; p->views1C.view174_17.bodyHealth = val; p->views1C.view45C_31.mirroredHealth = p->views5E4.view5E4_2.health;
        return;
    }
    f20 = p->views18.view18_3.body->speed;
    if (g_frontendScreenStatus.settings.local == 0) return;
    if (f20 < g_movementHealthRegenerationSpeedThreshold) return;
    cur = p->views5E4.view5E4_2.health;
    if (cur == 0.0f) return;
    if (p->views5D8.view5D8_4.ctrl->flag != 0 && g_frontendScreenStatus.modes.tag != 0) return;
    f20 = cur + (s32)(f20 * g_movementHealthRegenerationSpeedScale) * (g_frameElapsedTime * g_movementHealthRegenerationTuning.first);
    p->views5E4.view5E4_2.health = RW_MIN_LT(f20, Player_GetMaxHealth(p));
}

/* 8021CD70_8.CPP */
extern char g_navigationGraph;

extern u8 *g_currentActorInstance;

extern struct Shared_Floor *g_collisionCurrentActor;

extern struct Shared_StateInfo g_playerSpecialAnimationTable[];
extern struct Shared_StateInfo g_playerActionStateHandlers[];
extern void Portal_UpdateActorCurrentNode(void *, void *);
extern void Actor_ApplySupportingPlatformMotion(void *, void *);
extern void Barrel_FillDamagePacket(void *, s32, s32, s32, s32, s32);
extern void TeamSelect_UpdateDraftPanel(void *, void *, void *);
extern void Cteamselect_UpdateTeamWheel(void *, void *, void *);
extern void Playerai_EmptyWeaponEffectHook(void *, void *);
extern void Playerai_ApplyDamagePacket(void *, void *, void *);
extern void Player_UpdatePlayerEffectLights(void *, void *);
extern s32 Player_GetAmmoCapacity(void *, s32, s32);
extern void Playerai_UpdateReactionReserve(void *);
extern void Playerai_UpdateDelayedDamage(void *);
extern void Playerai_SetInheritedMotionFlags(void *, void *, void *);
extern void Playerai_UpdateModelBlend(void *, void *);
extern s32 Playerai_TryEnterMotionFlagState(void *, void *);
extern s32 Playerai_TryEnterBodyFlagState(void *, void *);
extern s32 Unicol_MoveActorWithCollision(void *, CVector3, s32 *);
struct CCollisionInfo2_t;
extern s32 Unicol_SweepActorMotion(void *, CVector3, CVector3, struct CCollisionInfo2_t *, f32, f32, f32, f32);
extern void GameObject_ApplyMaterialCurrents(void *, void *, void *, s32);
extern void Gobjinst_ReadActorMotionIndex(void *);
extern s32 Gobjinst_ChooseAnimationVariant(void *, s32, s32);
extern void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);
extern void Gobjinst_UpdateActorGroundRotation(void *);
extern s32 Gobjinst_RequestAnimationKind(void *, s32, s32);

extern f32 InstHdr_GetActorReach(void *);
extern s32 InstHdr_GetActorMotionState(void *);
extern struct Shared_Surface *InstHdr_FindActorModelEntry(void *);
extern s32 SoundElement_PlaySoundAtPosition(s16, CVector3, s32, s32);

extern f32 Graphu64_GetTrianglePlaneHeight(struct Shared_Model *, f32, f32);
extern f32 Region_GetPolygonHeight(struct Shared_Model *, f32, f32);
extern void Link_DispatchActorLinks(void *, s32, void *);
extern void Link_DispatchObjectLinks(struct Shared_Model *, s32, void *);

extern void ItemMenu_UpdateToggleMenu(void *, void *);
extern void Pickup_TryCollectActor(void *, void *);
#if !(defined(VERSION_US_REV1))
const float g_playerHealthRegenerationConstants[4] = {
    68.26667f, 0.1f, 256.0f, 0.06666667f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_playerBodyMovementConstants[2] = {
    0.25f, 1.3333334f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_playerHealthRegenerationConstantsUsRev1[4] = {
    68.26667f, 0.1f, 256.0f, 0.06666667f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_playerBodyMovementConstantsUsRev1[2] = {
    0.25f, 1.3333334f,
};
#endif
void Player_UpdateBodyMovementAndActions(SharedPlayer *player)
{
  CVector3 prev;
  struct Shared_Input saved;
  CVector3 diff;
  struct Shared_Placed found;
  struct Shared_Scratch scratch;
  f32 depth;
  f32 swim;
  SharedPlayer *actor;
  s32 linkFlags;
  s32 soundFlags;
  s32 human;
  f32 scale;
  f32 remaining;
  f32 moved;
  f32 rise;
  f32 floor;
  f32 amount;
  f32 f22;
  f32 f21;
  f32 f20;
  f32 f0;
  struct Shared_Model *model;
  CVector3 *pos;
  struct Shared_Surface *material;
  struct Shared_Surface *before;
  struct Shared_Surface *after;
  struct Shared_Model *oldModel;
  struct Shared_Model *newModel;
  struct Shared_Pickup *entry;
  struct Shared_PickupDef *def;
  s32 *stateFlags;
  s32 ground;
  s32 flag;
  s32 hit;
  s32 sound;
  s32 first;
  s32 second;
  s32 low;
  s32 i;
  s32 enable;
  s32 offset;
  s32 count;
  s32 drain;
  s32 flags;
  void (*update)(void *, void *);
  s32 cur;
  s32 held;
  f32 goal;
  f32 change;
  struct Shared_CharInfo *slotInfo;
  struct Shared_Effect *effect;
  f32 lo;
  struct Shared_Surface *under;
  s32 slot;
  struct Shared_Game *game;
  CGameStatus *net;
  struct Shared_World *world;
  s16 next770;
  u16 next770u;
  linkFlags = 0;
  soundFlags = 0;
  scale = g_frameElapsedTime;
  if (player->views122C.view122C_4.fxFlags & 0x2000)
  {
    g_frameElapsedTime = scale * g_playerMovementTimeScale;
  }
  else
    if (player->views122C.view122C_4.fxFlags & 0x80)
  {
    g_frameElapsedTime = scale * g_playerAlternateMovementTimeScale;
  }
  else
    if (player->views5E8.view11E0_186.timeScale > 0.0f)
  {
    g_frameElapsedTime = scale * player->views5E8.view11E0_186.timeScale;
  }
  human = player->views1C.view5D0_43.controlKind == 2;
  actor = player;
  if (Cinema_IsSequenceInWindow() != 0)
  {
    human = 1;
  }
  game = &g_gameSettings;
  if (game->local != 0)
  {
    human = 1;
  }
  Portal_UpdateActorCurrentNode(&g_navigationGraph, player);
  if (player->views1450.view1450_0.computerControlled != 0)
  {
    Nav_UpdateComputerPlayerStatus((struct Brain *)player->views1454.view1454_0.aiController);
  }
  if (game->local != 0)
  {
    Cache_SetResourceActivityState(8);
  }
  enable = 0;
  player->views1C.view1D8_32.self = player;
  player->views1C.view4C0_47.self = player;
  if ((player->views1C.view38_2.flags & 0x1000) && (game->local == 0))
  {
    enable = (game - 1)->flags == 0;
  }
  SoundElement_SetMusicGainScalingEnabled(enable);
  if (g_frontendScreenStatus.settings.local == 0)
  {
    if ((!((g_playerAlternateActionModifierEnabled != 0) && (player->views5E8.view688_43.input.held & 0x20))) && (player->views5E8.view688_43.input.pressed & 0x800))
    {
      if (player->toggleState != 0)
      {
        player->toggleState = 0;
      }
      else
      {
        player->toggleState = 1;
      }
    }
    if ((((g_frontendScreenStatus.settings.local == 0) && (!((player->views5E8.viewCB8_163.weaponLocked != 0) && (player->views5E8.view938_162.weaponWheel != 0)))) && (!((g_playerAlternateActionModifierEnabled != 0) && (player->views5E8.view688_43.input.held & 0x20)))) && (player->views5E8.view688_43.input.pressed & 0x200))
    {
      slotInfo = g_weaponInfoByType[player->views5E8.view770_113.weapon];
      next770 = slotInfo->viewsC.viewC_0.next_s;
      next770u = slotInfo->viewsC.viewC_1.next_u;
      if (next770 != (-1))
      {
        if (player->views5E8.view602_14.slots[next770].owned != 0)
        {
          player->views5E8.view770_113.weapon = next770u;
        }
      }
    }
  }
  Player_UpdateHealthRegeneration(player);
  Playerai_UpdateDamageTimers(player);
  Playerai_UpdateReactionReserve(player);
  Playerai_UpdateDelayedDamage(player);
  actor->views1C.view100_8.flags &= ~0x20000;
  if (human && (player->views5E8.view11D8_147.jumpCooldown <= 0.0f))
  {
    Gobjinst_UpdateActorRootDisplacement(actor);
  }
  if (((u16) player->views5E8.view650_16.state) >= 2)
  {
    Actor_ApplySupportingPlatformMotion(actor, &actor->views1C.view170_23.actorBody);
  }
  net = &g_gameSettings.counters;
  if (((net->m_bFragTagOn != 0) && (net->m_FragTagFlipTimer == 0)) && (player->views5D8.view5D8_9.profile->remote == 1))
  {
    linkFlags |= 0x2000;
    soundFlags |= 0x400000;
  }
  if ((g_gameSettings.counters.m_bCTFOn != 0) && (player->views5D8.view5D8_9.profile->remote == 1))
  {
    linkFlags |= 0x2000;
  }
  if (player->views5E8.view704_67.lift > 0.0f)
  {
    f32 left = player->views5E8.view704_67.lift - g_frameElapsedTime;
    if (left < 0.0f)
    {
      left = 0.0f;
    }
    player->views5E8.view704_67.lift = left;
  }
  if (player->views5E8.view670_30.shield > 0.0f)
  {
    f32 left = player->views5E8.view670_30.shield - g_frameElapsedTime;
    if (left < 0.0f)
    {
      left = 0.0f;
    }
    player->views5E8.view670_30.shield = left;
  }
  saved = player->views5E8.view688_43.input;
  for (remaining = g_frameElapsedTime; remaining > 0.0f;)
  {
    remaining = 0.0f;
    player->views5E8.view654_25.prevState = (u16) player->views5E8.view650_16.state;
    player->views5E8.view65C_32.savedStateTimer = player->views5E8.view664_27.timer;
    model = actor->views0.view14_6.model;
    Player_UpdateMovementSpeedFactor(player, actor, InstHdr_FindActorModelEntry(actor));
    if (g_frontendScreenStatus.settings.local == 0)
    {
      pos = &player->views0.view8_3.pos;
      if (((model != 0) && (pos != 0)) && (model->flags & 0x40))
      {
        amount = (f32) ((s32) (Graphu64_GetTrianglePlaneHeight(model, pos->x, pos->z) - Region_GetPolygonHeight(model, pos->x, pos->z)));
        if (amount < 1024.0f)
        {
          SoundElement_SetClampedAudioLevel(1.0f - (amount * 0.0009765625f));
          goto rumbled;
        }
      }
      SoundElement_SetClampedAudioLevel(0.0f);
      rumbled:
      ;

      ;
      ;
    }
    player->views5E8.view66C_29.movementTimeScale = g_frameElapsedTime * player->views5E8.view784_117.movementRate;
    Playerai_UpdateModelBlend(player, actor);
    player->views5E8.view6C8_57.speed = Gu_Sqrtf((player->views5E8.view6C0_64.velX * player->views5E8.view6C0_64.velX) + (player->views5E8.view6C4_67.velZ * player->views5E8.view6C4_67.velZ));
    player->views5E8.view75C_89.bobSpeed += player->views5E8.view6C8_57.speed * 0.021000001579523087f;
    player->views5E8.view758_87.bobStrength += player->views5E8.view6C8_57.speed * 0.00010000000474974513f;
    player->views5E8.view6E8_79.movementPosition = actor->views0.view8_3.pos;
    player->views5E8.view658_31.stateTime += g_frameElapsedTime;
    ground = InstHdr_GetActorMotionState(actor);
    if (((ground != 0) && (player->views5E8.view6D0_71.onGround == 0)) && (player->views5E8.view6CC_70.lastVelY < (-51.19999694824219f)))
    {
      Gobjinst_ReadActorMotionIndex(actor);
    }
    player->views5E8.view6D0_71.onGround = ground;
    player->views5E8.view6CC_70.lastVelY = actor->views1C.view20_2.velY;
    if (((ground == 0) && (player->views5E8.view650_16.state != 15)) && (!(actor->views1C.view38_2.flags & 0x2000)))
    {
      player->views5E8.view6E4_77.airTime += g_frameElapsedTime;
    }
    else
    {
      player->views5E8.view6E4_77.airTime = 0.0f;
    }
    if ((((u16) player->views5E8.view650_16.state) >= 2) && (player->views5E4.view5E4_2.health != 0))
    {
      f32 target;
      Player_TryEnterHitReactionState(player, actor);
      Playerai_TryEnterMotionFlagState(player, actor);
      if (((Playerai_TryEnterBodyFlagState(player, actor) == 0) && (player->views5E8.view728_73.kickPitch != 0.0f)) && (!(actor->views1C.view38_2.flags & 0x100)))
      {
        if (((f32) XMath_AbsoluteInteger((s32) player->views5E8.view728_73.kickPitch)) < 0.7853982448577881f)
        {
          actor->views1C.view6C_9.yaw += player->views5E8.view728_73.kickPitch;
        }
        player->views5E8.view728_73.kickPitch = 0.0f;
      }
      target = 0.0f;
      if (((((struct Shared_CharInfo *)g_weaponInfoByType[player->views5E8.view62E_17.character])->ammo <= 0) || (player->views5E8.view7E8_105.zoomed == 0)) || ((g_gameSettings.counters.m_bFragTagOn != 0) && (player->views5D8.view5D8_9.profile->remote != 0)))
      {
        effect = &player->views5E8.view878_158.effect;
        player->views5E8.view7E8_105.zoomed = 0;
        cur = effect->state;
        if ((cur != 0) && (cur != 3))
        {
          effect->state = 3;
        }
      }
      if ((player->views5E4.view5E4_2.health != 0) && (player->views5E8.view7E8_105.zoomed != 0))
      {
        target = 0.7f;
        player->views5E8.view7E8_105.zoomed = 1;
      }
      player->views5E8.view7F0_133.targetZoom = target;
      Playerai_EmptyWeaponEffectHook(&player->views5E8.view878_158.effect, player);
      Graphu64_EaseValueToward(&player->views5E8.view7EC_132.smoothedZoom, target, 0.5f);
      if ((target == 0.0f) && (player->views5E8.view7EC_132.smoothedZoom < 0.01f))
      {
        player->views5E8.view7EC_132.smoothedZoom = 0.0f;
      }
    }
    if ((Cinema_IsSequenceInWindow() == 0) || (((u32) (((u16) player->views5E8.view650_16.state) - 22)) < 12))
    {
      update = player->views13B4.view13B4_5.states[player->views5E8.view650_16.state].update;
      if (update != 0)
      {
        update(player, actor);
      }
    }
    material = InstHdr_FindActorModelEntry(actor);
    if (material != 0)
    {
      GameObject_ApplyMaterialCurrents(actor, material, &player->views5E8.view6E8_79.movementPosition, 1);
      if ((material->flags & 0x4000) && (player->views5E4.view5E4_2.health > 0))
      {
        Player_SetPlayerState(player, player, 32);
        Barrel_FillDamagePacket(scratch.views0.view0_0.damage, 0, 0x3E700, 0x41CCCCCC, 128, 0);
        Playerai_ApplyDamagePacket(player, &player->views1C.view170_23.actorBody, scratch.views0.view0_0.damage);
      }
      if (material->flags & 0x80000)
      {
        player->views5E8.view854_147.effectCountdown -= g_frameElapsedTime;
        if (player->views5E8.view854_147.effectCountdown <= 0.0f)
        {
          if (player->views5E4.view5E4_2.health > 0)
          {
            Barrel_FillDamagePacket(scratch.views0.view0_0.damage, 0, material->sound << 8, 0x41CCCCCC, 128, 0);
            Playerai_ApplyDamagePacket(player, &player->views1C.view170_23.actorBody, scratch.views0.view0_0.damage);
          }
          player->views5E8.view854_147.effectCountdown = material->timer;
        }
        player->reservedWord12EC = 0;
      }
    }
    held = actor->views1C.view38_2.flags & 0xC0000;
    flag = held != 0;
    stateFlags = player->views13B4.view13B4_5.states[player->views5E8.view650_16.state].flags;
    if (player->views5E8.view71C_89.forceCrouch != 0)
    {
      flag = 1;
      if (player->views5E8.view650_16.state != 4)
      {
        Player_SetPlayerState(player, actor, 4);
      }
    }
    goal = 0.0f;
    if (flag)
    {
      goal = 40.96f;
    }
    depth = player->views5E8.view718_70.crouch;
    Graphu64_EaseValueToward(&depth, goal, 0.25f);
    do
    {
      change = depth - player->views5E8.view718_70.crouch;
      if (change < 0.0f)
      {
        if ((-change) < 0.001f)
        {
          goto still;
        }
      }
      else
        if (change < 0.001f)
      {
        still:
        change = 0.0f;

      }
      moved = player->views5E8.view718_70.crouch + change;
      change = 40.96f - moved;
      lo = -10.24f;
    }
    while (0);
    player->views5E8.view718_70.crouch = moved;
    if ((lo <= change) && (change <= 10.24f))
    {
      *stateFlags |= 0x80;
    }
    else
    {
      *stateFlags &= ~0x80;
    }
    {
      f32 target = 0.0f;
      f32 step;
      if (((u32) (((u16) player->views5E8.view650_16.state) - 9)) < 4)
      {
        target = 66.56f;
      }
      swim = player->views5E8.view720_90.swim;
      Graphu64_EaseValueToward(&swim, target, 0.25f);
      step = swim - player->views5E8.view720_90.swim;
      if (step < 0.0f)
      {
        if ((-step) < 0.001f)
        {
          goto calm;
        }
      }
      else
        if (step < 0.001f)
      {
        calm:
        step = 0.0f;

      }
      player->views5E8.view720_90.swim += step;
    }
    rise = (((player->views18.view18_5.body->ceiling - player->views5E8.view780_116.cameraHeightOffset) - player->views5E8.view718_70.crouch) - player->views5E8.view720_90.swim) - player->views5E8.view6F4_83.heightDelta;
    if (rise > 0.0f)
    {
      f22 = InstHdr_GetActorReach(actor);
      f21 = Gobjinst_GetActorRadius(actor);
      f20 = Gobjinst_GetActorHeight(actor);
      f0 = InstHdr_GetActorBaseOffset(actor);
      scratch.views0.view0_1.to.x = actor->views0.view8_3.pos.x;
      scratch.views0.view0_1.to.y = actor->views0.view8_3.pos.y + rise;
      scratch.views0.view0_1.to.z = actor->views0.view8_3.pos.z;
      if (Unicol_SweepActorMotion(actor, actor->views0.view8_3.pos, scratch.views0.view0_1.to, &g_playerCollisionProbe, f22, f21, f20, f0) != 0)
      {
        floor = g_collisionCurrentActor->y - actor->views0.view8_3.pos.y;
        player->views5E8.view6E8_79.movementPosition.y -= rise - floor;
        rise = floor;
      }
    }
    player->views5E8.view6F4_83.heightDelta += rise;
    Playerai_SetInheritedMotionFlags(player, actor, material);
    if (player->views5E8.view678_40.powerupCountdown > 0.0f)
    {
      player->views5E8.view678_40.powerupCountdown -= g_frameElapsedTime;
      if (player->views5E8.view678_40.powerupCountdown < 0.0f)
      {
        player->views5E8.view678_40.powerupCountdown = 0.0f;
      }
    }
    Player_UpdatePlayerEffectLights(player, actor);
    oldModel = actor->views0.view14_6.model;
    prev = actor->views0.view8_3.pos;
    before = InstHdr_FindActorModelEntry(actor);
    if (player->views5E8.view5EA_2.moveEnabled != 0)
    {
      actor->views1C.view100_8.flags |= 0x10000;
      if (player->views5E8.view11D8_147.jumpCooldown > 0.0f)
      {
        player->views5E8.view6E8_79.movementPosition = player->views0.view8_3.pos;
      }
      hit = Unicol_MoveActorWithCollision(actor, player->views5E8.view6E8_79.movementPosition, stateFlags);
      actor->views1C.view100_8.flags &= ~0x10000;
    }
    else
    {
      hit = 0;
    }
    newModel = actor->views0.view14_6.model;
    after = InstHdr_FindActorModelEntry(actor);
    if (before != after)
    {
      Link_DispatchObjectLinks(oldModel, linkFlags | 2, actor);
      Link_DispatchObjectLinks(newModel, linkFlags | 1, actor);
      if ((after != 0) && (after->flags & 0x80000))
      {
        player->views5E8.view854_147.effectCountdown = after->timer;
      }
    }
    Scene_UpdateMovementTriggers(&g_world, actor, &prev, &actor->views0.view8_3.pos);
    if (hit != 0)
    {
      if ((g_currentActorInstance != 0) && ((*g_currentActorInstance) == 1))
      {
        Link_DispatchActorLinks(g_currentActorInstance, soundFlags | 2, actor);
      }
      if (g_collisionProbeActorOne != 0)
      {
        Link_DispatchObjectLinks(g_collisionProbeActorOne, linkFlags | 4, actor);
      }
      Player_TryThrowSelectedActor(player, actor, stateFlags);
      Player_ReturnZeroStub(player, actor, stateFlags);
      if ((g_playerMovementRuleMode == 2) && (((u32) (((u16) player->views5E8.view650_16.state) - 5)) < 2))
      {
        if (actor->views1C.view20_2.velY > 0.0f)
        {
          actor->views1C.view20_2.velY = 0.0f;
        }
        player->views5E8.view650_16.state = 6;
        player->views5E8.view6C4_67.velZ *= 0.001f;
        player->views5E8.view6C0_64.velX *= 0.001f;
      }
    }
    if ((g_currentActorInstance != 0) && ((*g_currentActorInstance) == 3))
    {
      Pickup_TryCollectActor(player, g_currentActorInstance);
    }
    if ((before != 0) && (after != 0))
    {
      if (after->flags & 0x4000000)
      {
        if (after->item != player->views5E8.view5EC_5.currentItem)
        {
          player->views5E8.view5EC_5.currentItem = after->item;
        }
      }
      if (after->flags & 0x8000000)
      {
        player->views5E8.view5EC_5.currentItem = after->item;
        player->views5E8.view5F0_9.pendingItem = after->item;
        g_world.selectionValues[3] = after->item;
      }
    }
    world = &g_world;
    for (i = 0; i < world->count; i++)
    {
      entry = world->objects[i];
      if (entry != 0)
      {
        if ((!(entry->def->flags & 4)) && ((def = entry->def) != 0))
        {
          diff.x = player->views0.view8_3.pos.x - entry->pos.x;
          diff.y = player->views0.view8_3.pos.y - entry->pos.y;
          diff.z = player->views0.view8_3.pos.z - entry->pos.z;
          if (((f32) ((s32) Gu_Sqrtf(((diff.x * diff.x) + (diff.y * diff.y)) + (diff.z * diff.z)))) < def->radius)
          {
            if (Scene_FindPlacedObjectsByKey(&g_world, -1, def->item, &found, 1) != 0)
            {
              world->offset.x = player->views0.view8_3.pos.x - found.pos.x;
              world->offset.y = player->views0.view8_3.pos.y - found.pos.y;
              world->offset.z = player->views0.view8_3.pos.z - found.pos.z;
            }
            else
            {
              world->offset = diff;
            }
            SoundElement_PlaySoundAtPosition(560, player->views0.view8_3.pos, 0, -1);
            Player_PlacePlayerAtSpawnPoint(player, def->item, 0, 0);
            break;
          }
        }
      }
    }

    player->views5E8.view688_43.input.pressed = 0;
    player->views5E8.view688_43.input.reservedWord = 0;
    player->views5E8.view688_43.input.reservedWord1 = 0;
    player->views5E8.view688_43.input.reservedWord2 = 0;
  }

  player->views5E8.view688_43.input = saved;
  {
    f32 fade = player->views5E8.view11E0_186.timeScale;
    g_frameElapsedTime = scale;
    if (fade != 0.0f)
    {
      f32 left = fade - (scale * 0.042857144f);
      if (left < 0.0f)
      {
        left = 0.0f;
      }
      if (player->views5E8.view678_40.powerupCountdown)
      {
        fade = left;
      }
      else
      {
        fade = left;
      }
      player->views5E8.view11E0_186.timeScale = fade;
    }
  }
  under = InstHdr_FindActorModelEntry(actor);
  if ((under != 0) && (under->flags & 0x4000))
  {
    actor->views1C.view20_2.velY = 0.0f;
  }
  else
    if (actor->views0.view8_3.pos.y < (g_sceneMinimumActorHeight - 5120.0f))
  {
    Player_PlacePlayerAtSpawnPoint(player, player->views5E8.view5EC_5.currentItem, 0, 0);
  }
  if (InstHdr_GetActorMotionState(actor) != 0)
  {
    player->views5E8.view6F8_84.previousTargetPosition = actor->views0.view8_3.pos;
  }
  if (human)
  {
    sound = 102;
    if (g_frontendScreenStatus.settings.local != 0)
    {
      if ((g_gameSettings.counters.m_bFragTagOn != 0) && (player->views5D8.view5D8_9.profile->remote != 0))
      {
        sound = g_fragTagModelId;
      }
      else
      {
        sound = g_characterModelIds[player->views18.view18_5.body->kind];
        player->views0.view3_2.team = player->views5D8.view5D8_9.profile->team;
      }
    }
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, player, sound, player->views5E8.view86C_125.animationId);
    if (player->views5E8.view870_157.previousAnimationId != player->views5E8.view86C_125.animationId)
    {
      if ((Gobjinst_RequestAnimationKind(actor, player->views5E8.view86C_125.animationId, 0) == 0) && (Cinema_IsSequenceInWindow() != 0))
      {
        Gobjinst_RequestAnimationKind(actor, 7000, 0);
      }
    }
    first = Gobjinst_ChooseAnimationVariant(actor, player->views5E8.view86C_125.animationId, -1);
    second = Gobjinst_ChooseAnimationVariant(actor, player->views5E8.view86C_125.animationId, first);
    low = second;
    if (second > first)
    {
      low = first;
    }
    flag = second;
    if (flag < first)
    {
      flag = first;
    }
    if (actor->views1C.view10E_20.animPending != 0)
    {
      if (actor->views1C.view108_16.anim == low)
      {
        if (Graphu64_RandomFloat(100.0f) < 0.4f)
        {
          Gobjinst_RequestAnimationIndex(actor, flag, 0);
          actor->views1C.view10E_20.animPending = 0;
        }
      }
      else
      {
        Gobjinst_RequestAnimationIndex(actor, low, 0);
        actor->views1C.view10E_20.animPending = 0;
      }
    }
  }
  if (!human)
  {
    Gobjinst_UpdateActorGroundRotation(actor);
  }
  player->views1C.view2E8_37.emitter.pos = player->views0.view8_3.pos;
  player->views1C.view2E8_37.emitter.model = player->views0.view14_6.model;
  player->views1C.view2E8_37.emitter.reservedFloat = player->views1C.view40_5.emitterFloat;
  player->views1C.view2E8_37.emitter.yaw = player->views1C.view6C_9.yaw;
  player->views1C.view2E8_37.emitter.rotation = player->views1C.view5C_6.emitterQuad;
  player->views5E8.view774_115.requestedPosition = player->views0.view8_3.pos;
  if ((g_gameSettings.flags & 8) || ((g_gameSettings.counters.enabled != 0) && (player->views5D8.view5D8_9.profile->counts != 0)))
  {
    player->views5E8.view5F4_13.ammo[0] = Player_GetAmmoCapacity(player, 0, 0);
    player->views5E8.view5F4_13.ammo[1] = Player_GetAmmoCapacity(player, 1, 0);
    player->views5E8.view5F4_13.ammo[2] = Player_GetAmmoCapacity(player, 2, 0);
  }
  if (g_gameSettings.flags & 4)
  {
    for (slot = 21; slot >= 0; slot--)
    {
      player->views5E8.view602_14.slots[slot].owned = 1;
    }

  }
  if (player->views5DC.view5DC_8.hud != 0)
  {
    player->views5DC.view5DC_8.hud->score = player->views16D4.view16D4_0.score;
    player->views5DC.view5DC_8.hud->bonus = player->pendingBonus;
  }
  if (player->pendingBonus != 0)
  {
    count = player->pendingBonus;
    drain = (count * 2) / 3;
    if (drain < 5)
    {
      drain = 5;
    }
    if (count < drain)
    {
      player->pendingBonus = 0;
    }
    else
    {
      player->pendingBonus = count - drain;
    }
  }
  TeamSelect_UpdateDraftPanel(&player->views5E8.view938_162.weaponWheel, player, &player->views1C.view458_40.weaponSelectionContext);
  Cteamselect_UpdateTeamWheel(&player->views5E8.viewCCC_164.teamWheel, player, &player->views1C.view458_40.weaponSelectionContext);
  if (player->views5E8.view62E_17.character == 0)
  {
    player->views13B4.view13B4_5.states = g_playerSpecialAnimationTable;
  }
  else
  {
    player->views13B4.view13B4_5.states = g_playerActionStateHandlers;
  }
  ItemMenu_UpdateToggleMenu(&player->views5E8.viewD40_165.toggleMenu, player);
  if (player->views5E8.view11D8_147.jumpCooldown > 0.0f)
  {
    player->views5E8.view11D8_147.jumpCooldown -= g_frameElapsedTime;
    if (player->views5E8.view11D8_147.jumpCooldown <= 0.0f)
    {
      player->views1C.view100_8.flags |= 0x1000000;
    }
  }
  if (player->views5E8.view11DC_185.timeScaleCountdown > 0.0f)
  {
    player->views5E8.view11DC_185.timeScaleCountdown -= scale;
    if (player->views5E8.view11DC_185.timeScaleCountdown <= 0.0f)
    {
      player->views5E8.view11DC_185.timeScaleCountdown = 0.0f;
      player->views122C.view122C_4.fxFlags &= ~0x2000;
    }
  }
  if (player->views5E8.view11EC_189.glowDuration > 0.0f)
  {
    f32 left = player->views5E8.view11EC_189.glowDuration - g_frameElapsedTime;
    if (!(left >= 0.0f))
    {
      left = 0.0f;
    }
    player->views5E8.view11EC_189.glowDuration = left;
  }
  player->views5E8.view688_43.input.shadow->pos = player->views0.view8_3.pos;
  if ((player->views1450.view1450_0.computerControlled != 0) && (g_gameSettings.counters.transitionActive == 0))
  {
    offset = 23;
  }
  else
  {
    offset = 0;
    if (g_playerWeaponClassMode != 1)
    {
      offset = 23;
    }
  }
  ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, &player->views1C.view2E8_37.emitter, ((struct Shared_CharInfo *)g_weaponInfoByType[player->views5E8.view62E_17.character])->sound + offset, player->views1C.view484_44.voice->bank);
  if (!(player->views1C.view100_8.flags & 0x400))
  {
    player->views5E8.view870_157.previousAnimationId = player->views5E8.view86C_125.animationId;
  }
  if (player->views122C.view122C_4.fxFlags & 0x4000)
  {
    if (player->views5E8.view11D8_147.jumpCooldown <= 0.0f)
    {
      player->views122C.view122C_4.fxFlags &= ~0x4000;
    }
  }
  if (player->views122C.view122C_4.fxFlags & 0x2000)
  {
    if (player->views5E8.view11DC_185.timeScaleCountdown <= 0.0f)
    {
      player->views122C.view122C_4.fxFlags &= ~0x2000;
    }
  }
  if ((!(player->views122C.view122C_4.fxFlags & 0x10020)) && (player->views122C.view122C_4.fxFlags != 0))
  {
    player->fxTime -= g_frameElapsedTime;
    if (player->fxTime <= 0.0f)
    {
      player->fxLevel = 0.0f;
      player->fxStage = -1;
      player->fxTime = 0.0f;
      player->fxSpeed = 0.0f;
      player->views122C.view122C_4.fxFlags &= 0xFFFF6000;
    }
    else
    {

      f32 right;
      f32 prior;
      f32 left;
      prior = player->fxLevel;
      right = player->rightAxisValue;
      left = prior - right;
      if (left < 0.0f)
      {
        left = 0.0f;
      }

      if (player->views5E8.view678_40.powerupCountdown)
      {
        right = left;
      }
      else
      {
        right = left;
      }
      player->fxLevel = right;
    }
  }
  else
    if (player->views122C.view122C_4.fxFlags & 0x10000)
  {
    player->fxTime = ((player->fxTime--) < 0.0f) ? (0.0f) : (player->fxTime--);
    player->views5E8.view5F4_13.ammo[1] = ((player->views5E8.view5F4_13.ammo[1]--) < 0) ? (0) : (player->views5E8.view5F4_13.ammo[1]--);
    if ((player->views5E8.view5F4_13.ammo[1] == 0) || (player->fxTime == 0.0f))
    {
      player->fxTime = 0.0f;
      player->views122C.view122C_4.fxFlags &= ~0x18400;
    }
  }
  else
    if (player->views122C.view122C_4.fxFlags & 0x20)
  {
    if (player->fxStage == (-1))
    {
      player->fxTime = 0.0f;
      player->fxStage = 0;
      player->fxSpeed = 75.0f;
    }
    if (player->fxStage == 0)
    {
      player->fxTime += g_frameElapsedTime;
      if ((player->fxTime > 15.0f) || (player->fxTime < 0.0f))
      {
        player->fxSpeed = -player->fxSpeed;
      }
      if (player->fxTime > 30.0f)
      {
        player->fxTime = 0.0f;
        player->fxStage = 1;
        player->fxSpeed = 20.0f;
      }
    }
    else
      if (player->fxStage == 1)
    {
      player->fxTime += g_frameElapsedTime;
      if (player->fxTime > 75.0f)
      {
        player->fxStage = 2;
        player->fxTime = 0.0f;
      }
    }
    else
      if (player->fxStage == 2)
    {
      player->fxTime += g_frameElapsedTime;
      if (player->fxTime >= 150.0f)
      {
        player->fxStage = 3;
        player->fxTime = 0.0f;
      }
    }
    else
      if (player->fxStage == 3)
    {
      player->fxTime += player->fxSpeed;
      if (player->fxTime > 600.0f)
      {
        player->fxStage = -1;
        player->fxTime = 0.0f;
        player->views122C.view122C_4.fxFlags &= ~0x20;
      }
    }
  }
}

/* Player_SetPlayerState_PlayerUpdateplayercamera.CPP */
/* Switches a player to a new state unless option g_motionVisibilitySettings is on, Playerai_IsRoundEndState refuses and the
   state is not 0x13 to 0x15: keeps the previous state and timer, clears flag 0x800000, runs the new
   state's entry handler from the player's state table at 0x13B4, loads the state's timer and its
   nonzero parameter at 0x86C, and returns 1 with the counter at 0x658 cleared when the handler left
   the state in place, otherwise 0. */

extern s32 Playerai_IsRoundEndState(void *player);

s32 Player_SetPlayerState(SharedPlayer *player, void *stateContext, s32 state) {
    void (*enter)(void *, void *);
    s32 parameter;

    if (g_gameSettings.local != 0 && Playerai_IsRoundEndState(player) != 0 && state != 21 && state != 19 && state != 20) {
        return 0;
    }
    player->views5E8.view652_20.previous = player->views5E8.view650_16.state;
    player->views5E8.view660_26.previousTimer = player->views5E8.view664_28.timer;
    player->views5E8.view650_16.state = state;
    player->views1C.view100_9.flags &= ~0x800000;
    enter = player->views13B4.view13B4_1.states[state].enter;
    if (enter != 0) {
        enter(player, stateContext);
    }
    player->views5E8.view664_28.timer = player->views13B4.view13B4_1.states[player->views5E8.view650_16.state].timer;
    parameter = player->views13B4.view13B4_1.states[player->views5E8.view650_16.state].parameter;
    if (parameter != 0) {
        player->views5E8.view86C_126.parameter = parameter;
    }
    if (player->views5E8.view650_16.state == state) {
        player->views5E8.view658_22.counter = 0;
        return 1;
    }
    return 0;
}

/* Sets a player's movement speed factor at 0x784: g_playerBaseAndEasyMovementFactors[0] in states 0 and 1, otherwise the
   character's speed at 0x1C of its descriptor, which for a computer player (0x1450) is scaled twice by
   its skill byte at 0x93 (g_playerBaseAndEasyMovementFactors[1] then g_playerMediumAndHardMovementFactors[1] for skill 0, g_playerMediumAndHardMovementFactors[0] then g_playerGroundMovementSpeedLimits
   for skill 1, unchanged for skill 2, other values reset to 0), then by the game option factor at 0x20
   of g_gameSettings when enabled at 0x1D, and by the ground's factor at 0x30 when state bits 3 at 0x38 are
   clear, there is ground, and InstHdr_GetActorMotionState reports true or the ground is flagged 0x800. */


void Player_UpdateMovementSpeedFactor(void *actorView, void *bodyActor, PlayerGroundContactView *ground) {
    u8 *options;

    if ((u16)((Shared_ActorView *)actorView)->action < 2) {
        ((Shared_ActorView *)actorView)->speedFactor = g_playerBaseAndEasyMovementFactors[0];
        return;
    }
    ((Shared_ActorView *)actorView)->speedFactor = ((MovementDescriptor *)(((PlayerCameraMotionView *)bodyActor)->definition))->speed;
    if (((Shared_ActorView *)actorView)->remote != 0) {
        switch (((Shared_ActorView *)actorView)->controls->difficulty) {
        default:
            ((Shared_ActorView *)actorView)->controls->difficulty = 0;
        case 0:
            ((Shared_ActorView *)actorView)->speedFactor *= g_playerBaseAndEasyMovementFactors[1];
            break;
        case 1:
            ((Shared_ActorView *)actorView)->speedFactor *= g_playerMediumAndHardMovementFactors[0];
            break;
        case 2:
            break;
        }
        if (((Shared_ActorView *)actorView)->remote != 0) {
            switch (((Shared_ActorView *)actorView)->controls->difficulty) {
            default:
                ((Shared_ActorView *)actorView)->controls->difficulty = 0;
            case 0:
                ((Shared_ActorView *)actorView)->speedFactor *= g_playerMediumAndHardMovementFactors[1];
                break;
            case 1:
                ((Shared_ActorView *)actorView)->speedFactor *= g_playerGroundMovementSpeedLimits[0];
                break;
            case 2:
                break;
            }
        }
    }
    options = (u8 *)&g_gameSettings;
    if (options[29] != 0) {
        ((Shared_ActorView *)actorView)->speedFactor *= ((Shared_Game *)options)->speedFactor;
    }
    if (!(((PlayerCameraMotionView *)(bodyActor))->flags & 3) && ground != 0
        && (InstHdr_GetActorMotionState(bodyActor) != 0 || (ground->flags & 0x800))) {
        ((Shared_ActorView *)actorView)->speedFactor *= ground->speedFactor;
    }
}


/* Check the ammo required by the selected primary or alternate weapon mode. */
s32 Player_HasAmmoForMode(void *object, s32 weaponNumber)
{
    Player *player = object;
    s32 weapon = weaponNumber;
    s32 slot;
    WeaponInfo *definition;
    s16 *condition;

    definition = g_weaponInfoByType[weapon];
    if (player->gear == 1) {
        condition = definition->weaponClass;
    } else {
        condition = definition->alternateClass;
    }
    slot = condition != 0 ? condition[0] : -1;
    if (slot != -1) {
        if (player->gear == 2) {
            switch (weapon) {
            default: {
                s16 *alternate = ((WeaponInfo *)g_weaponInfoByType[weapon])->alternateClass;
                if (alternate != 0) {
                    return player->ammo[slot] >= alternate[3];
                }
                return -1;
            }
            case 4:
                return player->ammo[slot] >= 48;
            case 3:
                return player->ammo[slot] >= 25;
            }
        }
        if (player->gear == 1) {
            switch (weapon) {
            default: {
                s16 *primary = ((WeaponInfo *)g_weaponInfoByType[weapon])->weaponClass;
                if (primary != 0) {
                    return player->ammo[slot] >= primary[3];
                }
                return -1;
            }
            case 4:
                return player->ammo[slot] >= 5;
            case 3:
                return player->ammo[slot] >= 3;
            }
        }
    }
    return -1;
}


/* 8021CD70_10.CPP */
/* Adds ammunition to a player's weapon slot: computes the slot's cap as Player_IsAmmoPickupBelowCapacity does (zero for
   no slot, the character's cap unless option g_gameControllerMode is 1, otherwise g_baseAmmoCapacities's cap plus the
   profile bonus from g_localPlayerProfiles unless the flag at 0x1450 is set), and when the slot has room it
   selects weapon 1, 5 or 4 at 0xCC0 for slots 0, 1 and 2 if the slot was empty and ammunition is
   added, then adds the amount clamped to the cap. Returns whether the slot had room. Adapted from
   Player_IsAmmoPickupBelowCapacity with the count read once into an int and the weapon selection as a switch. */

extern void *Pickup_FindAmmoEntry(s32);

s32 Player_AddAmmo(void *player, s32 slot, s32 amount) {
    s16 *count;
    s32 cap;
    s32 room;
    s32 total;
    s32 have;

    count = (&((Shared_ActorView *)(player))->ammo[0] + slot);
    if (slot == -1) {
        cap = 0;
    } else if (g_gameSettings.controllerMode != 1) {
        cap = ((Desc *)((Shared_ActorView *)(player))->model)->caps[slot];
    } else {
        cap = g_baseAmmoCapacities[slot];
        if (((Shared_ActorView *)(player))->remote == 0) {
            if (slot == 0) {
                cap += g_localPlayerProfiles[((Shared_ActorView *)(player))->mode].bonus0;
            } else if (slot == 1) {
                cap += g_localPlayerProfiles[((Shared_ActorView *)(player))->mode].bonus1;
            } else if (slot == 2) {
                cap += g_localPlayerProfiles[((Shared_ActorView *)(player))->mode].bonus2;
            }
        }
    }
    have = *count;
    room = have < cap;
    if (room) {
        if (have == 0 && amount > 0) {
            switch (slot) {
            case 0:
                ((Shared_ActorView *)(player))->strokes.word.unk_0x0CC0 = 1;
                break;
            case 1:
                ((Shared_ActorView *)(player))->strokes.word.unk_0x0CC0 = 5;
                break;
            case 2:
                ((Shared_ActorView *)(player))->strokes.word.unk_0x0CC0 = 4;
                break;
            }
        }
        total = (s16) (*count += amount);
        if (total > cap) {
            total = cap;
        }
        *count = total;
    }
    return room;
}

/* Returns whether a player can take more ammunition for a pickup: looks up the pickup's weapon slot
   through Pickup_FindAmmoEntry, takes the cap as zero for no slot, the character's cap at 0x108 when option
   g_gameControllerMode is not 1, or otherwise g_baseAmmoCapacities's cap raised, unless the flag at 0x1450 is set, by the
   player profile's bonus byte for slots 0, 1 and 2 in g_localPlayerProfiles, and compares the slot's count at
   0x5F4 against it. */

s32 Player_IsAmmoPickupBelowCapacity(void *context, s32 pickupType) {
    void *pickup;
    s32 slot;
    s16 *count;
    s32 cap;
    s32 base;

    pickup = Pickup_FindAmmoEntry(pickupType);
    if (pickup == 0) {
        return 0;
    }
    slot = ((AmmoPickupDefinition *)(pickup))->slot;
    count = (&((Shared_ActorView *)(context))->ammo[0] + slot);
    if (slot == -1) {
        cap = 0;
    } else {
        if (g_gameSettings.controllerMode != 1) {
            base = ((Desc *)((Shared_ActorView *)(context))->model)->caps[slot];
        } else {
            base = g_baseAmmoCapacities[slot];
            if (((Shared_ActorView *)(context))->remote == 0) {
                if (slot == 0) {
                    base += g_localPlayerProfiles[((Shared_ActorView *)(context))->mode].bonus0;
                } else if (slot == 1) {
                    base += g_localPlayerProfiles[((Shared_ActorView *)(context))->mode].bonus1;
                } else if (slot == 2) {
                    base += g_localPlayerProfiles[((Shared_ActorView *)(context))->mode].bonus2;
                }
            }
        }
        cap = base;
    }
    return *count < cap;
}

/* Starts a player's ducking states from input: with button 0x1000 held and the player not already
   down (states 9 to 0xC or 0x26) it enters state 0xC, or while being hit (states 0x13 to 0x15) keeps
   the button latched at 0x38 instead; otherwise, when not being hit, holding direction bits 0x2000
   without 0x3, on the ground or descending no faster than g_playerGroundMovementSpeedLimits[1] and not already down, it
   enters state 0xA. Returns whether a state was entered. */


s32 Player_TryEnterHitReactionState(void *player, void *bodyActor) {
    s16 state;
    s32 hit;

    if (((PlayerBodyMotionView *)(bodyActor))->inputFlags & 0x1000) {
        state = ((Shared_ActorView *)(player))->action;
        if (state != 11) {
            if (state != 12) {
                if (state != 9) {
                    if (state != 10) {
                        if (state != 38) {
                            if (state == 21 || state == 19 || state == 20) {
                                hit = 1;
                            } else {
                                hit = 0;
                            }
                            if (hit) {
                                ((Shared_ActorView *)(player))->unk_0x0038 |= 0x1000;
                                return 0;
                            }
                            Player_SetPlayerState(player, bodyActor, 12);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    state = ((Shared_ActorView *)(player))->action;
    if (state == 21 || state == 19 || state == 20) {
        hit = 1;
    } else {
        hit = 0;
    }
    if (hit) {
        return 0;
    }
    if ((((PlayerBodyMotionView *)(bodyActor))->inputFlags & 0x2003) != 0x2000) {
        return 0;
    }
    if (!(((PlayerBodyMotionView *)(bodyActor))->verticalSpeed <= 0.0f)) {
        return 0;
    }
    if (!(g_playerGroundMovementSpeedLimits[1] < ((PlayerBodyMotionView *)(bodyActor))->verticalSpeed)) {
        return 0;
    }
    state = ((Shared_ActorView *)(player))->action;
    if (state == 11) {
        return 0;
    }
    if (state == 12) {
        return 0;
    }
    if (state == 9) {
        return 0;
    }
    if (state == 10) {
        return 0;
    }
    if (state == 38) {
        return 0;
    }
    Player_SetPlayerState(player, bodyActor, 10);
    return 1;
}

s32 Player_TryThrowSelectedActor(void *playerObject, void *positionObject, s32 *unused) {
    ThrowPlayer *player = playerObject;
    ThrowPosition *position = positionObject;
    ThrowActor *actor, *selected;
    s32 kind;
    f32 offset, scale, xSpeed, angle;
    { void *object = g_currentActorInstance; actor = object; }
    if (!(player->flags & 0x8000)) goto invalid;
    if (!actor) return 0;
    selected = player->selected;
    if (actor == selected) goto invalid;
    if (actor->category != 1) return 0;
    kind = actor->definition->kind;
    if (kind != 1 || !selected) return 0;
    if (actor->state.active) {
        angle = position->angle;
        offset = g_playerThrowHeightOffset;
        xSpeed = player->speed * Gu_Sinf(angle + offset);
        scale = g_playerThrowForwardScale;
        actor->vx = xSpeed * scale;
        actor->vy = player->speed * g_playerThrowVerticalSpeedScale;
        actor->vz = player->speed * Math_Cosf(position->angle + offset) * scale;
        if (player->effect)
            Gsky_StartScaledShake(player->effect, g_playerHeavyThrowShakeStrength, 100.0f, g_playerHeavyThrowShakeStrength, g_playerHeavyThrowShakeDuration, kind, position->pos);
        if (selected->state.kind == 46) actor->state.flags |= 0x200;
        actor->state.timer = -1;
        Actor_RequestActorState(actor, &actor->state, 52);
    } else if (player->effect)
        Gsky_StartScaledShake(player->effect, g_playerLightThrowShakeStrength, 60.0f, g_playerLightThrowShakeStrength, g_playerLightThrowShakeDuration, kind, position->pos);
    return 1;
invalid:
    return 0;
}

/* A turn-rate table (g_playerAirViewAngleParameters and its siblings): yawScale gates and scales stick yaw, yawRate and
   pitchRate are the base smoothing rates, pitchScale scales pitchRate, downScale/upScale scale the
   look-down and look-up stick. */
typedef struct ViewTuning {
    f32 yawScale;
    f32 yawRate;
    f32 pitchRate;
    f32 pitchScale;
    f32 downScale;
    f32 upScale;
} ViewTuning;
/* The ground model's surface word: bits 0x6000 == 0x2000 mark ground that stops the view turning. */
typedef struct SurfaceView {
    u8 pad0[0x50];
    u32 flags; /* 0x50 */
} SurfaceView;
/* Smooths a player's view: the turn and look rates are the tuning table's rates damped by the state
   at 0x7EC and scaled by the profile's yaw and pitch sensitivities (128 = centre); control mode 1
   locks the look rate at 0.5 and mode 0 without the pitch option at 0.8. Unless the body stands on
   a surface that stops turning, the heading eases toward the stick yaw, then the pitch offset eases
   toward the stick pitch (degrees to radians). */
#if !(defined(VERSION_US_REV1))
const float g_playerMovementSpeedConstants[5] = {
    1.0f, 0.833f, 0.917f, 0.833f,
    0.917f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_playerHitReactionConstants[1] = {
    -20.48f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_playerThrowConstants[7] = {
    3.1415927f, 2e+01f, 3e+01f, 1.0f,
    5e+01f, 1.0f, 3e+01f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_playerMovementSpeedConstantsUsRev1[5] = {
    1.0f, 0.833f, 0.917f, 0.833f,
    0.917f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_playerHitReactionConstantsUsRev1[1] = {
    -20.48f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_playerThrowConstantsUsRev1[7] = {
    3.1415927f, 2e+01f, 3e+01f, 1.0f,
    5e+01f, 1.0f, 3e+01f,
};
#endif
void Player_UpdateViewAngles(Player *player, Player *body, ViewTuning *tuning) {
    f32 sens, decay, damp, yawSens, yawValue, yawRate, pitchSens, pitchValue, pitchRate, input, value, yawDelta;
    AiProfile *profile;
    SurfaceView *surface;
    if (player->locked != 0 || 0.0f < player->cooldown) return;
    decay = player->state7EC * 0.99f;
    profile = player->profile;
    sens = (f32)profile->yawSensitivity * 0.0078125f - 1.0f;
    yawSens = sens * 0.5f;
    damp = 1.0f - decay;
    yawValue = damp * tuning->yawRate;
    yawRate = yawSens + 0.875f;
    yawRate *= yawValue;
    sens = (f32)profile->sensitivity * 0.0078125f - 1.0f;
    pitchSens = sens * 0.4f;
    pitchValue = damp * tuning->pitchRate * tuning->pitchScale;
    pitchRate = pitchSens + 0.6f;
    pitchRate *= pitchValue;
    if (profile->controlMode != 0) {
        if (profile->controlMode == 1) pitchRate = 0.5f;
    } else if (profile->pitchMode == 0) pitchRate = 0.8f;
    surface = InstHdr_FindActorModelEntry(body);
    if (surface == 0 || (surface->flags & 0x6000) != 0x2000) {
        if (tuning->yawScale != 0.0f) {
            yawDelta = player->steer;
            yawDelta *= 80.0f;
            yawDelta = yawDelta * tuning->yawScale;
            yawDelta = yawDelta * 0.017453294f;
            Graphu64_EaseValueToward(&body->heading, body->heading + yawDelta, yawRate);
        }
    }
    input = -player->pitch * 80.0f;
    if (input < 0.0f) value = input * -0.71619713f * tuning->downScale;
    else value = input * 0.71619713f * tuning->upScale;
    value = value * 0.017453294f;
    Graphu64_EaseValueToward(&player->pitchOffset, value, pitchRate);
}

/* 8021CD70_11.CPP */
/* Updates player forward, strafe and impulse velocities, accumulates movement and plays the impulse sound. */


extern void Graphu64_AddVec3(CVector3 *,CVector3 *,CVector3 *),Graphu64_ScaleVector(CVector3 *,CVector3 *,f32);

void Player_UpdateGroundThrustAndBoost(SharedPlayer *player, PlayerBodyPositionYawView *body, SharedMovement *movementProfile) {
    CVector3 motion;
    f32 forwardSpeed;
    f32 updatedForwardSpeed;
    f32 boostCooldown;
    f32 forwardSpeedLimit;
    f32 unusedBoostFloat1;
    f32 forwardMotionX;
    f32 strafeSpeed;
    f32 unusedFloat;
    f32 unusedBoostFloat2;
    f32 strafeSpeedLimit;
    f32 unusedBoostFloat3;
    f32 unusedFloat1;
    f32 unusedBoostFloat4;
    f32 unusedBoostFloat5;
    f32 forwardBoostSpeed;
    f32 unusedBoostFloat6;
    f32 unusedBoostFloat7;
    f32 unusedBoostFloat8;
    f32 strafeSpeedMagnitude;
    s32 boostButtons;
    s32 unusedBoostStatus;
    s32 boostApplied;
    s32 boostReady;
    CVector3 *movementOutput;

    if (Cinema_IsSequenceActive() == 0) {
        boostApplied = 0;
        if (player->views5E8.view11B8_137.frozen == 0) {
            boostCooldown = player->views5E8.view6DC_60.boostCooldown;
            boostReady = 1;
            if (!(boostCooldown <= 0.0f)) {
                boostReady = 0;
                player->views5E8.view6DC_60.boostCooldown = (f32) (boostCooldown - (&g_frameElapsedTime)[0]);
            }
            forwardSpeed=player->views5E8.view6C0_51.movementSpeed; forwardSpeedLimit=movementProfile->speedLimit;
            if (forwardSpeed < 0.0f ? forwardSpeedLimit < -forwardSpeed : forwardSpeedLimit < forwardSpeed) {
                player->views5E8.view6C0_51.movementSpeed=Graphu64_DecayToZero(player->views5E8.view6C0_51.movementSpeed,movementProfile->speedDecay*0.5f);
            } else if(player->views5E8.view6A8_43.lift != 0.0f && player->views5E8.view7E8_105.zoomed != 2) {
                player->views5E8.view6C0_51.movementSpeed=Graphu64_IntegrateBoundedValue(player->views5E8.view6C0_51.movementSpeed,player->views5E8.view6A8_43.lift*movementProfile->acceleration,(player->views5E8.view6A8_43.lift<0.0f?-player->views5E8.view6A8_43.lift:player->views5E8.view6A8_43.lift)*movementProfile->speedLimit);
            } else {
                player->views5E8.view6C0_51.movementSpeed=Graphu64_DecayToZero(player->views5E8.view6C0_51.movementSpeed,movementProfile->speedDecay);
            }
            forwardMotionX = player->views5E8.view6C0_51.movementSpeed * Gu_Sinf(body->yaw + 3.1415927f);
            motion.y = 0;
            motion.x = forwardMotionX;
            motion.z = player->views5E8.view6C0_51.movementSpeed * Math_Cosf(body->yaw + 3.1415927f);
            strafeSpeed=player->views5E8.view6C4_54.sideSpeed; strafeSpeedLimit=movementProfile->strafeLimitOrBoostDecay;
            if (strafeSpeed < 0.0f ? strafeSpeedLimit < -strafeSpeed : strafeSpeedLimit < strafeSpeed) {
                player->views5E8.view6C4_54.sideSpeed=Graphu64_DecayToZero(player->views5E8.view6C4_54.sideSpeed,movementProfile->strafeDecayOrLiftAcceleration*0.5f);
            } else if(player->views5E8.view6A4_41.strafe != 0.0f) {
                player->views5E8.view6C4_54.sideSpeed=Graphu64_IntegrateBoundedValue(player->views5E8.view6C4_54.sideSpeed,player->views5E8.view6A4_41.strafe*movementProfile->strafeAccelerationOrBoostSpeed,(player->views5E8.view6A4_41.strafe<0.0f?-player->views5E8.view6A4_41.strafe:player->views5E8.view6A4_41.strafe)*movementProfile->strafeLimitOrBoostDecay);
            } else {
                player->views5E8.view6C4_54.sideSpeed=Graphu64_DecayToZero(player->views5E8.view6C4_54.sideSpeed,movementProfile->strafeDecayOrLiftAcceleration);
            }
            motion.x += player->views5E8.view6C4_54.sideSpeed * Gu_Sinf(body->yaw - 1.5707964f);
            motion.z += player->views5E8.view6C4_54.sideSpeed * Math_Cosf(body->yaw - 1.5707964f);
            strafeSpeedMagnitude = player->views5E8.view6C4_54.sideSpeed;
            if (strafeSpeedMagnitude < 0.0f) {
                strafeSpeedMagnitude = -strafeSpeedMagnitude;
            }
            updatedForwardSpeed = player->views5E8.view6C0_51.movementSpeed;
            if (updatedForwardSpeed < 0.0f) {
                if (-updatedForwardSpeed < strafeSpeedMagnitude) {
                    goto block_35;
                }
                goto block_36;
            }
            if (updatedForwardSpeed < strafeSpeedMagnitude) {
block_35:
                Graphu64_ClampMotionLength(&motion,movementProfile->strafeLimitOrBoostDecay);
            } else {
block_36:
                Graphu64_ClampMotionLength(&motion,movementProfile->speedLimit);
            }
            if (boostReady != 0) {
                boostButtons = player->views5E8.view6B0_46.actionFlags;
                if (boostButtons & 8) {
                    forwardBoostSpeed = movementProfile->boostSpeedOrLiftLimit;
                    boostApplied = 1;
                } else if (boostButtons & 4) {
                    forwardBoostSpeed = -movementProfile->boostSpeedOrLiftLimit * 0.5f;
                    boostApplied = 1;
                } else {
                    goto block_42;
                }
            } else {
block_42:
                forwardBoostSpeed = Graphu64_DecayToZero(player->views5E8.view6D4_58.forwardBoostSpeed, movementProfile->boostDecayOrLiftImpulse);
            }
            player->views5E8.view6D4_58.forwardBoostSpeed = forwardBoostSpeed;
            motion.x += player->views5E8.view6D4_58.forwardBoostSpeed * Gu_Sinf(body->yaw + 3.1415927f);
            motion.z += player->views5E8.view6D4_58.forwardBoostSpeed * Math_Cosf(body->yaw + 3.1415927f);
            if (boostReady && (player->views5E8.view6B8_49.input & 1)) {
                player->views5E8.view6D8_59.boostStrength = movementProfile->boostSpeedOrLiftLimit;
                player->views5E8.view6D8_59.boostStrength *= 0.75f;
                boostApplied=1;
            } else if (boostReady && (player->views5E8.view6B8_49.input & 2)) {
                player->views5E8.view6D8_59.boostStrength = -movementProfile->boostSpeedOrLiftLimit*0.75f;
                boostApplied=1;
            } else {
                player->views5E8.view6D8_59.boostStrength=Graphu64_DecayToZero(player->views5E8.view6D8_59.boostStrength,movementProfile->boostDecayOrLiftImpulse*0.75f);
            }
            motion.x += player->views5E8.view6D8_59.boostStrength * Gu_Sinf(body->yaw - 1.5707964f);
            motion.z += player->views5E8.view6D8_59.boostStrength * Math_Cosf(body->yaw - 1.5707964f);
            Graphu64_ScaleVector(&motion, &motion, player->views5E8.view66C_29.movementTimeScale);
            movementOutput = &player->views5E8.view6E8_63.movementX;
            Graphu64_AddVec3(movementOutput, movementOutput, &motion);
            if (boostApplied != 0) {
                player->views5E8.view6DC_60.boostCooldown = (f32) (player->views5E8.view6DC_60.boostCooldown + 7.5f);
                SoundElement_PlaySoundAtPosition(movementProfile->boostSoundId, body->position, 0, -1);
            }
        }
    }
}

/* 8021CD70_12.CPP */
/* Updates flying-player thrust and impulses, transforms movement into world space and applies descent and roll. */


extern CQuatern Gobjinst_BuildActorAimQuaternion(PlayerBodyMotionView *);
extern void Graphu64_AddVec3(CVector3 *,CVector3 *,CVector3 *),Graphu64_EaseValueToward(f32 *,f32,f32);
void Player_UpdateFlyingThrustAndBoost(SharedPlayer *player, PlayerBodyMotionView *body, SharedMovement *movementProfile) {
    CVector3 v18,v28,v38,v48,v58;
    MatrixF rotationMatrix;
    CQuatern bodyRotation;
    f32 forwardSpeed;
    f32 upwardSpeedLimit;
    f32 verticalSpeed;
    f32 boostCooldown;
    f32 forwardSpeedLimit;
    f32 unusedBoostFloat1;
    f32 strafeSpeed;
    f32 unusedFloat2;
    f32 unusedBoostFloat2;
    f32 strafeSpeedLimit;
    f32 unusedBoostFloat3;
    f32 unusedBoostFloat4;
    f32 unusedBoostFloat5;
    f32 forwardBoostSpeed;
    f32 unusedBoostFloat6;
    f32 unusedBoostFloat7;
    f32 unusedBoostFloat8;
    f32 unusedFloat3;
    s32 boostButtons;
    s32 unusedBoostStatus;
    s32 boostReady;
    s32 boostApplied;

    boostApplied = 0;
    boostCooldown = player->views5E8.view6DC_60.boostCooldown;
    boostReady = 1;
    if (!(boostCooldown <= 0.0f)) {
        boostReady = 0;
        player->views5E8.view6DC_60.boostCooldown = (f32) (boostCooldown - (&g_frameElapsedTime)[0]);
    }
    forwardSpeed=player->views5E8.view6C0_51.movementSpeed; forwardSpeedLimit=movementProfile->speedLimit;
    if (forwardSpeed<0.0f ? forwardSpeedLimit < -forwardSpeed : forwardSpeedLimit < forwardSpeed) {
        player->views5E8.view6C0_51.movementSpeed=Graphu64_DecayToZero(player->views5E8.view6C0_51.movementSpeed,movementProfile->speedDecay*0.5f);
    } else if(player->views5E8.view6A8_43.lift != 0.0f) {
        player->views5E8.view6C0_51.movementSpeed=Graphu64_IntegrateBoundedValue(player->views5E8.view6C0_51.movementSpeed,player->views5E8.view6A8_43.lift*movementProfile->acceleration,(player->views5E8.view6A8_43.lift<0.0f?-player->views5E8.view6A8_43.lift:player->views5E8.view6A8_43.lift)*movementProfile->speedLimit);
    } else {
        player->views5E8.view6C0_51.movementSpeed=Graphu64_DecayToZero(player->views5E8.view6C0_51.movementSpeed,movementProfile->speedDecay);
    }
    strafeSpeed=player->views5E8.view6C4_54.sideSpeed; strafeSpeedLimit=movementProfile->speedLimit;
    if (strafeSpeed<0.0f ? strafeSpeedLimit < -strafeSpeed : strafeSpeedLimit < strafeSpeed) {
        player->views5E8.view6C4_54.sideSpeed=Graphu64_DecayToZero(player->views5E8.view6C4_54.sideSpeed,movementProfile->speedDecay*0.5f);
    } else if(player->views5E8.view6A4_41.strafe != 0.0f) {
        player->views5E8.view6C4_54.sideSpeed=Graphu64_IntegrateBoundedValue(player->views5E8.view6C4_54.sideSpeed,player->views5E8.view6A4_41.strafe*movementProfile->acceleration,(player->views5E8.view6A4_41.strafe<0.0f?-player->views5E8.view6A4_41.strafe:player->views5E8.view6A4_41.strafe)*movementProfile->speedLimit*0.75f);
    } else {
        player->views5E8.view6C4_54.sideSpeed=Graphu64_DecayToZero(player->views5E8.view6C4_54.sideSpeed,movementProfile->speedDecay);
    }
    if (boostReady != 0) {
        boostButtons = player->views5E8.view6B0_46.actionFlags;
        if (boostButtons & 8) {
            forwardBoostSpeed = movementProfile->strafeAccelerationOrBoostSpeed;
            boostApplied = 1;
        } else if (boostButtons & 4) {
            forwardBoostSpeed = -movementProfile->strafeAccelerationOrBoostSpeed * 0.5f;
            boostApplied = 1;
        } else {
            goto block_31;
        }
    } else {
block_31:
        forwardBoostSpeed = Graphu64_DecayToZero(player->views5E8.view6D4_58.forwardBoostSpeed, movementProfile->strafeLimitOrBoostDecay);
    }
    player->views5E8.view6D4_58.forwardBoostSpeed = forwardBoostSpeed;
    if (boostReady && (player->views5E8.view6B8_49.input & 1)) {
        player->views5E8.view6D8_59.boostStrength=movementProfile->strafeAccelerationOrBoostSpeed;
        player->views5E8.view6D8_59.boostStrength*=0.75f;
        boostApplied=1;
    } else if (boostReady && (player->views5E8.view6B8_49.input & 2)) {
        player->views5E8.view6D8_59.boostStrength=-movementProfile->strafeAccelerationOrBoostSpeed*0.75f;
        boostApplied=1;
    } else {
        player->views5E8.view6D8_59.boostStrength=Graphu64_DecayToZero(player->views5E8.view6D8_59.boostStrength,movementProfile->strafeLimitOrBoostDecay*0.75f);
    }
    if ((boostReady != 0) && (player->views5E8.view6B0_46.actionFlags & 0x10)) {
        boostApplied = 1;
        body->verticalSpeed = (f32) (body->verticalSpeed + movementProfile->boostDecayOrLiftImpulse);
    }
    if (player->views5E8.view6AC_45.inputFlags & 0x10) {
        verticalSpeed = body->verticalSpeed;
        upwardSpeedLimit = movementProfile->boostSpeedOrLiftLimit;
        if (verticalSpeed < upwardSpeedLimit) {
            body->verticalSpeed = Graphu64_IntegrateBoundedValue(verticalSpeed, movementProfile->strafeDecayOrLiftAcceleration, upwardSpeedLimit);
        }
    }
    v18.x = 0.0f;
    v18.y = 0;
    v18.z = player->views5E8.view6C0_51.movementSpeed + player->views5E8.view6D4_58.forwardBoostSpeed;
    v28.x = player->views5E8.view6C4_54.sideSpeed + player->views5E8.view6D8_59.boostStrength;
    v28.y = 0;
    v28.z = 0;
    bodyRotation = Gobjinst_BuildActorAimQuaternion(body);
    MatrixFromQuaternion(&bodyRotation, &rotationMatrix);
    Graphu64_TransformPoint(&rotationMatrix, &v18, &v38);
    Graphu64_TransformPoint(&rotationMatrix, &v28, &v48);
    player->views5E8.view6E8_63.movementX = (f32) (player->views5E8.view6E8_63.movementX + ((v38.x + v48.x) * player->views5E8.view66C_29.movementTimeScale));
    player->views5E8.view6EC_64.height = (f32) (player->views5E8.view6EC_64.height + ((v38.y + v48.y) * player->views5E8.view66C_29.movementTimeScale));
    player->views5E8.view6F0_66.movementZ = (f32) (player->views5E8.view6F0_66.movementZ + ((v38.z + v48.z) * player->views5E8.view66C_29.movementTimeScale));
    if (body->verticalSpeed < 0.0f) {
        Graphu64_AddVec3(&v58, &v38, &v48);
        body->verticalSpeed = (f32) (body->verticalSpeed - (player->views13B4.view13B4_2.actionDefinitions[player->views5E8.view650_15.actionState].physics->time * (Gu_Sqrtf((v58.x * v58.x) + (v58.y * v58.y) + (v58.z * v58.z)) / (movementProfile->speedLimit * 4.0f)) * player->views5E8.view66C_29.movementTimeScale));
    }
    Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, ((player->views5E8.view6C4_54.sideSpeed * 1.8f) + (player->views5E8.view69C_39.stick * 16.0f)) * 0.01745329424738884f, 0.04f);
    if (boostApplied != 0) {
        player->views5E8.view6DC_60.boostCooldown = (f32) (player->views5E8.view6DC_60.boostCooldown + 7.5f);
        SoundElement_PlaySoundAtPosition(movementProfile->boostSoundId, body->position, 0, -1);
    }
}

/* 8021CD70_13.CPP */
/* Settles a player's weapon sway and applies its walking bob unless the player is recoiling at 0x11D8:
   eases the kick angles at 0x72C and 0x728 and the three sway angles at 0x730 to 0x738 back to rest,
   caps the bob speed at 0x75C and bob strength at 0x758 and decays both, clearing them once the
   strength falls below 0.06, then advances the bob phase from the stride at 0x658 and eases the
   weapon height at 0x740 (from the model's height at 0xF4 or a default) and its side and forward
   offsets at 0x73C and 0x744 along the camera's heading. */

void Player_UpdateWeaponSwayAndBob(SharedPlayer *player, ActorYawView *camera) {
    f32 step;
    f32 phase;
    f32 height;
    f32 rate;
    f32 amount;

    if (!(player->views5E8.view11D8_148.recoil > 0.0f)) {
        Graphu64_EaseValueToward(&player->views5E8.view72C_76.kickRoll, 0.0f, 0.25f);
        Graphu64_EaseValueToward(&player->views5E8.view728_74.kickPitch, 0.0f, 0.5f);
        step = 0.08726647496f;
        player->views5E8.view730_79.sway[0] = Graphu64_DecayToZero(player->views5E8.view730_79.sway[0], step);
        player->views5E8.view730_79.sway[1] = Graphu64_DecayToZero(player->views5E8.view730_79.sway[1], step);
        player->views5E8.view730_79.sway[2] = Graphu64_DecayToZero(player->views5E8.view730_79.sway[2], step);
        if (21.0f < player->views5E8.view75C_90.bobSpeed) {
            player->views5E8.view75C_90.bobSpeed = 21.0f;
        }
        if (0.1f < player->views5E8.view758_88.bobStrength) {
            player->views5E8.view758_88.bobStrength = 0.1f;
        }
        player->views5E8.view75C_90.bobSpeed = Graphu64_DecayToZero(player->views5E8.view75C_90.bobSpeed, 0.11666667f);
        player->views5E8.view758_88.bobStrength = Graphu64_DecayToZero(player->views5E8.view758_88.bobStrength, 0.00055555557f);
        if (player->views5E8.view758_88.bobStrength < 0.06f) {
            player->views5E8.view75C_90.bobSpeed = player->views5E8.view758_88.bobStrength = 0.0f;
        }
        phase = player->views5E8.view658_23.stride * player->views5E8.view75C_90.bobSpeed * 0.017453294f;
        if (player->views18.view18_2.model != 0) {
            height = player->views18.view18_2.model->height * 0.9f;
        } else {
            height = 82.94399261f;
        }
        rate = 0.5f;
        Graphu64_EaseValueToward(&player->views5E8.view740_84.height, height + player->views5E8.view758_88.bobStrength * (Gu_Sinf(phase) * 10.24f), rate);
        amount = player->views5E8.view758_88.bobStrength * (Math_Cosf(phase) * 8.192f);
        Graphu64_EaseValueToward(&player->views5E8.view73C_81.side, -Gu_Sinf(camera->yaw + 3.1415927f) * amount, rate);
        Graphu64_EaseValueToward(&player->views5E8.view744_86.forward, -Math_Cosf(camera->yaw + 3.1415927f) * amount, rate);
    }
}

/* 8021CD70_14.CPP */
/* Starts the effect at offset 0x740 of an object through Graphu64_EaseValueToward at half intensity, with a
   level taken from the owner at offset 0x18 scaled by g_playerOwnerHeightEffectTuning[0], or g_playerOwnerHeightEffectTuning[1] without an
   owner. */

void Player_EaseOwnerHeightEffect(struct EffectOwnerObject *object) {
    f32 level;

    if (object->owner != 0) {
        level = object->owner->height * g_playerOwnerHeightEffectTuning[0];
    } else {
        level = g_playerOwnerHeightEffectTuning[1];
    }
    Graphu64_EaseValueToward(&object->effect740, level, 0.5f);
}

/* 800C78B4.CPP */


/* 800C78C4.CPP */

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/playerBodyMovementPoolUsRev1.c */
#endif

/* 800C7938.CPP */


/* 800C794C.CPP */

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/playerHitReactionPoolUsRev1.c */
#endif

/* 800C7950.CPP */


/* 800C7A38.CPP */
#if !(defined(VERSION_US_REV1))
const float g_playerOwnerHeightEffectConstants[2] = {
    0.9f, 82.94399f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/playerOwnerHeightEffectPoolUsRev1.c */
const float g_playerOwnerHeightEffectConstantsUsRev1[2] = {
    0.9f, 82.94399f,
};
#endif
