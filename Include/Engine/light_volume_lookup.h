#ifndef ENGINE_LIGHT_VOLUME_LOOKUP_H
#define ENGINE_LIGHT_VOLUME_LOOKUP_H
#include "types.h"
struct LightVolumeConeDistanceLookup {
    float coneDistance[65];
    s32 enabled;
    s8 colorJitter[92];
    s32 state[2];
    void *actorDispatch[15];
    u32 tail[4];
};
extern struct LightVolumeConeDistanceLookup g_lightVolumeConeDistanceLookup;
#endif
