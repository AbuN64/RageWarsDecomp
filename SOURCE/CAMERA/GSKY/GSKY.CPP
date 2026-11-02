#include "TYPES.H"

/* Lens flare tables read by Sky_DrawLensFlare (FlareAlphas / FlareColors in COMMON/LENS_FLARE.H). */
s32 k_lensFlareAlphas[7] = {
    24, 24, 24, 24, 24, 24, 24,
};

/* seven R,G,B triples */
s32 k_lensFlareColors[21] = {
    255, 150, 150,
    255, 255, 150,
    150, 255, 150,
    150, 255, 255,
    150, 150, 255,
    200, 150, 255,
    255, 150, 255,
};
