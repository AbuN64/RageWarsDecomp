/* Open declarations of audio-driver callback contracts, MIT.
 * These signatures describe callers of the reconstructed Acmd builders;
 * no driver structure definitions or Nintendo SDK header text are included. */
#ifndef COMMON_AUDIO_CALLBACKS_H
#define COMMON_AUDIO_CALLBACKS_H
#include <PR/abi.h>
typedef Acmd *(*ALCmdHandler)(void *, short *, int, int, Acmd *);
typedef int (*ALSetParam)(void *, int, void *);
#endif
