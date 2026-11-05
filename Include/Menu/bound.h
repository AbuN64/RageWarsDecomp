#ifndef MENU_BOUND_H
#define MENU_BOUND_H
#include "types.h"
#include "Common/particle_lighting.h"
struct MenuBindingItemView {
    char pad[20];
    struct Binding *binding;
};
struct ObjectItemsDrawActorWithRedMenuEffect {
    char pad[0x140];
    Shared_ParticleLighting view[1];
};
extern void Bound_DrawActorWithMenuLighting(void *first, void *second, void *third);
extern void Bound_DrawActorWithRedMenuEffect(struct ObjectItemsDrawActorWithRedMenuEffect *object, void *context, void *lookup);
#endif
