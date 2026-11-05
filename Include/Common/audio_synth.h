#ifndef COMMON_AUDIO_SYNTH_H
#define COMMON_AUDIO_SYNTH_H
/* ALGlobals (COMMON/ALAUXBUS_S.H) owns its embedded synth driver.
 * 802B24A0 installs this address as the shared driver; storage spans 0x4C. */
extern ALGlobals g_audioSynthGlobals;
#endif
