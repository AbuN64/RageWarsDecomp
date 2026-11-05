#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata pool. */
/* Words 0x801E7720..0x801E7C68 are runtime addresses of the older build's pickup pools, absent from every ROM. */
unsigned int g_pickupLeftover_eu_15AEB0[2] = { 0x224710, 0x224970 };
void *g_pickupLeftover_eu_15AEB8[1] = { (void *)0x801E7900 };
#endif
