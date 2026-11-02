#include "COMMON/ITEMRECAT20V1.H"
#include "RENDER/PLAYER_CONTROLLER_RESET_VIEWS.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"

/* Draws a player's marker when it is enabled at 0x1214: loads the player's matrix for the current view
   g_lightingBufferIndex from its table at 0x1500, sets the render and geometry modes, fills the eight vertices of
   a red prism in g_playerDeathEffectVertices (alpha 150 on the upper and 100 on the lower corners), emits them with the
   eight triangles joining them, and passes the same colour and alphas to Fx_DrawRedParticleQuad with the
   matrix from the table at 0x1580 when 0x147C is set. */








extern s32 g_lightingBufferIndex;

extern s32 Geometry_SetModePreset(s32);
extern void Geometry_SetCombineMode(u32);
extern void Fx_DrawRedParticleQuad(UnitMtx *, s32, s32, s32);

void Player_DrawRedMarkerPrism(PlayerMarkerPrismView *player) {
    s32 red;
    s32 low;
    s32 high;

    if (player->marker != 0) {
        gSPMatrix(g_displayListCursor++, &player->views[g_lightingBufferIndex], G_MTX_LOAD);
        gDPPipeSync(g_displayListCursor++);
        Geometry_InvalidateMaterialKeys();
        Geometry_SetModePreset(14);
        Geometry_SetCombineMode(28);
        red = 200;
        low = 100;
        high = 150;
        gSPGeometryMode(g_displayListCursor++, G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | 0x80, 0);
        gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_SHADING_SMOOTH);
        g_playerDeathEffectVertices[0].x = 0;
        g_playerDeathEffectVertices[0].y = 1;
        g_playerDeathEffectVertices[0].z = 0;
        g_playerDeathEffectVertices[0].flag = 0;
        g_playerDeathEffectVertices[0].s = 0;
        g_playerDeathEffectVertices[0].t = 0;
        g_playerDeathEffectVertices[0].r = red;
        g_playerDeathEffectVertices[0].g = 0;
        g_playerDeathEffectVertices[0].b = 0;
        g_playerDeathEffectVertices[0].a = high;
        g_playerDeathEffectVertices[1].x = 1;
        g_playerDeathEffectVertices[1].y = 0;
        g_playerDeathEffectVertices[1].z = 0;
        g_playerDeathEffectVertices[1].flag = 0;
        g_playerDeathEffectVertices[1].s = 0;
        g_playerDeathEffectVertices[1].t = 0;
        g_playerDeathEffectVertices[1].r = red;
        g_playerDeathEffectVertices[1].g = 0;
        g_playerDeathEffectVertices[1].b = 0;
        g_playerDeathEffectVertices[1].a = high;
        g_playerDeathEffectVertices[2].x = 0;
        g_playerDeathEffectVertices[2].y = -1;
        g_playerDeathEffectVertices[2].z = 0;
        g_playerDeathEffectVertices[2].flag = 0;
        g_playerDeathEffectVertices[2].s = 0;
        g_playerDeathEffectVertices[2].t = 0;
        g_playerDeathEffectVertices[2].r = red;
        g_playerDeathEffectVertices[2].g = 0;
        g_playerDeathEffectVertices[2].b = 0;
        g_playerDeathEffectVertices[2].a = low;
        g_playerDeathEffectVertices[3].x = -1;
        g_playerDeathEffectVertices[3].y = -1;
        g_playerDeathEffectVertices[3].z = 0;
        g_playerDeathEffectVertices[3].flag = 0;
        g_playerDeathEffectVertices[3].s = 0;
        g_playerDeathEffectVertices[3].t = 0;
        g_playerDeathEffectVertices[3].r = red;
        g_playerDeathEffectVertices[3].g = 0;
        g_playerDeathEffectVertices[3].b = 0;
        g_playerDeathEffectVertices[3].a = low;
        g_playerDeathEffectVertices[4].x = 0;
        g_playerDeathEffectVertices[4].y = 1;
        g_playerDeathEffectVertices[4].z = -1;
        g_playerDeathEffectVertices[4].flag = 0;
        g_playerDeathEffectVertices[4].s = 0;
        g_playerDeathEffectVertices[4].t = 0;
        g_playerDeathEffectVertices[4].r = red;
        g_playerDeathEffectVertices[4].g = 0;
        g_playerDeathEffectVertices[4].b = 0;
        g_playerDeathEffectVertices[4].a = high;
        g_playerDeathEffectVertices[5].x = 1;
        g_playerDeathEffectVertices[5].y = 0;
        g_playerDeathEffectVertices[5].z = -1;
        g_playerDeathEffectVertices[5].flag = 0;
        g_playerDeathEffectVertices[5].s = 0;
        g_playerDeathEffectVertices[5].t = 0;
        g_playerDeathEffectVertices[5].r = red;
        g_playerDeathEffectVertices[5].g = 0;
        g_playerDeathEffectVertices[5].b = 0;
        g_playerDeathEffectVertices[5].a = high;
        g_playerDeathEffectVertices[6].x = 0;
        g_playerDeathEffectVertices[6].y = -1;
        g_playerDeathEffectVertices[6].z = -1;
        g_playerDeathEffectVertices[6].flag = 0;
        g_playerDeathEffectVertices[6].s = 0;
        g_playerDeathEffectVertices[6].t = 0;
        g_playerDeathEffectVertices[6].r = red;
        g_playerDeathEffectVertices[6].g = 0;
        g_playerDeathEffectVertices[6].b = 0;
        g_playerDeathEffectVertices[6].a = low;
        g_playerDeathEffectVertices[7].x = -1;
        g_playerDeathEffectVertices[7].y = -1;
        g_playerDeathEffectVertices[7].z = -1;
        g_playerDeathEffectVertices[7].flag = 0;
        g_playerDeathEffectVertices[7].s = 0;
        g_playerDeathEffectVertices[7].t = 0;
        g_playerDeathEffectVertices[7].r = red;
        g_playerDeathEffectVertices[7].g = 0;
        g_playerDeathEffectVertices[7].b = 0;
        g_playerDeathEffectVertices[7].a = low;
        gSPVertex(g_displayListCursor++, (u32) g_playerDeathEffectVertices, 8, 0);
        gSP1Triangle(g_displayListCursor++, 0, 1, 4, 0);
        gSP1Triangle(g_displayListCursor++, 1, 4, 5, 0);
        gSP1Triangle(g_displayListCursor++, 1, 2, 5, 0);
        gSP1Triangle(g_displayListCursor++, 2, 5, 6, 0);
        gSP1Triangle(g_displayListCursor++, 2, 3, 6, 0);
        gSP1Triangle(g_displayListCursor++, 3, 6, 7, 0);
        gSP1Triangle(g_displayListCursor++, 3, 0, 7, 0);
        gSP1Triangle(g_displayListCursor++, 0, 7, 4, 0);
        if (player->second != 0) {
            Fx_DrawRedParticleQuad(&player->markers[g_lightingBufferIndex], red, low, high);
        }
    }
}
