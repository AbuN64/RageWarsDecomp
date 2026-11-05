#ifndef COMMON_TILE_GRID_BYTES_H
#define COMMON_TILE_GRID_BYTES_H

/* Byte sizes of one tile image of the given number of texels, and the step from one tile image to the next. */

/* A 4-bit-per-texel image (intensity or mask). */
#define TILE_BYTES_4BPP(texels) ((texels) >> 1)

/* A 16-bit colour image followed by a 4-bit-per-texel image of the same size. */
#define TILE_BYTES_16BPP_PLUS_4BPP(texels) ((texels) * 2 + ((texels) >> 1))

/* Moves the tile pointer past an image of the given byte size, keeping the pointer type. */
#define TILE_GRID_ADVANCE(type, tile, bytes) ((tile) = (type)((char *)(tile) + (bytes)))

#endif
