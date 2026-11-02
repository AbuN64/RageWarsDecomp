#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E3A7F_remaining_E4680_unclaimed_E4CCC_unclaimed_E4CDC */
extern char g_characterPreviewTextReferenceShared5[];
void *g_CharacterPreviewKeys15UsRev1EncodedWords[1] = {
    g_characterPreviewTextReferenceShared5,
};

/* ROM-grounded data: src/ragewars_character_preview_keys_15_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 modelResource;
    s32 animation;
} g_characterPreviewKeys15UsRev1 __attribute__((aligned(4))) = {
    139,
    17
};
#endif
#endif
