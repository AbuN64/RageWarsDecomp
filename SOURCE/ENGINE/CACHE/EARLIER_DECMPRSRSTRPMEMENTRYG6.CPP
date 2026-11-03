#if defined(VERSION_EU)
/* Older build's rodata : the whole pMemEntry string (it was typed as a float over "Entr"), then its 2 pad bytes. */
char g_earlierDecmprsrStrPmementryG6[12] = "pMemEntry" "\0" "G6";
#endif
