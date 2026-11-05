#if defined(VERSION_EU)
/* One row of g_pickupCodePointers: the pickup data's offsets into the older build's code, relocated at load.
   Nothing reads the row, so it has no symbol of its own; versions/eu/earlier_build_symbols.txt names the table. */
__asm__(".data\n\t.align 2\n\t.word 0x00237668\n");
#endif
