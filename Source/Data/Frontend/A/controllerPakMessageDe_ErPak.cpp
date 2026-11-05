#if defined(VERSION_DE)
#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Frontend/controllerpak_message_pool.h"

char s_controllerPakMessageDe_ErPak[8] = "er pak\000";

char s_controllerPakMessageDe_ControllerPak[20] = "controller pak\000\000\000\000\000";

char s_controllerPakMessageDe_ZugriffAufDas[16] = "zugriff auf das";

char s_controllerPakMessageDe_ExpansionPakGefunden[24] = "expansion pak gefunden\000";

char s_controllerPakMessageDe_DrCkeEineTaste[20] = "DR\334CKE EINE TASTE\000\000";

char s_controllerPakMessageDe_BesuchenSieUnsereWebsiteUnter[52] = "BESUCHEN SIE UNSERE WEBSITE UNTER WWW.ACCLAIM.NET\000\000";

char s_controllerPakMessageDe_IhreGeduld[12] = "IHRE GEDULD";

char s_controllerPakMessageDe_PamTrumanUndTuckerFbr[28] = "PAM, TRUMAN UND TUCKER FbR\000";

char s_controllerPakMessageDe_UndLilly[12] = "UND LILLY\000\000";

char s_controllerPakMessageDe_JimDelbridgeHaileySebastian[36] = "JIM DELBRIDGE, HAILEY, SEBASTIAN\000\000\000";

char s_controllerPakMessageDe_AnnaLangstonSimonSkedd[28] = "ANNA LANGSTON, SIMON SKEDD,";

char s_controllerPakMessageDe_RamiFbrAllesWasSie[44] = "RAMI FbR ALLES, WAS SIE bBER AFFEN WEISS\000\000\000";

char s_controllerPakMessageDe_AngelaDafbrDassSieIn[60] = "ANGELA, DAFbR; DASS SIE IN DER NACHT AUF MICH GEWARTET HAT\000";

char s_controllerPakMessageDe_LorraineBrittanyUndKatie[32] = "LORRAINE, BRITTANY UND KATIE\000\000\000";

char s_controllerPakMessageDe_GreyThanksKasTsBehr[36] = "GREY THANKS KAS, TS BEHR UND BEN\000\000\000";

char s_controllerPakMessageDe_DanHillUndFamilie[24] = "DAN HILL UND FAMILIE\000\000\000";

char s_controllerPakMessageDe_MikeMarques[16] = "MIKE MARQUES\000\000\000";

char s_controllerPakMessageDe_SheaMackinCadeKylanUnd[40] = "SHEA MACKIN, CADE, KYLAN, UND FAMILIE\000\000";

char s_controllerPakMessageDe_HalbesTeamGeliehenHat[28] = "HALBES TEAM GELIEHEN HAT\000\000\000";

char s_controllerPakMessageDe_JeffEverettDafbrDassEr[40] = "JEFF EVERETT DAFbR; DASS ER UNS SEIN \000\000";

char s_controllerPakMessageDe_DavidUndMattImSatellite[36] = "DAVID UND MATT IM SATELLITE-STUDIO\000";

char s_controllerPakMessageDe_BrotherIchVermisseDich[28] = "BROTHER. ICH VERMISSE DICH.";

char s_controllerPakMessageDe_DrDonTHueyJr[40] = "DR. DON T. HUEY, JR., D.C. - MEIN BIG\000\000";

char s_controllerPakMessageDe_DassIchTunDurfteWas[44] = "DASS ICH TUN DURFTE; WAS MIR SPASS MACHT!\000\000";

char s_controllerPakMessageDe_MarleneUndRaymondPaciniDanke[36] = "MARLENE UND RAYMOND PACINI - DANKE,";

char s_controllerPakMessageDe_DamarisAuchCocoUndSnikers[36] = "DAMARIS (AUCH COCO UND SNIKERS!)\000\000\000";

char s_controllerPakMessageDe_JennyCowlishaw[16] = "JENNY COWLISHAW";

char s_controllerPakMessageDe_NochMehrDankAn[32] = "           NOCH MEHR DANK AN\000\000\000";

char s_controllerPakMessageDe_WarenDanken[16] = "WAREN, DANKEN.\000";

char s_controllerPakMessageDe_VerstendnisDassWirNieZuhause[36] = "VERSTeNDNIS, DASS WIR NIE ZUHAUSE\000\000";

char s_controllerPakMessageDe_IhreUnterstbtzungUndIhr[28] = "IHRE UNTERSTbTZUNG UND IHR\000";

char s_controllerPakMessageDe_FreundenUndFamilienFbr[28] = "FREUNDEN UND FAMILIEN FbR\000\000";

char s_controllerPakMessageDe_WirMnchtenBesondersUnseren[32] = "WIR MnCHTEN BESONDERS UNSEREN \000";

char s_controllerPakMessageDe_BesondererDankAn[44] = "                      BESONDERER DANK AN\000\000\000";

char s_controllerPakMessageDe_EdFortune[12] = "ED FORTUNE\000";

char s_controllerPakMessageDe_OnlineEditor[16] = "ONLINE-EDITOR\000\000";

char s_controllerPakMessageDe_BobbySaha[12] = "BOBBY SAHA\000";

char s_controllerPakMessageDe_InternetArchitekt[20] = "INTERNET-ARCHITEKT\000";

char s_controllerPakMessageDe_BenFischbach[16] = "BEN FISCHBACH\000\000";

char s_controllerPakMessageDe_SrManagerAcclaimOnline[28] = "SR. MANAGER ACCLAIM ONLINE\000";

char s_controllerPakMessageDe_MichelleSeebach[20] = "MICHELLE SEEBACH\000\000\000";

char s_controllerPakMessageDe_PrManager[12] = "PR-MANAGER\000";

char s_controllerPakMessageDe_JackScalici[16] = "JACK SCALICI\000\000\000";

char s_controllerPakMessageDe_JpCarnovale[16] = "JP CARNOVALE\000\000\000";

char s_controllerPakMessageDe_MarketingSpielanalyse[24] = "MARKETING-SPIELANALYSE\000";

char s_controllerPakMessageDe_DonJackson[12] = "DON JACKSON";

char s_controllerPakMessageDe_MarketingProduktmanager[28] = "MARKETING-PRODUKTMANAGER\000\000\000";

char s_controllerPakMessageDe_UlisesBatalla[16] = "ULISES BATALLA\000";

char s_controllerPakMessageDe_ChrisFrisone[16] = "CHRIS FRISONE\000\000";

char s_controllerPakMessageDe_MikeSterzel[16] = "MIKE STERZEL\000\000\000";

char s_controllerPakMessageDe_ChrisZino[12] = "CHRIS ZINO\000";

char s_controllerPakMessageDe_Techniker[12] = "TECHNIKER\000\000";

char s_controllerPakMessageDe_AnthonyGentile[16] = "ANTHONY GENTILE";

char s_controllerPakMessageDe_TurnoverTechniker[20] = "TURNOVER-TECHNIKER\000";

char s_controllerPakMessageDe_ChrisMaher[12] = "CHRIS MAHER";

char s_controllerPakMessageDe_TurnoverKoordinator[24] = "TURNOVER-KOORDINATOR\000\000\000";

char s_controllerPakMessageDe_MaxImas[12] = "MAX IMAS\000\000\000";

char s_controllerPakMessageDe_LloydThompson[16] = "LLOYD THOMPSON\000";

char s_controllerPakMessageDe_MarkBerkowitz[16] = "MARK BERKOWITZ\000";

char s_controllerPakMessageDe_JayCapozello[16] = "JAY CAPOZELLO\000\000";

char s_controllerPakMessageDe_DjPeluso[12] = "DJ PELUSO\000\000";

char s_controllerPakMessageDe_PaulJohnson[16] = "PAUL JOHNSON\000\000\000";

char s_controllerPakMessageDe_JoeCarbone[12] = "JOE CARBONE";

char s_controllerPakMessageDe_MauricePhilips[16] = "MAURICE PHILIPS";

char s_controllerPakMessageDe_ScottSnopowski[16] = "SCOTT SNOPOWSKI";

char s_controllerPakMessageDe_LucAngrandIi[16] = "LUC ANGRAND II\000";

char s_controllerPakMessageDe_BrhettHohwald[16] = "BRHETT HOHWALD\000";

char s_controllerPakMessageDe_DanBadilla[12] = "DAN BADILLA";

char s_controllerPakMessageDe_JoshuaRogers[16] = "JOSHUA ROGERS\000\000";

char s_controllerPakMessageDe_PaulDicarlo[16] = "PAUL DICARLO\000\000\000";

char s_controllerPakMessageDe_JonNicolai[12] = "JON NICOLAI";

char s_controllerPakMessageDe_ChrisRappo[12] = "CHRIS RAPPO";

char s_controllerPakMessageDe_Projektleiter[16] = "PROJEKTLEITER\000\000";

char s_controllerPakMessageDe_MattCanonico[16] = "MATT CANONICO\000\000";

char s_controllerPakMessageDe_MarkGarone[12] = "MARK GARONE";

char s_controllerPakMessageDe_Analyse[8] = "ANALYSE";

char s_controllerPakMessageDe_MikePatterson[16] = "MIKE PATTERSON\000";

char s_controllerPakMessageDe_BrianRegan[12] = "BRIAN REGAN";

char s_controllerPakMessageDe_LeitungAnalyse[16] = "LEITUNG ANALYSE";

char s_controllerPakMessageDe_JeffRosa[12] = "JEFF ROSA\000\000";

char s_controllerPakMessageDe_DaleTaylor[12] = "DALE TAYLOR";

char s_controllerPakMessageDe_QsLeitung[12] = "QS-LEITUNG\000";

char s_controllerPakMessageDe_CarolCaracciolo[20] = "CAROL CARACCIOLO\000\000\000";

char s_controllerPakMessageDe_QsManager[12] = "QS-MANAGER\000";

char s_controllerPakMessageDe_BillDickson[16] = "BILL DICKSON\000\000\000";

char s_controllerPakMessageDe_Handbuch[12] = "HANDBUCH\000\000\000";

char s_controllerPakMessageDe_NicoleRuisi[16] = "NICOLE RUISI\000\000\000";

char s_controllerPakMessageDe_KathleenByrne[16] = "KATHLEEN BYRNE\000";

char s_controllerPakMessageDe_JamesDaly[12] = "JAMES DALY\000";

char s_controllerPakMessageDe_Produzent[12] = "PRODUZENT\000\000";

char s_controllerPakMessageDe_NyProductDevelopment[44] = "                  NY PRODUCT DEVELOPMENT\000\000\000";

char s_controllerPakMessageDe_AcclaimEntertainmentInc[44] = "                ACCLAIM ENTERTAINMENT INC.\000";

char s_controllerPakMessageDe_PublisherCredits[48] = "                           PUBLISHER-CREDITS\000\000\000";

char s_controllerPakMessageDe_DarrenStubbington[20] = "DARREN STUBBINGTON\000";

char s_controllerPakMessageDe_AusfbherenderVpDerAcclaimStudios[40] = "AUSFbHERENDER VP DER ACCLAIM STUDIOS\000\000\000";

char s_controllerPakMessageDe_CraigGalley[16] = "CRAIG GALLEY\000\000\000";

char s_controllerPakMessageDe_VpTechnologie[16] = "VP TECHNOLOGIE\000";

char s_controllerPakMessageDe_CyrusLum[12] = "CYRUS LUM\000\000";

char s_controllerPakMessageDe_VpFbrDieDigitalproduktion[32] = "VP FbR DIE DIGITALPRODUKTION \000\000";

char s_controllerPakMessageDe_NigelCook[12] = "NIGEL COOK\000";

char s_controllerPakMessageDe_VpFbrProduktentwicklungUndDesign[40] = "VP FbR PRODUKTENTWICKLUNG UND DESIGN\000\000\000";

char s_controllerPakMessageDe_WeltweitesManagement[48] = "                       WELTWEITES MANAGEMENT\000\000\000";

char s_controllerPakMessageDe_AlanJohnson[16] = "ALAN JOHNSON\000\000\000";

char s_controllerPakMessageDe_LeitungDigitalproduktion[28] = "LEITUNG DIGITALPRODUKTION\000\000";

char s_controllerPakMessageDe_AudioManager[16] = "AUDIO-MANAGER\000\000";

char s_controllerPakMessageDe_Kreativdirektor[16] = "KREATIVDIREKTOR";

char s_controllerPakMessageDe_MalcolmCrummack[20] = "MALCOLM CRUMMACK\000\000\000";

char s_controllerPakMessageDe_LeiterProduktentwicklung[28] = "LEITER PRODUKTENTWICKLUNG\000\000";

char s_controllerPakMessageDe_StevenBroumley[16] = "STEVEN BROUMLEY";

char s_controllerPakMessageDe_TechnischerLeiter[20] = "TECHNISCHER LEITER\000";

char s_controllerPakMessageDe_RussellByrd[16] = "RUSSELL BYRD\000\000\000";

char s_controllerPakMessageDe_GmDerAcclaimStudiosAustin[32] = "GM DER ACCLAIM STUDIOS, AUSTIN\000";

char s_controllerPakMessageDe_LeitungAcclaimStudiosAustin[40] = "        LEITUNG ACCLAIM STUDIOS, AUSTIN";

char s_controllerPakMessageDe_MarcSchaefgenLordOfThe[36] = "MARC SCHAEFGEN - LORD OF THE DEAD\000\000";

char s_controllerPakMessageDe_TitosMenchacaTalSet[28] = "TITOS MENCHACA - TAL SET\000\000\000";

char s_controllerPakMessageDe_DougForrestBastille[24] = "DOUG FORREST - BASTILLE";

char s_controllerPakMessageDe_JoseBrownOblivionGuardian[36] = "JOSE BROWN - OBLIVION / GUARDIAN\000\000\000";

char s_controllerPakMessageDe_DavidDienstbierCampaigner[32] = "DAVID DIENSTBIER - CAMPAIGNER\000\000";

char s_controllerPakMessageDe_DavidKrauseFirebornDinosoids[36] = "DAVID KRAUSE - FIREBORN / DINOSOIDS";

char s_controllerPakMessageDe_JessicaRobertsonSyra[28] = "JESSICA ROBERTSON - SYRA\000\000\000";

char s_controllerPakMessageDe_ToddLowePurlin[20] = "TODD LOWE - PURLIN\000";

char s_controllerPakMessageDe_BernadetteNasonAdon[24] = "BERNADETTE NASON - ADON";

char s_controllerPakMessageDe_TravisDavisTurok[24] = "TRAVIS DAVIS - TUROK\000\000\000";

char s_controllerPakMessageDe_Sprecher[32] = "                       SPRECHER";

char s_controllerPakMessageDe_JustinWithers[16] = "JUSTIN WITHERS\000";

char s_controllerPakMessageDe_ShaneTate[12] = "SHANE TATE\000";

char s_controllerPakMessageDe_JimStrong[12] = "JIM STRONG\000";

char s_controllerPakMessageDe_BrandonRowlett[16] = "BRANDON ROWLETT";

char s_controllerPakMessageDe_MarkRichards[16] = "MARK RICHARDS\000\000";

char s_controllerPakMessageDe_ChrisKendall[16] = "CHRIS KENDALL\000\000";

char s_controllerPakMessageDe_JerremyArnston[16] = "JERREMY ARNSTON";

char s_controllerPakMessageDe_Tester[44] = "                                   TESTER\000\000";

char s_controllerPakMessageDe_RussBrewer[12] = "RUSS BREWER";

char s_controllerPakMessageDe_Projektleitung[16] = "PROJEKTLEITUNG\000";

char s_controllerPakMessageDe_ToddDowd[12] = "TODD DOWD\000\000";

char s_controllerPakMessageDe_LeiterQs[12] = "LEITER QS\000\000";

char s_controllerPakMessageDe_AustinQs[40] = "                           AUSTIN-QS\000\000\000";

char s_controllerPakMessageDe_JohnHenke[12] = "JOHN HENKE\000";

char s_controllerPakMessageDe_MarcSchaefgen[16] = "MARC SCHAEFGEN\000";

char s_controllerPakMessageDe_DarrenMitchell[16] = "DARREN MITCHELL";

char s_controllerPakMessageDe_Sounddesign[40] = "                           SOUNDDESIGN\000";

char s_controllerPakMessageDe_BeyBickerton[16] = "BEY BICKERTON\000\000";

char s_controllerPakMessageDe_DavidDienstbier[20] = "DAVID DIENSTBIER\000\000\000";

char s_controllerPakMessageDe_ZusetzlichesDesign[44] = "                       ZUSeTZLICHES DESIGN\000";

char s_controllerPakMessageDe_BrianWatson[16] = "BRIAN WATSON\000\000\000";

char s_controllerPakMessageDe_DavidSmith[12] = "DAVID SMITH";

char s_controllerPakMessageDe_AndyOneil[12] = "ANDY ONEIL\000";

char s_controllerPakMessageDe_StevanHird[12] = "STEVAN HIRD";

char s_controllerPakMessageDe_SteveBroumley[16] = "STEVE BROUMLEY\000";

char s_controllerPakMessageDe_ZusetzlicheProgrammierung[48] = "                   ZUSeTZLICHE PROGRAMMIERUNG\000\000";

char s_controllerPakMessageDe_DigitalImagingGroup[24] = "DIGITAL IMAGING GROUP\000\000";

char s_controllerPakMessageDe_RyanTracy[12] = "RYAN TRACY\000";

char s_controllerPakMessageDe_AlexOmlansky[16] = "ALEX OMLANSKY\000\000";

char s_controllerPakMessageDe_PeterFranco[16] = "PETER FRANCO\000\000\000";

char s_controllerPakMessageDe_ScottBrocker[16] = "SCOTT BROCKER\000\000";

char s_controllerPakMessageDe_ZusetzlichesDesignCopy[48] = "                         ZUSeTZLICHES DESIGN\000\000\000";

char s_controllerPakMessageDe_RobWhitakerDigitalproduktion[36] = "ROB WHITAKER - DIGITALPRODUKTION\000\000\000";

char s_controllerPakMessageDe_RobertWilsherDigitalproduktion[36] = "ROBERT WILSHER - DIGITALPRODUKTION\000";

char s_controllerPakMessageDe_JeffSheltonDesign[24] = "JEFF SHELTON - DESIGN\000\000";

char s_controllerPakMessageDe_RobbieMillerDigitalproduktion[36] = "ROBBIE MILLER - DIGITALPRODUKTION\000\000";

char s_controllerPakMessageDe_PaulMastersProgrammierung[32] = "PAUL MASTERS - PROGRAMMIERUNG\000\000";

char s_controllerPakMessageDe_BradMarquesDigitalproduktion[36] = "BRAD MARQUES - DIGITALPRODUKTION\000\000\000";

char s_controllerPakMessageDe_MarcMackinDigitalproduktion[32] = "MARC MACKIN - DIGITALPRODUKTION";

char s_controllerPakMessageDe_TrevorLemoineDigitalproduktion[36] = "TREVOR LEMOINE - DIGITALPRODUKTION\000";

char s_controllerPakMessageDe_MattKyleProgrammierung[28] = "MATT KYLE - PROGRAMMIERUNG\000";

char s_controllerPakMessageDe_MichaelHueyDesign[24] = "MICHAEL HUEY - DESIGN\000\000";

char s_controllerPakMessageDe_NeillGlancyDesign[24] = "NEILL GLANCY - DESIGN\000\000";

char s_controllerPakMessageDe_MichaelFongDigitalproduktion[36] = "MICHAEL FONG - DIGITALPRODUKTION\000\000\000";

char s_controllerPakMessageDe_JimCowlishawProgrammierung[32] = "JIM COWLISHAW - PROGRAMMIERUNG\000";

char s_controllerPakMessageDe_BruceCoonerProgrammierung[32] = "BRUCE COONER - PROGRAMMIERUNG\000\000";

char s_controllerPakMessageDe_JasonBehrDesign[20] = "JASON BEHR - DESIGN";

char s_controllerPakMessageDe_MichaelDaubert[16] = "MICHAEL DAUBERT";

char s_controllerPakMessageDe_KbnstlerischeLeitung[24] = "KbNSTLERISCHE LEITUNG\000\000";

char s_controllerPakMessageDe_FranciscoJavierLafuente[28] = "FRANCISCO JAVIER LAFUENTE\000\000";

char s_controllerPakMessageDe_Programmierleitung[20] = "PROGRAMMIERLEITUNG\000";

char s_controllerPakMessageDe_MarkPacini[12] = "MARK PACINI";

char s_controllerPakMessageDe_Projektmanager[16] = "PROJEKTMANAGER\000";

char s_controllerPakMessageDe_RageWarsTeam[48] = "                           RAGE WARS TEAM\000\000\000\000\000\000";
#endif
