#include "RENDER/PLAYER_CONTROLLER_RESET_VIEWS.H"
#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/LOCALDECODERANGE.H"
#include "COMMON/FRUSTUM.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "RENDER/RUMBLE_EXPANDMESHMATERIAL.H"
#include "SYSTEM/TEXTLOAD_RESETTEXTURECACHE.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern Gfx *g_displayListCursor;

extern char g_geometryMaterialIntensityTexture;

extern u32 g_geometryEffectGeometryMode;

extern s32 Geometry_SetModePreset(s32);

s32 SetN64_GetSizedPackSection(s32 packAddress, s32 sectionIndex, s32 *sectionSizeOut);

extern struct CacheResourceBlockView *Cache_AllocResourceBlock(s32, void *, s32);

void Cache_ReplaceResourceBlock(s32 unused, struct CacheResourceBlockView **handle, struct CacheResourceBlockView *replacement);



extern s32 g_geometryViewEffect;

extern signed char g_geometryMaterialLightDirection[3];

extern char g_playerViewRenderContext;

extern void Graphu64_UnpackFixedMatrix(f32 *matrix, void *model);

extern void Graphu64_GetMatrixTranslation(f32 *matrix, CVector3 *position);

extern char *Playerai_GetFirstPlayer(void *players);

extern void Graphu64_SubtractVectors(struct CVector3_t *difference, struct CVector3_t *leftVector, struct CVector3_t *rightVector);


void Geometry_SetupIntensityPass(void) {
    Gfx *cmd;

    TextLoad_ResetTextureCache();

    cmd = g_displayListCursor++;
    gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, &g_geometryMaterialIntensityTexture);
    cmd = g_displayListCursor++;
    gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP, 5, 0, G_TX_WRAP, 5, 0);
    cmd = g_displayListCursor++;
    gDPLoadSync(cmd);
    cmd = g_displayListCursor++;
    gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 255, 1024);
    cmd = g_displayListCursor++;
    gDPPipeSync(cmd);
    cmd = g_displayListCursor++;
    gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, 0, G_TX_WRAP, 5, 0);
    cmd = g_displayListCursor++;
    gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 124, 124);
    cmd = g_displayListCursor++;
    gSPTexture(cmd, 2048, 2048, 0, 0, G_ON);
    cmd = g_displayListCursor++;
    gDPSetTextureLUT(cmd, G_TT_NONE);
    cmd = g_displayListCursor++;
    gSPGeometryMode(cmd, 0, g_geometryEffectGeometryMode | 0x00260404);

    Geometry_SetModePreset(29);
}

/* Expand packed geometry commands into display lists while rebuilding resource offsets. */
void Geometry_ExpandModelCommands(s32 unused, struct CacheResourceBlockView **res, s32 extra, s32 sentinel) {
    s32 len0, len1, len3, len4, len5;
    struct CacheResourceBlockView *allocation;
    struct Pack *old;
    struct Pack *oldList;
    struct Pack *newList;
    u8 *vertices;
    u8 *vertexData;
    s32 vertexCount;
    s32 parts, size, count, i, commandSize, offset, total;
    struct Pack *dst;
    struct Pack *srcEntry, *dstEntry;
    u8 *input;
    Gfx *output;
    s32 tag;
    u32 value, a, b, c, n, block;
    s32 b2, c2;
    s32 vertexSlot, vertexOffset;
    const u32 vertexSegment = 0x02000000;
    const u32 matrixSegment = 0x01000000;
    s32 l, q, r;
    /* Expanded material records have the same size in both passes. */
    s32 materialBytes = 32;
    void *dstData;
    void *copySource4, *copySource5, *copySource3, *copySource2, *copySource1, *copySource0;
    if (Ppdecom_UnpackResource(res, 1) != 0) {
        parts = 6;
        if (extra == 0) {
            parts = 3;
            if (sentinel != 0) parts = 4;
        }
        size = (parts * 4 + 15) & ~7;
        old = (*res)->pack;
        SetN64_GetSizedPackSection(old, 0, &len0);
        size += len0;
        SetN64_GetSizedPackSection(old, 1, &len1);
        size += len1;
        oldList = SetN64_GetPackSection(old, 2);
        count = oldList->count;
        i = 0;
        size += (count * 4 + 15) & ~7;
        if (count > 0) do {
            srcEntry = SetN64_GetPackSection(oldList, i);
            size += 16;
            size += materialBytes;
            input = SetN64_GetPackSection(srcEntry, 1);
            {
                s32 countTag;
                commandSize = 0;
                while ((countTag = *input) != 0) {

                    if (countTag & 0x80) {
                        input += 2;
                        commandSize += 8;
                        if (*input & 0x80) input += 2;
                    } else {
                        countTag &= 0x60;
                        switch (countTag) {
                        case 32: input += 2; commandSize += 8; break;
                        case 64: input += 2; commandSize += 8; break;
                        case 96: input += 5; commandSize += 8; break;
                        }
                    }
                }
                size += (commandSize + 15) & ~7;
            }
            i++;
        } while (i < count);
        if (extra != 0) {
            SetN64_GetSizedPackSection(old, 3, &len3);
            size += len3;
            SetN64_GetSizedPackSection(old, 4, &len4);
            size += len4;
            SetN64_GetSizedPackSection(old, 5, &len5);
            size += len5;
        }
        if (sentinel != 0) size += 8;
        allocation = Cache_AllocResourceBlock(0, res, size);
        if (allocation != 0) {
            offset = (parts * 4 + 15) & ~7;
            old = (*res)->pack;
            dst = allocation->pack;
            dst->count = parts;
            dst->offsets[0] = offset;
            copySource0 = SetN64_GetSizedPackSection(old, 0, &len0);
            vertexCount = 0;
            vertices = SetN64_GetPackSection(dst, 0);
            Libc_CopyBytes(vertices, copySource0, len0);
            offset += len0;
            dst->offsets[1] = offset;
            copySource1 = SetN64_GetSizedPackSection(old, 1, &len1);
            dstData = SetN64_GetPackSection(dst, 1);
            Libc_CopyBytes(dstData, copySource1, len1);
            offset += len1;
            dst->offsets[2] = offset;
            oldList = SetN64_GetPackSection(old, 2);
            newList = SetN64_GetPackSection(dst, 2);
            count = oldList->count;
            i = 0;
            newList->count = count;
            total = (count * 4 + 15) & ~7;
            newList->offsets[0] = total;
            if (count > 0) {
                vertexData = vertices + 8;
                do {
                    srcEntry = SetN64_GetPackSection(oldList, i);
                    dstEntry = SetN64_GetPackSection(newList, i);
                    block = (srcEntry->count * 4 + 15) & ~7;
                    dstEntry->count = srcEntry->count;
                    dstEntry->offsets[0] = block;
                    copySource2 = SetN64_GetPackSection(srcEntry, 0);
                    dstData = SetN64_GetPackSection(dstEntry, 0);
                    Rumble_ExpandMeshMaterial(dstData, copySource2);
                    block += materialBytes;
                    dstEntry->offsets[1] = block;
                    input = SetN64_GetPackSection(srcEntry, 1);
                    output = SetN64_GetPackSection(dstEntry, 1);
                    if ((tag = *input) != 0) {
                        do {
                            commandSize = tag & 0x60;
                            if (tag & 0x80) {
                                value = *input++ << 8;
                                value |= *input++;
                                a = (s32)value >> 10 & 0x1F;
                                b = (s32)value >> 5 & 0x1F;
                                c = value & 0x1F;
                                if (*input & 0x80) {
                                    {
                                        s32 hi = *input++;
                                        s32 lo = *input++;
                                        value = hi << 8;
                                        value |= lo;
                                        commandSize = (s32)value >> 10 & 31;
                                        b2 = (s32)value >> 5 & 31;
                                        c2 = value & 31;
                                        gSP2Triangles(output++, a, b, c, 0, commandSize, b2, c2, 0);
                                    }
                                } else {
                                    gSP1Triangle(output++, a, b, c, 0);
                                }
                            } else {
                                switch (commandSize) {
                                case 32:
                                    value = *input++ << 8;
                                    value |= *input++;
                                    vertexSlot = (s32)value >> 5 & 31;
                                    n = value & 0x1F;
                                    if (n == 0) n = 32;
                                    vertexOffset = vertexCount;
                                    /* Segment 2 holds vertex data, following its eight-byte header. */
                                    gSPVertex(output++, (vertexData + vertexOffset * 16 - vertices) + vertexSegment, n, vertexSlot);
                                    vertexCount += n;
                                    break;
                                case 64:
                                    input++;
                                    {
                                        s32 matrixIndex = *input++;
                                        /* Segment 1 holds 64-byte matrices. */
                                        gSPMatrix(output++, matrixSegment + matrixIndex * 64,
                                                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                                    }
                                    break;
                                case 96:
                                    vertexSlot = tag & 31;
                                    input++;
                                    value = *input++;
                                    l = *input++;
                                    q = *input++;
                                    r = *input++;
                                    value <<= 24;
                                    value |= l << 16;
                                    value |= q << 8;
                                    value |= r;
                                    gSPModifyVertex(output++, vertexSlot, G_MWO_POINT_ST, value);
                                    break;
                                }
                            }
                            tag = *input;
                        } while (tag != 0);
                    }
                    gSPEndDisplayList(output++);
                    dstData = SetN64_GetPackSection(dstEntry, 1);
                    commandSize = (u8 *)output - (u8 *)dstData;
                    block += (commandSize + 7) & ~7;
                    total += block;
                    dstEntry->offsets[2] = block;
                    newList->offsets[i + 1] = total;
                    i++;
                } while (i < count);
            }
            offset += total;
            dst->offsets[3] = offset;
            if (extra != 0) {
                copySource3 = SetN64_GetSizedPackSection(old, 3, &len3);
                dstData = SetN64_GetPackSection(dst, 3);
                Libc_CopyBytes(dstData, copySource3, len3);
                offset += len3;
                dst->offsets[4] = offset;
                copySource4 = SetN64_GetSizedPackSection(old, 4, &len4);
                dstData = SetN64_GetPackSection(dst, 4);
                Libc_CopyBytes(dstData, copySource4, len4);
                offset += len4;
                dst->offsets[5] = offset;
                copySource5 = SetN64_GetSizedPackSection(old, 5, &len5);
                dstData = SetN64_GetPackSection(dst, 5);
                Libc_CopyBytes(dstData, copySource5, len5);
                offset += len5;
                dst->offsets[6] = offset;
            }
            if (sentinel != 0) {
                Gfx *sentinelData = SetN64_GetPackSection(dst, 3);
                offset += 8;
                sentinelData->words.w0 = -1;
                sentinelData->words.w1 = 0;
                dst->offsets[4] = offset;
            }
        }
        Cache_ReplaceResourceBlock(0, res, allocation);
    }
}

typedef struct { s32 flagWord; char pad4[2]; u8 flags; } ModelMaterial;

s32 Geometry_ApplyMaterialLighting(void *model, void *lights, ModelMaterial *material) {
    CVector3 direction;
    CVector3 position;
    f32 matrix[4][4];

    if (g_geometryViewEffect != 0 && (material->flagWord & 0x8000)) {
        Graphu64_UnpackFixedMatrix((f32 *)matrix, model);
        Graphu64_GetMatrixTranslation((f32 *)matrix, &position);
        Graphu64_SubtractVectors(&direction, &((PlayerControllerReleaseView *)Playerai_GetFirstPlayer(&g_playerViewRenderContext))->previousPosition, &position);
        Graphu64_NormalizeVec3(&direction);
        {
            Gfx *cmd;
            Gfx *light;
            Gfx *ambient;

            g_geometryMaterialLightDirection[0] = direction.x * g_geometryLightDirectionScale;
            g_geometryMaterialLightDirection[1] = direction.y * g_geometryLightDirectionScale;
            g_geometryMaterialLightDirection[2] = direction.z * g_geometryLightDirectionScale;
            cmd = g_displayListCursor++;
            gMoveWd(cmd, G_MW_NUMLIGHT, 0, 0x18);
            gDma2p(g_displayListCursor++, G_MOVEMEM, (unsigned int)(g_geometryMaterialLightDirection - 8), 16, G_MV_LIGHT, 48);
            gDma2p(g_displayListCursor++, G_MOVEMEM, (unsigned int)(g_geometryMaterialLightDirection - 0x10), 16, G_MV_LIGHT, 72);
        }
        return 1;
    }
    if (lights != 0) {
        gMoveWd(g_displayListCursor++, G_MW_NUMLIGHT, 0, 0x18);
        gDma2p(g_displayListCursor++, G_MOVEMEM, (unsigned int)((char *)lights + 8), 16, G_MV_LIGHT, 48);
        gDma2p(g_displayListCursor++, G_MOVEMEM, (unsigned int)lights, 16, G_MV_LIGHT, 72);
    }
    return 0;
}

#include "COMMON/GAME_SESSION.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/PACKEDMESHMATERIAL.H"
#include "COMMON/DISPLAY.H"
extern u32 g_displayListCapacityUsRev1;
extern CGameStatus g_matchRoundCounters;
extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern s32 Geometry_SetupMaterial(void *material, s32 pass);
/* Draws an actor model's parts, choosing each part by the 0x38 bits of its material byte 6: on the special
 * character 0x12 the part must equal the bits for its variant (or be a fade/bonus part whose flag is set),
 * otherwise the 0x38/0x30/0x10 groups are drawn only when the matching flag (fade, bonus, glow) is set. */
void Geometry_DrawActorModelParts(void **resource, struct Player *owner, void *matrix, s32 segment, Shared_ParticleLighting *lights, void *textures, s32 pass) {
    struct Pack *header;
    void *base;
    struct Pack *parts;
    struct Pack *part;
    MeshMaterial *material;
    s32 count;
    s32 i;
    s32 hide = 0;
    s32 bonus = 0;
    s32 glow = 0;
    CGameStatus *settings;

    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
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
    header = *resource;
    Cache_MarkResourceInUse(0, resource);
    if (segment != 0) {
        gSPSegment(g_displayListCursor++, 1, matrix);
    } else {
        gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD);
    }
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = parts->count;
    for (i = 0; i < count; i++) {
        AiProfile *state;
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        state = owner->profile;
        if (state->character == 18 && (g_matchRoundCounters.m_bFragTagOn == 0 || state->bonus == 0)) {
            u32 bits;
            u32 wanted;
            if (state->variant == 0) {
                wanted = 40;
            } else if (state->variant == 1) {
                wanted = 32;
            } else {
                wanted = 24;
            }
            bits = material->mode & 0x38;
            if (bits == wanted || (bits == 0x38 && hide != 0) || (bits == 0x30 && bonus != 0)) {
                if (Geometry_SetupMaterial(material, pass) != 0) {
                    void *list = SetN64_GetPackSection(part, 1);
                    gSPDisplayList(g_displayListCursor++, list);
                }
            }
        } else {
            u32 bits = material->mode & 0x38;
            if (bits == 0x38 && hide == 0) continue;
            if (bits == 0x30 && bonus == 0) continue;
            if (bits == 0x10 && glow == 0) continue;
            if (Geometry_SetupMaterial(material, pass) != 0) {
                void *list = SetN64_GetPackSection(part, 1);
                gSPDisplayList(g_displayListCursor++, list);
            }
        }
    }
}
