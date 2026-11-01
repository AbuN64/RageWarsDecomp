#include "TYPES.H" /* the draft_fields struct headers below spell s32/u16/u8; types.h must precede them */
#include "FRONTEND/PAKMENU.H"
#include "COMMON/MEASUREDRECAT0V1.H"
#include "COMMON/MEASURED.H"
#include "COMMON/MEASUREDRECAT14V4.H"
#include "COMMON/MEASUREDRECAT14V2.H"
#include "COMMON/AIPROFILE.H"
#include <ultra64.h>
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/GROUP.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/MTX.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "COMMON/COLORENTRY.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/RESULTS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/OBJRECAT18V1.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/OSVISCALE.H"
#include "COMMON/CTX.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/LABEL.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/STATERECAT91.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/OBJB.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ARGB_COLOR.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_FINDPROFILEOWNER.H"

/* Initializes four player-menu slots and selects the first available child node. */

#if defined(VERSION_DE)
enum { PAK_SLOT_RESOURCE_688 = 716, PAK_SLOT_RESOURCE_689 = 713, PAK_SLOT_RESOURCE_690 = 714, PAK_SLOT_RESOURCE_691 = 715, PAK_SLOT_RESOURCE_692 = 712, PAK_SLOT_RESOURCE_694 = 718 };
#elif defined(VERSION_EU)
enum { PAK_SLOT_RESOURCE_688 = 688, PAK_SLOT_RESOURCE_689 = 689, PAK_SLOT_RESOURCE_690 = 690, PAK_SLOT_RESOURCE_691 = 691, PAK_SLOT_RESOURCE_692 = 692, PAK_SLOT_RESOURCE_694 = 694 };

extern void *g_slotSelectionTextReferenceShared7[];
extern void *g_slotSelectionTextReferenceShared6[];

#elif defined(VERSION_EU_X)
enum { PAK_SLOT_RESOURCE_688 = 764, PAK_SLOT_RESOURCE_689 = 761, PAK_SLOT_RESOURCE_690 = 762, PAK_SLOT_RESOURCE_691 = 760, PAK_SLOT_RESOURCE_692 = 763, PAK_SLOT_RESOURCE_694 = 766 };

extern void *g_slotSelectionTextReferenceShared7[];
extern void *g_slotSelectionTextReferenceShared6[];

#else
enum { PAK_SLOT_RESOURCE_688 = 688, PAK_SLOT_RESOURCE_689 = 689, PAK_SLOT_RESOURCE_690 = 690, PAK_SLOT_RESOURCE_691 = 691, PAK_SLOT_RESOURCE_692 = 692, PAK_SLOT_RESOURCE_694 = 694 };

#endif
extern void Widget_SetWidgetFlag100(MenuWidget *record, int enable);
extern void SmpOverlay_ShowSlotNode(s32,s32,MenuWidget *);
extern void *SmpOverlay_GetSlotValue(s32, s32);
extern s32 Widget_ListHasFlag100(struct WidgetNode *node);
void PAKInterface_BuildProfileSlotList(s32 player) {
 s32 i;
 MenuWidget *label,*value;
 g_pakProfileScreenState->players[player].chosen=0;
 /* the hub EC30 returns the item view; nodes[] hold this unit's MenuWidget storage */
 g_pakProfileScreenState->players[player].nodes[0]=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget,PAK_SLOT_RESOURCE_694);
 g_pakProfileScreenState->players[player].nodes[1]=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget,PAK_SLOT_RESOURCE_691);
 g_pakProfileScreenState->players[player].nodes[2]=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget,PAK_SLOT_RESOURCE_688);
 g_pakProfileScreenState->players[player].nodes[3]=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget,PAK_SLOT_RESOURCE_692);
 for(i=0;i<4;i++) {
  g_pakProfileScreenState->players[player].used[i]=2;
  g_pakProfileScreenState->players[player].nodes[i]->alpha=255;
  label=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].nodes[i],PAK_SLOT_RESOURCE_689);
  Widget_SetWidgetFlag100(g_pakProfileScreenState->players[player].nodes[i],0);
  value=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].nodes[i],PAK_SLOT_RESOURCE_690);
  if(g_pakProfileScreenState->players[player].records[i].player!=-1) {
   value->text=g_pakProfileScreenState->players[player].records[i].name;
   g_pakProfileScreenState->players[player].used[i]=1;
   if(g_pakProfileScreenState->phase==1) {
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].nodes[i],PAK_SLOT_RESOURCE_689),0);
    if(Frontend_FindProfileOwner(g_pakProfileScreenState->players[player].profile,g_pakProfileScreenState->players[player].records[i].owner)!=-1) {
     g_pakProfileScreenState->players[player].used[i]=0;
     Widget_SetWidgetFlag100(g_pakProfileScreenState->players[player].nodes[i],1);
     Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].nodes[i],PAK_SLOT_RESOURCE_689),1);
    }
   }
#if defined(VERSION_EU)
  } else {value->text=((g_slotSelectionTextReferenceShared7)[g_languageIndex]);Widget_SetWidgetFlag08((SlotSelectionWidget *)label,0);}
#elif defined(VERSION_EU_X)
  } else {value->text=((g_slotSelectionTextReferenceShared6)[g_languageIndex]);Widget_SetWidgetFlag08((SlotSelectionWidget *)label,0);}
#else
  } else {value->text=(g_slotSelectionTextReferenceShared1[0]);Widget_SetWidgetFlag08((SlotSelectionWidget *)label,0);}
#endif
 }
 label=SmpOverlay_GetSlotValue(g_pakProfileScreenState->root,player);
 while(Widget_ListHasFlag100(label))label=label->next;
 SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root,player,label);
}
