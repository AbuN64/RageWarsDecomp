#if defined(VERSION_DE)
/* 36 bytes of stale fill between the end of Nav_UpdatePatrolRoute and the 0x20-aligned Nav_UpdateObjectArrivalChase: the
   first five words read like a leaf function but start at a non-8-aligned address and nothing jumps, calls or points to
   them, the last four are loop debris from an earlier build; read by no instruction */
unsigned int g_navUpdateObjectArrivalChaseAlignPad[9] = {
    0x8C8201D8, 0x8C431454, 0x2402FFFF, 0xAC600220, 0x03E00008, 0xAC620224, 0x326500FF, 0x2610FFFF,
    0x1600FFF9,
};
#endif
