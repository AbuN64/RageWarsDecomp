#ifndef DATA_GFXDATA_AUDIO_DECODEFRAME_DATA_H
#define DATA_GFXDATA_AUDIO_DECODEFRAME_DATA_H
struct FragTagMatchRulesView;
extern u8 g_alternateGraphicsMicrocodeData[];
extern u8 g_alternateGraphicsMicrocodeText[];
extern u8 g_graphicsMicrocodeData[];
extern u8 g_graphicsMicrocodeText[];
#ifdef VERSION_DE
extern u8 g_backdropTextLines[1092];
#endif
extern char g_tlbMissExceptionVector[];
extern char huffman_signed6_dictionary[];
extern char huffman_signed7_five_dictionary[];
extern char huffman_signed7_nine_dictionary[];

extern u8 g_optionsSecondaryLocalizedLabels[4];
#include "Common/player_record_and_fragtag_views.h"
extern struct FragTagMatchRulesView g_gameSettingsView __asm__("g_gameSettings");
#endif
