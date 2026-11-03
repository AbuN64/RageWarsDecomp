#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/ANIMATION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "UI/QUAG/N64_ENG.H"
#include "FRONTEND/WIDGET_FINDWIDGETATPOINT.H"
#include "RESMGR/resmgr_string_memory.H"
#include "MENU.H"
#include "COMMON/SCREEN.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/LABEL.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/STATEPAIR.H"
#include "COMMON/MENURECAT24.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "COMMON/RECORDRECATCV1.H"
#include "FRONTEND/SMP_OVERLAY.H"
#include "FRONTEND/PAKINTERFACE_SETSCREENPHASE.H"
#include "COMMON/GAME_SESSION.H"
#include "FRONTEND/SCREEN.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"

/* SMP_OVERLAY.CPP */
/* SMP_OVERLAY.CPP */
/* 804196C0_24.CPP */
/* Allocates and zeroes a 0x70-byte overlay node, copies the 0x2C-byte header of the owner's tree root into it, tags it 0x7A51 with kind 0x7D5 and flags 8, links it to its owner and the given value, inserts it under the root through Node_InsertWidgetBefore and records it as the owner's overlay. */

extern void Node_InsertWidgetBefore(struct Tree *node, struct Tree *added);

/* Unless slot index is locked, hides the node shown in that slot, finds node id under the context root through Node_FindWidgetByResourceId, shows it, and stores it in that slot or, in shared mode, in all four slots; then clears the slot's lock. */

/* Unless slot index is locked, hides the node in that slot and shows the given node through Widget_SetWidgetFlag40_EquipActivateequipmentpanel, storing it in that slot or, in shared mode, in all four slots. */

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_overlaySlotEventIds, an actor kind at g_overlaySlotEventActorKinds and a handler at g_overlaySlotEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

/* Draws the child at 0x8 of window window with the arguments passed by value once Widget_ComputeWidgetBounds resolves the window's rectangle, and when flag 0x200 of the halfword at 0x12 is set it saves the four values N64Eng_GetClipBounds reports, narrows them by the resolved basis through Node_ClampRectToClip_FrontendOpenresourcearchive and installs them through N64Eng_SetClipBounds around the draw, restoring the saved values after it. Adapted from N64Eng_DrawNumericWidgetChildren. */

extern s32 Widget_ComputeWidgetBounds(struct CacheResourceBlockView *draw, struct CacheResourceBlockView *hit, struct WidgetLayout *widget, struct t_dldc *ctx);





extern void Widget_DrawVisibleSiblings(void *, Args);

void SmpOverlay_RegisterOverlayClass(void) {
    SmSmngr_RegisterElementHandlers(2005, g_SmpOverlay_DispatchSlotEventAddress, g_SmpOverlay_DrawOverlayWidgetAddress, 3);
}

NodeMenuCreateOverlayNode *SmpOverlay_CreateOverlayNode(MenuOverlayOwnerView *owner, s32 value) {
    NodeMenuCreateOverlayNode *node;

    node = (NodeMenuCreateOverlayNode *)Cache_AllocateMemory(112);
    XPlus_FillBytes(node, 0, 112);
    *(Header44 *)node = *(Header44 *)owner->root;
    node->kind = 2005;
    node->flags = 8;
    node->value = value;
    node->owner = owner;
    node->tag = 31313;
    node->reservedWord = 0;
    Node_InsertWidgetBefore(owner->root, node);
    return owner->overlay = node;
}

void SmpOverlay_ShowSlotById(MenuMultiUserOwnerView *owner, s32 index, s32 id) {
    sm_dlmultiuser *context;
    NodeMenuShowSlotById *node;
    s32 i;

    context = owner->context;
    if (context->locked[index] == 0) {
        if (context->shown[index] != 0) {
            Menu_RouteElementEvent(context->shown[index]->id, 16, 0, 0, 0);
        }
        node = (NodeMenuShowSlotById *)Node_FindWidgetByResourceId(context->root, id & 0xFFFF);
        Menu_RouteElementEvent(node->id, 15, 0, 0, 0);
        if (context->shared == 0) {
            context->shown[index] = node;
        } else {
            for (i = 3; i >= 0; i--) {
                context->shown[i] = node;
            }
        }
    }
    context->locked[index] = 0;
}

/* Stores a value into entry i of the word array at offset 0x5C of an object; SmpOverlay_GetSlotValue_PakinterfaceRelabelslotrows reads
   the parallel array at offset 0x4C. */

void SmpOverlay_SetSlotValue(struct MenuSlotValueArrayView *object, s32 index, s32 value) {
    object->values[index] = value;
}

/* Counts the non-zero words among the first n of the array at offset 0x5C of an object, n being
   its count at 0x48. */

s32 SmpOverlay_CountUsedSlots(struct MenuCountedSlotValueArrayView *object) {
    s32 used = 0;
    s32 i;

    for (i = 0; i < object->count; i++) {
        if (object->values[i] != 0) {
            used++;
        }
    }
    return used;
}

/* Returns entry i of the word array at offset 0x4C of an object; SmpOverlay_SetSlotValue_SmpOverlay writes the
   parallel array at offset 0x5C. */

struct WidgetNode *SmpOverlay_GetSlotValue(struct SmpOverlaySlotsView *object, s32 index) {
    return object->values[index];
}

/* Returns the halfword at offset 0xC of the object held in entry i of the pointer array at
   offset 0x4C of an object. */

s16 SmpOverlay_GetSlotNodeId(struct MenuObjectSlotArrayView *object, s32 index) {
    return object->entries[index]->input;
}

void SmpOverlay_ShowSlotNodeById(sm_dlmultiuser *context, s32 index, s32 id) {
    NodeMenuShowSlotById *node;
    s32 i;

    if (context->locked[index] == 0) {
        if (context->shown[index] != 0) {
            Menu_RouteElementEvent(context->shown[index]->id, 16, 0, 0, 0);
        }
        node = (NodeMenuShowSlotById *)Node_FindWidgetByResourceId(context->root, id & 0xFFFF);
        Menu_RouteElementEvent(node->id, 15, 0, 0, 0);
        if (context->shared == 0) {
            context->shown[index] = node;
        } else {
            for (i = 3; i >= 0; i--) {
                context->shown[i] = node;
            }
        }
    }
}

void SmpOverlay_ShowSlotNode(sm_dlmultiuser *context, s32 index, NodeMenuShowSlotById *node) {
    s32 i;

    if (context->locked[index] == 0) {
        if (context->shown[index] != 0) {
            Widget_SetWidgetFlag40(context->shown[index], 0);
        }
        Widget_SetWidgetFlag40(node, 1);
        if (context->shared == 0) {
            context->shown[index] = node;
        } else {
            for (i = 3; i >= 0; i--) {
                context->shown[i] = node;
            }
        }
    }
}

/* Stores a value into the word at offset 0x6C of an object; Preview_SelectPreviewModel_SmpOverlay uses it to set that word
   to one on the object held at offset 4 of the structure g_profileStatisticsScreen points to. */

void SmpOverlay_SetObjectValue(struct Object6C *object, s32 value) {
    object->value = value;
}

s32 SmpOverlay_DispatchSlotEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (
#if defined(VERSION_DE)
g_overlaySlotEventHandlersDe
#elif defined(VERSION_EU)
g_overlaySlotEventHandlersEu
#elif defined(VERSION_EU_X)
g_overlaySlotEventHandlersEuX
#elif defined(VERSION_US)
g_overlaySlotEventHandlersUs
#elif defined(VERSION_US_REV1)
g_overlaySlotEventHandlers
#endif
 != 0) {
        wildcard = 30000;
        entry = (char *)&
#if defined(VERSION_DE)
g_overlaySlotEventHandlersDe
#elif defined(VERSION_EU)
g_overlaySlotEventHandlersEu
#elif defined(VERSION_EU_X)
g_overlaySlotEventHandlersEuX
#elif defined(VERSION_US)
g_overlaySlotEventHandlersUs
#elif defined(VERSION_US_REV1)
g_overlaySlotEventHandlers
#endif
;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_overlaySlotEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_overlaySlotEventActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}

void SmpOverlay_DrawOverlayWidget(Shared_Item *widget, Args args) {
    QuadN64EngDrawNumericWidgetChildren first;
    QuadN64EngDrawNumericWidgetChildren basis;
    QuadN64EngDrawNumericWidgetChildren value;
    QuadN64EngDrawNumericWidgetChildren transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((widget->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.x, &value.z, &value.y, &value.w);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.x, transformed.z,
                          transformed.y, transformed.w);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(widget->label, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.x, value.z, value.y, value.w);
        }
    }
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 SmpOverlay_ReturnUnhandledEvent(void) {
    return 0;
}

/* 804196C0_25.CPP */
/* Calls MarkMenuEventHandled and, for an event of kind one on a slot with no word at 0x5C whose child at 0x4C has flag 0x10 of its halfword at 0x12 set and a target at 0x34, passes the owner, the slot and the target to SmpOverlay_ShowSlotNode_SmpOverlay, returning zero. */

/* After MarkMenuEventHandled, forwards an event for a channel to Menu_RouteElementEvent with the channel's handler id
   (short at 0xC of the handler at 0x4C) when the channel is not muted (word at 0x5C) and has a handler;
   returns 0. */

/* Calls Cache_FreeMemory with the arguments it was given and returns zero. */

s32 SmpOverlay_FollowSlotTarget34(struct sm_dlmultiuser_t *owner, s32 unused1, s32 slot, s32 kind) {
    struct Child *child;

    MarkMenuEventHandled();
    if (kind != 1) {
        return 0;
    }
    if (owner->locked[(u16)slot] != 0) {
        return 0;
    }
    child = owner->shown[(u16)slot];
    if (child == 0) {
        return 0;
    }
    if (!(child->flags & 0x10)) {
        return 0;
    }
    if (child->target == 0) {
        return 0;
    }
    SmpOverlay_ShowSlotNode(owner, (u16)slot, child->target);
    return 0;
}

s32 SmpOverlay_FollowSlotTarget2c(struct sm_dlmultiuser_t *owner, s32 unused1, s32 slot, s32 kind) {
    struct MenuListTargetView *child;

    MarkMenuEventHandled();
    if (kind != 1) {
        return 0;
    }
    if (owner->locked[(u16)slot] != 0) {
        return 0;
    }
    child = owner->shown[(u16)slot];
    if (child == 0) {
        return 0;
    }
    if (!(child->flags & 0x10)) {
        return 0;
    }
    if (child->target == 0) {
        return 0;
    }
    SmpOverlay_ShowSlotNode(owner, (u16)slot, child->target);
    return 0;
}

s32 SmpOverlay_FollowSlotTarget38(struct sm_dlmultiuser_t *owner, s32 unused1, s32 slot, s32 kind) {
    struct MenuOverlayTargetView *child;

    MarkMenuEventHandled();
    if (kind != 1) {
        return 0;
    }
    if (owner->locked[(u16)slot] != 0) {
        return 0;
    }
    child = owner->shown[(u16)slot];
    if (child == 0) {
        return 0;
    }
    if (!(child->flags & 0x10)) {
        return 0;
    }
    if (child->target == 0) {
        return 0;
    }
    SmpOverlay_ShowSlotNode(owner, (u16)slot, child->target);
    return 0;
}

s32 SmpOverlay_FollowSlotTarget30(struct sm_dlmultiuser_t *owner, s32 unused1, s32 slot, s32 kind) {
    struct MenuTextTargetView *child;

    MarkMenuEventHandled();
    if (kind != 1) {
        return 0;
    }
    if (owner->locked[(u16)slot] != 0) {
        return 0;
    }
    child = owner->shown[(u16)slot];
    if (child == 0) {
        return 0;
    }
    if (!(child->flags & 0x10)) {
        return 0;
    }
    if (child->target == 0) {
        return 0;
    }
    SmpOverlay_ShowSlotNode(owner, (u16)slot, child->target);
    return 0;
}

int SmpOverlay_ForwardSlotEvent(Mixer *mixer, int unused, int channel, int value, int extra) {
    MenuActorInputView *h;

    MarkMenuEventHandled();
    if (mixer->muted[(unsigned short)channel] != 0) {
        return 0;
    }
    h = mixer->handlers[(unsigned short)channel];
    if (h == 0) {
        return 0;
    }
    Menu_RouteElementEvent(h->input, 1, channel, value, extra);
    return 0;
}

s32 SmpOverlay_FreeEventObject(void *allocation) {
    Cache_FreeMemory(allocation);
    return 0;
}

/* 8041BEA8_5.CPP */
extern SlotDialog *g_pakDialog;

/* Calls Widget_SetWidgetFlag40_EquipActivateequipmentpanel with flag 1 on each of the list's items (count at 0x48, items from 0x4C) and
   returns 0. */

/* Updates the slot-selection dialog after availability and capacity probes, choosing unavailable, empty and confirmation states or entering the requested transition. The negative probe statuses -4, -3 and -1 trigger the error transition. */

#if defined(VERSION_DE)
enum { SLOT_RESOURCE_962 = 956, SLOT_RESOURCE_966 = 961, SLOT_RESOURCE_968 = 960, SLOT_RESOURCE_971 = 964 };
#elif defined(VERSION_EU)
enum { SLOT_RESOURCE_962 = 962, SLOT_RESOURCE_966 = 966, SLOT_RESOURCE_968 = 968, SLOT_RESOURCE_971 = 971 };

#elif defined(VERSION_EU_X)
enum { SLOT_RESOURCE_962 = 967, SLOT_RESOURCE_966 = 969, SLOT_RESOURCE_968 = 971, SLOT_RESOURCE_971 = 975 };

#else
enum { SLOT_RESOURCE_962 = 962, SLOT_RESOURCE_966 = 966, SLOT_RESOURCE_968 = 968, SLOT_RESOURCE_971 = 971 };

#endif

extern s32 Control_IsControllerConnected(s32);

extern void SmXlate_SwitchScreen(s32);

extern void Menu_SetFocusedElement(s32);

extern void Tsmos_ActivateControllerState(void);

extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);

extern s32 Note_FindNoteByName(void *name, s32 channel, s32 *noteIndex);

extern s32 PAKInterface_CheckRecordsNoteCapacity(void *slot, s32 *out);

extern void SmpOverlay_AdvancePakDialogPort(void);

#if defined(VERSION_DE)
extern const unsigned char g_noteCountIntFormat[];

extern s32 g_pakProfileOperationPhase;
#elif defined(VERSION_EU)
extern char s_pakDialogNoteCountFormatEuropean[];
extern s32 g_pakDialogProbeStateEu;
#elif defined(VERSION_EU_X)
extern char s_pakDialogNoteCountFormatEuropean[];
extern s32 g_pakDialogProbeStateEuX;

#elif defined(VERSION_US)
extern const unsigned char g_noteCountIntFormat[];

extern s32 g_pakDialogProbeStateUs;
#else
extern const unsigned char g_noteCountIntFormat[];
extern s32 g_pakDialogProbeStateUsRev1;

#endif

/* Calls Tsmos_DeactivateControllerState and MarkMenuEventHandled, then SmXlate_SwitchScreen with 2, sets g_pakRecheckRequested and returns
   one. */

/* Refreshes each of the four ports through Note_ProbeStatus and sets field 0x1C of g_pakDialog as soon as one reports status 0, -1, -3 or -4 through Note_GetStatus, clearing it otherwise. */

/* Advances the slot-dialog retry counter. Before the fourth attempt it updates
 * the dialog; later attempts start the transition and mark it active. */

extern void SmpOverlay_RefreshPakDialog(void);

/* Builds screen state g_pakDialog under a parent window: allocates its 0x2C bytes, keeps the parent,
   opens windows 0x3C3 (shown), 0x3C9, 0x3C4 and 0x3C5 (hidden) at 0x4 to 0x10, clears the words at
   0x14 and 0x18, resets through Frontend_RequestScreenMode_AchieveUpdateresultsscreen(0) and Tsmos_DeactivateControllerState, sets g_introSelectedItem to -1 and
   g_introSelectionState to 0, releases the resources of g_gameSession and of its block at 0x3C8, clears the
   word at 0x1C and returns zero. */

extern void SetN64_ResetSessionPlayerPools(void *, s32, s32);

extern void Scene_LoadLevelResources(void *, s32, s32);

/* Releases the object g_pakDialog holds through Cache_FreeMemory, clears g_pakDialog and returns zero. */

/* In one- or no-player mode, counts a tick on the state g_pakDialog and, while it is not paused, once
   more than five ticks have passed runs Tsmos_ActivateControllerState and SmpOverlay_AdvancePakDialogPort; always returns 0. */

/* The slot-error scalar is real external storage in every ROM version: the de cart writes
   800DF4C4, eu writes 800EFB34, eu-x writes 800EACF4, us writes 800DE174, us-rev1 800E3514. */

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_pakDialogEventIds, an actor kind at g_pakDialogEventActorKinds and a handler at g_pakDialogEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

int SmpOverlay_SetListWidgetFlag40(OverlayWidgetListView *list) {
    int i;

    for (i = 0; i < list->count; i++) {
        Widget_SetWidgetFlag40(list->items[i], 1);
    }
    return 0;
}

void SmpOverlay_RefreshPakDialog(void) {
    s32 foundNote;
    u32 hasRoom;
    s32 focusedResourceId;
    s32 controllerConnected;
    s32 pakStatus;
    s32 hasCapacity;
    s32 canContinue;
    Label *statusTextWidget;

    Menu_SetFocusedElement(SLOT_RESOURCE_962);
    Widget_SetWidgetFlag08(g_pakDialog->absent, 0);
    canContinue = 0;
    Widget_SetWidgetFlag08(g_pakDialog->unavailable, 0);
    hasCapacity = 1;
    Widget_SetWidgetFlag08(g_pakDialog->prompt, 0);
    controllerConnected = Control_IsControllerConnected(0);
    if (controllerConnected == 1) {
        SmpOverlay_ProbePakDialogPorts();
        if (g_pakDialog->ready == 1) {
            Note_ProbeStatus(g_pakProfileControllerPort);
            pakStatus = Note_GetStatus(g_pakProfileControllerPort);
            switch (pakStatus) { /* irregular */
            case 0:
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                if ((Note_FindNoteByName(((g_pakProfileGameNames)[g_languageIndex]), g_pakProfileControllerPort, &foundNote) == 0) && (PAKInterface_CheckRecordsNoteCapacity(g_pakProfileControllerPort, &hasRoom) == 0)) {
#else
                if ((Note_FindNoteByName((g_pakProfileGameNameFixed), g_pakProfileControllerPort, &foundNote) == 0) && (PAKInterface_CheckRecordsNoteCapacity(g_pakProfileControllerPort, &hasRoom) == 0)) {
#endif
                    hasCapacity = hasRoom > 0U;
                }
                break;
            case -4:
            case -3:
            case -1:
                canContinue = 1;
                break;
            }
        }
    }
    if (controllerConnected == 0) {
        g_pakDialog->state = 1;
        g_pakDialog->elapsed = 0;
        Widget_SetWidgetFlag08(g_pakDialog->main, 0);
        Widget_SetWidgetFlag08(g_pakDialog->unavailable, 1);
        goto block_25;
    }
    if (g_pakDialog->ready == 0) {
        g_pakDialog->state = 2;
        g_pakDialog->elapsed = 0;
        Widget_SetWidgetFlag08(g_pakDialog->main, 0);
        Widget_SetWidgetFlag08(g_pakDialog->absent, 1);
        focusedResourceId = SLOT_RESOURCE_971;
        goto block_24;
    }
    if ((canContinue == 1) || (g_combinedControllerProfile.buttons & 0x1000)) {
        MarkMenuEventHandled();
        g_pakRequestLatched = 1;
        g_pakStartButtonLatched = 1;
        g_pakScanActive = 0;
        if (canContinue == 0) {
#if defined(VERSION_DE)
            g_pakProfileOperationPhase = 0;
#elif defined(VERSION_EU)
            g_pakDialogProbeStateEu = 0;
#elif defined(VERSION_EU_X)
            g_pakDialogProbeStateEuX = 0;
#elif defined(VERSION_US)
            g_pakDialogProbeStateUs = 0;
#else
            g_pakDialogProbeStateUsRev1 = 0;
#endif
        } else {
#if defined(VERSION_DE)
            g_pakProfileOperationPhase = 2;
#elif defined(VERSION_EU)
            g_pakDialogProbeStateEu = 2;
#elif defined(VERSION_EU_X)
            g_pakDialogProbeStateEuX = 2;
#elif defined(VERSION_US)
            g_pakDialogProbeStateUs = 2;
#else
            g_pakDialogProbeStateUsRev1 = 2;
#endif
        }
        PAKInterface_SetScreenPhase(6);
        SmXlate_SwitchScreen(19);
        return;
    }
    if (hasCapacity == 1) {
        SmpOverlay_AdvancePakDialogPort();
        return;
    }
    statusTextWidget = Node_FindWidgetByResourceId(g_pakDialog->root, SLOT_RESOURCE_968);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    XStdio_FormatBuffer(g_pakDialog->text, s_pakDialogNoteCountFormatEuropean, g_pakProfileControllerPort + 1);
#else
    XStdio_FormatBuffer(g_pakDialog->text, g_noteCountIntFormat, g_pakProfileControllerPort + 1);
#endif
    statusTextWidget->text = g_pakDialog->text;
    g_pakDialog->state = 3;
    g_pakDialog->elapsed = 0;
    Widget_SetWidgetFlag08(g_pakDialog->main, 0);
    Widget_SetWidgetFlag08(g_pakDialog->prompt, 1);
    focusedResourceId = SLOT_RESOURCE_966;
block_24:
    Menu_SetFocusedElement(focusedResourceId);
block_25:
    Tsmos_ActivateControllerState();
}

s32 SmpOverlay_FinishPakDialog(void) {
    Tsmos_DeactivateControllerState();
    MarkMenuEventHandled();
    SmXlate_SwitchScreen(2);
    g_pakRecheckRequested = 1;
    return 1;
}

void SmpOverlay_ProbePakDialogPorts(void) {
    s32 port;

    g_pakDialog->ready = 0;
    for (port = 0; port < 4; port++) {
        Note_ProbeStatus(port);
        switch (Note_GetStatus(port)) {
        case 0:
            g_pakDialog->ready = 1;
            return;
        case -1:
        case -3:
        case -4:
            g_pakDialog->ready = 1;
            return;
        }
    }
}

void SmpOverlay_AdvancePakDialogPort(void) {
    g_pakProfileControllerPort++;
    if (g_pakProfileControllerPort >= 4) {
        Tsmos_DeactivateControllerState();
        MarkMenuEventHandled();
        SmXlate_SwitchScreen(2);
        g_pakRecheckRequested = 1;
    } else {
        SmpOverlay_RefreshPakDialog();
    }
}

s32 SmpOverlay_CreatePakDialog(void *parent) {
    void *window;
    char *resources;
    g_pakDialog = Cache_AllocateMemory(44);
    g_pakDialog->root = parent;
#if defined(VERSION_DE)
    window = Node_FindWidgetByResourceId(parent, 958);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    window = Node_FindWidgetByResourceId(parent, 963);
#elif defined(VERSION_EU_X)
    window = Node_FindWidgetByResourceId(parent, 972);
#endif
    g_pakDialog->main = window;
    Widget_SetWidgetFlag08(window, 1);
#if defined(VERSION_DE)
    window = Node_FindWidgetByResourceId(parent, 963);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    window = Node_FindWidgetByResourceId(parent, 969);
#elif defined(VERSION_EU_X)
    window = Node_FindWidgetByResourceId(parent, 973);
#endif
    g_pakDialog->absent = window;
    Widget_SetWidgetFlag08(window, 0);
#if defined(VERSION_DE)
    window = Node_FindWidgetByResourceId(parent, 957);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    window = Node_FindWidgetByResourceId(parent, 964);
#elif defined(VERSION_EU_X)
    window = Node_FindWidgetByResourceId(parent, 966);
#endif
    g_pakDialog->unavailable = window;
    Widget_SetWidgetFlag08(window, 0);
#if defined(VERSION_DE)
    window = Node_FindWidgetByResourceId(parent, 959);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    window = Node_FindWidgetByResourceId(parent, 965);
#elif defined(VERSION_EU_X)
    window = Node_FindWidgetByResourceId(parent, 968);
#endif
    g_pakDialog->prompt = window;
    Widget_SetWidgetFlag08(window, 0);
    g_pakDialog->elapsed = 0;
    g_pakDialog->state = 0;
    Frontend_RequestScreenMode(0);
    Tsmos_DeactivateControllerState();
    g_introSelectedItem = -1;
    g_introSelectionState = 0;
    resources = (char *)&g_gameSession;
    SetN64_ResetSessionPlayerPools(resources, 0, 0);
    Scene_LoadLevelResources((char *)&((GameSession *)resources)->world, 0, 0);
    g_pakDialog->ready = 0;
    return 0;
}

s32 SmpOverlay_DestroyPakDialog(void) {
    Cache_FreeMemory(g_pakDialog);
    g_pakDialog = 0;
    return 0;
}

int SmpOverlay_TickPakDialog(void) {
    if (g_selectionMessageStage < 2) {
        g_pakDialog->elapsed++;
        if (g_pakDialog->state == 0) {
            if (g_pakDialog->elapsed < 6) {
                return 0;
            }
            Tsmos_ActivateControllerState();
            SmpOverlay_AdvancePakDialogPort();
        }
    }
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 SmpOverlay_ReturnUnhandledPakDialogEvent(void) {
    return 0;
}

s32 SmpOverlay_ConsumePakDialogEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* The dialog-event codes Menu_GetFocusedElementId reports differ per cartridge family: the European
   eu-x cart numbers them 0x3C9..0x3CF, the de cart 0x3C1..0x3C5, and eu/us/us-rev1 0x3C6..0x3CB.
   Each case below carries the same work in every family, only its label changes. */
s32 SmpOverlay_HandlePakDialogChoice(void) {
    MarkMenuEventHandled();
    switch (Menu_GetFocusedElementId()) {
#if defined(VERSION_EU_X)
    case 975:
#elif defined(VERSION_DE)
    case 964:
#else
    case 971:
#endif
        Widget_SetWidgetFlag08(g_pakDialog->absent, 0);
        SmpOverlay_RefreshPakDialog();
        break;
#if defined(VERSION_EU_X)
    case 974:
#elif defined(VERSION_DE)
    case 965:
#else
    case 970:
#endif
        SmpOverlay_FinishPakDialog();
        break;
#if defined(VERSION_EU_X)
    case 970:
#elif defined(VERSION_DE)
    case 962:
#else
    case 967:
#endif
        SmpOverlay_AdvancePakDialogPort();
        break;
#if defined(VERSION_EU_X)
    case 969:
#elif defined(VERSION_DE)
    case 961:
#else
    case 966:
#endif
        g_pakRequestLatched = 1;
        g_pakStartButtonLatched = 1;
        g_pakScanActive = 0;
#if defined(VERSION_EU)
        g_pakDialogProbeStateEu = 1;
#elif defined(VERSION_EU_X)
        g_pakDialogProbeStateEuX = 1;
#elif defined(VERSION_DE)
        g_pakProfileOperationPhase = 1;
#elif defined(VERSION_US)
        g_pakDialogProbeStateUs = 1;
#else
        g_pakDialogProbeStateUsRev1 = 1;
#endif
        PAKInterface_SetScreenPhase(6);
        SmXlate_SwitchScreen(19);
        break;
    }
    return 0;
}

s32 SmpOverlay_DispatchPakDialogEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_pakDialogEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_pakDialogEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_pakDialogEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_pakDialogEventActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}

/* 800E1470_2.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
const unsigned char s_SmpOverlay_RefreshPakDialogTextDePart2[16] = {
    0x25, 0x64, 0x00,
    /* Retained suffix 800EDAD3..800EDAE0 in this same object. */
    0x2F, 0x01, 0x29, 0x01, 0x2C, 0x01, 0x2A, 0x01, 0x2B, 0x08, 0x00, 0xFF, 0xE5,
};
#endif
#if defined(VERSION_EU_X)
const unsigned int s_SmpOverlay_RefreshPakDialogTextDePart2[1] = {
    0x25640086,
};
#endif
#endif


/* DEBUG_MENU_RETAINED_STORAGE_FLOAT_WORDS_EU_X.CPP */
#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
f32 g_OverlaysElevenConstantsRetainedWords2[3] = {
    0.00450450461f, 0.00352112669f, 0.00450450461f
};
#endif
#endif

/* G_OVERLAYSNINECONSTANTSFLOATCONSTANTWORDS.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: data/unresolved/800E1484 */
#if defined(VERSION_US_REV1)
f32 g_overlaysNineConstantsFloatConstantWords[3] = {
    0.00450450461f, 0.00352112669f, 0.00450450461f
};
#endif
#endif

/* G_NOTECOUNTINTFORMAT.CPP */
#if defined(VERSION_DE) || defined(VERSION_US)
const unsigned char s_pakDialogNoteCountFormat[3] = {
    0x25, 0x64, 0x00,
};
#endif

#if defined(VERSION_US)
char s_GNotecountintformatMEDALSSCREEText[13] =
    "_MEDALS_SCREE";
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
char s_GNotecountintformatMObjectIndeText[13] =
    "m object inde";
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_noteCountIntFormat_GNotecountintformat.c */
const unsigned char g_noteCountIntFormat[] = {
    0x25, 0x64, 0x00,
#if defined(VERSION_US_REV1)
    0x86,
#endif
};
#endif
