

/* s_bursteText_SBurstetext.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_resident_strings_D3568_us_rev1.c */
char s_bursteText[12] = "T BURSTE";
#endif

/* g_burstTextPackedStateWords_SBurstetext.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/writable/800D2950_unclaimed_D3574 */
/* A word (read as a word by its users) followed by three bytes; packed so the object stays 7 bytes. */
struct {
    unsigned int w0;
    unsigned char b1[3];
} __attribute__((packed)) g_burstTextPackedStateWords = {
    0x00000001,
    { 0x00, 0x00, 0x00 },
};
#endif
