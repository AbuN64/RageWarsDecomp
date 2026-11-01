#ifndef SYSTEM_CONTACT_EFFECT_H
#define SYSTEM_CONTACT_EFFECT_H
#include "TYPES.H"
#include "COMMON/BOX_CONTACT.H"
/* Contact effect table indexed by effect id: the handler and its delivery flags (0x10 delivers outside scene
 * mode 4; particle impacts also test 1, 2 and 4). The flags word was read as g_animationEventEffectDescriptors. */
typedef void (*ContactEffectHandler)(void *, void *, s32, CVector3, ContactEffectStyle);
typedef struct ContactEffectEntry {
    ContactEffectHandler handler;
    u32 flags;
} ContactEffectEntry;
extern ContactEffectEntry g_effectCallbackFlags[];
#endif
