#ifndef GOBJINST_GOBJINST_BUILDTARGETAIMORIENTATION_H
#define GOBJINST_GOBJINST_BUILDTARGETAIMORIENTATION_H
#include "types.h"
#include "Common/vector.h"
#include "Common/vector4f.h"
struct ActorDirectionTiltInput;
CQuatern Gobjinst_BuildActorDirectionTilt(struct ActorDirectionTiltInput *input);
CQuatern Gobjinst_BuildTargetAimOrientation(char *actor, CVector3 point);
#endif
