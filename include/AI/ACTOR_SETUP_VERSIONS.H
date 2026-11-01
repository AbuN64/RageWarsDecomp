#ifndef AI_ACTOR_SETUP_VERSIONS_H
#define AI_ACTOR_SETUP_VERSIONS_H
/* The actor-record builder and its two behaviour tables sit at different addresses in each cartridge. */
#if defined(VERSION_EU)
#define ACTOR_TABLE_A g_Gobjinst_BuildActorTransformAddressEu
#define ACTOR_TABLE_B g_Gobjinst_DrawMaskedModelAddressEu
#elif defined(VERSION_EU_X)
#define ACTOR_TABLE_A g_Gobjinst_BuildActorTransformAddressEuX
#define ACTOR_TABLE_B g_Gobjinst_DrawMaskedModelAddressEuX
#elif defined(VERSION_US)
#define ACTOR_TABLE_A g_Gobjinst_BuildActorTransformAddressUs
#define ACTOR_TABLE_B g_Gobjinst_DrawMaskedModelAddressUs
#elif defined(VERSION_US_REV1)
#define ACTOR_TABLE_A g_Gobjinst_BuildActorTransformAddressUsRev1
#define ACTOR_TABLE_B g_Gobjinst_DrawMaskedModelAddressUsRev1
#else
#define ACTOR_TABLE_A g_Gobjinst_BuildActorTransformAddressDe
#define ACTOR_TABLE_B g_Gobjinst_DrawMaskedModelAddressDe
#endif
#endif
