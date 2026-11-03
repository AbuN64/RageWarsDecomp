#ifndef COMMON_LIBSN_AND_RESIDENT_CALLBACKS_H
#define COMMON_LIBSN_AND_RESIDENT_CALLBACKS_H
#include "TYPES.H"
#include "../../sdk/include/libultra/io/io.H"



extern void Turret_AdvanceRomEntry();
extern void Turret_DecreaseHealthRomEntry();
extern void Turret_CalcOrientMtxRomEntry();
extern void Turret_SpecialEffectsRomEntry();

extern void PitchMatrix(void *matrixStorage, f32 pitchAngle);
#endif
