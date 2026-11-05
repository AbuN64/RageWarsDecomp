#ifndef AI_PLAYERAI_UPDATEDELAYEDDAMAGE__PLAYER_H
#define AI_PLAYERAI_UPDATEDELAYEDDAMAGE__PLAYER_H
#include "types.h"
#include "Common/small_records.h"

struct Slot;
struct Slot {
    char data[24];
};
typedef struct Slot Slot;

#include "types.h"
extern void Playerai_UpdateDelayedDamage(void *);

#endif
