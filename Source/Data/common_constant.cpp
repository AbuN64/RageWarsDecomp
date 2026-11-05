#if defined(VERSION_DE)

#include "Data/rest_source_records.h"


#include "include_asm.h"


#include "Common/residentstate.h"


#include "Common/runtime_declarations.h"


#include "Data/Common/common_resource_link_words.h"


#include <PR/gbi.h>


#include "Common/effectcontribution.h"


#include "Common/osviscale.h"


#include "types.h"


#include "Data/Common/g_tlbmissexceptionvector.h"


#include "Data/Common/pickup_dispatchhandler_data.h"


#include "Menu_label_slots/menu_label_slots.h"


#include "Data/Common/g_pickupammodefinitions.h"


#include "Common/gameplay_transition.h"

#if defined(VERSION_US_REV1)
struct PickupLifeDefinition {
    unsigned int labelSlot;
    unsigned short id;
    unsigned short sharedFlag;
    unsigned short reserved8[2];
    unsigned short lifePoints;
    unsigned short reserved14;
    unsigned int applyEntry;
};
#endif

CommonConstantWordsLayout g_commonConstant = {
    { (void *)&g_screenMessageSubstitutionSource, ((char *)&g_playerModeLightPattern + 2432), g_screenMessageTextCells[0], g_screenMessageTextCells[1], ((char *)&g_playerModeLightPattern + 2456), ((char *)&g_playerModeLightPattern + 2464), g_deText_2Gesundheit, g_deText_10Gesundheit, g_deText_15Gesundheit, g_deText_25Gesundheit, g_deText_50Gesundheit, g_deText_volleGesundheit, g_deText_ultraGesundheit, g_deText_1Lebenspunkt, g_deText_10Lebenspunkte, g_deText_unbesiegbarkeit, g_deText_zeitraffer, g_deText_taschenlampe, g_deText_taschenlampenbatterie, g_deText_infrarotbrille, g_deText_atemDesLebens, g_deText_augeDerWahrheit, g_deText_sprungDesGlaubens, g_deText_flSterTalisman, g_deText_herzAusFeuer, g_deText_blaueAdlerfeder, g_deText_graueAdlerfeder, g_deText_brauneAdlerfeder, g_deText_lilaAdlerfeder, g_deText_roteAdlerfeder, g_deText_partikelbeschleunigerTeil, g_deText_vergeltung, g_deText_flaggeGefordert, g_deText_flaggeErobert, g_deText_flaggeZurCkgebracht, g_deText_duHastDieMacht, g_deText_funktionNichtVerfGbar, g_deText_warhammer, g_deText_raptorKlaue, g_deText_miteBiss, g_deText_bumerang, g_deText_tekArmbrust, g_deText_mag60, g_deText_shotgun, g_deText_sturmgewehr, g_deText_minigun, g_deText_plasmaGewehr, g_deText_freezeGun, g_deText_flareGun, g_deText_granaten, g_deText_skorpion, g_deText_napalmGel, g_deText_emaciator, g_deText_inflator, g_deText_brustbrecher, g_deText_zerebralbohrer, g_deText_pfmMine, g_deText_eisenklaue, g_deText_teleportMine, g_deText_wachturm, g_deText_signalEntfernt, g_deText_zielMarkiert, g_deText_abwehrMarkiert, g_deText_verlangsamung, g_deText_schutz, g_deText_regeneration, g_deText_versteinerung, g_deText_schadensumkehr, g_deText_unsichtbarkeit, g_deText_energieBertragung, g_deText_geschwindigkeit, g_deText_teleportieren, g_deText_inSicherheitTeleportiert, g_deText_schwererSchaden, g_deText_unverwundbarkeit, g_deText_kugelschild, g_deText_energieschwund, g_deText_etwasAnderes, g_deText_schild, g_deText_anTeamKojoteAngeschlossen, g_deText_anTeamBR, g_deText_anTeamPumaAngeschlossen, g_deText_anTeamViperAngeschlossen, g_deText_wasFREine, g_deText_getTetVonS, g_deText_erwischtVonS, g_deText_geschlagenVonS, g_deText_sHatDichAusgel, g_deText_sHatDichBesiegt, g_deText_sHatDichGelyncht, g_deText_vonSZermalmt, g_deText_durchDeineEigeneHand, g_deText_wasFREineOptionsPageEntry, g_deText_schlechterZug, g_deText_hmVorsicht, g_deText_schmatz, g_deText_uups, g_deText_duWurdestBesiegt, g_deText_embryoImplantiert, g_deText_embryoZerstRt, g_deText_erledigeS, g_deText_oderFindeDenEnergiekern },
    g_deText_energiestE,
    g_deText_energiestE2,
    g_deText_schu,
    g_deText_schuAmmoList,
    g_deText_explosivgeschosse,
    g_deText_explosivgeschosseOptionsPageEntry,
    { g_deText_munition, g_deText_schuOptionsPageEntry, g_deText_energiesto, g_deText_explosivgescho, g_deText_zerebralbohrerOptionsPageEntry, g_deText_pfmMineOptionsPageEntry, g_deText_wachturmOptionsPageEntry, g_deText_eisenklaueWeaponList, g_deText_teleportMineOptionsPageEntry, g_deText_novize, g_deText_neuling, g_deText_grunzer, g_deText_scout, g_deText_held, g_deText_spurensucher, g_deText_jeger, g_deText_kempfer, g_deText_darkling, g_deText_suchender, g_deText_mnrder, g_deText_vernichter, g_deText_kriegsherr, g_deText_todeswind, g_deText_eroberer, g_deText_meister, g_deText_tyrant, g_deText_kriegssklave, g_deText_handGottes, g_deText_heuptling, g_deText_leer, g_deText_neuerSpieler, g_deText_turok, g_deText_warrior, g_deText_master, g_deText_alpha, g_deText_beta, g_deText_gamma, g_deText_campain, g_deText_slaver, g_deText_tyrantRoster, g_deText_fireborn, g_deText_icelord, g_deText_entrail, g_deText_mites, g_deText_compies, g_deText_teddies, g_deText_juggnaut, g_deText_sloth, g_deText_mauler, g_deText_drone, g_deText_grunt, g_deText_slave, g_deText_soldier, g_deText_captain, g_deText_king, g_deText_bastille, g_deText_talSet, g_deText_syra, g_deText_symbiont, g_deText_guardian, g_deText_ravage, g_deText_cyclops, g_deText_lorddead, g_deText_maggot, g_deText_vile, g_deText_elite, g_deText_biobot, g_deText_killbot, g_deText_death, g_deText_reaper, g_deText_maw, g_deText_raptor, g_deText_slag, g_deText_claw, g_deText_warclubs, g_deText_turokRoster, g_deText_mantidDrone, g_deText_campaigner, g_deText_firebornOptionsPageEntry, g_deText_mantidSoldier, g_deText_alphaRoster, g_deText_lordOfTheDead, g_deText_eliteGuard, g_deText_guardianOptionsPageEntry, g_deText_juggernaut, g_deText_oblivionSpawn, g_deText_bastilleOptionsPageEntry, g_deText_syraCharacterSelect, g_deText_symbiontOptionsPageEntry, g_deText_talSetOptionsPageEntry, g_deText_raptorCharacterSelect, g_deText_mantidMites, g_deText_flaggeDMalErobern, g_deText_flaggeDMalErobernOptionsPageEntry, g_deText_dTeamCapturesErobern, g_deText_tagTheMonkeyD, g_deText_tagTheMonkeyD2, g_deText_dKreaturTagsErobern, g_deText_dFragErobern, g_deText_dFragsErobern, g_deText_dTeamFragErobern, g_deText_dTeamFragsErobern, g_deText_in02dSekundenOder, g_deText_inDMinuteUnd, g_deText_inDMinutenUnd, g_deText_inDMinuteOder, g_deText_inDMinutenOder, g_deText_mitDLeben, g_deText_mitDLebenOptionsPageEntry, g_deText_sBesiegt, g_deText_sUndSBesiegt, g_deText_jederFRSich, g_deText_durchgefbhrtTrialOptionsPageEntry, g_deText_durchgefbhrtBasicTraining, g_deText_durchgefbhrtCrossroads, g_deText_durchgefbhrtGrimRetreat, g_deText_durchgefbhrtCathedral, g_deText_durchgefbhrtFallout, g_deText_durchgefbhrtBoxedSet, g_deText_durchgefbhrtDireStraight, g_deText_durchgefbhrtPrey, g_deText_durchgefbhrtWarehouse, g_deText_durchgefbhrtWaterTemple, g_deText_durchgefbhrtBombShelter, g_deText_durchgefbhrtTempered, g_deText_durchgefbhrtEarthTemple, g_deText_durchgefbhrtFireTemple, g_deText_durchgefbhrtMystic, g_deText_durchgefbhrtBottleneck, g_deText_durchgefbhrtTightrope, g_deText_durchgefbhrtThePit, g_deText_durchgefbhrtLeapOfFaith, g_deText_durchgefbhrtWickedDance, g_deText_durchgefbhrtBunker, g_deText_durchgefbhrtAmphitheater, g_deText_durchgefbhrtFireWalker, g_deText_durchgefbhrtCrypts, g_deText_durchgefbhrtBreakdown, g_deText_durchgefbhrtRetaliation, g_deText_durchgefbhrtHopeless, g_deText_durchgefbhrtMatrix, g_deText_durchgefbhrtFathom, g_deText_durchgefbhrtThePedestal, g_deText_durchgefbhrtDefcon5, g_deText_durchgefbhrtSpiritTemple, g_deText_durchgefbhrtStronghold, g_deText_durchgefbhrtCourtyard, g_deText_durchgefbhrtStarlight, g_deText_15FragsIn5, g_deText_25FragsIn10, g_deText_keineFrags, g_deText_fbnfmalSelbstGetntet, g_deText_letzter, g_deText_fragAuszeichnungen, g_deText_tropheenFbrAbschbsse, g_deText_10SpielerInEiner, g_deText_inDieserRundeNicht, g_deText_bastilleBesiegt, g_deText_syraBesiegt, g_deText_symbiontBesiegt, g_deText_talSetBesiegt, g_deText_kooperativSzenarioBeendet, g_deText_einfach, g_deText_mittel, g_deText_schwer, g_deText_aus, g_deText_ein, g_deText_rot, g_deText_grbn, g_deText_horizontal, g_deText_vertikal, g_deText_niedrigeAuflns, g_deText_hoheAuflns, g_deText_letterbox, g_deText_nein, g_deText_ja, g_deText_novizeOptionsPageEntry, g_deText_einfachOptionsPageEntry, g_deText_normal, g_deText_veteran, g_deText_experte, g_deText_arcade, g_deText_rad, g_deText_tap, g_deText_gemischt, g_deText_controllerD, g_deText_ctf, g_deText_tbl, g_deText_bl, g_deText_ft, g_deText_gauntlet, g_deText_fragfest, g_deText_zeitspiel, g_deText_spielerD, g_deText_adlerTalismanGefunden1, g_deText_halbenAdlerTalisman1, g_deText_zweitenAdlerTalismanGefunden, g_deText_berTalismanGefunden5, g_deText_kojoteTalismanGefunden50, g_deText_pumaTalismanGefunden50, g_deText_viperTalismanGefundenMax, g_deText_kooperativeTalismanGefunden, g_deText_minigameSymbolGefunden, g_deText_sturmgewehrGefunden, g_deText_schnellfeuerUpgradeFbrSturmgewehr, g_deText_scharfschbtzenvisierFbrTekArmbrust, g_deText_granatwerferGefunden, g_deText_granatwerferUpgradeGefunden, g_deText_plasmaGewehrGefunden, g_deText_visierFbrPlasmaGewehr, g_deText_seureangriffMnglich, g_deText_sprungklaueGefunden, g_deText_radioaktiveFlareGunGefunden, g_deText_upgradeFbrDieRadioaktive, g_deText_skorpionWerferGefunden, g_deText_magnetUpgradeFbrSkorpion, g_deText_freezeGunGefunden, g_deText_upgradeFbrFreezeGun, g_deText_napalmGelGefunden, g_deText_lasersichtgeretFbrMag60, g_deText_brustbrecherGefunden, g_deText_inflatorGefunden, g_deText_inflatorUpgradeGefunden, g_deText_bumerangGefunden, g_deText_upgradeFbrBumerangGefunden, g_deText_minigunGefunden, g_deText_schildUpgradeFbrMinigun, g_deText_shotgunStrassenfegerUpgradeGefunden, g_deText_emaciatorGefunden, g_deText_upgradeFbrEmaciatorGefunden, g_deText_warhammerRaketenUpgradeGefunden, g_deText_duHastSEntriegelt, g_deText_missionGescheitert, g_deText_gegenstandBereitsGefunden, g_deText_team, g_deText_treffer, g_deText_tags, g_deText_flags, g_deText_gratulationFragfestBberstanden, g_deText_gratulationZeitspielBeendet, g_deText_german, g_deText_pistolClip10Rounds, g_deText_rifleClip10Rounds, g_deText_schwierigkeitEinfach, g_deText_schwierigkeitMittel, g_deText_schwierigkeitSchwer, g_deText_steuermodusExperte, g_deText_steuermodusArcade, g_deText_steuermodus, g_deText_steuerseiteLinks, g_deText_steuerseiteRechts, g_deText_quellblickEin, g_deText_quellblickAus, g_deText_automZielenEin, g_deText_automZielenAus, g_deText_farbeAus, g_deText_farbeRot, g_deText_farbeGrN, g_deText_2SpLayoutHorz, g_deText_2SpLayoutVert, g_deText_oberflCheDurchsichtig, g_deText_oberflCheUndurchsichtig, g_deText_oberflChe, g_deText_controlStickHorzNorm, g_deText_controlStickHorz, g_deText_controlStickVertNorm, g_deText_controlStickVert, g_deText_waffenwahlSchnell, g_deText_waffenwahlNorm, g_deText_auflSungNiedrig, g_deText_auflSungHoch, g_deText_auflSungHochFilm, g_deText_auflSungSuperniedrig, g_deText_auflSungNiedrigFilm, g_deText_helligkeitNorm, g_deText_helligkeit, g_deText_languageGerman, g_deText_zurCk, g_deText_keins, g_deText_laden, g_deText_namenNdern, g_deText_blahblah, g_deText_handicapRows[0], g_deText_handicapRows[1], g_deText_handicapRows[2], g_deText_handicapRows[3], g_deText_handicapKeins, g_deText_handicapMax, g_deText_steuerungExperte, g_deText_steuerungArcade, g_deText_steuerung, g_deText_spielen, g_deText_diesesSpielIst, g_deText_mitDemRumble, g_deText_pakKompatibel, g_deText_bitteSetzeDas, g_deText_rumblePak, g_deText_jetztEinUmEs, g_deText_fRDiesesSpiel, g_deText_zuVerwenden, g_deText_wHlen, g_deText_blau, g_deText_rotBloodScoreMenu, g_deText_endergebnis, g_deText_ergebnisBlau, g_deText_ergebnisRot, g_deText_bitteWarten, g_deText_pause, g_deText_spielWiederAufnehmen, g_deText_missionsstatus, g_deText_mission, g_deText_inventar, g_deText_ladenInGameMenu, g_deText_optionen, g_deText_cheats, g_deText_abbrechen, g_deText_inventarOptionsPageEntry, g_deText_ok, g_deText_rageWars, g_deText_turok2_, g_deText_51, g_deText_nrwd, g_screenMessageTextCells[2775], g_screenMessageTextCells[2776], g_screenMessageTextCells[2777], g_screenMessageTextCells[2778], g_screenMessageTextCells[2779], g_screenMessageTextCells[2780], g_screenMessageTextCells[2781], g_screenMessageTextCells[2782], g_screenMessageTextCells[2783], g_screenMessageTextCells[2784], g_screenMessageTextCells[2785], g_screenMessageTextCells[2786], g_screenMessageTextCells[2787], g_screenMessageTextCells[2788], g_screenMessageTextCells[2789], g_screenMessageTextCells[2790], g_screenMessageTextCells[2791], g_screenMessageTextCells[2792], g_screenMessageTextCells[2793], g_screenMessageTextCells[2794], g_screenMessageTextCells[2795], g_screenMessageTextCells[2796], g_screenMessageTextCells[2797], g_screenMessageTextCells[2798], g_screenMessageTextCells[2799], g_screenMessageTextCells[2800], g_screenMessageTextCells[2801], g_screenMessageTextCells[2802], g_screenMessageTextCells[2803], g_deText_anderesSpiel, g_screenMessageTextCells[2808], g_screenMessageTextCells[2809], g_screenMessageTextCells[2810], g_screenMessageTextCells[2811], g_screenMessageTextCells[2812], g_screenMessageTextCells[2813], g_screenMessageTextCells[2814], g_screenMessageTextCells[2815], g_screenMessageTextCells[2816], g_screenMessageTextCells[2817], g_screenMessageTextCells[2818], g_screenMessageTextCells[2819], g_screenMessageTextCells[2820], g_screenMessageTextCells[2821], g_screenMessageTextCells[2822], g_screenMessageTextCells[2823], g_screenMessageTextCells[2824], g_screenMessageTextCells[2825], g_screenMessageTextCells[2826], g_screenMessageTextCells[2827], g_screenMessageTextCells[2828], g_screenMessageTextCells[2829], g_screenMessageTextCells[2830], g_screenMessageTextCells[2831], g_screenMessageTextCells[2840], g_screenMessageTextCells[2841], g_screenMessageTextCells[2842], g_screenMessageTextCells[2843], g_screenMessageTextCells[2844], g_screenMessageTextCells[2845], g_screenMessageTextCells[2846], g_screenMessageTextCells[2847], g_screenMessageTextCells[2848], g_screenMessageTextCells[2849], g_screenMessageTextCells[2850], g_screenMessageTextCells[2851], g_screenMessageTextCells[2852], g_deText_fehler, g_deText_wichtig, g_deText_okOptionsPageEntry, g_deText_Text, g_screenMessageTextCells[2859], g_screenMessageTextCells[2860], g_screenMessageTextCells[2861], g_screenMessageTextCells[2862], g_screenMessageTextCells[2863], g_screenMessageTextCells[2864], g_screenMessageTextCells[2865], g_screenMessageTextCells[2866], g_screenMessageTextCells[2867], g_screenMessageTextCells[2868], g_screenMessageTextCells[2869], g_screenMessageTextCells[2870], g_screenMessageTextCells[2871], g_screenMessageTextCells[2872], g_screenMessageTextCells[2873], g_screenMessageTextCells[2874], g_screenMessageTextCells[2875], g_screenMessageTextCells[2876], g_screenMessageTextCells[2877], g_screenMessageTextCells[2878], g_screenMessageTextCells[2879], g_screenMessageTextCells[2880], g_screenMessageTextCells[2881], g_screenMessageTextCells[2882], g_screenMessageTextCells[2883], g_screenMessageTextCells[2884], g_screenMessageTextCells[2885], g_screenMessageTextCells[2886], g_screenMessageTextCells[2887], g_screenMessageTextCells[2888], g_screenMessageTextCells[2889], g_screenMessageTextCells[2890], g_screenMessageTextCells[2891], g_screenMessageTextCells[2892], g_screenMessageTextCells[2893], g_screenMessageTextCells[2894], g_screenMessageTextCells[2895], g_screenMessageTextCells[2896], g_screenMessageTextCells[2897], g_screenMessageTextCells[2898], g_screenMessageTextCells[2899], g_screenMessageTextCells[2900], g_screenMessageTextCells[2901], g_screenMessageTextCells[2902], g_screenMessageTextCells[2903], g_screenMessageTextCells[2904], g_screenMessageTextCells[2905], g_screenMessageTextCells[2906], g_screenMessageTextCells[2907], g_screenMessageTextCells[2908], g_screenMessageTextCells[2909], g_screenMessageTextCells[2910], g_screenMessageTextCells[2911], g_screenMessageTextCells[2912], g_screenMessageTextCells[2913], g_screenMessageTextCells[2914], g_screenMessageTextCells[2915], g_screenMessageTextCells[2916], g_screenMessageTextCells[2917], g_screenMessageTextCells[2918], g_screenMessageTextCells[2919], g_screenMessageTextCells[2920], g_screenMessageTextCells[2921], g_screenMessageTextCells[2922], g_screenMessageTextCells[2923], g_screenMessageTextCells[2924], g_screenMessageTextCells[2925], g_screenMessageTextCells[2926], g_screenMessageTextCells[2927], g_screenMessageTextCells[2928], g_screenMessageTextCells[2929], g_screenMessageTextCells[2930], g_screenMessageTextCells[2931], g_screenMessageTextCells[2932], g_screenMessageTextCells[2933], g_screenMessageTextCells[2934], g_screenMessageTextCells[2935], g_screenMessageTextCells[2936], g_screenMessageTextCells[2937], g_screenMessageTextCells[2938], g_screenMessageTextCells[2939], g_screenMessageTextCells[2940], g_screenMessageTextCells[2941], g_screenMessageTextCells[2942], g_screenMessageTextCells[2943], g_screenMessageTextCells[2944], g_screenMessageTextCells[2945], g_screenMessageTextCells[2946], g_screenMessageTextCells[2947], g_screenMessageTextCells[2948], g_screenMessageTextCells[2949], g_screenMessageTextCells[2950], g_screenMessageTextCells[2951], g_screenMessageTextCells[2952], g_screenMessageTextCells[2953], g_screenMessageTextCells[2954], g_screenMessageTextCells[2955], g_screenMessageTextCells[2956], g_screenMessageTextCells[2957], g_screenMessageTextCells[2958], g_screenMessageTextCells[2959], g_screenMessageTextCells[2960], g_screenMessageTextCells[2961], g_screenMessageTextCells[2962], g_screenMessageTextCells[2963], g_screenMessageTextCells[2964], g_screenMessageTextCells[2965], g_screenMessageTextCells[2966], g_screenMessageTextCells[2967], g_screenMessageTextCells[2968], g_screenMessageTextCells[2969], g_screenMessageTextCells[2970], g_screenMessageTextCells[2971], g_screenMessageTextCells[2972], g_screenMessageTextCells[2973], g_screenMessageTextCells[2974], g_screenMessageTextCells[2975], g_screenMessageTextCells[2976], g_screenMessageTextCells[2977], g_screenMessageTextCells[2978], g_screenMessageTextCells[2979], g_deText_speichern, g_deText_ladenOptionsPageEntry, g_deText_gesundheit, g_deText_munitionOptionsPageEntry, g_deText_zurCkSaveLoadMenu, g_screenMessageTextCells[2995], g_screenMessageTextCells[2996], g_screenMessageTextCells[2997], g_screenMessageTextCells[2998], g_screenMessageTextCells[2999], g_screenMessageTextCells[3000], g_screenMessageTextCells[3001], g_screenMessageTextCells[3002], g_screenMessageTextCells[3003], g_screenMessageTextCells[3004], g_deText_ufmTreffer, g_deText_trefferCopies[0], g_deText_trefferCopies[1], g_deText_trefferCopies[2], g_deText_ndern, ((char *)&g_playerModeLightPattern + 14528), ((char *)&g_playerModeLightPattern + 14532), ((char *)&g_playerModeLightPattern + 14536), g_deText_tagVon, g_deText_deineTags, g_deText_besiegtVon, g_deText_besiegt, g_deText_selbstGetTet, g_deText_flaggeVerlohren, g_deText_erHatDieFlagge, g_deText_willstDu, g_deText_wirklich, g_deText_jaOptionsPageEntry, g_deText_neinOptionsPageEntry, g_deText_cheatsOptionsPageEntry, g_deText_ladenSaveMenu, g_deText_speichernOptionsPageEntry, g_deText_cheatEingeben, g_deText_jetztBeitreten, g_deText_warte, g_deText_verbinde, g_deText_zurCkConnectMenu, g_deText_weiter, g_deText_gameOver, g_deText_zeitXx, g_deText_fertig, g_deText_neuerCheatAktiviert, g_screenMessageTextCells[3100], g_screenMessageTextCells[3101], g_screenMessageTextCells[3102], g_screenMessageTextCells[3103], g_screenMessageTextCells[3104], g_screenMessageTextCells[3105], g_screenMessageTextCells[3106], g_screenMessageTextCells[3107], g_screenMessageTextCells[3108], g_screenMessageTextCells[3109], g_screenMessageTextCells[3110], g_screenMessageTextCells[3111], g_screenMessageTextCells[3112], g_screenMessageTextCells[3113], g_screenMessageTextCells[3114], g_screenMessageTextCells[3115], g_screenMessageTextCells[3116], g_screenMessageTextCells[3117], g_screenMessageTextCells[3118], g_screenMessageTextCells[3119], g_screenMessageTextCells[3120], g_screenMessageTextCells[3121], g_screenMessageTextCells[3122], g_screenMessageTextCells[3123], g_screenMessageTextCells[3124], g_screenMessageTextCells[3125], g_screenMessageTextCells[3126], g_screenMessageTextCells[3127], g_screenMessageTextCells[3128], g_screenMessageTextCells[3129], g_screenMessageTextCells[3130], g_screenMessageTextCells[3131], g_screenMessageTextCells[3132], g_screenMessageTextCells[3133], g_screenMessageTextCells[3134], g_screenMessageTextCells[3135], g_screenMessageTextCells[3136], g_screenMessageTextCells[3137], g_screenMessageTextCells[3138], g_screenMessageTextCells[3139], g_screenMessageTextCells[3140], g_screenMessageTextCells[3141], g_screenMessageTextCells[3142], g_screenMessageTextCells[3143], g_screenMessageTextCells[3144], g_screenMessageTextCells[3145], g_screenMessageTextCells[3146], g_screenMessageTextCells[3147], g_screenMessageTextCells[3148], g_screenMessageTextCells[3149], g_screenMessageTextCells[3150], g_screenMessageTextCells[3151], g_screenMessageTextCells[3152], g_screenMessageTextCells[3153], g_screenMessageTextCells[3154], g_screenMessageTextCells[3155], g_screenMessageTextCells[3156], g_screenMessageTextCells[3157], g_screenMessageTextCells[3158], g_screenMessageTextCells[3159], g_screenMessageTextCells[3160], g_screenMessageTextCells[3161], g_screenMessageTextCells[3162], g_screenMessageTextCells[3163], g_screenMessageTextCells[3164], g_screenMessageTextCells[3165], g_screenMessageTextCells[3166], g_screenMessageTextCells[3167], g_screenMessageTextCells[3168], g_screenMessageTextCells[3169], g_deText_deineFrags, g_deText_deineTagsOptionsPageEntry, g_deText_gesamt, g_deTotalsPanels[0].eins, g_deTotalsPanels[0].zwei, g_deTotalsPanels[0].drei, g_deTotalsPanels[0].vier, g_deTotalsPanels[0].tags, g_deTotalsPanels[0].frags, g_deTotalsPanels[0].erledigt, g_deTotalsPanels[0].tschuess, g_deTotalsPanels[1].eins, g_deTotalsPanels[1].zwei, g_deTotalsPanels[1].drei, g_deTotalsPanels[1].vier, g_deTotalsPanels[1].tags, g_deTotalsPanels[1].frags, g_deTotalsPanels[1].erledigt, g_deTotalsPanels[1].tschuess, g_deTotalsPanels[2].eins, g_deTotalsPanels[2].zwei, g_deTotalsPanels[2].drei, g_deTotalsPanels[2].vier, g_deTotalsPanels[2].tags, g_deTotalsPanels[2].frags, g_deTotalsPanels[2].erledigt, g_deTotalsPanels[2].tschuess, g_deTotalsPanels[3].eins, g_deTotalsPanels[3].zwei, g_deTotalsPanels[3].drei, g_deTotalsPanels[3].vier, g_deTotalsPanels[3].tags, g_deTotalsPanels[3].frags, g_deTotalsPanels[3].erledigt, g_deTotalsPanels[3].tschuess, g_deText_spieler1, g_deText_spieler2, g_deText_spieler3, g_deText_spieler4, g_deText_einzel, g_deText_neuesSpiel, g_deText_ladenSinglePlayerMenu, g_deText_mehrspieler, g_deText_mehrspielerSpiel, g_deText_spielartWHlen, g_deText_jederGegenJeden, g_deText_jederGegenJedenOptionsPageEntry, g_deText_zeitlimitKeins, g_deText_fragLimitKeins, g_deText_levelWillkRlich, g_deText_levelExperimentelles, g_deText_levelMordImMondschein, g_deText_levelAufEngemRaum, g_deText_levelSchmiedeDesVulkan, g_deText_levelTeleportersportler, g_deText_levelSpiegelrand, g_deText_levelZielscheiben, g_deText_levelWasserwahnsinn, g_deText_levelHysterie, g_deText_levelGruft, g_deText_levelImQuadrat, g_deText_levelAbartigeAcht, g_deText_levelInsSchwarze, g_deText_strukturBurg, g_deText_strukturStahlwerk, g_deText_strukturPalisadenfort, g_deText_strukturKatakomben, g_deText_strukturGefNgnis, g_deText_strukturGrossstadt, g_deText_strukturRoterDrache, g_deText_strukturPaintball, g_deText_strukturSmiley, g_deText_fadenkreuzAn, g_deText_fadenkreuzAus, g_deText_spielstart, g_deText_zurCkDeathmatchSetup, g_deText_fragTag, g_deText_fragTagOptionsPageEntry, g_deText_tagLimitKeins, g_deText_levelIrrenhaus, g_deText_levelErwischt, g_deText_levelLGenUnd, g_deText_levelPrimattica, g_deText_levelKugelhagel, g_deText_levelAndersAlsErhofft, g_deText_teamGegner, g_deText_waffenEinrichten, g_deText_gefrierkanoneAn, g_deText_gefrierkanoneAus, g_deText_feuersturmKanoneAn, g_deText_feuersturmKanoneAus, g_deText_schredderAn, g_deText_schredderAus, g_deText_plasmageschTzAn, g_deText_plasmageschTzAus, g_deText_zielsuchkanoneAn, g_deText_zielsuchkanoneAus, g_deText_granatenwerferAn, g_deText_granatenwerferAus, g_deText_skorpionRaketenwerferAn, g_deText_skorpionRaketenwerferAus, g_deText_torpedowerferAn, g_deText_torpedowerferAus, g_deText_training, g_deText_levelWillkRlichOptionsPageEntry, g_deText_levelBogenschiessen, g_deText_levelSchiessen, g_deText_levelZehnkampf, g_deText_rundenzahl, g_deText_spielstartOptionsPageEntry, g_deText_zurCkCheckpointMenu, g_deText_ladenCheckpointMenu, g_deText_optionenOptionsPageEntry, g_deText_cheatsCheckpointMenu, g_deText_checkpoint, g_deText_speicherpunkt, g_deText_soundOptionen, g_deText_lautstRkeMusikAus, g_deText_lautstRkeMusikMax, g_deText_lautstRkeMusikNorm, g_deText_lautstRkeMusik, g_deText_lautstRkeSfxAus, g_deText_lautstRkeSfxMax, g_deText_lautstRkeSfxNorm, g_deText_lautstRkeSfx, g_deText_lautstRkeSpracheAus, g_deText_lautstRkeSpracheMax, g_deText_lautstRkeSpracheNorm, g_deText_lautstRkeSprache, g_deText_musikNein, g_deText_music, g_deText_indexNein, g_deText_spracheNein, g_deText_missionBeendet, g_deText_missionGescheitertOptionsPageEntry, g_deText_totemVerteidigen, g_deText_spielertempo, g_deText_spielertempoStandard, g_deText_standard, g_deText_gesundheitSchlecht, g_deText_TextOptionsPageEntry, g_deText_0, g_deText_1, g_deText_2, g_deText_3, g_deText_4, (void *)&g_artsendPreviousTextureHoldCount, (void *)&g_artsendNextTextureHoldCount, (void *)((char *)&g_artsendNextTextureHoldCount + 4), (void *)((char *)&g_artsendNextTextureHoldCount + 8), (void *)&g_artsendPreviousPageHoldCount, (void *)((char *)&g_artsendToggleButtonHeld + 228) },
    8.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x4),
    32.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0xC),
    128.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x14),
    512.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x1C),
    2048.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x24),
    8192.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x2C),
    32768.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x34),
    131072.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x3C),
    524288.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x44),
    2097152.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x4C),
    8388608.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x54),
    33554432.0f,
    (void *)((char *)&g_creditsLocalizedLines + 0x5C),
    1.3421773e+08f,
    (void *)((char *)&g_creditsLocalizedLines + 0x64),
    5.368709e+08f,
    (void *)((char *)&g_creditsLocalizedLines + 0x6C),
    2.1474836e+09f,
    (void *)((char *)&g_creditsLocalizedLines + 0x74),
    0x50000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x7C),
    0x51000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x84),
    0x52000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x8C),
    0x53000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x94),
    0x54000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x9C),
    0x55000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xA4),
    0x56000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xAC),
    0x57000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xB4),
    0x58000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xBC),
    0x59000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xC4),
    0x5A000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xCC),
    0x30000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xD4),
    0x31000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xDC),
    0x32000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xE4),
    0x33000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xEC),
    0x34000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xF4),
    0x35000000,
    (void *)((char *)&g_creditsLocalizedLines + 0xFC),
    0x36000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x104),
    0x37000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x10C),
    3.0517578e-05f,
    (void *)((char *)&g_creditsLocalizedLines + 0x114),
    0.00012207031f,
    (void *)((char *)&g_creditsLocalizedLines + 0x11C),
    0x02000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x124),
    0x03000000,
    (void *)((char *)&g_creditsLocalizedLines + 0x12C),
    0x04000000,
    { (void *)((char *)&g_creditsLocalizedLines + 0x134), 0, &g_creditsLocalizedLines[79], &g_screenMessageSubstitutionReplacement[2], 0, 0, 0, 0, 0 },
};
#endif
