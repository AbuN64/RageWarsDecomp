#include "Data/rest_source_records.h"
#include "Ai/Nav/combatinit.h"
#include "Ai/Nav/nav_updatevisiblepursuit.h"
#include "Data/Ovl1_d/nav_initvisiblepursuit.h"
#if defined(VERSION_US_REV1)
PlayerControllerStateHeaderUsRev1Layout g_playerControllerStateHeader_usrev1_CEDEC = {
    { 0, 0 },
    1.0f,
    { 5, 0 },
};
RestplayerControllerStateIdThirteenUsRev1Record397 g_playerControllerStateIdThirteen_usrev1_CEE00 = {
    13,
};
unsigned int g_playerControllerStartCallback_usrev1_CEE04[1] = {
    (unsigned int)Nav_InitVisiblePursuit,
};
unsigned int g_playerControllerUpdateCallback_usrev1_CEE08[1] = {
    (unsigned int)Nav_UpdateVisiblePursuit,
};
PlayerControllerStateHeaderAlternateUsRev1Layout g_playerControllerStateHeaderAlternate_usrev1_CEE0C = {
    { 0, 0 },
    1.0f,
    { 5, 0 },
};
RestplayerControllerStateEndUsRev1Record399 g_playerControllerStateEnd_usrev1_CEE20 = {
    -1,
};
#endif
