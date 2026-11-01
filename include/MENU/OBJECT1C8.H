#ifndef MENU_OBJECT1C8_H
#define MENU_OBJECT1C8_H
#include "TYPES.H"
#include "COMMON/LONE/MENU_TINT_ALPHA.H"
#include "COMMON/ITEMRECAT20V1.H"
struct Object1C8;
struct Object1C8 {
    char pad[0x1C8];
    s32 first;
    s32 second;
};

struct WidgetDescriptor;
struct WidgetDescriptor {
    short type;
    short pad;
    int flags;
    unsigned short x;
    unsigned short y;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    int value;
};

struct MenuItemVisibilityFlagView;
struct MenuItemVisibilityFlagView {
    char pad[0x478];
    s32 flag;
};

struct MenuItemVisibilityFlagView;

struct MenuItemFlagsView;
struct MenuItemFlagsView {
    char pad[8];
    u32 flags;
};

struct WidgetDescriptor;
struct CMenuItem_t;
struct CMenuItem_t {
    int id;
    unsigned short type;
    unsigned short pad;
    int flags;
    unsigned short x;
    unsigned short y;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    int value;
    struct WidgetDescriptor *desc;
    int index;
    void *extra;
    int m_pMenu;
};

struct WidgetDescriptor;
typedef struct WidgetDescriptor WidgetDescriptor;

struct CMenuItem_t;
typedef struct CMenuItem_t CMenuItem;


struct MenuItemInputStateView;
struct MenuItemInputStateView {
    char pad0[0xB0];
    s32 a;
    s32 b;
    s32 padB8;
    s32 c;
};

struct HandlersItemsInvokeHandlerAndClearItemState;
struct HandlersItemsInvokeHandlerAndClearItemState {
    char pad[0xC];
    void (*callback)();
};
struct HandlersItemsInvokeHandlerAndClearItemState;
struct MenuItemCallbackAndStateView;
struct MenuItemInputStateView;
struct MenuItemCallbackAndStateView {
    char pad[0x14];
    struct HandlersItemsInvokeHandlerAndClearItemState *handlers;
    char pad18[0x20 - 0x18];
    struct MenuItemInputStateView *state;
};

struct MenuItemCallbackAndStateView;

struct MenuItemCountView;
struct MenuItemCountView {
    char pad[0x1C8];
    s32 count;
};

struct MenuSpriteElement;
typedef struct MenuSpriteElement MenuSpriteElement;

struct Object1C8;

struct MenuSpriteElement;
struct Shared_HudView;
struct MenuSpriteElement {
    char pad0[0x40];
    struct Shared_HudView *owner;
    char pad44[0x184];
    s32 frame;
    s32 active;
};



struct Handlers;
struct Handlers {
    char pad[0xC];
    void (*callback)(void *, void *);
};
struct Handlers;
struct MenuResourceItemView;
struct MenuItemInputStateView;
struct MenuResourceItemView {
    char pad0[8];
    s32 resource;
    char padC[0x14 - 0xC];
    struct Handlers *handlers;
    char pad18[0x20 - 0x18];
    struct MenuItemInputStateView *state;
};

struct MenuItemCountView;

struct MenuItemControllerView;
struct MenuItemControllerView {
    char pad[0x698];
    s32 value;
};

struct MenuItemOwnerLinkView;
struct MenuItemControllerView;
struct MenuItemOwnerLinkView {
    char pad[0x1C];
    struct MenuItemControllerView *owner;
};

struct MenuItemOwnerLinkView;


struct MenuItemFlagsView;
typedef struct MenuItemFlagsView MenuItemFlagsView;


struct MenuResourceItemView;
struct ListPakClearMenuItemList;
struct ListPakClearMenuItemList {
    struct MenuResourceItemView *head;
};

struct MenuItemTargetView;
struct MenuItemTargetView {
    s32 pad0;
    s16 kind;
    char pad6[0x14 - 6];
    void **target;
};


#endif
