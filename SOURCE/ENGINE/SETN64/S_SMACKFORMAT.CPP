#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
/* k_SSmackformatEncodedWordsBlock1_SSmackformat.CPP */
RestSSmackformatEncodedWordsBlock1Layout339 k_SSmackformatEncodedWordsBlock1 = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18 },
    0.0079651f,
    -1,
    0x8C500000,
    0x16020007,
    0,
};
#endif
#if defined(VERSION_EU)
RestSSmackformatEncodedWordsBlock1Layout340 k_SSmackformatEncodedWordsBlock1 = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0, -1 },
    { 0.70710677f, 0.0f, -0.70710677f },
};
#endif
#if defined(VERSION_EU_X)
RestSSmackformatEncodedWordsBlock1Layout341 k_SSmackformatEncodedWordsBlock1 = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18 },
    "k %s",
    -1,
    "or find Powe",
};
#endif
#endif
#if defined(VERSION_US_REV1)
/* Announce message block shared by the menu handler table: ids 10..18 followed by the kill-message
   text tail "nted", "Embryo Destr". us-rev1 wording; the other cartridges word this block in their
   own language, so only the versions carrying these bytes land here. */
RestSSmackformatEncodedWordsLayout343 k_SSmackformatEncodedWords = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18 },
    "nted",
    -1,
    "Embryo Destr",
};
#endif
