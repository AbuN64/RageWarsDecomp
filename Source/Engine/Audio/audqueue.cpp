#include "Engine/lists.h"
#include "Common/runtime_declarations.h"
#include "Common/listnode.h"
#include "Engine/Audio/audqueue.h"

/* AUDQUEUE.CPP */

void Audio_InsertChannelLink(void **listHead, ListNodeNextView *channelLink) {
    *(void **)channelLink = *listHead;
    channelLink->value = listHead;
    ((ListNodeNextView *)((*listHead)))->value = channelLink;
    *listHead = channelLink;
}
