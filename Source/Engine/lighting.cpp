#include "Engine/cache.h"
#include "LIBC.H"
#include "include_asm.h"
#include "Common/sharedplayer.h"
#include "Common/model_tree_region_operations.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Fx/normalize_vector.h"
#include "Common/libsn_and_resident_callbacks.h"
#include "Render/player_controller_reset_views.h"
#include "Common/world.h"
#include "Common/shared_gameslot.h"
#include "Common/triple.h"
#include "Common/effectrender.h"
#include "Common/approachlocation.h"
#include "Actors/vertex_light_and_actor_views.h"
#include "Render/setn64_getpacksection.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include <platform_sdk.h>
#include "Engine/gregion.h"
#include "Engine/session.h"
#include "Game/builddirectionmatrix.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Engine/graphics_math.h"
#include "Engine/Instance/statinst.h"
#include "Engine/lighting.h"
#include "Common/cache_allocateresource.h"
#include "libgultra.h"
#include "Data/rest_source_records.h"
#include "libultra/ACTOR_STATE_TABLE_END_DATA.H"
#include "Engine/particle.h"

/* LIGHTING.CPP */

/* Decodes one stored light volume record into a runtime volume: fixed-point translation, rotation and scale
 * become the transform matrix and its inverse, the eight transformed unit-cube corners give the world bounds, and
 * a shape-1 volume derives its axis from the stored tilt instead of a rotation. */
void Lighting_DecodeBoxTransform(SceneLightVolume *self, LightVolumeRecord *src) {
    CVector3 translation;
    CVector3 rotation;
    CVector3 scale;
    CVector3 corners[8];
    CVector3 up;
    CVector3 tilt;
    CVector3 probe;
    u8 *matrix;
    s32 inside;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    self->shape = src->shape;
    translation.x = src->translation[0] * 2.38418579e-05f;
    translation.y = src->translation[1] * 2.38418579e-05f;
    translation.z = src->translation[2] * 2.38418579e-05f;
    if (self->shape != 1) {
        rotation.x = src->rotation[0] * 9.31322575e-09f;
        rotation.y = src->rotation[1] * 9.31322575e-09f;
        rotation.z = src->rotation[2] * 9.31322575e-09f;
    } else {
        up.x = 0;
        up.y = (-1.0f);
        up.z = 0;
        tilt.x = src->rotation[0] * 9.31322575e-09f;
        tilt.y = src->rotation[1] * 9.31322575e-09f;
        tilt.z = src->rotation[2] * 9.31322575e-09f;
        matrix = &self->transform;
        Graphu64_IdentityMatrix(matrix);
        RollMatrix(matrix, tilt.x);
        YawMatrix(matrix, tilt.y);
        Graphu64_ProjectPoint(matrix, &up, &self->axis);
        rotation.x = 0;
        rotation.y = 0;
        rotation.z = 0;
    }
    inside = 1;
    if (((rotation.x < 0) ? -rotation.x : rotation.x) > 0.00999999978f) {
        inside = 0;
    }
    if (((rotation.y < 0) ? -rotation.y : rotation.y) > 0.00999999978f) {
        inside = 0;
    }
    if (((rotation.z < 0) ? -rotation.z : rotation.z) > 0.00999999978f) {
        inside = 0;
    }
    self->flagB9 = 0;
    if (inside != 0) {
        self->flagB9 = 1;
    }
    scale.x = src->scale[0] * 2.38418579e-05f;
    scale.y = src->scale[1] * 2.38418579e-05f;
    scale.z = src->scale[2] * 2.38418579e-05f;
    self->falloff = (f32)src->falloff * 2 * 4.65661287e-10f;
    self->value = (f32)src->value * 2 * 4.65661287e-10f;
    if (g_gameSettings.flags & 0x4000) {
        self->direction.x = 0;
        self->direction.y = 0;
        self->direction.z = 0;
    } else {
        self->direction.x = (f32)src->direction[0] * 2.37487257e-06f;
        self->direction.y = (f32)src->direction[1] * 2.37487257e-06f;
        self->direction.z = (f32)src->direction[2] * 2.37487257e-06f;
    }
    matrix = &self->transform;
    self->flagB8 = src->flagB8;
    self->animatedLight = src->animatedLight;
    self->reservedWord = src->reservedWord;
    Graphu64_IdentityMatrix(matrix);
    Graphu64_ScaleMatrixWorld(matrix, scale.x, scale.y, scale.z);
    RollMatrix(matrix, rotation.z);
    YawMatrix(matrix, rotation.y);
    PitchMatrix(matrix, rotation.x);
    TranslateMatrix(matrix, translation.x, translation.y, translation.z);
    Graphu64_InvertAffineMatrix(&self->inverse, matrix);
    for (i = 0; i < 8; i++) {
        x = 1.0f;
        y = 1.0f;
        z = 1.0f;
        if (i & 1) {
            x = -1.0f;
        }
        if (i & 2) {
            y = -1.0f;
        }
        if (i & 4) {
            z = -1.0f;
        }
        probe.x = x;
        probe.y = y;
        probe.z = z;
        Graphu64_ProjectPoint(&self->transform, &probe, &corners[i]);
    }
    Region_ComputePointBounds(&self->bounds, 8, corners);
}

s32 Lighting_EvaluateLocalVolume(SceneLightVolume *lightVolume, CVector3 localPosition,
                  CVector3 *vectorComponents, f32 *intensity) {
    f32 falloff;
    f32 absoluteY;
    f32 absoluteZ;
    f32 volumeDistance;
    f32 localX;
    u8 shapeValue;

    localX = localPosition.x;
    volumeDistance = 0.0f;
    if (!(g_lightVolumePositiveBound <= localX) && !(localX <= g_lightVolumeNegativeBound) &&
        !(g_lightVolumePositiveBound <= localPosition.y) && !(localPosition.y <= g_lightVolumeNegativeBound) &&
        !(g_lightVolumePositiveBound <= localPosition.z) && !(localPosition.z <= g_lightVolumeNegativeBound)) {
        shapeValue = lightVolume->shape;
        switch (shapeValue) {
        case 0:
            volumeDistance = (localX * localX) + (localPosition.y * localPosition.y) +
                      (localPosition.z * localPosition.z);
            if (!(g_lightVolumePositiveBound < volumeDistance)) {
                volumeDistance = g_lightVolumeSphereDistanceLookup[(s32)(volumeDistance * g_lightVolumeSphereLookupScale)];
                goto shared;
            }
            goto fail;
        case 2:
            if (!(localX <= 0.0f)) {
                volumeDistance = (localPosition.y * localPosition.y) +
                          (localPosition.z * localPosition.z);
                if (!((localX * localX) < volumeDistance)) {
                    volumeDistance = g_lightVolumeConeDistanceLookup.coneDistance[(s32)(volumeDistance * g_lightVolumeConeLookupScale)];
                    volumeDistance /= localX;
                    goto shared;
                }
            }
            goto fail;
        case 1:
            if (localX < 0.0f) {
                localX = -localX;
            }
            absoluteY = localPosition.y;
            localPosition.x = localX;
            if (absoluteY < 0.0f) {
                absoluteY = -absoluteY;
            }
            absoluteZ = localPosition.z;
            localPosition.y = absoluteY;
            if (absoluteZ < 0.0f) {
                absoluteZ = -absoluteZ;
            }
            localPosition.z = absoluteZ;
            volumeDistance = absoluteZ;
            if (!(absoluteY <= volumeDistance)) {
                volumeDistance = absoluteY;
            }
            if (!(localX <= volumeDistance)) {
                volumeDistance = localX;
            }
            goto shared;
        default:
            goto shared;
        }
shared:
        volumeDistance = g_lightVolumeUnitIntensity - volumeDistance;
        falloff = lightVolume->falloff;
        if (volumeDistance < falloff) {
            volumeDistance /= falloff;
        } else {
            volumeDistance = g_lightVolumeUnitIntensity;
        }
        if (lightVolume->shape == 1) {
            *vectorComponents = lightVolume->axis;
        } else {
            *vectorComponents = localPosition;
        }
        Graphu64_NormalizeVec3(vectorComponents);
        *intensity = volumeDistance;
        return 1;
    } else {
fail:
        vectorComponents->y = 0.0f;
        vectorComponents->z = 0.0f;
        vectorComponents->x = g_lightVolumeDefaultDirectionX;
        *intensity = 0.0f;
        return 0;
    }
}



s32 Lighting_EvaluateLightVolume(SceneLightVolume *lightVolume, CVector3 worldPoint, CVector3 surfaceNormal, f32 *lightTransform,
                  CVector3 *lightContribution, f32 *contributionWeight) {
    CVector3 second;
    CVector3 first;
    CVector3 normal;
    f32 amount;
    f32 dot;
    f32 value;
    f32 objectValue;

    if (lightVolume->flagB9 != 0) {
        first.x = worldPoint.x * lightTransform[0];
        first.y = worldPoint.y * lightTransform[5];
        first.z = worldPoint.z * lightTransform[10];
        first.x += lightTransform[12];
        first.y += lightTransform[13];
        first.z += lightTransform[14];
        second.x = surfaceNormal.x * lightTransform[0];
        second.y = surfaceNormal.y * lightTransform[5];
        second.z = surfaceNormal.z * lightTransform[10];
    } else {
        Graphu64_TransformPoint(lightTransform, &worldPoint.x, &first);
        Graphu64_TransformDirection(lightTransform, &surfaceNormal.x, &second);
    }
    Graphu64_NormalizeVec3(&second.x);
    if (Lighting_EvaluateLocalVolume(lightVolume, first, &normal, &amount) == 0) {
        return 0;
    }
    {
        dot = -((normal.x * second.x) + (normal.y * second.y) +
                (normal.z * second.z));
        if (dot < 0.0f) {
            dot = 0.0f;
        }
        objectValue = lightVolume->value;
        value = amount * (objectValue +
                          (dot * (1.0f - objectValue)));
        amount = value;
        if (value <= 0.0f) {
            amount = 0.0f;
        }
        if (lightVolume->flagB8 != 0) {
            amount = -amount;
        }
        if (contributionWeight != 0) {
            *contributionWeight = amount;
        }
        Graphu64_ScaleVector(lightContribution, &lightVolume->direction, amount);
    }
    return 1;
}

void Lighting_AccumulateVertexLighting(SceneLightVolume **lights, s32 lightCount, Vertices38 *mesh,
                     FixedPointMatrix *matrices, CVector3 *output, s32 multiple)
{
    f32 matrix[16];
    CVector3 sum, position, normal, worldPosition, worldNormal, contribution;
    f32 amount, selectedAmount;
    s32 count, i, j, mode, colour, level, drawn;
    CVector3 *dest;
    u32 pattern;
    Vertex38 *vertex, *base;
    SceneLightVolume *light;

    count = mesh->count;
    base = mesh->vertices;
    Graphu64_ConvertMatrixToFloat(matrix, matrices);
    drawn = 0;
    for (i = 0; i < count; i++) {
        vertex = &base[i];
        dest = &output[drawn];
        mode = 0;
        selectedAmount = 0.0f;
        colour = 0;
        if (vertex->flags & 0x80) {
            continue;
        }
        if (multiple) {
            Graphu64_ConvertMatrixToFloat(matrix, &matrices[vertex->flags >> 8]);
        }
        position.x = vertex->px;
        position.y = vertex->py;
        position.z = vertex->pz;
        Graphu64_TransformPoint(matrix, &position, &worldPosition);
        normal.x = vertex->x;
        normal.y = vertex->y;
        normal.z = vertex->z;
        Graphu64_TransformDirection(matrix, &normal, &worldNormal);
        sum.x = 0.0f;
        sum.y = 0.0f;
        sum.z = 0.0f;
        for (j = 0; j < lightCount; j++) {
            light = lights[j];
            contribution.x = 0.0f;
            contribution.y = 0.0f;
            contribution.z = 0.0f;
            if (light->bounds.max.x > worldPosition.x &&
                light->bounds.max.y > worldPosition.y &&
                light->bounds.max.z > worldPosition.z &&
                light->bounds.min.x <= worldPosition.x &&
                light->bounds.min.y <= worldPosition.y &&
                light->bounds.min.z <= worldPosition.z &&
                Lighting_EvaluateLightVolume(light, worldPosition, worldNormal,
                                light->inverse, &contribution, &amount)) {
                if (light->animatedLight) {
                    mode = light->animatedLight;
                    colour = light->animationSeed;
                    selectedAmount = amount;
                }
                Graphu64_AddVec3(&sum, &sum, &contribution);
            }
        }
        if (mode) {
            level = 0;
            if (selectedAmount < 0.6f) level = 1;
            if (selectedAmount < 0.3f) level = 2;
            if (mode == 1) {
                vertex->flags = (vertex->flags & 0xFF8F) |
                                (((colour % 7 + 1) << 4) & 0x70);
            }
            if (mode == 2) {
                pattern = 0;
                pattern += (u32)worldPosition.x / 10;
                pattern += (u32)worldPosition.y / 10;
                pattern += (u32)worldPosition.z / 10;
                pattern = pattern % 7 + 1;
                vertex->flags = (vertex->flags & 0xFF8F) |
                                ((pattern << 4) & 0x70);
            }
            vertex->flags = (vertex->flags & 0xFFF3) | (level << 2);
            if (selectedAmount < 0.1f) {
                vertex->flags &= 0xFF83;
            }
        }
        dest->x += sum.x;
        dest->y += sum.y;
        dest->z += sum.z;
        drawn++;
    }
}

void Lighting_AccumulateDirectionalLighting(Vertices38 *data, FixedPointMatrix *matrices, CVector3 *output, s32 skin) {
    CVector3 light;
    f32 matrix[16];
    CVector3 normal, transformed;
    Light38 *source;
    Vertex38 *vertex, *base;
    CVector3 *dest;
    s32 drawn;
    s32 count, i;
    f32 dot, intensity;
    count = data->count;
    base = data->vertices;
    Graphu64_ConvertMatrixToFloat(matrix, matrices);
    source = g_sceneLightSources;
    light.x = source->x;
    light.y = source->y;
    light.z = source->z;
    Graphu64_NormalizeVec3(&light);
    drawn = 0;
    for (i = 0; i < count; i++) {
        vertex = &base[i];
        dest = &output[drawn];
        if (!(vertex->flags & 0x80)) {
            f32 red, green, blue;
            if (skin) Graphu64_ConvertMatrixToFloat(matrix, &matrices[vertex->flags >> 8]);
            normal.x = vertex->x;
            normal.y = vertex->y;
            normal.z = vertex->z;
            Graphu64_TransformDirection(matrix, &normal, &transformed);
            dot = transformed.x * light.x + transformed.y * light.y + transformed.z * light.z;
            intensity = ((dot < 0.0f) ? 0.2196078598f : (dot + 0.2196078598f)) * 255.0f;
            dot = intensity;
            red = dest->x + dot;
            green = dest->y + dot;
            blue = dest->z + dot;
            dest->x = red;
            dest->y = green;
            dest->z = blue;
            drawn++;
        }
    }
}

typedef struct Bounds {
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;
} Bounds;

typedef struct HitBox {
    u8 pad0[0x60];
    u32 signature[16];
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;
    u8 padB8[2];
    u8 flagBA;
    u8 padBB[2];
    u8 flagBD;
    u8 padBE[2];
} HitBox;

typedef struct HitBoxTable {
    s32 reservedWord;
    s32 count;
    HitBox boxes[1];
} HitBoxTable;

/* Collects the light volumes of the world sectors whose x/z extent overlaps box: the hit boxes in
   pack section 2 of each such sector whose bounds intersect box go to out (at most 64, with
   duplicates across sectors dropped by their summed signature words). Writes their number to
   outCount and returns 1 when any accepted box has flagBA set. */
s32 Lighting_QueryWorldLightVolumes(Bounds *box, void **out, s32 *outCount) {
    u32 keys[64];
    /* A query may intersect every world sector; accepted volumes are capped at 64. */
    WorldSector *sectors[128];
    s32 flag;
    s32 matches;
    s32 count;
    s32 i;
    s32 n;
    s32 j;
    u32 sum;
    s32 dup;
    WorldSector *sector;
    HitBoxTable *table;
    HitBox *entry;
    WorldSectorExtent *extent;
    Shared_World *world = &g_world;
    count = 0;
    matches = 0;
    flag = 0;
    for (i = 0; i < world->sectorEntryCount; i++) {
        sector = &world->sectors[i];
        extent = sector->bounds;
        if (extent->maxX > box->minX && extent->minX < box->maxX && extent->maxZ > box->minZ && extent->minZ < box->maxZ) {
            sectors[matches++] = sector;
        }
    }
    if (matches == 1) {
        sector = sectors[0];
        table = SetN64_GetPackSection(sector->resource->data, 2);
        n = table->count;
        n--;
        entry = table->boxes;
        for (; n != -1; n--) {
            if (box->maxX > entry->minX && box->minX < entry->maxX &&
                box->maxZ > entry->minZ && box->minZ < entry->maxZ &&
                box->maxY > entry->minY && box->minY < entry->maxY) {
                out[count++] = entry;
                if (entry->flagBA != 0) {
                    flag = 1;
                }
                if (count == 64) {
                    break;
                }
            }
            entry++;
        }
    } else if (matches < 2) {
        *outCount = count;
        return flag;
    } else {
        for (i = 0; i < matches; i++) {
            sector = sectors[i];
            table = SetN64_GetPackSection(sector->resource->data, 2);
            n = table->count;
            n--;
            entry = table->boxes;
            for (; n != -1; n--) {
                if (box->maxX > entry->minX && box->minX < entry->maxX &&
                    box->maxZ > entry->minZ && box->minZ < entry->maxZ &&
                    box->maxY > entry->minY && box->minY < entry->maxY) {
                    u32 *signature = entry->signature;
                    sum = 0;
                    for (j = 0; j < 16; j++) {
                        sum += signature[j];
                    }
                    dup = 0;
                    if (i != 0) {
                        for (j = 0; j < count; j++) {
                            if (keys[j] == sum) {
                                dup = 1;
                                break;
                            }
                        }
                    }
                    if (dup == 0) {
                        out[count] = entry;
                        keys[count] = sum;
                        count++;
                        if (entry->flagBA != 0) {
                            flag = 1;
                        }
                        if (count == 64) {
                            *outCount = count;
                            return flag;
                        }
                    }
                }
                entry++;
            }
        }
    }
    *outCount = count;
    return flag;
}

/* Filters the hit boxes held in section 2 of the pack table: keeps those whose bounds intersect the
   given bounds and which either carry no id filter (flagBD clear), are paired with wanted, or list
   the key that Statinst_FindPlacedPropIndex(wanted, table) finds inside the id list stored for
   their index in section 3. Writes the accepted box pointers into out (at most 64), reports their
   number through countOut, and returns 1 when any accepted box has flagBA set. With no table (table
   null) it defers to Lighting_QueryWorldLightVolumes. */

typedef struct IdList {
    u16 count;
    s16 ids[1];
} IdList;

s32 Lighting_QueryLightVolumes(Bounds *bounds, void *table, void **out, s32 *countOut, u8 *wanted) {
    s32 foundCount;
    s32 result;
    s32 idx;
    s32 found;
    s32 n;
    s32 *idTable;
    s32 key;
    s32 id;
    s16 *ids;
    s16 len;
    IdList *list;
    HitBoxTable *boxTable;
    HitBox *box;

    foundCount = 0;
    result = 0;
    if (table == NULL) {
        return Lighting_QueryWorldLightVolumes(bounds, out, countOut);
    }
    boxTable = SetN64_GetPackSection(table, 2);
    idx = boxTable->count;
    idx--;
    box = boxTable->boxes;
    for (; idx != -1; idx--) {
        if (bounds->maxX > box->minX && bounds->minX < box->maxX
            && bounds->maxZ > box->minZ && bounds->minZ < box->maxZ
            && bounds->maxY > box->minY && bounds->minY < box->maxY) {
            if (box->flagBD != 0) {
                found = 0;
                if (*wanted == 1) {
                    found = 1;
                } else {
                    idTable = SetN64_GetPackSection(table, 3);
                    if (*idTable > 0) {
                        list = SetN64_GetPackSection(idTable, idx);
                        ids = (s16 *)list;
                        len = list->count;
                        ids++;
                        key = Statinst_FindPlacedPropIndex(wanted, table);
                        for (n = 0; n < len; n++) {
                            id = *ids;
                            if (id >= 6000) {
                                id -= 6000;
                            } else if (id >= 4000) {
                                id -= 4000;
                            } else if (id >= 2000) {
                                id -= 2000;
                            }
                            if (id == key) {
                                found = 1;
                                break;
                            }
                            ids++;
                        }
                    }
                }
            } else {
                found = 1;
            }
            if (found != 0) {
                out[foundCount] = box;
                foundCount++;
                if (box->flagBA != 0) {
                    result = 1;
                }
                if (foundCount == 64) {
                    break;
                }
            }
        }
        box++;
    }
    *countOut = foundCount;
    return result;
}

/* A coloured model vertex: the Vtx_t layout, colour bytes at 0xC (bit 0x80 of flags keeps the vertex colour). */
typedef struct { s16 x, y, z; u16 flags; s16 s, t; u8 r, g, b, a; } ColorVertex;
typedef struct { s32 tag, count; ColorVertex vertices[1]; } ColorMesh;
/* Accumulated light per vertex (0..255 per channel). */
typedef struct { f32 x, y, z; } VertexColor;

static inline f32 clampIntensity(f32 c) {
    f32 r;
    if (!(c <= 255.0f)) {
        c = 255.0f;
    }
    r = c;
    if (!(5.0f <= r)) {
        r = 5.0f;
    }
    return r;
}
/* Writes the accumulated lighting into the mesh's vertex colours: each channel is clamped to 5..255, blended toward
 * white by the brightness setting (brightness / 255, at most 1) and stored clamped to a byte, except on vertices
 * with flag 0x80. With setting flag 0x4000 the colours are masked to black instead. */
void Lighting_ApplyVertexColors(ColorMesh *mesh, VertexColor *colors) {
    u8 colorMask = 0;
    f32 whiteBlend;
    VertexColor color;
    ColorVertex *vertex;
    s32 count, i, channelValue;
    if (1.0f < (f32)g_gameSettings.lightingGamma * (1.0f / 255.0f)) {
        whiteBlend = 1.0f;
    } else {
        whiteBlend = (f32)g_gameSettings.lightingGamma * (1.0f / 255.0f);
    }
    vertex = mesh->vertices;
    count = mesh->count;
    if (g_gameSettings.flags & 0x4000) {
        for (i = 0; i < count; i++) {
            vertex[i].r &= colorMask;
            vertex[i].g &= colorMask;
            vertex[i].b &= colorMask;
        }
    } else {
        for (i = 0; i < count; i++) {
            color = *colors++;
            color.x = clampIntensity(color.x) * (1.0f - whiteBlend) + whiteBlend * 255.0f;
            color.y = clampIntensity(color.y) * (1.0f - whiteBlend) + whiteBlend * 255.0f;
            color.z = clampIntensity(color.z) * (1.0f - whiteBlend) + whiteBlend * 255.0f;
            if (!(vertex[i].flags & 0x80)) {
                channelValue = (s32)color.x;
                channelValue = (channelValue < 256) ? ((channelValue < 0) ? 0 : ((channelValue < 256) ? channelValue : 255)) : 255;
                vertex[i].r = channelValue;
                channelValue = (s32)color.y;
                channelValue = (channelValue < 256) ? ((channelValue < 0) ? 0 : ((channelValue < 256) ? channelValue : 255)) : 255;
                vertex[i].g = channelValue;
                channelValue = (s32)color.z;
                channelValue = (channelValue < 256) ? ((channelValue < 0) ? 0 : ((channelValue < 256) ? channelValue : 255)) : 255;
                vertex[i].b = channelValue;
            }
        }
    }
}

/* "Lit Vertices": allocation tag */


/* A lit model vertex: the Vtx_t layout, colour bytes at 0xC. */
typedef struct LitVertex {
    s16 position[3];
    s16 flags;
    s16 texture[2];
    u8 color[4];
} LitVertex;
/* Section 1 of a model pack: per-vertex packed RGB lighting, present when count is non-zero. */
typedef struct LitColorTable {
    s32 stride, count;
    s32 packed[1];
} LitColorTable;
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
static inline void clampLitColor(u8 *dest, LitVertex *vertex) {
    dest[0] = MAX((u8)MIN(vertex->color[0], 225), 30);
    dest[1] = MAX((u8)MIN(vertex->color[1], 225), 30);
    dest[2] = MAX((u8)MIN(vertex->color[2], 225), 30);
}
/* Builds a lit copy of a model pack section 0: clears the per-vertex light accumulators, copies the model into a new
 * allocation (with a colour trailer section when the bounds query found light volumes that need it), adds the model's
 * packed RGB lighting, then directional or volume lighting, applies it to the vertex colours and, for the trailer,
 * stores each vertex colour clamped to 30..225. Returns the allocation handle, or 0 when allocation fails. */
s32 Lighting_BuildLitModel(s32 modelResource, void *lightResource, Bounds *bounds, FixedPointMatrix *matrices, s32 skinned,
                         u8 *wanted) {
    void *lights[64];
    s32 lightCount;
    s32 needsColors;
    s32 modelBytes;
    Vertices38 *model;
    u8 **allocation;
    Vertices38 *copiedModel;
    u8 *colors = 0;
    LitColorTable *table;
    s32 modelVertexCount;
    s32 clearIndex, colorIndex, sectorIndex, trailerIndex;
    s32 worldLightCount;
    s32 packedColor;
    s32 *pack;
    needsColors = Lighting_QueryLightVolumes(bounds, lightResource, lights, &lightCount, wanted);
    model = (Vertices38 *)SetN64_GetSizedPackSection(modelResource, 0, &modelBytes);
    modelVertexCount = model->count;
    for (clearIndex = 0; clearIndex < modelVertexCount; clearIndex++) {
        g_vertexLightAccumulation[clearIndex].x = 0;
        g_vertexLightAccumulation[clearIndex].y = 0;
        g_vertexLightAccumulation[clearIndex].z = 0;
    }
    if (needsColors != 0) {
        allocation = Cache_AllocateResource(0, modelBytes + 4 * sizeof(s32) + model->count * 4, 0, s_litVerticesAllocationTag);
        if (allocation == 0) {
            return 0;
        }
        /* section pack: last section index, section offsets, 0xDEADBEEF end marker */
        pack = (s32 *)*allocation;
        pack[0] = 1;
        pack[1] = 16;
        pack[2] = modelBytes + 16;
        pack[3] = 0xDEADBEEF;
        copiedModel = (Vertices38 *)(*allocation + pack[1]);
        colors = *allocation + pack[2];
        Libc_CopyBytes(copiedModel, model, modelBytes);
    } else {
        allocation = Cache_AllocateResource(0, modelBytes + 8, 0, s_litVerticesAllocationTag);
        if (allocation == 0) {
            return 0;
        }
        ((s32 *)*allocation)[0] = 0;
        copiedModel = (Vertices38 *)(*allocation + 8);
        Libc_CopyBytes(copiedModel, model, modelBytes);
    }
    table = SetN64_GetPackSection((void *)modelResource, 1);
    if (table->count != 0) {
        s32 *packed = table->packed;
        for (colorIndex = 0; colorIndex < modelVertexCount; colorIndex++) {
            CVector3 *light = &g_vertexLightAccumulation[colorIndex];
            s32 red, green, blue;
            packedColor = packed[colorIndex];
            red = ((s32)((u32)(packedColor & 0xFF0000) << 8)) >> 23;
            green = (s8)(packedColor >> 8) * 2;
            blue = ((s32)((u32)packedColor << 24)) >> 23;
            light->x += red;
            light->y += green;
            light->z += blue;
        }
    }
    if (g_vertexLightingMode == 0) {
        Lighting_AccumulateDirectionalLighting(copiedModel, matrices, g_vertexLightAccumulation, skinned);
    } else if (lightCount == 0) {
        Shared_World *world = &g_world;
        worldLightCount = 0;
        for (sectorIndex = 0; sectorIndex < world->sectorEntryCount; sectorIndex++) {
            worldLightCount += ((HitBoxTable *)SetN64_GetPackSection(*(void **)world->sectors[sectorIndex].resource, 2))->count;
        }
        if (worldLightCount == 0) {
            Lighting_AccumulateDirectionalLighting(copiedModel, matrices, g_vertexLightAccumulation, skinned);
        }
    } else {
        Lighting_AccumulateVertexLighting((SceneLightVolume **)lights, lightCount, copiedModel, matrices, g_vertexLightAccumulation, skinned);
    }
    Lighting_ApplyVertexColors((void *)copiedModel, (void *)g_vertexLightAccumulation);
    if (needsColors != 0) {
        s32 vertexCount = copiedModel->count;
        s32 colorSlot = 0;
        LitVertex *vertices = (LitVertex *)copiedModel->vertices;
        for (trailerIndex = 0; trailerIndex < vertexCount; trailerIndex++) {
            u8 *dest = &colors[colorSlot * 4];
            colorSlot++;
            clampLitColor(dest, &vertices[trailerIndex]);
        }
    }
    return (s32)allocation;
}

#if defined(VERSION_DE)
const char s_litVerticesAllocationText[16] =
    "Lit Vertices\000\006\064\003";
extern const unsigned int k_litVerticesTrailingWord;
#endif

#if defined(VERSION_EU)
const char s_litVerticesAllocationText[16] =
    "Lit Vertices\000\343\030\043";
extern const unsigned int k_litVerticesTrailingWord;
#endif

#if defined(VERSION_EU_X)
const char s_litVerticesAllocationText[16] =
    "Lit Vertices\000\360\000\000";

#endif

#if defined(VERSION_US)
const char s_litVerticesAllocationText[16] =
    "Lit Vertices\000\021\103\103";

#endif

#if defined(VERSION_US_REV1)

#endif

/* Keep this source unit's macros local to its body. */
#undef MAX
#undef MIN

/* action_initbreakablemotion_data.CPP */

#if defined(VERSION_DE) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern unsigned int g_breakableMotionZeros[8];
#else
unsigned int g_breakableMotionZeros[8] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
#endif

#if defined(VERSION_US)
extern struct {
    unsigned int words0[56];
    char text1[12];
    unsigned int words2[280];
} g_actionInitBreakableMotionRecordTable_us;
#endif

#if defined(VERSION_EU_X)
extern unsigned short g_actionInitBreakableMotionRecordTable_eu_x[678];
#endif

#if defined(VERSION_EU)
unsigned short g_actionInitBreakableMotionRecordTable_eu[678] = {
    0x0000, 0x0000, 0x0020, 0x45F0, 0x0000, 0x0000, 0x8011, 0x03D8, 0x0020, 0x45C0, 0x3F80, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0020, 0x467C, 0x0020, 0x4030, 0x8011, 0x03D8,
    0x0020, 0x4644, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0020, 0x474C,
    0x0020, 0x475C, 0x8011, 0x03D8, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x448C, 0x0020, 0x44EC, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0020, 0x4794, 0x0020, 0x47B0, 0x0020, 0x47E0, 0x0020, 0x47FC, 0x0027, 0x8FF8, 0x0027, 0x9048,
    0x0027, 0x8FAC, 0x0000, 0x0000, 0x0027, 0x917C, 0x0027, 0x91BC, 0x0027, 0x90C0, 0x0027, 0x919C,
    0x0027, 0x91DC, 0x0027, 0x91FC, 0x0027, 0x921C, 0x0000, 0x0000, 0x0027, 0x9234, 0x0000, 0x0000,
    0x0027, 0x8FC8, 0x0000, 0x0000, 0x3EDF, 0x66F4, 0x3E27, 0x8D37, 0x3EC0, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x4C88, 0x0020, 0x4890, 0x8011, 0x04F8, 0x0000, 0x5212,
    0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0020, 0x4D4C, 0x0020, 0x4A88,
    0x8011, 0x04F8, 0x0000, 0x521C, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0020, 0x4BD4, 0x0020, 0x4BF0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x4E00,
    0x0020, 0x4E1C, 0x0020, 0x4E4C, 0x0020, 0x4E68, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x8011, 0x03D8, 0x0020, 0x5318, 0x3F80, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0001, 0x0020, 0x5344, 0x0020, 0x54B4, 0x8011, 0x03D8, 0x0020, 0x5334,
    0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0020, 0x5500, 0x0020, 0x560C,
    0x8011, 0x03D8, 0x0020, 0x54F0, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0020, 0x522C, 0x0020, 0x526C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x56B4,
    0x0020, 0x56F0, 0x0027, 0x921C, 0x0000, 0x0000, 0x0027, 0x9234, 0x0000, 0x0000, 0x0027, 0x8FAC,
    0x0000, 0x0000, 0x0027, 0x8FC8, 0x0000, 0x0000, 0x0027, 0x908C, 0x0000, 0x0000, 0x0027, 0x9104,
    0x0000, 0x0000, 0x6963, 0x6573, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x06A5, 0x03E8,
    0x06A6, 0x01F4, 0x06A7, 0x000A, 0xFFFF, 0x0000, 0x06A6, 0x01F4, 0x06A7, 0x000A, 0xFFFF, 0x0000,
    0x06B8, 0x03E8, 0x06BA, 0x01F4, 0x06BB, 0x000A, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x60A0, 0x0020, 0x614C, 0x0000, 0x0000,
    0x0000, 0x52D0, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0001, 0x0020, 0x5740,
    0x0020, 0x61F8, 0x0000, 0x0000, 0x0000, 0x52DA, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400,
    0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x5EE4, 0x0020, 0x5F38, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0020, 0x6250, 0x0020, 0x6278, 0x0020, 0x62A8, 0x0020, 0x62D0, 0x3F80, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x6784, 0x8011, 0x03D8, 0x0020, 0x6778,
    0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x6624,
    0x0020, 0x66C4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x678C, 0x0000, 0x0000, 0x0020, 0x67DC,
    0x0020, 0x681C, 0x0020, 0x684C, 0x0020, 0x68B8, 0x0027, 0x8FF8, 0x0027, 0x9048, 0x0027, 0x917C,
    0x0027, 0x91BC, 0x0027, 0x90C0, 0x0027, 0x919C, 0x0027, 0x91DC, 0x0027, 0x91FC, 0x0020, 0x6950,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x7AB0, 0x0020, 0x7ADC,
    0x8011, 0x00B0, 0x0020, 0x7758, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0001,
    0x0020, 0x7B7C, 0x0020, 0x7BD8, 0x8011, 0x00B0, 0x0020, 0x7758, 0x3F80, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0002, 0x0020, 0x7C88, 0x0020, 0x7CB4, 0x8011, 0x00B0, 0x0020, 0x7758,
    0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0003, 0x0020, 0x7D54, 0x0020, 0x7DB0,
    0x8011, 0x00B0, 0x0020, 0x7758, 0x3F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0004,
    0x0000, 0x0000, 0x0020, 0x70F0, 0x8011, 0x00B0, 0x0020, 0x7758, 0x3F80, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x7814, 0x0020, 0x78B0, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0020, 0x7E5C, 0x0000, 0x0000, 0x0020, 0x7E94, 0x0000, 0x0000, 0x0020, 0x7F3C,
    0x0020, 0x7F80, 0x0020, 0x7ECC, 0x0020, 0x7F0C, 0x0020, 0x7FB0, 0x0000, 0x0000, 0x0020, 0x7FC0,
    0x0000, 0x0000, 0x0020, 0x7FE4, 0x0000, 0x0000, 0x0020, 0x8004, 0x0000, 0x0000, 0x0027, 0x908C,
    0x0000, 0x0000, 0x0027, 0x9104, 0x0000, 0x0000,
};
#endif

#if defined(VERSION_DE)
extern unsigned int g_actionInitBreakableMotionRecordTable_de[339];
#endif

/* Retained data for this translation unit. */

const float g_lighting[6] = {
    1.0f, -1.0f, 64.0f, 64.0f, 1.0f, 1.0f,
};
#if defined(VERSION_EU_X)
const unsigned int k_litVerticesAllocationTagTrailingZeroWord = 0x00000000;
#endif
#if defined(VERSION_US)
const unsigned int g_vertexColorsTag = 0x616D6572;
#endif
#if defined(VERSION_US_REV1)
const char g_litVerticesText[16] = "Lit Vertices\000\203\022o";
#endif
#if defined(VERSION_DE)
const unsigned int k_litVerticesTrailingWord = 0x8E840038;
#endif
#if defined(VERSION_EU)
const unsigned int k_litVerticesTrailingWord = 0x00031880;
#endif
