
/* ROM-grounded data: rodata/writable/800CD394 */
#ifdef VERSION_DE
unsigned int g_LibsnInitializepollinghostDataEncodedWords[11] = {
    0x00000000, 0x00000000, 0x00006000, 0x0001E000, 0x0007E000, 0x001FE000, 0x007FE000, 0x01FFE000,
    0x80000000, 0x00000000, 0x00000000,
};
#endif
#ifdef VERSION_EU
unsigned int g_LibsnInitializepollinghostDataEncodedWords[11] = {
    0x00000000, 0x00000000, 0x00006000, 0x0001E000, 0x0007E000, 0x001FE000, 0x007FE000, 0x01FFE000,
    0x80000000, 0xBE19999A, 0x3F666666,
};
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
unsigned int g_LibsnInitializepollinghostDataEncodedWords[11] = {
    0x00000000, 0x00000000, 0x00006000, 0x0001E000, 0x0007E000, 0x001FE000, 0x007FE000, 0x01FFE000,
    0x80000000, 0x00020000, 0x00030000,
};
#endif
#ifdef VERSION_US
unsigned int g_LibsnInitializepollinghostDataEncodedWords[11] = {
    0x00000000, 0x00000000, 0x00006000, 0x0001E000, 0x0007E000, 0x001FE000, 0x007FE000, 0x01FFE000,
    0x80000000, 0x4249454E, 0x43455400,
};
#endif
