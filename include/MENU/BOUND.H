#ifndef MENU_BOUND_H
#define MENU_BOUND_H
#include "TYPES.H"
#include "COMMON/PARTICLE_LIGHTING.H"
struct MenuBindingItemView {
    char pad[20];
    struct Binding *binding;
};
struct ObjectItemsDrawActorWithRedMenuEffect {
    char pad[0x140];
    Shared_ParticleLighting view[1];
};
#endif
