

#if defined(VERSION_US)
unsigned int k_FrontendEncodedWordsBlock1[3] = {
    0x656F7352, 0x00000000, 0x00000F00,
};
#endif

#if defined(VERSION_EU_X)
unsigned int g_FrontendEncodedWordsBlock10[3] = {
    0x00000018, 0x00000019, 0x0000001C,
};
#endif

#if defined(VERSION_US_REV1)
unsigned int g_FrontendEncodedWordsBlock3[3] = {
    0x00000002, 0x00000003, 0x00000008,
};
#endif

#if defined(VERSION_EU)
const unsigned int k_FrontendEncodedWordsBlock5[3] = {
    0x0800FFCA, 0x008B008C, 0x0800FFC6,
};
#endif
