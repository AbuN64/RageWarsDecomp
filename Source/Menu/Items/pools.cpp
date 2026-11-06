#include "Engine/session.h"
#include "include_asm.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Common/gameplay_camera.h"
#include "Common/viewflags.h"
#include "Common/objb.h"
#include "Common/heap_arena_entry.h"
#include "types.h"
#include "Ui/X_files/x_plus.h"
#include "Menu/scene_resource_preview_and_collision_views.h"
#include "Common/sharedplayer.h"
#include "Engine/Cache/list.h"
#include "Camera/camera.h"
#include "Engine/Audio/T2soundelement/sound_context_control.h"
#include "Gsky/gsky_setgameplaymode.h"
#include "Gsky/sky_drawlensflare.h"
#include "Gsky/sky_posttargetedscreenmessage.h"
#include "Pool/pool.h"
#include "Pools/pools.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/Lone/screen_message_allocation_label.h"
#include "Common/resourcelockstate.h"
#include "Common/cache_allocateresource.h"
#include "Common/triple.h"
#include "Common/cache_releaseresource.h"

/* Initializes camera transforms, viewport state, clipping records, and resource lists. */

void Gsky_ResetFadeState(void *);                            /* extern */
void Menu_InitMenuMessageList(void *);                    /* extern */

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x10, 0x14, 0x20, 0x24], gap at: 0x18. */
void Pools_InitializeGameplayCamera(GameplayCamera *camera) {
    f32 unitValue;
    f32 zero;
    s16 viewportExtent;
    s32 viewportIndex;
    Floats *orientationValues;
    CShake *transformDefaults;
    Floats *firstEffectDefaults;
    Floats *secondEffectDefaults;
    Floats *thirdEffectDefaults;

    Sky_InitializeLensFlareState(((void *)&((GameplayCamera *)camera)->bobSuppressed));
    Graphu64_IdentityMatrix(((GameplayCamera *)camera)->viewOrient);
    Graphu64_IdentityMatrix(((GameplayCamera *)camera)->viewProjection);
    zero = 0.0f;
    unitValue = 1.0f;
    orientationValues = ((void *)&((GameplayCamera *)camera)->orientation);
    orientationValues->floatAt8 = zero;
    orientationValues->floatAt4 = zero;
    camera->orientation.x = zero;
    camera->orientation.w = unitValue;
    Graphu64_IdentityMatrix(((GameplayCamera *)camera)->inverseViewOrient);
    camera->viewWidth = (f32) g_hudReferenceViewportWidth;
    camera->viewHeight = (f32) g_hudReferenceViewportHeight;
    camera->reservedWord = -1;
    camera->viewLeft = zero;
    camera->viewTop = zero;
    camera->clearRed = 0;
    camera->reservedByteE = 0;
    camera->clearGreen = 0;
    camera->reservedByteF = 0;
    camera->clearBlue = 0;
    camera->reservedByteG = 0;
    camera->reservedByteD = 0;
    camera->reservedByteH = 0;
    camera->reservedFloat = unitValue;
    camera->fogNear = 995;
    camera->reservedWordB = 995;
    camera->damageEffectMode = 0;
    camera->dirty = 0;
    camera->pixelXScale = unitValue;
    camera->pixelYScale = unitValue;
    camera->farPlane = (f32) 1024.0f;
    camera->reservedFloatB = (f32) 1024.0f;
    camera->verticalFieldOfView = (f32) 47.5f;
    camera->reservedFloatC = (f32) 47.5f;
    Gsky_ResetFadeState(camera);
    transformDefaults = &camera->shake;
    camera->shakeHorizontal = zero;
    camera->shakeVertical = zero;
    transformDefaults->m_vPos.x = zero;
    transformDefaults->m_vPos.y = zero;
    transformDefaults->m_vPos.z = zero;
    transformDefaults->m_Radius = unitValue;
    firstEffectDefaults = ((void *)&((GameplayCamera *)camera)->shake.x);
    firstEffectDefaults->floatAt4 = zero;
    firstEffectDefaults->floatAt8 = zero;
    firstEffectDefaults->floatAtC = zero;
    firstEffectDefaults->floatAt10 = zero;
    secondEffectDefaults = ((void *)&((GameplayCamera *)camera)->shake.y);
    secondEffectDefaults->floatAt4 = zero;
    secondEffectDefaults->floatAt8 = zero;
    secondEffectDefaults->floatAtC = zero;
    secondEffectDefaults->floatAt10 = zero;
    thirdEffectDefaults = ((void *)&((GameplayCamera *)camera)->shake.z);
    thirdEffectDefaults->floatAt4 = zero;
    thirdEffectDefaults->floatAt8 = zero;
    thirdEffectDefaults->floatAtC = zero;
    thirdEffectDefaults->floatAt10 = zero;
    Gsky_SetGameplayMode(camera, 0);
    viewportExtent = g_hudReferenceViewportWidth * 2;
    for (viewportIndex = 0; viewportIndex < 2; viewportIndex++) {
        ((GameplayCamera *)camera)->viewports[viewportIndex].vscale[0] = viewportExtent;
        ((GameplayCamera *)camera)->viewports[viewportIndex].vscale[1] = viewportExtent;
        ((GameplayCamera *)camera)->viewports[viewportIndex].vscale[2] = 1023;
        ((GameplayCamera *)camera)->viewports[viewportIndex].vscale[3] = 0;
        ((GameplayCamera *)camera)->viewports[viewportIndex].vtrans[0] = viewportExtent;
        ((GameplayCamera *)camera)->viewports[viewportIndex].vtrans[1] = viewportExtent;
        ((GameplayCamera *)camera)->viewports[viewportIndex].vtrans[2] = 0;
        ((GameplayCamera *)camera)->viewports[viewportIndex].vtrans[3] = 0;
    }
    Menu_InitMenuMessageList(((void *)&((GameplayCamera *)camera)->messageList));
    Graphu64_IdentityMatrix(((GameplayCamera *)camera)->faceScreen);
    Graphu64_IdentityMatrix(((GameplayCamera *)camera)->faceScreenUpright);
    camera->fadeEnabled = 0;
    camera->monochrome = 0;
    camera->kickStep = 50;
    camera->effectArgument = 0;
    g_cameraFramingTransitionTimer = 0;
    List_InitializeIntrusive(&((GameplayCamera *)camera)->objects, 0, 4);
    Gsky_InitializeMessageEntryPool(camera);
}

static inline void resetShakeAxis_pools(CShakeAxis *axis) {
    axis->value = 0;
    axis->m_LastShake = 0;
    axis->m_Amp = 0;
    axis->m_Angle = 0;
}
static inline void resetShake_pools(CShake *entry, f32 value) {
    entry->m_vPos.x = 0;
    entry->m_vPos.y = 0;
    entry->m_vPos.z = 0;
    entry->m_Radius = value;
    resetShakeAxis_pools(&entry->x);
    resetShakeAxis_pools(&entry->y);
    resetShakeAxis_pools(&entry->z);
}
void Pools_ResetActorPools(ScreenMessageOwner *owner, s32 actorCount)
{
    s32 i;
    f32 initialValue;
    if (actorCount > 4) actorCount = 4;
    owner->header.lastMode = 0;
    owner->header.layoutTimer = 0;
    owner->self.index = 0;
    Pools_InitializeGameplayCamera(&owner->self);
    owner->header.layoutTimer = 2;
    List_InitializeIntrusive(&owner->freeEffects, 0, 4);
    List_InitializeIntrusive(&owner->activeEffects, 0, 4);
    initialValue = k_menuInitialCounterValue;
    for (i = 0; i < 8; i++) {
        resetShake_pools(&owner->effects[i], initialValue);
        List_AppendIntrusive(&owner->freeEffects, &owner->effects[i]);
    }
    List_InitializeIntrusive(&owner->header.active, 0, 4);
    List_InitializeIntrusive(&owner->header.views, 0, 4);
    List_InitializeIntrusive(&owner->activeMessages, 0, 4);
    owner->state = 1;
    SoundElement_SetListenerCamera(&owner->self);
    Cache_DrainAndCompactResources(0);
    if (owner->header.allocation) {
        Cache_ReleaseResource(0, owner->header.allocation);
        owner->header.allocation = 0; owner->header.cameras = 0; owner->header.count = 0;
    }
    Cache_DrainAndCompactResources(0);
    if (owner->storage.allocation) {
        Cache_ReleaseResource(0, owner->storage.allocation);
        owner->storage.allocation = 0; owner->storage.first = 0; owner->storage.count = 0;
    }
    if (actorCount) {
        owner->header.count = actorCount;
        owner->header.allocation = Cache_AllocateResource(0, actorCount * 3800, 35, g_camerasText);
        owner->header.cameras = *(GameplayCamera **)owner->header.allocation;
        XPlus_FillMemory(owner->header.cameras, 0, actorCount * 3800);
        for (i = 0; i < owner->header.count; i++) {
            owner->header.cameras[i].index = i;
            List_AppendIntrusive(&owner->header.active, &owner->header.cameras[i]);
        }
        SoundElement_SetListenerCamera(owner->header.cameras);
        owner->state = 0;
    }
    owner->storage.count = 16;
    owner->storage.allocation = Cache_AllocateResource(0, 0x400, 35, g_screenMessageAllocationLabel);
    owner->storage.first = *owner->storage.allocation;
    XPlus_FillMemory(owner->storage.first, 0, 0x400);
    for (i = 0; i < owner->storage.count; i++) {
        List_AppendIntrusive(&owner->activeMessages, &((CCameraText *)owner->storage.first)[i]);
    }
}


/* Resets a screen-message owner: clears it, initialises its active, view and active-message lists,
   sets its state to 1 and its layout timer to 2, zeroes the header and storage counters, and resets the embedded
   camera through Pools_InitializeGameplayCamera and Camera_UpdateViewProjectionAndEffects. */
void Pools_ResetPlayers(ScreenMessageOwner *actor) {

    XPlus_FillMemory(actor, 0, 4616);
    List_InitializeIntrusive(&actor->header.active, 0, 4);
    List_InitializeIntrusive(&actor->header.views, 0, 4);
    List_InitializeIntrusive(&actor->activeMessages, 0, 4);
    actor->state = 1;
    actor->header.allocation = 0;
    actor->header.cameras = 0;
    actor->header.count = 0;
    actor->storage.allocation = 0;
    actor->storage.first = 0;
    actor->storage.count = 0;
    actor->header.layoutTimer = 2;
    Pools_InitializeGameplayCamera(&actor->self);
    Camera_UpdateViewProjectionAndEffects(&actor->self);
}

/* Initialises the entry pool of the scene effects of every camera in the group's camera array, then the one of the group's own camera. */
void Pools_InitGroupPools(Triple *group) {
    int i;

    for (i = 0; i < group->z; i++) {
        Pool_InitEntryPool((char *)(i * 3800 + group->y + 1392));
    }
    Pool_InitEntryPool((char *)&((ScreenMessageOwner *)group)->self.sceneEffects);
}

/* Moves an owner's model, when it has one, from the owner's model list to its recycled list after
   finalising it through Pools_InitializeGameplayCamera. Returns the model. */
void *Pools_RecycleModel(struct Draw *owner) {
    void *object = owner->model;

    if (object != 0) {
        Pools_InitializeGameplayCamera(object);
        List_RemoveIntrusive(&owner->model, object);
        List_AppendIntrusive(&owner->recycled, object);
    }
    return object;
}

/* Moves a pool entry from an owner's recycled list back to the front of its model list. */
void Pools_TransferPoolEntry(char *object, void *value) {
    List_RemoveIntrusive(&((struct Draw *)object)->recycled, value);
    List_PrependIntrusive(&((struct Draw *)object)->model, value);
}
