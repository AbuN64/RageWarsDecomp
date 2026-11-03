#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MODEL_TREE_REGION_OPERATIONS.H"
#include "TYPES.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "RENDER/PLAYER_CONTROLLER_RESET_VIEWS.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/APPROACHLOCATION.H"
#include "ACTORS/VERTEX_LIGHT_AND_ACTOR_VIEWS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include <ultra64.h>
#include "ENGINE/GREGION.H"
#include "ENGINE/SETN64.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "GRAPHU64/GRAPHU64_GETANGLEDISTANCE.H"
#include "GRAPHU64/GRAPHU64_PACKFIXEDMATRIX.H"

/* 80275E44_12.CPP */
#define SK_FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))




extern void Graphu64_ScaleMatrixWorld(void *, f32, f32, f32);



void Lighting_DecodeBoxTransform(u8 *self, u8 *src) {
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
    SK_FIELD(self, u8, 187) = SK_FIELD(src, u8, 47);
    translation.x = SK_FIELD(src, s32, 0) * 2.38418579e-05f;
    translation.y = SK_FIELD(src, s32, 4) * 2.38418579e-05f;
    translation.z = SK_FIELD(src, s32, 8) * 2.38418579e-05f;
    if (SK_FIELD(self, u8, 187) != 1) {
        rotation.x = SK_FIELD(src, s32, 12) * 9.31322575e-09f;
        rotation.y = SK_FIELD(src, s32, 16) * 9.31322575e-09f;
        rotation.z = SK_FIELD(src, s32, 20) * 9.31322575e-09f;
    } else {
        up.x = 0;
        up.y = (-1.0f);
        up.z = 0;
        tilt.x = SK_FIELD(src, s32, 12) * 9.31322575e-09f;
        tilt.y = SK_FIELD(src, s32, 16) * 9.31322575e-09f;
        tilt.z = SK_FIELD(src, s32, 20) * 9.31322575e-09f;
        matrix = &((SceneLightVolume *)self)->transform;
        Graphu64_IdentityMatrix(matrix);
        RollMatrix(matrix, tilt.x);
        YawMatrix(matrix, tilt.y);
        Graphu64_ProjectPoint(matrix, &up, &((SceneLightVolume *)self)->axis);
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
    SK_FIELD(self, u8, 185) = 0;
    if (inside != 0) {
        SK_FIELD(self, u8, 185) = 1;
    }
    scale.x = SK_FIELD(src, s32, 24) * 2.38418579e-05f;
    scale.y = SK_FIELD(src, s32, 28) * 2.38418579e-05f;
    scale.z = SK_FIELD(src, s32, 32) * 2.38418579e-05f;
    SK_FIELD(self, f32, 0) = (f32)SK_FIELD(src, s32, 36) * 2 * 4.65661287e-10f;
    SK_FIELD(self, f32, 4) = (f32)SK_FIELD(src, s32, 40) * 2 * 4.65661287e-10f;
    if (g_gameSettings.flags & 0x4000) {
        SK_FIELD(self, s32, 8) = 0;
        SK_FIELD(self, s32, 12) = 0;
        SK_FIELD(self, s32, 16) = 0;
    } else {
        SK_FIELD(self, f32, 8) = (f32)SK_FIELD(src, u32, 60) * 2.37487257e-06f;
        SK_FIELD(self, f32, 12) = (f32)SK_FIELD(src, u32, 64) * 2.37487257e-06f;
        SK_FIELD(self, f32, 16) = (f32)SK_FIELD(src, u32, 68) * 2.37487257e-06f;
    }
    matrix = &((SceneLightVolume *)self)->transform;
    SK_FIELD(self, u8, 184) = SK_FIELD(src, u8, 55);
    SK_FIELD(self, u8, 186) = SK_FIELD(src, u8, 59);
    SK_FIELD(self, u8, 189) = SK_FIELD(src, u8, 75);
    Graphu64_IdentityMatrix(matrix);
    Graphu64_ScaleMatrixWorld(matrix, scale.x, scale.y, scale.z);
    RollMatrix(matrix, rotation.z);
    YawMatrix(matrix, rotation.y);
    PitchMatrix(matrix, rotation.x);
    TranslateMatrix(matrix, translation.x, translation.y, translation.z);
    Graphu64_InvertAffineMatrix(&((SceneLightVolume *)self)->inverse, matrix);
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
        Graphu64_ProjectPoint(&((SceneLightVolume *)self)->transform, &probe, &corners[i]);
    }
    Region_ComputePointBounds(&((SceneLightVolume *)self)->bounds, 8, corners);
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
                    volumeDistance = g_lightVolumeConeDistanceLookup[(s32)(volumeDistance * g_lightVolumeConeLookupScale)];
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

/* 800C9BB0.CPP */
const float g_lightVolumeEvaluationConstantsUsRev1[6] = {
    1.0f, -1.0f, 64.0f, 64.0f, 1.0f, 1.0f,
};

/* 80277444_2.CPP */


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
                     PackedMatrixWords *matrices, CVector3 *output, s32 multiple)
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

void Lighting_AccumulateDirectionalLighting(Vertices38 *data, PackedMatrixWords *matrices, CVector3 *output, s32 skin) {
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
        table = SetN64_GetPackSection(sector->resource->pack, 2);
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
            table = SetN64_GetPackSection(sector->resource->pack, 2);
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

/* Filters the 0xC0-byte hit records held in table slot 2 of table: keeps those whose box
   (six floats at record offset 0xA0) intersects the given bounds, and which either have no
   byte set at record offset 0xBD, are paired with wanted, or list the key that
   Statinst_FindPlacedPropIndex(wanted, table) finds inside the id list at slot table-table index of the list
   table in slot 3. Writes the accepted record pointers into out (at most 0x40 of them),
   reports their number through countOut, and returns 1 when any accepted record has its byte at
   record offset 0xBA set. With no table (table null) it defers to Lighting_QueryWorldLightVolumes. */

extern int Statinst_FindPlacedPropIndex(void *wanted,int key);

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

extern char s_litVerticesAllocationTag[13]; /* "Lit Vertices": allocation tag */
extern CVector3 g_vertexLightAccumulation[];
extern s32 g_vertexLightingMode;

extern void **Cache_AllocateResource(s32, s32, s32, char *);

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
s32 Lighting_BuildLitModel(s32 modelResource, void *lightResource, Bounds *bounds, PackedMatrixWords *matrices, s32 skinned,
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

/* 800C9C0C_2.CPP */
#if defined(VERSION_DE)
const char s_litVerticesAllocationText[16] =
    "Lit Vertices\000\006\064\003";
const unsigned int k_lightingEncodedBytesBlock1TrailingWord = 0x8E840038;
#endif

#if defined(VERSION_EU)
const char s_litVerticesAllocationText[16] =
    "Lit Vertices\000\343\030\043";
const unsigned int k_lightingEncodedBytesBlock2TrailingWord = 0x00031880;
#endif

#if defined(VERSION_EU_X)
const char s_litVerticesAllocationText[16] =
    "Lit Vertices\000\360\000\000";
const unsigned int k_litVerticesAllocationTagTrailingZeroWord = 0x00000000;
#endif

#if defined(VERSION_US)
const char s_litVerticesAllocationText[16] =
    "Lit Vertices\000\021\103\103";
const unsigned int k_lightingApplyVertexColorsWords = 0x616D6572;
#endif









#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_litVerticesText_Lighting.c */
const char g_litVerticesText[16] = "Lit Vertices\000\203\022o";
#endif
