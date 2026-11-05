#ifndef ENGINE_UNICOL_INSTCOL_INSTCOL_H
#define ENGINE_UNICOL_INSTCOL_INSTCOL_H
struct Query;
#include "Engine/Unicol/Polycol/polycol_tracemeshtriangle.h"
#include "Collide/ccollision_testsegmentdisk.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Common/world.h"
#include "Common/level_actor.h"
#include "Common/runtime_declarations.h"
#include "Common/motion_step.h"
#include "Common/rendersortrecord.h"
#include "types.h"
#include "Engine/Unicol/PLTFMCOL.h"
#include "Pickup/pickup_cancollect.h"
#include "Common/approachlocation.h"
struct ActorMotion;
struct LevelActor;
extern f32 InstHdr_GetActorBaseOffset(void *);
extern s32 CCollision_TestRayCylinder(void *, CVector3 *, f32, f32, f32, s32, void *, s32);
extern void Instcol_TestEntityContact(struct ActorMotion *, struct Query *, struct LevelActor *);
#endif
