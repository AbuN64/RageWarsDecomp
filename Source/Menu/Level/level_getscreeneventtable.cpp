

#if defined(VERSION_US_REV1)
/* Three words just before the encoded cheat code text. */
extern unsigned int g_encodedCheatTextHeaderWords[3];

/* Encoded cheat codes g_menuCheatCodeData reads, NUL-separated, in ROM order; each row
   was its own symbol before (bytes 0x00, 0x2C, 0x4C, 0x78). */
char g_encodedCheatCodeText[168] =
    "J@LFWRIILLXMYAY@B]V\000BDUBV@IED@\\BCCG\\QEZRZQ"
    "FSMLPVRUAYO\000LHEKPVIR\\\000\000\000A@JDKJ"
    "HDGFV@UM]HD\000WICWWDRBP]_YI@O_\000\000\000\000IFMWEG@F"
    "PHRPUPCFC\000\000\000SUMNT@K\000HNNBWQODCKER\000\000\000\000UCGQJJICDL";
#endif

#if defined(VERSION_US_REV1)
unsigned int g_LevelGetscreeneventtableWords[3] = {
    0x0000001D, 0x00000001, 0x00000008,
};

extern char g_residentTextStorageA[44];
#endif

#if defined(VERSION_US_REV1)
extern char g_residentTextFragmentA[32];

extern char g_residentTextStorageB[44];
#endif

#if defined(VERSION_US_REV1)
extern char g_residentTextFragmentB[48];
#endif

/* Retained data for this translation unit. */
#if defined(VERSION_US_REV1)
unsigned int g_encodedCheatTextHeaderWords[3] = {
    0x0000001D, 0x00000001, 0x00000008,
};
#endif
#if defined(VERSION_US_REV1)
char g_residentTextStorageA[44] = "J@LFWRIILLXMYAY@B]V\000BDUBV@IED@\\BCCG\\QEZRZQ";
#endif
#if defined(VERSION_US_REV1)
char g_residentTextFragmentA[32] = "FSMLPVRUAYO\000LHEKPVIR\\\000\000\000A@JDKJ";
#endif
#if defined(VERSION_US_REV1)
char g_residentTextStorageB[44] = "HDGFV@UM]HD\000WICWWDRBP]_YI@O_\000\000\000\000IFMWEG@F";
#endif
#if defined(VERSION_US_REV1)
char g_residentTextFragmentB[48] = "PHRPUPCFC\000\000\000SUMNT@K\000HNNBWQODCKER\000\000\000\000UCGQJJICDL";
#endif
