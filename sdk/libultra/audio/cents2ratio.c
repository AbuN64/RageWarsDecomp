#include "include_asm.h"
#include "COMMON/VECTOR4F.H"
#include "../../include/BUF16B.H"
#include "TYPES.H"

/* ROM-grounded data: src/g_audio_CentsToPitchRatioConstantWords_Event.c */
const float g_audio_CentsToPitchRatioConstantWords[2] = {
    1.0f, 1.0005778f,
};

extern f32 g_centsToPitchRatioConstants[];

f32 alCents2Ratio(s32 cents)
{
  f32 result;
  f32 base;
  s32 n;
  int unitRatioIndex;
  unitRatioIndex = 0;
  result = g_centsToPitchRatioConstants[unitRatioIndex];
  base = g_centsToPitchRatioConstants[1];
  n = cents;
  if (n < 0)
  {
    base = (0.999422550201416f);
    n = -n;
  }
  if (n != 0)
  {
    do
    {
      if (n & 1)
      {
        result *= base;
      }
      n >>= 1;
      base *= base;
    }
    while (n != 0);
  }
  return result;
}


void alCSPPlay(ALCSPlayer *playerAddress) {
    s16 stopEvent[8];

    stopEvent[0] = 0xF;
    alEvtqPostEvent(&playerAddress->evtq, stopEvent, 0);
}


#if defined(VERSION_EU)
unsigned int k_EventEncodedWordsBlock1[1] = {
    0x43999999,
};
#endif

#if defined(VERSION_DE)
unsigned int k_EventEncodedWords[1] = {
    0x71706C61,
};
#endif
