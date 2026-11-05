

#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_DE)
unsigned int k_navCheckcloseattackrouteFragment[2] = {
    0xAFBF0020, 0x0C0AC031,
};
#endif
#if defined(VERSION_US)
unsigned int k_navCheckcloseattackrouteFragment[2] = {
    0x00000000, 0x0E6D5F6E,
};
#endif
#endif

#if defined(VERSION_EU)
unsigned int g_NavCheckcloseattackrouteData[2] = {
    0x1420FFFD, 0x25080010,
};
#endif
