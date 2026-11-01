#include "COMMON/PACKEDMESHMATERIAL.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MODEL_RENDER.H"
#include "include_asm.h"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include <PR/abi.h>
#include <PR/gbi.h>
#include "TYPES.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Draws every part of a model resource with the shared material g_tintedModelSharedMaterial when the frame's command buffer still has 3000 commands free and Geometry_SetupMaterial accepts the material: sets the render mode, selects blend 2 through Geometry_SetCombineMode_GeometryDrawcharactereffectparts, loads the model matrix (or sets it as segment 1), loads an optional two-light block, registers the resource, sets segment 2 to the given texture base or the model's own and emits each part's display list. Adapted from Geometry_DrawWithMaterialOverride with the render mode, blend and light commands added and the per-part lighting call removed. */




extern Gfx *g_displayListCursor;
#include "COMMON/DISPLAY.H"
extern char g_tintedModelSharedMaterial;
extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern s32 Geometry_SetupMaterial(void *material, s32 pass);
extern void Geometry_SetCombineMode(u32 mode);

void Geometry_DrawSharedMaterialModel(void **resource, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    s32 count;
    s32 i;

    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(&g_tintedModelSharedMaterial, pass) == 0) {
        return;
    }
    gDPSetRenderMode(g_displayListCursor++, 0x0C184F50, 0);
    Geometry_SetCombineMode(2);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    if (lights != 0) {
        Gfx *cmd = g_displayListCursor++;
        gMoveWd(cmd, G_MW_NUMLIGHT, 0, 0x18);
        cmd = g_displayListCursor++;
        gDma2p(cmd, G_MOVEMEM, lights + 8, 16, G_MV_LIGHT, 48);
        cmd = g_displayListCursor++;
        gDma2p(cmd, G_MOVEMEM, lights, 16, G_MV_LIGHT, 72);
    }
    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        SetN64_GetPackSection(part, 0);
        {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

/* Draws every part of a model resource with the shared material g_geometryOverrideMaterial when the frame's command buffer still has 3000 commands free and Geometry_SetupMaterial accepts the material: prepares through XPlus_NextRandomInteger, flags the material 0x20 and sets g_menuModelFillEnabled, sets the render mode, loads the model matrix (or sets it as segment 1), loads an optional two-light block, registers the resource, sets segment 2 to the given texture base or the model's own and emits each part's display list, skipping parts whose material blend bits are all set unless the owner's 0x122C flag 0x400 is set. Adapted from Geometry_DrawSharedMaterialModel with the preparation and flag stores added, the blend call removed and the per-part owner test added. */




#include "COMMON/DISPLAY.H"

extern s32 XPlus_NextRandomInteger(void);






void Geometry_DrawOwnerFilteredPass(void **resource, void *owner, void *matrix, s32 segment, Shared_ParticleLighting *lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;
    s32 *shared;
    Gfx **start;
    u32 used;

    XPlus_NextRandomInteger();
    start = &g_gameSession.ring.current->commands;
    shared = &g_geometryOverrideMaterial;
    *shared |= 0x20;
    used = (u32)g_displayListCursor - (u32)*start;
    g_menuModelFillEnabled = 1;
    if (g_displayListCapacityUsRev1 - used / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) == 0) {
        return;
    }
    gDPSetRenderMode(g_displayListCursor++, 0x0C184DD8, 0);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    if (lights != 0) {
        Gfx *cmd = g_displayListCursor++;
        gMoveWd(cmd, G_MW_NUMLIGHT, 0, 0x18);
        cmd = g_displayListCursor++;
        gDma2p(cmd, G_MOVEMEM, lights->diffuse, 16, G_MV_LIGHT, 48);
        cmd = g_displayListCursor++;
        gDma2p(cmd, G_MOVEMEM, lights, 16, G_MV_LIGHT, 72);
    }
    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if ((((Material *)material)->flags & 0x38) != 0x38 || (((PlayerDamageFlagsView *)(owner))->flags & 0x400)) {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

#include "COMMON/AIPROFILE.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "COMMON/PACKEDMESHMATERIAL.H"
extern f32 g_geometryDefaultTintColor, g_geometryDefaultTintAlpha;
extern CGameStatus g_matchRoundCounters;
/* Draws a character model's parts with the shared material g_tintedModelSharedMaterial, choosing each part by the 0x38 bits of
 * its material byte 6: on the special state 0x12 the part must equal the bits for the variant at 0x81, otherwise
 * the 0x38/0x30/0x10 groups are drawn only when the matching flag (fade, bonus, glow) was computed first. */
void Geometry_DrawCharacterEffectParts(void **resource, struct Player *owner, void *matrix, s32 segment, Shared_ParticleLighting *lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    MeshMaterial *material;
    s32 count;
    s32 i;
    s32 hide = 0;
    s32 bonus = 0;
    s32 glow = 0;
    s32 flags;
    MeshMaterial *shared;
    CGameStatus *settings;

    if (matrix == 0) {
        return;
    }
    settings = &g_matchRoundCounters;
    if (settings->enabled != 0) {
        AiProfile *state = owner->profile;
        if (state->character == 11 && state->enabled != 0) {
            hide = 0 < settings->m_nBastilleShield;
        }
    }
    if (owner->reactionFlags & 0x8000) {
        hide = 1;
    }
    if (0.0f < owner->glow) {
        glow = 1;
    }
    if (g_matchRoundCounters.m_bCTFOn != 0 && owner->profile->bonus == 1) {
        bonus = 1;
    }
    shared = (MeshMaterial *)&g_tintedModelSharedMaterial;
    flags = shared->flags;
    shared->flags = flags | 0x400;
    g_menuModelFillColor[0] = g_menuModelFillColor[1] = g_menuModelFillColor[2] = g_geometryDefaultTintColor;
    g_menuModelFillColor[3] = g_geometryDefaultTintAlpha;
    shared->flags = flags | 0x1402;
    g_menuModelFillEnabled = 3;
    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) != 0) {
        gDPSetRenderMode(g_displayListCursor++, 0x0C184DD8, 0);
        Geometry_SetCombineMode(1);
        if (segment != 0) {
            gSPSegment(g_displayListCursor++, 1, matrix);
        } else {
            gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD);
        }
        if (lights != 0) {
            Gfx *cmd = g_displayListCursor++;
            gMoveWd(cmd, G_MW_NUMLIGHT, 0, 0x18);
            cmd = g_displayListCursor++;
            gDma2p(cmd, G_MOVEMEM, lights->diffuse, 16, G_MV_LIGHT, 48);
            cmd = g_displayListCursor++;
            gDma2p(cmd, G_MOVEMEM, lights, 16, G_MV_LIGHT, 72);
        }
        Cache_MarkResourceInUse(0, resource);
        header = *resource;
        base = textures;
        if (base == 0) {
            base = SetN64_GetPackSection(header, 0);
        }
        gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
        parts = SetN64_GetPackSection(header, 2);
        count = *(s32 *)parts;
        for (i = 0; i < count; i++) {
            AiProfile *state;
            u32 bits;
            part = SetN64_GetPackSection(parts, i);
            material = SetN64_GetPackSection(part, 0);
            if (i == 0) {
                Geometry_ApplyMaterialLighting(matrix, lights, material);
            }
            state = owner->profile;
            if (state->character == 18 && (g_matchRoundCounters.m_bFragTagOn == 0 || state->bonus == 0)) {
                switch (state->variant) {
                case 0:
                    if ((material->mode & 0x38) == 0x28) {
                        if (Geometry_SetupMaterial(material, pass) != 0) {
                            void *list = SetN64_GetPackSection(part, 1);
                            Gfx *cmd = g_displayListCursor++;
                            gSPDisplayList(cmd, (unsigned int)list);
                        }
                    }
                    break;
                case 1:
                    if ((material->mode & 0x38) == 0x20) {
                        if (Geometry_SetupMaterial(material, pass) != 0) {
                            void *list = SetN64_GetPackSection(part, 1);
                            Gfx *cmd = g_displayListCursor++;
                            gSPDisplayList(cmd, (unsigned int)list);
                        }
                    }
                    break;
                case 2:
                    if ((material->mode & 0x38) == 0x18) {
                        if (Geometry_SetupMaterial(material, pass) != 0) {
                            void *list = SetN64_GetPackSection(part, 1);
                            Gfx *cmd = g_displayListCursor++;
                            gSPDisplayList(cmd, (unsigned int)list);
                        }
                    }
                    break;
                }
            } else {
                bits = material->mode & 0x38;
                if (bits == 0x38 && hide == 0) continue;
                if (bits == 0x30 && bonus == 0) continue;
                if (bits == 0x10 && glow == 0) continue;
                if (Geometry_SetupMaterial(material, pass) != 0) {
                    void *list = SetN64_GetPackSection(part, 1);
                    Gfx *cmd = g_displayListCursor++;
                    gSPDisplayList(cmd, (unsigned int)list);
                }
            }
        }
    }
    g_menuModelFillEnabled = 0;
}

#include "COMMON/GAME_SESSION.H"
extern const f32 g_geometryOpaqueTintAlpha;
extern void Geometry_ApplyMaterialLighting(void *, void *, void *);
/* Draws every part of a model resource with the shared material g_tintedModelSharedMaterial after setting its fixed colour
 * bytes (0x10..0x17) and flags 0x1402, when the frame's command buffer still has 3000 commands free; the first
 * part's material is registered through Geometry_ApplyMaterialLighting with the caller's two inputs. */
void Geometry_DrawModelWithSharedMaterial(void **resource, void *matrix, s32 segment, void *lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;
    MeshMaterial *shared;
    u32 flags;
    if (matrix == 0) {
        return;
    }
    XPlus_NextRandomInteger();
    shared = (MeshMaterial *)&g_tintedModelSharedMaterial;
    flags = shared->flags;
    shared->secondaryColor[0] = 128;
    shared->secondaryColor[1] = 95;
    shared->secondaryColor[2] = 34;
    shared->secondaryColor[3] = 240;
    shared->primaryColor[0] = 219;
    shared->primaryColor[1] = 184;
    shared->primaryColor[2] = 119;
    shared->primaryColor[3] = 64;
    shared->flags = flags | 0x400;
    g_menuModelFillColor[3] = g_geometryOpaqueTintAlpha;
    shared->flags = flags | 0x1402;
    g_menuModelFillEnabled = 1;
    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) == 0) {
        return;
    }
    gDPSetRenderMode(g_displayListCursor++, 0x0C184DD8, 0);
    Geometry_SetCombineMode(1);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);
            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}
