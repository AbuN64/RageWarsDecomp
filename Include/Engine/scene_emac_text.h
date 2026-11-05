#ifndef ENGINE_SCENE_EMAC_TEXT_H
#define ENGINE_SCENE_EMAC_TEXT_H
/* The scene owns the seven words of this folded table in each ROM. */
#if defined(VERSION_DE)
extern struct RestemacTextLayout324 g_emacText;
#elif defined(VERSION_EU)
extern unsigned short g_emacText[14];
#elif defined(VERSION_EU_X)
extern struct RestemacTextLayout325 g_emacText;
#elif defined(VERSION_US)
extern struct RestemacTextLayout326 g_emacText;
#elif defined(VERSION_US_REV1)
typedef struct SceneEmacRev1 {
    unsigned int w0;
    unsigned char b1[4];
    unsigned int w2;
    unsigned char b3[4];
    unsigned int w4;
    unsigned char b5[4];
    unsigned int w6;
} SceneEmacRev1;
extern SceneEmacRev1 g_emacText;
#endif
#endif
