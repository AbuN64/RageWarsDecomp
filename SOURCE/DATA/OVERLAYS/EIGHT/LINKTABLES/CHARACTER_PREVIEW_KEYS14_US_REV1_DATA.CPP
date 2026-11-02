#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E3A7F_remaining_E4680_unclaimed_E4C5C_unclaimed_E4C6C */
extern char g_characterPreviewTextReferenceShared4[];
void *g_CharacterPreviewKeys14UsRev1EncodedWords[1] = {
    g_characterPreviewTextReferenceShared4,
};

/* ROM-grounded data: src/ragewars_character_preview_keys_14_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 modelResource;
    s32 animation;
} g_characterPreviewKeys14UsRev1 __attribute__((aligned(4))) = {
    128,
    14
};
#endif
#endif
