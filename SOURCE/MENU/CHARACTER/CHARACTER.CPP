#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"
#include "COMMON/ANIMATION.H"
#include "include_asm.h"
#include "MENU/CHARACTER_SELECTION_IDS.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SCREEN.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "FRONTEND/JOIN_RANDOMIZEJOINREQUESTENTRIES.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* 8041F1FC_2.CPP */
extern s32 Widget_ListHasFlag100(struct WidgetNode *);

extern void *SmpOverlay_GetSlotValue(s32, s32);

#if defined(VERSION_DE)
enum { MENU_RESOURCE = 908 };
#elif defined(VERSION_EU)
enum { MENU_RESOURCE = 914 };
#elif defined(VERSION_EU_X)
enum { MENU_RESOURCE = 918 };
#elif defined(VERSION_US)
enum { MENU_RESOURCE = 914 };
#elif defined(VERSION_US_REV1)
enum { MENU_RESOURCE = 914 };
#endif

/* JOIN_CYCLEJOINREQUESTRANK.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const float k_joinCycleRankFloatOne[1] = {
    1.0f,
};
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#endif

/* CHARACTER.CPP */
/* 8041F1FC.CPP */
#if defined(VERSION_US_REV1)
s32 CCharacterSelection_OpenCharacterSelectionScreen(s32 screen)
{
  CVector3 scale;
  s32 j;
  s32 i;
  s32 model;
  s32 row;
  SlotSelectionPlayerConfig *config;
  SlotSelectionWidget *item;
  s32 rest;
  g_characterSelectionMenu = Cache_AllocateMemory(4952);
  g_characterSelectionMenu->screen = (void *) screen;
  g_characterSelectionMenu->slotOverlay = SmpOverlay_CreateOverlayNode(screen, 4);
  SmpOverlay_ShowSlotById(screen, 0, 122);
  SmpOverlay_ShowSlotById(screen, 1, 122);
  SmpOverlay_ShowSlotById(screen, 2, 122);
  SmpOverlay_ShowSlotById(screen, 3, 122);
  Random_SetSelectedStage(0, 0);
  g_characterSelectionMenu->clock = 0;
  scale.x = 1.0f;
  scale.y = 1.0f;
  scale.z = 1.0f;
  for (i = 0; i < 4; i++)
  {
    g_characterSelectionMenu->players[i].slotOverlay = 0;
    g_characterSelectionMenu->players[i].kind = g_characterSelectionMenuEntries[i].kind;
    g_characterSelectionMenu->players[i].highlight = 0;
    g_characterSelectionMenu->players[i].selectionState = 0;
    g_characterSelectionMenu->players[i].choice = 0;
    g_characterSelectionMenu->players[i].tintFramesLeft = 0;
    model = Key_GetCharacterPreviewModel(g_characterSelectionMenu->players[i].kind);
    row = Key_FindCharacterPreviewRow(g_characterSelectionMenu->players[i].kind);
    scale.x = g_characterPortraitRecords[row].scale[i];
    scale.y = g_characterPortraitRecords[row].scale[i];
    scale.z = g_characterPortraitRecords[row].scale[i];
    Preview_InitModelPreview(g_characterSelectionMenu->players[i].model, 9, model + 911, 75, 24000, scale, g_characterPortraitRecords[row].position[i], g_characterPortraitRecords[row].distance[i], g_characterPortraitRecords[row].light[i]);
    Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].title)->alpha = 110;
    for (j = 0; j < 3; j++)
    {
      Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].cells[j].id)->alpha = 80;
      Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].options[j].id), 1);
    }

  }

  g_characterSelectionMenu->phase = 1;
  g_characterSelectionMenu->timer = 4;
  g_characterSelectionMenu->header = Node_FindWidgetByResourceId((void *) screen, 172);
  g_characterSelectionMenu->header->x -= g_characterSelectionMenu->header->w;
  g_characterSelectionMenu->headerStep = g_characterSelectionMenu->header->w / 4;
  rest = g_characterSelectionMenu->header->w - (g_characterSelectionMenu->headerStep * 4);
  g_characterSelectionMenu->header->x += rest;
  g_characterSelectionMenu->footer = Node_FindWidgetByResourceId((void *) screen, 147);
  g_characterSelectionMenu->footer->x += g_characterSelectionMenu->footer->w;
  g_characterSelectionMenu->footerStep = g_characterSelectionMenu->footer->w / 4;
  rest = g_characterSelectionMenu->footer->w - (g_characterSelectionMenu->footerStep * 4);
  g_characterSelectionMenu->footer->x -= rest;
  Node_FindWidgetByResourceId((void *) screen, 118)->alpha = 110;
  Node_FindWidgetByResourceId((void *) screen, 121)->alpha = 25;
  g_characterSelectionMenu->prompt = SmpFlicker_CreateFlickerWidget(116, 0xFF);
  item = Node_FindWidgetByResourceId((void *) screen, 116);
  g_characterSelectionMenu->promptItem = item;
  Widget_SetWidgetFlag08(item, 0);
  g_characterSelectionMenu->pulse = Node_FindWidgetByResourceId((void *) screen, 123);
  Widget_SetWidgetFlag08(g_characterSelectionMenu->pulse, 0);
  g_characterSelectionMenu->pulse->alpha = 0;
  g_characterSelectionMenu->pulseStep = 50;
  Menu_RefreshCharacterUnlocks();
  config = g_playerSettings;
  for (i = 0; i < 4; i++)
  {
    if (config[i].active == 1)
    {
      Menu_ShowPlayerCharacterSelection(i);
    }
  }

  Tsmos_DeactivateControllerState();
  g_characterSelectionMenu->result = -1;
  return 0;
}
#endif

#if defined(VERSION_US)
extern float g_characterPreviewInitialScale;
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"
#include "COMMON/ANIMATION.H"

s32 Character_CreateSelectionMenuUs(void *screen)
{
  CVector3 scale;
  s32 j;
  s32 i;
  s32 model;
  s32 row;
  SlotSelectionPlayerConfig *config;
  SlotSelectionWidget *item;
  s32 rest;
  g_characterSelectionMenu = Cache_AllocateMemory(4952);
  g_characterSelectionMenu->screen = screen;
  g_characterSelectionMenu->slotOverlay = SmpOverlay_CreateOverlayNode((s32) screen, 4);
  SmpOverlay_ShowSlotById((s32) screen, 0, 122);
  SmpOverlay_ShowSlotById((s32) screen, 1, 122);
  SmpOverlay_ShowSlotById((s32) screen, 2, 122);
  SmpOverlay_ShowSlotById((s32) screen, 3, 122);
  Random_SetSelectedStage(0, 0);
  g_characterSelectionMenu->clock = 0;
  scale.x = g_characterPreviewInitialScale;
  scale.y = g_characterPreviewInitialScale;
  scale.z = g_characterPreviewInitialScale;
  for (i = 0; i < 4; i++)
  {
    g_characterSelectionMenu->players[i].slotOverlay = 0;
    g_characterSelectionMenu->players[i].kind = g_characterSelectionMenuEntries[i].kind;
    g_characterSelectionMenu->players[i].highlight = 0;
    g_characterSelectionMenu->players[i].selectionState = 0;
    g_characterSelectionMenu->players[i].choice = 0;
    g_characterSelectionMenu->players[i].tintFramesLeft = 0;
    model = Key_GetCharacterPreviewModel(g_characterSelectionMenu->players[i].kind);
    row = Key_FindCharacterPreviewRow(g_characterSelectionMenu->players[i].kind);
    scale.x = g_characterPortraitRecords[row].scale[i];
    scale.y = g_characterPortraitRecords[row].scale[i];
    scale.z = g_characterPortraitRecords[row].scale[i];
    Preview_InitModelPreview(g_characterSelectionMenu->players[i].model, 9, model + 911, 75, 24000, scale, g_characterPortraitRecords[row].position[i], g_characterPortraitRecords[row].distance[i], g_characterPortraitRecords[row].light[i]);
    Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].title)->alpha = 110;
    for (j = 0; j < 3; j++)
    {
      Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].cells[j].id)->alpha = 80;
      Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].options[j].id), 1);
    }

  }

  g_characterSelectionMenu->phase = 1;
  g_characterSelectionMenu->timer = 4;
  g_characterSelectionMenu->header = Node_FindWidgetByResourceId(screen, 172);
  g_characterSelectionMenu->header->x -= g_characterSelectionMenu->header->w;
  g_characterSelectionMenu->headerStep = g_characterSelectionMenu->header->w / 4;
  rest = g_characterSelectionMenu->header->w - (g_characterSelectionMenu->headerStep * 4);
  g_characterSelectionMenu->header->x += rest;
  g_characterSelectionMenu->footer = Node_FindWidgetByResourceId(screen, 147);
  g_characterSelectionMenu->footer->x += g_characterSelectionMenu->footer->w;
  g_characterSelectionMenu->footerStep = g_characterSelectionMenu->footer->w / 4;
  rest = g_characterSelectionMenu->footer->w - (g_characterSelectionMenu->footerStep * 4);
  g_characterSelectionMenu->footer->x -= rest;
  Node_FindWidgetByResourceId(screen, 118)->alpha = 110;
  Node_FindWidgetByResourceId(screen, 121)->alpha = 25;
  g_characterSelectionMenu->prompt = SmpFlicker_CreateFlickerWidget(116, 0xFF);
  item = Node_FindWidgetByResourceId(screen, 116);
  g_characterSelectionMenu->promptItem = item;
  Widget_SetWidgetFlag08(item, 0);
  g_characterSelectionMenu->pulse = Node_FindWidgetByResourceId(screen, 123);
  Widget_SetWidgetFlag08(g_characterSelectionMenu->pulse, 0);
  g_characterSelectionMenu->pulse->alpha = 0;
  g_characterSelectionMenu->pulseStep = 50;
  Menu_RefreshCharacterUnlocks();
  config = g_playerSettings;
  for (i = 0; i < 4; i++)
  {
    if (config[i].active == 1)
    {
      Menu_ShowPlayerCharacterSelection(i);
    }
  }

  Tsmos_DeactivateControllerState();
  g_characterSelectionMenu->result = -1;
  return 0;
}
#endif

#if defined(VERSION_EU)
extern float g_characterPreviewInitialScale;
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"
#include "COMMON/ANIMATION.H"

s32 Character_CreateSelectionMenuEuropean(void *screen)
{
  CVector3 scale;
  s32 j;
  s32 i;
  s32 model;
  s32 row;
  SlotSelectionPlayerConfig *config;
  SlotSelectionWidget *item;
  s32 rest;
  g_characterSelectionMenu = Cache_AllocateMemory(4952);
  g_characterSelectionMenu->screen = screen;
  g_characterSelectionMenu->slotOverlay = SmpOverlay_CreateOverlayNode((s32) screen, 4);
  SmpOverlay_ShowSlotById((s32) screen, 0, 122);
  SmpOverlay_ShowSlotById((s32) screen, 1, 122);
  SmpOverlay_ShowSlotById((s32) screen, 2, 122);
  SmpOverlay_ShowSlotById((s32) screen, 3, 122);
  Random_SetSelectedStage(0, 0);
  g_characterSelectionMenu->clock = 0;
  scale.x = g_characterPreviewInitialScale;
  scale.y = g_characterPreviewInitialScale;
  scale.z = g_characterPreviewInitialScale;
  for (i = 0; i < 4; i++)
  {
    g_characterSelectionMenu->players[i].slotOverlay = 0;
    g_characterSelectionMenu->players[i].kind = g_characterSelectionMenuEntries[i].kind;
    g_characterSelectionMenu->players[i].highlight = 0;
    g_characterSelectionMenu->players[i].selectionState = 0;
    g_characterSelectionMenu->players[i].choice = 0;
    g_characterSelectionMenu->players[i].tintFramesLeft = 0;
    model = Key_GetCharacterPreviewModel(g_characterSelectionMenu->players[i].kind);
    row = Key_FindCharacterPreviewRow(g_characterSelectionMenu->players[i].kind);
    scale.x = g_characterPortraitRecords[row].scale[i];
    scale.y = g_characterPortraitRecords[row].scale[i];
    scale.z = g_characterPortraitRecords[row].scale[i];
    Preview_InitModelPreview(g_characterSelectionMenu->players[i].model, 9, model + 911, 75, 24000, scale, g_characterPortraitRecords[row].position[i], g_characterPortraitRecords[row].distance[i], g_characterPortraitRecords[row].light[i]);
    Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].title)->alpha = 110;
    for (j = 0; j < 3; j++)
    {
      Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].cells[j].id)->alpha = 80;
      Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].options[j].id), 1);
    }

  }

  g_characterSelectionMenu->phase = 1;
  g_characterSelectionMenu->timer = 4;
  g_characterSelectionMenu->header = Node_FindWidgetByResourceId(screen, 172);
  g_characterSelectionMenu->header->x -= g_characterSelectionMenu->header->w;
  g_characterSelectionMenu->headerStep = g_characterSelectionMenu->header->w / 4;
  rest = g_characterSelectionMenu->header->w - (g_characterSelectionMenu->headerStep * 4);
  g_characterSelectionMenu->header->x += rest;
  g_characterSelectionMenu->footer = Node_FindWidgetByResourceId(screen, 147);
  g_characterSelectionMenu->footer->x += g_characterSelectionMenu->footer->w;
  g_characterSelectionMenu->footerStep = g_characterSelectionMenu->footer->w / 4;
  rest = g_characterSelectionMenu->footer->w - (g_characterSelectionMenu->footerStep * 4);
  g_characterSelectionMenu->footer->x -= rest;
  Node_FindWidgetByResourceId(screen, 118)->alpha = 110;
  Node_FindWidgetByResourceId(screen, 121)->alpha = 25;
  g_characterSelectionMenu->prompt = SmpFlicker_CreateFlickerWidget(116, 0xFF);
  item = Node_FindWidgetByResourceId(screen, 116);
  g_characterSelectionMenu->promptItem = item;
  Widget_SetWidgetFlag08(item, 0);
  g_characterSelectionMenu->pulse = Node_FindWidgetByResourceId(screen, 123);
  Widget_SetWidgetFlag08(g_characterSelectionMenu->pulse, 0);
  g_characterSelectionMenu->pulse->alpha = 0;
  g_characterSelectionMenu->pulseStep = 50;
  Menu_RefreshCharacterUnlocks();
  config = g_playerSettings;
  for (i = 0; i < 4; i++)
  {
    if (config[i].active == 1)
    {
      Menu_ShowPlayerCharacterSelection(i);
    }
  }

  Tsmos_DeactivateControllerState();
  g_characterSelectionMenu->result = -1;
  return 0;
}
#endif

#if defined(VERSION_EU_X)
extern float g_characterPreviewInitialScale;
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"
#include "COMMON/ANIMATION.H"

s32 Character_CreateSelectionMenuEuropeanX(void *screen)
{
  CVector3 scale;
  s32 j;
  s32 i;
  s32 model;
  s32 row;
  SlotSelectionPlayerConfig *config;
  SlotSelectionWidget *item;
  s32 rest;
  g_characterSelectionMenu = Cache_AllocateMemory(4952);
  g_characterSelectionMenu->screen = screen;
  g_characterSelectionMenu->slotOverlay = SmpOverlay_CreateOverlayNode((s32) screen, 4);
  SmpOverlay_ShowSlotById((s32) screen, 0, 126);
  SmpOverlay_ShowSlotById((s32) screen, 1, 126);
  SmpOverlay_ShowSlotById((s32) screen, 2, 126);
  SmpOverlay_ShowSlotById((s32) screen, 3, 126);
  Random_SetSelectedStage(0, 0);
  g_characterSelectionMenu->clock = 0;
  scale.x = g_characterPreviewInitialScale;
  scale.y = g_characterPreviewInitialScale;
  scale.z = g_characterPreviewInitialScale;
  for (i = 0; i < 4; i++)
  {
    g_characterSelectionMenu->players[i].slotOverlay = 0;
    g_characterSelectionMenu->players[i].kind = g_characterSelectionMenuEntries[i].kind;
    g_characterSelectionMenu->players[i].highlight = 0;
    g_characterSelectionMenu->players[i].selectionState = 0;
    g_characterSelectionMenu->players[i].choice = 0;
    g_characterSelectionMenu->players[i].tintFramesLeft = 0;
    model = Key_GetCharacterPreviewModel(g_characterSelectionMenu->players[i].kind);
    row = Key_FindCharacterPreviewRow(g_characterSelectionMenu->players[i].kind);
    scale.x = g_characterPortraitRecords[row].scale[i];
    scale.y = g_characterPortraitRecords[row].scale[i];
    scale.z = g_characterPortraitRecords[row].scale[i];
    Preview_InitModelPreview(g_characterSelectionMenu->players[i].model, 9, model + 911, 75, 24000, scale, g_characterPortraitRecords[row].position[i], g_characterPortraitRecords[row].distance[i], g_characterPortraitRecords[row].light[i]);
    Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].title)->alpha = 110;
    for (j = 0; j < 3; j++)
    {
      Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].cells[j].id)->alpha = 80;
      Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].options[j].id), 1);
    }

  }

  g_characterSelectionMenu->phase = 1;
  g_characterSelectionMenu->timer = 4;
  g_characterSelectionMenu->header = Node_FindWidgetByResourceId(screen, 176);
  g_characterSelectionMenu->header->x -= g_characterSelectionMenu->header->w;
  g_characterSelectionMenu->headerStep = g_characterSelectionMenu->header->w / 4;
  rest = g_characterSelectionMenu->header->w - (g_characterSelectionMenu->headerStep * 4);
  g_characterSelectionMenu->header->x += rest;
  g_characterSelectionMenu->footer = Node_FindWidgetByResourceId(screen, 151);
  g_characterSelectionMenu->footer->x += g_characterSelectionMenu->footer->w;
  g_characterSelectionMenu->footerStep = g_characterSelectionMenu->footer->w / 4;
  rest = g_characterSelectionMenu->footer->w - (g_characterSelectionMenu->footerStep * 4);
  g_characterSelectionMenu->footer->x -= rest;
  Node_FindWidgetByResourceId(screen, 122)->alpha = 110;
  Node_FindWidgetByResourceId(screen, 125)->alpha = 25;
  g_characterSelectionMenu->prompt = SmpFlicker_CreateFlickerWidget(120, 0xFF);
  item = Node_FindWidgetByResourceId(screen, 120);
  g_characterSelectionMenu->promptItem = item;
  Widget_SetWidgetFlag08(item, 0);
  g_characterSelectionMenu->pulse = Node_FindWidgetByResourceId(screen, 0x7f);
  Widget_SetWidgetFlag08(g_characterSelectionMenu->pulse, 0);
  g_characterSelectionMenu->pulse->alpha = 0;
  g_characterSelectionMenu->pulseStep = 50;
  Menu_RefreshCharacterUnlocks();
  config = g_playerSettings;
  for (i = 0; i < 4; i++)
  {
    if (config[i].active == 1)
    {
      Menu_ShowPlayerCharacterSelection(i);
    }
  }

  Tsmos_DeactivateControllerState();
  g_characterSelectionMenu->result = -1;
  return 0;
}
#endif

#if defined(VERSION_DE)
extern float g_characterPreviewInitialScale;
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"
#include "COMMON/ANIMATION.H"

s32 Character_CreateSelectionMenuGerman(void *screen)
{
  CVector3 scale;
  s32 j;
  s32 i;
  s32 model;
  s32 row;
  SlotSelectionPlayerConfig *config;
  SlotSelectionWidget *item;
  s32 rest;
  g_characterSelectionMenu = Cache_AllocateMemory(4952);
  g_characterSelectionMenu->screen = screen;
  g_characterSelectionMenu->slotOverlay = SmpOverlay_CreateOverlayNode((s32) screen, 4);
  SmpOverlay_ShowSlotById((s32) screen, 0, 120);
  SmpOverlay_ShowSlotById((s32) screen, 1, 120);
  SmpOverlay_ShowSlotById((s32) screen, 2, 120);
  SmpOverlay_ShowSlotById((s32) screen, 3, 120);
  Random_SetSelectedStage(0, 0);
  g_characterSelectionMenu->clock = 0;
  scale.x = g_characterPreviewInitialScale;
  scale.y = g_characterPreviewInitialScale;
  scale.z = g_characterPreviewInitialScale;
  for (i = 0; i < 4; i++)
  {
    g_characterSelectionMenu->players[i].slotOverlay = 0;
    g_characterSelectionMenu->players[i].kind = g_characterSelectionMenuEntries[i].kind;
    g_characterSelectionMenu->players[i].highlight = 0;
    g_characterSelectionMenu->players[i].selectionState = 0;
    g_characterSelectionMenu->players[i].choice = 0;
    g_characterSelectionMenu->players[i].tintFramesLeft = 0;
    model = Key_GetCharacterPreviewModel(g_characterSelectionMenu->players[i].kind);
    row = Key_FindCharacterPreviewRow(g_characterSelectionMenu->players[i].kind);
    scale.x = g_characterPortraitRecords[row].scale[i];
    scale.y = g_characterPortraitRecords[row].scale[i];
    scale.z = g_characterPortraitRecords[row].scale[i];
    Preview_InitModelPreview(g_characterSelectionMenu->players[i].model, 9, model + 911, 75, 24000, scale, g_characterPortraitRecords[row].position[i], g_characterPortraitRecords[row].distance[i], g_characterPortraitRecords[row].light[i]);
    Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].title)->alpha = 110;
    for (j = 0; j < 3; j++)
    {
      Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].cells[j].id)->alpha = 80;
      Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[i].options[j].id), 1);
    }

  }

  g_characterSelectionMenu->phase = 1;
  g_characterSelectionMenu->timer = 4;
  g_characterSelectionMenu->header = Node_FindWidgetByResourceId(screen, 170);
  g_characterSelectionMenu->header->x -= g_characterSelectionMenu->header->w;
  g_characterSelectionMenu->headerStep = g_characterSelectionMenu->header->w / 4;
  rest = g_characterSelectionMenu->header->w - (g_characterSelectionMenu->headerStep * 4);
  g_characterSelectionMenu->header->x += rest;
  g_characterSelectionMenu->footer = Node_FindWidgetByResourceId(screen, 145);
  g_characterSelectionMenu->footer->x += g_characterSelectionMenu->footer->w;
  g_characterSelectionMenu->footerStep = g_characterSelectionMenu->footer->w / 4;
  rest = g_characterSelectionMenu->footer->w - (g_characterSelectionMenu->footerStep * 4);
  g_characterSelectionMenu->footer->x -= rest;
  Node_FindWidgetByResourceId(screen, 116)->alpha = 110;
  Node_FindWidgetByResourceId(screen, 119)->alpha = 25;
  g_characterSelectionMenu->prompt = SmpFlicker_CreateFlickerWidget(114, 0xFF);
  item = Node_FindWidgetByResourceId(screen, 114);
  g_characterSelectionMenu->promptItem = item;
  Widget_SetWidgetFlag08(item, 0);
  g_characterSelectionMenu->pulse = Node_FindWidgetByResourceId(screen, 121);
  Widget_SetWidgetFlag08(g_characterSelectionMenu->pulse, 0);
  g_characterSelectionMenu->pulse->alpha = 0;
  g_characterSelectionMenu->pulseStep = 50;
  Menu_RefreshCharacterUnlocks();
  config = g_playerSettings;
  for (i = 0; i < 4; i++)
  {
    if (config[i].active == 1)
    {
      Menu_ShowPlayerCharacterSelection(i);
    }
  }

  Tsmos_DeactivateControllerState();
  g_characterSelectionMenu->result = -1;
  return 0;
}
#endif

/* Advances the selection panels, cursor highlight and character previews. */
s32 Character_UpdateCharacterPreview(s32 unusedFirst,s32 unusedSecond,s32 elapsedTicks) {
    CVector3 scale;
    f32 highlightAlpha;
    s16 resource;
    s32 previewModelOffset;
    s32 phase;
    s32 enterTicksRemaining;
    s32 exitTicksRemaining;
    s32 fadeTicksRemaining;
    s32 entryIndex;
    s32 i;
    s32 empty_slot;
    MenuWidget *highlight;
    MenuWidget *highlightWidget;
    MenuWidget *headerWidget;
    MenuWidget *footerWidget;
    MenuWidget *pulse;
    MenuWidget *header;
    MenuWidget *footer;
    struct WidgetNode *widgetNode;

    phase = g_characterSelectionMenu->phase;
    switch (phase) {
    case 1:
        header = g_characterSelectionMenu->header;
        header->x = (u16) (header->x + (u16)g_characterSelectionMenu->headerStep);
        footer = g_characterSelectionMenu->footer;
        footer->x = (u16) (footer->x - (u16)g_characterSelectionMenu->footerStep);
        enterTicksRemaining = g_characterSelectionMenu->timer - 1;
        g_characterSelectionMenu->timer = enterTicksRemaining;
        if (enterTicksRemaining <= 0) {
            SoundElement_PlayFlatSound(3705);
            Widget_SetWidgetFlag08(g_characterSelectionMenu->promptItem, 1);
            SmpFlicker_StartFlicker(g_characterSelectionMenu->prompt, 4);
            g_characterSelectionMenu->phase = 4;
            g_characterSelectionMenu->timer = 4;
        }
        break;
    case 2:
        headerWidget = g_characterSelectionMenu->header;
        headerWidget->x = (u16) (headerWidget->x - (u16)g_characterSelectionMenu->headerStep);
        footerWidget = g_characterSelectionMenu->footer;
        footerWidget->x = (u16) (footerWidget->x + (u16)g_characterSelectionMenu->footerStep);
        exitTicksRemaining = g_characterSelectionMenu->timer - 1;
        g_characterSelectionMenu->timer = exitTicksRemaining;
        if (exitTicksRemaining <= 0) {
            g_characterSelectionMenu->phase = 3;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(g_characterSelectionMenu->result);
            return 0;
        }
        break;
    case 3:
        Tsmos_ActivateControllerState();
        break;
    case 4:
        g_characterSelectionMenu->timer = g_characterSelectionMenu->timer - 1 < 0 ? 0 :
            g_characterSelectionMenu->timer - 1 > g_characterSelectionMenu->timer ? g_characterSelectionMenu->timer : g_characterSelectionMenu->timer - 1;
        if ((g_characterSelectionMenu->timer <= 0) && (SmpFlicker_IsFlickerIdle(g_characterSelectionMenu->prompt) != 0)) {
            SmpFlicker_RestoreFlickerValue(g_characterSelectionMenu->prompt);
            g_characterSelectionMenu->phase = 6;
            g_characterSelectionMenu->timer = 4;
            Widget_SetWidgetFlag08(g_characterSelectionMenu->pulse, 1);
        }
        break;
    case 5:
        SoundElement_PlayFlatSound(3704);
        g_characterSelectionMenu->phase = 2;
        g_characterSelectionMenu->timer = 4;
        Widget_SetWidgetFlag08(g_characterSelectionMenu->promptItem, 0);
        Widget_SetWidgetFlag08(g_characterSelectionMenu->pulse, 0);
        break;
    case 7: break;
    case 6:
        pulse = g_characterSelectionMenu->pulse;
        pulse->alpha = (u8) (pulse->alpha + (u8)g_characterSelectionMenu->pulseStep);
        fadeTicksRemaining = g_characterSelectionMenu->timer - 1;
        g_characterSelectionMenu->timer = fadeTicksRemaining;
        if (fadeTicksRemaining <= 0) {
            g_characterSelectionMenu->pulse->alpha = 200;
            g_characterSelectionMenu->phase = 3;
        }
        break;
    }
        if (g_characterSelectionMenu->phase == 3) {
            i = 0;
            empty_slot = CHARACTER_EMPTY_SLOT;
            g_characterSelectionMenu->clock = (s32) (g_characterSelectionMenu->clock + elapsedTicks);
            do {
                if (g_characterSelectionMenu->players[i].selectionState == 1) {
                    if (g_characterSelectionMenu->players[i].highlight != 0) {
                        highlightAlpha = (Math_Cosf((f32) i + ((f32) g_characterSelectionMenu->clock * 0.0033333334f)) * 70.0f) + 170.0f;
                        highlight = g_characterSelectionMenu->players[i].highlight;
                        highlight->alpha=(unsigned int)highlightAlpha;
                    }
                    widgetNode = SmpOverlay_GetSlotValue(g_characterSelectionMenu->slotOverlay, i);
                    highlightWidget = g_characterSelectionMenu->players[i].highlight;
                    if ((highlightWidget->x != (widgetNode->x - 2)) || (highlightWidget->y != (widgetNode->y - 2))) {
                        SoundElement_PlayFlatSound(3711);
                        if (Widget_ListHasFlag100(widgetNode) == 0) {
                            resource = widgetNode->resource;
                            if (resource != empty_slot) {
                                g_characterSelectionMenu->players[i].kind = (s32) resource;
                                previewModelOffset = Key_GetCharacterPreviewModel(resource);
                                entryIndex = Key_FindCharacterPreviewRow(g_characterSelectionMenu->players[i].kind);
                                scale.x = g_characterPortraitRecords[entryIndex].scale[i];
                                scale.y = g_characterPortraitRecords[entryIndex].scale[i];
                                scale.z = g_characterPortraitRecords[entryIndex].scale[i];
                                Preview_InitModelPreview(g_characterSelectionMenu->players[i].model, 9, previewModelOffset + 911, 75, 24000, scale, g_characterPortraitRecords[entryIndex].position[i], g_characterPortraitRecords[entryIndex].distance[i], g_characterPortraitRecords[entryIndex].light[i]);
                            } else {
                                Menu_RandomizeCharacterPreview(i);
                            }
                        } else {
                            g_characterSelectionMenu->players[i].kind = -1;
                        }
                        Menu_RefreshPlayerCharacterVariants(i);
                    } else if (widgetNode->resource == empty_slot) {
                        Menu_RandomizeCharacterPreview(i);
                    }
                    g_characterSelectionMenu->players[i].highlight->x = (s16) ((u16) widgetNode->x - 2);
                    g_characterSelectionMenu->players[i].highlight->y = (s16) ((u16) widgetNode->y - 2);
                }
                i += 1;
            } while (i < 4);
        }
        return 0;
}
