#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "MENU/SELECTION_DISPATCHCHARACTERSELECTIONEVENT.H"

/* SELECTION_DESTROYUSCHARACTERSELECTIONMENU.CPP */
#if defined(VERSION_US)
/* Releases the object g_characterSelectionMenu holds through Cache_FreeMemory, clears g_characterSelectionMenu, calls
   Tsmos_ActivateControllerState and Tsmos_SetModeOneFlag with 2, and returns zero. */
extern struct SelectionScreenState *g_characterSelectionMenu;
extern void Tsmos_ActivateControllerState(void);

s32 Selection_DestroyUsCharacterSelectionMenu(void) {
    Cache_FreeMemory(g_characterSelectionMenu);
    g_characterSelectionMenu = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetModeOneFlag(2);
    return 0;
}

/* Calls Tsmos_SetModeOneFlag with 1 and SoundElement_PlayFlatSound with 0xE78, and returns zero. */

s32 Selection_ActivateCharacterSelectionMode(void) {
    Tsmos_SetModeOneFlag(1);
    SoundElement_PlayFlatSound(3704);
    return 0;
}
#endif
/* SELECTION_DESTROYCHARACTERSELECTIONMENU.CPP */
#if !(defined(VERSION_US))
/* Releases the object g_characterSelectionMenu holds through Cache_FreeMemory, clears g_characterSelectionMenu, calls
   Tsmos_ActivateControllerState and Tsmos_SetModeOneFlag with 2, and returns zero. */
extern struct SelectionScreenState *g_characterSelectionMenu;
extern void Tsmos_ActivateControllerState(void);

s32 Selection_DestroyCharacterSelectionMenu(void) {
    Cache_FreeMemory(g_characterSelectionMenu);
    g_characterSelectionMenu = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetModeOneFlag(2);
    return 0;
}

/* Calls Tsmos_SetModeOneFlag with 1 and SoundElement_PlayFlatSound with 0xE78, and returns zero. */

s32 Selection_ActivateCharacterSelectionMode(void) {
    Tsmos_SetModeOneFlag(1);
    SoundElement_PlayFlatSound(3704);
    return 0;
}
#endif

/* SELECTION_CANCELCHARACTERCONFIRMATION.CPP */
/* Handles a packed message whose high half is type 3 with no extra argument: when the entry named by
   its low half in the 0x4C8-byte table g_characterSelectionMenu is active and has a target, runs Menu_CyclePlayerCharacterVariant on it
   and plays sound 0xE7C; always returns 0. */

extern void Menu_CyclePlayerCharacterVariant(int, CharacterVariantSelectionEntry *);

/* Advances a player panel from its ready state and starts its selection. */

void MarkMenuEventHandled(void);

                           /* extern */
void SmpOverlay_SetSlotValue(s32, s32, s32, StateMenuCancelCharacterConfirmation *);

         /* extern */
void Preview_SetPreviewTransformUpdate(struct Object49C *object, s32 value);

                    /* extern */

/* Applies the chosen character when the active player panel is ready. */

                                  /* extern */
s32 Widget_ListHasFlag100(struct WidgetNode *node);

                             /* extern */
void *SmpOverlay_GetSlotValue(s32, s32);

                        /* extern */
s32 SmpOverlay_GetSlotNodeId(s32, s32);

                        /* extern */
void Menu_ApplySlotValueGfx(s32, s32);

                          /* extern */

#if defined(VERSION_DE)
enum { SPECIAL_CHAR = 127 };
#elif defined(VERSION_EU_X)
enum { SPECIAL_CHAR = 133 };
#else
enum { SPECIAL_CHAR = 129 };
#endif

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_characterSelectionEventIds, an actor kind at g_characterSelectionEventActorKinds and a handler at g_characterSelectionEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

extern s32 g_characterSelectionEventIds;

extern s32 g_characterSelectionEventActorKinds;

extern WidgetEventHandler g_characterSelectionEventHandlers;

int Selection_HandleCharacterVariantCycle(int unused0, int unused1, unsigned int message, int extra) {
    int index = message & 0xFFFF;
    CharacterVariantSelectionEntry *e;

    if ((message >> 16) == 3 && extra == 0) {
        e = &((CharacterVariantSelectionEntry *)g_characterSelectionMenu)[index];
        if (e->active == 1 && e->target != -1) {
            Menu_CyclePlayerCharacterVariant(index, e);
            SoundElement_PlayFlatSound(3708);
        }
    }
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Selection_ReturnCharacterEventZeroA(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Selection_ReturnCharacterEventZeroB(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Selection_ReturnCharacterEventZeroC(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Selection_ReturnCharacterEventZeroD(void) {
    return 0;
}

/* extern */

s32 Selection_CancelCharacterConfirmation(s32 unused0, s32 unused1, s32 entryId) {
    s32 confirmationState;
    s32 entryIndex;
    s32 entryOffset;
    StateMenuCancelCharacterConfirmation *selectionEntry;

    MarkMenuEventHandled();
    entryIndex = entryId & 0xFFFF;
    entryOffset = entryIndex * 1224;
    selectionEntry = (StateMenuCancelCharacterConfirmation *)&((PanelRecord *)g_characterSelectionMenu)[entryIndex];
    confirmationState = selectionEntry->confirmationState;
    switch (confirmationState) {
    case 1:
        if (g_gameSettings.controllerMode != 1) {
            g_characterSelectionMenu->phase = 5;
            g_characterSelectionMenu->timer = 4;
            g_characterSelectionMenu->result = 3;
        }
        break;
    case 3:
        selectionEntry->confirmationState = 1;
        SmpOverlay_SetSlotValue(g_characterSelectionMenu->slotOverlay, entryIndex, 0, selectionEntry);
        Preview_SetPreviewTransformUpdate(&((PanelRecord *)(entryOffset + (s32)g_characterSelectionMenu))->target, 1);
        Menu_RefreshPlayerCharacterVariants(entryIndex);
        break;
    }
    return 0;
}

s32 Selection_ReadSelectionSlot(s32 unusedFirst, s32 unusedSecond, s32 packedPlayer) {
    s32 entryIndex;
    s32 choice;
    s32 unusedValue;
    CharacterSelectionRoot *characterSelectionRoot;

    entryIndex = packedPlayer & 0xFFFF;
    choice = SmpOverlay_GetSlotNodeId(g_characterSelectionMenu->slotOverlay, entryIndex);
    MarkMenuEventHandled();
    characterSelectionRoot = (CharacterSelectionRoot *)((char *)g_characterSelectionMenu + (entryIndex * sizeof(SelectionScreenPlayer)));
    if (characterSelectionRoot->phase == 1) {
        if (choice == SPECIAL_CHAR) Menu_ApplySlotValueGfx(entryIndex,characterSelectionRoot->choice);
        else if (Widget_ListHasFlag100(SmpOverlay_GetSlotValue(g_characterSelectionMenu->slotOverlay,entryIndex)) == 0) Menu_ApplySlotValueGfx(entryIndex,choice);
    }
    return 0;
}

s32 Selection_DispatchCharacterSelectionEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_characterSelectionEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_characterSelectionEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_characterSelectionEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_characterSelectionEventActorKinds)) + offset))->value;
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

