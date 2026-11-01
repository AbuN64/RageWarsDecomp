#include "include_asm.h"
#include "COMMON/OWNERRECAT8V2.H"
#include "ANIM/COLLISION_EMPTYEUXHOOK.H"

/* COLLISION_EMPTYUSHOOK.CPP */
/* 8023A284_30.CPP */

/* 8023CFB0.CPP */
#if defined(VERSION_US)
void Collision_EmptyUsHook(void) {}
#endif

/* 8023CFB0_2.CPP */
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void Collision_EmptyEuXHook(void) { }
#endif

/* 8023CFB0_4.CPP */
#if defined(VERSION_EU)
/** Perform no operation. */
void Collision_EmptyEuHook(void) {
}
#endif
