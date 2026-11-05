#ifndef MENU_MISC_PLAYERSTATE_CMENUPROFILE_FORMATPROFILEQUANTITYLABEL_SYMBOLS_H
#define MENU_MISC_PLAYERSTATE_CMENUPROFILE_FORMATPROFILEQUANTITYLABEL_SYMBOLS_H
#include "types.h"
extern char *g_profileQuantityDefaultLabels[];
/* One row of label pointers per profile selection 1 to 3, one pointer per language: 4 in eu, 3 in eu-x, 1 elsewhere. */
#if defined(VERSION_EU)
#define PROFILE_QUANTITY_CHOICE_LANGUAGES 4
#elif defined(VERSION_EU_X)
#define PROFILE_QUANTITY_CHOICE_LANGUAGES 3
#else
#define PROFILE_QUANTITY_CHOICE_LANGUAGES 1
#endif
extern char *g_profileQuantityChoiceLabels[3][PROFILE_QUANTITY_CHOICE_LANGUAGES];
extern char *g_profileQuantityZeroLabels[];
extern char *g_profileHandicapMaxLabels[];
#if (defined(VERSION_EU) || defined(VERSION_EU_X)) && (defined(VERSION_EU_X))
extern char *g_profileQuantityDefaultLabelsEuStorage[];
#endif
#if (defined(VERSION_EU) || defined(VERSION_EU_X)) && !((defined(VERSION_EU_X)))
extern char *PROFILE_QUANTITY_DEFAULT_LABELS_EU[];
#endif
#if (defined(VERSION_EU) || defined(VERSION_EU_X))
extern char g_profileAlternateQuantityFormat[];
#endif
#if !((defined(VERSION_EU) || defined(VERSION_EU_X)))
extern char g_profileQuantityFormat[];
#endif
#endif
