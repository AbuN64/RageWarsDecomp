#if defined(VERSION_US)

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


typedef struct IdList {
    u16 count;
    s16 ids[1];
} IdList;


typedef struct { s16 x, y, z; u16 flags; s16 s, t; u8 r, g, b, a; } ColorVertex;


typedef struct { s32 tag, count; ColorVertex vertices[1]; } ColorMesh;


typedef struct { f32 x, y, z; } VertexColor;


typedef struct LitVertex {
    s16 position[3];
    s16 flags;
    s16 texture[2];
    u8 color[4];
} LitVertex;


typedef struct LitColorTable {
    s32 stride, count;
    s32 packed[1];
} LitColorTable;

s32 k_cachedSurfaceNormalWords[6] = {
    0, 0, 0, 0, 0, 0,
};

float k_audioDistanceAttenuationCurve[65] = {
    0.0f, 0.353553f, 0.420448f, 0.465302f, 0.5f, 0.528686f,
    0.553341f, 0.575082f, 0.594604f, 0.612372f, 0.628717f, 0.643877f,
    0.658037f, 0.671337f, 0.683891f, 0.695789f, 0.707107f, 0.717905f,
    0.728238f, 0.738148f, 0.747674f, 0.75685f, 0.765704f, 0.77426f,
    0.782542f, 0.790569f, 0.798359f, 0.805927f, 0.813288f, 0.820455f,
    0.827438f, 0.834248f, 0.840896f, 0.84739f, 0.853738f, 0.859948f,
    0.866025f, 0.871978f, 0.877811f, 0.88353f, 0.88914f, 0.894645f,
    0.900051f, 0.905362f, 0.91058f, 0.91571f, 0.920756f, 0.92572f,
    0.930605f, 0.935414f, 0.940151f, 0.944817f, 0.949414f, 0.953946f,
    0.958415f, 0.962821f, 0.967168f, 0.971457f, 0.97569f, 0.979869f,
    0.983995f, 0.988069f, 0.992094f, 0.996071f, 1.0f,
};

struct LightVolumeConeDistanceLookup g_lightVolumeConeDistanceLookup = {
    { 0.0f, 0.125f, 0.176777f, 0.216506f, 0.25f, 0.279509f, 0.306186f, 0.330719f, 0.353553f, 0.375f, 0.395285f, 0.414578f, 0.433013f, 0.450694f, 0.467707f, 0.484123f, 0.5f, 0.515388f, 0.53033f, 0.544862f, 0.559017f, 0.572822f, 0.586302f, 0.599479f, 0.612372f, 0.625f, 0.637377f, 0.649519f, 0.661438f, 0.673146f, 0.684653f, 0.695971f, 0.707107f, 0.71807f, 0.728869f, 0.73951f, 0.75f, 0.760345f, 0.770552f, 0.780625f, 0.790569f, 0.800391f, 0.810093f, 0.81968f, 0.829156f, 0.838525f, 0.847791f, 0.856957f, 0.866025f, 0.875f, 0.883883f, 0.892679f, 0.901388f, 0.910014f, 0.918559f, 0.927025f, 0.935414f, 0.943729f, 0.951972f, 0.960143f, 0.968246f, 0.976281f, 0.984251f, 0.992157f, 1.0f },
    1,
    { -9, -7, -8, -11, 8, 14, 25, 12, 18, 23, 26, 14, -4, -18, -14, -29, -41, -30, -27, -25, -27, -35, -30, -22, -31, -27, -17, -14, 0, 2, -2, -13, -13, -9, 5, 2, -2, 9, 24, 31, 34, 29, 21, 24, 10, 13, -3, -6, 1, 19, 31, 39, 29, 30, 20, 20, -1, -15, -26, -20, -24, -31, -29, -24, -26, -15, -15, 2, 17, 8, 7, 17, 14, 9, 12, 12, 4, 12, 5, 10, 13, 5, -3, -2, -10, -9, -8, -21, -21, -24, 72, 65 },
    { 0, 0 },
    { (void *)&g_lightAnimationOffsetTable[0x5C], (void *)&g_lightAnimationOffsetTable[0x5C], (void *)&g_triggeredMotionDispatchTriggerPairs_us[0x40], (void *)&g_spawnActorDispatchTable[0x88], (void *)&g_turretDispatchTriggerPairs_us[0x48], (void *)&g_lightAnimationOffsetTable[0x5C], (void *)&g_actionEnterDispatchTable[0x88], (void *)&g_damageDispatchTriggerPairs_us[0x78], (void *)&g_lightAnimationOffsetTable[0x5C], (void *)&g_movingMotionDispatchTriggerPairs_us[0x2C], (void *)&g_actionMotionDispatchTriggerPairs_us[0x4C], (void *)&g_lightAnimationOffsetTable[0x5C], (void *)&g_lightAnimationOffsetTable[0x5C], (void *)&g_lightAnimationOffsetTable[0x5C], (void *)&g_lightAnimationOffsetTable[0x5C] },
    { 0x00660000, 0x00040000, 0x00000021, 0x3F800000 },
};
#endif

#if defined(VERSION_US_REV1)

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


typedef struct IdList {
    u16 count;
    s16 ids[1];
} IdList;


typedef struct { s16 x, y, z; u16 flags; s16 s, t; u8 r, g, b, a; } ColorVertex;


typedef struct { s32 tag, count; ColorVertex vertices[1]; } ColorMesh;


typedef struct { f32 x, y, z; } VertexColor;


typedef struct LitVertex {
    s16 position[3];
    s16 flags;
    s16 texture[2];
    u8 color[4];
} LitVertex;


typedef struct LitColorTable {
    s32 stride, count;
    s32 packed[1];
} LitColorTable;

s32 k_cachedSurfaceNormalWords[6] = {
    0, 0, 0, 0, 0, 0,
};

float k_audioDistanceAttenuationCurve[65] = {
    0.0f, 0.353553f, 0.420448f, 0.465302f, 0.5f, 0.528686f,
    0.553341f, 0.575082f, 0.594604f, 0.612372f, 0.628717f, 0.643877f,
    0.658037f, 0.671337f, 0.683891f, 0.695789f, 0.707107f, 0.717905f,
    0.728238f, 0.738148f, 0.747674f, 0.75685f, 0.765704f, 0.77426f,
    0.782542f, 0.790569f, 0.798359f, 0.805927f, 0.813288f, 0.820455f,
    0.827438f, 0.834248f, 0.840896f, 0.84739f, 0.853738f, 0.859948f,
    0.866025f, 0.871978f, 0.877811f, 0.88353f, 0.88914f, 0.894645f,
    0.900051f, 0.905362f, 0.91058f, 0.91571f, 0.920756f, 0.92572f,
    0.930605f, 0.935414f, 0.940151f, 0.944817f, 0.949414f, 0.953946f,
    0.958415f, 0.962821f, 0.967168f, 0.971457f, 0.97569f, 0.979869f,
    0.983995f, 0.988069f, 0.992094f, 0.996071f, 1.0f,
};

float g_coneAttenuationSqrtRamp[65] = {
    0.0f, 0.125f, 0.176777f, 0.216506f, 0.25f, 0.279509f,
    0.306186f, 0.330719f, 0.353553f, 0.375f, 0.395285f, 0.414578f,
    0.433013f, 0.450694f, 0.467707f, 0.484123f, 0.5f, 0.515388f,
    0.53033f, 0.544862f, 0.559017f, 0.572822f, 0.586302f, 0.599479f,
    0.612372f, 0.625f, 0.637377f, 0.649519f, 0.661438f, 0.673146f,
    0.684653f, 0.695971f, 0.707107f, 0.71807f, 0.728869f, 0.73951f,
    0.75f, 0.760345f, 0.770552f, 0.780625f, 0.790569f, 0.800391f,
    0.810093f, 0.81968f, 0.829156f, 0.838525f, 0.847791f, 0.856957f,
    0.866025f, 0.875f, 0.883883f, 0.892679f, 0.901388f, 0.910014f,
    0.918559f, 0.927025f, 0.935414f, 0.943729f, 0.951972f, 0.960143f,
    0.968246f, 0.976281f, 0.984251f, 0.992157f, 1.0f,
};
#endif
