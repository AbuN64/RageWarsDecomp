#if defined(VERSION_EU)
/* Older build's runtime pointers: the address cells point into the older build's rodata, which no ROM of this build holds. */
void *g_pickupLeftover_eu_15B8B8[1] = { (void *)0x80158BB4 };
#endif
