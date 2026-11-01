#ifndef ENGINE_CACHE_LIST_H
#define ENGINE_CACHE_LIST_H
#include "TYPES.H"
#include "COMMON/S1.H"

void List_PrependIntrusive(void *list, void *node);
extern IntrusiveList g_resourceAvailableRequests;

extern void List_InsertAfterIntrusive(void *list, s32 anchorNode, s32 insertedNode);
extern void List_DropIntrusiveTail(IntrusiveList *list);
extern void List_TraverseIntrusiveNodes(IntrusiveList *list);
extern void List_MoveIntrusiveToTail(void *list, s32 nodeToMove);
extern void List_RemoveIntrusive(void *list, void *node);
#endif
