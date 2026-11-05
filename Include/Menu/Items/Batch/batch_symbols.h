#ifndef MENU_ITEMS_BATCH_BATCH_SYMBOLS_H
#define MENU_ITEMS_BATCH_BATCH_SYMBOLS_H
#include "types.h"
typedef struct PoolVertex {
    s16 x;
    s16 y;
    s16 z;
    s16 flag;
    s16 s;
    s16 t;
    u8 color[4];
} PoolVertex;
extern PoolVertex g_particleSpriteVertices[4];
#endif
