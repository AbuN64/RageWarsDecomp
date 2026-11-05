#ifndef ENGINE_GDYNLIGHT_H
#define ENGINE_GDYNLIGHT_H
struct IntrusiveList;
struct RangeNode;
struct CVector3_t;
struct CGameDynamicLight_t;
void Gdynlight_AccumulateLightDirections(struct CGameDynamicLight_t *lightPool, CVector3 position,
                   CVector3 *left, f32 *remainingIntensity);
void *Gdynlight_AllocateLightNode(void *intrusiveList, void *radiusDescriptor);
void *Gdynlight_AllocateWorldLight(s32 intrusiveList, s32 index);
int Gdynlight_GetFirstLight(struct IntrusiveList *intrusiveList);
int Gdynlight_GetNextLight(void *lightPool, struct RangeNode *rangeNode);
#endif
