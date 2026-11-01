#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const float g_actorMotionResetUnitConstants[2] = {
    1.0f, 0.8f,
};
#endif





#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/GameObject_ResetActorMotionConstantsUsRev1.c */
const float g_GameObject_ResetActorMotionConstantsUsRev1[1] = {
    1.0f,
};

/* ROM-grounded data: src/Gobjinst_HasClearPathToActorConstantsUsRev1.c */
const float g_Gobjinst_HasClearPathToActorConstantsUsRev1[1] = {
    0.8f,
};
#endif
