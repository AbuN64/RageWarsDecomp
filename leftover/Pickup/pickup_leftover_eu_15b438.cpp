#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata pool. */
/* Words 0x801E7720..0x801E7C68 are runtime addresses of the older build's pickup pools, absent from every ROM. */
unsigned int g_pickupLeftover_eu_15B438[2] = { 0x226618, 0x226640 };
void *g_pickupLeftover_eu_15B440[1] = { (void *)0x801E7C68 };
#endif
