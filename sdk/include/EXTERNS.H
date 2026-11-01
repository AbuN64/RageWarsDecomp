#ifndef EXTERNS_H
#define EXTERNS_H
#include "TYPES.H"
extern s32 _Printf(void *(*)(void *, const char *, s32), void *, const char *, char *);
#include "COMMON/ALSEQUENCEPLAYER.H"
/* Divides an integer by a float and truncates toward zero, asserting first if the divisor is
   zero; clamps the result to 0x7FFFFFFF when the quotient would overflow a signed 32-bit int. */

#if defined(VERSION_US_REV1)
extern const f32 g_SndplayerWords1;
extern const char g_SndplayerBytes2[];
extern const char g_audioSndplayerSourceText[];
#else
extern const f32 g_SndplayerBytes1;
extern const char g_soundPlayerAssertText[];
extern const char s_audioSndplayerText[];
#endif
#endif
