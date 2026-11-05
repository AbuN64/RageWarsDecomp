#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata pool. */
/* Words 0x801E7720..0x801E7C68 are runtime addresses of the older build's pickup pools, absent from every ROM. */
unsigned int g_pickupLeftover_eu_15AE68[2] = { 0x2237EC, 0x223870 };
void *g_pickupLeftover_eu_15AE70[1] = { (void *)0x801E7BC8 };
#endif
