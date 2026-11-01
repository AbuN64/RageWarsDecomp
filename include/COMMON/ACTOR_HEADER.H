#ifndef COMMON_ACTOR_HEADER_H
#define COMMON_ACTOR_HEADER_H
#include "TYPES.H"
/* Common actor header occupies player offsets 0 through 0x1B. */
struct ModelBlend;
struct EffectOwnerObject {
    char pad[0x18];
    struct ModelBlend *owner;
    u8 reserved1C[0x740 - 0x1C];
    u8 effect740;
};
#endif
