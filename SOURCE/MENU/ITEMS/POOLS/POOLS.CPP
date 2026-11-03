#include "include_asm.h"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJB.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "UI/X_FILES/X_PLUS.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"

/* Initializes camera transforms, viewport state, clipping records, and resource lists. */


void Sky_InitializeLensFlareState(void *);                               /* extern */
void Gsky_SetGameplayMode(void *, s32);                         /* extern */
void Gsky_ResetFadeState(void *);                            /* extern */
void Gsky_InitializeMessageEntryPool(void *);                            /* extern */
void Graphu64_IdentityMatrix(void *);                            /* extern */
void Menu_InitMenuMessageList(void *);                    /* extern */


extern s32 g_hudReferenceViewportWidth;






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

#include "TYPES.H"
extern f32 k_menuInitialCounterValue;
extern char g_camerasText[];
extern char g_screenMessageAllocationLabel[];
extern void SoundElement_SetListenerCamera(void *);
extern void Cache_DrainAndCompactResources(s32);
extern void Cache_ReleaseResource(s32, void *);
extern void **Cache_AllocateResource(s32, s32, s32, char *);
static inline void resetShakeAxis(CShakeAxis *axis) {
    axis->value = 0;
    axis->m_LastShake = 0;
    axis->m_Amp = 0;
    axis->m_Angle = 0;
}
static inline void resetShake(CShake *entry, f32 value) {
    entry->m_vPos.x = 0;
    entry->m_vPos.y = 0;
    entry->m_vPos.z = 0;
    entry->m_Radius = value;
    resetShakeAxis(&entry->x);
    resetShakeAxis(&entry->y);
    resetShakeAxis(&entry->z);
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
        resetShake(&owner->effects[i], initialValue);
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

/* Resets a 0x1208-byte actor: clears it through XPlus_FillMemory, initialises its three lists at 0xC,
   0x20 and 0xF24 through List_InitializeIntrusive, sets its words at 0x1200 and 0x38 to 1 and 2, clears those at
   0 to 8 and 0xF18 to 0xF20, and resets the parts at offset 0x40 through Pools_InitializeGameplayCamera and
   Camera_UpdateViewProjectionAndEffects. */

void Pools_InitializeGameplayCamera(GameplayCamera *camera);

extern void Camera_UpdateViewProjectionAndEffects(void *);

/* Updates each of the group's items (count at 0x8, 0xED8-byte records from the address at 0x4) through
   the block at 0x570 of each, then the group's own block at 0x5B0, all with Pool_InitEntryPool_SkyPosttargetedscreenmessage. */


extern void Pool_InitEntryPool(char *);

void Pools_ResetPlayers(ScreenMessageOwner *actor) {
    char *parts;

    XPlus_FillMemory(actor, 0, 4616);
    List_InitializeIntrusive(&actor->header.active, 0, 4);
    List_InitializeIntrusive(&actor->header.views, 0, 4);
    List_InitializeIntrusive(&actor->activeMessages, 0, 4);
    parts = (char *)&actor->self;
    actor->state = 1;
    actor->header.allocation = 0;
    actor->header.cameras = 0;
    actor->header.count = 0;
    actor->storage.allocation = 0;
    actor->storage.first = 0;
    actor->storage.count = 0;
    actor->header.layoutTimer = 2;
    Pools_InitializeGameplayCamera(parts);
    Camera_UpdateViewProjectionAndEffects(parts);
}

void Pools_InitGroupPools(Triple *group) {
    int i;

    for (i = 0; i < group->z; i++) {
        Pool_InitEntryPool((char *)(i * 3800 + group->y + 1392));
    }
    Pool_InitEntryPool((char *)&((ScreenMessageOwner *)group)->self.sceneEffects);
}

/* Detaches the object at offset 0xC of an owner: when there is one, finalises it through
   Pools_InitializeGameplayCamera and removes it from the lists at offsets 0xC and 0x20 through List_RemoveIntrusive and
   List_AppendIntrusive. Returns the object. */



/* Calls List_RemoveIntrusive on offset 0x20 of an object and List_PrependIntrusive on offset 0xC with the second
   argument. */



void *Pools_RecycleModel(struct Draw *owner) {
    void *object = owner->model;

    if (object != 0) {
        Pools_InitializeGameplayCamera(object);
        List_RemoveIntrusive(&owner->model, object);
        List_AppendIntrusive(&owner->recycled, object);
    }
    return object;
}

void Pools_TransferPoolEntry(char *object, void *value) {
    List_RemoveIntrusive(&((struct Draw *)object)->recycled, value);
    List_PrependIntrusive(&((struct Draw *)object)->model, value);
}
