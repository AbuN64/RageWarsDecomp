#ifndef ENGINE_CACHE_MUTEX_H
#define ENGINE_CACHE_MUTEX_H
#include "types.h"
struct MenuRules {
    char pad0[0x18];
    void *message; /* osCreateMesgQueue single-message backing store */
    s32 locked;
};
typedef struct MenuRules MenuRules;
void Mutex_InitializeQueueLock(struct MenuRules *menuRules);
#endif
