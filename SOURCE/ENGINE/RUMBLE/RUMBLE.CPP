#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/PACKEDMESHMATERIAL.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLD.H"
#include "COMMON/S1.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "ENGINE/RUMBLE.H"
#include "TYPES.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "ENGINE/RUMBLE.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "RENDER/CONTROL_CYCLEACTORSNAPSHOTMODE.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/SCENE_DRAWTRANSITIONCOLOROVERLAY.H"

static inline f32 distanceToNode(RumbleSpatialEffectNode *node, CVector3 from) {
    f32 x = from.x - node->position.x;
    f32 y = from.y - node->position.y;
    f32 z = from.z - node->position.z;
    return Gu_Sqrtf(x * x + y * y + z * z);
}
/* Sums the strength of every source in the pool at the given position (inverse-distance falloff scaled by each
 * source's two curves), clamped to 0..1; the pool is read with interrupts disabled. */
f32 Rumble_GetSpatialEffectLevel(RumbleSpatialPoolView *pool, CVector3 position) {
    f32 value = pool->baseLevel;
    s32 mask = __osDisableInt();
    RumbleSpatialEffectNode *node;
    f32 distance, amount, first, second, limit;
    if (g_gameSettings.counters.transitionActive == 1 || Cinema_IsSequenceInWindow() != 0) {
        value = 0.0f;
    } else {
        node = pool->activeEffects.head;
        while (node != 0) {
            distance = distanceToNode(node, position);
            if (distance == 0.0f || node->radius == 0.0f) {
                amount = 1.0f;
            } else if (distance < node->radius) {
                amount = 1.0f - distance / node->radius;
            } else {
                amount = 0.0f;
            }
            amount *= node->strength;
            first = Control_SampleEffectCurve(&node->amplitudeCurve);
            second = Control_SampleEffectCurve(&node->lifetimeCurve);
            value += amount * first * second;
            node = node->next;
        }
    }
    __osRestoreInt(mask);
    limit = 1.0f;
    if (!(limit < value) && value < 0.0f) {
        return 0.0f;
    }
    return limit < value ? limit : value;
}

#include "RENDER/CONTROL_CYCLEACTORSNAPSHOTMODE.H"
#include "ENGINE/SCENE_DRAWTRANSITIONCOLOROVERLAY.H"

/* With interrupts masked, takes the first node of a pool's free list, moves it onto the pool's active list and initialises it with its key, position, two values and owner slot (storing the node there), then binds the two handles named by the key's identifiers, returning the node or null. */

static inline void bind(RumbleEffectNode *node, s32 offset, s32 id) {

    Control_InitializeCurvePlayer((char *)node + offset, Scene_GetEffectCurveRecord(&g_world, id));
}

static inline void init(RumbleEffectNode *node, Clip *key, CVector3 position, f32 value0, f32 value1, RumbleEffectNode **owner) {
    node->key = key;
    node->position = position;
    node->value0 = value0;
    node->value1 = value1;
    node->owner = owner;
    if (owner != 0) {
        *owner = node;
    }
    bind(node, 32, key->mode);
    bind(node, 44, key->frames);
}

static inline IntrusiveList *active_list(RumbleNodePoolView *pool) {
    return &pool->active;
}

void Rumble_InitEffectNode(RumbleEffectNode *effectNode, Clip *effectClip, CVector3 effectPosition,
                   f32 valueStart, f32 valueEnd, void **ownerSlot) {

    effectNode->key = effectClip;
    effectNode->position = effectPosition;
    effectNode->value0 = valueStart;
    effectNode->value1 = valueEnd;
    effectNode->owner = ownerSlot;
    if (ownerSlot != 0) {
        *ownerSlot = effectNode;
    }
    Control_InitializeCurvePlayer(&effectNode->amplitudeHandle,
                  (unsigned int)Scene_GetEffectCurveRecord(&g_world, effectClip->mode));
    Control_InitializeCurvePlayer(&effectNode->lifetimeHandle,
                  (unsigned int)Scene_GetEffectCurveRecord(&g_world, effectClip->frames));
}

/** Clear the target word when the pointer field is populated. */
void Rumble_ClearEffectOwnerSlot(char *object) {
    struct RumbleEffectNode *node = (void *)object;
    struct RumbleEffectNode **target = node->owner;
    if (target != 0) {
        *target = 0;
    }
}

/** Store the supplied word at object offset 0x38. */
void Rumble_SetEffectOwnerSlot(void *effectNode, int ownerSlotAddress) {
    ActorFlagsWordView *record = effectNode;
    record->flags = ownerSlotAddress;
}

s32 Rumble_TestEffectHandleCompletion(RumbleEffectNode *effectNode) {
    s32 result;

    result = 0;
    if (Control_AdvanceEffectCurve(&effectNode->amplitudeHandle) != 0) {
        result = 1;
    } else if (Control_AdvanceEffectCurve(&effectNode->lifetimeHandle) != 0) {
        result = 1;
    }
    return result;
}

f32 Rumble_EvaluateSpatialEffectNode(f32 *effectNode, u32 positionXBits, u32 positionYBits, u32 positionZBits) {
    f32 magnitude;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 limit;
    f32 factor;
    f32 first;

    dx = *(f32 *)&positionXBits - effectNode[3];
    dy = *(f32 *)&positionYBits - effectNode[4];
    dz = *(f32 *)&positionZBits - effectNode[5];
    magnitude = Gu_Sqrtf((dx * dx) + (dy * dy) + (dz * dz));
    if ((magnitude == 0.0f) || ((limit = effectNode[6]) == 0.0f)) {
        factor = g_spatialEffectCenterGain;
    } else {
        factor = 0.0f;
        if (magnitude < limit) {
            factor = g_spatialEffectFalloffUnitGain - (magnitude / limit);
        }
    }
    factor *= effectNode[7];
    first = Control_SampleEffectCurve(&effectNode[8]);
    return factor * first * Control_SampleEffectCurve(&effectNode[11]);
}

void Rumble_InitPoolNodes(void *effectPool, void *nodeStorage, s32 nodeCount) {

    s32 i;
    RumbleEffectNode *p;
    u32 saved;

    p = nodeStorage;
    saved = __osDisableInt();
    List_InitializeIntrusive(effectPool, 0, 4);
    List_InitializeIntrusive(&((RumbleNodePoolView *)effectPool)->active, 0, 4);
    i = 0;
    if (nodeCount > 0) {
        do {
            List_AppendIntrusive(effectPool, p);
            i += 1;
            p++;
        } while (i < nodeCount);
    }
    ((RumbleNodePoolView *)effectPool)->baseLevel = 0;
    __osRestoreInt(saved);
}

RumbleEffectNode *Rumble_AllocatePoolNode(RumbleNodePoolView *pool, Clip *key, CVector3 position, f32 value0, f32 value1, RumbleEffectNode **owner) {

    s32 mask;
    RumbleEffectNode *node;

    mask = __osDisableInt();
    node = pool->free.head;
    if (node != 0) {
        List_RemoveIntrusive(&pool->free, node);
        List_AppendIntrusive(&pool->active, node);
        init(node, key, position, value0, value1, owner);
    }
    __osRestoreInt(mask);
    return node;
}

void Rumble_RecycleFinishedEffectNodes(void *pool) {

    RumbleEffectNode *node;
    RumbleEffectNode *next;
    s32 flag;
    u32 saved;
    RumbleEffectNode **inner;

    saved = __osDisableInt();
    for (node = (*active_list(pool)).head; node != 0; node = next) {
        next = node->next;
        flag = 0;
        if (Control_AdvanceEffectCurve(&node->amplitudeHandle) != 0 || Control_AdvanceEffectCurve(&node->lifetimeHandle) != 0) {
            flag = 1;
        }
        if (flag == 0) {
            continue;
        }
        inner = node->owner;
        if (inner != 0) {
            *inner = 0;
        }
        List_RemoveIntrusive(&(*active_list(pool)), node);
        List_AppendIntrusive(pool, node);
    }
    __osRestoreInt(saved);
}

void Rumble_FreeAllPoolNodes(void *effectPool) {

    void *node;
    void *next;
    s32 saved;

    saved = __osDisableInt();
    node = ((RumbleNodePoolView *)effectPool)->active.head;
    if (node != 0) {
        do {
            next = ((RumbleEffectNode *)node)->next;
            List_RemoveIntrusive(&((RumbleNodePoolView *)effectPool)->active, node);
            List_AppendIntrusive(effectPool, node);
            node = next;
        } while (node != 0);
    }
    ((RumbleNodePoolView *)effectPool)->baseLevel = 0;
    __osRestoreInt(saved);
}


/* ROM-grounded data: src/g_rumble_EvaluateSpatialEffectNodeConstantWords_Rumble.c */
const float g_rumble_EvaluateSpatialEffectNodeConstantWords[2] = {
    1.0f, 1.0f,
};




#if defined(VERSION_DE)
char s_RumbleNeConstrucText[12] =
    "ne__Construc";
#endif
