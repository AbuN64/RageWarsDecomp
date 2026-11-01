#ifndef COMMON_S1_H
#define COMMON_S1_H
#include "TYPES.H"
/* Initializes an empty list whose nodes keep their links at the given offsets. */
extern void List_InitializeIntrusive(IntrusiveList *list, s32 prevOffset, s32 nextOffset);

/* Appends node at the tail and returns the new count. */
extern s32 List_AppendIntrusive(IntrusiveList *list, void *node);

struct HeapArena_Entryrecat18v3;












#endif
