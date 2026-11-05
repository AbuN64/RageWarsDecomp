#include "Common/gameplay_camera.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/world.h"
#include "Common/sharedplayer.h"
#include "Common/viewflags.h"
#include "types.h"
#include "Engine/gregion.h"
#include "Gsky/gsky_setplayerviewinputs.h"
#include "Cinema/cinema.h"
#include "Camera/fade_and_color_blend_views.h"
#include "Gsky/gsky_copyobjectposition.h"
#include "Gsky/gsky_setgameplaymode.h"
#include "Camera/camera_address_symbols.h"
#include "Common/triple.h"
#include "Common/vector4f.h"
#include "Camera/gsky_resetheadbob.h"
#include "Camera/gsky.h"
#include "Common/shared_gameslot.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Common/aiprofile.h"
#include "Gsky/gsky_projecttoscreen.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Gsky/gsky_findscreenmessage.h"
#include "Engine/visdata_decoderegiongrid.h"
#include "Gsky/gsky_containsvisiblepoint.h"
#include "Engine/Audio/channel.h"
#include "Common/output.h"
#include <platform_sdk.h>
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/sessionhandlerrow.h"
#include <PR/gbi.h>
#include "Gsky/gsky_loadprojectionmatrix.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/menu_match_globals.h"
#include "Common/heap_arena_entry.h"
#include "Engine/Cache/list.h"
#include "Common/sky_layers.h"
#include "Gsky/sky_postscaledscreenmessage.h"
#include "Common/ballisticparams.h"
#include "Common/screenmessagesubstitution.h"
#include "Gsky/sky_posttargetedscreenmessage.h"
#include "Pool/pool.h"
#include "Weaponshake/weaponshake.h"
#include "Common/cache_releaseresource.h"
#include "Common/Lone/screen_message_allocation_label.h"
#include "Common/gameplay_movement.h"
#include "Camera/gsky_getfloorsurfaceshake.h"
#include "Ui/X_files/x_plus.h"
#include "Engine/Audio/T2soundelement/sound_context_control.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Common/cache_allocateresource.h"
#include "Cache/cache_allocateresourceat.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Sched/sky_postscreenmessage.h"
#include "Common/shared_particleinstance.h"
#include "Common/weapon_screen_message_operations.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Common/lens_flare.h"
#include "Gsky/sky_drawlensflare.h"

/* Stores its parameters into the camera's view-input fields, then refreshes the camera's ground reference and picks its surface value from the ground under it. */

void Gsky_SetPlayerViewInputs(GameplayCamera *camera, s32 bobSuppression, f32 lensFlareInputOne, f32 lensFlareInputTwo, f32 lensFlareInputThree, f32 lensFlareInputFour, f32 floorSampleX,
                   f32 floorSampleY, f32 floorSampleZ, f32 floorHeightOffset, Shared_Quad floorSampleData, s32 floorPolygon, f32 requestedZoomBlend,
                   f32 requestedZoomFov) {
    s32 object;
    f32 value;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    camera->bobSuppressed = bobSuppression;
    camera->lensFlareInputOne = lensFlareInputOne;
    camera->lensFlareInputTwo = lensFlareInputTwo;
    camera->lensFlareInputThree = lensFlareInputThree;
    camera->lensFlareInputFour = lensFlareInputFour;
    camera->floorSampleX = floorSampleX;
    camera->floorSampleY = floorSampleY;
    camera->floorSampleZ = floorSampleZ;
    camera->floorHeightOffset = floorHeightOffset;
    camera->floorSampleData = floorSampleData;
    camera->floorPoly = (void *)floorPolygon;
    camera->zoomBlend = requestedZoomBlend;
    camera->zoomFov = requestedZoomFov;
    if (Cinema_IsSequenceInWindow() != 0) {
        camera->floorPoly = (void *)Scene_FindFloorPolygon(&g_world, &camera->floorSampleX);
    }
    object = (s32)camera->floorPoly;
    x = camera->floorSampleX;
    y = camera->floorSampleY;
    z = camera->floorSampleZ;
    w = camera->floorHeightOffset;
    camera->floorSurface = g_defaultCameraSurfaceType;
    if (object != 0 && Cinema_IsSequenceInWindow() == 0) {
        value = ((y + w) - Region_GetPolygonHeight(object, x, z)) * k_cameraInputSurfaceDistanceScale;
        if (value < k_cameraInputSurfaceUpperDistance && k_cameraInputSurfaceLowerDistance < value) {
            camera->floorSurface = ((MenuRules *)(object))->locked;
        }
    }
    if (Cinema_IsSequenceInWindow() != 0) {
        camera->floorSurface = g_defaultCameraSurfaceType;
    }
    if (camera->zoomBlend > 0.0f) {
        camera->floorSurface = g_defaultCameraSurfaceType;
    }
}

/** Copy the three-word vector at source offset 0x260. */
void *Gsky_CopyObjectPosition(void *destination, void *source) {
    GameplayCamera *camera = source;

    CVector3 *out = destination;
    *out =
        camera->corners[0];
    return destination;
}

#include "Common/funcptr.h"

void Gsky_SetGameplayMode(void *gameplayCamera, s16 requestedMode) {
    FuncPtr fn;

    ((GameplayCamera *)gameplayCamera)->mode = requestedMode;
    ((GameplayCamera *)gameplayCamera)->elapsed = 0;
    ((GameplayCamera *)gameplayCamera)->state = 0;
    ((GameplayCamera *)gameplayCamera)->stateCounter = 0;
    fn = g_cameraGameplayModeCallbacks[((GameplayCamera *)gameplayCamera)->mode][0];
    if (fn != 0) {
        ((void (*)(void *))fn)(gameplayCamera);
    }
}

void Gsky_ResetHeadBob(GameplayCamera *camera) {
    if (camera != 0) {
        f32 f0 = k_cameraInitialBobAmplitudeX;
        f32 f1 = k_cameraInitialBobAmplitudeY;
        f32 f2 = k_cameraInitialBobRateX;
        f32 f3 = k_cameraInitialBobRateY[0];

        camera->bobPhaseX = 0;
        camera->bobPhaseY = 0;
        camera->bobAmplitudeX = f0;
        camera->bobAmplitudeY = f1;
        camera->bobRateX = f2;
        camera->bobRateY = f3;
    }
}

void Gsky_HeadBobInitializeNoOp(void) {
}

void Gsky_HeadBobUpdateNoOp(void) {
}

void Gsky_SetDamageEffect(GameplayCamera *racer, signed char effectMode, signed char delay) {
    if (racer != 0) {
        racer->damageEffectMode = effectMode;
        racer->damageEffectDelay = delay;
    }
}

/* The native ABI receives full words. Narrowing happens at the byte stores,
 * so callers may pass values such as 0x80 and 0xFF without sign extension. */
void Gsky_StartFade(void *camera, s32 requestedFadeMode, s32 startValue, s32 endValue, s32 stepAmount, s32 redChannel, s32 greenChannel, s32 blueChannel)
{
 do { if (camera != 0) { ((GameplayCamera *)camera)->fadeStep = (s8) stepAmount; ((GameplayCamera *)camera)->fadeMode = requestedFadeMode; ((GameplayCamera *)camera)->fadeStart = startValue; ((GameplayCamera *)camera)->fadeEnd = endValue; ((GameplayCamera *)camera)->fadeState = 0; ((GameplayCamera *)camera)->fadeRed = (s8) redChannel; ((GameplayCamera *)camera)->fadeGreen = (s8) greenChannel; ((GameplayCamera *)camera)->fadeBlue = (s8) blueChannel; ((GameplayCamera *)camera)->fadeCounter = 0; ((GameplayCamera *)camera)->fadeEnabled = 1; } } while (0);
}

#define g_gameSettingsView (*(s32 *)&g_gameSettings)

void Gsky_GetMaskedEffectColor(ThreeChannels *threeChannels, s8 *red, s8 *green, s8 *blue) {
    if (g_gameSettingsView & 0x4000) {
        *red = 0;
        *green = 0;
        *blue = 0;
        return;
    }
    *red = threeChannels->first & 0xF8;
    *green = threeChannels->second & 0xF8;
    *blue = threeChannels->third & 0xF8;
}

void Gsky_ProjectToScreen(s32 view, s32 point, f32 *screenX, f32 *screenY) {
    CVector3 value;
    f32 half;

    Graphu64_ProjectPoint(view + 480, point, &value);
    half = (f32)(g_hudReferenceViewportWidth / 2);
    *screenX = value.x * half + half;
    *screenY = value.y * (f32)(-g_hudReferenceViewportHeight / 2) +
            (f32)(g_hudReferenceViewportHeight / 2);
}

void *Gsky_FindScreenMessage(int messageId) {
    Player *node = g_transientPlayerList.actorList;
    if (node != 0) {
        do {
            if ((s32)node->camera == messageId) {
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

/* Configures an emitter: stores a position vector, a shared value in three channels, a scale, and three rates converted by the constant in k_cameraInitialBobRateY. */


static inline void Camera_InitShakeEmitter(ShakeEmitterChannelView *obj, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos)
{
    obj->position = pos;
    obj->scale = scale;
    obj->firstValue = value;
    obj->firstRate = a;
    obj->secondValue = value;
    obj->secondRate = b;
    obj->thirdValue = value;
    obj->thirdRate = c;
}

void Gsky_StartScaledShake(ShakeEmitterChannelView *obj, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos)
{
    if (obj != 0) {
        f32 k = k_cameraInitialBobRateY[1];
        Camera_InitShakeEmitter(obj, a * k, b * k, c * k, scale, value, pos);
    }
}

s32 Gsky_ContainsVisiblePoint(s32 cameraAddress, Triple testPoint) {
    return Visdata_ContainsPoint((char *)&((GameplayCamera *)cameraAddress)->clipPlanes, &testPoint);
}

/** Resets every fade parameter of the camera. */
void Gsky_ResetFadeState(void *cameraStorage) {
    GameplayCamera *state = cameraStorage;
    float value = k_cameraFadeResetValue[0];
    state->fadeParameterMode = 0;
    state->fadeParameterState = 0;
    state->fadeParameterOne = 0;
    state->fadeParameterTwo = 0;
    state->fadeParameterThree = 0;
    state->fadeParameterFour = 0;
    state->fadeScalarOne = value;
    state->fadeScalarTwo = value;
}

/** Perform the no-op hook. */
void Gsky_ViewportUpdateNoOp(void) {
}

/** Clears the contact value and enables the fade-mode flag. */
void Gsky_StartFadeModeOne(char *object) {
    struct CCollisionResults *output = (void *)object;
    output->contactValue = 0;
    output->typeFC = 1;
}

int Gsky_StartFadeModeTwo(void *outputStorage) {
    struct CCollisionResults *output = (void *)outputStorage;
    output->contactValue = 0;
    output->typeFC = 2;
    return 2;
}

/* Loads the camera's double-buffered HUD projection matrix for the current frame buffer. */
void Gsky_LoadProjectionMatrix(u32 cameraAddress) {
    GameplayCamera *camera = (GameplayCamera *)cameraAddress;
    gSPMatrix(g_displayListCursor++, (u32)camera->hudProjection[g_lightingBufferIndex], G_MTX_LOAD | G_MTX_PROJECTION);
}

f32 Gsky_GetDistanceTo(void *gameplayCamera, CVector3 *targetPosition) {
    CVector3 delta;
    GameplayCamera *camera = gameplayCamera;
    Graphu64_SubtractVectors(&delta, &camera->position, targetPosition);
    return Gu_Sqrtf((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
}

/** Perform no work for its callers. */
void Gsky_DrawPlayerListNoOp(void) {
}

/* Spawns an emitter record: takes the head of the free emitter list into the active emitter list (or reuses the spare record when none is free) and fills its position, scale, shared value and three rates converted by k_cameraFadeResetValue. */


static inline void Camera_InitShakeNode(CShake *node, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos)
{
    node->m_vPos = pos;
    node->m_Radius = scale;
    node->x.mode = value;
    node->x.value = a;
    node->y.mode = value;
    node->y.value = b;
    node->z.mode = value;
    node->z.value = c;
}

/* Posts a text as on-screen messages, one per line: the text (or g_screenMessageSubstitutionReplacement when given g_screenMessageSubstitutionSource) is split
 * at newlines and for each non-empty line the oldest message node of the owner's free message list is recycled
 * (cleared through Gsky_ClearScreenMessage, unlinked, and appended to the active message list of the camera) and set up
 * as a kind 2 message centred horizontally 80 pixels above the bottom of the screen, scaled by the given
 * size. Returns the last message node. */



static inline CCameraText *Camera_RecycleOldestMessage(void *owner, void *pool) {
    CCameraText *oldest;

    oldest = ((struct ScreenMessageOwner *)owner)->activeMessages.head;
    if (oldest != 0) {
        Gsky_ClearScreenMessage(oldest);
        List_RemoveIntrusive(&((struct ScreenMessageOwner *)owner)->activeMessages, oldest);
        List_AppendIntrusive(&((struct GameplayCamera *)pool)->objects, oldest);
    }
    return oldest;
}

static inline CCameraText *Camera_PostMessageLines(void *owner, void *pool, u8 *text, s32 kind, f32 size, s32 target) {
    CCameraText *message;
    s32 height;
    u8 *line;
    u8 *p;

    message = 0;
    if (pool == 0) {
        return message;
    }
    if (text == g_screenMessageSubstitutionSource) {
        text = (u8 *)g_screenMessageSubstitutionReplacement;
    }
    p = text;
    line = p;
    while (*p != 0) {
        p++;
        if (*p == '\n' || *p == 0) {
            if (line != p) {
                message = Camera_RecycleOldestMessage(owner, pool);
                if (message != 0) {
                    s32 half = g_hudReferenceViewportWidth / 2;
                    message->kind = kind;
                    message->text = line;
                    message->m_nAlpha = 0;
                    message->alpha = 1.0f;
                    message->target = target;
                    message->forceScaledText = 0;
                    message->m_ModeTime = 0;
                    message->postResetWord = 0;
                    message->m_XScale = 1.0f;
                    message->m_YScale = 1.0f;
                    height = g_hudReferenceViewportHeight;
                    message->x = half;
                    message->y = height - 80;
                    message->m_DisplayTime = size * 15.0f;
                }
                line = p + 1;
            }
        }
    }
    return message;
}

void Gsky_StartEmitter(char *obj, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos)
{
    ScreenMessageOwner *state = (void *)obj;
    CShake *node = state->freeEffects.head;
    f32 k;

    if (node != 0) {
        List_RemoveIntrusive(&state->freeEffects, node);
        List_PrependIntrusive(&state->activeEffects, node);
    } else {
        node = state->activeEffects.tail;
    }
    k = k_cameraFadeResetValue[1];
    Camera_InitShakeNode(node, a * k, b * k, c * k, scale, value, pos);
}

void *Gsky_FindNearestCamera(MenuMatchGlobals *menuMatchGlobals, CVector3 *zero) {
    CVector3 position;
    GameplayCamera *node;
    void *bestNode;
    f32 bestDist;
    f32 distSq;

    Graphu64_LimitVectorLength(&zero->x, 20000.0f);
    if (menuMatchGlobals->useFallbackCamera != 0) {
        return &menuMatchGlobals->fallbackCamera;
    }
    node = menuMatchGlobals->cameras;
    bestDist = k_screenMessageInitialNearestDistance;
    bestNode = 0;
    if (node != 0) {
        do {
            Graphu64_SubtractVectors(&position, zero, &node->position);
            distSq = (position.x * position.x) +
                     (position.y * position.y) +
                     (position.z * position.z);
            if (distSq < bestDist) {
                bestNode = node;
                bestDist = distSq;
            }
            node = node->next;
        } while (node != 0);
    }
    if (bestNode == 0) {
        return &menuMatchGlobals->fallbackCamera;
    }
    return bestNode;
}

f32 Gsky_GetMeanViewDistance(ScreenMessageOwner *viewOwner, void *targetPosition) {
    CVector3 position;
    f32 sum;
    GameplayCamera *node;
    f64 divisor;
    s32 count;

    if (viewOwner->header.views.count == 0) {
        return 0.0f;
    }
    node = viewOwner->header.views.head;
    sum = 0.0f;
    if (node != 0) {
        do {
            Graphu64_SubtractVectors(&position, &((GameplayCamera *)node)->position, targetPosition);
            sum += Gu_Sqrtf(
                (position.x * position.x) +
                (position.y * position.y) +
                (position.z * position.z));
            node = node->next;
        } while (node != 0);
    }
    count = viewOwner->header.views.count;
    divisor = (f64)count;
    if (count < 0) {
        divisor += k_screenMessageScaleDivisorStep;
    }
    return sum / (f32)divisor;
}

void *Gsky_PostFlaggedScreenMessage(struct ScreenMessageOwner *owner, struct GameplayCamera *pool, u8 *text) {
    struct CCameraText_t *message = Camera_PostScreenMessage(owner, pool, text);
    if (message != 0) {
        message->forceScaledText = 1;
    }
    return message;
}

CCameraText *Gsky_PostScaledScreenMessage(void *owner, void *pool, u8 *text, f32 size) {
    return Camera_PostMessageLines(owner, pool, text, 2, size, -1);
}

/* Posts a text as on-screen messages for a target: the target's messages still in the pool's message list
 * are unlinked and returned to the owner's free message list, then the text (or g_screenMessageSubstitutionReplacement when given g_screenMessageSubstitutionSource)
 * is split at newlines and for each non-empty line the oldest message node of the owner's list is recycled
 * and set up as a kind 2 message for the target, centred horizontally 80 pixels above the bottom of the
 * screen and scaled by the given size. Returns the last message node. */




static inline CCameraText *Camera_PostTargetedMessageLines(void *owner, void *pool, u8 *text, s32 kind, f32 size, s32 target) {
    CCameraText *message;
    s32 height;
    u8 *line;
    u8 *p;

    message = 0;
    if (pool == 0) {
        return message;
    }
    if (text == g_screenMessageSubstitutionSource) {
        text = (u8 *)g_screenMessageSubstitutionReplacement;
    }
    p = text;
    line = p;
    while (*p != 0) {
        p++;
        if (*p == '\n' || *p == 0) {
            if (line != p) {
                message = Camera_RecycleOldestMessage(owner, pool);
                if (message != 0) {
                    message->kind = kind;
                    message->text = line;
                    message->m_nAlpha = 0;
                    message->alpha = 1.0f;
                    message->target = target;
                    message->forceScaledText = 0;
                    message->m_ModeTime = 0;
                    message->postResetWord = 0;
                    message->m_XScale = 1.0f;
                    message->m_YScale = 1.0f;
                    height = g_hudReferenceViewportHeight;
                    message->x = g_hudReferenceViewportWidth / 2;
                    message->y = height - 80;
                    message->m_DisplayTime = size * 15.0f;
                }
                line = p + 1;
            }
        }
    }
    return message;
}

CCameraText *Gsky_PostTargetedScreenMessage(void *owner, void *pool, u8 *text, s32 target, f32 size) {
    CCameraText *pending;
    CCameraText *next;

    if (pool == 0) {
        return 0;
    }
    for (pending = ((struct GameplayCamera *)pool)->objects.head; pending != 0; pending = next) {
        next = pending->next;
        if (pending->target == target) {
            List_RemoveIntrusive(&((struct GameplayCamera *)pool)->objects, pending);
            List_PrependIntrusive(&((struct ScreenMessageOwner *)owner)->activeMessages, pending);
        }
    }
    pending = Camera_PostTargetedMessageLines(owner, pool, text, 2, size, target);
    return pending;
}

/* Starting at the tail follows prev (+0), preserving order when prepending. */
void Gsky_ActivateMessagePool(struct ScreenMessageOwner *owner, struct GameplayCamera *pool) {
    CCameraText *message;
    CCameraText *nextMessage;
    void *activeList;

    if (pool != 0) {
        message = pool->objects.tail;
        activeList = &pool->objects;
        if (message != 0) {
            do {
                nextMessage = message->prev;
                List_RemoveIntrusive(activeList, message);
                List_PrependIntrusive(&owner->activeMessages, message);
                message = nextMessage;
                activeList = &pool->objects;
            } while (message != 0);
        }
    }
}

void Gsky_ActivateAllMessagePools(s32 messageOwner) {
    CCameraText *next;
    CCameraText *nextPooledMessage;
    CCameraText *embeddedMessage;
    CCameraText *pooledMessage;
    void *embeddedPool;
    void *poolCursor;

    embeddedPool = (void *)(messageOwner + 64);
    if (embeddedPool != 0) {
        embeddedMessage = ((struct GameplayCamera *)embeddedPool)->objects.tail;
        if (embeddedMessage != 0) {
            do {
                next = embeddedMessage->prev;
                List_RemoveIntrusive(&((struct GameplayCamera *)embeddedPool)->objects, embeddedMessage);
                List_PrependIntrusive(&((struct ScreenMessageOwner *)messageOwner)->activeMessages, embeddedMessage);
                embeddedMessage = next;
            } while (embeddedMessage != 0);
        }
    }

    poolCursor = g_gameplayCameraList.camera;
    if (poolCursor != 0) {
        do {
            pooledMessage = ((struct GameplayCamera *)poolCursor)->objects.tail;
            if (pooledMessage != 0) {
                do {
                    nextPooledMessage = pooledMessage->prev;
                    List_RemoveIntrusive(&((struct GameplayCamera *)poolCursor)->objects, pooledMessage);
                    List_PrependIntrusive(&((struct ScreenMessageOwner *)messageOwner)->activeMessages, pooledMessage);
                    pooledMessage = nextPooledMessage;
                } while (pooledMessage != 0);
            }
            poolCursor = ((struct GameplayCamera *)poolCursor)->next;
        } while (poolCursor != 0);
    }
}

/** Initializes the screen message entry pool held in the scene effects of the gameplay camera at the given address. */
void Gsky_InitializeMessageEntryPool(int viewAddress) {
    Pool_InitEntryPool((char *)&((GameplayCamera *)viewAddress)->sceneEffects);
}

void *Gsky_RecycleFirstScreenMessage(void *screenMessageOwner, struct GameplayCamera *screenMessagePool) {
    struct ScreenMessageOwner *owner = screenMessageOwner;
    struct GameplayCamera *pool = screenMessagePool;
    CCameraText *message;

    message = owner->activeMessages.head;
    if (message != 0) {
        Gsky_ClearScreenMessage(message);
        List_RemoveIntrusive(&owner->activeMessages, message);
        List_AppendIntrusive(&pool->objects, message);
    }
    return message;
}

void Gsky_ActivateScreenMessage(s32 destinationOwner, s32 sourcePool, s32 messageNode) {
    List_RemoveIntrusive(&((GameplayCamera *)sourcePool)->objects, messageNode);
    List_PrependIntrusive(&((ScreenMessageOwner *)destinationOwner)->activeMessages, messageNode);
}

void Gsky_ClearScreenMessage(void *screenMessage) {
    struct CCameraText_t *message = screenMessage;
    message->kind = 0;
    message->target = 0;
}

/** Clears the level and the three state words of a shake channel. */
void Gsky_InitializeShakeChannel(void *channelStorage) {
    struct Channel *channel = channelStorage;
    channel->level = 0.0f;
    channel->state[0] = 0;
    channel->state[1] = 0;
    channel->state[2] = 0;
}

/** Stores the float argument scaled by k_screenMessageWaveLevelScale as the channel's level and the int argument as its mode. */
void Gsky_SetShakeChannel(struct Channel *channel, float inputLevel, int waveMode) {
    channel->level = inputLevel * (k_screenMessageWaveLevelScale);
    channel->mode = waveMode;
}

/* Evaluates a wave: kind 1 returns Gu_Sinf_SkyPosttargetedscreenmessage of the wave phase scaled by k_screenMessageWavePhaseScale, times
   the wave amplitude; kind 0 returns Graphu64_RandomBetween over minus to plus the amplitude; any other
   kind returns zero. */
f32 Gsky_SampleShakeWave(struct Wave *wave) {
    switch (wave->kind) {
    case 1:
        return Gu_Sinf(wave->phase * k_screenMessageWavePhaseScale) * wave->amplitude;
    case 0:
        return Graphu64_RandomBetween(-wave->amplitude, wave->amplitude);
    }
    return 0.0f;
}

/** Zero the object's vector fields and reset the scale field to the default. */
void Gsky_InitializeShakeRecord(void *channelRecord) {
    struct CameraShakeRecordView *o = channelRecord;
    struct Channel *channel0;
    struct Channel *channel1;
    struct Channel *channel2;
    f32 diag;

    diag = k_screenMessageWaveDefault;
    channel0 = &o->channels[0];
    o->triple.x = 0;
    o->triple.y = 0;
    o->triple.z = 0;
    o->value = diag;
    channel0->level = 0;
    channel0->state[0] = 0;
    channel0->state[1] = 0;
    channel0->state[2] = 0;
    channel1 = &o->channels[1];
    channel2 = &o->channels[2];
    channel1->level = 0;
    channel1->state[0] = 0;
    channel1->state[1] = 0;
    channel1->state[2] = 0;
    channel2->level = 0;
    channel2->state[0] = 0;
    channel2->state[1] = 0;
    channel2->state[2] = 0;
}

/* Configures a shake record: stores the triple and the value, and gives each of its three channels the same
   mode and a level scaled by k_screenMessageChannelLevelScale. */

void Gsky_SetShakeRecord(struct CameraShakeRecordView *record, f32 first, f32 second, f32 third, f32 value, s32 mode,
                   Triple triple) {
    record->triple = triple;
    record->value = value;
    record->channels[0].mode = mode;
    record->channels[1].mode = mode;
    record->channels[2].mode = mode;
    record->channels[0].level = first * k_screenMessageChannelLevelScale;
    record->channels[1].level = second * k_screenMessageChannelLevelScale;
    record->channels[2].level = third * k_screenMessageChannelLevelScale;
}

s32 Gsky_UpdateShakeRecord(s32 waveRecord) {
    s32 result;
    u32 secondChannelDone;
    u32 firstChannelDone;
    u32 thirdChannelDone;

    firstChannelDone = Weapon_UpdateShakeAxis(waveRecord + 24);
    secondChannelDone = Weapon_UpdateShakeAxis(waveRecord + 44);
    thirdChannelDone = Weapon_UpdateShakeAxis(waveRecord + 64);
    result = 0;
    if ((firstChannelDone != 0) && (secondChannelDone != 0)) {
        result = thirdChannelDone > 0U;
    }
    return result;
}

/* Produces a random shake offset for an object: looks up the object's model entry in g_world_AchieveUpdateresultsscreen and
 * zeroes the offset when there is none; otherwise eases the horizontal and vertical shake amplitudes
 * toward the pair k_floorShakeTargetHorizontal when the entry is flagged as shaking (toward zero when not)
 * and draws each offset component at random within the scaled amplitudes. */
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

/** Preserve the empty hook. */
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
    allocation = Cache_AllocateResource(0, bytes, 35, g_messageBufferAllocationLabel);
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



f32 Gsky_StepValueTowardTarget(s32 stepContext, f32 value, f32 target, f32 step) {
    if (Control_IsSnapshotActive() != 0) {
        value = target;
    }
    if (value < target) {
        value += step;
        g_cameraFramingTransitionTimer = k_screenMessageValueIncreaseMarker;
        if (target < value) {
            value = target;
        }
    } else if (target < value) {
        value -= step;
        g_cameraFramingTransitionTimer = k_screenMessageValueDecreaseMarker;
        if (value < target) {
            value = target;
        }
    }
    return value;
}

/* Posts a text as on-screen messages, one per line, with the given kind, target and size: the text (or
 * g_screenMessageSubstitutionReplacement when given g_screenMessageSubstitutionSource) is split at newlines and for each non-empty line the oldest message node
 * of the owner's free message list is recycled (cleared through Gsky_ClearScreenMessage, unlinked, and appended to the active
 * message message list of the camera) and set up as a message centred horizontally 80 pixels above the bottom of the
 * screen, scaled by the given size. Returns the last message node. */



static inline CCameraText *Camera_RecycleOldestScreenMessage(void *owner, void *pool) {
    struct ScreenMessageOwner *messageOwner = owner;
    struct GameplayCamera *messagePool = pool;
    CCameraText *oldest;

    oldest = messageOwner->activeMessages.head;
    if (oldest != 0) {
        Gsky_ClearScreenMessage(oldest);
        List_RemoveIntrusive(&messageOwner->activeMessages, oldest);
        List_AppendIntrusive(&messagePool->objects, oldest);
    }
    return oldest;
}

CCameraText *Sky_PostScreenMessage(void *owner, void *pool, u8 *text, s32 kind, f32 size, s32 target) {
    CCameraText *message;
    u8 *line;
    u8 *p;
    s32 height;

    message = 0;
    if (pool == 0) {
        return message;
    }
    if (text == g_screenMessageSubstitutionSource) {
        text = (u8 *)g_screenMessageSubstitutionReplacement;
    }
    p = text;
    line = p;
    while (*p != 0) {
        p++;
        if (*p == '\n' || *p == 0) {
            if (line != p) {
                message = Camera_RecycleOldestScreenMessage(owner, pool);
                if (message != 0) {
                    message->kind = kind;
                    message->text = line;
                    message->m_nAlpha = 0;
                    message->alpha = 1.0f;
                    message->target = target;
                    message->forceScaledText = 0;
                    message->m_ModeTime = 0;
                    message->postResetWord = 0;
                    message->m_XScale = 1.0f;
                    message->m_YScale = 1.0f;
                    height = g_hudReferenceViewportHeight;
                    message->x = g_hudReferenceViewportWidth / 2;
                    message->y = height - 80;
                    message->m_DisplayTime = size * 15.0f;
                }
                line = p + 1;
            }
        }
    }
    return message;
}

/* Clears effect state and initializes its scalar, vector and resource defaults. */
void Sky_InitializeLensFlareState(LensFlareEffectState *effectState) {
    f32 zeroValue;
    CVector3 *vectorDefaults;

    effectState->initialScalar.i = 0;
    zeroValue = effectState->initialScalar.f;
    effectState->enabled = 1;
    vectorDefaults = &effectState->v;
    effectState->stateWordOne = 0;
    effectState->stateWordTwo = 0;
    effectState->stateWordThree = 0;
    effectState->stateWordFour = 0;
    effectState->stateWordFive = 0;
    effectState->stateWordSix = 0;
    effectState->stateWordSeven = 0;
    vectorDefaults->z = zeroValue;
    vectorDefaults->y = zeroValue;
    effectState->v.x = zeroValue;
    effectState->scale = 1.0f;
    effectState->stateWordEight = 0;
    effectState->scalarOffset = zeroValue;
    effectState->defaultAngle = 0.174532949924469f;
    effectState->defaultStateValue = g_defaultCameraSurfaceType;
}

/* 80238670.CPP */
extern s32 g_hudReferenceViewportWidth;
extern Gfx *g_displayListCursor;
extern f32 Gu_Sqrtf(f32);
void Sky_DrawLensFlare(ClipView *actor, f32 x, f32 y, f32 intensity, s32 special, s32 flareFlags) {
    FlareRadii radii = *(const FlareRadii *)k_lensFlareRadii;
    FlareAlphas alphas = *(const FlareAlphas *)k_lensFlareAlphas;
    FlareColors colors = *(const FlareColors *)k_lensFlareColors;
    f32 dx, dy, distance, nx, ny;
    f32 bottom, right, left, top, edge, width, half, alpha;
    Gfx *gfx;
    s32 i;
    if (intensity == 0.0f || actor->hidden) return;
    dx = g_hudReferenceViewportWidth / 2 - x;
    dy = g_hudReferenceViewportHeight / 2 - y;
    gfx = g_displayListCursor++;
    gDPSetTextureFilter(gfx, G_TF_BILERP);
    distance = Gu_Sqrtf(dx * dx + dy * dy);
    if (!special) {
        edge = distance / Gu_Sqrtf((f32)(g_hudReferenceViewportWidth * g_hudReferenceViewportWidth) * 0.25f + (f32)(g_hudReferenceViewportHeight * g_hudReferenceViewportHeight) * 0.25f);
        if (edge > 1.0f) intensity = 0.0f;
        else intensity *= 1.0f - edge;
    }
    distance *= 0.4f;
    if ((dx < 0.0f ? -dx : dx) > (dy < 0.0f ? -dy : dy)) {
        nx = -1.0f;
        if (dx > 0.0f) nx = 1.0f;
        ny = dy / (dx < 0.0f ? -dx : dx);
    } else {
        nx = dx / (dy < 0.0f ? -dy : dy);
        ny = -1.0f;
        if (dy > 0.0f) ny = 1.0f;
    }
    if (special) {
        half = 35.2f;
        bottom = (f32)g_hudReferenceViewportHeight + half;
        right = (f32)g_hudReferenceViewportWidth + half - x;
        left = x + half;
        top = y + half;
        edge = bottom - y;
        if (!(edge <= right)) edge = right;
        if (!(edge <= top)) edge = top;
        if (!(edge <= left)) edge = left;
        if (!(edge <= half)) edge = half;
        if (edge < 0.0f) intensity = 0.0f;
        else {
            alpha = bottom - y;
            if (!(alpha <= right)) alpha = right;
            if (!(alpha <= top)) alpha = top;
            if (!(alpha <= left)) alpha = left;
            if (!(alpha <= half)) alpha = half;
            intensity *= alpha / half;
        }
        intensity = intensity > 1.0f || !(intensity < 0.0f) ? (intensity > 1.0f ? 1.0f : intensity) : 0.0f;
    }
    for (i = 0; i < 7; i++) {
        x += nx * distance;
        y += ny * distance;
        if (special && i == 0) width = 2.0f;
        else width = radii.value[i] * 0.03125f;
        width *= 0.55f;
        half = width * 16.0f;
        if (!(x > -half && x < g_hudReferenceViewportWidth + half && y > (top = -half) && y < g_hudReferenceViewportHeight + half)) return;
        if (special && i == 0) {
            gDPSetEnvColor(g_displayListCursor++, 255, 255, 255, intensity * 255.0f);
            OnScreen_DrawSpriteResource(600, 0, (s16)(s32)(x - half), (s16)(s32)(y - half), width, width, 1);
        } else {
            gDPSetEnvColor(g_displayListCursor++, colors.value[i * 3], colors.value[i * 3 + 1], colors.value[i * 3 + 2], alphas.value[i] * intensity);
            OnScreen_DrawSpriteResource(601, 0, (s16)(s32)(x - half), (s16)(s32)(y - half), width, width, 1);
        }
    }
}

/* The lens sources are the effect owner's group list at +0xFC14. */

extern void Onscrn_SetupSpriteMode(s32);
extern s32 Geometry_SetModePreset(s32);


/* Same body as Gsky_ProjectToScreen: project a world point through the view matrix to screen pixels. */
static inline void ProjectToScreen(ClipView *view, CVector3 *point, f32 *screenX, f32 *screenY) {
    CVector3 value;
    f32 half;
    Graphu64_ProjectPoint(view->viewProjection, point, &value);
    half = (f32)(g_hudReferenceViewportWidth / 2);
    *screenX = value.x * half + half;
    *screenY = value.y * (f32)(-g_hudReferenceViewportHeight / 2) + (f32)(g_hudReferenceViewportHeight / 2);
}

/* Draws the lens flares of every lit flare source the view can see. */
void Gsky_DrawObjectFlares(ClipView *view) {
    Gfx **gfx = &g_displayListCursor;
    Gfx *g;
    Shared_Particle *source;
    f32 x, y;
    s32 mask = 8 << view->index;

    Onscrn_SetupSpriteMode(100);
    Geometry_SetModePreset(26);
    g = *gfx;
    gDPSetTextureFilter(g++, G_TF_BILERP);
    *gfx = g;
    for (source = (Shared_Particle *)((struct EffectSystem *)g_actorParticleEffectSystem)->groups.head; source != 0; source = source->groupNext) {
        if ((source->flags & mask) && (source->desc->flags & 0x80000)) {
            ProjectToScreen(view, &source->inst.pos, &x, &y);
            Sky_DrawLensFlare(view, x, y, source->alpha * (1.0f / 255.0f), 0, 0);
        }
    }
}

/* First six of the seven lens flare radii (FlareRadii in COMMON/LENS_FLARE.H); the seventh follows in its own file. */
float k_lensFlareRadii[6] = {
    16.0f, 16.0f, 24.0f, 32.0f, 16.0f, 32.0f,
};

/* Lens flare tables read by Sky_DrawLensFlare (FlareAlphas / FlareColors in COMMON/LENS_FLARE.H). */


/* seven R,G,B triples */
















#if !(defined(VERSION_US_REV1))
const float k_gskySetShakeChannelLeadDecay[1] = {
    0.1f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_gskySetShakeChannelLeadDecay[1] = {
    0.1f,
};
#endif





#if !(defined(VERSION_US_REV1))
const float k_gskySetShakeChannelTailDecay[1] = {
    0.1f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_gskySetShakeChannelTailDecay[1] = {
    0.1f,
};
#endif







#if defined(VERSION_EU)
const char k_linkTablesStringBytesEu[3] __attribute__((aligned(1))) = "B@\000";
#endif


#if defined(VERSION_US)
/* Seventh and last element of k_lensFlareRadii (the first six are in K_LENSFLARERADII.CPP). */

#endif

/* Retained data for this translation unit. */

const float k_gskyResetheadbobDataFloatConstantWords[3] = {
    0.09765625f, 11.0f, 5.0f,
};

const float k_gskyResetHeadBobConstants[4] = {
    0.2f, 0.1f, 1.5707965f, 1.308997f,
};

const float k_gskyResetHeadBobDecay[1] = {
    0.1f,
};

const float k_gskyStartEmitterUnit[1] = {
    1.0f,
};

const float k_gskyStartemitterDataFloatConstantWords[1] = {
    0.1f,
};

const float k_GskyFindnearestcameraMaxFiniteFloatWords[1] = {
    3.4028235e+38f,
};

const double k_gskyGetmeanviewdistanceDataFloatConstantWords[1] = {
    4294967296.0,
};

const float k_gskySetShakeChannelDegreeToRadian[1] = {
    0.017453294f,
};

const float k_gskySetShakeChannelUnit[1] = {
    1.0f,
};

const float k_gskyFloatConstantWords[6] = {
    0.5f, 0.25f, 0.2f, 0.017453294f,
    0.1f, 10.24f,
};

const float k_gskyFloatConstantsTail[3] = {
    0.09765625f, 11.0f, 5.0f,
};

const float k_skyPostscreenmessageDataFloatConstantWords[2] = {
    3e+01f, 3e+01f,
};
#if defined(VERSION_US)
const float k_lensFlareFinalRadiusBytesUs = 48.0f;
#endif
