#if defined(VERSION_EU)
/* Cells written as 0x80xxxxxx literals point into the older build; no ROM carries those bytes. */
/* Older build's runtime pointer table (flag words beside the pointers). */
void *g_pickupLeftover_eu_15FCC4[14] = { (void *)0x20000000, (void *)0x20000000, (void *)&g_ppdecomFlagLabelCu1, (void *)0x10000000, (void *)0x10000000, (void *)&g_ppdecomFlagLabelCu0, (void *)0x08000000, (void *)0x08000000, (void *)0x8014CF00, (void *)0x04000000, (void *)0x04000000, (void *)&g_ppdecomPoolTableFloatsTarget, (void *)0x02000000, (void *)0x02000000 };
#endif
