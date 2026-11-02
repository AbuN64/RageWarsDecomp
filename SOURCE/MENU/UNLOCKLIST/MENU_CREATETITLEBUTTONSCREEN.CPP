#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/MENUSELECTIONMESSAGE.H"

/* 804366D0_11.CPP */
extern struct MenuMenuCreateTitleButtonScreen *g_titleButtonScreen;

/* Builds a three-item menu: allocates 0x14 bytes into g_titleButtonScreen through Cache_AllocateMemory, creates the
   title 0x3CC/0x3CD through SmpFade_CreateFadeWidget and the button 0x3CF through SmpFlicker_CreateFlickerWidget with 0x6E,
   finds entry 0x3CE of the list through Node_FindWidgetByResourceId and sets its byte at 0x10 to 0xF, and stores
   the three with 3 and -1 in the block. Returns zero. */

extern struct Record *Cache_AllocateMemory(s32 size);

extern void *SmpFade_CreateFadeWidget(s32, s32);

extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);

extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);

/* Releases the object g_titleButtonScreen holds through Cache_FreeMemory, clears g_titleButtonScreen and returns zero. */

s32 Menu_CreateTitleButtonScreen(void *list) {
    struct ResourceSmpFlickerCreateFlickerWidget *item;
    g_titleButtonScreen = Cache_AllocateMemory(20);
#if defined(VERSION_DE)
    g_titleButtonScreen->title = SmpFade_CreateFadeWidget(966, 966 + 1);
    g_titleButtonScreen->button = SmpFlicker_CreateFlickerWidget(966 + 3, 110);
    item = Node_FindWidgetByResourceId(list, 966 + 2);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    g_titleButtonScreen->title = SmpFade_CreateFadeWidget(972, 972 + 1);
    g_titleButtonScreen->button = SmpFlicker_CreateFlickerWidget(972 + 3, 110);
    item = Node_FindWidgetByResourceId(list, 972 + 2);
#elif defined(VERSION_EU_X)
    g_titleButtonScreen->title = SmpFade_CreateFadeWidget(976, 976 + 1);
    g_titleButtonScreen->button = SmpFlicker_CreateFlickerWidget(976 + 3, 110);
    item = Node_FindWidgetByResourceId(list, 976 + 2);
#endif
    g_titleButtonScreen->item = item;
    item->value = 15;
    g_titleButtonScreen->count = 3;
    g_titleButtonScreen->selection = -1;
    return 0;
}

s32 Menu_FreeTitleButtonScreen(void) {
    Cache_FreeMemory(g_titleButtonScreen);
    g_titleButtonScreen = 0;
    return 0;
}

/* 804379C8.CPP */
#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* Calls SmpButton_WrapButtonWidget with 0x3D0 and then 0x3D1, and returns zero. */
extern void SmpButton_WrapButtonWidget(s32);

s32 Menu_WrapTitleButtonScreenNodes(void) {
    SmpButton_WrapButtonWidget(976);
    SmpButton_WrapButtonWidget(977);
    return 0;
}
#endif
