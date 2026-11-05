#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/effectrender.h"
#include "Frontend/frontend_data_address_symbols.h"
#include "Credits_blank_label/debuglink.h"
#include "Frontend/controllerpak_message_pool.h"
#include "Constants/pak_ok_label_data.h"
#include "Constants/credits_lines_data.h"

/* G_CONSTANTSENCODEDWORDS.CPP */
#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US)
RestConstantsDataVariant2 g_audioDecoderConstants = {
    "NICe",
    0x7175042E,
    { 0, 0, 3840 },
    0x0A000400,
    { (void *)((char *)&g_audioTransformFftTable + 8), (void *)((char *)&g_audioTransformFftTable + 264), (void *)&g_audioDecodedSampleSlots[3072], 0 },
    { 1, 196615, 983071, 4128895, 16712191 },
    { 0x03FF07FF, 0x0FFF1FFF },
    1.9960936f,
    { -65536, 1, 131076, 524304, 2097216, 8388864 },
    { 0x02000400, 0x08001000, 0x20004000 },
    (void *)&g_tlbMissExceptionVector,
    { 262152, 786450, 1638433, 2883637, 4128843, 5832809, 8257685, 12124416 },
    { 0x379837F1, 0x37B504F3, 0x37D744FD },
    { 3.0517578e-05f, 3.629172e-05f, 4.3158372e-05f, 5.1324245e-05f, 6.1035156e-05f, 7.258344e-05f, 8.6316744e-05f, 0.00010264849f, 0.00012207031f, 0.00017263349f, 0.00014516688f, 0.00020529698f, 0.00024414062f, 0.00029033376f, 0.00034526698f, 0.00041059396f, 0.00048828125f, 0.0005806675f, 0.00069053395f, 0.0008211879f, 0.0009765625f, 0.0011613352f, 0.0013810679f, 0.0016423758f, 0.001953125f, 0.00232267f, 0.0027621358f, 0.0032847517f, 0.00390625f, 0.00464534f, 0.0055242716f, 0.0065695033f, 0.0078125f, 0.00929068f, 0.011048543f, 0.013139006f, 0.015625f, 0.01858136f, 0.022097087f, 0.026278013f, 0.03125f, 0.03716272f, 0.044194173f, 0.052556027f, 0.0625f, 0.07432544f, 0.088388346f, 0.10511205f, 0.125f, 0.14865088f, 0.1767767f, 0.2102241f, 0.25f, 0.29730177f, 0.35355338f, 0.4204482f, 0.5f, 0.59460354f, 0.70710677f, 0.8408964f, 1.0f }
};
#endif

/* K_MENULABELTEXTPOINTERS.CPP */
#if defined(VERSION_US_REV1)

void *k_menuLabelTextPointers[10] = {
    g_expansionPakNoticeTextPool, g_debuglinkTextBytes, s_controllerPakText, 0,
    0, 0, (void *)&g_expansionPakNoticeTextPool[16], 0,
    (void *)&g_expansionPakNoticeTextPool[36], 0,
};
#endif

/* ITEM_MULTIPLAYER_AND_ACHIEVEMENT_TEXT_POOL.CPP */
#if defined(VERSION_US_REV1)
char s_itemMultiplayerAchievement_2Health[12] = "2 health\000\000\000";
char g_usRev1Text_10Health[12] = "10 health\000\000";
char g_usRev1Text_15Health[12] = "15 health\000\000";
char g_usRev1Text_25Health[12] = "25 health\000\000";
char g_usRev1Text_50Health[12] = "50 health\000\000";
char g_usRev1Text_fullHealth[12] = "full health";
char s_itemMultiplayerAchievement_UltraHealth[16] = "ultra health\000\000\000";
char g_usRev1Text_1LifeForce[16] = "1 life force\000\000\000";
char g_usRev1Text_10LifeForce[16] = "10 life force\000\000";
char g_usRev1Text_invincibility[16] = "invincibility\000\000";
char g_usRev1Text_planeWalker[16] = "plane walker\000\000\000";
char s_itemMultiplayerAchievement_Flashlight[12] = "flashlight\000";
char g_usRev1Text_flashlightBattery[20] = "flashlight battery\000";
char s_itemMultiplayerAchievement_InfraredGoggles[20] = "InfraRed Goggles\000\000\000";
char s_itemMultiplayerAchievement_BreathOfLife[16] = "breath of life\000";
char s_itemMultiplayerAchievement_EyeOfTruth[16] = "eye of truth\000\000\000";
char s_itemMultiplayerAchievement_LeapOfFaith[16] = "leap of faith\000\000";
char s_itemMultiplayerAchievement_Whispers[12] = "whispers\000\000\000";
char s_itemMultiplayerAchievement_HeartOfFire[16] = "heart of fire\000\000";
char s_itemMultiplayerAchievement_BlueEagleFeather[20] = "blue eagle feather\000";
char g_usRev1Text_greyEagleFeather[20] = "grey eagle feather\000";
char s_itemMultiplayerAchievement_BrownEagleFeather[20] = "brown eagle feather";
char g_usRev1Text_purpleEagleFeather[24] = "purple eagle feather\000\000\000";
char s_itemMultiplayerAchievement_RedEagleFeather[20] = "red eagle feather\000\000";
char g_usRev1Text_nukeWeaponPart[20] = "nuke weapon part\000\000\000";
char s_itemMultiplayerAchievement_Retaliation[16] = "Retaliation !\000\000";
char s_itemMultiplayerAchievement_FlagWasClaimed[20] = "Flag was claimed\000\000\000";
char s_itemMultiplayerAchievement_FlagWasCaptured[20] = "Flag was captured\000\000";
char s_itemMultiplayerAchievement_FlagReturned[16] = "Flag returned\000\000";
char s_itemMultiplayerAchievement_ThePowerIsYours[20] = "The Power is Yours\000";
char s_itemMultiplayerAchievement_FunctionNotAvailable[24] = "Function Not Available\000";
char s_itemMultiplayerAchievement_Warhammer[12] = "WARHAMMER\000\000";
char s_itemMultiplayerAchievement_RaptorClaw[12] = "RAPTOR CLAW";
char s_itemMultiplayerAchievement_MiteBite[12] = "MITE BITE\000\000";
char s_itemMultiplayerAchievement_Boomerang[12] = "BOOMERANG\000\000";
char s_itemMultiplayerAchievement_TekCrossbow[16] = "TEK CROSSBOW\000\000\000";
char s_itemMultiplayerAchievement_Mag60[8] = "MAG 60\000";
char s_itemMultiplayerAchievement_Shotgun[8] = "SHOTGUN";
char s_itemMultiplayerAchievement_AssaultRifle[16] = "ASSAUlT RIFLE\000\000";
char s_itemMultiplayerAchievement_Minigun[8] = "MINIGUN";
char s_itemMultiplayerAchievement_PlasmaRifle[16] = "PLASMA RIFLE\000\000\000";
char s_itemMultiplayerAchievement_FreezeGun[12] = "FREEZE GUN\000";
char s_itemMultiplayerAchievement_FlareGun[12] = "FLARE GUN\000\000";
char s_itemMultiplayerAchievement_Grenades[12] = "GRENADES\000\000\000";
char s_itemMultiplayerAchievement_Scorpion[12] = "SCORPION\000\000\000";
char g_usRev1Text_napalmGel[12] = "NAPALM GEL\000";
char s_itemMultiplayerAchievement_Emaciator[12] = "EMACIATOR\000\000";
char s_itemMultiplayerAchievement_Inflator[12] = "INFLATOR\000\000\000";
char g_usRev1Text_chestBurster[16] = "CHEST BURSTER\000\000";
char g_usRev1Text_cerebralBore[16] = "CEREBRAL BORE\000\000";
char s_itemMultiplayerAchievement_PfmMine[12] = "PFM MINE\000\000\000";
char s_itemMultiplayerAchievement_IronClaw[12] = "IRON CLAW\000\000";
char s_itemMultiplayerAchievement_TeleportMine[16] = "TELEPORT MINE\000\000";
char s_itemMultiplayerAchievement_SentryTurret[16] = "SENTRY TURRET\000\000";
char s_itemMultiplayerAchievement_AttractRemoved[16] = "ATTRACT REMOVED";
char s_itemMultiplayerAchievement_AttractMarked[16] = "ATTRACT MARKED\000";
char g_usRev1Text_repulseMarked[16] = "REPULSE MARKED\000";
char g_usRev1Text_joinedTeamCoyote[20] = "Joined Team Coyote\000";
char g_usRev1Text_joinedTeamBear[20] = "Joined Team Bear\000\000\000";
char g_usRev1Text_joinedTeamCougar[20] = "Joined Team Cougar\000";
char g_usRev1Text_joinedTeamViper[20] = "Joined Team Viper\000\000";
char g_usRev1Text_youFraggedYourself[24] = "You fragged yourself.\000\000";
char s_itemMultiplayerAchievement_MangledByS[16] = "Mangled by %s.\000";
char g_usRev1Text_fraggedByS[16] = "Fragged by %s.\000";
char g_usRev1Text_smackedByS[16] = "Smacked  by %s.";
char g_usRev1Text_sObliteratedYou[20] = "%s obliterated you.";
char g_usRev1Text_sButcheredYou[20] = "%s butchered you.\000\000";
char g_usRev1Text_sCrushedYou[16] = "%s crushed you.";
char g_usRev1Text_poundedByS[16] = "Pounded by %s.\000";
char g_usRev1Text_yourOtherLeft[20] = "your other left.\000\000\000";
char g_usRev1Text_oops[8] = "Oops...";
char g_usRev1Text_badMove[12] = "Bad move...";
char g_usRev1Text_umWatchYourStep[24] = "Um...  Watch your step\077";
char s_itemMultiplayerAchievement_OopsCopy[8] = "Oops...";
char s_itemMultiplayerAchievement_YouWereBested[20] = "You were bested.\000\000\000";
char s_itemMultiplayerAchievement_Munch[8] = "Munch.\000";
char s_itemMultiplayerAchievement_EmbryoImplanted[20] = "Embryo Implanted\000\000\000";
char s_itemMultiplayerAchievement_EmbryoDestroyed[20] = "Embryo Destroyed\000\000\000";
char s_itemMultiplayerAchievement_SmackS[12] = "Smack %s\000\000\000";
char s_itemMultiplayerAchievement_OrFindPowerCore[20] = "or find Power Core\000";
char s_itemMultiplayerAchievement_EnergyRounds[16] = "Energy rounds\000\000";
char s_itemMultiplayerAchievement_EnergyRoundsCopy[16] = "Energy rounds\000\000";
char s_itemMultiplayerAchievement_BulletRounds[16] = "Bullet rounds\000\000";
char s_itemMultiplayerAchievement_BulletRoundsCopy[16] = "Bullet rounds\000\000";
char g_usRev1Text_explosiveRounds[20] = "Explosive rounds\000\000\000";
char g_usRev1Text_explosiveRoundsPickupLabel[20] = "Explosive rounds\000\000\000";
char g_usRev1Text_ammoPack[12] = "Ammo pack\000\000";
char g_usRev1Text_bullet[8] = "bullet\000";
char g_usRev1Text_energyRound[16] = "energy round\000\000\000";
char g_usRev1Text_explosiveRound[16] = "explosive round";
char g_usRev1Text_cerebralBoreItemLabel[16] = "cerebral bore\000\000";
char g_usRev1Text_pfmMine[12] = "pfm mine\000\000\000";
char g_usRev1Text_sentryTurret[16] = "sentry turret\000\000";
char g_usRev1Text_ironClaw[12] = "iron claw\000\000";
char s_itemMultiplayerAchievement_TeleportMineCopy[16] = "teleport mine\000\000";
char g_usRev1Text_slowTime[16] = "Slow Time...\000\000\000";
char g_usRev1Text_blastShield[16] = "Blast Shield...";
char g_usRev1Text_regeneration[16] = "Regeneration...";
char g_usRev1Text_petrify[12] = "Petrify...\000";
char g_usRev1Text_damageReversal[20] = "Damage Reversal...\000";
char g_usRev1Text_invisibility[16] = "Invisibility...";
char g_usRev1Text_lifeForceVampire[24] = "Life Force Vampire...\000\000";
char g_usRev1Text_speedBurst[16] = "Speed Burst...\000";
char g_usRev1Text_teleportation[20] = "Teleportation...\000\000\000";
char g_usRev1Text_teleportedToSafety[28] = "Teleported to safety...(\077)\000";
char s_itemMultiplayerAchievement_MassiveDamage[20] = "Massive Damage...\000\000";
char s_itemMultiplayerAchievement_Invunerability[20] = "Invunerability...\000\000";
char s_itemMultiplayerAchievement_BulletShield[20] = "Bullet Shield...\000\000\000";
char s_itemMultiplayerAchievement_EnergyAbsorption[24] = "Energy Absorption...\000\000\000";
char g_usRev1Text_somethingElse[20] = "Something Else...\000\000";
char g_usRev1Text_shield[8] = "Shield\000";
char g_usRev1Text_novice[8] = "NOVICE\000";
char s_itemMultiplayerAchievement_Newcomer[12] = "NEWCOMER\000\000\000";
char s_itemMultiplayerAchievement_Grunt[8] = "GRUNT\000\000";
char g_usRev1Text_scout[8] = "SCOUT\000\000";
char g_usRev1Text_brave[8] = "BRAVE\000\000";
char s_itemMultiplayerAchievement_Tracker[8] = "TRACKER";
char g_usRev1Text_hunter[8] = "HUNTER\000";
char s_itemMultiplayerAchievement_Warrior[8] = "WARRIOR";
char g_usRev1Text_darkling[12] = "DARKLING\000\000\000";
char g_usRev1Text_seeker[8] = "SEEKER\000";
char s_itemMultiplayerAchievement_Assassin[12] = "ASSASSIN\000\000\000";
char g_usRev1Text_bane[8] = "BANE\000\000\000";
char g_usRev1Text_warlord[8] = "WARLORD";
char g_usRev1Text_deathwind[12] = "DEATHWIND\000\000";
char g_usRev1Text_conqueror[12] = "CONQUEROR\000\000";
char g_usRev1Text_master[8] = "MASTER\000";
char g_usRev1Text_tyrant[8] = "TYRANT\000";
char g_usRev1Text_warslave[12] = "WARSLAVE\000\000\000";
char g_usRev1Text_godhand[8] = "GODHAND";
char g_usRev1Text_chieftain[12] = "CHIEFTAIN\000\000";
char g_usRev1Text_achievementOnProvingGrounds[32] = "ACHIEVEMENT ON PROVING GROUNDS\000";
char g_usRev1Text_achievementOnBasicTraining[32] = "ACHIEVEMENT ON BASIC TRAINING\000\000";
char g_usRev1Text_achievementOnCrossroads[28] = "ACHIEVEMENT ON CROSSROADS\000\000";
char g_usRev1Text_achievementOnGrimRetreat[28] = "ACHIEVEMENT ON GRIM RETREAT";
char g_usRev1Text_achievementOnCathedral[28] = "ACHIEVEMENT ON CATHEDRAL\000\000\000";
char g_usRev1Text_achievementOnFallout[24] = "ACHIEVEMENT ON FALLOUT\000";
char g_usRev1Text_achievementOnBoxedSet[28] = "ACHIEVEMENT ON BOXED SET\000\000\000";
char g_usRev1Text_achievementOnDireStraight[32] = "ACHIEVEMENT ON DIRE STRAIGHT\000\000\000";
char g_usRev1Text_achievementOnPrey[20] = "ACHIEVEMENT ON PREY";
char g_usRev1Text_achievementOnWarehouse[28] = "ACHIEVEMENT ON WAREHOUSE\000\000\000";
char s_itemMultiplayerAchievement_AchievementOnWaterTemple[28] = "ACHIEVEMENT ON WATER TEMPLE";
char g_usRev1Text_achievementOnBombShelter[28] = "ACHIEVEMENT ON BOMB SHELTER";
char g_usRev1Text_achievementOnTempered[24] = "ACHIEVEMENT ON TEMPERED";
char g_usRev1Text_achievementOnEarthTemple[28] = "ACHIEVEMENT ON EARTH TEMPLE";
char g_usRev1Text_achievementOnFireTemple[28] = "ACHIEVEMENT ON FIRE TEMPLE\000";
char g_usRev1Text_achievementOnMystic[24] = "ACHIEVEMENT ON MYSTIC\000\000";
char g_usRev1Text_achievementOnBottleneck[28] = "ACHIEVEMENT ON BOTTLENECK\000\000";
char g_usRev1Text_achievementOnTightrope[28] = "ACHIEVEMENT ON TIGHTROPE\000\000\000";
char g_usRev1Text_achievementOnThePit[24] = "ACHIEVEMENT ON THE PIT\000";
char g_usRev1Text_achievementOnLeapOf[32] = "ACHIEVEMENT ON LEAP OF FAITH\000\000\000";
char g_usRev1Text_achievementOnWickedDance[28] = "ACHIEVEMENT ON WICKED DANCE";
char g_usRev1Text_achievementOnBunker[24] = "ACHIEVEMENT ON BUNKER\000\000";
char g_usRev1Text_achievementOnAmphitheater[28] = "ACHIEVEMENT ON AMPHITHEATER";
char g_usRev1Text_achievementOnFireWalker[28] = "ACHIEVEMENT ON FIRE WALKER\000";
char g_usRev1Text_achievementOnCrypts[24] = "ACHIEVEMENT ON CRYPTS\000\000";
char g_usRev1Text_achievementOnBreakdown[28] = "ACHIEVEMENT ON BREAKDOWN\000\000\000";
char g_usRev1Text_achievementOnRetaliation[28] = "ACHIEVEMENT ON RETALIATION\000";
char g_usRev1Text_achievementOnHopeless[24] = "ACHIEVEMENT ON HOPELESS";
char g_usRev1Text_achievementOnMatrix[24] = "ACHIEVEMENT ON MATRIX\000\000";
char g_usRev1Text_achievementOnFathom[24] = "ACHIEVEMENT ON FATHOM\000\000";
char g_usRev1Text_achievementOnThePedestal[28] = "ACHIEVEMENT ON THE PEDESTAL";
char g_usRev1Text_achievementOnDefcon5[24] = "ACHIEVEMENT ON DEFCON 5";
char g_usRev1Text_achievementOnSpiritTemple[32] = "ACHIEVEMENT ON SPIRIT TEMPLE\000\000\000";
char s_itemMultiplayerAchievement_AchievementOnStronghold[28] = "ACHIEVEMENT ON STRONGHOLD\000\000";
char g_usRev1Text_achievementOnCourtyard[28] = "ACHIEVEMENT ON COURTYARD\000\000\000";
char g_usRev1Text_achievementOnStarlight[28] = "ACHIEVEMENT ON STARLIGHT\000\000\000";
char g_usRev1Text_attained15FragsIn[32] = "ATTAINED 15 FRAGS IN 5 MINUTES\000";
char g_usRev1Text_attained25FragsIn[32] = "ATTAINED 25 FRAGS IN 10 MINUTES";
char g_usRev1Text_notGettingAnyFrags[24] = "NOT GETTING ANY FRAGS\000\000";
char g_usRev1Text_killingYourself5Times[28] = "KILLING YOURSELF 5 TIMES\000\000\000";
char g_usRev1Text_comingInLast[16] = "COMING IN LAST\000";
char g_usRev1Text_totalFragAward[20] = "TOTAL FRAG AWARD\000\000\000";
char g_usRev1Text_totalBeingKilledAward[28] = "TOTAL BEING KILLED AWARD\000\000\000";
char g_usRev1Text_sniping10PeopleIn[32] = "SNIPING 10 PEOPLE IN A ROUND\000\000\000";
char g_usRev1Text_notBeingKilledIn[28] = "NOT BEING KILLED IN A ROUND";
char g_usRev1Text_defeatedBastille[20] = "DEFEATED BASTILLE\000\000";
char g_usRev1Text_defeatedSyra[16] = "DEFEATED SYRA\000\000";
char g_usRev1Text_defeatedSymbiont[20] = "DEFEATED SYMBIONT\000\000";
char g_usRev1Text_defeatedTalSet[20] = "DEFEATED TAL SET\000\000\000";
char g_usRev1Text_beatingTheCooperativeScenario[36] = "BEATING THE COOPERATIVE SCENARIO\000\000\000";
char g_usRev1Text_empty[8] = "<EMPTY>";
char s_itemMultiplayerAchievement_NewPlayer[16] = "<NEW PLAYER>\000\000\000";
char g_usRev1Text_turok[8] = "TUROK\000\000";
char g_usRev1Text_warrior[8] = "WARRIOR";
char g_usRev1Text_masterItemLabel[8] = "MASTER\000";
char g_usRev1Text_adon[8] = "ADON\000\000\000";
char g_usRev1Text_seekerItemLabel[8] = "SEEKER\000";
char g_usRev1Text_huntress[12] = "HUNTRESS\000\000\000";
char g_usRev1Text_campain[8] = "CAMPAIN";
char g_usRev1Text_slaver[8] = "SLAVER\000";
char g_usRev1Text_tyrantItemLabel[8] = "TYRANT\000";
char g_usRev1Text_fireborn[12] = "FIREBORN\000\000\000";
char g_usRev1Text_icelord[8] = "ICELORD";
char g_usRev1Text_entrail[8] = "ENTRAIL";
char g_usRev1Text_mites[8] = "MITES\000\000";
char g_usRev1Text_compies[8] = "COMPIES";
char g_usRev1Text_teddies[8] = "TEDDIES";
char g_usRev1Text_juggnaut[12] = "JUGGNAUT\000\000\000";
char g_usRev1Text_sloth[8] = "SLOTH\000\000";
char s_itemMultiplayerAchievement_Mauler[8] = "MAULER\000";
char g_usRev1Text_drone[8] = "DRONE\000\000";
char g_usRev1Text_grunt[8] = "GRUNT\000\000";
char g_usRev1Text_slave[8] = "SLAVE\000\000";
char s_itemMultiplayerAchievement_Soldier[8] = "SOLDIER";
char g_usRev1Text_captain[8] = "CAPTAIN";
char g_usRev1Text_king[8] = "KING\000\000\000";
char g_usRev1Text_bastille[12] = "BASTILLE\000\000\000";
char g_usRev1Text_talSet[8] = "TAL SET";
char g_usRev1Text_syra[8] = "SYRA\000\000\000";
char g_usRev1Text_symbiont[12] = "SYMBIONT\000\000\000";
char g_usRev1Text_guardian[12] = "GUARDIAN\000\000\000";
char g_usRev1Text_ravage[8] = "RAVAGE\000";
char g_usRev1Text_cyclops[8] = "CYCLOPS";
char g_usRev1Text_lorddead[12] = "LORDDEAD\000\000\000";
char g_usRev1Text_maggot[8] = "MAGGOT\000";
char g_usRev1Text_vile[8] = "VILE\000\000\000";
char g_usRev1Text_elite[8] = "ELITE\000\000";
char g_usRev1Text_biobot[8] = "BIOBOT\000";
char g_usRev1Text_killbot[8] = "KILLBOT";
char g_usRev1Text_death[8] = "DEATH\000\000";
char g_usRev1Text_reaper[8] = "REAPER\000";
char s_itemMultiplayerAchievement_Maw[4] = "MAW";
char g_usRev1Text_raptor[8] = "RAPTOR\000";
char g_usRev1Text_slag[8] = "SLAG\000\000\000";
char g_usRev1Text_claw[8] = "CLAW\000\000\000";
char g_usRev1Text_warclubs[12] = "WARCLUBS\000\000\000";
char g_usRev1Text_turokItemLabel[8] = "TUROK\000\000";
char g_usRev1Text_mantidDrone[16] = "MANTID DRONE\000\000\000";
char g_usRev1Text_campaigner[12] = "CAMPAIGNER\000";
char g_usRev1Text_firebornItemLabel[12] = "FIREBORN\000\000\000";
char g_usRev1Text_mantidSoldier[16] = "MANTID SOLDIER\000";
char g_usRev1Text_adonItemLabel[8] = "ADON\000\000\000";
char g_usRev1Text_lordOfTheDead[20] = "LORD OF THE DEAD\000\000\000";
char g_usRev1Text_eliteGuard[12] = "ELITE GUARD";
char g_usRev1Text_guardianItemLabel[12] = "GUARDIAN\000\000\000";
char g_usRev1Text_juggernaut[12] = "JUGGERNAUT\000";
char g_usRev1Text_oblivionSpawn[16] = "OBLIVION SPAWN\000";
char g_usRev1Text_bastilleItemLabel[12] = "BASTILLE\000\000\000";
char g_usRev1Text_syraItemLabel[8] = "SYRA\000\000\000";
char g_usRev1Text_symbiontItemLabel[12] = "SYMBIONT\000\000\000";
char g_usRev1Text_talSetItemLabel[8] = "TAL SET";
char g_usRev1Text_raptorItemLabel[8] = "RAPTOR\000";
char g_usRev1Text_mantidMites[16] = "MANTID MITES\000\000\000";
char g_usRev1Text_captureTheFlagD[28] = "capture the flag %d time\000\000\000";
char g_usRev1Text_captureTheFlagD2[28] = "capture the flag %d times\000\000";
char g_usRev1Text_acquireDTeamCaptures[28] = "acquire %d team captures\000\000\000";
char g_usRev1Text_tagTheMonkeyD[24] = "tag the monkey %d time\000";
char g_usRev1Text_tagTheMonkeyD2[24] = "tag the monkey %d times";
char g_usRev1Text_acquireDCreatureTags[28] = "acquire %d creature tags\000\000\000";
char g_usRev1Text_acquireDFrag[16] = "acquire %d frag";
char g_usRev1Text_acquireDFrags[20] = "acquire %d frags\000\000\000";
char g_usRev1Text_acquireDTeamFrag[24] = "acquire %d team frag\000\000\000";
char g_usRev1Text_acquireDTeamFrags[24] = "acquire %d team frags\000\000";
char g_usRev1Text_in02dSecondsOr[24] = "in %02d seconds or less";
char g_usRev1Text_inDMinuteAnd[40] = "in %d minute and %02d seconds or less\000\000";
char g_usRev1Text_inDMinutesAnd[40] = "in %d minutes and %02d seconds or less\000";
char g_usRev1Text_inDMinuteOr[24] = "in %d minute or less\000\000\000";
char g_usRev1Text_inDMinutesOr[24] = "in %d minutes or less\000\000";
char g_usRev1Text_withDLife[16] = "with %d life\000\000\000";
char g_usRev1Text_withDLives[16] = "with %d lives\000\000";
char g_usRev1Text_defeatS[12] = "defeat %s\000\000";
char g_usRev1Text_defeatBothSAnd[24] = "defeat both %s and %s\000\000";
char g_usRev1Text_everyManForThemselves[28] = "every man for themselves\000\000\000";
char g_usRev1Text_easy[8] = "EASY\000\000\000";
char g_usRev1Text_medium[8] = "MEDIUM\000";
char g_usRev1Text_hard[8] = "HARD\000\000\000";
char g_usRev1Text_off[4] = "OFF";
#endif

/* MENU_ON_LABEL_DATA.CPP */
#if defined(VERSION_US_REV1)
char g_MenuOnLabelStorage[4] = "ON\000\000";
#endif

/* G_COLORORIENTATIONRESOLUTIONTEXTPOOL.CPP */
#if defined(VERSION_US_REV1)
char s_colorOrientationResolution_Red[4] = "RED";
char g_usRev1Text_green[8] = "GREEN\000\000";
char g_usRev1Text_horizontal[12] = "HORIZONTAL\000";
char g_usRev1Text_vertical[12] = "VERTICAL\000\000\000";
char g_usRev1Text_lorez[8] = "LOREZ\000\000";
char g_usRev1Text_hirez[8] = "HIREZ\000\000";
char g_usRev1Text_letterbox[12] = "LETTERBOX\000\000";
#endif

/* MENU_NO_LABEL_DATA.CPP */
#if defined(VERSION_US_REV1)
char g_MenuNoLabelStorage[4] = "NO\000\000";
#endif

/* G_DIFFICULTYCONTROLLERMENUTEXTPOOL.CPP */
#if defined(VERSION_US_REV1)
char s_difficultyControllerMenu_Yes[4] = "YES";
char g_usRev1Text_noviceItemLabel[8] = "NOVICE\000";
char g_usRev1Text_easyItemLabel[8] = "EASY\000\000\000";
char g_usRev1Text_normal[8] = "NORMAL\000";
char g_usRev1Text_veteran[8] = "VETERAN";
char g_usRev1Text_expert[8] = "EXPERT\000";
char g_usRev1Text_arcade[8] = "ARCADE\000";
char g_usRev1Text_wheel[8] = "WHEEL\000\000";
char g_usRev1Text_tap[4] = "TAP";
char g_usRev1Text_mixed[8] = "MIXED\000\000";
char g_usRev1Text_controllerD[16] = "CONTROLLER %d\000\000";
char g_usRev1Text_ctf[4] = "CTF";
char g_usRev1Text_tbl[4] = "TBL";
#endif

/* MENU_ABBREVIATIONS_DATA.CPP */
#if defined(VERSION_US_REV1)
char g_MenuAbbreviationsStorage[8] = "BL\000\000FT\000\000";
#endif

/* G_MATCHMODEANDREWARDTEXTPOOL.CPP */
#if defined(VERSION_US_REV1)
char s_matchModeReward_Gauntlet[12] = "GAUNTLET\000\000\000";
char g_usRev1Text_fragFest[12] = "FRAG FEST\000\000";
char g_usRev1Text_timeTrial[12] = "TIME TRIAL\000";
char g_usRev1Text_playerD[12] = "PLAYER%d\000\000\000";
char g_usRev1Text_acquiredEagleTalisman1[32] = "ACQUIRED EAGLE TALISMAN. 1 UP!\000";
char g_usRev1Text_acquiredHalfEagleTalisman[52] = "ACQUIRED HALF EAGLE TALISMAN. ANoTHER GIVES 1 UP\000\000\000";
char g_usRev1Text_acquiredTheOtherEagle[48] = "ACQUIRED THE OTHER EAGLE TALISMAN, GAINED 1 UP!";
char g_usRev1Text_acquiredBearTalismanExplosive[44] = "ACQUIRED BEAR TALISMAN. EXPLOSIVE AMMO UP 5";
char g_usRev1Text_acquiredCoyoteTalismanBullet[44] = "ACQUIRED COYOTE TALISMAN. BULLET AMMO UP 50";
char g_usRev1Text_acquiredCougarTalismanEnergy[44] = "ACQUIRED COUGAR TALISMAN. ENERGY AMMO UP 50";
char g_usRev1Text_acquiredViperTalismanHealth[44] = "ACQUIRED VIPER TALISMAN. HEAlTH MAX UP 5\000\000\000";
char g_usRev1Text_acquiredCooperativeTalisman[32] = "ACQUIRED COOPERATIVE TALISMAN\000\000";
char g_usRev1Text_acquiredMinigameIcon[24] = "ACQUIRED MINIGAME ICON\000";
char g_usRev1Text_acquiredAssaultRifle[24] = "ACQUIRED ASSAULT RIFLE\000";
char g_usRev1Text_acquiredAssaultRifleRapid[44] = "ACQUIRED ASSAULT RIFLE RAPID FIRE UPGRADE\000\000";
char g_usRev1Text_acquiredTekCrossBow[36] = "ACQUIRED TEK CROSS BOW SNIPER SCOPE";
char g_usRev1Text_acquiredGrenadeLauncher[28] = "ACQUIRED GRENADE LAUNCHER\000\000";
char g_usRev1Text_acquiredGrenadeLauncherUpgrade[36] = "ACQUIRED GRENADE LAUNCHER UPGRADE\000\000";
char g_usRev1Text_acquiredPlasmaRifle[24] = "ACQUIRED PLASMA RIFLE\000\000";
char g_usRev1Text_acquiredPlasmaRifleScope[28] = "ACQUIRED PLASMA RIFLE SCOPE";
char g_usRev1Text_acquiredAcidSpitAttack[28] = "ACQUIRED ACID SPIT ATTACK\000\000";
char g_usRev1Text_acquiredJumpClawAttack[28] = "ACQUIRED JUMP CLAW ATTACK\000\000";
char g_usRev1Text_acquiredRadioactiveFlareGun[32] = "ACQUIRED RADIOACTIVE FLARE GUN\000";
char g_usRev1Text_acquiredRadioactiveFlareGunMatchOptionLabel[40] = "ACQUIRED RADIOACTIVE FLARE GUN UPGRADE\000";
char g_usRev1Text_acquiredScorpionLauncher[28] = "ACQUIRED SCORPION LAUNCHER\000";
char g_usRev1Text_acquiredScorpionLauncherMagnet[44] = "ACQUIRED SCORPION LAUNCHER MAGNET UPGRADE\000\000";
char g_usRev1Text_acquiredFreezeGun[20] = "ACQUIRED FREEZE GUN";
char g_usRev1Text_acquiredFreezeGunUpgrade[28] = "ACQUIRED FREEZE GUN UPGRADE";
char g_usRev1Text_acquiredNapalmGel[20] = "ACQUIRED NAPALM GEL";
char g_usRev1Text_acquiredMag60Laser[36] = "ACQUIRED MAG 60 LASER SIGHT UPGRADE";
char g_usRev1Text_acquiredChestburster[24] = "ACQUIRED CHESTBURSTER\000\000";
char g_usRev1Text_acquiredInflator[20] = "ACQUIRED INFLATOR\000\000";
char g_usRev1Text_acquiredInflatorUpgrade[28] = "ACQUIRED INFLATOR UPGRADE\000\000";
char g_usRev1Text_acquiredBoomerang[20] = "ACQUIRED BOOMERANG\000";
char g_usRev1Text_acquiredBoomerangUpgrade[28] = "ACQUIRED BOOMERANG UPGRADE\000";
char g_usRev1Text_acquiredMinigun[20] = "ACQUIRED MINIGUN\000\000\000";
char g_usRev1Text_acquiredMinigunPersonalShield[44] = "ACQUIRED MINIGUN PERSONAL SHIELD UPGRADE\000\000\000";
char g_usRev1Text_acquiredShotgunStreetsweeperUpgrade[40] = "ACQUIRED SHOTGUN STREETSWEEPER UPGRADE\000";
char g_usRev1Text_acquiredEmaciator[20] = "ACQUIRED EMACIATOR\000";
char g_usRev1Text_acquiredEmaciatorUpgrade[28] = "ACQUIRED EMACIATOR UPGRADE\000";
char g_usRev1Text_acquiredWarhammerRocketUpgrade[36] = "ACQUIRED WARHAMMER ROCKET UPGRADE\000\000";
char g_usRev1Text_youHaveUnlockedS[24] = "YOU HAVE UNLOCKED %s\000\000\000";
char g_usRev1Text_missionFailed[16] = "MISSION FAILED\000";
char g_usRev1Text_itemPreviouslyAcquired[28] = "ITEM PREVIOUSLY ACQUIRED\000\000\000";
char g_usRev1Text_team[8] = "TEAM\000\000\000";
char g_usRev1Text_hit[8] = "HIT%\000\000\000";
char g_usRev1Text_tags[8] = "TAGS\000\000\000";
char g_usRev1Text_flags[8] = "FLAGS\000\000";
char g_usRev1Text_congratulationsYouHaveCompleted[48] = "CONGRATULATIONS! YOU HAVE COMPLETED FRAG FEST\000\000";
char g_usRev1Text_congratulationsYouHaveCompletedMatchOptionLabel[48] = "CONGRATULATIONS! YOU HAVE COMPLETED TIME TRIAL\000";
char g_usRev1Text_english[8] = "ENGLISH";
char g_usRev1Text_pistolClip10Rounds[24] = "pistol clip (10 rounds)";
char g_usRev1Text_rifleClip10Rounds[24] = "rifle clip (10 rounds)\000";
char g_usRev1Text_difficultyEasy[24] = "difficulty   :     easy";
char g_usRev1Text_difficultyNormal[24] = "difficulty   :   normal";
char g_usRev1Text_difficultyHard[24] = "difficulty   :     hard";
char g_usRev1Text_controlTypeExpert[24] = "control type :   expert";
char g_usRev1Text_controlTypeArcade[24] = "control type :   arcade";
char g_usRev1Text_controlType[24] = "control type :   \077\077\077\077\077\077";
char g_usRev1Text_controlSideLeft[24] = "control side :     left";
char g_usRev1Text_controlSideRight[24] = "control side :    right";
char g_usRev1Text_lookSpringOn[24] = "look spring  :       on";
char g_usRev1Text_lookSpringOff[24] = "look spring  :      off";
char g_usRev1Text_autoAimOn[24] = "auto aim     :       on";
char g_usRev1Text_autoAimOff[24] = "auto aim     :      off";
char g_usRev1Text_bloodColorOff[24] = "blood color  :      off";
char g_usRev1Text_bloodColorRed[24] = "blood color  :      red";
char g_usRev1Text_bloodColorGreen[24] = "blood color  :    green";
char g_usRev1Text_2PlyrLayoutHorz[24] = "2 plyr layout:     horz";
char g_usRev1Text_2PlyrLayoutVert[24] = "2 plyr layout:     vert";
char g_usRev1Text_opacityClear[24] = "opacity      :    clear";
char g_usRev1Text_opacityOpaque[24] = "opacity      :   opaque";
char g_usRev1Text_opacity[24] = "opacity      :         ";
char g_usRev1Text_controlStickHorzNorm[24] = "control stick horz:norm";
char g_usRev1Text_controlStickHorz[24] = "control stick horz:    ";
char g_usRev1Text_controlStickVertNorm[24] = "control stick vert:norm";
char g_usRev1Text_controlStickVert[24] = "control stick vert:    ";
char g_usRev1Text_weaponSelectQuick[24] = "Weapon Select:    quick";
char g_usRev1Text_weaponSelectNorm[24] = "Weapon Select:     norm";
char g_usRev1Text_resolutionLoRez[24] = "Resolution   :   lo-rez";
char g_usRev1Text_resolutionHiRez[24] = "Resolution   :   hi-rez";
char g_usRev1Text_resolutionHiRezLb[24] = "Resolution   :hi-rez-lb";
char g_usRev1Text_resolutionSmLoRez[24] = "Resolution   :sm-lo-rez";
char g_usRev1Text_resolutionLoRezLb[24] = "Resolution   :lo-rez-lb";
char g_usRev1Text_brightnessNorm[24] = "brightness   :     norm";
char g_usRev1Text_brightness[24] = "brightness   :         ";
char g_usRev1Text_languageEnglish[24] = "language     :  english";
char g_usRev1Text_goBack[8] = "go back";
#endif

/* G_BLOODSCOREMENUTEXTPOOL.CPP */
#if defined(VERSION_US_REV1)
char s_bloodScoreMenu_Choose[8] = "choose\000";
char g_usRev1Text_blueBlood[12] = "blue blood\000";
char g_usRev1Text_redBlood[12] = "red blood\000\000";
char g_usRev1Text_finalScore[12] = "final score";
char g_usRev1Text_blueBloodScore[24] = "blue blood score :    \000";
char g_usRev1Text_redBloodScore[24] = " red blood score :    \000";
char g_usRev1Text_pleaseWait[20] = "please wait.....\000\000\000";
char g_usRev1Text_paused[8] = "paused\000";
char s_bloodScoreMenu_ResumeGame[12] = "resume game";
char g_usRev1Text_missionStatus[16] = "mission status\000";
char g_usRev1Text_missionObjectives[20] = "mission objectives\000";
char g_usRev1Text_inventory[12] = "inventory\000\000";
char g_usRev1Text_load[8] = "load\000\000\000";
char g_usRev1Text_options[8] = "options";
char g_usRev1Text_cheats[8] = "cheats\000";
char g_usRev1Text_quit[8] = "quit\000\000\000";
char g_usRev1Text_inventoryInventoryLabel[12] = "inventory\000\000";
#endif

/* MENU_OKAY_LABEL_WORD_EU_X_DATA.CPP */
#if defined(VERSION_US_REV1)
char g_menuOkayLabelWordEuX[4] = "ok\000\000";
#endif

/* GAME_TITLE_TEXT.CPP */
#if defined(VERSION_US_REV1)
char s_gameTitle_RageWars[12] = "RAGE WARS\000\000";
char g_usRev1Text_turok2_[8] = "TUROK 2";
#endif

/* LABEL_TEXT_FIFTY_ONE.CPP */
#if defined(VERSION_US_REV1)
char g_menuNumberLabelText[4] = "51\000\000";
#endif

/* S_NRWETEXT.CPP */
#if defined(VERSION_US_REV1)
char s_nrweText[8] = "NRWE";
#endif

/* S_OTHERGAMETEXT.CPP */
#if defined(VERSION_US_REV1)
char s_otherGameText[12] = "OTHER GAME";
#endif

/* G_NOTEDIFFICULTYMENUTEXTPOOL.CPP */
#if defined(VERSION_US_REV1)
char s_noteDifficultyMenu_NoteInfo[12] = "note info\000\000";
char g_usRev1Text_deleteNote[12] = "delete note";
char g_usRev1Text_difficultyEasyPakNoteLabel[20] = "difficulty :  easy\000";
char g_usRev1Text_difficultyNormalPakNoteLabel[20] = "difficulty :normal\000";
char g_usRev1Text_difficultyHardPakNoteLabel[20] = "difficulty :  hard\000";
char g_usRev1Text_health[20] = "health     :      \000";
char g_usRev1Text_lives[20] = "lives      :      \000";
char g_usRev1Text_timeClockReadout[16] = "time :000.00.00";
char g_usRev1Text_noteInfo[12] = "note info\000\000";
char g_usRev1Text_deleteNoteCopies[2][12] = { "delete note", "delete note" };
char g_usRev1Text_nameExt[24] = "name             ext \000\000";
char g_usRev1Text_Text[24] = "                     \000\000";
char g_usRev1Text_name[20] = "name  :            ";
char g_usRev1Text_type[20] = "type  :            ";
char g_usRev1Text_frags[20] = "frags :            ";
char g_usRev1Text_rank[20] = "rank  :            ";
char g_usRev1Text_loadPakNoteLabel[8] = "load\077\000\000";
char g_usRev1Text_delete[8] = "delete\077";
char g_usRev1Text_deletePakNoteLabel[8] = "delete\077";
char g_usRev1Text_error[8] = "error\000\000";
char g_usRev1Text_important[12] = "important\000\000";
#endif

/* PAK_OK_LABEL_DATA.CPP */
#if defined(VERSION_US_REV1)
unsigned char g_PakOkLabelStorage[3] = {
    0x6F, 0x6B, 0x00,
};
#endif

/* G_SAVELOADHEALTHAMMOMENUTEXTPOOL.CPP */
#if defined(VERSION_US_REV1)
char g_saveLoadHealthAmmoMenuTextPool[8] = "   save";
char g_usRev1Text_loadSaveLoadMenu[8] = "   load";
char g_usRev1Text_healthSaveLoadMenu[8] = " health";
char g_usRev1Text_ammo[8] = "   ammo";
char g_usRev1Text_goBackSaveLoadMenu[8] = "go back";
#endif

/* HIT_FEEDBACK_AND_EDIT_TEXT.CPP */
#if defined(VERSION_US_REV1)
char g_hitLocationMessageText[12] = "pmf shot!\000\000";
char g_usRev1Text_bodyShot[12] = "body shot!\000";
char g_usRev1Text_headShot[12] = "head shot!\000";
char g_usRev1Text_armShot[12] = "arm shot!\000\000";
char g_usRev1Text_edit[8] = "edit\000\000\000";
#endif

/* G_UNREFERENCEDPACKEDBYTEWORDSUSREVISION.CPP */
#if defined(VERSION_US_REV1)
ConstantsEncodedWordsBlock14Layout g_unreferencedPackedByteWordsUsRevision = {
    { 0x02000000, 0x03000000, 0x04000000 }
};
#endif

/* COMBAT_AND_CONFIRMATION_TEXT.CPP */
#if defined(VERSION_US_REV1)
char s_combatConfirm_TaggedBy[12] = "tagged by \000";
char g_usRev1Text_youTagged[12] = "you tagged ";
char g_usRev1Text_killedBy[12] = "killed by \000";
char g_usRev1Text_youKilled[12] = "you killed ";
char g_usRev1Text_youKilledYourself[20] = "you killed yourself";
char g_usRev1Text_youLostTheFlag[24] = "you lost the flag!!!\000\000\000";
char g_usRev1Text_heDroppedTheFlag[24] = "He dropped the flag!!!\000";
char g_usRev1Text_areYouSure[16] = "are you sure\077\000\000";
char g_usRev1Text_youWantTo[12] = "you want to";
char g_usRev1Text_yes[4] = "yes";
#endif

/* MENU_NO_LABEL_WORD_EU_X_DATA.CPP */
#if defined(VERSION_US_REV1)
char g_menuNoLabelWordEuX[4] = "no\000\000";
#endif

/* CHEAT_GAME_OPTIONS_AND_STATUS_TEXT_POOL.CPP */
#if defined(VERSION_US_REV1)
char s_cheatOptions_Cheats[8] = "cheats\000";
char g_usRev1Text_loadInGameMenuOptionLabel[8] = "load\000\000\000";
char g_usRev1Text_save[8] = "save\000\000\000";
char g_usRev1Text_enterCheat[12] = "enter cheat";
char g_usRev1Text_joinNow[12] = "join now\000\000\000";
char g_usRev1Text_waiting[12] = "waiting..\000\000";
char g_usRev1Text_connect[12] = "connect..\000\000";
char g_usRev1Text_goBackInGameMenuOptionLabel[8] = "go back";
char g_usRev1Text_continue[12] = "continue \077\000";
char g_usRev1Text_gameOver[12] = "game over\000\000";
char g_usRev1Text_timeXx[12] = "time : xx\000\000";
char g_usRev1Text_done[8] = "done\000\000\000";
char g_usRev1Text_newCheatEnabled[20] = "new cheat enabled\000\000";
char g_usRev1Text_invincibilityActivated[24] = "invincibility activated";
char g_usRev1Text_infiniteLivesActivated[28] = "infinite lives activated\000\000\000";
char g_usRev1Text_allWeaponsActivated[24] = "all weapons activated\000\000";
char g_usRev1Text_unlimitedAmmoActivated[28] = "unlimited ammo activated\000\000\000";
char g_usRev1Text_allKeysActivated[20] = "all keys activated\000";
char g_usRev1Text_bigHeadModeActivated[24] = "big head mode activated";
char g_usRev1Text_tinyModeActivated[20] = "tiny mode activated";
char g_usRev1Text_stickModeActivated[24] = "stick mode activated\000\000\000";
char g_usRev1Text_bigHandsAndFeet[36] = "big hands and feet mode activated\000\000";
char g_usRev1Text_penAndInkMode[28] = "pen and ink mode activated\000";
char g_usRev1Text_gouraudModeActivated[24] = "gouraud mode activated\000";
char g_usRev1Text_juansCheatActivated[24] = "juans cheat activated\000\000";
char g_usRev1Text_zachAttackCheatActivated[28] = "zach attack cheat activated";
char g_usRev1Text_allMapActivated[20] = "all map activated\000\000";
char g_usRev1Text_blackoutModeActivated[24] = "blackout mode activated";
char g_usRev1Text_mmmmTastyFrootyStripes[32] = "mmmm... tasty frooty stripes\000\000\000";
char g_usRev1Text_warpLevel1Activated[24] = "warp level 1 activated\000";
char g_usRev1Text_warpLevel2Activated[24] = "warp level 2 activated\000";
char g_usRev1Text_warpLevel3Activated[24] = "warp level 3 activated\000";
char g_usRev1Text_warpLevel4Activated[24] = "warp level 4 activated\000";
char g_usRev1Text_warpLevel5Activated[24] = "warp level 5 activated\000";
char g_usRev1Text_warpLevel6Activated[24] = "warp level 6 activated\000";
char g_usRev1Text_warpQueenBossActivated[28] = "warp queen boss activated\000\000";
char g_usRev1Text_warpBlindBossActivated[32] = "warp blind one boss activated\000\000";
char g_usRev1Text_warpMotherBossActivated[28] = "warp mother boss activated\000";
char g_usRev1Text_warpPrimagenBossActivated[32] = "warp primagen boss activated\000\000\000";
char g_usRev1Text_warpCreditsActivated[24] = "warp credits activated\000";
char g_usRev1Text_invincibilityOn[28] = "invincibility         :  on";
char g_usRev1Text_invincibilityOff[28] = "invincibility         : off";
char g_usRev1Text_infiniteLivesOn[28] = "infinite lives        :  on";
char g_usRev1Text_infiniteLivesOff[28] = "infinite lives        : off";
char g_usRev1Text_allWeaponsOn[28] = "all weapons           :  on";
char g_usRev1Text_allWeaponsOff[28] = "all weapons           : off";
char g_usRev1Text_unlimitedAmmoOn[28] = "unlimited ammo        :  on";
char g_usRev1Text_unlimitedAmmoOff[28] = "unlimited ammo        : off";
char g_usRev1Text_allSpecialObjectsOn[28] = "all special objects   :  on";
char g_usRev1Text_allSpecialObjectsOff[28] = "all special objects   : off";
char g_usRev1Text_bigHeadModeOn[28] = "big head mode         :  on";
char g_usRev1Text_bigHeadModeOff[28] = "big head mode         : off";
char g_usRev1Text_tinyModeOn[28] = "tiny mode             :  on";
char g_usRev1Text_tinyModeOff[28] = "tiny mode             : off";
char g_usRev1Text_stickModeOn[28] = "stick mode            :  on";
char g_usRev1Text_stickModeOff[28] = "stick mode            : off";
char g_usRev1Text_bigHandsFeetModeOn[28] = "big hands / feet mode :  on";
char g_usRev1Text_bigHandsFeetModeOff[28] = "big hands / feet mode : off";
char g_usRev1Text_penAndInkModeOn[28] = "pen and ink mode      :  on";
char g_usRev1Text_penAndInkModeOff[28] = "pen and ink mode      : off";
char g_usRev1Text_gouraudModeOn[28] = "gouraud mode          :  on";
char g_usRev1Text_gouraudModeOff[28] = "gouraud mode          : off";
char g_usRev1Text_juansCheatOn[28] = "juans cheat           :  on";
char g_usRev1Text_juansCheatOff[28] = "juans cheat           : off";
char g_usRev1Text_zachAttackCheatOn[28] = "zach attack cheat     :  on";
char g_usRev1Text_zachAttackCheatOff[28] = "zach attack cheat     : off";
char g_usRev1Text_allMapOn[28] = "all map               :  on";
char g_usRev1Text_allMapOff[28] = "all map               : off";
char g_usRev1Text_blackoutOn[28] = "blackout              :  on";
char g_usRev1Text_blackoutOff[28] = "blackout              : off";
char g_usRev1Text_frootyStripesOn[28] = "frooty stripes        :  on";
char g_usRev1Text_frootyStripesOff[28] = "frooty stripes        : off";
char g_usRev1Text_warpPortOfAdia[28] = "warp:          port of adia";
char g_usRev1Text_warpRiverOfSouls[28] = "warp:        river of souls";
char g_usRev1Text_warpDeathMarshes[28] = "warp:         death marshes";
char g_usRev1Text_warpLairOfThe[28] = "warp:lair of the blind ones";
char g_usRev1Text_warpHiveOfThe[28] = "warp:   hive of the mantids";
char g_usRev1Text_warpPrimagenSLightship[28] = "warp:  primagen's lightship";
char g_usRev1Text_warpQueenBoss[28] = "warp:            queen boss";
char g_usRev1Text_warpBlindBossMenuLine[28] = "warp:        blind one boss";
char g_usRev1Text_warpMotherBoss[28] = "warp:           mother boss";
char g_usRev1Text_warpPrimagenBoss[28] = "warp:         primagen boss";
char g_usRev1Text_warpCredits[28] = "warp:               credits";
char g_usRev1Text_youFragged[12] = "you fragged";
char g_usRev1Text_youTaggedOptionLabel[12] = "you tagged\000";
char g_usRev1Text_totals[8] = "totals\000";
TotalsPanels g_usRev1TotalsPanels = {
    {
        "one     :0000                \000\000",
        "two     :0000                \000\000",
        "three   :0000                \000\000",
        "four    :0000                \000\000",
        "tags    :0000                \000\000",
        "frags   :0000                \000\000",
        "deaths  :0000                \000\000",
        "suicides:0000\000\000",
    },
    {
        {
            "one     :0000                \000\000",
            "two     :0000                \000\000",
            "three   :0000                \000\000",
            "four    :0000                \000\000",
            "tags    :0000\000\000",
            "frags   :0000\000\000",
            "deaths  :0000\000\000",
            "suicides:0000\000\000",
        },
        {
            "one     :0000                \000\000",
            "two     :0000                \000\000",
            "three   :0000                \000\000",
            "four    :0000                \000\000",
            "tags    :0000\000\000",
            "frags   :0000\000\000",
            "deaths  :0000\000\000",
            "suicides:0000\000\000",
        },
        {
            "one     :0000                \000\000",
            "two     :0000                \000\000",
            "three   :0000                \000\000",
            "four    :0000                \000\000",
            "tags    :0000\000\000",
            "frags   :0000\000\000",
            "deaths  :0000\000\000",
            "suicides:0000\000\000",
        },
    },
};
char g_usRev1Text_player1[12] = "player 1\000\000\000";
char g_usRev1Text_player2[12] = "player 2\000\000\000";
char g_usRev1Text_player3[12] = "player 3\000\000\000";
char g_usRev1Text_player4[12] = "player 4\000\000\000";
char g_usRev1Text_single[8] = "single\000";
char g_usRev1Text_newGame[12] = "new game\000\000\000";
char g_usRev1Text_loadSinglePlayerMenuOptionLabel[8] = "load\000\000\000";
char g_usRev1Text_multi[8] = "multi\000\000";
char g_usRev1Text_deathmatch[12] = "deathmatch\000";
char g_usRev1Text_selectGameType[20] = "select game type\000\000\000";
char g_usRev1Text_bloodLust[12] = "blood lust\000";
char g_usRev1Text_bloodLustOptionLabel[12] = "blood lust\000";
char g_usRev1Text_timedGameNone[24] = "timed game       :none\000";
char g_usRev1Text_fragLimitNone[24] = "frag limit       :none\000";
char g_usRev1Text_levelRandom[24] = "level:          random\000";
char g_usRev1Text_levelExperimentata[24] = "level:   experimentata\000";
char g_usRev1Text_levelMoonlitMayhem[24] = "level:  moonlit mayhem\000";
char g_usRev1Text_levelCloseQuartered[24] = "level: close quartered\000";
char g_usRev1Text_levelVulcanSForge[24] = "level:  vulcan's forge\000";
char g_usRev1Text_levelTeleportastic[24] = "level:   teleportastic\000";
char g_usRev1Text_levelMirrororrim[24] = "level:     mirrororrim\000";
char g_usRev1Text_levelFishInA[24] = "level:fish in a barrel\000";
char g_usRev1Text_levelH2Whoa[24] = "level:       h 2 whoa!\000";
char g_usRev1Text_levelEscheria[24] = "level:        escheria\000";
char g_usRev1Text_levelMoshCrypt[24] = "level:      mosh crypt\000";
char g_usRev1Text_levelSquaresCubed[24] = "level:   squares cubed\000";
char g_usRev1Text_levelCrazyEight[24] = "level:     crazy eight\000";
char g_usRev1Text_levelBullseye[24] = "level:        bullseye\000";
char g_usRev1Text_textureSetCastle[24] = "texture set:    castle\000";
char g_usRev1Text_textureSetSteelMill[24] = "texture set:steel mill\000";
char g_usRev1Text_textureSetOakFort[24] = "texture set:  oak fort\000";
char g_usRev1Text_textureSetCatacombs[24] = "texture set: catacombs\000";
char g_usRev1Text_textureSetJailhouse[24] = "texture set: jailhouse\000";
char g_usRev1Text_textureSetBigCity[24] = "texture set:  big city\000";
char g_usRev1Text_textureSetRedDragon[24] = "texture set:red dragon\000";
char g_usRev1Text_textureSetPaintball[24] = "texture set: paintball\000";
char g_usRev1Text_textureSetMrHappy[24] = "texture set:  mr happy\000";
char g_usRev1Text_crosshairsOn[24] = "crosshairs       :  on\000";
char g_usRev1Text_crosshairsOff[24] = "crosshairs       : off\000";
char g_usRev1Text_startGame[12] = "start game\000";
char g_usRev1Text_goBackDeathmatchSetupOptionLabel[8] = "go back";
char g_usRev1Text_fragTag[12] = "frag tag\000\000\000";
char g_usRev1Text_fragTagOptionLabel[12] = "frag tag\000\000\000";
char g_usRev1Text_tagLimitNone[24] = "tag limit        :none\000";
char g_usRev1Text_levelMadhouse[24] = "level:       madhouse!\000";
char g_usRev1Text_levelSnap[24] = "level:            snap\000";
char g_usRev1Text_levelSneaksNLadders[24] = "level:sneaks n ladders\000";
char g_usRev1Text_levelPrimattica[24] = "level:      primattica\000";
char g_usRev1Text_levelCrossfire[24] = "level:       crossfire\000";
char g_usRev1Text_levelYNG[24] = "level:  y.n.g.w.t.s.f.\000";
char g_usRev1Text_teamBlood[12] = "team blood\000";
char g_usRev1Text_customizeWeapons[20] = "customize weapons\000\000";
char g_usRev1Text_chargeDartRifleOn[24] = "charge dart rifle : on\000";
char g_usRev1Text_chargeDartRifleOff[24] = "charge dart rifle :off\000";
char g_usRev1Text_firestormOn[24] = "firestorm         : on\000";
char g_usRev1Text_firestormOff[24] = "firestorm         :off\000";
char g_usRev1Text_assaultRifleOn[24] = "assault rifle     : on\000";
char g_usRev1Text_assaultRifleOff[24] = "assault rifle     :off\000";
char g_usRev1Text_plasmaRifleOn[24] = "plasma rifle      : on\000";
char g_usRev1Text_plasmaRifleOff[24] = "plasma rifle      :off\000";
char g_usRev1Text_cerebralBoreOn[24] = "cerebral bore     : on\000";
char g_usRev1Text_cerebralBoreOff[24] = "cerebral bore     :off\000";
char g_usRev1Text_grenadeLauncherOn[24] = "grenade launcher  : on\000";
char g_usRev1Text_grenadeLauncherOff[24] = "grenade launcher  :off\000";
char g_usRev1Text_scorpionLauncherOn[24] = "scorpion launcher : on\000";
char g_usRev1Text_scorpionLauncherOff[24] = "scorpion launcher :off\000";
char g_usRev1Text_torpedoLauncherOn[24] = "torpedo launcher  : on\000";
char g_usRev1Text_torpedoLauncherOff[24] = "torpedo launcher  :off\000";
char g_usRev1Text_training[12] = "training\000\000\000";
char g_usRev1Text_levelRandomOptionLabel[24] = "level      :    random\000";
char g_usRev1Text_levelArchery[24] = "level      :   archery\000";
char g_usRev1Text_levelShooting[24] = "level      :  shooting\000";
char g_usRev1Text_levelDecathalon[24] = "level      :decathalon\000";
char g_usRev1Text_noOfLaps[24] = "no of laps :          \000";
char g_usRev1Text_startGameOptionLabel[12] = "start game\000";
char g_usRev1Text_goBackTrainingSetupOptionLabel[8] = "go back";
char g_usRev1Text_loadTitleMenuOptionLabel[8] = "load\000\000\000";
char g_usRev1Text_optionsOptionLabel[8] = "options";
char g_usRev1Text_cheatsOptionLabel[8] = "cheats\000";
char g_usRev1Text_checkPoint[12] = "check point";
char g_usRev1Text_savePoint[12] = "save point\000";
char g_usRev1Text_soundOptions[16] = "sound options\000\000";
char g_usRev1Text_musicVolumeOff[24] = "music volume  :   off\000\000";
char g_usRev1Text_musicVolumeMax[24] = "music volume  :   max\000\000";
char g_usRev1Text_musicVolumeNorm[24] = "music volume  :  norm\000\000";
char g_usRev1Text_musicVolume[24] = "music volume  :      \000\000";
char g_usRev1Text_sfxVolumeOff[24] = "sfx volume    :   off\000\000";
char g_usRev1Text_sfxVolumeMax[24] = "sfx volume    :   max\000\000";
char g_usRev1Text_sfxVolumeNorm[24] = "sfx volume    :  norm\000\000";
char g_usRev1Text_sfxVolume[24] = "sfx volume    :      \000\000";
char g_usRev1Text_speechVolumeOff[24] = "speech volume :   off\000\000";
char g_usRev1Text_speechVolumeMax[24] = "speech volume :   max\000\000";
char g_usRev1Text_speechVolumeNorm[24] = "speech volume :  norm\000\000";
char g_usRev1Text_speechVolume[24] = "speech volume :      \000\000";
char g_usRev1Text_musicNone[24] = "music         :  none\000\000";
char g_usRev1Text_music[24] = "music         :      \000\000";
char g_usRev1Text_indexNone[24] = "index        :  none\000\000\000";
char g_usRev1Text_speechNone[24] = "speech       :  none\000\000\000";
char g_usRev1Text_missionComplete[20] = "mission complete.\000\000";
char g_usRev1Text_missionFailedOptionLabel[16] = "mission failed.";
char g_usRev1Text_defendTheTotem[20] = "defend the totem\000\000\000";
char g_usRev1Text_playerSpeed[24] = "player speed :        \000";
char g_usRev1Text_playerSpeedDefault[24] = "player speed : default\000";
char g_usRev1Text_default[8] = "default";
char g_usRev1Text_lowHealth[12] = "low health\000";
#endif

/* MENU_DIGIT_LABELS_DATA.CPP */
#if defined(VERSION_US_REV1)
char ragewars_menu_digit_labels_us_rev1_StorageWords[44] = " \000\000\0000\000\000\0001\000\000\0002\000\000\0003\000\000\0004\000\000\0005\000\000\0006\000\000\0007\000\000\0008\000\000\0009\000\000\000";
#endif

/* CREDITS_LINES_DATA.CPP */
#if defined(VERSION_US_REV1)

void *ragewars_credits_lines_us_rev1_StorageWords[264] = {
    s_rageWarsTeamText, g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[1036], (void *)&g_projectLeadQaCreditsTextPool[1024],
    g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[1008], (void *)&g_projectLeadQaCreditsTextPool[980], g_debuglinkTextBytes,
    g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[968], (void *)&g_projectLeadQaCreditsTextPool[952], g_debuglinkTextBytes,
    g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[932], (void *)&g_projectLeadQaCreditsTextPool[904], (void *)&g_projectLeadQaCreditsTextPool[876],
    (void *)&g_projectLeadQaCreditsTextPool[840], (void *)&g_projectLeadQaCreditsTextPool[816], (void *)&g_projectLeadQaCreditsTextPool[792], (void *)&g_projectLeadQaCreditsTextPool[768],
    (void *)&g_projectLeadQaCreditsTextPool[728], (void *)&g_projectLeadQaCreditsTextPool[692], (void *)&g_projectLeadQaCreditsTextPool[656], (void *)&g_projectLeadQaCreditsTextPool[628],
    (void *)&g_projectLeadQaCreditsTextPool[592], (void *)&g_projectLeadQaCreditsTextPool[568], (void *)&g_projectLeadQaCreditsTextPool[528], (void *)&g_projectLeadQaCreditsTextPool[492],
    g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[452], g_debuglinkTextBytes,
    (void *)&g_projectLeadQaCreditsTextPool[436], (void *)&g_projectLeadQaCreditsTextPool[420], (void *)&g_projectLeadQaCreditsTextPool[404], (void *)&g_projectLeadQaCreditsTextPool[392],
    (void *)&g_projectLeadQaCreditsTextPool[368], g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[324],
    g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[308], (void *)&g_projectLeadQaCreditsTextPool[296], (void *)&g_projectLeadQaCreditsTextPool[284],
    (void *)&g_projectLeadQaCreditsTextPool[272], (void *)&g_projectLeadQaCreditsTextPool[256], g_debuglinkTextBytes, g_debuglinkTextBytes,
    (void *)&g_projectLeadQaCreditsTextPool[212], g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[192], (void *)&g_projectLeadQaCreditsTextPool[176],
    g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[136], g_debuglinkTextBytes,
    (void *)&g_projectLeadQaCreditsTextPool[120], (void *)&g_projectLeadQaCreditsTextPool[104], (void *)&g_projectLeadQaCreditsTextPool[92], g_debuglinkTextBytes,
    g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[52], g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[40],
    (void *)&g_projectLeadQaCreditsTextPool[28], g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[12], g_projectLeadQaCreditsTextPool,
    g_debuglinkTextBytes, g_debuglinkTextBytes, s_testersText, g_debuglinkTextBytes,
    (void *)&g_productDevelopmentCreditsTextPool[1036], (void *)&g_productDevelopmentCreditsTextPool[1020], (void *)&g_productDevelopmentCreditsTextPool[1004], (void *)&g_productDevelopmentCreditsTextPool[988],
    (void *)&g_productDevelopmentCreditsTextPool[976], (void *)&g_productDevelopmentCreditsTextPool[964], (void *)&g_productDevelopmentCreditsTextPool[948], g_debuglinkTextBytes,
    g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[908], g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[884],
    (void *)&g_productDevelopmentCreditsTextPool[860], (void *)&g_productDevelopmentCreditsTextPool[840], (void *)&g_productDevelopmentCreditsTextPool[812], (void *)&g_productDevelopmentCreditsTextPool[776],
    (void *)&g_productDevelopmentCreditsTextPool[744], (void *)&g_productDevelopmentCreditsTextPool[708], (void *)&g_productDevelopmentCreditsTextPool[684], (void *)&g_productDevelopmentCreditsTextPool[656],
    (void *)&g_productDevelopmentCreditsTextPool[620], g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[576],
    g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[544], (void *)&g_productDevelopmentCreditsTextPool[528], g_debuglinkTextBytes,
    (void *)&g_productDevelopmentCreditsTextPool[508], (void *)&g_productDevelopmentCreditsTextPool[492], g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[460],
    (void *)&g_productDevelopmentCreditsTextPool[440], g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[420], (void *)&g_projectLeadQaCreditsTextPool[192],
    g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[404], (void *)&g_projectLeadQaCreditsTextPool[120], g_debuglinkTextBytes,
    (void *)&g_productDevelopmentCreditsTextPool[372], (void *)&g_productDevelopmentCreditsTextPool[356], g_debuglinkTextBytes, g_debuglinkTextBytes,
    (void *)&g_productDevelopmentCreditsTextPool[316], g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[276], (void *)&g_productDevelopmentCreditsTextPool[264],
    g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[236], (void *)&g_productDevelopmentCreditsTextPool[224], g_debuglinkTextBytes,
    (void *)&g_productDevelopmentCreditsTextPool[204], (void *)&g_productDevelopmentCreditsTextPool[188], g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[156],
    (void *)&g_productDevelopmentCreditsTextPool[136], g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[88],
    g_debuglinkTextBytes, (void *)&g_productDevelopmentCreditsTextPool[44], g_productDevelopmentCreditsTextPool, g_debuglinkTextBytes,
    g_debuglinkTextBytes, s_producerText, (void *)&g_turnoverCreditsTextPool[564], g_debuglinkTextBytes,
    g_debuglinkTextBytes, (void *)&g_turnoverCreditsTextPool[544], (void *)&g_turnoverCreditsTextPool[528], (void *)&g_turnoverCreditsTextPool[512],
    g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_turnoverCreditsTextPool[488], (void *)&g_turnoverCreditsTextPool[472],
    g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_projectLeadQaCreditsTextPool[40], (void *)&g_turnoverCreditsTextPool[452],
    g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_turnoverCreditsTextPool[436], (void *)&g_turnoverCreditsTextPool[424],
    (void *)&g_turnoverCreditsTextPool[412], g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_turnoverCreditsTextPool[392],
    (void *)&g_turnoverCreditsTextPool[380], (void *)&g_turnoverCreditsTextPool[364], g_debuglinkTextBytes, g_debuglinkTextBytes,
    (void *)&g_turnoverCreditsTextPool[348], (void *)&g_turnoverCreditsTextPool[336], (void *)&g_turnoverCreditsTextPool[320], g_debuglinkTextBytes,
    g_debuglinkTextBytes, (void *)&g_turnoverCreditsTextPool[304], (void *)&g_turnoverCreditsTextPool[292], (void *)&g_turnoverCreditsTextPool[280],
    g_debuglinkTextBytes, g_debuglinkTextBytes, s_testersText, (void *)&g_turnoverCreditsTextPool[264],
    (void *)&g_turnoverCreditsTextPool[248], (void *)&g_turnoverCreditsTextPool[236], (void *)&g_turnoverCreditsTextPool[220], (void *)&g_turnoverCreditsTextPool[204],
    (void *)&g_turnoverCreditsTextPool[188], (void *)&g_turnoverCreditsTextPool[172], (void *)&g_turnoverCreditsTextPool[160], (void *)&g_turnoverCreditsTextPool[144],
    (void *)&g_turnoverCreditsTextPool[132], (void *)&g_turnoverCreditsTextPool[116], (void *)&g_turnoverCreditsTextPool[100], (void *)&g_turnoverCreditsTextPool[84],
    (void *)&g_turnoverCreditsTextPool[72], g_debuglinkTextBytes, (void *)&g_turnoverCreditsTextPool[48], (void *)&g_turnoverCreditsTextPool[36],
    g_debuglinkTextBytes, (void *)&g_turnoverCreditsTextPool[16], g_turnoverCreditsTextPool, g_debuglinkTextBytes,
    g_techniciansCreditsText, (void *)&g_expansionPakNoticeTextPool[1244], (void *)&g_expansionPakNoticeTextPool[1228], (void *)&g_expansionPakNoticeTextPool[1212],
    (void *)&g_expansionPakNoticeTextPool[1196], g_debuglinkTextBytes, (void *)&g_expansionPakNoticeTextPool[1168], (void *)&g_expansionPakNoticeTextPool[1156],
    g_debuglinkTextBytes, (void *)&g_expansionPakNoticeTextPool[1132], (void *)&g_expansionPakNoticeTextPool[1116], (void *)&g_expansionPakNoticeTextPool[1100],
    g_debuglinkTextBytes, (void *)&g_expansionPakNoticeTextPool[1088], (void *)&g_expansionPakNoticeTextPool[1068], g_debuglinkTextBytes,
    (void *)&g_expansionPakNoticeTextPool[1040], (void *)&g_expansionPakNoticeTextPool[1024], g_debuglinkTextBytes, (void *)&g_expansionPakNoticeTextPool[1004],
    (void *)&g_expansionPakNoticeTextPool[992], g_debuglinkTextBytes, (void *)&g_expansionPakNoticeTextPool[976], (void *)&g_expansionPakNoticeTextPool[964],
    g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_expansionPakNoticeTextPool[924], g_debuglinkTextBytes,
    (void *)&g_expansionPakNoticeTextPool[888], (void *)&g_expansionPakNoticeTextPool[864], (void *)&g_expansionPakNoticeTextPool[836], (void *)&g_expansionPakNoticeTextPool[808],
    (void *)&g_expansionPakNoticeTextPool[780], (void *)&g_expansionPakNoticeTextPool[752], g_debuglinkTextBytes, (void *)&g_expansionPakNoticeTextPool[712],
    (void *)&g_expansionPakNoticeTextPool[696], (void *)&g_expansionPakNoticeTextPool[664], (void *)&g_expansionPakNoticeTextPool[628], (void *)&g_expansionPakNoticeTextPool[596],
    (void *)&g_expansionPakNoticeTextPool[560], (void *)&g_expansionPakNoticeTextPool[528], (void *)&g_expansionPakNoticeTextPool[492], (void *)&g_expansionPakNoticeTextPool[456],
    (void *)&g_expansionPakNoticeTextPool[436], (void *)&g_expansionPakNoticeTextPool[396], (void *)&g_expansionPakNoticeTextPool[380], (void *)&g_expansionPakNoticeTextPool[360],
    (void *)&g_expansionPakNoticeTextPool[324], (void *)&g_expansionPakNoticeTextPool[292], (void *)&g_expansionPakNoticeTextPool[252], (void *)&g_expansionPakNoticeTextPool[216],
    (void *)&g_expansionPakNoticeTextPool[188], (void *)&g_expansionPakNoticeTextPool[152], (void *)&g_expansionPakNoticeTextPool[140], (void *)&g_expansionPakNoticeTextPool[112],
    (void *)&g_expansionPakNoticeTextPool[96], g_debuglinkTextBytes, g_debuglinkTextBytes, g_debuglinkTextBytes,
    g_debuglinkTextBytes, g_debuglinkTextBytes, g_debuglinkTextBytes, g_debuglinkTextBytes,
    g_debuglinkTextBytes, g_debuglinkTextBytes, (void *)&g_expansionPakNoticeTextPool[56], 0,
};
#endif
