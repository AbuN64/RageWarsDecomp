#include "UI/QUAG/N64_ENG.H"
#include "COMMON/CALLBACK.H"
#include "TYPES.H"
#include "COMMON/AUDIO_INITIALIZE.H"
#include "COMMON/FRUSTUM.H"
#include "COMMON/INTEGERSTATE530.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "RESMGR/STREAM.H"
#include "UI/SMOS/SM_SMNGR.H"

typedef struct Shared_MenuDefinition Shared_MenuDefinition;
struct Shared_MenuDefinition {
    u32 unknown00[3];
    s16 ownerId;
    u16 reservedWord;
    u16 reservedWord1;
    u16 flags;
    u32 reservedElements[11];
    s32 loadedResource;
    Shared_MenuDefinition *defaultFocus;
};
void SmSmngr_InitializeCurrentScreen(void);
void Menu_PopScreen(void);
void StreamBufferFree(StreamBuffer *);
void Stream_DrainResourceWork(void);
void Node_AcquireArchiveEntry(s32);
void Node_ReleaseReferencedBuffer(s32);




extern Shared_MenuDefinition *g_screenDefaultFocus;

void SmXlate_SwitchScreen(s32 index) {
    s32 (*pushBeginCallback)(s32, s32, s32, s32);
    s32 (*pushOwnerCallback)(s32, s32, s32, s32);
    s32 (*replaceLoadCallback)(s32, s32, s32, s32);
    s32 (*replaceReadyCallback)(s32, s32, s32, s32);
    s32 (*focusEnterCallback)(s32, s32, s32, s32);
    s32 (*switchCompleteCallback)(s32, s32, s32, s32);
    s32 (*callback)(s32, s32, s32, s32);
    s32 (*focusLeaveCallback)(s32, s32, s32, s32);
    s32 (*pushLoadCallback)(s32, s32, s32, s32);
    s32 (*pushReadyCallback)(s32, s32, s32, s32);
    s32 oldFocusOwner;
    s32 newFocusOwner;
    s32 (*replaceLoader)(s32);
    s32 (*pushLoader)(s32);
    s32 currentOrInvalidIndex;
    Shared_MenuDefinition *updatedFocus;
    s32 argument;
    s32 e03_arg_copy;
    s32 focus_index_final;
    s32 focus_index;
    s32 callback_status;
    s32 callback_status_5;
    s32 savedReplaceReadyHandled;
    s32 savedFocusEnterHandled;
    s32 savedSwitchCompleteHandled;
    s32 owner;
    s32 handled;
    s32 savedFocusLeaveHandled;
    s32 savedPushLoadHandled;
    s32 savedPushReadyHandled;
    s32 savedPushBeginHandled;
    s32 savedPushOwnerHandled;
    s32 savedReplaceLoadHandled;
    s32 current;
    s32 load_flag;
    s32 *transition_state;
    s32 menuScreenOwnerResult;
    s32 currentScreenIndex;
    Shared_MenuDefinition *priorDefaultFocus;
    s32 previousScreenIndex;
    s32 search_bound;
    s32 screenSearchIndex;
    s32 activeSearchIndex;
    s32 releaseIndex;
    s32 releaseCursor;
    s32 alreadyActive;
    ScreenEntry *search_entries;
    s32 refreshFocus;
    s32 screenFound;
    s32 remainingHandlerCount;
    ScreenManager *manager;
    ScreenEntry *newScreenEntry;
    ScreenEntry *parentScreenEntry;
    Shared_MenuDefinition *focus;
    ScreenEntry *pushedScreenEntry;
    ScreenEntry *replacedScreenEntry;
    Shared_MenuDefinition *finalFocus;
    void *screens;
    Shared_MenuDefinition *newDefinition;
    Shared_MenuDefinition *replacementDefinition;
    Shared_MenuDefinition *parentDefinition;
    Shared_MenuDefinition *pushedDefinition;
    ScreenManager *releaseManager;
    Shared_MenuDefinition *currentDefinition;
    struct MenuHandlerEntry *handlerCursor;
    ScreenEntry *screenCursor;
    ScreenEntry *activeScreenCursor;

    Stream_DrainResourceWork();
    alreadyActive = 0;
    refreshFocus = 1;
    if (g_screenManager->current >= 0) {
        GetMenuScreenOwner();
    }
    previousScreenIndex = g_screenManager->current;
    screens = g_screenManager->screens;
    screenSearchIndex = 0;
    if (previousScreenIndex >= 0) {
        search_bound = previousScreenIndex;
        screenCursor = (void *)screens;
loop_4:
        screenSearchIndex += 1;
        if (screenCursor->owner == index) {
            goto block_found_trampoline;
        }
        screenCursor++;
        if (search_bound >= screenSearchIndex) {
            goto loop_4;
        }
    }
    screenFound = 0;
block_search_check:
    if (screenFound == 0) {
        goto block_not_found;
    }
    {
        menuScreenOwnerResult = GetMenuScreenOwner();
        activeSearchIndex = g_screenManager->lowIndex;
        currentOrInvalidIndex = g_screenManager->current;
        if (currentOrInvalidIndex >= activeSearchIndex) {
            search_entries = g_screenManager->screens;
            do {
                if (search_entries[activeSearchIndex].owner == index) {
                    alreadyActive = 1;
                }
                activeSearchIndex += 1;
            } while (currentOrInvalidIndex >= activeSearchIndex);
        }
        manager = g_screenManager;
        if (((ScreenEntry *)screens)[manager->current].owner != index) {
            do {
                manager->screenChangePending = 1;
                Menu_PopScreen();

                manager = g_screenManager;
            } while (((ScreenEntry *)screens)[g_screenManager->current].owner != index);
        }
        g_screenManager->cacheCount = 0;
        g_screenManager->focus = menuScreenOwnerResult;
        if (alreadyActive == 0) {
            Node_AcquireArchiveEntry(index);
            newDefinition = Node_GetScreenData(index);
            newScreenEntry = ((void *)&g_screenManager->screens[g_screenManager->current]);
            newScreenEntry->primary = newDefinition;
            newScreenEntry->owner = index;
            newScreenEntry->focus = newDefinition->defaultFocus;
            g_screenDefaultFocus = newDefinition->defaultFocus;
            currentDefinition = newDefinition;
            SmSmngr_InitializeCurrentScreen();
            if (((u16) currentDefinition->flags >> 12) & 1) {

                load_flag = 1;
                current = g_screenManager->current;
loop_18:
                if ((((u16) currentDefinition->flags >> 12) & 1) == load_flag) {
                    currentScreenIndex = --g_screenManager->current;
                    g_screenManager->lowIndex = currentScreenIndex;

                    screenSearchIndex = g_screenManager->current;
                    Node_AcquireArchiveEntry(g_screenManager->screens[screenSearchIndex].owner);
                    owner = g_screenManager->screens[g_screenManager->current].owner;
                    parentDefinition = Node_GetScreenData(owner);
                    parentScreenEntry = ((void *)&g_screenManager->screens[g_screenManager->current]);
                    parentScreenEntry->primary = parentDefinition;
                    parentScreenEntry->owner = owner;
                    parentScreenEntry->focus = parentDefinition->defaultFocus;
                    g_screenDefaultFocus = parentDefinition->defaultFocus;
                    g_screenManager->cacheCount = 0;
                    currentDefinition = parentDefinition;
                    SmSmngr_InitializeCurrentScreen();
                    goto loop_18;
                }
                g_screenManager->current = current;
            }
            goto block_78;
block_found_trampoline:
            screenFound = 1;
            goto block_search_check;
        } else {
            currentDefinition = g_screenManager->screens[g_screenManager->current].primary;
            g_screenManager->cacheCount = 0;
            if (((ScreenManager *)g_screenManager)->current != -1) {
                callback = g_screenManager->callback;
                if (callback != 0) {
                    handled = g_screenManager->handled;
                    g_screenManager->handled = 0;
                    callback(3591, 0, 0, 0);
                    callback_status = g_screenManager->handled;
                    if (callback_status == 1) {
                        refreshFocus = 0;
                        g_screenManager->handled = handled;
                        goto after_found_callback;
                    }
                    g_screenManager->handled = handled;
                }
                DispatchCurrentScreenEvent(1, 3591, 0, 0, 0);
                goto block_27;
            } else {
block_27:
                refreshFocus = 0;
            }
        }
after_found_callback:
        goto block_78;
    }
block_not_found:
    Node_AcquireArchiveEntry(index);
    if (((u16) (((Shared_MenuDefinition *)(Node_GetScreenData(index)))->flags) >> 12) & 1) {
        focus = g_screenManager->screens[g_screenManager->current].focus;
        if ((focus != 0) && ((oldFocusOwner = focus->ownerId, (Node_IsValidScreenIndex((s32) oldFocusOwner) == 0)) || (oldFocusOwner == g_screenManager->screens[g_screenManager->current].owner)) && ((focus_index = g_screenManager->current), (oldFocusOwner != g_screenManager->focus)) && ((currentOrInvalidIndex = -1), (focus_index != currentOrInvalidIndex))) {
            focusLeaveCallback = g_screenManager->callback;
            if (focusLeaveCallback != 0) {
                savedFocusLeaveHandled = g_screenManager->handled;
                g_screenManager->handled = 0;
                focusLeaveCallback(16, 0, 0, 0);
                callback_status = g_screenManager->handled;
                if (callback_status == 1) {
                    g_screenManager->handled = savedFocusLeaveHandled;
                    goto after_focus10;
                }
                g_screenManager->handled = savedFocusLeaveHandled;
            }
            if (oldFocusOwner == (((Shared_MenuDefinition *)(g_screenManager->screens[g_screenManager->current].primary))->ownerId)) {
                SmSmngr_DispatchPrimaryScreenEvent(16, 0, 0, 0);
            } else {
                DispatchElementEvent(oldFocusOwner, 16, 0, 0, 0);
            }
        }
after_focus10:
        g_screenManager->focus = GetMenuScreenOwner();
        g_screenManager->current = (s32) (g_screenManager->current + 1);
        pushedDefinition = Node_GetScreenData(index);
        pushedScreenEntry = ((void *)&g_screenManager->screens[g_screenManager->current]);
        pushedScreenEntry->primary = pushedDefinition;
        pushedScreenEntry->owner = index;
        pushedScreenEntry->focus = pushedDefinition->defaultFocus;
        currentDefinition = pushedDefinition;
        g_screenDefaultFocus = currentDefinition->defaultFocus;
        StreamBufferFree(&g_screenManager->screens[g_screenManager->current].data);
        pushLoader = g_screenManager->callback2;
        if (pushLoader != 0) {
            (((Shared_MenuDefinition *)(g_screenManager->screens[g_screenManager->current].primary))->loadedResource) = pushLoader(index);
        }
        g_screenManager->cacheCount = 0;
        if (g_screenManager->current != -1) {
            pushLoadCallback = g_screenManager->callback;
            if (pushLoadCallback != 0) {
                savedPushLoadHandled = g_screenManager->handled;
                g_screenManager->handled = 0;
                pushLoadCallback(3590, 0, 0, 0);
                callback_status_5 = g_screenManager->handled;
                if (callback_status_5 == 1) {
                    g_screenManager->handled = savedPushLoadHandled;
                    goto after_e06;
                }
                g_screenManager->handled = savedPushLoadHandled;
            }
            DispatchCurrentScreenEvent(1, 3590, 0, 0, 0);
        }
after_e06:
        if (((ScreenManager *)g_screenManager)->current != -1) {
            pushReadyCallback = g_screenManager->callback;
            if (pushReadyCallback != 0) {
                savedPushReadyHandled = g_screenManager->handled;
                g_screenManager->handled = 0;
                pushReadyCallback(3591, 0, 0, 0);
                callback_status = g_screenManager->handled;
                if (callback_status == 1) {
                    g_screenManager->handled = savedPushReadyHandled;
                    goto block_78;
                }
                g_screenManager->handled = savedPushReadyHandled;
            }
            DispatchCurrentScreenEvent(1, 3591, 0, 0, 0);
        }
        goto block_78;
    }
    if (g_screenManager->current != -1) {
        pushBeginCallback = g_screenManager->callback;
        if (pushBeginCallback != 0) {
            savedPushBeginHandled = g_screenManager->handled;
            g_screenManager->handled = 0;
            pushBeginCallback(3585, 0, 0, 0);
            callback_status = g_screenManager->handled;
            if (callback_status == 1) {
                g_screenManager->handled = savedPushBeginHandled;
                goto after_e01;
            }
            g_screenManager->handled = savedPushBeginHandled;
        }
        SmSmngr_DispatchPrimaryScreenEvent(3585, 0, 0, 0);
    }
after_e01:
    Stream_DrainResourceWork();
    e03_arg_copy = index;
    if (g_screenManager->current != -1) {
        pushOwnerCallback = g_screenManager->callback;
        if (pushOwnerCallback != 0) {
            savedPushOwnerHandled = g_screenManager->handled;
            g_screenManager->handled = 0;
            pushOwnerCallback(3587, index, 0, 0);
            callback_status = g_screenManager->handled;
            if (callback_status == 1) {
                g_screenManager->handled = savedPushOwnerHandled;
                goto after_e03;
            }
            g_screenManager->handled = savedPushOwnerHandled;
        }
        SmSmngr_DispatchPrimaryScreenEvent(3587, e03_arg_copy, 0, 0);
    }
after_e03:
    releaseManager = g_screenManager;
    currentScreenIndex = releaseManager->current;
    releaseCursor = releaseManager->lowIndex;
    if (currentScreenIndex >= 0) {
        if (currentScreenIndex >= releaseCursor) {
            releaseIndex = releaseCursor;
            do {
                releaseCursor += 1;
                Node_ReleaseReferencedBuffer(releaseManager->screens[releaseIndex].owner);
                releaseManager = g_screenManager;
                g_screenManager->screens[releaseIndex].primary = 0;
                g_screenManager->screens[releaseIndex].focus = 0;
                releaseIndex += 1;
            } while (g_screenManager->current >= releaseCursor);
        }
        remainingHandlerCount = 63;
        handlerCursor = g_screenManager->handlers;
        do {
            handlerCursor->override_handler = 0;
            remainingHandlerCount -= 1;
            handlerCursor++;
        } while (remainingHandlerCount >= 0);

        releaseManager = g_screenManager;
    }
    releaseManager->lowIndex = releaseManager->current;
    g_screenManager->focus = GetMenuScreenOwner();
    g_screenManager->current = (s32) (g_screenManager->current + 1);
    replacementDefinition = Node_GetScreenData(index);
    replacedScreenEntry = ((void *)&g_screenManager->screens[g_screenManager->current]);
    replacedScreenEntry->primary = replacementDefinition;
    replacedScreenEntry->owner = index;
    replacedScreenEntry->focus = replacementDefinition->defaultFocus;
    g_screenDefaultFocus = replacementDefinition->defaultFocus;
    g_screenManager->lowIndex = (s32) g_screenManager->current;
    replaceLoader = g_screenManager->callback2;
    currentDefinition = replacementDefinition;
    if (replaceLoader != 0) {
        (((Shared_MenuDefinition *)(g_screenManager->screens[g_screenManager->current].primary))->loadedResource) = replaceLoader(index);
    }
    g_screenManager->cacheCount = 0;
    if (g_screenManager->current != -1) {
        replaceLoadCallback = g_screenManager->callback;
        if (replaceLoadCallback != 0) {
            savedReplaceLoadHandled = g_screenManager->handled;
            g_screenManager->handled = 0;
            replaceLoadCallback(3590, 0, 0, 0);
            callback_status = g_screenManager->handled;
            if (callback_status == 1) {
                g_screenManager->handled = savedReplaceLoadHandled;
                goto after_e06_second;
            }
            g_screenManager->handled = savedReplaceLoadHandled;
        }
        DispatchCurrentScreenEvent(1, 3590, 0, 0, 0);
    }
after_e06_second:
    if (((ScreenManager *)g_screenManager)->current != -1) {
        replaceReadyCallback = g_screenManager->callback;
        if (replaceReadyCallback != 0) {
            savedReplaceReadyHandled = g_screenManager->handled;
            g_screenManager->handled = 0;
            replaceReadyCallback(3591, 0, 0, 0);
            callback_status = g_screenManager->handled;
            if (callback_status == 1) {
                g_screenManager->handled = savedReplaceReadyHandled;
                goto after_e07_second;
            }
            g_screenManager->handled = savedReplaceReadyHandled;
        }
        DispatchCurrentScreenEvent(1, 3591, 0, 0, 0);
    }
after_e07_second:
    if (GetMenuScreenOwner() != index) {
        g_screenManager->cacheCount = 0;
        return;
    }
block_78:
    transition_state = &g_screenManager->screenChangePending;
    *transition_state = 1;
    while (refreshFocus != 0) {
        refreshFocus = 0;
        priorDefaultFocus = g_screenDefaultFocus;
        updatedFocus = currentDefinition->defaultFocus;
        if (priorDefaultFocus != updatedFocus) {

            manager = g_screenManager;
            previousScreenIndex = manager->current;
            manager->screens[previousScreenIndex].focus = updatedFocus;
        }
    }
    finalFocus = g_screenManager->screens[g_screenManager->current].focus;
    if ((finalFocus != 0) && ((newFocusOwner = finalFocus->ownerId, (Node_IsValidScreenIndex((s32) newFocusOwner) == 0)) || (newFocusOwner == g_screenManager->screens[g_screenManager->current].owner)) && ((focus_index_final = g_screenManager->current), (newFocusOwner != g_screenManager->focus)) && ((currentOrInvalidIndex = -1), (focus_index_final != currentOrInvalidIndex))) {
        focusEnterCallback = g_screenManager->callback;
        if (focusEnterCallback != 0) {
            savedFocusEnterHandled = g_screenManager->handled;
            g_screenManager->handled = 0;
            focusEnterCallback(15, 0, 0, 0);
            callback_status = g_screenManager->handled;
            if (callback_status == 1) {
                g_screenManager->handled = savedFocusEnterHandled;
                goto after_focus;
            }
            g_screenManager->handled = savedFocusEnterHandled;
        }
        if (newFocusOwner == (((Shared_MenuDefinition *)(g_screenManager->screens[g_screenManager->current].primary))->ownerId)) {
            SmSmngr_DispatchPrimaryScreenEvent(15, 0, 0, 0);
        } else {
            DispatchElementEvent(newFocusOwner, 15, 0, 0, 0);
        }
    }
after_focus:
    if (g_screenManager->current != -1) {
        switchCompleteCallback = g_screenManager->callback;
        if (switchCompleteCallback != 0) {
            savedSwitchCompleteHandled = g_screenManager->handled;
            g_screenManager->handled = 0;
            switchCompleteCallback(3592, 0, 0, 0);
            callback_status = g_screenManager->handled;
            if (callback_status == 1) {
                g_screenManager->handled = savedSwitchCompleteHandled;
                goto after_e08;
            }
            g_screenManager->handled = savedSwitchCompleteHandled;
        }
        argument = (s32)(N64Eng_GetTimeSeconds() * 1000.0);
        DispatchCurrentScreenEvent(1, 3592, argument - g_screenManager->frames, argument, 0);
    }
after_e08:
}
