

#if defined(VERSION_US)
struct {
    char text0[12];
    unsigned int words1[1];
} g_FrontendUpdatetimedscreenEncodedWords = {
    "RAX_VICTORY_",
    {
        0x3D888889,
    },
};
#endif

#if defined(VERSION_DE)
char g_FrontendUpdatetimedscreenEncodedWordsBlock_de_DEB04[12] =
    "%d\000\000%d%%\000\000\000";
#endif

#if defined(VERSION_US_REV1)
unsigned int g_FrontendUpdatetimedscreenEncodedWordsBlock_usrev1_E2B34[3] = {
    0x00000001, 0x00000004, 0x00000010,
};
#endif
