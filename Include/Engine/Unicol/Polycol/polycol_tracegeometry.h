#ifndef ENGINE_UNICOL_POLYCOL_POLYCOL_TRACEGEOMETRY_H
#define ENGINE_UNICOL_POLYCOL_POLYCOL_TRACEGEOMETRY_H
#include "Engine/Unicol/Polycol/polycol_tracemeshtriangle.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/ppdecom_unpackresource.h"
#include "Anim/collision_ray.h"
#include "Engine/Unicol/polycol.h"
#include "Render/setn64_getpacksection.h"
#include "Collide/ccollision_testsegmentdisk.h"
#include "Engine/Unicol/plane.h"
#include "Ppdecom/ppdecom_quicksortrecords.h"
struct WorldCollisionElementTable;
extern void CPolyCollision_TraceElementMesh(void *contextAddress);
#include "Anim/collision_ray.h"

/* The world's counted table of collision elements: its entries start after a 0x5AC-byte header. */
typedef struct WorldCollisionElementTable {
    char header[0x5AC];
    s32 count;
    EntryC entries[1];
} WorldCollisionElementTable;
extern struct WorldCollisionElementTable g_worldCollisionElementTable;
#endif
