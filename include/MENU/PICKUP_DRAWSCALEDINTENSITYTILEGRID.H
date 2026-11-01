#ifndef MENU_PICKUP_DRAWSCALEDINTENSITYTILEGRID_H
#define MENU_PICKUP_DRAWSCALEDINTENSITYTILEGRID_H
#include "COMMON/ENTRYRECATE.H"
extern void Pickup_DrawScaledIntensityTileGrid(u16 *grid, f32 x0, f32 y, f32 sx, f32 sy);
extern void Pickup_BuildByteLookup(int unused, unsigned char *pairs, int count, unsigned char *table);
extern void Pickup_SetupPickupText(void);
extern void Pickup_DrawIntensityTileGrid(u16 *grid, s16 x0, s32 y);
#endif
