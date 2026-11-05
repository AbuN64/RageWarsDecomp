#ifndef SYSTEM_CONTACT_EFFECT_H
#define SYSTEM_CONTACT_EFFECT_H
#include "types.h"
#include "Common/box_contact.h"
struct ContactEffectEntry;
/* Contact effect table indexed by effect id: the handler and its delivery flags (0x10 delivers outside scene
 * mode 4; particle impacts also test 1, 2 and 4). Animation event masks use this same flags word at +4. */
typedef void (*ContactEffectHandler)(void *, void *, s32, CVector3, ContactEffectStyle);
typedef struct ContactEffectEntry {
    ContactEffectHandler handler;
    u32 flags;
} ContactEffectEntry;
extern struct ContactEffectEntry g_effectCallbackFlags[];
#endif
