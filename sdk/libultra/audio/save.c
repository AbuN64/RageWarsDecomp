#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Common/alfxparam.h"
#include <PR/abi.h>
#include "Common/audio_callbacks.h"
#include "Common/alsequenceplayer.h"
#include "Common/audio_effect_chain.h"
#include "../../include/libultra/audio/save.H"
#include "types.h"
#include "../../include/libultra/debug/assert.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/alauxbus_s.h"

/* ALSAVEPULL.CPP */
/* 802B63E4_4.CPP */

/* save_3.c */
#if defined(VERSION_EU)
#include "Common/alfxparam.h"
#include <PR/abi.h>
#include "Common/audio_callbacks.h"
#include "Common/alsequenceplayer.h"
#include "Common/audio_effect_chain.h"
#include "libultra/audio/save.H"
#include "types.h"
#include "libultra/debug/assert.h"
#include "../../include/libultra/audio/save.h"
Acmd *alSavePull(ALSave_u1 *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    ALFilter_u1 *source = filter->filter.source;

    if (!source) {
        __assert(g_audioSaveAssertConditionText, g_audioSaveText, 0x22);
    }
    ptr = source->handler(source, outp, outCount, sampleOffset, ptr);
    aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
    aInterleave(ptr++, 0x440, 0x580);
    aSetBuffer(ptr++, 0, 0, 0, outCount << 2);
    aSaveBuffer(ptr++, filter->dramout);
    return ptr;
}
#endif

/* save.c */
/* 802B63E4_3.CPP */

/* save.c */
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1) || defined(VERSION_DE) || defined(VERSION_US)
Acmd *alSavePull(ALSave_u1 *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    ALFilter_u1 *source = filter->filter.source;

    if (!source) {
        __assert(g_audioSaveAssertConditionText, g_audioSaveText, 0x22);
    }
    ptr = source->handler(source, outp, outCount, sampleOffset, ptr);
    aSetBuffer(ptr++, 0, 0, 0, outCount << 1);
    aInterleave(ptr++, 0x440, 0x580);
    aSetBuffer(ptr++, 0, 0, 0, outCount << 2);
    aSaveBuffer(ptr++, filter->dramout);
    return ptr;
}
#endif

/* save_2.c */
s32 alSaveParam(ALSave *saveFilter, s32 parameterId, ALFilter_s14 *parameterValue)
{
  switch (parameterId)
  {
    case 1:
      saveFilter->filter.source = parameterValue;
      goto ret0;

    case 6:
      saveFilter->dramout = parameterValue;

    default:
      ret0:
    return 0;

      return 0;

  }

}

/* save_bytes.c */
#if !(defined(VERSION_US))
/* ROM-grounded data: src/g_saveAssertExpressionText.c */
const unsigned char g_saveAssertExpressionText[4] = {
    0x45, 0x58, 0x00, 0x00,
};
#endif

/* save_text.c */
#if !(defined(VERSION_US))
/* ROM-grounded data: src/audioSaveTextPoolEuXUsRev1.c */
const unsigned char g_audioSaveText[] = {
    0x61, 0x75, 0x64, 0x69, 0x6F, 0x2F, 0x73, 0x61, 0x76, 0x65, 0x2E, 0x63, 0x00,
#if defined(VERSION_DE)
    0xF0, 0x00, 0x00,
#endif
#if defined(VERSION_EU)
    0x00, 0x00, 0x00,
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
    0x00, 0x00, 0x01,
#endif
};
#endif
