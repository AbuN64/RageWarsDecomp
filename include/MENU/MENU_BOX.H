#ifndef MENU_MENU_BOX_H
#define MENU_MENU_BOX_H
#include "TYPES.H"
/* One corner of the unit box a menu frame is drawn from: x/y/z offsets and an RGB colour. */
typedef struct MenuBoxCorner {
    s32 x, y, z;
    s32 red, green, blue;
} MenuBoxCorner;
/* The eight corners (front face z 0, back face z -2) Menu_InitializeMenu copies into both vertex
   banks of a new menu. */
extern MenuBoxCorner g_menuBoxCorners[8];
#endif
