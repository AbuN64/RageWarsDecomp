#include "include_asm.h"
#include "Common/virtual_pager.h"
#include "Anim/collision_emptyeuxhook.h"

/* ACCEPTS.CPP */

#if defined(VERSION_US)
void Collision_EmptyUsHook(void) {}
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void Collision_EmptyEuXHook(void) { }
#endif

#if defined(VERSION_EU)
/** Perform no operation. */
void Collision_EmptyEuHook(void) {
}
#endif
