#ifndef MENU_LABEL_SLOTS_MENU_LABEL_SLOTS_H
#define MENU_LABEL_SLOTS_MENU_LABEL_SLOTS_H
#include "Data/totals_panels.h"
struct KeyboardKeyLabelWordsLayout;
extern void *g_itemLabelSlots[];
#if defined(VERSION_US_REV1)
extern void *g_pickupLabelDirectory[103];
#endif
#if defined(VERSION_US_REV1)
extern struct KeyboardKeyLabelWordsLayout g_keyboardKeyLabel;
#endif
extern char g_menuLabelSlotWords[];
#if defined(VERSION_US_REV1)
extern char g_SkyPostscaledscreenmessageEncodedBytes[];
#endif
extern char g_usRev1Text_10Health[]; /* "10 health" */
extern char g_usRev1Text_15Health[]; /* "15 health" */
extern char g_usRev1Text_25Health[]; /* "25 health" */
extern char g_usRev1Text_50Health[]; /* "50 health" */
extern char g_usRev1Text_fullHealth[]; /* "full health" */
extern char g_usRev1Text_1LifeForce[]; /* "1 life force" */
extern char g_usRev1Text_10LifeForce[]; /* "10 life force" */
extern char g_usRev1Text_invincibility[]; /* "invincibility" */
extern char g_usRev1Text_planeWalker[]; /* "plane walker" */
extern char g_usRev1Text_flashlightBattery[]; /* "flashlight battery" */
extern char g_usRev1Text_greyEagleFeather[]; /* "grey eagle feather" */
extern char g_usRev1Text_purpleEagleFeather[]; /* "purple eagle feather" */
extern char g_usRev1Text_nukeWeaponPart[]; /* "nuke weapon part" */
extern char g_usRev1Text_napalmGel[]; /* "NAPALM GEL" */
extern char g_usRev1Text_chestBurster[]; /* "CHEST BURSTER" */
extern char g_usRev1Text_cerebralBore[]; /* "CEREBRAL BORE" */
extern char g_usRev1Text_repulseMarked[]; /* "REPULSE MARKED" */
extern char g_usRev1Text_joinedTeamCoyote[]; /* "Joined Team Coyote" */
extern char g_usRev1Text_joinedTeamBear[]; /* "Joined Team Bear" */
extern char g_usRev1Text_joinedTeamCougar[]; /* "Joined Team Cougar" */
extern char g_usRev1Text_joinedTeamViper[]; /* "Joined Team Viper" */
extern char g_usRev1Text_youFraggedYourself[]; /* "You fragged yourself." */
extern char g_usRev1Text_fraggedByS[]; /* "Fragged by %s." */
extern char g_usRev1Text_smackedByS[]; /* "Smacked  by %s." */
extern char g_usRev1Text_sObliteratedYou[]; /* "%s obliterated you." */
extern char g_usRev1Text_sButcheredYou[]; /* "%s butchered you." */
extern char g_usRev1Text_sCrushedYou[]; /* "%s crushed you." */
extern char g_usRev1Text_poundedByS[]; /* "Pounded by %s." */
extern char g_usRev1Text_yourOtherLeft[]; /* "your other left." */
extern char g_usRev1Text_oops[]; /* "Oops..." */
extern char g_usRev1Text_badMove[]; /* "Bad move..." */
extern char g_usRev1Text_umWatchYourStep[]; /* "Um...  Watch your step?" */
extern char g_usRev1Text_explosiveRounds[]; /* "Explosive rounds" */
extern char g_usRev1Text_explosiveRoundsPickupLabel[]; /* "Explosive rounds" */
extern char g_usRev1Text_ammoPack[]; /* "Ammo pack" */
extern char g_usRev1Text_bullet[]; /* "bullet" */
extern char g_usRev1Text_energyRound[]; /* "energy round" */
extern char g_usRev1Text_explosiveRound[]; /* "explosive round" */
extern char g_usRev1Text_cerebralBoreItemLabel[]; /* "cerebral bore" */
extern char g_usRev1Text_pfmMine[]; /* "pfm mine" */
extern char g_usRev1Text_sentryTurret[]; /* "sentry turret" */
extern char g_usRev1Text_ironClaw[]; /* "iron claw" */
extern char g_usRev1Text_slowTime[]; /* "Slow Time..." */
extern char g_usRev1Text_blastShield[]; /* "Blast Shield..." */
extern char g_usRev1Text_regeneration[]; /* "Regeneration..." */
extern char g_usRev1Text_petrify[]; /* "Petrify..." */
extern char g_usRev1Text_damageReversal[]; /* "Damage Reversal..." */
extern char g_usRev1Text_invisibility[]; /* "Invisibility..." */
extern char g_usRev1Text_lifeForceVampire[]; /* "Life Force Vampire..." */
extern char g_usRev1Text_speedBurst[]; /* "Speed Burst..." */
extern char g_usRev1Text_teleportation[]; /* "Teleportation..." */
extern char g_usRev1Text_teleportedToSafety[]; /* "Teleported to safety...(?)" */
extern char g_usRev1Text_somethingElse[]; /* "Something Else..." */
extern char g_usRev1Text_shield[]; /* "Shield" */
extern char g_usRev1Text_novice[]; /* "NOVICE" */
extern char g_usRev1Text_scout[]; /* "SCOUT" */
extern char g_usRev1Text_brave[]; /* "BRAVE" */
extern char g_usRev1Text_hunter[]; /* "HUNTER" */
extern char g_usRev1Text_darkling[]; /* "DARKLING" */
extern char g_usRev1Text_seeker[]; /* "SEEKER" */
extern char g_usRev1Text_bane[]; /* "BANE" */
extern char g_usRev1Text_warlord[]; /* "WARLORD" */
extern char g_usRev1Text_deathwind[]; /* "DEATHWIND" */
extern char g_usRev1Text_conqueror[]; /* "CONQUEROR" */
extern char g_usRev1Text_master[]; /* "MASTER" */
extern char g_usRev1Text_tyrant[]; /* "TYRANT" */
extern char g_usRev1Text_warslave[]; /* "WARSLAVE" */
extern char g_usRev1Text_godhand[]; /* "GODHAND" */
extern char g_usRev1Text_chieftain[]; /* "CHIEFTAIN" */
extern char g_usRev1Text_achievementOnProvingGrounds[]; /* "ACHIEVEMENT ON PROVING GROUNDS" */
extern char g_usRev1Text_achievementOnBasicTraining[]; /* "ACHIEVEMENT ON BASIC TRAINING" */
extern char g_usRev1Text_achievementOnCrossroads[]; /* "ACHIEVEMENT ON CROSSROADS" */
extern char g_usRev1Text_achievementOnGrimRetreat[]; /* "ACHIEVEMENT ON GRIM RETREAT" */
extern char g_usRev1Text_achievementOnCathedral[]; /* "ACHIEVEMENT ON CATHEDRAL" */
extern char g_usRev1Text_achievementOnFallout[]; /* "ACHIEVEMENT ON FALLOUT" */
extern char g_usRev1Text_achievementOnBoxedSet[]; /* "ACHIEVEMENT ON BOXED SET" */
extern char g_usRev1Text_achievementOnDireStraight[]; /* "ACHIEVEMENT ON DIRE STRAIGHT" */
extern char g_usRev1Text_achievementOnPrey[]; /* "ACHIEVEMENT ON PREY" */
extern char g_usRev1Text_achievementOnWarehouse[]; /* "ACHIEVEMENT ON WAREHOUSE" */
extern char g_usRev1Text_achievementOnBombShelter[]; /* "ACHIEVEMENT ON BOMB SHELTER" */
extern char g_usRev1Text_achievementOnTempered[]; /* "ACHIEVEMENT ON TEMPERED" */
extern char g_usRev1Text_achievementOnEarthTemple[]; /* "ACHIEVEMENT ON EARTH TEMPLE" */
extern char g_usRev1Text_achievementOnFireTemple[]; /* "ACHIEVEMENT ON FIRE TEMPLE" */
extern char g_usRev1Text_achievementOnMystic[]; /* "ACHIEVEMENT ON MYSTIC" */
extern char g_usRev1Text_achievementOnBottleneck[]; /* "ACHIEVEMENT ON BOTTLENECK" */
extern char g_usRev1Text_achievementOnTightrope[]; /* "ACHIEVEMENT ON TIGHTROPE" */
extern char g_usRev1Text_achievementOnThePit[]; /* "ACHIEVEMENT ON THE PIT" */
extern char g_usRev1Text_achievementOnLeapOf[]; /* "ACHIEVEMENT ON LEAP OF FAITH" */
extern char g_usRev1Text_achievementOnWickedDance[]; /* "ACHIEVEMENT ON WICKED DANCE" */
extern char g_usRev1Text_achievementOnBunker[]; /* "ACHIEVEMENT ON BUNKER" */
extern char g_usRev1Text_achievementOnAmphitheater[]; /* "ACHIEVEMENT ON AMPHITHEATER" */
extern char g_usRev1Text_achievementOnFireWalker[]; /* "ACHIEVEMENT ON FIRE WALKER" */
extern char g_usRev1Text_achievementOnCrypts[]; /* "ACHIEVEMENT ON CRYPTS" */
extern char g_usRev1Text_achievementOnBreakdown[]; /* "ACHIEVEMENT ON BREAKDOWN" */
extern char g_usRev1Text_achievementOnRetaliation[]; /* "ACHIEVEMENT ON RETALIATION" */
extern char g_usRev1Text_achievementOnHopeless[]; /* "ACHIEVEMENT ON HOPELESS" */
extern char g_usRev1Text_achievementOnMatrix[]; /* "ACHIEVEMENT ON MATRIX" */
extern char g_usRev1Text_achievementOnFathom[]; /* "ACHIEVEMENT ON FATHOM" */
extern char g_usRev1Text_achievementOnThePedestal[]; /* "ACHIEVEMENT ON THE PEDESTAL" */
extern char g_usRev1Text_achievementOnDefcon5[]; /* "ACHIEVEMENT ON DEFCON 5" */
extern char g_usRev1Text_achievementOnSpiritTemple[]; /* "ACHIEVEMENT ON SPIRIT TEMPLE" */
extern char g_usRev1Text_achievementOnCourtyard[]; /* "ACHIEVEMENT ON COURTYARD" */
extern char g_usRev1Text_achievementOnStarlight[]; /* "ACHIEVEMENT ON STARLIGHT" */
extern char g_usRev1Text_attained15FragsIn[]; /* "ATTAINED 15 FRAGS IN 5 MINUTES" */
extern char g_usRev1Text_attained25FragsIn[]; /* "ATTAINED 25 FRAGS IN 10 MINUTES" */
extern char g_usRev1Text_notGettingAnyFrags[]; /* "NOT GETTING ANY FRAGS" */
extern char g_usRev1Text_killingYourself5Times[]; /* "KILLING YOURSELF 5 TIMES" */
extern char g_usRev1Text_comingInLast[]; /* "COMING IN LAST" */
extern char g_usRev1Text_totalFragAward[]; /* "TOTAL FRAG AWARD" */
extern char g_usRev1Text_totalBeingKilledAward[]; /* "TOTAL BEING KILLED AWARD" */
extern char g_usRev1Text_sniping10PeopleIn[]; /* "SNIPING 10 PEOPLE IN A ROUND" */
extern char g_usRev1Text_notBeingKilledIn[]; /* "NOT BEING KILLED IN A ROUND" */
extern char g_usRev1Text_defeatedBastille[]; /* "DEFEATED BASTILLE" */
extern char g_usRev1Text_defeatedSyra[]; /* "DEFEATED SYRA" */
extern char g_usRev1Text_defeatedSymbiont[]; /* "DEFEATED SYMBIONT" */
extern char g_usRev1Text_defeatedTalSet[]; /* "DEFEATED TAL SET" */
extern char g_usRev1Text_beatingTheCooperativeScenario[]; /* "BEATING THE COOPERATIVE SCENARIO" */
extern char g_usRev1Text_empty[]; /* "<EMPTY>" */
extern char g_usRev1Text_turok[]; /* "TUROK" */
extern char g_usRev1Text_warrior[]; /* "WARRIOR" */
extern char g_usRev1Text_masterItemLabel[]; /* "MASTER" */
extern char g_usRev1Text_adon[]; /* "ADON" */
extern char g_usRev1Text_seekerItemLabel[]; /* "SEEKER" */
extern char g_usRev1Text_huntress[]; /* "HUNTRESS" */
extern char g_usRev1Text_campain[]; /* "CAMPAIN" */
extern char g_usRev1Text_slaver[]; /* "SLAVER" */
extern char g_usRev1Text_tyrantItemLabel[]; /* "TYRANT" */
extern char g_usRev1Text_fireborn[]; /* "FIREBORN" */
extern char g_usRev1Text_icelord[]; /* "ICELORD" */
extern char g_usRev1Text_entrail[]; /* "ENTRAIL" */
extern char g_usRev1Text_mites[]; /* "MITES" */
extern char g_usRev1Text_compies[]; /* "COMPIES" */
extern char g_usRev1Text_teddies[]; /* "TEDDIES" */
extern char g_usRev1Text_juggnaut[]; /* "JUGGNAUT" */
extern char g_usRev1Text_sloth[]; /* "SLOTH" */
extern char g_usRev1Text_drone[]; /* "DRONE" */
extern char g_usRev1Text_grunt[]; /* "GRUNT" */
extern char g_usRev1Text_slave[]; /* "SLAVE" */
extern char g_usRev1Text_captain[]; /* "CAPTAIN" */
extern char g_usRev1Text_king[]; /* "KING" */
extern char g_usRev1Text_bastille[]; /* "BASTILLE" */
extern char g_usRev1Text_talSet[]; /* "TAL SET" */
extern char g_usRev1Text_syra[]; /* "SYRA" */
extern char g_usRev1Text_symbiont[]; /* "SYMBIONT" */
extern char g_usRev1Text_guardian[]; /* "GUARDIAN" */
extern char g_usRev1Text_ravage[]; /* "RAVAGE" */
extern char g_usRev1Text_cyclops[]; /* "CYCLOPS" */
extern char g_usRev1Text_lorddead[]; /* "LORDDEAD" */
extern char g_usRev1Text_maggot[]; /* "MAGGOT" */
extern char g_usRev1Text_vile[]; /* "VILE" */
extern char g_usRev1Text_elite[]; /* "ELITE" */
extern char g_usRev1Text_biobot[]; /* "BIOBOT" */
extern char g_usRev1Text_killbot[]; /* "KILLBOT" */
extern char g_usRev1Text_death[]; /* "DEATH" */
extern char g_usRev1Text_reaper[]; /* "REAPER" */
extern char g_usRev1Text_raptor[]; /* "RAPTOR" */
extern char g_usRev1Text_slag[]; /* "SLAG" */
extern char g_usRev1Text_claw[]; /* "CLAW" */
extern char g_usRev1Text_warclubs[]; /* "WARCLUBS" */
extern char g_usRev1Text_turokItemLabel[]; /* "TUROK" */
extern char g_usRev1Text_mantidDrone[]; /* "MANTID DRONE" */
extern char g_usRev1Text_campaigner[]; /* "CAMPAIGNER" */
extern char g_usRev1Text_firebornItemLabel[]; /* "FIREBORN" */
extern char g_usRev1Text_mantidSoldier[]; /* "MANTID SOLDIER" */
extern char g_usRev1Text_adonItemLabel[]; /* "ADON" */
extern char g_usRev1Text_lordOfTheDead[]; /* "LORD OF THE DEAD" */
extern char g_usRev1Text_eliteGuard[]; /* "ELITE GUARD" */
extern char g_usRev1Text_guardianItemLabel[]; /* "GUARDIAN" */
extern char g_usRev1Text_juggernaut[]; /* "JUGGERNAUT" */
extern char g_usRev1Text_oblivionSpawn[]; /* "OBLIVION SPAWN" */
extern char g_usRev1Text_bastilleItemLabel[]; /* "BASTILLE" */
extern char g_usRev1Text_syraItemLabel[]; /* "SYRA" */
extern char g_usRev1Text_symbiontItemLabel[]; /* "SYMBIONT" */
extern char g_usRev1Text_talSetItemLabel[]; /* "TAL SET" */
extern char g_usRev1Text_raptorItemLabel[]; /* "RAPTOR" */
extern char g_usRev1Text_mantidMites[]; /* "MANTID MITES" */
extern char g_usRev1Text_captureTheFlagD[]; /* "capture the flag %d time" */
extern char g_usRev1Text_captureTheFlagD2[]; /* "capture the flag %d times" */
extern char g_usRev1Text_acquireDTeamCaptures[]; /* "acquire %d team captures" */
extern char g_usRev1Text_tagTheMonkeyD[]; /* "tag the monkey %d time" */
extern char g_usRev1Text_tagTheMonkeyD2[]; /* "tag the monkey %d times" */
extern char g_usRev1Text_acquireDCreatureTags[]; /* "acquire %d creature tags" */
extern char g_usRev1Text_acquireDFrag[]; /* "acquire %d frag" */
extern char g_usRev1Text_acquireDFrags[]; /* "acquire %d frags" */
extern char g_usRev1Text_acquireDTeamFrag[]; /* "acquire %d team frag" */
extern char g_usRev1Text_acquireDTeamFrags[]; /* "acquire %d team frags" */
extern char g_usRev1Text_in02dSecondsOr[]; /* "in %02d seconds or less" */
extern char g_usRev1Text_inDMinuteAnd[]; /* "in %d minute and %02d seconds or less" */
extern char g_usRev1Text_inDMinutesAnd[]; /* "in %d minutes and %02d seconds or less" */
extern char g_usRev1Text_inDMinuteOr[]; /* "in %d minute or less" */
extern char g_usRev1Text_inDMinutesOr[]; /* "in %d minutes or less" */
extern char g_usRev1Text_withDLife[]; /* "with %d life" */
extern char g_usRev1Text_withDLives[]; /* "with %d lives" */
extern char g_usRev1Text_defeatS[]; /* "defeat %s" */
extern char g_usRev1Text_defeatBothSAnd[]; /* "defeat both %s and %s" */
extern char g_usRev1Text_everyManForThemselves[]; /* "every man for themselves" */
extern char g_usRev1Text_easy[]; /* "EASY" */
extern char g_usRev1Text_medium[]; /* "MEDIUM" */
extern char g_usRev1Text_hard[]; /* "HARD" */
extern char g_usRev1Text_off[]; /* "OFF" */
extern char g_usRev1Text_green[]; /* "GREEN" */
extern char g_usRev1Text_horizontal[]; /* "HORIZONTAL" */
extern char g_usRev1Text_vertical[]; /* "VERTICAL" */
extern char g_usRev1Text_lorez[]; /* "LOREZ" */
extern char g_usRev1Text_hirez[]; /* "HIREZ" */
extern char g_usRev1Text_letterbox[]; /* "LETTERBOX" */
extern char g_usRev1Text_noviceItemLabel[]; /* "NOVICE" */
extern char g_usRev1Text_easyItemLabel[]; /* "EASY" */
extern char g_usRev1Text_normal[]; /* "NORMAL" */
extern char g_usRev1Text_veteran[]; /* "VETERAN" */
extern char g_usRev1Text_expert[]; /* "EXPERT" */
extern char g_usRev1Text_arcade[]; /* "ARCADE" */
extern char g_usRev1Text_wheel[]; /* "WHEEL" */
extern char g_usRev1Text_tap[]; /* "TAP" */
extern char g_usRev1Text_mixed[]; /* "MIXED" */
extern char g_usRev1Text_controllerD[]; /* "CONTROLLER %d" */
extern char g_usRev1Text_ctf[]; /* "CTF" */
extern char g_usRev1Text_tbl[]; /* "TBL" */
extern char g_usRev1Text_ft[]; /* "FT" */
extern char g_usRev1Text_fragFest[]; /* "FRAG FEST" */
extern char g_usRev1Text_timeTrial[]; /* "TIME TRIAL" */
extern char g_usRev1Text_playerD[]; /* "PLAYER%d" */
extern char g_usRev1Text_acquiredEagleTalisman1[]; /* "ACQUIRED EAGLE TALISMAN. 1 UP!" */
extern char g_usRev1Text_acquiredHalfEagleTalisman[]; /* "ACQUIRED HALF EAGLE TALISMAN. ANoTHER GI" */
extern char g_usRev1Text_acquiredTheOtherEagle[]; /* "ACQUIRED THE OTHER EAGLE TALISMAN, GAINE" */
extern char g_usRev1Text_acquiredBearTalismanExplosive[]; /* "ACQUIRED BEAR TALISMAN. EXPLOSIVE AMMO U" */
extern char g_usRev1Text_acquiredCoyoteTalismanBullet[]; /* "ACQUIRED COYOTE TALISMAN. BULLET AMMO UP" */
extern char g_usRev1Text_acquiredCougarTalismanEnergy[]; /* "ACQUIRED COUGAR TALISMAN. ENERGY AMMO UP" */
extern char g_usRev1Text_acquiredViperTalismanHealth[]; /* "ACQUIRED VIPER TALISMAN. HEAlTH MAX UP 5" */
extern char g_usRev1Text_acquiredCooperativeTalisman[]; /* "ACQUIRED COOPERATIVE TALISMAN" */
extern char g_usRev1Text_acquiredMinigameIcon[]; /* "ACQUIRED MINIGAME ICON" */
extern char g_usRev1Text_acquiredAssaultRifle[]; /* "ACQUIRED ASSAULT RIFLE" */
extern char g_usRev1Text_acquiredAssaultRifleRapid[]; /* "ACQUIRED ASSAULT RIFLE RAPID FIRE UPGRAD" */
extern char g_usRev1Text_acquiredTekCrossBow[]; /* "ACQUIRED TEK CROSS BOW SNIPER SCOPE" */
extern char g_usRev1Text_acquiredGrenadeLauncher[]; /* "ACQUIRED GRENADE LAUNCHER" */
extern char g_usRev1Text_acquiredGrenadeLauncherUpgrade[]; /* "ACQUIRED GRENADE LAUNCHER UPGRADE" */
extern char g_usRev1Text_acquiredPlasmaRifle[]; /* "ACQUIRED PLASMA RIFLE" */
extern char g_usRev1Text_acquiredPlasmaRifleScope[]; /* "ACQUIRED PLASMA RIFLE SCOPE" */
extern char g_usRev1Text_acquiredAcidSpitAttack[]; /* "ACQUIRED ACID SPIT ATTACK" */
extern char g_usRev1Text_acquiredJumpClawAttack[]; /* "ACQUIRED JUMP CLAW ATTACK" */
extern char g_usRev1Text_acquiredRadioactiveFlareGun[]; /* "ACQUIRED RADIOACTIVE FLARE GUN" */
extern char g_usRev1Text_acquiredRadioactiveFlareGunMatchOptionLabel[]; /* "ACQUIRED RADIOACTIVE FLARE GUN UPGRADE" */
extern char g_usRev1Text_acquiredScorpionLauncher[]; /* "ACQUIRED SCORPION LAUNCHER" */
extern char g_usRev1Text_acquiredScorpionLauncherMagnet[]; /* "ACQUIRED SCORPION LAUNCHER MAGNET UPGRAD" */
extern char g_usRev1Text_acquiredFreezeGun[]; /* "ACQUIRED FREEZE GUN" */
extern char g_usRev1Text_acquiredFreezeGunUpgrade[]; /* "ACQUIRED FREEZE GUN UPGRADE" */
extern char g_usRev1Text_acquiredNapalmGel[]; /* "ACQUIRED NAPALM GEL" */
extern char g_usRev1Text_acquiredMag60Laser[]; /* "ACQUIRED MAG 60 LASER SIGHT UPGRADE" */
extern char g_usRev1Text_acquiredChestburster[]; /* "ACQUIRED CHESTBURSTER" */
extern char g_usRev1Text_acquiredInflator[]; /* "ACQUIRED INFLATOR" */
extern char g_usRev1Text_acquiredInflatorUpgrade[]; /* "ACQUIRED INFLATOR UPGRADE" */
extern char g_usRev1Text_acquiredBoomerang[]; /* "ACQUIRED BOOMERANG" */
extern char g_usRev1Text_acquiredBoomerangUpgrade[]; /* "ACQUIRED BOOMERANG UPGRADE" */
extern char g_usRev1Text_acquiredMinigun[]; /* "ACQUIRED MINIGUN" */
extern char g_usRev1Text_acquiredMinigunPersonalShield[]; /* "ACQUIRED MINIGUN PERSONAL SHIELD UPGRADE" */
extern char g_usRev1Text_acquiredShotgunStreetsweeperUpgrade[]; /* "ACQUIRED SHOTGUN STREETSWEEPER UPGRADE" */
extern char g_usRev1Text_acquiredEmaciator[]; /* "ACQUIRED EMACIATOR" */
extern char g_usRev1Text_acquiredEmaciatorUpgrade[]; /* "ACQUIRED EMACIATOR UPGRADE" */
extern char g_usRev1Text_acquiredWarhammerRocketUpgrade[]; /* "ACQUIRED WARHAMMER ROCKET UPGRADE" */
extern char g_usRev1Text_youHaveUnlockedS[]; /* "YOU HAVE UNLOCKED %s" */
extern char g_usRev1Text_missionFailed[]; /* "MISSION FAILED" */
extern char g_usRev1Text_itemPreviouslyAcquired[]; /* "ITEM PREVIOUSLY ACQUIRED" */
extern char g_usRev1Text_team[]; /* "TEAM" */
extern char g_usRev1Text_hit[]; /* "HIT%" */
extern char g_usRev1Text_tags[]; /* "TAGS" */
extern char g_usRev1Text_flags[]; /* "FLAGS" */
extern char g_usRev1Text_congratulationsYouHaveCompleted[]; /* "CONGRATULATIONS! YOU HAVE COMPLETED FRAG" */
extern char g_usRev1Text_congratulationsYouHaveCompletedMatchOptionLabel[]; /* "CONGRATULATIONS! YOU HAVE COMPLETED TIME" */
extern char g_usRev1Text_english[]; /* "ENGLISH" */
extern char g_usRev1Text_pistolClip10Rounds[]; /* "pistol clip (10 rounds)" */
extern char g_usRev1Text_rifleClip10Rounds[]; /* "rifle clip (10 rounds)" */
extern char g_usRev1Text_difficultyEasy[]; /* "difficulty   :     easy" */
extern char g_usRev1Text_difficultyNormal[]; /* "difficulty   :   normal" */
extern char g_usRev1Text_difficultyHard[]; /* "difficulty   :     hard" */
extern char g_usRev1Text_controlTypeExpert[]; /* "control type :   expert" */
extern char g_usRev1Text_controlTypeArcade[]; /* "control type :   arcade" */
extern char g_usRev1Text_controlType[]; /* "control type :   ??????" */
extern char g_usRev1Text_controlSideLeft[]; /* "control side :     left" */
extern char g_usRev1Text_controlSideRight[]; /* "control side :    right" */
extern char g_usRev1Text_lookSpringOn[]; /* "look spring  :       on" */
extern char g_usRev1Text_lookSpringOff[]; /* "look spring  :      off" */
extern char g_usRev1Text_autoAimOn[]; /* "auto aim     :       on" */
extern char g_usRev1Text_autoAimOff[]; /* "auto aim     :      off" */
extern char g_usRev1Text_bloodColorOff[]; /* "blood color  :      off" */
extern char g_usRev1Text_bloodColorRed[]; /* "blood color  :      red" */
extern char g_usRev1Text_bloodColorGreen[]; /* "blood color  :    green" */
extern char g_usRev1Text_2PlyrLayoutHorz[]; /* "2 plyr layout:     horz" */
extern char g_usRev1Text_2PlyrLayoutVert[]; /* "2 plyr layout:     vert" */
extern char g_usRev1Text_opacityClear[]; /* "opacity      :    clear" */
extern char g_usRev1Text_opacityOpaque[]; /* "opacity      :   opaque" */
extern char g_usRev1Text_opacity[]; /* "opacity      :         " */
extern char g_usRev1Text_controlStickHorzNorm[]; /* "control stick horz:norm" */
extern char g_usRev1Text_controlStickHorz[]; /* "control stick horz:    " */
extern char g_usRev1Text_controlStickVertNorm[]; /* "control stick vert:norm" */
extern char g_usRev1Text_controlStickVert[]; /* "control stick vert:    " */
extern char g_usRev1Text_weaponSelectQuick[]; /* "Weapon Select:    quick" */
extern char g_usRev1Text_weaponSelectNorm[]; /* "Weapon Select:     norm" */
extern char g_usRev1Text_resolutionLoRez[]; /* "Resolution   :   lo-rez" */
extern char g_usRev1Text_resolutionHiRez[]; /* "Resolution   :   hi-rez" */
extern char g_usRev1Text_resolutionHiRezLb[]; /* "Resolution   :hi-rez-lb" */
extern char g_usRev1Text_resolutionSmLoRez[]; /* "Resolution   :sm-lo-rez" */
extern char g_usRev1Text_resolutionLoRezLb[]; /* "Resolution   :lo-rez-lb" */
extern char g_usRev1Text_brightnessNorm[]; /* "brightness   :     norm" */
extern char g_usRev1Text_brightness[]; /* "brightness   :         " */
extern char g_usRev1Text_languageEnglish[]; /* "language     :  english" */
extern char g_usRev1Text_goBack[]; /* "go back" */
extern char g_usRev1Text_blueBlood[]; /* "blue blood" */
extern char g_usRev1Text_redBlood[]; /* "red blood" */
extern char g_usRev1Text_finalScore[]; /* "final score" */
extern char g_usRev1Text_blueBloodScore[]; /* "blue blood score :    " */
extern char g_usRev1Text_redBloodScore[]; /* " red blood score :    " */
extern char g_usRev1Text_pleaseWait[]; /* "please wait....." */
extern char g_usRev1Text_paused[]; /* "paused" */
extern char g_usRev1Text_missionStatus[]; /* "mission status" */
extern char g_usRev1Text_missionObjectives[]; /* "mission objectives" */
extern char g_usRev1Text_inventory[]; /* "inventory" */
extern char g_usRev1Text_load[]; /* "load" */
extern char g_usRev1Text_options[]; /* "options" */
extern char g_usRev1Text_cheats[]; /* "cheats" */
extern char g_usRev1Text_quit[]; /* "quit" */
extern char g_usRev1Text_inventoryInventoryLabel[]; /* "inventory" */
extern char g_usRev1Text_turok2_[]; /* "TUROK 2" */
extern char g_usRev1Text_deleteNote[]; /* "delete note" */
extern char g_usRev1Text_difficultyEasyPakNoteLabel[]; /* "difficulty :  easy" */
extern char g_usRev1Text_difficultyNormalPakNoteLabel[]; /* "difficulty :normal" */
extern char g_usRev1Text_difficultyHardPakNoteLabel[]; /* "difficulty :  hard" */
extern char g_usRev1Text_health[]; /* "health     :      " */
extern char g_usRev1Text_lives[]; /* "lives      :      " */
extern char g_usRev1Text_timeClockReadout[]; /* "time :000.00.00" */
extern char g_usRev1Text_noteInfo[]; /* "note info" */
extern char g_usRev1Text_deleteNoteCopies[2][12]; /* 2 x "delete note" */
extern char g_usRev1Text_nameExt[]; /* "name             ext " */
extern char g_usRev1Text_Text[]; /* "                     " */
extern char g_usRev1Text_name[]; /* "name  :            " */
extern char g_usRev1Text_type[]; /* "type  :            " */
extern char g_usRev1Text_frags[]; /* "frags :            " */
extern char g_usRev1Text_rank[]; /* "rank  :            " */
extern char g_usRev1Text_loadPakNoteLabel[]; /* "load?" */
extern char g_usRev1Text_delete[]; /* "delete?" */
extern char g_usRev1Text_deletePakNoteLabel[]; /* "delete?" */
extern char g_usRev1Text_error[]; /* "error" */
extern char g_usRev1Text_important[]; /* "important" */
extern char g_usRev1Text_loadSaveLoadMenu[]; /* "   load" */
extern char g_usRev1Text_healthSaveLoadMenu[]; /* " health" */
extern char g_usRev1Text_ammo[]; /* "   ammo" */
extern char g_usRev1Text_goBackSaveLoadMenu[]; /* "go back" */
extern char g_usRev1Text_bodyShot[]; /* "body shot!" */
extern char g_usRev1Text_headShot[]; /* "head shot!" */
extern char g_usRev1Text_armShot[]; /* "arm shot!" */
extern char g_usRev1Text_edit[]; /* "edit" */
extern char g_usRev1Text_youTagged[]; /* "you tagged " */
extern char g_usRev1Text_killedBy[]; /* "killed by " */
extern char g_usRev1Text_youKilled[]; /* "you killed " */
extern char g_usRev1Text_youKilledYourself[]; /* "you killed yourself" */
extern char g_usRev1Text_youLostTheFlag[]; /* "you lost the flag!!!" */
extern char g_usRev1Text_heDroppedTheFlag[]; /* "He dropped the flag!!!" */
extern char g_usRev1Text_areYouSure[]; /* "are you sure?" */
extern char g_usRev1Text_youWantTo[]; /* "you want to" */
extern char g_usRev1Text_yes[]; /* "yes" */
extern char g_usRev1Text_loadInGameMenuOptionLabel[]; /* "load" */
extern char g_usRev1Text_save[]; /* "save" */
extern char g_usRev1Text_enterCheat[]; /* "enter cheat" */
extern char g_usRev1Text_joinNow[]; /* "join now" */
extern char g_usRev1Text_waiting[]; /* "waiting.." */
extern char g_usRev1Text_connect[]; /* "connect.." */
extern char g_usRev1Text_goBackInGameMenuOptionLabel[]; /* "go back" */
extern char g_usRev1Text_continue[]; /* "continue ?" */
extern char g_usRev1Text_gameOver[]; /* "game over" */
extern char g_usRev1Text_timeXx[]; /* "time : xx" */
extern char g_usRev1Text_done[]; /* "done" */
extern char g_usRev1Text_newCheatEnabled[]; /* "new cheat enabled" */
extern char g_usRev1Text_invincibilityActivated[]; /* "invincibility activated" */
extern char g_usRev1Text_infiniteLivesActivated[]; /* "infinite lives activated" */
extern char g_usRev1Text_allWeaponsActivated[]; /* "all weapons activated" */
extern char g_usRev1Text_unlimitedAmmoActivated[]; /* "unlimited ammo activated" */
extern char g_usRev1Text_allKeysActivated[]; /* "all keys activated" */
extern char g_usRev1Text_bigHeadModeActivated[]; /* "big head mode activated" */
extern char g_usRev1Text_tinyModeActivated[]; /* "tiny mode activated" */
extern char g_usRev1Text_stickModeActivated[]; /* "stick mode activated" */
extern char g_usRev1Text_bigHandsAndFeet[]; /* "big hands and feet mode activated" */
extern char g_usRev1Text_penAndInkMode[]; /* "pen and ink mode activated" */
extern char g_usRev1Text_gouraudModeActivated[]; /* "gouraud mode activated" */
extern char g_usRev1Text_juansCheatActivated[]; /* "juans cheat activated" */
extern char g_usRev1Text_zachAttackCheatActivated[]; /* "zach attack cheat activated" */
extern char g_usRev1Text_allMapActivated[]; /* "all map activated" */
extern char g_usRev1Text_blackoutModeActivated[]; /* "blackout mode activated" */
extern char g_usRev1Text_mmmmTastyFrootyStripes[]; /* "mmmm... tasty frooty stripes" */
extern char g_usRev1Text_warpLevel1Activated[]; /* "warp level 1 activated" */
extern char g_usRev1Text_warpLevel2Activated[]; /* "warp level 2 activated" */
extern char g_usRev1Text_warpLevel3Activated[]; /* "warp level 3 activated" */
extern char g_usRev1Text_warpLevel4Activated[]; /* "warp level 4 activated" */
extern char g_usRev1Text_warpLevel5Activated[]; /* "warp level 5 activated" */
extern char g_usRev1Text_warpLevel6Activated[]; /* "warp level 6 activated" */
extern char g_usRev1Text_warpQueenBossActivated[]; /* "warp queen boss activated" */
extern char g_usRev1Text_warpBlindBossActivated[]; /* "warp blind one boss activated" */
extern char g_usRev1Text_warpMotherBossActivated[]; /* "warp mother boss activated" */
extern char g_usRev1Text_warpPrimagenBossActivated[]; /* "warp primagen boss activated" */
extern char g_usRev1Text_warpCreditsActivated[]; /* "warp credits activated" */
extern char g_usRev1Text_invincibilityOn[]; /* "invincibility         :  on" */
extern char g_usRev1Text_invincibilityOff[]; /* "invincibility         : off" */
extern char g_usRev1Text_infiniteLivesOn[]; /* "infinite lives        :  on" */
extern char g_usRev1Text_infiniteLivesOff[]; /* "infinite lives        : off" */
extern char g_usRev1Text_allWeaponsOn[]; /* "all weapons           :  on" */
extern char g_usRev1Text_allWeaponsOff[]; /* "all weapons           : off" */
extern char g_usRev1Text_unlimitedAmmoOn[]; /* "unlimited ammo        :  on" */
extern char g_usRev1Text_unlimitedAmmoOff[]; /* "unlimited ammo        : off" */
extern char g_usRev1Text_allSpecialObjectsOn[]; /* "all special objects   :  on" */
extern char g_usRev1Text_allSpecialObjectsOff[]; /* "all special objects   : off" */
extern char g_usRev1Text_bigHeadModeOn[]; /* "big head mode         :  on" */
extern char g_usRev1Text_bigHeadModeOff[]; /* "big head mode         : off" */
extern char g_usRev1Text_tinyModeOn[]; /* "tiny mode             :  on" */
extern char g_usRev1Text_tinyModeOff[]; /* "tiny mode             : off" */
extern char g_usRev1Text_stickModeOn[]; /* "stick mode            :  on" */
extern char g_usRev1Text_stickModeOff[]; /* "stick mode            : off" */
extern char g_usRev1Text_bigHandsFeetModeOn[]; /* "big hands / feet mode :  on" */
extern char g_usRev1Text_bigHandsFeetModeOff[]; /* "big hands / feet mode : off" */
extern char g_usRev1Text_penAndInkModeOn[]; /* "pen and ink mode      :  on" */
extern char g_usRev1Text_penAndInkModeOff[]; /* "pen and ink mode      : off" */
extern char g_usRev1Text_gouraudModeOn[]; /* "gouraud mode          :  on" */
extern char g_usRev1Text_gouraudModeOff[]; /* "gouraud mode          : off" */
extern char g_usRev1Text_juansCheatOn[]; /* "juans cheat           :  on" */
extern char g_usRev1Text_juansCheatOff[]; /* "juans cheat           : off" */
extern char g_usRev1Text_zachAttackCheatOn[]; /* "zach attack cheat     :  on" */
extern char g_usRev1Text_zachAttackCheatOff[]; /* "zach attack cheat     : off" */
extern char g_usRev1Text_allMapOn[]; /* "all map               :  on" */
extern char g_usRev1Text_allMapOff[]; /* "all map               : off" */
extern char g_usRev1Text_blackoutOn[]; /* "blackout              :  on" */
extern char g_usRev1Text_blackoutOff[]; /* "blackout              : off" */
extern char g_usRev1Text_frootyStripesOn[]; /* "frooty stripes        :  on" */
extern char g_usRev1Text_frootyStripesOff[]; /* "frooty stripes        : off" */
extern char g_usRev1Text_warpPortOfAdia[]; /* "warp:          port of adia" */
extern char g_usRev1Text_warpRiverOfSouls[]; /* "warp:        river of souls" */
extern char g_usRev1Text_warpDeathMarshes[]; /* "warp:         death marshes" */
extern char g_usRev1Text_warpLairOfThe[]; /* "warp:lair of the blind ones" */
extern char g_usRev1Text_warpHiveOfThe[]; /* "warp:   hive of the mantids" */
extern char g_usRev1Text_warpPrimagenSLightship[]; /* "warp:  primagen's lightship" */
extern char g_usRev1Text_warpQueenBoss[]; /* "warp:            queen boss" */
extern char g_usRev1Text_warpBlindBossMenuLine[]; /* "warp:        blind one boss" */
extern char g_usRev1Text_warpMotherBoss[]; /* "warp:           mother boss" */
extern char g_usRev1Text_warpPrimagenBoss[]; /* "warp:         primagen boss" */
extern char g_usRev1Text_warpCredits[]; /* "warp:               credits" */
extern char g_usRev1Text_youFragged[]; /* "you fragged" */
extern char g_usRev1Text_youTaggedOptionLabel[]; /* "you tagged" */
extern char g_usRev1Text_totals[]; /* "totals" */
extern TotalsPanels g_usRev1TotalsPanels;
extern char g_usRev1Text_player1[]; /* "player 1" */
extern char g_usRev1Text_player2[]; /* "player 2" */
extern char g_usRev1Text_player3[]; /* "player 3" */
extern char g_usRev1Text_player4[]; /* "player 4" */
extern char g_usRev1Text_single[]; /* "single" */
extern char g_usRev1Text_newGame[]; /* "new game" */
extern char g_usRev1Text_loadSinglePlayerMenuOptionLabel[]; /* "load" */
extern char g_usRev1Text_multi[]; /* "multi" */
extern char g_usRev1Text_deathmatch[]; /* "deathmatch" */
extern char g_usRev1Text_selectGameType[]; /* "select game type" */
extern char g_usRev1Text_bloodLust[]; /* "blood lust" */
extern char g_usRev1Text_bloodLustOptionLabel[]; /* "blood lust" */
extern char g_usRev1Text_timedGameNone[]; /* "timed game       :none" */
extern char g_usRev1Text_fragLimitNone[]; /* "frag limit       :none" */
extern char g_usRev1Text_levelRandom[]; /* "level:          random" */
extern char g_usRev1Text_levelExperimentata[]; /* "level:   experimentata" */
extern char g_usRev1Text_levelMoonlitMayhem[]; /* "level:  moonlit mayhem" */
extern char g_usRev1Text_levelCloseQuartered[]; /* "level: close quartered" */
extern char g_usRev1Text_levelVulcanSForge[]; /* "level:  vulcan's forge" */
extern char g_usRev1Text_levelTeleportastic[]; /* "level:   teleportastic" */
extern char g_usRev1Text_levelMirrororrim[]; /* "level:     mirrororrim" */
extern char g_usRev1Text_levelFishInA[]; /* "level:fish in a barrel" */
extern char g_usRev1Text_levelH2Whoa[]; /* "level:       h 2 whoa!" */
extern char g_usRev1Text_levelEscheria[]; /* "level:        escheria" */
extern char g_usRev1Text_levelMoshCrypt[]; /* "level:      mosh crypt" */
extern char g_usRev1Text_levelSquaresCubed[]; /* "level:   squares cubed" */
extern char g_usRev1Text_levelCrazyEight[]; /* "level:     crazy eight" */
extern char g_usRev1Text_levelBullseye[]; /* "level:        bullseye" */
extern char g_usRev1Text_textureSetCastle[]; /* "texture set:    castle" */
extern char g_usRev1Text_textureSetSteelMill[]; /* "texture set:steel mill" */
extern char g_usRev1Text_textureSetOakFort[]; /* "texture set:  oak fort" */
extern char g_usRev1Text_textureSetCatacombs[]; /* "texture set: catacombs" */
extern char g_usRev1Text_textureSetJailhouse[]; /* "texture set: jailhouse" */
extern char g_usRev1Text_textureSetBigCity[]; /* "texture set:  big city" */
extern char g_usRev1Text_textureSetRedDragon[]; /* "texture set:red dragon" */
extern char g_usRev1Text_textureSetPaintball[]; /* "texture set: paintball" */
extern char g_usRev1Text_textureSetMrHappy[]; /* "texture set:  mr happy" */
extern char g_usRev1Text_crosshairsOn[]; /* "crosshairs       :  on" */
extern char g_usRev1Text_crosshairsOff[]; /* "crosshairs       : off" */
extern char g_usRev1Text_startGame[]; /* "start game" */
extern char g_usRev1Text_goBackDeathmatchSetupOptionLabel[]; /* "go back" */
extern char g_usRev1Text_fragTag[]; /* "frag tag" */
extern char g_usRev1Text_fragTagOptionLabel[]; /* "frag tag" */
extern char g_usRev1Text_tagLimitNone[]; /* "tag limit        :none" */
extern char g_usRev1Text_levelMadhouse[]; /* "level:       madhouse!" */
extern char g_usRev1Text_levelSnap[]; /* "level:            snap" */
extern char g_usRev1Text_levelSneaksNLadders[]; /* "level:sneaks n ladders" */
extern char g_usRev1Text_levelPrimattica[]; /* "level:      primattica" */
extern char g_usRev1Text_levelCrossfire[]; /* "level:       crossfire" */
extern char g_usRev1Text_levelYNG[]; /* "level:  y.n.g.w.t.s.f." */
extern char g_usRev1Text_teamBlood[]; /* "team blood" */
extern char g_usRev1Text_customizeWeapons[]; /* "customize weapons" */
extern char g_usRev1Text_chargeDartRifleOn[]; /* "charge dart rifle : on" */
extern char g_usRev1Text_chargeDartRifleOff[]; /* "charge dart rifle :off" */
extern char g_usRev1Text_firestormOn[]; /* "firestorm         : on" */
extern char g_usRev1Text_firestormOff[]; /* "firestorm         :off" */
extern char g_usRev1Text_assaultRifleOn[]; /* "assault rifle     : on" */
extern char g_usRev1Text_assaultRifleOff[]; /* "assault rifle     :off" */
extern char g_usRev1Text_plasmaRifleOn[]; /* "plasma rifle      : on" */
extern char g_usRev1Text_plasmaRifleOff[]; /* "plasma rifle      :off" */
extern char g_usRev1Text_cerebralBoreOn[]; /* "cerebral bore     : on" */
extern char g_usRev1Text_cerebralBoreOff[]; /* "cerebral bore     :off" */
extern char g_usRev1Text_grenadeLauncherOn[]; /* "grenade launcher  : on" */
extern char g_usRev1Text_grenadeLauncherOff[]; /* "grenade launcher  :off" */
extern char g_usRev1Text_scorpionLauncherOn[]; /* "scorpion launcher : on" */
extern char g_usRev1Text_scorpionLauncherOff[]; /* "scorpion launcher :off" */
extern char g_usRev1Text_torpedoLauncherOn[]; /* "torpedo launcher  : on" */
extern char g_usRev1Text_torpedoLauncherOff[]; /* "torpedo launcher  :off" */
extern char g_usRev1Text_training[]; /* "training" */
extern char g_usRev1Text_levelRandomOptionLabel[]; /* "level      :    random" */
extern char g_usRev1Text_levelArchery[]; /* "level      :   archery" */
extern char g_usRev1Text_levelShooting[]; /* "level      :  shooting" */
extern char g_usRev1Text_levelDecathalon[]; /* "level      :decathalon" */
extern char g_usRev1Text_noOfLaps[]; /* "no of laps :          " */
extern char g_usRev1Text_startGameOptionLabel[]; /* "start game" */
extern char g_usRev1Text_goBackTrainingSetupOptionLabel[]; /* "go back" */
extern char g_usRev1Text_loadTitleMenuOptionLabel[]; /* "load" */
extern char g_usRev1Text_optionsOptionLabel[]; /* "options" */
extern char g_usRev1Text_cheatsOptionLabel[]; /* "cheats" */
extern char g_usRev1Text_checkPoint[]; /* "check point" */
extern char g_usRev1Text_savePoint[]; /* "save point" */
extern char g_usRev1Text_soundOptions[]; /* "sound options" */
extern char g_usRev1Text_musicVolumeOff[]; /* "music volume  :   off" */
extern char g_usRev1Text_musicVolumeMax[]; /* "music volume  :   max" */
extern char g_usRev1Text_musicVolumeNorm[]; /* "music volume  :  norm" */
extern char g_usRev1Text_musicVolume[]; /* "music volume  :      " */
extern char g_usRev1Text_sfxVolumeOff[]; /* "sfx volume    :   off" */
extern char g_usRev1Text_sfxVolumeMax[]; /* "sfx volume    :   max" */
extern char g_usRev1Text_sfxVolumeNorm[]; /* "sfx volume    :  norm" */
extern char g_usRev1Text_sfxVolume[]; /* "sfx volume    :      " */
extern char g_usRev1Text_speechVolumeOff[]; /* "speech volume :   off" */
extern char g_usRev1Text_speechVolumeMax[]; /* "speech volume :   max" */
extern char g_usRev1Text_speechVolumeNorm[]; /* "speech volume :  norm" */
extern char g_usRev1Text_speechVolume[]; /* "speech volume :      " */
extern char g_usRev1Text_musicNone[]; /* "music         :  none" */
extern char g_usRev1Text_music[]; /* "music         :      " */
extern char g_usRev1Text_indexNone[]; /* "index        :  none" */
extern char g_usRev1Text_speechNone[]; /* "speech       :  none" */
extern char g_usRev1Text_missionComplete[]; /* "mission complete." */
extern char g_usRev1Text_missionFailedOptionLabel[]; /* "mission failed." */
extern char g_usRev1Text_defendTheTotem[]; /* "defend the totem" */
extern char g_usRev1Text_playerSpeed[]; /* "player speed :        " */
extern char g_usRev1Text_playerSpeedDefault[]; /* "player speed : default" */
extern char g_usRev1Text_default[]; /* "default" */
extern char g_usRev1Text_lowHealth[]; /* "low health" */
/* Runs of empty 4-byte text cells. */
extern char g_usRev1Text_displayOptionsCells[][4];
extern char g_usRev1Text_pakMenuCells[][4];
extern char g_usRev1Text_saveLoadMenuCells[][4];
#endif
