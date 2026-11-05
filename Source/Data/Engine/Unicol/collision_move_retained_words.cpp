#if defined(VERSION_US_REV1)

#include "include_asm.h"


#include "types.h"


#include "Common/motion_step.h"


#include "Common/weapon_screen_message_operations.h"


#include "Common/triple.h"


#include "Common/sharedplayer.h"


#include "Common/virtual_pager.h"


#include "Common/rendersortrecord.h"


#include "Common/sky_layers.h"


#include "Anim/cplane_resetcontact.h"


#include "Engine/Unicol/collide.h"


#include "Graphu64/graphu64_getangledistance.h"


#include "Engine/Unicol/Collide/ccollision_traceactormotion.h"


#include "Polycol/polycol_tracegeometry.h"


#include "Polycol/cpolycollision_traceceilingtriangle.h"


#include "Common/vector4f.h"


#include "Common/runtime_declarations.h"


#include "Common/approachlocation.h"


#include "Common/output.h"


#include "Common/graphics_matrix_and_vector_math.h"


#include "Fx/normalize_vector.h"


#include "Engine/Unicol/Collide/ccollision_intersectsegmentbox.h"


#include "Engine/Unicol/plane.h"


#include "Engine/Unicol/Collide/ccollision_testoffsetpolygon.h"


#include "Common/ballisticparams.h"


#include "Common/Lone/collision_current_actor.h"


#include "Engine/Unicol/Collide/ccollision_testraycylinder.h"


#include "Plane/ccollision_intersectfrontplanepoint.h"


#include "Rsp/random_direction_and_affine_math.h"


#include "Engine/Unicol/Collide/ccollision_testsegmentpolygon.h"


#include "Common/aiprofile.h"


#include "Common/box_contact.h"


#include "Common/legacy_collision_actor.h"


#include "Common/world.h"


#include "Collide/ccollision_testsegmentdisk.h"


#include "Engine/scene_drawopaqueactors.h"


#include "Sched/sky_postscreenmessage.h"


#include "Common/ccollisionsetup_t.h"


#include "Io/debug_memory.h"


#include "Common/format.h"


#include "Common/resident_event_handler.h"


#include "data_overlay_layouts.h"



struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 retainedFloatWords[12];
} g_gameObjectMoveToXzKeepHeightRetainedWords __attribute__((aligned(4))) = {
    0,
    0,
    0,
    0,
    -1,
    { 0x3f, 0xc7, 0x4f, 0x67, 0x3f, 0xc7, 0x2f, 0x5e, 0x3f, 0xc7, 0xf, 0x55 }
};

struct {
    u8 retainedFloatWord[4];
} g_weaponSlotNearQuarterTurnRadians __attribute__((aligned(4))) = {
    { 0x3F, 0xC8, 0x0F, 0x9A }
};
#endif
