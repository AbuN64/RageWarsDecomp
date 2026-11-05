#ifndef PARTICLE_PARTICLE_UPDATETYPEDMOTION_H
#define PARTICLE_PARTICLE_UPDATETYPEDMOTION_H
#include "Common/ballisticparams.h"
struct SteeringParticle;
void Particle_SteerSoundTrackingParticle(void *);                      /* extern */
struct Shared_Particle;
void Particle_SteerHoming(struct Shared_Particle *particle);                      /* extern */
#endif
