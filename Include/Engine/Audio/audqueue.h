#ifndef ENGINE_AUDIO_AUDQUEUE_H
#define ENGINE_AUDIO_AUDQUEUE_H
#include "Common/listnode.h"

struct ListNodeNextView;
extern void Audio_InsertChannelLink(void **previousLink, struct ListNodeNextView *link);
#endif
