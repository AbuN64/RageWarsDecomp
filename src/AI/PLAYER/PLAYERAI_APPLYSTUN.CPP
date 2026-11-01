#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/OBJRECV5.H"
#include "WEAPONS/PLAYERAI_APPLYSTUN.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"



/* Fuzzy draft: the other versions' body, not diffed against this version's asm. */
typedef struct {
    char pad0[0x98];
    s32 rule;
    char pad9C[0xA0 - 0x9C];
    s32 protect;
} StunProtectionRules;

extern StunProtectionRules g_matchRoundCounters[];

extern void Gsky_StartFade(void *camera, s32 requestedFadeMode, s32 startValue, s32 endValue, s32 stepAmount, s32 redChannel, s32 greenChannel, s32 blueChannel);

void Playerai_ApplyStun(SharedPlayer *player, f32 amount) {
    f32 stun;

    if (amount != 0.0f && !(75.0f <= player->views5E8.view11D8_149.stun) && !(player->views5E8.view670_31.shield > 0.0f)
        && !(g_matchRoundCounters->rule != 0
#if defined(VERSION_DE) || defined(VERSION_EU_X)
            && player->views5D8.view5D8_2.controls->team != 0
#endif
            && player->views5D8.view5D8_2.controls->mode == 11 && g_matchRoundCounters->protect > 0)
        && !(player->views122C.view122C_2.options & 0x8000)) {
        stun = player->views5E8.view11D8_149.stun + amount * 15.0f;
        if (75.0f < stun) {
            stun = 75.0f;
        }
        player->views5E8.view11D8_149.stun = stun;
        Actor_RequestActorState(player->views1C.view2E8_28.weapon, player->views1C.view458_30.ammo, 2);
        if (player->views5E8.view1210_153.marker != 0) {
            if (player->views5E4.view5E4_4.holding != 0) {
                Player_SetPlayerState(player, player, 2);
            }
            player->views5E8.view1210_153.marker = 0;
            player->views5E8.view1214_156.markerShown = 0;
        }
        player->views1C.view100_9.flags &= ~0x01000000;
        if (player->views5DC.view5DC_2.view != 0) {
            if (((PlayerFlashView *)player->views5DC.view5DC_2.view)->flash == 0) {
                Gsky_StartFade((PlayerFlashView *)player->views5DC.view5DC_2.view, 128, 0, 0, 250, (u8) (u32) Graphu64_RandomFloat(7.5f), 0,
                              (u8) (u32) ((player->views5E8.view11D8_149.stun * 0.06666667f - 1.5f) * 15.0f));
            } else {
                ((PlayerFlashView *)player->views5DC.view5DC_2.view)->flash = 3;
                ((PlayerFlashView *)player->views5DC.view5DC_2.view)->level = (u32) player->views5E8.view11D8_149.stun;
            }
        }
    }
}
