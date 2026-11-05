#ifndef COMMON_NAVIGATION_NODE_AND_ROUTE_VIEWS_H
#define COMMON_NAVIGATION_NODE_AND_ROUTE_VIEWS_H
#include "types.h"
#include "Common/navigation_graph.h"



struct ActorMotionResource;
struct NavigationNodeFlagsView;
typedef struct NavigationNodeFlagsView NavigationNodeFlagsView;


extern float g_portalRelatedGoalDefaultValue;





struct IntPair;




union NavigationPackedFlags;
typedef union NavigationPackedFlags NavigationPackedFlags;

union NavigationPackedFlags;
union NavigationPackedFlags {
    u32 v0;
    u16 v1;
};

struct NavigationNodeFlagsView;
struct NavigationNodeFlagsView {
    char pad0[0xC];
    NavigationPackedFlags flags;
};




extern float g_portalResetSearchValue;








extern float g_portalNodeInitialValue;






#include "Common/aiprofile.h"



#include "Common/rec.h"
typedef struct NavigationPlatform {
    u8 pad0[8];
    CVector3 pos;
    u8 pad14[4];
    struct ActorMotionResource *resource;
    u8 pad1C[0xC8];
    u16 objectId;
    u8 padE6[0x8A];
    ActorMotionState motion;
    u8 pad2E0[8];
} NavigationPlatform;
typedef struct PlatformRoute { s16 reserved; s16 count; } PlatformRoute;
#endif
