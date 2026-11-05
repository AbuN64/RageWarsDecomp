#ifndef AI_SPAWNAI_SYMBOLS_H
#define AI_SPAWNAI_SYMBOLS_H
struct IntrusiveList;
extern struct IntrusiveList g_spawnedActorList;
#include "types.h"
#include "Common/small_records.h"
/* Spawn choice tables placed by the symbol map; no C definition exists. */
extern SpawnChoice g_spawnChoices[];
#endif
