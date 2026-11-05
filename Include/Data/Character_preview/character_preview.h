#ifndef DATA_CHARACTER_PREVIEW_CHARACTER_PREVIEW_H
#define DATA_CHARACTER_PREVIEW_CHARACTER_PREVIEW_H
#include "types.h"

typedef struct CharacterPreviewProfile {
    const char *name;
    s32 resource;
    s32 character;
    s32 animation;
    float scaleDistance[8];
    float positions[12];
    s32 lightOffsets[4];
} CharacterPreviewProfile;

extern char g_characterNames[];
#if defined(VERSION_US_REV1)
extern CharacterPreviewProfile g_characterPreviewProfiles[12];
#endif
#endif
