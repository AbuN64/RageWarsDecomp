#include "COMMON/VIEWFLAGS.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/LONE/SCREEN_MESSAGE_ALLOCATION_LABEL.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/GAMEPLAY_MOVEMENT.H"
#include "COMMON/WORLD.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "CAMERA/GSKY_GETFLOORSURFACESHAKE.H"
#include "UI/X_FILES/X_PLUS.H"
#include "ENGINE/AUDIO/T2SOUNDELEMENT/SOUND_CONTEXT_CONTROL.H"
#include "ENGINE/GREGION.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"

/* 80233920_31.CPP */
/* Produces a random shake offset for an object: looks up the object's model entry in g_world_AchieveUpdateresultsscreen and
 * zeroes the offset when there is none; otherwise eases the horizontal and vertical shake amplitudes
 * at 0xF4 and 0xF8 toward the pair k_floorShakeTargetHorizontal when the entry is flagged 0x10000 (toward zero when not)
 * and draws each offset component at random within the scaled amplitudes. */





extern void **Cache_AllocateResource(s32, s32, s32, char *);



extern void Cache_DrainAndCompactResources(s32 a);

void Gsky_GetFloorSurfaceShake(void *gameplayCamera, CVector3 *out) {
    GameplayCamera *o = gameplayCamera;
    f32 value;
    Shared_Surface *entry;
    f32 targetX;
    f32 targetY;
    f32 scale;

    targetY = 0.0f;
    targetX = targetY;
    entry = Scene_GetModelRecordByIndexPointer(&g_world, (u16 *)o->floorPoly);
    if (entry == 0) {
        out->x = targetY;
        out->y = targetY;
        out->z = targetY;
        return;
    }
    if (entry->flags & 0x10000) {
        targetX = k_floorShakeTargetHorizontal;
        targetY = k_floorShakeTargetVertical;
    }
    value = o->shakeHorizontal + (targetX - o->shakeHorizontal) * k_floorShakeHorizontalBlend.value;
    scale = k_floorShakeHorizontalScale.value;
    o->shakeHorizontal = value;
    o->shakeVertical += (targetY - o->shakeVertical) * k_floorShakeVerticalBlend.value;
    out->x = Graphu64_RandomBetween(-o->shakeHorizontal * scale, o->shakeHorizontal * scale);
    out->y = Graphu64_RandomBetween(0.0f, o->shakeVertical * k_floorShakeVerticalScale.value);
    value = -o->shakeHorizontal * scale;
    out->z = Graphu64_RandomBetween(value, o->shakeHorizontal * scale);
}

/** Preserve the empty hook at VRAM 0x80239FBC. */
void Gsky_FloorSurfaceNoOp(void) {
}

void Gsky_DrawViewportEffectNoOp(void) {
}

void Gsky_UpdateFloorSurface(void *gameplayCamera) {
    s32 object;
    GameplayCamera *camera = gameplayCamera;
    f32 value;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    if (Cinema_IsSequenceInWindow() != 0) {
        camera->floorPoly = (CameraFloorSurfaceView *)Scene_FindFloorPolygon(&g_world, &camera->floorSampleX);
    }
    object = (s32)camera->floorPoly;
    x = camera->floorSampleX;
    y = camera->floorSampleY;
    z = camera->floorSampleZ;
    w = camera->floorHeightOffset;
    camera->floorSurface = g_defaultCameraSurfaceType;
    if (object != 0 && Cinema_IsSequenceInWindow() == 0) {
        value = ((y + w) - Region_GetPolygonHeight(object, x, z)) * k_floorSurfaceDistanceScale;
        if (value < k_floorSurfaceUpperDistance && k_floorSurfaceLowerDistance < value) {
            CameraFloorSurfaceView *surface = (CameraFloorSurfaceView *)object;
            camera->floorSurface = surface->surfaceType;
        }
    }
    if (Cinema_IsSequenceInWindow() != 0) {
        camera->floorSurface = g_defaultCameraSurfaceType;
    }
    if (camera->zoomBlend > 0.0f) {
        camera->floorSurface = g_defaultCameraSurfaceType;
    }
}

void Gsky_AllocateMessageBuffer(void *messageBuffer, s32 count) {
    MessageBuffer *buffer = messageBuffer;
    s32 *allocation;
    s32 bytes;
    s32 firstBlock;

    bytes = count * 3800;
    buffer->count = count;
    allocation = Cache_AllocateResource(0, bytes, 35, (char *)&g_messageBufferAllocationLabelStorage + 4);
    buffer->allocation = allocation;
    firstBlock = *allocation;
    buffer->first = firstBlock;
    XPlus_FillMemory(firstBlock, 0, bytes);
}

void Gsky_AllocateScreenMessageStorage(void *screenMessageOwner, int count) {
    struct ScreenMessageOwner *owner = screenMessageOwner;
    int *allocation;
    int bytes;
    int firstBlock;
    bytes = count << 6;
    owner->storage.count = count;
    allocation = Cache_AllocateResource(0, bytes, 35, &g_screenMessageAllocationLabel);
    owner->storage.allocation = allocation;
    firstBlock = *allocation;
    owner->storage.first = firstBlock;
    XPlus_FillMemory(firstBlock, 0, bytes);
}

void Gsky_ReleaseScreenMessageRendering(struct ScreenMessageOwner *owner) {
    s32 allocation;

    owner->state = 1;
    SoundElement_SetListenerCamera((intptr_t)&owner->self);
    Cache_DrainAndCompactResources(0);
    allocation = owner->header.allocation;
    if (allocation != 0) {
        Cache_ReleaseResource(0, allocation);
        owner->header.allocation = 0;
        owner->header.cameras = 0;
        owner->header.count = 0;
    }
}

/* 80233920_32.CPP */
void Gsky_ReleaseMessageBuffer(void *bufferOwner) {
    s32 allocationHandle;
    Cache_DrainAndCompactResources(0);
    allocationHandle = (s32)(((struct ScreenMessageOwner *) ((s8 *) bufferOwner))->storage.allocation);
    if (allocationHandle != 0) {
        Cache_ReleaseResource(0, allocationHandle);
        (((struct ScreenMessageOwner *) ((s8 *) bufferOwner))->storage.allocation) = 0;
        (((struct ScreenMessageOwner *) ((s8 *) bufferOwner))->storage.first) = 0;
        (((struct ScreenMessageOwner *) ((s8 *) bufferOwner))->storage.count) = 0;
    }
}
