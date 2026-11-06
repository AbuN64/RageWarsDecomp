#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Frontend/controllerpak_message_pool.h"

/* G_WORLDEXTENTCONSTANTSDE.CPP */
#if defined(VERSION_DE)
#if defined(VERSION_DE)
extern ConstantsEncodedWordsBlock1Layout g_worldExtentConstantsDe;
#else
ConstantsEncodedWordsBlock1Layout g_worldExtentConstantsDe = {
    0x8E230020,
    4395043,
    0x0D00BC20,
    { 1e+08f, -1e+08f, 1e+08f }
};
#endif
#endif

/* G_CONTROLLERPAKMESSAGEPOOL_DE.CPP */
#if defined(VERSION_DE)
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ErPak[8];
#else
char s_controllerPakMessageDe_ErPak[8] = "er pak\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ControllerPak[20];
#else
char s_controllerPakMessageDe_ControllerPak[20] = "controller pak\000\000\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ZugriffAufDas[16];
#else
char s_controllerPakMessageDe_ZugriffAufDas[16] = "zugriff auf das";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ExpansionPakGefunden[24];
#else
char s_controllerPakMessageDe_ExpansionPakGefunden[24] = "expansion pak gefunden\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DrCkeEineTaste[20];
#else
char s_controllerPakMessageDe_DrCkeEineTaste[20] = "DR\334CKE EINE TASTE\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BesuchenSieUnsereWebsiteUnter[52];
#else
char s_controllerPakMessageDe_BesuchenSieUnsereWebsiteUnter[52] = "BESUCHEN SIE UNSERE WEBSITE UNTER WWW.ACCLAIM.NET\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_IhreGeduld[12];
#else
char s_controllerPakMessageDe_IhreGeduld[12] = "IHRE GEDULD";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_PamTrumanUndTuckerFbr[28];
#else
char s_controllerPakMessageDe_PamTrumanUndTuckerFbr[28] = "PAM, TRUMAN UND TUCKER FbR\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_UndLilly[12];
#else
char s_controllerPakMessageDe_UndLilly[12] = "UND LILLY\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JimDelbridgeHaileySebastian[36];
#else
char s_controllerPakMessageDe_JimDelbridgeHaileySebastian[36] = "JIM DELBRIDGE, HAILEY, SEBASTIAN\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AnnaLangstonSimonSkedd[28];
#else
char s_controllerPakMessageDe_AnnaLangstonSimonSkedd[28] = "ANNA LANGSTON, SIMON SKEDD,";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_RamiFbrAllesWasSie[44];
#else
char s_controllerPakMessageDe_RamiFbrAllesWasSie[44] = "RAMI FbR ALLES, WAS SIE bBER AFFEN WEISS\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AngelaDafbrDassSieIn[60];
#else
char s_controllerPakMessageDe_AngelaDafbrDassSieIn[60] = "ANGELA, DAFbR; DASS SIE IN DER NACHT AUF MICH GEWARTET HAT\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_LorraineBrittanyUndKatie[32];
#else
char s_controllerPakMessageDe_LorraineBrittanyUndKatie[32] = "LORRAINE, BRITTANY UND KATIE\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_GreyThanksKasTsBehr[36];
#else
char s_controllerPakMessageDe_GreyThanksKasTsBehr[36] = "GREY THANKS KAS, TS BEHR UND BEN\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DanHillUndFamilie[24];
#else
char s_controllerPakMessageDe_DanHillUndFamilie[24] = "DAN HILL UND FAMILIE\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MikeMarques[16];
#else
char s_controllerPakMessageDe_MikeMarques[16] = "MIKE MARQUES\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_SheaMackinCadeKylanUnd[40];
#else
char s_controllerPakMessageDe_SheaMackinCadeKylanUnd[40] = "SHEA MACKIN, CADE, KYLAN, UND FAMILIE\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_HalbesTeamGeliehenHat[28];
#else
char s_controllerPakMessageDe_HalbesTeamGeliehenHat[28] = "HALBES TEAM GELIEHEN HAT\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JeffEverettDafbrDassEr[40];
#else
char s_controllerPakMessageDe_JeffEverettDafbrDassEr[40] = "JEFF EVERETT DAFbR; DASS ER UNS SEIN \000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DavidUndMattImSatellite[36];
#else
char s_controllerPakMessageDe_DavidUndMattImSatellite[36] = "DAVID UND MATT IM SATELLITE-STUDIO\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BrotherIchVermisseDich[28];
#else
char s_controllerPakMessageDe_BrotherIchVermisseDich[28] = "BROTHER. ICH VERMISSE DICH.";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DrDonTHueyJr[40];
#else
char s_controllerPakMessageDe_DrDonTHueyJr[40] = "DR. DON T. HUEY, JR., D.C. - MEIN BIG\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DassIchTunDurfteWas[44];
#else
char s_controllerPakMessageDe_DassIchTunDurfteWas[44] = "DASS ICH TUN DURFTE; WAS MIR SPASS MACHT!\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarleneUndRaymondPaciniDanke[36];
#else
char s_controllerPakMessageDe_MarleneUndRaymondPaciniDanke[36] = "MARLENE UND RAYMOND PACINI - DANKE,";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DamarisAuchCocoUndSnikers[36];
#else
char s_controllerPakMessageDe_DamarisAuchCocoUndSnikers[36] = "DAMARIS (AUCH COCO UND SNIKERS!)\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JennyCowlishaw[16];
#else
char s_controllerPakMessageDe_JennyCowlishaw[16] = "JENNY COWLISHAW";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_NochMehrDankAn[32];
#else
char s_controllerPakMessageDe_NochMehrDankAn[32] = "           NOCH MEHR DANK AN\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_WarenDanken[16];
#else
char s_controllerPakMessageDe_WarenDanken[16] = "WAREN, DANKEN.\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_VerstendnisDassWirNieZuhause[36];
#else
char s_controllerPakMessageDe_VerstendnisDassWirNieZuhause[36] = "VERSTeNDNIS, DASS WIR NIE ZUHAUSE\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_IhreUnterstbtzungUndIhr[28];
#else
char s_controllerPakMessageDe_IhreUnterstbtzungUndIhr[28] = "IHRE UNTERSTbTZUNG UND IHR\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_FreundenUndFamilienFbr[28];
#else
char s_controllerPakMessageDe_FreundenUndFamilienFbr[28] = "FREUNDEN UND FAMILIEN FbR\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_WirMnchtenBesondersUnseren[32];
#else
char s_controllerPakMessageDe_WirMnchtenBesondersUnseren[32] = "WIR MnCHTEN BESONDERS UNSEREN \000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BesondererDankAn[44];
#else
char s_controllerPakMessageDe_BesondererDankAn[44] = "                      BESONDERER DANK AN\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_EdFortune[12];
#else
char s_controllerPakMessageDe_EdFortune[12] = "ED FORTUNE\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_OnlineEditor[16];
#else
char s_controllerPakMessageDe_OnlineEditor[16] = "ONLINE-EDITOR\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BobbySaha[12];
#else
char s_controllerPakMessageDe_BobbySaha[12] = "BOBBY SAHA\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_InternetArchitekt[20];
#else
char s_controllerPakMessageDe_InternetArchitekt[20] = "INTERNET-ARCHITEKT\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BenFischbach[16];
#else
char s_controllerPakMessageDe_BenFischbach[16] = "BEN FISCHBACH\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_SrManagerAcclaimOnline[28];
#else
char s_controllerPakMessageDe_SrManagerAcclaimOnline[28] = "SR. MANAGER ACCLAIM ONLINE\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MichelleSeebach[20];
#else
char s_controllerPakMessageDe_MichelleSeebach[20] = "MICHELLE SEEBACH\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_PrManager[12];
#else
char s_controllerPakMessageDe_PrManager[12] = "PR-MANAGER\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JackScalici[16];
#else
char s_controllerPakMessageDe_JackScalici[16] = "JACK SCALICI\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JpCarnovale[16];
#else
char s_controllerPakMessageDe_JpCarnovale[16] = "JP CARNOVALE\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarketingSpielanalyse[24];
#else
char s_controllerPakMessageDe_MarketingSpielanalyse[24] = "MARKETING-SPIELANALYSE\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DonJackson[12];
#else
char s_controllerPakMessageDe_DonJackson[12] = "DON JACKSON";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarketingProduktmanager[28];
#else
char s_controllerPakMessageDe_MarketingProduktmanager[28] = "MARKETING-PRODUKTMANAGER\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_UlisesBatalla[16];
#else
char s_controllerPakMessageDe_UlisesBatalla[16] = "ULISES BATALLA\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ChrisFrisone[16];
#else
char s_controllerPakMessageDe_ChrisFrisone[16] = "CHRIS FRISONE\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MikeSterzel[16];
#else
char s_controllerPakMessageDe_MikeSterzel[16] = "MIKE STERZEL\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ChrisZino[12];
#else
char s_controllerPakMessageDe_ChrisZino[12] = "CHRIS ZINO\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Techniker[12];
#else
char s_controllerPakMessageDe_Techniker[12] = "TECHNIKER\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AnthonyGentile[16];
#else
char s_controllerPakMessageDe_AnthonyGentile[16] = "ANTHONY GENTILE";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_TurnoverTechniker[20];
#else
char s_controllerPakMessageDe_TurnoverTechniker[20] = "TURNOVER-TECHNIKER\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ChrisMaher[12];
#else
char s_controllerPakMessageDe_ChrisMaher[12] = "CHRIS MAHER";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_TurnoverKoordinator[24];
#else
char s_controllerPakMessageDe_TurnoverKoordinator[24] = "TURNOVER-KOORDINATOR\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MaxImas[12];
#else
char s_controllerPakMessageDe_MaxImas[12] = "MAX IMAS\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_LloydThompson[16];
#else
char s_controllerPakMessageDe_LloydThompson[16] = "LLOYD THOMPSON\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarkBerkowitz[16];
#else
char s_controllerPakMessageDe_MarkBerkowitz[16] = "MARK BERKOWITZ\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JayCapozello[16];
#else
char s_controllerPakMessageDe_JayCapozello[16] = "JAY CAPOZELLO\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DjPeluso[12];
#else
char s_controllerPakMessageDe_DjPeluso[12] = "DJ PELUSO\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_PaulJohnson[16];
#else
char s_controllerPakMessageDe_PaulJohnson[16] = "PAUL JOHNSON\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JoeCarbone[12];
#else
char s_controllerPakMessageDe_JoeCarbone[12] = "JOE CARBONE";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MauricePhilips[16];
#else
char s_controllerPakMessageDe_MauricePhilips[16] = "MAURICE PHILIPS";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ScottSnopowski[16];
#else
char s_controllerPakMessageDe_ScottSnopowski[16] = "SCOTT SNOPOWSKI";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_LucAngrandIi[16];
#else
char s_controllerPakMessageDe_LucAngrandIi[16] = "LUC ANGRAND II\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BrhettHohwald[16];
#else
char s_controllerPakMessageDe_BrhettHohwald[16] = "BRHETT HOHWALD\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DanBadilla[12];
#else
char s_controllerPakMessageDe_DanBadilla[12] = "DAN BADILLA";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JoshuaRogers[16];
#else
char s_controllerPakMessageDe_JoshuaRogers[16] = "JOSHUA ROGERS\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_PaulDicarlo[16];
#else
char s_controllerPakMessageDe_PaulDicarlo[16] = "PAUL DICARLO\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JonNicolai[12];
#else
char s_controllerPakMessageDe_JonNicolai[12] = "JON NICOLAI";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ChrisRappo[12];
#else
char s_controllerPakMessageDe_ChrisRappo[12] = "CHRIS RAPPO";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Projektleiter[16];
#else
char s_controllerPakMessageDe_Projektleiter[16] = "PROJEKTLEITER\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MattCanonico[16];
#else
char s_controllerPakMessageDe_MattCanonico[16] = "MATT CANONICO\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarkGarone[12];
#else
char s_controllerPakMessageDe_MarkGarone[12] = "MARK GARONE";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Analyse[8];
#else
char s_controllerPakMessageDe_Analyse[8] = "ANALYSE";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MikePatterson[16];
#else
char s_controllerPakMessageDe_MikePatterson[16] = "MIKE PATTERSON\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BrianRegan[12];
#else
char s_controllerPakMessageDe_BrianRegan[12] = "BRIAN REGAN";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_LeitungAnalyse[16];
#else
char s_controllerPakMessageDe_LeitungAnalyse[16] = "LEITUNG ANALYSE";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JeffRosa[12];
#else
char s_controllerPakMessageDe_JeffRosa[12] = "JEFF ROSA\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DaleTaylor[12];
#else
char s_controllerPakMessageDe_DaleTaylor[12] = "DALE TAYLOR";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_QsLeitung[12];
#else
char s_controllerPakMessageDe_QsLeitung[12] = "QS-LEITUNG\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_CarolCaracciolo[20];
#else
char s_controllerPakMessageDe_CarolCaracciolo[20] = "CAROL CARACCIOLO\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_QsManager[12];
#else
char s_controllerPakMessageDe_QsManager[12] = "QS-MANAGER\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BillDickson[16];
#else
char s_controllerPakMessageDe_BillDickson[16] = "BILL DICKSON\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Handbuch[12];
#else
char s_controllerPakMessageDe_Handbuch[12] = "HANDBUCH\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_NicoleRuisi[16];
#else
char s_controllerPakMessageDe_NicoleRuisi[16] = "NICOLE RUISI\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_KathleenByrne[16];
#else
char s_controllerPakMessageDe_KathleenByrne[16] = "KATHLEEN BYRNE\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JamesDaly[12];
#else
char s_controllerPakMessageDe_JamesDaly[12] = "JAMES DALY\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Produzent[12];
#else
char s_controllerPakMessageDe_Produzent[12] = "PRODUZENT\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_NyProductDevelopment[44];
#else
char s_controllerPakMessageDe_NyProductDevelopment[44] = "                  NY PRODUCT DEVELOPMENT\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AcclaimEntertainmentInc[44];
#else
char s_controllerPakMessageDe_AcclaimEntertainmentInc[44] = "                ACCLAIM ENTERTAINMENT INC.\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_PublisherCredits[48];
#else
char s_controllerPakMessageDe_PublisherCredits[48] = "                           PUBLISHER-CREDITS\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DarrenStubbington[20];
#else
char s_controllerPakMessageDe_DarrenStubbington[20] = "DARREN STUBBINGTON\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AusfbherenderVpDerAcclaimStudios[40];
#else
char s_controllerPakMessageDe_AusfbherenderVpDerAcclaimStudios[40] = "AUSFbHERENDER VP DER ACCLAIM STUDIOS\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_CraigGalley[16];
#else
char s_controllerPakMessageDe_CraigGalley[16] = "CRAIG GALLEY\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_VpTechnologie[16];
#else
char s_controllerPakMessageDe_VpTechnologie[16] = "VP TECHNOLOGIE\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_CyrusLum[12];
#else
char s_controllerPakMessageDe_CyrusLum[12] = "CYRUS LUM\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_VpFbrDieDigitalproduktion[32];
#else
char s_controllerPakMessageDe_VpFbrDieDigitalproduktion[32] = "VP FbR DIE DIGITALPRODUKTION \000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_NigelCook[12];
#else
char s_controllerPakMessageDe_NigelCook[12] = "NIGEL COOK\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_VpFbrProduktentwicklungUndDesign[40];
#else
char s_controllerPakMessageDe_VpFbrProduktentwicklungUndDesign[40] = "VP FbR PRODUKTENTWICKLUNG UND DESIGN\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_WeltweitesManagement[48];
#else
char s_controllerPakMessageDe_WeltweitesManagement[48] = "                       WELTWEITES MANAGEMENT\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AlanJohnson[16];
#else
char s_controllerPakMessageDe_AlanJohnson[16] = "ALAN JOHNSON\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_LeitungDigitalproduktion[28];
#else
char s_controllerPakMessageDe_LeitungDigitalproduktion[28] = "LEITUNG DIGITALPRODUKTION\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AudioManager[16];
#else
char s_controllerPakMessageDe_AudioManager[16] = "AUDIO-MANAGER\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Kreativdirektor[16];
#else
char s_controllerPakMessageDe_Kreativdirektor[16] = "KREATIVDIREKTOR";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MalcolmCrummack[20];
#else
char s_controllerPakMessageDe_MalcolmCrummack[20] = "MALCOLM CRUMMACK\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_LeiterProduktentwicklung[28];
#else
char s_controllerPakMessageDe_LeiterProduktentwicklung[28] = "LEITER PRODUKTENTWICKLUNG\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_StevenBroumley[16];
#else
char s_controllerPakMessageDe_StevenBroumley[16] = "STEVEN BROUMLEY";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_TechnischerLeiter[20];
#else
char s_controllerPakMessageDe_TechnischerLeiter[20] = "TECHNISCHER LEITER\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_RussellByrd[16];
#else
char s_controllerPakMessageDe_RussellByrd[16] = "RUSSELL BYRD\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_GmDerAcclaimStudiosAustin[32];
#else
char s_controllerPakMessageDe_GmDerAcclaimStudiosAustin[32] = "GM DER ACCLAIM STUDIOS, AUSTIN\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_LeitungAcclaimStudiosAustin[40];
#else
char s_controllerPakMessageDe_LeitungAcclaimStudiosAustin[40] = "        LEITUNG ACCLAIM STUDIOS, AUSTIN";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarcSchaefgenLordOfThe[36];
#else
char s_controllerPakMessageDe_MarcSchaefgenLordOfThe[36] = "MARC SCHAEFGEN - LORD OF THE DEAD\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_TitosMenchacaTalSet[28];
#else
char s_controllerPakMessageDe_TitosMenchacaTalSet[28] = "TITOS MENCHACA - TAL SET\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DougForrestBastille[24];
#else
char s_controllerPakMessageDe_DougForrestBastille[24] = "DOUG FORREST - BASTILLE";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JoseBrownOblivionGuardian[36];
#else
char s_controllerPakMessageDe_JoseBrownOblivionGuardian[36] = "JOSE BROWN - OBLIVION / GUARDIAN\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DavidDienstbierCampaigner[32];
#else
char s_controllerPakMessageDe_DavidDienstbierCampaigner[32] = "DAVID DIENSTBIER - CAMPAIGNER\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DavidKrauseFirebornDinosoids[36];
#else
char s_controllerPakMessageDe_DavidKrauseFirebornDinosoids[36] = "DAVID KRAUSE - FIREBORN / DINOSOIDS";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JessicaRobertsonSyra[28];
#else
char s_controllerPakMessageDe_JessicaRobertsonSyra[28] = "JESSICA ROBERTSON - SYRA\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ToddLowePurlin[20];
#else
char s_controllerPakMessageDe_ToddLowePurlin[20] = "TODD LOWE - PURLIN\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BernadetteNasonAdon[24];
#else
char s_controllerPakMessageDe_BernadetteNasonAdon[24] = "BERNADETTE NASON - ADON";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_TravisDavisTurok[24];
#else
char s_controllerPakMessageDe_TravisDavisTurok[24] = "TRAVIS DAVIS - TUROK\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Sprecher[32];
#else
char s_controllerPakMessageDe_Sprecher[32] = "                       SPRECHER";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JustinWithers[16];
#else
char s_controllerPakMessageDe_JustinWithers[16] = "JUSTIN WITHERS\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ShaneTate[12];
#else
char s_controllerPakMessageDe_ShaneTate[12] = "SHANE TATE\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JimStrong[12];
#else
char s_controllerPakMessageDe_JimStrong[12] = "JIM STRONG\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BrandonRowlett[16];
#else
char s_controllerPakMessageDe_BrandonRowlett[16] = "BRANDON ROWLETT";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarkRichards[16];
#else
char s_controllerPakMessageDe_MarkRichards[16] = "MARK RICHARDS\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ChrisKendall[16];
#else
char s_controllerPakMessageDe_ChrisKendall[16] = "CHRIS KENDALL\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JerremyArnston[16];
#else
char s_controllerPakMessageDe_JerremyArnston[16] = "JERREMY ARNSTON";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Tester[44];
#else
char s_controllerPakMessageDe_Tester[44] = "                                   TESTER\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_RussBrewer[12];
#else
char s_controllerPakMessageDe_RussBrewer[12] = "RUSS BREWER";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Projektleitung[16];
#else
char s_controllerPakMessageDe_Projektleitung[16] = "PROJEKTLEITUNG\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ToddDowd[12];
#else
char s_controllerPakMessageDe_ToddDowd[12] = "TODD DOWD\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_LeiterQs[12];
#else
char s_controllerPakMessageDe_LeiterQs[12] = "LEITER QS\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AustinQs[40];
#else
char s_controllerPakMessageDe_AustinQs[40] = "                           AUSTIN-QS\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JohnHenke[12];
#else
char s_controllerPakMessageDe_JohnHenke[12] = "JOHN HENKE\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarcSchaefgen[16];
#else
char s_controllerPakMessageDe_MarcSchaefgen[16] = "MARC SCHAEFGEN\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DarrenMitchell[16];
#else
char s_controllerPakMessageDe_DarrenMitchell[16] = "DARREN MITCHELL";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Sounddesign[40];
#else
char s_controllerPakMessageDe_Sounddesign[40] = "                           SOUNDDESIGN\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BeyBickerton[16];
#else
char s_controllerPakMessageDe_BeyBickerton[16] = "BEY BICKERTON\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DavidDienstbier[20];
#else
char s_controllerPakMessageDe_DavidDienstbier[20] = "DAVID DIENSTBIER\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ZusetzlichesDesign[44];
#else
char s_controllerPakMessageDe_ZusetzlichesDesign[44] = "                       ZUSeTZLICHES DESIGN\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BrianWatson[16];
#else
char s_controllerPakMessageDe_BrianWatson[16] = "BRIAN WATSON\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DavidSmith[12];
#else
char s_controllerPakMessageDe_DavidSmith[12] = "DAVID SMITH";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AndyOneil[12];
#else
char s_controllerPakMessageDe_AndyOneil[12] = "ANDY ONEIL\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_StevanHird[12];
#else
char s_controllerPakMessageDe_StevanHird[12] = "STEVAN HIRD";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_SteveBroumley[16];
#else
char s_controllerPakMessageDe_SteveBroumley[16] = "STEVE BROUMLEY\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ZusetzlicheProgrammierung[48];
#else
char s_controllerPakMessageDe_ZusetzlicheProgrammierung[48] = "                   ZUSeTZLICHE PROGRAMMIERUNG\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_DigitalImagingGroup[24];
#else
char s_controllerPakMessageDe_DigitalImagingGroup[24] = "DIGITAL IMAGING GROUP\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_RyanTracy[12];
#else
char s_controllerPakMessageDe_RyanTracy[12] = "RYAN TRACY\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_AlexOmlansky[16];
#else
char s_controllerPakMessageDe_AlexOmlansky[16] = "ALEX OMLANSKY\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_PeterFranco[16];
#else
char s_controllerPakMessageDe_PeterFranco[16] = "PETER FRANCO\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ScottBrocker[16];
#else
char s_controllerPakMessageDe_ScottBrocker[16] = "SCOTT BROCKER\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_ZusetzlichesDesignCopy[48];
#else
char s_controllerPakMessageDe_ZusetzlichesDesignCopy[48] = "                         ZUSeTZLICHES DESIGN\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_RobWhitakerDigitalproduktion[36];
#else
char s_controllerPakMessageDe_RobWhitakerDigitalproduktion[36] = "ROB WHITAKER - DIGITALPRODUKTION\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_RobertWilsherDigitalproduktion[36];
#else
char s_controllerPakMessageDe_RobertWilsherDigitalproduktion[36] = "ROBERT WILSHER - DIGITALPRODUKTION\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JeffSheltonDesign[24];
#else
char s_controllerPakMessageDe_JeffSheltonDesign[24] = "JEFF SHELTON - DESIGN\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_RobbieMillerDigitalproduktion[36];
#else
char s_controllerPakMessageDe_RobbieMillerDigitalproduktion[36] = "ROBBIE MILLER - DIGITALPRODUKTION\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_PaulMastersProgrammierung[32];
#else
char s_controllerPakMessageDe_PaulMastersProgrammierung[32] = "PAUL MASTERS - PROGRAMMIERUNG\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BradMarquesDigitalproduktion[36];
#else
char s_controllerPakMessageDe_BradMarquesDigitalproduktion[36] = "BRAD MARQUES - DIGITALPRODUKTION\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarcMackinDigitalproduktion[32];
#else
char s_controllerPakMessageDe_MarcMackinDigitalproduktion[32] = "MARC MACKIN - DIGITALPRODUKTION";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_TrevorLemoineDigitalproduktion[36];
#else
char s_controllerPakMessageDe_TrevorLemoineDigitalproduktion[36] = "TREVOR LEMOINE - DIGITALPRODUKTION\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MattKyleProgrammierung[28];
#else
char s_controllerPakMessageDe_MattKyleProgrammierung[28] = "MATT KYLE - PROGRAMMIERUNG\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MichaelHueyDesign[24];
#else
char s_controllerPakMessageDe_MichaelHueyDesign[24] = "MICHAEL HUEY - DESIGN\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_NeillGlancyDesign[24];
#else
char s_controllerPakMessageDe_NeillGlancyDesign[24] = "NEILL GLANCY - DESIGN\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MichaelFongDigitalproduktion[36];
#else
char s_controllerPakMessageDe_MichaelFongDigitalproduktion[36] = "MICHAEL FONG - DIGITALPRODUKTION\000\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JimCowlishawProgrammierung[32];
#else
char s_controllerPakMessageDe_JimCowlishawProgrammierung[32] = "JIM COWLISHAW - PROGRAMMIERUNG\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_BruceCoonerProgrammierung[32];
#else
char s_controllerPakMessageDe_BruceCoonerProgrammierung[32] = "BRUCE COONER - PROGRAMMIERUNG\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_JasonBehrDesign[20];
#else
char s_controllerPakMessageDe_JasonBehrDesign[20] = "JASON BEHR - DESIGN";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MichaelDaubert[16];
#else
char s_controllerPakMessageDe_MichaelDaubert[16] = "MICHAEL DAUBERT";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_KbnstlerischeLeitung[24];
#else
char s_controllerPakMessageDe_KbnstlerischeLeitung[24] = "KbNSTLERISCHE LEITUNG\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_FranciscoJavierLafuente[28];
#else
char s_controllerPakMessageDe_FranciscoJavierLafuente[28] = "FRANCISCO JAVIER LAFUENTE\000\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Programmierleitung[20];
#else
char s_controllerPakMessageDe_Programmierleitung[20] = "PROGRAMMIERLEITUNG\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_MarkPacini[12];
#else
char s_controllerPakMessageDe_MarkPacini[12] = "MARK PACINI";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_Projektmanager[16];
#else
char s_controllerPakMessageDe_Projektmanager[16] = "PROJEKTMANAGER\000";
#endif
#if defined(VERSION_DE)
extern char s_controllerPakMessageDe_RageWarsTeam[48];
#else
char s_controllerPakMessageDe_RageWarsTeam[48] = "                           RAGE WARS TEAM\000\000\000\000\000\000";
#endif
#endif

/* G_CONTROLLERPAKMESSAGEPOOL_US.CPP */
#if defined(VERSION_US)
char s_controllerPakMessageUs_PActivecontrollerPak[28] = "P_ACTIVEcontroller pak\000\000\000\000\000";
char s_controllerPakMessageUs_AccessingThe[16] = "accessing the\000\000";
char s_controllerPakMessageUs_ExpansionPakFound[20] = "EXPANSION PAK FOUND";
char s_controllerPakMessageUs_PressAnyButton[20] = "PRESS ANY BUTTON\000\000\000";
char s_controllerPakMessageUs_VisitOurWebsiteAtWww[40] = "VISIT OUR WEBSITE AT WWW.ACCLAIM.NET\000\000\000";
char s_controllerPakMessageUs_TheirPatience[16] = "THEIR PATIENCE\000";
char s_controllerPakMessageUs_PamTrumanAndTuckerFor[28] = "PAM, TRUMAN AND TUCKER FOR\000";
char s_controllerPakMessageUs_AndLilly[12] = "AND LILLY\000\000";
char s_controllerPakMessageUs_JimDelbridgeHaileySebastian[36] = "JIM DELBRIDGE, HAILEY, SEBASTIAN\000\000\000";
char s_controllerPakMessageUs_AnnaLangstonSimonSkedd[28] = "ANNA LANGSTON, SIMON SKEDD,";
char s_controllerPakMessageUs_RamiForTeachingMeAbout[36] = "RAMI FOR TEACHING ME ABOUT MONKEYS\000";
char s_controllerPakMessageUs_AngelaForWaitingUpFor[40] = "ANGELA FOR WAITING UP FOR ME AT NIGHT\000\000";
char s_controllerPakMessageUs_LorraineBrittanyAndKatie[32] = "LORRAINE, BRITTANY AND KATIE\000\000\000";
char s_controllerPakMessageUs_GreyThanksKasTsBehr[36] = "GREY THANKS KAS, TS BEHR, AND BEN\000\000";
char s_controllerPakMessageUs_DanHillAndFamily[20] = "DAN HILL AND FAMILY";
char s_controllerPakMessageUs_MikeMarques[16] = "MIKE MARQUES\000\000\000";
char s_controllerPakMessageUs_SheaMackinCadeKylanAnd[40] = "SHEA MACKIN, CADE, KYLAN, AND FAMILY\000\000\000";
char s_controllerPakMessageUs_HalfOfHisTeam[20] = "HALF OF HIS TEAM\000\000\000";
char s_controllerPakMessageUs_JeffEverettForLettingUs[36] = "JEFF EVERETT FOR LETTING US BORROW\000";
char s_controllerPakMessageUs_DavidAndMattAtSatellite[36] = "DAVID AND MATT AT SATELLITE STUDIO\000";
char s_controllerPakMessageUs_BrotherBeFreeIMiss[32] = "BROTHER. BE FREE. I MISS YOU.\000\000";
char s_controllerPakMessageUs_DrDonTHueyJr[36] = "DR. DON T. HUEY, JR., D.C. - MY BIG";
char s_controllerPakMessageUs_ForLettingMeDoWhat[32] = "FOR LETTING ME DO WHAT I LOVE!\000";
char s_controllerPakMessageUs_MarleneAndRaymondPaciniThanks[36] = "MARLENE AND RAYMOND PACINI - THANKS";
char s_controllerPakMessageUs_DamarisCocoAndSnikersToo[32] = "DAMARIS (COCO AND SNIKERS TOO!)";
char s_controllerPakMessageUs_JennyCowlishaw[16] = "JENNY COWLISHAW";
char s_controllerPakMessageUs_AdditionalSpecialThanksTo[40] = "           ADDITIONAL SPECIAL THANKS TO";
char s_controllerPakMessageUs_OfWhyWeWereNever[28] = "OF WHY WE WERE NEVER HOME.\000";
char s_controllerPakMessageUs_SupportAndUnderstanding[28] = "SUPPORT AND UNDERSTANDING\000\000";
char s_controllerPakMessageUs_RageWarsTeamForTheir[28] = "RAGE WARS TEAM FOR THEIR\000\000\000";
char s_controllerPakMessageUs_FriendsAndFamilyOfThe[28] = "FRIENDS AND FAMILY OF THE\000\000";
char s_controllerPakMessageUs_ThankYouToAllOf[24] = "THANK YOU TO ALL OF THE";
char s_controllerPakMessageUs_WeWouldLikeToExtend[36] = "WE WOULD LIKE TO EXTEND A SPECIAL\000\000";
char s_controllerPakMessageUs_SpecialThanks[40] = "                      SPECIAL THANKS\000\000\000";
char s_controllerPakMessageUs_EdFortune[12] = "ED FORTUNE\000";
char s_controllerPakMessageUs_OnlineEditor[16] = "ONLINE EDITOR\000\000";
char s_controllerPakMessageUs_BobbySaha[12] = "BOBBY SAHA\000";
char s_controllerPakMessageUs_InternetArchitect[20] = "INTERNET ARCHITECT\000";
char s_controllerPakMessageUs_BenFischbach[16] = "BEN FISCHBACH\000\000";
char s_controllerPakMessageUs_SrManagerAcclaimOnline[28] = "SR. MANAGER ACCLAIM ONLINE\000";
char s_controllerPakMessageUs_MichelleSeebach[20] = "MICHELLE SEEBACH\000\000\000";
char s_controllerPakMessageUs_PrManager[12] = "PR MANAGER\000";
char s_controllerPakMessageUs_JackScalici[16] = "JACK SCALICI\000\000\000";
char s_controllerPakMessageUs_JpCarnovale[16] = "JP CARNOVALE\000\000\000";
char s_controllerPakMessageUs_MarketingGameAnalyst[24] = "MARKETING GAME ANALYST\000";
char s_controllerPakMessageUs_DonJackson[12] = "DON JACKSON";
char s_controllerPakMessageUs_MarketingProductManager[28] = "MARKETING PRODUCT MANAGER\000\000";
char s_controllerPakMessageUs_UlisesBatalla[16] = "ULISES BATALLA\000";
char s_controllerPakMessageUs_ChrisFrisone[16] = "CHRIS FRISONE\000\000";
char s_controllerPakMessageUs_MikeSterzel[16] = "MIKE STERZEL\000\000\000";
char s_controllerPakMessageUs_ChrisZino[12] = "CHRIS ZINO\000";
char s_controllerPakMessageUs_Technicians[12] = "TECHNICIANS";
char s_controllerPakMessageUs_AnthonyGentile[16] = "ANTHONY GENTILE";
char s_controllerPakMessageUs_TurnoverTechnician[20] = "TURNOVER TECHNICIAN";
char s_controllerPakMessageUs_ChrisMaher[12] = "CHRIS MAHER";
char s_controllerPakMessageUs_TurnoverCoordinator[24] = "TURNOVER COORDINATOR\000\000\000";
char s_controllerPakMessageUs_MaxImas[12] = "MAX IMAS\000\000\000";
char s_controllerPakMessageUs_LloydThompson[16] = "LLOYD THOMPSON\000";
char s_controllerPakMessageUs_MarkBerkowitz[16] = "MARK BERKOWITZ\000";
char s_controllerPakMessageUs_JayCapozello[16] = "JAY CAPOZELLO\000\000";
char s_controllerPakMessageUs_DjPeluso[12] = "DJ PELUSO\000\000";
char s_controllerPakMessageUs_PaulJohnson[16] = "PAUL JOHNSON\000\000\000";
char s_controllerPakMessageUs_JoeCarbone[12] = "JOE CARBONE";
char s_controllerPakMessageUs_MauricePhilips[16] = "MAURICE PHILIPS";
char s_controllerPakMessageUs_ScottSnopowski[16] = "SCOTT SNOPOWSKI";
char s_controllerPakMessageUs_LucAngrandIi[16] = "LUC ANGRAND II\000";
char s_controllerPakMessageUs_BrhettHohwald[16] = "BRHETT HOHWALD\000";
char s_controllerPakMessageUs_DanBadilla[12] = "DAN BADILLA";
char s_controllerPakMessageUs_JoshuaRogers[16] = "JOSHUA ROGERS\000\000";
char s_controllerPakMessageUs_PaulDicarlo[16] = "PAUL DICARLO\000\000\000";
char s_controllerPakMessageUs_JonNicolai[12] = "JON NICOLAI";
char s_controllerPakMessageUs_ChrisRappo[12] = "CHRIS RAPPO";
char s_controllerPakMessageUs_ProjectLeads[16] = "PROJECT LEADS\000\000";
char s_controllerPakMessageUs_MattCanonico[16] = "MATT CANONICO\000\000";
char s_controllerPakMessageUs_MarkGarone[12] = "MARK GARONE";
char s_controllerPakMessageUs_LeadAnalysts[16] = "LEAD ANALYSTS\000\000";
char s_controllerPakMessageUs_MikePatterson[16] = "MIKE PATTERSON\000";
char s_controllerPakMessageUs_BrianRegan[12] = "BRIAN REGAN";
char s_controllerPakMessageUs_SeniorLeadAnalyst[20] = "SENIOR LEAD ANALYST";
char s_controllerPakMessageUs_JeffRosa[12] = "JEFF ROSA\000\000";
char s_controllerPakMessageUs_DaleTaylor[12] = "DALE TAYLOR";
char s_controllerPakMessageUs_QaSupervisor[16] = "QA SUPERVISOR\000\000";
char s_controllerPakMessageUs_CarolCaracciolo[20] = "CAROL CARACCIOLO\000\000\000";
char s_controllerPakMessageUs_BillDickson[16] = "BILL DICKSON\000\000\000";
char s_controllerPakMessageUs_ManualSupportManager[24] = "MANUAL SUPPORT MANAGER\000";
char s_controllerPakMessageUs_NicoleRuisi[16] = "NICOLE RUISI\000\000\000";
char s_controllerPakMessageUs_KathleenByrne[16] = "KATHLEEN BYRNE\000";
char s_controllerPakMessageUs_ProjectTracking[20] = "PROJECT TRACKING\000\000\000";
char s_controllerPakMessageUs_JamesDaly[12] = "JAMES DALY\000";
char s_controllerPakMessageUs_Producer[12] = "PRODUCER\000\000\000";
char s_controllerPakMessageUs_NyProductDevelopment[44] = "                  NY PRODUCT DEVELOPMENT\000\000\000";
char s_controllerPakMessageUs_AcclaimEntertainmentInc[44] = "                ACCLAIM ENTERTAINMENT INC.\000";
char s_controllerPakMessageUs_PublisherCredits[48] = "                           PUBLISHER CREDITS\000\000\000";
char s_controllerPakMessageUs_DarrenStubbington[20] = "DARREN STUBBINGTON\000";
char s_controllerPakMessageUs_ExecutiveVpOfAcclaimStudios[32] = "EXECUTIVE VP OF ACCLAIM STUDIOS";
char s_controllerPakMessageUs_CraigGalley[16] = "CRAIG GALLEY\000\000\000";
char s_controllerPakMessageUs_VpOfTechnology[20] = "VP OF TECHNOLOGY\000\000\000";
char s_controllerPakMessageUs_CyrusLum[12] = "CYRUS LUM\000\000";
char s_controllerPakMessageUs_VpOfDigitalProductions[28] = "VP OF DIGITAL PRODUCTIONS\000\000";
char s_controllerPakMessageUs_NigelCook[12] = "NIGEL COOK\000";
char s_controllerPakMessageUs_VpOfProductDevelopmentAnd[40] = "VP OF PRODUCT DEVELOPMENT AND DESIGN\000\000\000";
char s_controllerPakMessageUs_GlobalDirectors[40] = "                       GLOBAL DIRECTORS";
char s_controllerPakMessageUs_AlanJohnson[16] = "ALAN JOHNSON\000\000\000";
char s_controllerPakMessageUs_DirectorOfDigitalProductions[32] = "DIRECTOR OF DIGITAL PRODUCTIONS";
char s_controllerPakMessageUs_AudioManager[16] = "AUDIO MANAGER\000\000";
char s_controllerPakMessageUs_CreativeDirector[20] = "CREATIVE DIRECTOR\000\000";
char s_controllerPakMessageUs_MalcolmCrummack[20] = "MALCOLM CRUMMACK\000\000\000";
char s_controllerPakMessageUs_DirectorOfProductDevelopment[32] = "DIRECTOR OF PRODUCT DEVELOPMENT";
char s_controllerPakMessageUs_StevenBroumley[16] = "STEVEN BROUMLEY";
char s_controllerPakMessageUs_TechnicalDirector[20] = "TECHNICAL DIRECTOR\000";
char s_controllerPakMessageUs_RussellByrd[16] = "RUSSELL BYRD\000\000\000";
char s_controllerPakMessageUs_GmOfAcclaimStudiosAustin[32] = "GM OF ACCLAIM STUDIOS AUSTIN\000\000\000";
char s_controllerPakMessageUs_AcclaimStudiosAustinDirectors[44] = "        ACCLAIM STUDIOS AUSTIN DIRECTORS\000\000\000";
char s_controllerPakMessageUs_MarcSchaefgenLordOfThe[36] = "MARC SCHAEFGEN - LORD OF THE DEAD\000\000";
char s_controllerPakMessageUs_TitosMenchacaTalSet[28] = "TITOS MENCHACA - TAL SET\000\000\000";
char s_controllerPakMessageUs_DougForrestBastille[24] = "DOUG FORREST - BASTILLE";
char s_controllerPakMessageUs_JoseBrownOblivionGuardian[36] = "JOSE BROWN - OBLIVION / GUARDIAN\000\000\000";
char s_controllerPakMessageUs_DavidDienstbierCampaigner[32] = "DAVID DIENSTBIER - CAMPAIGNER\000\000";
char s_controllerPakMessageUs_DavidKrauseFirebornDinosoids[36] = "DAVID KRAUSE - FIREBORN / DINOSOIDS";
char s_controllerPakMessageUs_JessicaRobertsonSyra[28] = "JESSICA ROBERTSON - SYRA\000\000\000";
char s_controllerPakMessageUs_ToddLowePurlin[20] = "TODD LOWE - PURLIN\000";
char s_controllerPakMessageUs_BernadetteNasonAdon[24] = "BERNADETTE NASON - ADON";
char s_controllerPakMessageUs_TravisDavisTurok[24] = "TRAVIS DAVIS - TUROK\000\000\000";
char s_controllerPakMessageUs_CharacterVoices[40] = "                       CHARACTER VOICES";
char s_controllerPakMessageUs_JustinWithers[16] = "JUSTIN WITHERS\000";
char s_controllerPakMessageUs_ShaneTate[12] = "SHANE TATE\000";
char s_controllerPakMessageUs_JimStrong[12] = "JIM STRONG\000";
char s_controllerPakMessageUs_BrandonRowlett[16] = "BRANDON ROWLETT";
char s_controllerPakMessageUs_MarkRichards[16] = "MARK RICHARDS\000\000";
char s_controllerPakMessageUs_ChrisKendall[16] = "CHRIS KENDALL\000\000";
char s_controllerPakMessageUs_JerremyArnston[16] = "JERREMY ARNSTON";
char s_controllerPakMessageUs_Testers[44] = "                                   TESTERS\000";
char s_controllerPakMessageUs_RussBrewer[12] = "RUSS BREWER";
char s_controllerPakMessageUs_ProjectLead[16] = "PROJECT LEAD\000\000\000";
char s_controllerPakMessageUs_ToddDowd[12] = "TODD DOWD\000\000";
char s_controllerPakMessageUs_QaManager[12] = "QA MANAGER\000";
char s_controllerPakMessageUs_AustinQa[40] = "                           AUSTIN QA\000\000\000";
char s_controllerPakMessageUs_JohnHenke[12] = "JOHN HENKE\000";
char s_controllerPakMessageUs_MarcSchaefgen[16] = "MARC SCHAEFGEN\000";
char s_controllerPakMessageUs_DarrenMitchell[16] = "DARREN MITCHELL";
char s_controllerPakMessageUs_SoundDesign[40] = "                           SOUND DESIGN";
char s_controllerPakMessageUs_BeyBickerton[16] = "BEY BICKERTON\000\000";
char s_controllerPakMessageUs_DavidDienstbier[20] = "DAVID DIENSTBIER\000\000\000";
char s_controllerPakMessageUs_AdditionalDesign[44] = "                       ADDITIONAL DESIGN\000\000\000";
char s_controllerPakMessageUs_BrianWatson[16] = "BRIAN WATSON\000\000\000";
char s_controllerPakMessageUs_DavidSmith[12] = "DAVID SMITH";
char s_controllerPakMessageUs_AndyOneil[12] = "ANDY ONEIL\000";
char s_controllerPakMessageUs_StevanHird[12] = "STEVAN HIRD";
char s_controllerPakMessageUs_SteveBroumley[16] = "STEVE BROUMLEY\000";
char s_controllerPakMessageUs_AdditionalProgramming[44] = "                   ADDITIONAL PROGRAMMING\000\000";
char s_controllerPakMessageUs_DigitalImagingGroup[24] = "DIGITAL IMAGING GROUP\000\000";
char s_controllerPakMessageUs_RyanTracy[12] = "RYAN TRACY\000";
char s_controllerPakMessageUs_AlexOmlansky[16] = "ALEX OMLANSKY\000\000";
char s_controllerPakMessageUs_PeterFranco[16] = "PETER FRANCO\000\000\000";
char s_controllerPakMessageUs_ScottBrocker[16] = "SCOTT BROCKER\000\000";
char s_controllerPakMessageUs_AdditionalArt[40] = "                         ADDITIONAL ART";
char s_controllerPakMessageUs_RobWhitakerDigitalProductions[36] = "ROB WHITAKER - DIGITAL PRODUCTIONS\000";
char s_controllerPakMessageUs_RobertWilsherDigitalProductions[40] = "ROBERT WILSHER - DIGITAL PRODUCTIONS\000\000\000";
char s_controllerPakMessageUs_JeffSheltonDesign[24] = "JEFF SHELTON - DESIGN\000\000";
char s_controllerPakMessageUs_RobbieMillerDigitalProductions[36] = "ROBBIE MILLER - DIGITAL PRODUCTIONS";
char s_controllerPakMessageUs_PaulMastersProgramming[28] = "PAUL MASTERS - PROGRAMMING\000";
char s_controllerPakMessageUs_BradMarquesDigitalProductions[36] = "BRAD MARQUES - DIGITAL PRODUCTIONS\000";
char s_controllerPakMessageUs_MarcMackinDigitalProductions[36] = "MARC MACKIN - DIGITAL PRODUCTIONS\000\000";
char s_controllerPakMessageUs_TrevorLemoineDigitalProductions[40] = "TREVOR LEMOINE - DIGITAL PRODUCTIONS\000\000\000";
char s_controllerPakMessageUs_MattKyleProgramming[24] = "MATT KYLE - PROGRAMMING";
char s_controllerPakMessageUs_MichaelHueyDesign[24] = "MICHAEL HUEY - DESIGN\000\000";
char s_controllerPakMessageUs_NeillGlancyDesign[24] = "NEILL GLANCY - DESIGN\000\000";
char s_controllerPakMessageUs_MichaelFongDigitalProductions[36] = "MICHAEL FONG - DIGITAL PRODUCTIONS\000";
char s_controllerPakMessageUs_JimCowlishawProgramming[28] = "JIM COWLISHAW - PROGRAMMING";
char s_controllerPakMessageUs_BruceCoonerProgramming[28] = "BRUCE COONER - PROGRAMMING\000";
char s_controllerPakMessageUs_JasonBehrDesign[20] = "JASON BEHR - DESIGN";
char s_controllerPakMessageUs_MichaelDaubert[16] = "MICHAEL DAUBERT";
char s_controllerPakMessageUs_LeadArtist[12] = "LEAD ARTIST";
char s_controllerPakMessageUs_FranciscoJavierLafuente[28] = "FRANCISCO JAVIER LAFUENTE\000\000";
char s_controllerPakMessageUs_LeadProgrammer[16] = "LEAD PROGRAMMER";
char s_controllerPakMessageUs_MarkPacini[12] = "MARK PACINI";
char s_controllerPakMessageUs_ProjectManager[16] = "PROJECT MANAGER";
char s_controllerPakMessageUs_RageWarsTea[40] = "                           RAGE WARS TEA";
unsigned int s_controllerPakMessageUs_TrailerWords[4] = { 0x4D000F00, 0x00000000, 0x106D5F6E, 0x50726564 };
#endif
