#ifndef COMMON_WORLD_SCENE_H
#define COMMON_WORLD_SCENE_H
#include "Common/world.h"
struct Shared_World;
struct Player;
struct ObjB;
#ifndef WORLD_SCENE_LIST_AND_LOOKUP_DECLARATIONS_H
#define WORLD_SCENE_LIST_AND_LOOKUP_DECLARATIONS_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"




extern void Scene_ClearActorLinksById(struct Shared_World *scene, s32 linkId);








extern struct LevelActor *Scene_ResolveActorLinkGroup(struct Shared_World *obj, int id);




extern s32 Scene_TestLevelRecordStateBit(void *world, struct ObjB *levelBitRecord);


struct Shared_World;





extern int g_vertexLightingMode;







struct LevelActor;
extern struct LevelActor *Scene_FindNearestMatchingActor(struct Shared_World *world, struct LevelActor *self, s32 team, s32 kind, s32 activeOnly);

extern struct LevelActor *Scene_FindTypeFourteenActorByDefinitionId(struct Shared_World *world, s32 id);





extern struct LevelActor *Scene_FindNearestListedEntry(struct Shared_World *owner, struct LevelActor *pos);





extern struct LevelActor *Scene_FindSwitchByDefinitionId(struct Shared_World *world, s32 id);












extern s32 Scene_GetTriggerCounterById(struct Shared_World *counterOwner, s32 counterId);








extern struct Player *Scene_FindNearestObjectToFirstPlayer(struct Shared_World *world);














#endif
#endif
