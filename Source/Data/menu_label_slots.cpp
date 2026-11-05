#include "Data/rest_source_records.h"
#include "Constants/credits_lines_data.h"
#include "Constants/pak_ok_label_data.h"
#include "Menu_label_slots/menu_label_slots.h"
#include "Constants/hit_feedback_and_edit_text.h"
#include "Constants/g_saveloadhealthammomenutextpool.h"

/* MENU_LABEL_SLOTS.CPP */
#if defined(VERSION_US_REV1)
#include "Constants/k_menulabeltextpointers.h"
void *k_menuLabelTextDirectory[6] = {
    g_SkyPostscaledscreenmessageEncodedBytes, k_menuLabelTextPointers, (void *)(k_menuLabelTextPointers + 16), (void *)(k_menuLabelTextPointers + 20),
    (void *)(k_menuLabelTextPointers + 24), (void *)(k_menuLabelTextPointers + 32),
};
#endif

#if defined(VERSION_US_REV1)
#include "Frontend/controllerpak_message_pool.h"
void *g_pickupLabelDirectory[103] = {
    s_itemMultiplayerAchievement_2Health, g_usRev1Text_10Health, g_usRev1Text_15Health, g_usRev1Text_25Health,
    g_usRev1Text_50Health, g_usRev1Text_fullHealth, s_itemMultiplayerAchievement_UltraHealth, g_usRev1Text_1LifeForce,
    g_usRev1Text_10LifeForce, g_usRev1Text_invincibility, g_usRev1Text_planeWalker, s_itemMultiplayerAchievement_Flashlight,
    g_usRev1Text_flashlightBattery, s_itemMultiplayerAchievement_InfraredGoggles, s_itemMultiplayerAchievement_BreathOfLife, s_itemMultiplayerAchievement_EyeOfTruth,
    s_itemMultiplayerAchievement_LeapOfFaith, s_itemMultiplayerAchievement_Whispers, s_itemMultiplayerAchievement_HeartOfFire, s_itemMultiplayerAchievement_BlueEagleFeather,
    g_usRev1Text_greyEagleFeather, s_itemMultiplayerAchievement_BrownEagleFeather, g_usRev1Text_purpleEagleFeather, s_itemMultiplayerAchievement_RedEagleFeather,
    g_usRev1Text_nukeWeaponPart, s_itemMultiplayerAchievement_Retaliation, s_itemMultiplayerAchievement_FlagWasClaimed, s_itemMultiplayerAchievement_FlagWasCaptured,
    s_itemMultiplayerAchievement_FlagReturned, s_itemMultiplayerAchievement_ThePowerIsYours, s_itemMultiplayerAchievement_FunctionNotAvailable, s_itemMultiplayerAchievement_Warhammer,
    s_itemMultiplayerAchievement_RaptorClaw, s_itemMultiplayerAchievement_MiteBite, s_itemMultiplayerAchievement_Boomerang, s_itemMultiplayerAchievement_TekCrossbow,
    s_itemMultiplayerAchievement_Mag60, s_itemMultiplayerAchievement_Shotgun, s_itemMultiplayerAchievement_AssaultRifle, s_itemMultiplayerAchievement_Minigun,
    s_itemMultiplayerAchievement_PlasmaRifle, s_itemMultiplayerAchievement_FreezeGun, s_itemMultiplayerAchievement_FlareGun, s_itemMultiplayerAchievement_Grenades,
    s_itemMultiplayerAchievement_Scorpion, g_usRev1Text_napalmGel, s_itemMultiplayerAchievement_Emaciator, s_itemMultiplayerAchievement_Inflator,
    g_usRev1Text_chestBurster, g_usRev1Text_cerebralBore, s_itemMultiplayerAchievement_PfmMine, s_itemMultiplayerAchievement_IronClaw,
    s_itemMultiplayerAchievement_TeleportMine, s_itemMultiplayerAchievement_SentryTurret, s_itemMultiplayerAchievement_AttractRemoved, s_itemMultiplayerAchievement_AttractMarked,
    g_usRev1Text_repulseMarked, g_usRev1Text_slowTime, g_usRev1Text_blastShield, g_usRev1Text_regeneration,
    g_usRev1Text_petrify, g_usRev1Text_damageReversal, g_usRev1Text_invisibility, g_usRev1Text_lifeForceVampire,
    g_usRev1Text_speedBurst, g_usRev1Text_teleportation, g_usRev1Text_teleportedToSafety, s_itemMultiplayerAchievement_MassiveDamage,
    s_itemMultiplayerAchievement_Invunerability, s_itemMultiplayerAchievement_BulletShield, s_itemMultiplayerAchievement_EnergyAbsorption, g_usRev1Text_somethingElse,
    g_usRev1Text_shield, g_usRev1Text_joinedTeamCoyote, g_usRev1Text_joinedTeamBear, g_usRev1Text_joinedTeamCougar,
    g_usRev1Text_joinedTeamViper, g_usRev1Text_youFraggedYourself, s_itemMultiplayerAchievement_MangledByS, g_usRev1Text_fraggedByS,
    g_usRev1Text_smackedByS, g_usRev1Text_sObliteratedYou, g_usRev1Text_sButcheredYou, g_usRev1Text_sCrushedYou,
    g_usRev1Text_poundedByS, g_usRev1Text_yourOtherLeft, g_usRev1Text_oops, g_usRev1Text_badMove,
    g_usRev1Text_umWatchYourStep, s_itemMultiplayerAchievement_Munch, s_itemMultiplayerAchievement_OopsCopy, s_itemMultiplayerAchievement_YouWereBested,
    s_itemMultiplayerAchievement_EmbryoImplanted, s_itemMultiplayerAchievement_EmbryoDestroyed, s_itemMultiplayerAchievement_SmackS, s_itemMultiplayerAchievement_OrFindPowerCore,
    s_itemMultiplayerAchievement_EnergyRounds, s_itemMultiplayerAchievement_EnergyRoundsCopy, s_itemMultiplayerAchievement_BulletRounds, s_itemMultiplayerAchievement_BulletRoundsCopy,
    g_usRev1Text_explosiveRounds, g_usRev1Text_explosiveRoundsPickupLabel, g_usRev1Text_ammoPack,
};
#endif

#if defined(VERSION_US_REV1)

#include "Constants/menu_on_label_data.h"
#include "Constants/g_colororientationresolutiontextpool.h"
#include "Constants/menu_no_label_data.h"
#include "Constants/g_difficultycontrollermenutextpool.h"
void *g_itemLabelSlots[187] = {
    g_usRev1Text_bullet, g_usRev1Text_energyRound, g_usRev1Text_explosiveRound, g_usRev1Text_cerebralBoreItemLabel,
    g_usRev1Text_pfmMine, g_usRev1Text_sentryTurret, g_usRev1Text_ironClaw, s_itemMultiplayerAchievement_TeleportMineCopy,
    g_usRev1Text_novice, s_itemMultiplayerAchievement_Newcomer, s_itemMultiplayerAchievement_Grunt, g_usRev1Text_scout,
    g_usRev1Text_brave, s_itemMultiplayerAchievement_Tracker, g_usRev1Text_hunter, s_itemMultiplayerAchievement_Warrior,
    g_usRev1Text_darkling, g_usRev1Text_seeker, s_itemMultiplayerAchievement_Assassin, g_usRev1Text_bane,
    g_usRev1Text_warlord, g_usRev1Text_deathwind, g_usRev1Text_conqueror, g_usRev1Text_master,
    g_usRev1Text_tyrant, g_usRev1Text_warslave, g_usRev1Text_godhand, g_usRev1Text_chieftain,
    g_usRev1Text_empty, s_itemMultiplayerAchievement_NewPlayer, g_usRev1Text_turok, g_usRev1Text_warrior,
    g_usRev1Text_masterItemLabel, g_usRev1Text_adon, g_usRev1Text_seekerItemLabel, g_usRev1Text_huntress,
    g_usRev1Text_campain, g_usRev1Text_slaver, g_usRev1Text_tyrantItemLabel, g_usRev1Text_fireborn,
    g_usRev1Text_icelord, g_usRev1Text_entrail, g_usRev1Text_mites, g_usRev1Text_compies,
    g_usRev1Text_teddies, g_usRev1Text_juggnaut, g_usRev1Text_sloth, s_itemMultiplayerAchievement_Mauler,
    g_usRev1Text_drone, g_usRev1Text_grunt, g_usRev1Text_slave, s_itemMultiplayerAchievement_Soldier,
    g_usRev1Text_captain, g_usRev1Text_king, g_usRev1Text_bastille, g_usRev1Text_talSet,
    g_usRev1Text_syra, g_usRev1Text_symbiont, g_usRev1Text_guardian, g_usRev1Text_ravage,
    g_usRev1Text_cyclops, g_usRev1Text_lorddead, g_usRev1Text_maggot, g_usRev1Text_vile,
    g_usRev1Text_elite, g_usRev1Text_biobot, g_usRev1Text_killbot, g_usRev1Text_death,
    g_usRev1Text_reaper, s_itemMultiplayerAchievement_Maw, g_usRev1Text_raptor, g_usRev1Text_slag,
    g_usRev1Text_claw, g_usRev1Text_warclubs, g_usRev1Text_turokItemLabel, g_usRev1Text_mantidDrone,
    g_usRev1Text_campaigner, g_usRev1Text_firebornItemLabel, g_usRev1Text_mantidSoldier, g_usRev1Text_adonItemLabel,
    g_usRev1Text_lordOfTheDead, g_usRev1Text_eliteGuard, g_usRev1Text_guardianItemLabel, g_usRev1Text_juggernaut,
    g_usRev1Text_oblivionSpawn, g_usRev1Text_bastilleItemLabel, g_usRev1Text_syraItemLabel, g_usRev1Text_symbiontItemLabel,
    g_usRev1Text_talSetItemLabel, g_usRev1Text_raptorItemLabel, g_usRev1Text_mantidMites, g_usRev1Text_captureTheFlagD,
    g_usRev1Text_captureTheFlagD2, g_usRev1Text_acquireDTeamCaptures, g_usRev1Text_tagTheMonkeyD, g_usRev1Text_tagTheMonkeyD2,
    g_usRev1Text_acquireDCreatureTags, g_usRev1Text_acquireDFrag, g_usRev1Text_acquireDFrags, g_usRev1Text_acquireDTeamFrag,
    g_usRev1Text_acquireDTeamFrags, g_usRev1Text_in02dSecondsOr, g_usRev1Text_inDMinuteAnd, g_usRev1Text_inDMinutesAnd,
    g_usRev1Text_inDMinuteOr, g_usRev1Text_inDMinutesOr, g_usRev1Text_withDLife, g_usRev1Text_withDLives,
    g_usRev1Text_defeatS, g_usRev1Text_defeatBothSAnd, g_usRev1Text_everyManForThemselves, g_usRev1Text_achievementOnProvingGrounds,
    g_usRev1Text_achievementOnBasicTraining, g_usRev1Text_achievementOnCrossroads, g_usRev1Text_achievementOnGrimRetreat, g_usRev1Text_achievementOnCathedral,
    g_usRev1Text_achievementOnFallout, g_usRev1Text_achievementOnBoxedSet, g_usRev1Text_achievementOnDireStraight, g_usRev1Text_achievementOnPrey,
    g_usRev1Text_achievementOnWarehouse, s_itemMultiplayerAchievement_AchievementOnWaterTemple, g_usRev1Text_achievementOnBombShelter, g_usRev1Text_achievementOnTempered,
    g_usRev1Text_achievementOnEarthTemple, g_usRev1Text_achievementOnFireTemple, g_usRev1Text_achievementOnMystic, g_usRev1Text_achievementOnBottleneck,
    g_usRev1Text_achievementOnTightrope, g_usRev1Text_achievementOnThePit, g_usRev1Text_achievementOnLeapOf, g_usRev1Text_achievementOnWickedDance,
    g_usRev1Text_achievementOnBunker, g_usRev1Text_achievementOnAmphitheater, g_usRev1Text_achievementOnFireWalker, g_usRev1Text_achievementOnCrypts,
    g_usRev1Text_achievementOnBreakdown, g_usRev1Text_achievementOnRetaliation, g_usRev1Text_achievementOnHopeless, g_usRev1Text_achievementOnMatrix,
    g_usRev1Text_achievementOnFathom, g_usRev1Text_achievementOnThePedestal, g_usRev1Text_achievementOnDefcon5, g_usRev1Text_achievementOnSpiritTemple,
    s_itemMultiplayerAchievement_AchievementOnStronghold, g_usRev1Text_achievementOnCourtyard, g_usRev1Text_achievementOnStarlight, g_usRev1Text_attained15FragsIn,
    g_usRev1Text_attained25FragsIn, g_usRev1Text_notGettingAnyFrags, g_usRev1Text_killingYourself5Times, g_usRev1Text_comingInLast,
    g_usRev1Text_totalFragAward, g_usRev1Text_totalBeingKilledAward, g_usRev1Text_sniping10PeopleIn, g_usRev1Text_notBeingKilledIn,
    g_usRev1Text_defeatedBastille, g_usRev1Text_defeatedSyra, g_usRev1Text_defeatedSymbiont, g_usRev1Text_defeatedTalSet,
    g_usRev1Text_beatingTheCooperativeScenario, g_usRev1Text_easy, g_usRev1Text_medium, g_usRev1Text_hard,
    g_usRev1Text_off, g_MenuOnLabelStorage, g_colorOrientationResolutionTextPool, g_usRev1Text_green,
    g_usRev1Text_horizontal, g_usRev1Text_vertical, g_usRev1Text_lorez, g_usRev1Text_hirez,
    g_usRev1Text_letterbox, g_MenuNoLabelStorage, g_difficultyControllerMenuTextPool, g_usRev1Text_noviceItemLabel,
    g_usRev1Text_easyItemLabel, g_usRev1Text_normal, g_usRev1Text_veteran, g_usRev1Text_expert,
    g_usRev1Text_arcade, g_usRev1Text_wheel, g_usRev1Text_tap, g_usRev1Text_mixed,
    g_usRev1Text_controllerD, g_usRev1Text_ctf, g_usRev1Text_tbl,
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/menu_abbreviations_data.h"
void *g_menuAbbreviationAndFtLabelSlots[2] = {
    g_MenuAbbreviationsStorage, g_usRev1Text_ft,
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/g_matchmodeandrewardtextpool.h"
void *g_matchOptionLabelSlots[88] = {
    g_matchModeAndRewardTextPool, g_usRev1Text_fragFest, g_usRev1Text_timeTrial, g_usRev1Text_playerD,
    g_usRev1Text_acquiredEagleTalisman1, g_usRev1Text_acquiredHalfEagleTalisman, g_usRev1Text_acquiredTheOtherEagle, g_usRev1Text_acquiredBearTalismanExplosive,
    g_usRev1Text_acquiredCoyoteTalismanBullet, g_usRev1Text_acquiredCougarTalismanEnergy, g_usRev1Text_acquiredViperTalismanHealth, g_usRev1Text_acquiredCooperativeTalisman,
    g_usRev1Text_acquiredMinigameIcon, g_usRev1Text_acquiredAssaultRifle, g_usRev1Text_acquiredAssaultRifleRapid, g_usRev1Text_acquiredTekCrossBow,
    g_usRev1Text_acquiredGrenadeLauncher, g_usRev1Text_acquiredGrenadeLauncherUpgrade, g_usRev1Text_acquiredPlasmaRifle, g_usRev1Text_acquiredPlasmaRifleScope,
    g_usRev1Text_acquiredAcidSpitAttack, g_usRev1Text_acquiredJumpClawAttack, g_usRev1Text_acquiredRadioactiveFlareGun, g_usRev1Text_acquiredRadioactiveFlareGunMatchOptionLabel,
    g_usRev1Text_acquiredScorpionLauncher, g_usRev1Text_acquiredScorpionLauncherMagnet, g_usRev1Text_acquiredFreezeGun, g_usRev1Text_acquiredFreezeGunUpgrade,
    g_usRev1Text_acquiredNapalmGel, g_usRev1Text_acquiredMag60Laser, g_usRev1Text_acquiredChestburster, g_usRev1Text_acquiredInflator,
    g_usRev1Text_acquiredInflatorUpgrade, g_usRev1Text_acquiredBoomerang, g_usRev1Text_acquiredBoomerangUpgrade, g_usRev1Text_acquiredMinigun,
    g_usRev1Text_acquiredMinigunPersonalShield, g_usRev1Text_acquiredShotgunStreetsweeperUpgrade, g_usRev1Text_acquiredEmaciator, g_usRev1Text_acquiredEmaciatorUpgrade,
    g_usRev1Text_acquiredWarhammerRocketUpgrade, g_usRev1Text_youHaveUnlockedS, g_usRev1Text_missionFailed, g_usRev1Text_itemPreviouslyAcquired,
    g_usRev1Text_team, g_usRev1Text_hit, g_usRev1Text_tags, g_usRev1Text_flags,
    g_usRev1Text_congratulationsYouHaveCompleted, g_usRev1Text_congratulationsYouHaveCompletedMatchOptionLabel, g_usRev1Text_english, g_usRev1Text_pistolClip10Rounds,
    g_usRev1Text_rifleClip10Rounds, g_usRev1Text_difficultyEasy, g_usRev1Text_difficultyNormal, g_usRev1Text_difficultyHard,
    g_usRev1Text_controlTypeExpert, g_usRev1Text_controlTypeArcade, g_usRev1Text_controlType, g_usRev1Text_controlSideLeft,
    g_usRev1Text_controlSideRight, g_usRev1Text_lookSpringOn, g_usRev1Text_lookSpringOff, g_usRev1Text_autoAimOn,
    g_usRev1Text_autoAimOff, g_usRev1Text_bloodColorOff, g_usRev1Text_bloodColorRed, g_usRev1Text_bloodColorGreen,
    g_usRev1Text_2PlyrLayoutHorz, g_usRev1Text_2PlyrLayoutVert, g_usRev1Text_opacityClear, g_usRev1Text_opacityOpaque,
    g_usRev1Text_opacity, g_usRev1Text_controlStickHorzNorm, g_usRev1Text_controlStickHorz, g_usRev1Text_controlStickVertNorm,
    g_usRev1Text_controlStickVert, g_usRev1Text_weaponSelectQuick, g_usRev1Text_weaponSelectNorm, g_usRev1Text_resolutionLoRez,
    g_usRev1Text_resolutionHiRez, g_usRev1Text_resolutionHiRezLb, g_usRev1Text_resolutionSmLoRez, g_usRev1Text_resolutionLoRezLb,
    g_usRev1Text_brightnessNorm, g_usRev1Text_brightness, g_usRev1Text_languageEnglish, g_usRev1Text_goBack,
};
#endif

#if defined(VERSION_US_REV1)

void *k_cheatMenuTextCells[22] = {
    g_usRev1Text_displayOptionsCells[0], g_usRev1Text_displayOptionsCells[1], g_usRev1Text_displayOptionsCells[2], g_usRev1Text_displayOptionsCells[3],
    g_usRev1Text_displayOptionsCells[4], g_usRev1Text_displayOptionsCells[5], g_usRev1Text_displayOptionsCells[6], g_usRev1Text_displayOptionsCells[7],
    g_usRev1Text_displayOptionsCells[8], g_usRev1Text_displayOptionsCells[9], g_usRev1Text_displayOptionsCells[10], g_usRev1Text_displayOptionsCells[11],
    g_usRev1Text_displayOptionsCells[12], g_usRev1Text_displayOptionsCells[13], g_usRev1Text_displayOptionsCells[14], g_usRev1Text_displayOptionsCells[15],
    g_usRev1Text_displayOptionsCells[16], g_usRev1Text_displayOptionsCells[17], g_usRev1Text_displayOptionsCells[18], g_usRev1Text_displayOptionsCells[19],
    g_usRev1Text_displayOptionsCells[20], g_usRev1Text_displayOptionsCells[21],
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/g_bloodscoremenutextpool.h"
void *g_inventoryLabelSlot[17] = {
    g_bloodScoreMenuTextPool, g_usRev1Text_blueBlood, g_usRev1Text_redBlood, g_usRev1Text_finalScore,
    g_usRev1Text_blueBloodScore, g_usRev1Text_redBloodScore, g_usRev1Text_pleaseWait, g_usRev1Text_paused,
    &g_bloodScoreMenuTextPool[120], g_usRev1Text_missionStatus, g_usRev1Text_missionObjectives, g_usRev1Text_inventory,
    g_usRev1Text_load, g_usRev1Text_options, g_usRev1Text_cheats, g_usRev1Text_quit,
    g_usRev1Text_inventoryInventoryLabel,
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/menu_okay_label_word_eu_x_data.h"
void *g_menuOkayLabelSlot[1] = {
    g_menuOkayLabelWordEuX,
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/game_title_text.h"
void *g_gameTitleLabelSlots[2] = {
    g_gameTitleLabelText, g_usRev1Text_turok2_,
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/menu_label_number_text.h"
void *g_menuNumberLabelSlot[1] = {
    g_menuNumberLabelText,
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/s_nrwetext.h"
void *g_nrweLabelSlot[1] = {
    s_nrweText,
};
#endif

#if defined(VERSION_US_REV1)
void * g_nrweBlankLabelSlots[29] = {
    &g_menuLabelSlotWords[8], &g_menuLabelSlotWords[12], &g_menuLabelSlotWords[16], &g_menuLabelSlotWords[20], &g_menuLabelSlotWords[24], &g_menuLabelSlotWords[28],
    &g_menuLabelSlotWords[32], &g_menuLabelSlotWords[36], &g_menuLabelSlotWords[40], &g_menuLabelSlotWords[44], &g_menuLabelSlotWords[48], &g_menuLabelSlotWords[52],
    &g_menuLabelSlotWords[56], &g_menuLabelSlotWords[60], &g_menuLabelSlotWords[64], &g_menuLabelSlotWords[68], &g_menuLabelSlotWords[72], &g_menuLabelSlotWords[76],
    &g_menuLabelSlotWords[80], &g_menuLabelSlotWords[84], &g_menuLabelSlotWords[88], &g_menuLabelSlotWords[92], &g_menuLabelSlotWords[96], &g_menuLabelSlotWords[100],
    &g_menuLabelSlotWords[104], &g_menuLabelSlotWords[108], &g_menuLabelSlotWords[112], &g_menuLabelSlotWords[116], &g_menuLabelSlotWords[120],
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/s_othergametext.h"
void *g_otherGameLabelSlot[1] = {
    s_otherGameText,
};
#endif

#if defined(VERSION_US_REV1)
void * g_otherGameBlankLabelSlots[17] = {
    &g_menuLabelSlotWords[124], &g_menuLabelSlotWords[140], &g_menuLabelSlotWords[144], &g_menuLabelSlotWords[148], &g_menuLabelSlotWords[152], &g_menuLabelSlotWords[156],
    &g_menuLabelSlotWords[160], &g_menuLabelSlotWords[164], &g_menuLabelSlotWords[168], &g_menuLabelSlotWords[172], &g_menuLabelSlotWords[176], &g_menuLabelSlotWords[180],
    &g_menuLabelSlotWords[184], &g_menuLabelSlotWords[188], &g_menuLabelSlotWords[192], &g_menuLabelSlotWords[196], &g_menuLabelSlotWords[200],
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/g_notedifficultymenutextpool.h"
void *g_pakNoteLabelSlots[22] = {
    g_noteDifficultyMenuTextPool, g_usRev1Text_deleteNote, g_usRev1Text_difficultyEasyPakNoteLabel, g_usRev1Text_difficultyNormalPakNoteLabel,
    g_usRev1Text_difficultyHardPakNoteLabel, g_usRev1Text_health, g_usRev1Text_lives, g_usRev1Text_timeClockReadout,
    g_usRev1Text_noteInfo, g_usRev1Text_deleteNoteCopies[0], g_usRev1Text_deleteNoteCopies[1], g_usRev1Text_nameExt,
    g_usRev1Text_Text, g_usRev1Text_name, g_usRev1Text_type, g_usRev1Text_frags,
    g_usRev1Text_rank, g_usRev1Text_loadPakNoteLabel, g_usRev1Text_delete, g_usRev1Text_deletePakNoteLabel,
    g_usRev1Text_error, g_usRev1Text_important,
};
#endif

#if defined(VERSION_US_REV1)

void *g_pakOkLabelSlot[1] = {
    g_PakOkLabelStorage,
};
#endif

#if defined(VERSION_US_REV1)
void * g_saveLoadAndHitShotLabelSlots[145] = {
    g_usRev1Text_pakMenuCells[0], g_usRev1Text_pakMenuCells[1], g_usRev1Text_pakMenuCells[2], g_usRev1Text_pakMenuCells[3], g_usRev1Text_pakMenuCells[4], g_usRev1Text_pakMenuCells[5],
    g_usRev1Text_pakMenuCells[6], g_usRev1Text_pakMenuCells[7], g_usRev1Text_pakMenuCells[8], g_usRev1Text_pakMenuCells[9], g_usRev1Text_pakMenuCells[10], g_usRev1Text_pakMenuCells[11],
    g_usRev1Text_pakMenuCells[12], g_usRev1Text_pakMenuCells[13], g_usRev1Text_pakMenuCells[14], g_usRev1Text_pakMenuCells[15], g_usRev1Text_pakMenuCells[16], g_usRev1Text_pakMenuCells[17],
    g_usRev1Text_pakMenuCells[18], g_usRev1Text_pakMenuCells[19], g_usRev1Text_pakMenuCells[20], g_usRev1Text_pakMenuCells[21], g_usRev1Text_pakMenuCells[22], g_usRev1Text_pakMenuCells[23],
    g_usRev1Text_pakMenuCells[24], g_usRev1Text_pakMenuCells[25], g_usRev1Text_pakMenuCells[26], g_usRev1Text_pakMenuCells[27], g_usRev1Text_pakMenuCells[28], g_usRev1Text_pakMenuCells[29],
    g_usRev1Text_pakMenuCells[30], g_usRev1Text_pakMenuCells[31], g_usRev1Text_pakMenuCells[32], g_usRev1Text_pakMenuCells[33], g_usRev1Text_pakMenuCells[34], g_usRev1Text_pakMenuCells[35],
    g_usRev1Text_pakMenuCells[36], g_usRev1Text_pakMenuCells[37], g_usRev1Text_pakMenuCells[38], g_usRev1Text_pakMenuCells[39], g_usRev1Text_pakMenuCells[40], g_usRev1Text_pakMenuCells[41],
    g_usRev1Text_pakMenuCells[42], g_usRev1Text_pakMenuCells[43], g_usRev1Text_pakMenuCells[44], g_usRev1Text_pakMenuCells[45], g_usRev1Text_pakMenuCells[46], g_usRev1Text_pakMenuCells[47],
    g_usRev1Text_pakMenuCells[48], g_usRev1Text_pakMenuCells[49], g_usRev1Text_pakMenuCells[50], g_usRev1Text_pakMenuCells[51], g_usRev1Text_pakMenuCells[52], g_usRev1Text_pakMenuCells[53],
    g_usRev1Text_pakMenuCells[54], g_usRev1Text_pakMenuCells[55], g_usRev1Text_pakMenuCells[56], g_usRev1Text_pakMenuCells[57], g_usRev1Text_pakMenuCells[58], g_usRev1Text_pakMenuCells[59],
    g_usRev1Text_pakMenuCells[60], g_usRev1Text_pakMenuCells[61], g_usRev1Text_pakMenuCells[62], g_usRev1Text_pakMenuCells[63], g_usRev1Text_pakMenuCells[64], g_usRev1Text_pakMenuCells[65],
    g_usRev1Text_pakMenuCells[66], g_usRev1Text_pakMenuCells[67], g_usRev1Text_pakMenuCells[68], g_usRev1Text_pakMenuCells[69], g_usRev1Text_pakMenuCells[70], g_usRev1Text_pakMenuCells[71],
    g_usRev1Text_pakMenuCells[72], g_usRev1Text_pakMenuCells[73], g_usRev1Text_pakMenuCells[74], g_usRev1Text_pakMenuCells[75], g_usRev1Text_pakMenuCells[76], g_usRev1Text_pakMenuCells[77],
    g_usRev1Text_pakMenuCells[78], g_usRev1Text_pakMenuCells[79], g_usRev1Text_pakMenuCells[80], g_usRev1Text_pakMenuCells[81], g_usRev1Text_pakMenuCells[82], g_usRev1Text_pakMenuCells[83],
    g_usRev1Text_pakMenuCells[84], g_usRev1Text_pakMenuCells[85], g_usRev1Text_pakMenuCells[86], g_usRev1Text_pakMenuCells[87], g_usRev1Text_pakMenuCells[88], g_usRev1Text_pakMenuCells[89],
    g_usRev1Text_pakMenuCells[90], g_usRev1Text_pakMenuCells[91], g_usRev1Text_pakMenuCells[92], g_usRev1Text_pakMenuCells[93], g_usRev1Text_pakMenuCells[94], g_usRev1Text_pakMenuCells[95],
    g_usRev1Text_pakMenuCells[96], g_usRev1Text_pakMenuCells[97], g_usRev1Text_pakMenuCells[98], g_usRev1Text_pakMenuCells[99], g_usRev1Text_pakMenuCells[100], g_usRev1Text_pakMenuCells[101],
    g_usRev1Text_pakMenuCells[102], g_usRev1Text_pakMenuCells[103], g_usRev1Text_pakMenuCells[104], g_usRev1Text_pakMenuCells[105], g_usRev1Text_pakMenuCells[106], g_usRev1Text_pakMenuCells[107],
    g_usRev1Text_pakMenuCells[108], g_usRev1Text_pakMenuCells[109], g_usRev1Text_pakMenuCells[110], g_usRev1Text_pakMenuCells[111], g_usRev1Text_pakMenuCells[112], g_usRev1Text_pakMenuCells[113],
    g_usRev1Text_pakMenuCells[114], g_usRev1Text_pakMenuCells[115], g_usRev1Text_pakMenuCells[116], g_usRev1Text_pakMenuCells[117], g_usRev1Text_pakMenuCells[118], g_usRev1Text_pakMenuCells[119],
    g_usRev1Text_pakMenuCells[120], g_usRev1Text_pakMenuCells[121], (void *)&g_saveLoadHealthAmmoMenuTextPool, g_usRev1Text_loadSaveLoadMenu, g_usRev1Text_healthSaveLoadMenu, g_usRev1Text_ammo,
    g_usRev1Text_goBackSaveLoadMenu, g_usRev1Text_saveLoadMenuCells[0], g_usRev1Text_saveLoadMenuCells[1], g_usRev1Text_saveLoadMenuCells[2], g_usRev1Text_saveLoadMenuCells[3], g_usRev1Text_saveLoadMenuCells[4],
    g_usRev1Text_saveLoadMenuCells[5], g_usRev1Text_saveLoadMenuCells[6], g_usRev1Text_saveLoadMenuCells[7], g_usRev1Text_saveLoadMenuCells[8], g_usRev1Text_saveLoadMenuCells[9], (void *)&g_hitLocationMessageText,
    g_usRev1Text_bodyShot, g_usRev1Text_headShot, g_usRev1Text_armShot, g_usRev1Text_edit, &g_hitLocationMessageText[56], &g_hitLocationMessageText[60],
    &g_hitLocationMessageText[64],
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/combat_and_confirmation_text.h"
void *g_confirmationLabelSlot[10] = {
    g_multiplayerTagAndKillMessageText, g_usRev1Text_youTagged, g_usRev1Text_killedBy, g_usRev1Text_youKilled,
    g_usRev1Text_youKilledYourself, g_usRev1Text_youLostTheFlag, g_usRev1Text_heDroppedTheFlag, g_usRev1Text_areYouSure,
    g_usRev1Text_youWantTo, g_usRev1Text_yes,
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/menu_no_label_word_eu_x_data.h"
void *g_menuNoLabelSlot[1] = {
    g_menuNoLabelWordEuX,
};
#endif

#if defined(VERSION_US_REV1)
#include "Constants/cheat_game_options_and_status_text_pool.h"
#include "Constants/menu_digit_labels_data.h"
void *g_optionLabelSlots[224] = {
    g_cheatGameOptionsAndStatusTextPool, g_usRev1Text_loadInGameMenuOptionLabel, g_usRev1Text_save, g_usRev1Text_enterCheat,
    g_usRev1Text_joinNow, g_usRev1Text_waiting, g_usRev1Text_connect, g_usRev1Text_goBackInGameMenuOptionLabel,
    g_usRev1Text_continue, g_usRev1Text_gameOver, g_usRev1Text_timeXx, g_usRev1Text_done,
    g_usRev1Text_newCheatEnabled, g_usRev1Text_invincibilityActivated, g_usRev1Text_infiniteLivesActivated, g_usRev1Text_allWeaponsActivated,
    g_usRev1Text_unlimitedAmmoActivated, g_usRev1Text_allKeysActivated, g_usRev1Text_bigHeadModeActivated, g_usRev1Text_tinyModeActivated,
    g_usRev1Text_stickModeActivated, g_usRev1Text_bigHandsAndFeet, g_usRev1Text_penAndInkMode, g_usRev1Text_gouraudModeActivated,
    g_usRev1Text_juansCheatActivated, g_usRev1Text_zachAttackCheatActivated, g_usRev1Text_allMapActivated, g_usRev1Text_blackoutModeActivated,
    g_usRev1Text_mmmmTastyFrootyStripes, g_usRev1Text_warpLevel1Activated, g_usRev1Text_warpLevel2Activated, g_usRev1Text_warpLevel3Activated,
    g_usRev1Text_warpLevel4Activated, g_usRev1Text_warpLevel5Activated, g_usRev1Text_warpLevel6Activated, g_usRev1Text_warpQueenBossActivated,
    g_usRev1Text_warpBlindBossActivated, g_usRev1Text_warpMotherBossActivated, g_usRev1Text_warpPrimagenBossActivated, g_usRev1Text_warpCreditsActivated,
    g_usRev1Text_invincibilityOn, g_usRev1Text_invincibilityOff, g_usRev1Text_infiniteLivesOn, g_usRev1Text_infiniteLivesOff,
    g_usRev1Text_allWeaponsOn, g_usRev1Text_allWeaponsOff, g_usRev1Text_unlimitedAmmoOn, g_usRev1Text_unlimitedAmmoOff,
    g_usRev1Text_allSpecialObjectsOn, g_usRev1Text_allSpecialObjectsOff, g_usRev1Text_bigHeadModeOn, g_usRev1Text_bigHeadModeOff,
    g_usRev1Text_tinyModeOn, g_usRev1Text_tinyModeOff, g_usRev1Text_stickModeOn, g_usRev1Text_stickModeOff,
    g_usRev1Text_bigHandsFeetModeOn, g_usRev1Text_bigHandsFeetModeOff, g_usRev1Text_penAndInkModeOn, g_usRev1Text_penAndInkModeOff,
    g_usRev1Text_gouraudModeOn, g_usRev1Text_gouraudModeOff, g_usRev1Text_juansCheatOn, g_usRev1Text_juansCheatOff,
    g_usRev1Text_zachAttackCheatOn, g_usRev1Text_zachAttackCheatOff, g_usRev1Text_allMapOn, g_usRev1Text_allMapOff,
    g_usRev1Text_blackoutOn, g_usRev1Text_blackoutOff, g_usRev1Text_frootyStripesOn, g_usRev1Text_frootyStripesOff,
    g_usRev1Text_warpPortOfAdia, g_usRev1Text_warpRiverOfSouls, g_usRev1Text_warpDeathMarshes, g_usRev1Text_warpLairOfThe,
    g_usRev1Text_warpHiveOfThe, g_usRev1Text_warpPrimagenSLightship, g_usRev1Text_warpQueenBoss, g_usRev1Text_warpBlindBossMenuLine,
    g_usRev1Text_warpMotherBoss, g_usRev1Text_warpPrimagenBoss, g_usRev1Text_warpCredits, g_usRev1Text_youFragged,
    g_usRev1Text_youTaggedOptionLabel, g_usRev1Text_totals, g_usRev1TotalsPanels.first.one, g_usRev1TotalsPanels.first.two,
    g_usRev1TotalsPanels.first.three, g_usRev1TotalsPanels.first.four, g_usRev1TotalsPanels.first.tags, g_usRev1TotalsPanels.first.frags,
    g_usRev1TotalsPanels.first.deaths, g_usRev1TotalsPanels.first.suicides, g_usRev1TotalsPanels.rest[0].one, g_usRev1TotalsPanels.rest[0].two,
    g_usRev1TotalsPanels.rest[0].three, g_usRev1TotalsPanels.rest[0].four, g_usRev1TotalsPanels.rest[0].tags, g_usRev1TotalsPanels.rest[0].frags,
    g_usRev1TotalsPanels.rest[0].deaths, g_usRev1TotalsPanels.rest[0].suicides, g_usRev1TotalsPanels.rest[1].one, g_usRev1TotalsPanels.rest[1].two,
    g_usRev1TotalsPanels.rest[1].three, g_usRev1TotalsPanels.rest[1].four, g_usRev1TotalsPanels.rest[1].tags, g_usRev1TotalsPanels.rest[1].frags,
    g_usRev1TotalsPanels.rest[1].deaths, g_usRev1TotalsPanels.rest[1].suicides, g_usRev1TotalsPanels.rest[2].one, g_usRev1TotalsPanels.rest[2].two,
    g_usRev1TotalsPanels.rest[2].three, g_usRev1TotalsPanels.rest[2].four, g_usRev1TotalsPanels.rest[2].tags, g_usRev1TotalsPanels.rest[2].frags,
    g_usRev1TotalsPanels.rest[2].deaths, g_usRev1TotalsPanels.rest[2].suicides, g_usRev1Text_player1, g_usRev1Text_player2,
    g_usRev1Text_player3, g_usRev1Text_player4, g_usRev1Text_single, g_usRev1Text_newGame,
    g_usRev1Text_loadSinglePlayerMenuOptionLabel, g_usRev1Text_multi, g_usRev1Text_deathmatch, g_usRev1Text_selectGameType,
    g_usRev1Text_bloodLust, g_usRev1Text_bloodLustOptionLabel, g_usRev1Text_timedGameNone, g_usRev1Text_fragLimitNone,
    g_usRev1Text_levelRandom, g_usRev1Text_levelExperimentata, g_usRev1Text_levelMoonlitMayhem, g_usRev1Text_levelCloseQuartered,
    g_usRev1Text_levelVulcanSForge, g_usRev1Text_levelTeleportastic, g_usRev1Text_levelMirrororrim, g_usRev1Text_levelFishInA,
    g_usRev1Text_levelH2Whoa, g_usRev1Text_levelEscheria, g_usRev1Text_levelMoshCrypt, g_usRev1Text_levelSquaresCubed,
    g_usRev1Text_levelCrazyEight, g_usRev1Text_levelBullseye, g_usRev1Text_textureSetCastle, g_usRev1Text_textureSetSteelMill,
    g_usRev1Text_textureSetOakFort, g_usRev1Text_textureSetCatacombs, g_usRev1Text_textureSetJailhouse, g_usRev1Text_textureSetBigCity,
    g_usRev1Text_textureSetRedDragon, g_usRev1Text_textureSetPaintball, g_usRev1Text_textureSetMrHappy, g_usRev1Text_crosshairsOn,
    g_usRev1Text_crosshairsOff, g_usRev1Text_startGame, g_usRev1Text_goBackDeathmatchSetupOptionLabel, g_usRev1Text_fragTag,
    g_usRev1Text_fragTagOptionLabel, g_usRev1Text_tagLimitNone, g_usRev1Text_levelMadhouse, g_usRev1Text_levelSnap,
    g_usRev1Text_levelSneaksNLadders, g_usRev1Text_levelPrimattica, g_usRev1Text_levelCrossfire, g_usRev1Text_levelYNG,
    g_usRev1Text_teamBlood, g_usRev1Text_customizeWeapons, g_usRev1Text_chargeDartRifleOn, g_usRev1Text_chargeDartRifleOff,
    g_usRev1Text_firestormOn, g_usRev1Text_firestormOff, g_usRev1Text_assaultRifleOn, g_usRev1Text_assaultRifleOff,
    g_usRev1Text_plasmaRifleOn, g_usRev1Text_plasmaRifleOff, g_usRev1Text_cerebralBoreOn, g_usRev1Text_cerebralBoreOff,
    g_usRev1Text_grenadeLauncherOn, g_usRev1Text_grenadeLauncherOff, g_usRev1Text_scorpionLauncherOn, g_usRev1Text_scorpionLauncherOff,
    g_usRev1Text_torpedoLauncherOn, g_usRev1Text_torpedoLauncherOff, g_usRev1Text_training, g_usRev1Text_levelRandomOptionLabel,
    g_usRev1Text_levelArchery, g_usRev1Text_levelShooting, g_usRev1Text_levelDecathalon, g_usRev1Text_noOfLaps,
    g_usRev1Text_startGameOptionLabel, g_usRev1Text_goBackTrainingSetupOptionLabel, g_usRev1Text_loadTitleMenuOptionLabel, g_usRev1Text_optionsOptionLabel,
    g_usRev1Text_cheatsOptionLabel, g_usRev1Text_checkPoint, g_usRev1Text_savePoint, g_usRev1Text_soundOptions,
    g_usRev1Text_musicVolumeOff, g_usRev1Text_musicVolumeMax, g_usRev1Text_musicVolumeNorm, g_usRev1Text_musicVolume,
    g_usRev1Text_sfxVolumeOff, g_usRev1Text_sfxVolumeMax, g_usRev1Text_sfxVolumeNorm, g_usRev1Text_sfxVolume,
    g_usRev1Text_speechVolumeOff, g_usRev1Text_speechVolumeMax, g_usRev1Text_speechVolumeNorm, g_usRev1Text_speechVolume,
    g_usRev1Text_musicNone, g_usRev1Text_music, g_usRev1Text_indexNone, g_usRev1Text_speechNone,
    g_usRev1Text_missionComplete, g_usRev1Text_missionFailedOptionLabel, g_usRev1Text_defendTheTotem, g_usRev1Text_playerSpeed,
    g_usRev1Text_playerSpeedDefault, g_usRev1Text_default, g_usRev1Text_lowHealth, ragewars_menu_digit_labels_us_rev1_StorageWords,
};
#endif

#if defined(VERSION_US_REV1)

void *k_menuDigitLabelPointers[10] = {
    &ragewars_menu_digit_labels_us_rev1_StorageWords[4], &ragewars_menu_digit_labels_us_rev1_StorageWords[8], &ragewars_menu_digit_labels_us_rev1_StorageWords[12], &ragewars_menu_digit_labels_us_rev1_StorageWords[16],
    &ragewars_menu_digit_labels_us_rev1_StorageWords[20], &ragewars_menu_digit_labels_us_rev1_StorageWords[24], &ragewars_menu_digit_labels_us_rev1_StorageWords[28], &ragewars_menu_digit_labels_us_rev1_StorageWords[32],
    &ragewars_menu_digit_labels_us_rev1_StorageWords[36], &ragewars_menu_digit_labels_us_rev1_StorageWords[40],
};
#endif

#if defined(VERSION_US_REV1)

void *g_creditsLinesStoragePointer[1] = {
    ragewars_credits_lines_us_rev1_StorageWords,
};
#endif

#if defined(VERSION_US_REV1)
KeyboardKeyLabelWordsLayout g_keyboardKeyLabel = {
    { { 8.0f, (void *)&g_keyboardKeyLabel }, { 32.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[1].constant }, { 128.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[2].constant }, { 512.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[3].constant }, { 2048.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[4].constant }, { 8192.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[5].constant }, { 32768.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[6].constant }, { 131072.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[7].constant }, { 524288.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[8].constant }, { 2097152.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[9].constant }, { 8388608.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[10].constant }, { 33554432.0f, (void *)&g_keyboardKeyLabel.scaleStepRows[11].constant }, { 1.3421773e+08f, (void *)&g_keyboardKeyLabel.scaleStepRows[12].constant }, { 5.368709e+08f, (void *)&g_keyboardKeyLabel.scaleStepRows[13].constant }, { 2.1474836e+09f, (void *)&g_keyboardKeyLabel.scaleStepRows[14].constant } },
    { { 0x50000000, &g_keyboardKeyLabel.keyCharacterRows[0].packedValue }, { 0x51000000, &g_keyboardKeyLabel.keyCharacterRows[1].packedValue }, { 0x52000000, &g_keyboardKeyLabel.keyCharacterRows[2].packedValue }, { 0x53000000, &g_keyboardKeyLabel.keyCharacterRows[3].packedValue }, { 0x54000000, &g_keyboardKeyLabel.keyCharacterRows[4].packedValue }, { 0x55000000, &g_keyboardKeyLabel.keyCharacterRows[5].packedValue }, { 0x56000000, &g_keyboardKeyLabel.keyCharacterRows[6].packedValue }, { 0x57000000, &g_keyboardKeyLabel.keyCharacterRows[7].packedValue }, { 0x58000000, &g_keyboardKeyLabel.keyCharacterRows[8].packedValue }, { 0x59000000, &g_keyboardKeyLabel.keyCharacterRows[9].packedValue }, { 0x5A000000, &g_keyboardKeyLabel.keyCharacterRows[10].packedValue }, { 0x30000000, &g_keyboardKeyLabel.keyCharacterRows[11].packedValue }, { 0x31000000, &g_keyboardKeyLabel.keyCharacterRows[12].packedValue }, { 0x32000000, &g_keyboardKeyLabel.keyCharacterRows[13].packedValue }, { 0x33000000, &g_keyboardKeyLabel.keyCharacterRows[14].packedValue }, { 0x34000000, &g_keyboardKeyLabel.keyCharacterRows[15].packedValue }, { 0x35000000, &g_keyboardKeyLabel.keyCharacterRows[16].packedValue }, { 0x36000000, &g_keyboardKeyLabel.keyCharacterRows[17].packedValue }, { 0x37000000, &g_keyboardKeyLabel.keyCharacterRows[18].packedValue } },
    { { 3.0517578e-05f, (void *)&g_keyboardKeyLabel.fineScaleStepRows[0].constant }, { 0.00012207031f, (void *)&g_keyboardKeyLabel.fineScaleStepRows[1].constant } },
    { { 0x02000000, &g_keyboardKeyLabel.keyCodeRows[0].packedValue }, { 0x03000000, &g_keyboardKeyLabel.keyCodeRows[1].packedValue } },
    0x04000000,
    { &g_keyboardKeyLabel.packedValue, 0, &g_keyboardKeyLabel.references[1] },
};
#endif
