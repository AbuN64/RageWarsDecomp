#ifndef COMMON_ALFXPARAM_H
#define COMMON_ALFXPARAM_H
#include "types.h"

#include "Common/osthread_s.h"
#include "Sirawread/sirawread.h"

#if defined(VERSION_US_REV1)
extern const unsigned char g_audioResamplerSourceText[];
#else
extern const char g_audioResamplerSourceText[];
#endif

extern int alFxParam(int *filter, int paramId, int param);


extern s32 g_audioAssertionConditionText;
extern s32 g_audioAssertionSourceText;

extern s32 g_peripheralReadAssertText;
extern const char s_pirawreadText[15];


extern s32 g_signalProcessorDmaAssertText;
extern const char s_sprawdmaText[14];
#endif
