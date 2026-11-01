#ifndef RENDER_SHARED_REACTIONINTERACTION_H
#define RENDER_SHARED_REACTIONINTERACTION_H
#include "TYPES.H"
struct Shared_ReactionInteraction {
    void* sourceObject;
    s32 damage;
    f32 magnitude;
    s32 damageFlags;
    s32 shield;
};
#endif
