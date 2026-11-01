#ifndef COMMON_PLAYER_GETPLAYERINDEX_H
#define COMMON_PLAYER_GETPLAYERINDEX_H
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/SHARED_DEBUGFIELD.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/SHARED_MENUSELECTION.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"



struct PlayerRankInner;


#include "COMMON/ITEMRECAT20V1.H"









#include "COMMON/BALLISTICPARAMS.H"




#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern const char g_playerMenuValueFormat[];
#else
extern char g_fmtDec4Pad[];
#endif
extern s32 Player_GetPlayerIndex(void *, void *);
#endif
