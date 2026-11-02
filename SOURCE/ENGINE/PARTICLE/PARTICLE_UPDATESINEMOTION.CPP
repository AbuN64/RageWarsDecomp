#include "COMMON/TRIPLE.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"

/* Advance the two measured oscillator phases and apply their velocity deltas. */






extern void Graphu64_CrossVectors(CVector3 *, CVector3 *, CVector3 *);


void Particle_UpdateSineMotion(void *particle, f32 amplitudeScale) {
    CVector3 referenceAxis;
    CVector3 perpendicularAxis;
    Triple travelDirection;
    CVector3 previousSineOffset;
    CVector3 nextSineOffset;
    CVector3 sideAxis;
    f32 fadeInDuration;
    f32 nextSineAngleX;
    f32 nextSineAngleY;
    f32 particleAge;
    f32 motionAmplitude;
    s8 fadeInFrames;

    fadeInFrames = ((Shared_Particle *)particle)->desc->sineWave->fadeInFrames;
    motionAmplitude = g_particleSineMotionAmplitude;
    if (fadeInFrames != 0) {
        particleAge = ((Shared_Particle *)particle)->time;
        fadeInDuration = (f32) fadeInFrames;
        if (particleAge < fadeInDuration) {
            motionAmplitude = particleAge / fadeInDuration;
        }
    }
    motionAmplitude *= amplitudeScale;
    travelDirection = *(Triple *)&((Shared_Particle *)particle)->direction;
    if (((Shared_Particle *)particle)->sineAmplitudeX > 0.0f) {
        CVector3 *velocity;

        referenceAxis.x = 0.0f;
        referenceAxis.z = 0.0f;
        referenceAxis.y = g_particleSineMotionOffsetY;
        Graphu64_CrossVectors(&perpendicularAxis, &referenceAxis, (CVector3 *)&travelDirection);
        Graphu64_ScaleVector(&previousSineOffset, &perpendicularAxis, Gu_Sinf(((Shared_Particle *)particle)->sineAngleX) * ((Shared_Particle *)particle)->sineAmplitudeX * motionAmplitude);
        nextSineAngleX = ((Shared_Particle *)particle)->sineAngleX + (((Shared_Particle *)particle)->sineAngleSpeedX * motionAmplitude * g_frameElapsedTime);
        ((Shared_Particle *)particle)->sineAngleX = nextSineAngleX;
        Graphu64_ScaleVector(&nextSineOffset, &perpendicularAxis, Gu_Sinf(nextSineAngleX) * ((Shared_Particle *)particle)->sineAmplitudeX * motionAmplitude);
        velocity = &((Shared_Particle *)particle)->inst.velocity;
        Graphu64_SubtractVectors(velocity, velocity, &previousSineOffset);
        Graphu64_AddVec3((CVector3 *) velocity, (CVector3 *) velocity, (CVector3 *) &nextSineOffset);
    } else {
        ((Shared_Particle *)particle)->sineAngleX = (f32) (((Shared_Particle *)particle)->sineAngleX + (((Shared_Particle *)particle)->sineAngleSpeedX * motionAmplitude * g_frameElapsedTime));
    }
    if (((Shared_Particle *)particle)->sineAmplitudeY > 0.0f) {
        referenceAxis.x = 0.0f;
        referenceAxis.z = 0.0f;
        referenceAxis.y = g_particleSineMotionTargetY;
        Graphu64_CrossVectors(&sideAxis, &referenceAxis, (CVector3 *)&travelDirection);
        Graphu64_CrossVectors(&perpendicularAxis, &sideAxis, (CVector3 *)&travelDirection);
        Graphu64_ScaleVector(&previousSineOffset, &perpendicularAxis, Gu_Sinf(((Shared_Particle *)particle)->sineAngleY) * ((Shared_Particle *)particle)->sineAmplitudeY * motionAmplitude);
        nextSineAngleY = ((Shared_Particle *)particle)->sineAngleY + (((Shared_Particle *)particle)->sineAngleSpeedY * motionAmplitude * g_frameElapsedTime);
        ((Shared_Particle *)particle)->sineAngleY = nextSineAngleY;
        Graphu64_ScaleVector(&nextSineOffset, &perpendicularAxis, Gu_Sinf(nextSineAngleY) * ((Shared_Particle *)particle)->sineAmplitudeY * motionAmplitude);
        Graphu64_SubtractVectors(&((Shared_Particle *)particle)->inst.velocity, &((Shared_Particle *)particle)->inst.velocity, &previousSineOffset);
        Graphu64_AddVec3(&((Shared_Particle *)particle)->inst.velocity, &((Shared_Particle *)particle)->inst.velocity, &nextSineOffset);
        return;
    }
    ((Shared_Particle *)particle)->sineAngleY = (f32) (((Shared_Particle *)particle)->sineAngleY + (((Shared_Particle *)particle)->sineAngleSpeedY * motionAmplitude * g_frameElapsedTime));
}
