#ifndef ENGINE_GDYNLIGHT_H
#define ENGINE_GDYNLIGHT_H
struct RangeNode;
struct CVector3_t;
void Gdynlight_AccumulateLightDirections(struct RangeNode **lightList, struct CVector3_t position, struct CVector3_t *left, f32 *remainingIntensity);
void *Gdynlight_AllocateLightNode(void *intrusiveList, void *radiusDescriptor);
void *Gdynlight_AllocateWorldLight(s32 intrusiveList, s32 index);
int Gdynlight_GetFirstLight(void *intrusiveList);
int Gdynlight_GetNextLight(void *unused0, void *rangeNode);
#endif
