#ifndef RENDER_MATERIAL_RECORDS_H
#define RENDER_MATERIAL_RECORDS_H
#include "types.h"

struct PackedMaterialHalfwordView {
    char pad0[0x2];
    u16 spreadHighWord;
};

typedef struct PackedMaterialHalfwordView PackedMaterialHalfwordView;

#endif
