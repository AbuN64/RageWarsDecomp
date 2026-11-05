#ifndef DATA_RSP_G_BOSSACTIVTEXT_H
#define DATA_RSP_G_BOSSACTIVTEXT_H
#include "Frontend/frontend_address_symbols.h"
#include "Common/aiprofile.h"
#include "Data/rest_source_records.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Data/totals_panels.h"
extern char g_backdropTextLinesDe[];

extern char g_pakNoteTypeAdonLabel[];
extern char g_pakNoteTypeTelsetLabel[];
extern char g_pakNoteTypeFirebornLabel[];
extern char g_pakPreviewTypeLabelBuffer[];
extern char *g_pakRankThresholdTexts[12];
extern char g_pickupAmmoDefinitionsTail[]; /* label strings that follow the ammo definition table */
extern char g_profileQuantityDefaultLabelsEuStorage[];
extern char g_screenMessageSubstitutionSource[];
extern char g_videoModeDefaultLabel[];
/* Localised EU strings referenced by the boss activation text table. */
extern TotalsPanels g_euTotalsPanels;
extern TotalsPanelFr g_euFrenchTotalsPanels[4];
extern TotalsPanels g_euItalianTotalsPanels;
extern TotalsPanels g_euSpanishTotalsPanels;
extern char g_euText_cH[]; /* "C,H" */
extern char g_euText_cI[]; /* "C@I" */
extern char g_euText_ctj[]; /* "CTJ" */
/* Localised EU strings referenced by the boss activation text table. */
extern char g_euText_bB[]; /* "B´B" */
extern char g_euText_bC[]; /* "BÈC" */
extern char g_euText_bD[]; /* "BÜD" */
extern char g_euText_bE[]; /* "BðE" */
/* Runs of empty 4-byte text cells. */
extern char g_screenMessageTextCells[][4];
#endif
