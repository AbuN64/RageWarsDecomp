#ifndef MENU_INITVIEW_H
#define MENU_INITVIEW_H
#include "TYPES.H"

typedef struct InitView { char pad0[4]; u32 flags; char pad8[0xF4]; f32 x, y, z; } InitView;

#endif
