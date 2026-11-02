#if defined(VERSION_EU)
/* Older build's rodata : the pSearchEntry string, then its 3 pad bytes. */
char g_earlierListStrPsearchentryFla[16] = "pSearchEntry" "\0" "FLA";
#endif
