#ifndef COMMON_MODEL_INSTANCE_H
#define COMMON_MODEL_INSTANCE_H
#include "types.h"
struct ObjectSceneChangeInstanceModel {
    char pad0[4];
    s16 index;
    char pad6[0xDE];
    u16 id;
};
#endif
