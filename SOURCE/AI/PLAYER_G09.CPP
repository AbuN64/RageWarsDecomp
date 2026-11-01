#include "include_asm.h"
#include "TYPES.H"

/* PLAYER_LIGHT_AND_AMMO_CONSTANT_WORDS.CPP */
/* 800C768C.CPP */
const float g_playerEffectLightConstantWordsUsRev1[10] = {
    204.79999f, 0.5f, 1.0f, 614.39996f,
    0.5f, 1.0f, 7e+01f, 2e+01f,
    0.5f, 1.0f,
};

/* 800C76B4.CPP */
const float g_playerAmmoCounterConstantWordsUsRev1[14] = {
    0.9f, -9.0f, 1.0f, 1e+01f,
    32.0f, 8.0f, 6.0f, 4.0f,
    8.0f, 6.0f, 4.0f, 8.0f,
    6.0f, 4.0f,
};

/* K_OVERLAYSONECONSTANTSTEXTBYTES.CPP */
/* ROM-grounded data: src/overlaysOneConstantsTextBytes.c */
#if defined(VERSION_DE)
const char k_overlaysOneConstantsTextBytes[3] __attribute__((aligned(1))) = "%s\000";
#endif
#if defined(VERSION_EU)
const char k_overlaysOneConstantsTextBytes[3] __attribute__((aligned(1))) = "%s\000";
#endif
#if defined(VERSION_EU_X)
const char k_overlaysOneConstantsTextBytes[3] __attribute__((aligned(1))) = "%s\000";
#endif
#if defined(VERSION_US)
const char k_overlaysOneConstantsTextBytes[3] __attribute__((aligned(1))) = "%s\000";
#endif
#if defined(VERSION_US_REV1)
const char k_overlaysOneConstantsTextBytes[3] __attribute__((aligned(1))) = "%s\000";
#endif
