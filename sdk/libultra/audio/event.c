#include "../../include/libgultra.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "../../include/BUF16B.H"
#include "../../include/libgultra/alunlink.h"
#include "include_asm.h"


                  /* osSetIntMask */


            /* alUnlink */


void alEvtqNew(ALEventQueue *eventQueue, ALEventListItem *eventStorage, s32 eventCapacity) {
    ALEventQueue *queue = eventQueue;
    s32 i;
    char *p;

    i = 0;
    queue->eventCount = 0;
    queue->allocList.next = 0;
    queue->allocList.prev = 0;
    queue->freeList.next = 0;
    queue->freeList.prev = 0;
    if (eventCapacity > 0) {
        p = (char *)eventStorage;
        do {
            alLink(p, eventQueue);
            i += 1;
            p += 0x1C;
        } while (i < eventCapacity);
    }
}

ALMicroTime alEvtqNextEvent(ALEventQueue *eventQueue, ALEvent *outputEvent) {
    void *node;
    s32 saved;
    s32 result;

    saved = osSetIntMask(1);
    node = ((ALEventQueue *)eventQueue)->allocList.next;
    if (node != 0) {
        alUnlink(node);
        ((void (*)(void *, void *, s32))alCopy)(&((ALEventListItem *)node)->evt, outputEvent, 0x10);
        alLink(node, eventQueue);
        result = ((ALEventListItem *)node)->delta;
    } else {
        outputEvent->type = -1;
        result = 0;
    }
    osSetIntMask(saved);
    return result;
}

  /* alLink */
 /* alCopy */

void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, s32 delta)
{
    ALEventListItem *item;
    ALEventListItem *nextItem;
    ListLink *node;
    s32 postAtEnd = 0;
    s32 mask;

    mask = osSetIntMask(1);

    item = (ALEventListItem *)evtq->freeList.next;
    if (!item) {
        osSetIntMask(mask);
        return;
    }

    alUnlink((ListLink *)item);
    ((void (*)(void *, void *, s32))alCopy)(evt, &item->evt, sizeof(*evt));

    if (delta == 0x7FFFFFFF)
        postAtEnd = -1;

    for (node = &evtq->allocList; node != 0; node = node->next) {
        if (!node->next) {
            if (postAtEnd)
                item->delta = 0;
            else
                item->delta = delta;
            alLink((ListLink *)item, node);
            break;
        } else {
            nextItem = (ALEventListItem *)node->next;

            if (delta < nextItem->delta) {
                item->delta = delta;
                nextItem->delta -= delta;

                alLink((ListLink *)item, node);
                break;
            }

            delta -= nextItem->delta;
        }
    }

    osSetIntMask(mask);
}

void alEvtqFlush(ALEventQueue *previousNode) {
    ALEventQueue *queue = previousNode;
    NodeGskyActivateMessagePool *cur;
    NodeGskyActivateMessagePool *next;
    s32 saved;

    saved = osSetIntMask(1);
    cur = queue->allocList.next;
    if (cur != 0) {
        do {
            next = cur->next;
            alUnlink((ListLink *)cur);
            alLink(cur, previousNode);
            cur = next;
        } while (cur != 0);
    }
    osSetIntMask(saved);
}


void alEvtqFlushType(ALEventQueue *previousNode, s16 eventType) {
    s32 saved;
    char *cur;
    char *next;

    saved = osSetIntMask(1);
    cur = ((ALEventQueue *)previousNode)->allocList.next;
    if (cur != 0) {
        do {
            next = ((ALEventListItem *)cur)->node.next;
            if (((ALEventListItem *)cur)->evt.type == eventType) {
                if (next != 0) {
                    ((ALEventListItem *)next)->delta = ((ALEventListItem *)next)->delta + ((ALEventListItem *)cur)->delta;
                }
                alUnlink((ListLink *)cur);
                alLink(cur, previousNode);
            }
            cur = next;
        } while (cur != 0);
    }
    osSetIntMask(saved);
}

