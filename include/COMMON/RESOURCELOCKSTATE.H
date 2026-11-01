#ifndef COMMON_RESOURCELOCKSTATE_H
#define COMMON_RESOURCELOCKSTATE_H
#include "TYPES.H"
/* The resource API retains an unused arena selector. */
void Cache_DrainAndCompactResources(s32 unusedHeap);
#include "COMMON/ITEMRECAT20V1.H"
extern int Cache_QueryResourceEntryCount(void);


extern int Cache_ReadResourceEntryCount(void);


extern int Cache_GetPendingRequestCount(void);




extern int g_resourceEntryCount;

struct ResourceNodePair;
typedef struct ResourceNodePair ResourceNodePair;

extern int g_resourcePendingRequestCount;

struct ResourceNodePair;

extern int Cache_GetResourceEntryCount(void);



#endif
