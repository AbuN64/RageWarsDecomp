

/* g_OvlgameInitializecontrollersessionEncodedBytes_OvlgameInitializecontrollersessionData.CPP */
/* ROM-grounded data: rodata/unresolved/800D0E51 */
unsigned char g_OvlgameInitializecontrollersessionEncodedBytes[1] = {
    0x00,
};

/* g_OvlgameInitializecontrollersessionHalfwordAndWords.CPP */
/* ROM-grounded data: rodata/writable/800D0E52 */
#ifdef VERSION_DE
/* A halfword, then seven words read as words (lw) at 0x800D0E54; packed because the words start 2 bytes in. */
struct {
    unsigned short h0;
    unsigned int w1[7];
} __attribute__((packed)) D_blob_phase2_92fa79f50dd8dc42e292 = {
    0x0000,
    {
        0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000001,
        0x0000F000, 0x0001E800, 0x0001CC00,
    },
};
#endif
#ifdef VERSION_EU
/* A halfword, then seven words read as words (lw) at 0x800D0E54; packed because the words start 2 bytes in. */
struct {
    unsigned short h0;
    unsigned int w1[7];
} __attribute__((packed)) D_blob_phase2_92fa79f50dd8dc42e292 = {
    0x0000,
    {
        0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000001,
        0x4C455552, 0x20434F4D, 0x50524548,
    },
};
#endif
#ifdef VERSION_EU_X
/* A halfword, then seven words read as words (lw) at 0x800D0E54; packed because the words start 2 bytes in. */
struct {
    unsigned short h0;
    unsigned int w1[7];
} __attribute__((packed)) D_blob_phase2_92fa79f50dd8dc42e292 = {
    0x0000,
    {
        0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000001,
        0x3F835A18, 0x3F8334A1, 0x3F830F24,
    },
};
#endif
#ifdef VERSION_US
/* A halfword, then seven words read as words (lw) at 0x800D0E54; packed because the words start 2 bytes in. */
struct {
    unsigned short h0;
    unsigned int w1[7];
} __attribute__((packed)) D_blob_phase2_92fa79f50dd8dc42e292 = {
    0x0000,
    {
        0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000001,
        0x45425241, 0x4C5F424F, 0x52455F42,
    },
};
#endif
#ifdef VERSION_US_REV1
/* A halfword, then seven words read as words (lw) at 0x800D0E54; packed because the words start 2 bytes in. */
struct {
    unsigned short h0;
    unsigned int w1[7];
} __attribute__((packed)) D_blob_phase2_92fa79f50dd8dc42e292 = {
    0x0000,
    {
        0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000001,
        0x3F83EFAF, 0x3F83CA53, 0x3F83A4F0,
    },
};
#endif
