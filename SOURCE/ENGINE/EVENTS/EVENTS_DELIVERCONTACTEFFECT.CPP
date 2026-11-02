#include "COMMON/VECTOR4F.H"
#include "include_asm.h"

#include "TYPES.H"
#include "COMMON/BOX_CONTACT.H"
#include "COMMON/WORLD.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "SYSTEM/CONTACT_EFFECT.H"
typedef struct ContactNode ContactNode;
struct ContactNode {
    u8 pad0[0x16E0];
    ContactNode *next; /* 0x16E0 */
};
extern ContactNode *g_transientPlayerList;
static inline void dispatchEffect(void *object, void *source, s32 effect, CVector3 position, ContactEffectStyle style) {
    if (g_effectCallbackFlags[effect].handler != 0) {
        g_effectCallbackFlags[effect].handler(object, source, effect, position, style);
    }
}
/* Delivers a contact effect to objects: when the scene is in mode 4 or the effect's flags allow it, the effect's
 * handler (g_effectCallbackFlags table, flags in the second word: 2 = broadcast, 8 = scene object array) is called either
 * on the target alone or on every other object -- the scene's object array or its registered list
 * and then the player list chained at 0x16E0 -- skipping the target.
 * Byte-exact for us-rev1 (index-addressed actor loop). */
void Events_DeliverContactEffect(void *target, void *source, s32 effect, s32 unused, CVector3 position, ContactEffectStyle style) {
    s32 i;
    s32 count;
    LevelActor *actor;
    LevelActor *objects;
    void *other;
    ContactNode *node;
    Shared_World *world = &g_world;
    if (world->mode != 4 && (g_effectCallbackFlags[effect].flags & 0x10) == 0) {
        return;
    }
    if ((g_effectCallbackFlags[effect].flags & 2) == 0) {
        dispatchEffect(target, source, effect, position, style);
        return;
    }
    if ((g_effectCallbackFlags[effect].flags & 8) != 0) {
        count = world->actorCount;
        objects = world->actors;
        for (i = 0; i < count; i++) {
            other = &objects[i];
            if (other != target) {
                dispatchEffect(other, source, effect, position, style);
            }
        }
        for (node = g_transientPlayerList; node != 0; node = node->next) {
            if ((void *)node != target && (char *)&((SharedPlayer *)node)->views1C.view2E8_27.weapon != target) {
                dispatchEffect(node, source, effect, position, style);
            }
        }
    } else {
        count = world->registeredCount;
        for (i = 0; i < count; i++) {
            other = world->registered[i];
            if (other != target) {
                dispatchEffect(other, source, effect, position, style);
            }
        }
        node = g_transientPlayerList;
        while (node != 0) {
            if ((void *)node != target && (char *)&((SharedPlayer *)node)->views1C.view2E8_27.weapon != target) {
                dispatchEffect(node, source, effect, position, style);
            }
            node = node->next;
        }
    }
}
