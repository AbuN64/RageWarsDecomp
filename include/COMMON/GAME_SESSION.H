#ifndef COMMON_GAME_SESSION_H
#define COMMON_GAME_SESSION_H
#include "TYPES.H"
#include "COMMON/DISPLAY.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "COMMON/RENDERSETTINGS.H"
#include "COMMON/SESSION_STATE.H"
typedef struct GameSession GameSession;
struct GameSession {
    Display ring;
    s32 resource; /* +0x3C4 */
    Shared_World world; /* +0x3C8; probe 20261019T014445806769Z call boundary */
    u8 reservedWorld[0x1BCF8 - 0x3C8 - sizeof(Shared_World)];
    Hud hud; /* +0x1BCF8; probe 20261019T014445806769Z call boundary */
    u8 reservedHud[0x25580 - 0x1BCF8 - sizeof(Hud)];
    CPlayerPool menu[1]; /* +0x25580, Player_ResetMenuPool_GameSession */
    u8 reserved255C4[4];
    /* g_matchEndingTeamWheelClose is this session's match state at +0x25B5C. Its
     * messages overlap the screen-message owner, and its settings overlap
     * local/arena. The pause word belongs to clockPaused only. */
    union {
        struct {
            struct ScreenMessageOwner players[1]; /* +0x255C8, Pools_ResetPlayers_Channel */
            u8 reservedPlayers[0x26825 - 0x255C8 - sizeof(struct ScreenMessageOwner)];
            u8 local; /* +0x26825: g_gameSettings.local, the local-player input flag (Match_StartMatchTransition_Initial) */
            u8 arena; /* +0x26826: SetN64_StartRound */
            u8 reserved26827[0x26D8C - 0x26827];
            RenderSettings settings; /* +0x26D8C */
            f32 transitionTime; /* +0x26DB0 */
            s32 previousMode;
            s32 mode;
            s32 target;
            u8 fastFade; /* +0x26DC0: SetN64_UpdateFadeTransition steps the fade by 0.5 instead of 0.1 */
            u8 phase; /* +0x26DC1: fade phase: 0 idle, 1 fading in, 2 fading out */
            u8 reserved26DC2[2];
            f32 timer;
            s32 enabled;
            s32 reservedTransitionState;
            s32 transitionBlocked;
            s32 clockPaused;
            s32 selector;
            s32 selectionActive;
        };
        struct {
            u8 reserved255C8[0x25B5C - 0x255C8];
            GameSessionState match; /* +0x25B5C; rules at +0x26DE0 */
        };
    };
};
/* The game session; its ring.current is g_currentRenderFrame (+0x3C0). */
extern GameSession g_gameSession;
#endif
