#ifndef PARTICLE_PARTICLE_UPDATESYSTEM_H
#define PARTICLE_PARTICLE_UPDATESYSTEM_H
struct DraftWorld827C8;
void Particle_ReleaseOwnerEmitters(struct DraftWorld827C8 *world, s32 owner);
struct ActorWorld;
void Particle_RetireOwnedActors(struct ActorWorld *world, void *owner);
#endif
