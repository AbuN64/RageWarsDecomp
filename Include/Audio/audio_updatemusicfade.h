#ifndef AUDIO_AUDIO_UPDATEMUSICFADE_H
#define AUDIO_AUDIO_UPDATEMUSICFADE_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Common/listnode.h"
#include "Common/resident_event_handler.h"
#include "Common/vector4f.h"
extern void Audio_UpdateMusicFade(void *queue);
struct AudioStateD844;
struct AudioRootD844;
void Audio_InitializeMusicPlayer(struct AudioStateD844 *state, struct AudioRootD844 *root);
#endif
