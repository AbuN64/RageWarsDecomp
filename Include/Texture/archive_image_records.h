#ifndef TEXTURE_ARCHIVE_IMAGE_RECORDS_H
#define TEXTURE_ARCHIVE_IMAGE_RECORDS_H
#include "types.h"

struct ArchiveTextureDataEntryView {
    s32 unused;
    s32 flags;
    char rest[20];
};

struct ImageHeader {
    char pad0[2];
    unsigned char widthShift;
    unsigned char heightShift;
    char pad4[0x1D - 4];
    unsigned char scale;
    char pad1E[0x21 - 0x1E];
    unsigned char width;
    unsigned char height;
    unsigned char format;
    char data[1];
};

#endif
