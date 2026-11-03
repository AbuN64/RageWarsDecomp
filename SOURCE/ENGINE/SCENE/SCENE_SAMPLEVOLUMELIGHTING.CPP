#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/LEVEL_GOAL.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/SCENERECAT10C0.H"
#include "ENGINE/SCENE.H"
#include "COMMON/WORLD.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/PLAYERPROFILES.H"
#include "ENGINE/CINEMA/CINEMA.H"

/* Collects up to 10 light volumes holding a point from the world sector whose x/z extent holds it, returning their
 * count through total (0 outside every sector). */
void Scene_FindLightVolumes(Shared_World *world, CVector3 *point, SceneLightVolume **volumes, s32 *total) {
    WorldSector *sector;
    s32 i, found, sectorCount, volumeCount;
    f32 x, z;
    LightVolumeList *list;
    SceneLightVolume *volume, *base;
    sector = 0;
    i = 0;
    found = 0;
    x = point->x; z = point->z;
    sectorCount = world->sectorCount;
    for (; i < sectorCount; i++) {
        WorldSectorExtent *extent = world->sectors[i].bounds;
        if (extent->maxX < x || x < extent->minX ||
            extent->maxZ < z || z < extent->minZ) continue;
        sector = &world->sectors[i];
        break;
    }
    if (sector == 0) {
        *total = 0;
    } else {
        list = SetN64_GetPackSection(sector->resource->pack, 2);
        volumeCount = list->count;
        base = list->volumes;
        for (i = 0; i < volumeCount; i++) {
            Box *bounds;
            volume = &base[i];
            bounds = &volume->bounds;
            if (bounds->max.x > point->x && bounds->max.y > point->y && bounds->max.z > point->z &&
                bounds->min.x <= point->x && bounds->min.y <= point->y && bounds->min.z <= point->z) {
                volumes[found++] = volume;
                if (found == 10) break;
            }
        }
        *total = found;
    }
}

#include <ultra64.h>
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "ACTIONAI/ACTION_UPDATEBREAKABLEPROXIMITY.H"
#include "ENGINE/CACHE/CACHE.H"
#include "ENGINE/SETN64.H"
#include "GRAPHU64/GRAPHU64_GETANGLEDISTANCE.H"
#include "GSKY/SKY_POSTSCALEDSCREENMESSAGE.H"
extern s32 Lighting_EvaluateLocalVolume(SceneLightVolume *, f32, f32, f32, CVector3 *, f32 *);

extern f32 Link_GetLightAnimationOffset(void *);
static inline f32 sampleDot(CVector3 *a, f32 *b, s32 index) { f32 *d=b+index+128; return a->x*d[0] + a->y*d[1] + a->z*d[2]; }
void Scene_SampleVolumeLighting(SceneLightVolume **volumes, s32 count, CVector3 *position, Shared_ParticleLighting *lighting) {
    Shared_Game *settings;
    /* The first 128 floats are weights; the remaining 384 hold XYZ directions. */
    f32 samples[512];
    f32 *weights;
    f32 *directions;
    f32 *sampleDirection;
    CVector3 transformed;
    CVector3 combinedDirection;
    CVector3 color;
    CVector3 ambient;
    CVector3 backLight;
    CVector3 diffuse;
    CVector3 contribution;
    CVector3 localDirection;
    CVector3 translatedDirection;
    CVector3 animationColor;
    CVector3 animatedContribution;
    SceneLightVolume *animatedVolume;
    f32 zero;
    f32 one;
    f32 scale;
    f32 brightness;
    f32 level;
    f32 pulse;
    f32 amount;
    f32 backScale;
    f32 ambientRed;
    f32 ambientGreenLevel;
    f32 ambientBlueLevel;
    f32 diffuseRedLevel;
    f32 diffuseGreenLevel;
    f32 ambientGreen;
    f32 ambientBlue;
    f32 diffuseRed;
    f32 diffuseGreen;
    f32 diffuseBlue;
    s32 sampleIndex;
    SceneLightVolume *volume;

    settings = &g_gameSettings;
    brightness = (f32)(u32)settings->lightingGamma * 0.003921568859368563f;
    animatedVolume = NULL;
    if (settings->flags & 0x4000) {
        lighting->ambientCopy[0] = 0;
        lighting->ambient[0] = 0;
        lighting->ambientCopy[1] = 0;
        lighting->ambient[1] = 0;
        lighting->ambientCopy[2] = 0;
        lighting->ambient[2] = 0;
        lighting->diffuseCopy[0] = 0;
        lighting->diffuse[0] = 0;
        lighting->diffuseCopy[1] = 0;
        lighting->diffuse[1] = 0;
        lighting->diffuseCopy[2] = 0;
        lighting->diffuse[2] = 0;
        lighting->direction[0] = 0x7F;
        lighting->direction[1] = 0;
        lighting->direction[2] = 0;
        return;
    }
    sampleIndex = 0;
    combinedDirection.x = combinedDirection.y = combinedDirection.z = 0.0f;
    ambient.x = ambient.y = ambient.z = 0.0f;
    backLight.x = backLight.y = backLight.z = 0.0f;
    diffuse.x = diffuse.y = diffuse.z = 0.0f;
    if (sampleIndex < count) {


        weights = samples;
        directions = samples + 128;
        do {
            sampleDirection = directions + sampleIndex * 3;
            volume = volumes[sampleIndex];
            Graphu64_TransformPoint(volume->inverse, position, &transformed);
            if (Lighting_EvaluateLocalVolume(volume, transformed.x, transformed.y, transformed.z, &localDirection, &weights[sampleIndex]) != 0) {
                Graphu64_AddVec3(&translatedDirection, &localDirection, &transformed);
                Graphu64_ProjectPoint(volume->transform, &translatedDirection, &localDirection);
                Graphu64_SubtractVectors(sampleDirection, position, &localDirection);
                Graphu64_NormalizeVec3(sampleDirection);
                color = volume->direction;
                if (volume->animatedLight != 0) {
                    level = Link_GetLightAnimationOffset(volume);
                    animationColor.x = level;
                    animationColor.y = level;
                    animationColor.z = level;
                    Graphu64_ScaleVector(&contribution, &animationColor, weights[sampleIndex] * volume->value);
                    animatedVolume = volume;
                    if (volume->flagB8 != 0) {
                        Graphu64_ScaleVector(&contribution, &contribution, -1.0f);
                    }
                    Graphu64_AddVec3(&ambient, &ambient, &contribution);
                }
                amount = volume->value * 0.5f;
                scale = 1.0f - amount;
                Graphu64_ScaleVector(&contribution, &color, weights[sampleIndex] * amount);
                if (volume->flagB8 != 0) {
                    Graphu64_ScaleVector(&contribution, &contribution, -1.0f);
                }
                Graphu64_AddVec3(&ambient, &ambient, &contribution);
                weights[sampleIndex] *= scale;
                amount = color.x; if (amount < 0.0f) amount = -amount;
                if (color.y < 0.0f) amount = amount - color.y; else amount = amount + color.y;
                if (color.z < 0.0f) scale = amount - color.z; else scale = amount + color.z;
                Graphu64_ScaleVector(&contribution, sampleDirection, weights[sampleIndex]);
                Graphu64_ScaleVector(&contribution, &contribution, scale);
                Graphu64_AddVec3(&combinedDirection, &combinedDirection, &contribution);
                if (volume->flagB8 != 0) {
                    weights[sampleIndex] = -weights[sampleIndex];
                }
            } else {
                sampleDirection[0] = 0.0f;
                sampleDirection[1] = 0.0f;
                sampleDirection[2] = 0.0f;
                weights[sampleIndex] = 0.0f;
            }


            sampleIndex += 1;

        } while (sampleIndex < count);
    }
    Graphu64_NormalizeVec3(&combinedDirection);
    sampleIndex = 0;
    if (sampleIndex < count) {
        one = 1.0f;
        zero = 0.0f;
        do {
            volume = volumes[sampleIndex];
            scale = sampleDot(&combinedDirection, samples, sampleIndex * 3);
            backScale = one - scale; if (scale < zero) backScale = one;
            backScale *= 0.5f;
            color = volume->direction;
            scale = one - backScale;
            if (volume == animatedVolume) {
                pulse = Link_GetLightAnimationOffset(volume);
                animationColor.x = pulse;
                animationColor.y = pulse;
                animationColor.z = pulse;
                Graphu64_ScaleVector(&animatedContribution, &animationColor, scale * samples[sampleIndex]);
                Graphu64_AddVec3(&diffuse, &diffuse, &animatedContribution);
                Graphu64_ScaleVector(&animatedContribution, &animationColor, backScale * samples[sampleIndex]);
                Graphu64_AddVec3(&backLight, &backLight, &animatedContribution);
            }
            Graphu64_ScaleVector(&contribution, &color, scale * samples[sampleIndex]);
            Graphu64_AddVec3(&diffuse, &diffuse, &contribution);


            Graphu64_ScaleVector(&contribution, &color, backScale * samples[sampleIndex]);
            Graphu64_AddVec3(&backLight, &backLight, &contribution);
            sampleIndex++;
        } while (sampleIndex < count);
    }
    Graphu64_ScaleVector(&backLight, &backLight, 0.5f);
    Graphu64_AddVec3(&ambient, &ambient, &backLight);
    if (ambient.x < 0.0f) {
        diffuse.x += ambient.x;
    }
    if (ambient.y < 0.0f) {
        diffuse.y += ambient.y;
    }
    if (ambient.z < 0.0f) {
        diffuse.z += ambient.z;
    }
    ambientRed = ambient.x;
    if (!(ambientRed <= 255.0f)) ambientRed = 255.0f;
    if (!(5.0f <= ambientRed)) ambientRed = 5.0f;
    ambient.x = ambientRed * (1.0f - brightness) + brightness * 255.0f;
    ambientGreen = ambient.y;
    if (!(ambientGreen <= 255.0f)) ambientGreen = 255.0f;
    ambientGreenLevel = ambientGreen;
    if (!(5.0f <= ambientGreenLevel)) ambientGreenLevel = 5.0f;
    ambient.y = ambientGreenLevel * (1.0f - brightness) + brightness * 255.0f;
    ambientBlue = ambient.z;
    if (!(ambientBlue <= 255.0f)) ambientBlue = 255.0f;
    ambientBlueLevel = ambientBlue;
    if (!(5.0f <= ambientBlueLevel)) ambientBlueLevel = 5.0f;
    ambient.z = ambientBlueLevel * (1.0f - brightness) + brightness * 255.0f;
    diffuseRed = diffuse.x;
    if (!(diffuseRed <= 255.0f)) diffuseRed = 255.0f;
    diffuseRedLevel = diffuseRed;
    if (!(5.0f <= diffuseRedLevel)) diffuseRedLevel = 5.0f;
    diffuse.x = diffuseRedLevel * (1.0f - brightness) + brightness * 255.0f;
    diffuseGreen = diffuse.y;
    if (!(diffuseGreen <= 255.0f)) diffuseGreen = 255.0f;
    diffuseGreenLevel = diffuseGreen;
    if (!(5.0f <= diffuseGreenLevel)) diffuseGreenLevel = 5.0f;
    diffuse.y = diffuseGreenLevel * (1.0f - brightness) + brightness * 255.0f;
    diffuseBlue = diffuse.z;
    if (!(diffuseBlue <= 255.0f)) diffuseBlue = 255.0f;
    if (!(5.0f <= diffuseBlue)) diffuseBlue = 5.0f;
    diffuse.z = diffuseBlue * (1.0f - brightness) + brightness * 255.0f;
    lighting->ambient[0] = lighting->ambientCopy[0] = (u32)ambient.x;
    lighting->ambient[1] = lighting->ambientCopy[1] = (u32)ambient.y;
    lighting->ambient[2] = lighting->ambientCopy[2] = (u32)ambient.z;
    lighting->diffuse[0] = lighting->diffuseCopy[0] = (u32)diffuse.x;
    lighting->diffuse[1] = lighting->diffuseCopy[1] = (u32)diffuse.y;
    lighting->diffuse[2] = lighting->diffuseCopy[2] = (u32)diffuse.z;
    lighting->direction[0] = (s32)(combinedDirection.x * 127.0f);
    lighting->direction[1] = (s32)(combinedDirection.y * 127.0f);
    lighting->direction[2] = (s32)(combinedDirection.z * 127.0f);
}

#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/WORLD.H"
#include "COMMON/LEVEL_ACTOR.H"

typedef struct SceneTriggerDefinition {
    ActorDefinitionHeader header;
    char pad18[8];
    f32 enterRadius;
    f32 exitRadius;
    f32 touchRadius;
} SceneTriggerDefinition;
/* Fires the movement triggers an actor crosses between two positions. Only kinds 0xB and 1 trip triggers. Kind 6
 * triggers are rings (enter when moving inside enterRadius from outside it, exit when moving outside exitRadius
 * from inside it); kinds 10 and 7 fire their enter event inside their radius while the two actors overlap in height,
 * and a kind 10 trigger first asks Action_ShowTriggerMessage_SceneSamplevolumelighting. Distances are measured in the xz plane. */
void Scene_UpdateMovementTriggers(Shared_World *world, LevelActor *actor, CVector3 *before, CVector3 *after) {
    s32 isKindB;
    s32 isKind1;
    f32 bottom;
    f32 top;
    f32 triggerBottom;
    f32 triggerTop;
    f32 beforeDistance;
    f32 afterDistance;
    f32 enterRadius;
    f32 exitRadius;
    f32 radius;
    s32 kind;
    s32 flags;
    s32 enterOnB;
    s32 enterOn1;
    s32 exitOnB;
    s32 exitOn1;
    s32 entering;
    s32 exiting;
    s32 hit;
    s32 enterMode;
    s32 exitMode;
    s32 ring;
    s32 checkHeight;
    s32 i;
    SceneTriggerDefinition *definition;
    LevelActor *trigger;

    if (before->x == after->x && before->y == after->y && before->z == after->z) {
        return;
    }
    kind = actor->definition->kind;
    isKindB = kind == 11;
    isKind1 = kind == 1;
    bottom = actor->position0.y + InstHdr_GetActorBaseOffset(actor);
    top = bottom + Gobjinst_GetActorHeight(actor);
    for (i = 0; i < world->flaggedCount; i++) {
        trigger = world->flagged[i];
        if (trigger == actor) {
            continue;
        }
        ring = 0;
        checkHeight = 0;
        triggerBottom = trigger->position0.y + InstHdr_GetActorBaseOffset(trigger);
        triggerTop = triggerBottom + Gobjinst_GetActorHeight(trigger);
        definition = (SceneTriggerDefinition *)trigger->definition;
        switch (definition->header.kind) {
        case 6:
            enterMode = 0;
            ring = 1;
            exitMode = 1;
            flags = definition->header.flags;
            enterRadius = definition->enterRadius;
            exitRadius = definition->exitRadius;
            enterOnB = flags & 4;
            enterOn1 = flags & 8;
            exitOnB = flags & 0x10;
            exitOn1 = flags & 0x20;
            break;
        case 10:
            enterMode = 1;
            exitMode = 0;
            exitOnB = 0;
            exitOn1 = 0;
            checkHeight = 1;
            flags = definition->header.flags;
            enterRadius = definition->exitRadius;
            exitRadius = 0.0f;
            enterOnB = flags & 4;
            enterOn1 = flags & 8;
            break;
        case 7:
            enterMode = 1;
            exitMode = 0;
            exitOnB = 0;
            exitOn1 = 0;
            checkHeight = 1;
            flags = definition->header.flags;
            enterRadius = definition->touchRadius;
            exitRadius = 0.0f;
            enterOnB = flags & 8;
            enterOn1 = flags & 0x10;
            break;
        default:
            enterMode = 0;
            enterRadius = 0.0f;
            enterOnB = 0;
            enterOn1 = 0;
            exitMode = 0;
            exitOnB = 0;
            exitOn1 = 0;
            exitRadius = 0.0f;
            break;
        }
        if (checkHeight && (top < triggerBottom || triggerTop < bottom)) {
            entering = 0;
            exiting = 0;
        } else {
            entering = 0;
            if ((isKindB && enterOnB) || (isKind1 && enterOn1)) {
                entering = 1;
            }
            exiting = 0;
            if ((isKindB && exitOnB) || (isKind1 && exitOn1)) {
                exiting = 1;
            }
        }
        if (entering || exiting) {
            beforeDistance = (before->x - trigger->position0.x) * (before->x - trigger->position0.x) +
                             (before->z - trigger->position0.z) * (before->z - trigger->position0.z);
            afterDistance = (after->x - trigger->position0.x) * (after->x - trigger->position0.x) +
                            (after->z - trigger->position0.z) * (after->z - trigger->position0.z);
            if (entering) {
                if (ring) {
                    radius = enterRadius * enterRadius;
                    hit = 0;
                    if (radius < beforeDistance && afterDistance <= radius) {
                        hit = 1;
                    }
                } else {
                    hit = 1;
                    if (!(afterDistance <= enterRadius * enterRadius)) {
                        hit = 0;
                    }
                }
                if (hit) {
                    if (trigger->definition->kind == 10 && enterMode == 1) {
                        hit = Action_ShowTriggerMessage(trigger, &trigger->behaviorFlags, actor);
                    }
                    if (hit) {
                        Actor_RequestActorState(trigger, &trigger->behaviorFlags, enterMode);
                    }
                }
            }
            if (exiting) {
                if (ring) {
                    radius = exitRadius * exitRadius;
                    hit = 0;
                    if (beforeDistance <= radius && radius < afterDistance) {
                        hit = 1;
                    }
                } else {
                    hit = 1;
                    if (!(exitRadius * exitRadius < afterDistance)) {
                        hit = 0;
                    }
                }
                if (hit) {
                    Actor_RequestActorState(trigger, &trigger->behaviorFlags, exitMode);
                }
            }
        }
    }
}

#include "TYPES.H"
#include "COMMON/COLORENTRY.H"
#include "COMMON/WORLD.H"
extern f32 g_frameElapsedTime;

#include "COMMON/MENU_MATCH_GLOBALS.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern u8 *g_optionFlagsChangedMessageText[];
#else
extern u8 *g_optionFlagsChangedMessageText;
#endif
extern void Track_RequestCameraRefresh(void), Track_RequestTrackByKey(s32);
extern s32 SetN64_IsModeThirteen(void);
extern void Scene_LoadLevelResources(void *, s32, s32);

static inline s32 transitionId(Shared_World *scene) {
    if (scene->selectionFlags != 0) return scene->selectionSpawn.kind;
    return scene->selectionValues[1];
}
void Scene_UpdateSelectionTransition(Shared_World *scene)
{
    ColorEntry *entry = &g_emacText[scene->selectionState];
    s32 id;
    MenuSettings *settings;
    switch (scene->frozen) {
    case 0:
        break;
    case 1:
        if (scene->selectionTimer == entry->value) {
            if (scene->selectionValues[1] == 999) { Track_RequestCameraRefresh(); Track_RequestTrackByKey(400); }
            if (scene->selectionState == 0) scene->frozen = 0;
            else scene->frozen = 2;
            if (scene->selectionValues[1] < 0) { scene->selectionValues[1] = ~scene->selectionValues[1]; scene->selectionFlags = 0; }
            else scene->selectionFlags = Scene_FindPlacedObjectsByKey(scene, -1, scene->selectionValues[1], &scene->selectionSpawn, 1);
            scene->selectionValues[0] = scene->selectionValues[1];
            id = transitionId(scene);
            Scene_LoadLevelResources(scene, id, scene->selectionFlags);
            settings = &g_frontendScreenStatus.settings;
            if (scene->previewStart != settings->optionFlags && SetN64_IsModeThirteen()) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, g_optionFlagsChangedMessageText[settings->language], 4.0f);
#else
                Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, g_optionFlagsChangedMessageText, 4.0f);
#endif
                scene->previewStart = settings->optionFlags;
            }
        } else {
            scene->selectionTimer += g_frameElapsedTime;
            if (entry->value < scene->selectionTimer) scene->selectionTimer = entry->value;
        }
        break;
    case 2:
        if (scene->selectionTimer == 0.0f) scene->frozen = 0;
        else {
            scene->selectionTimer -= g_frameElapsedTime;
            if (scene->selectionTimer < 0.0f) scene->selectionTimer = 0.0f;
        }
        break;
    }
}


#include "COMMON/WORLD.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENU_TEXT.H"
#include "COMMON/RESULTS_TEXT.H"
extern void Cache_ReleaseResource(s32, void *);
typedef struct ResultsText {
    char *text;
    s32 length;
} ResultsText;
typedef struct ResultsCourse {
    u8 reservedBytes[0x21];
    u8 laps;          /* 0x21 */
    u8 targetCount;   /* 0x22 */
    u8 rounds;        /* 0x23 */
    u8 timeLimit;     /* 0x24: seconds */
    u8 reservedBytes1[3];
    u8 lives;         /* 0x28 */
} ResultsCourse;
typedef struct LevelChallenge {
    u8 reservedBytes2[4];
    u8 character;     /* 0x4: the opponent's character key */
    u8 reservedWord;
    u16 weapons[8];   /* 0x6: starting weapon item ids (read by the achieve loadout) */
} LevelChallenge;
extern ResultsCourse *g_currentStagePreset;
extern ResultsHeadingCharacter g_resultCharacterHeadings[];
extern char g_levelNameText[], g_resultsNameFormat_de[], g_cResource_UnpackRequestEntry[];
extern char *g_characterPreviewTextReferenceShared1;
extern char *g_characterPreviewTextReferenceShared2;
extern char *g_characterPreviewTextReferenceShared3;
extern char *g_characterPreviewTextReferenceShared4;
extern char *g_characterPreviewTextReferenceShared5;
extern char *g_resultsRoundsOneFormat;
extern char *g_resultsRoundsTwoFormat;
extern char *g_resultsRoundsThreeFormat;
extern char *g_resultsLapsOneFormat;
extern char *g_resultsLapsTwoFormat;
extern char *g_resultsLapsThreeFormat;
extern char *g_resultsLapsFourFormat;
extern char *g_resultsLapsFiveFormat;
extern char *g_resultsGoalOneFormat;
extern char *g_resultsGoalTwoFormat;
extern char *g_resultsTimeLimitFormat;
extern char *g_resultsMinutesSecondsOneFormat;
extern char *g_resultsMinutesSecondsTwoFormat;
extern char *g_resultsMinutesOneFormat;
extern char *g_resultsMinutesTwoFormat;
extern *g_resultsPlayerOrLivesOneFormat;
extern char *g_pakDialogTextReferenceShared1;
extern char *g_resultsGoalLabelFormat;
extern char *g_resultsGoalValueFormat;
extern char *g_slotSelectionTextReferenceShared4;
extern void Cinema_AddMessage(int goal);

extern void *Cache_RequestWordCountedResourcePinned(s32, void **, s32, void *);


extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);
extern u8 Player_GetLevelProgress(Profile *, s32);
extern void Scene_ReleaseCachedLevelData(Shared_World *);
extern void *Cache_RequestResource(s32, u32, u32, u32, u32, s32, void *, const char *, u32);

extern s32 Key_FindKeyIndex(s32);
static inline void copyLevelName(Shared_World *world, s32 level, char *out, s32 limit) {
    void *handle;
    s32 entry;
    void *bank;
    ResultsText *name;
    s32 length;

    entry = SetN64_GetDirectoryEntry(world->resourceDirectory, world->resourceBank, level);
    bank = Cache_RequestWordCountedResourcePinned(0, &handle, entry, g_levelIndexText);
    name = Cache_RequestPackSection(0, handle, 8, entry, world, 0, g_levelNameText);
    length = name->length;
    if (limit < length) {
        length = limit;
    }
    Libc_CopyBytes(out, name->text, length);
    Cache_ReleaseResource(0, name);
    if (world->level != level) {
        Cache_ReleaseResource(0, bank);
    }
}
static inline LevelChallenge *findLevelChallenge(Shared_World *world, s32 level) {
    s32 size;
    void **index;
    s32 file;
    s32 mode;
    s32 direct;

    if (world->resourceHandle == 0 || world->resourceKey != level) {
        Scene_ReleaseCachedLevelData(world);
        if (world->challengeFile != 0) {
            mode = 16;
            direct = 1;
            index = Cache_RequestResource(0, world->challengeFile, world->challengeFile, world->challengeFileSize, mode,
                                     0, 0, g_sceneResourceRequestSpareDe, direct);
            if (index != 0) {
                file = SetN64_LocatePackSection((s32)*index, world->challengeFile, level, &size);
                Cache_ReleaseResource(0, index);
                if ((world->resourceHandle =
                         Cache_RequestResource(0, file, file, size, mode, 0, g_cResource_UnpackRequestEntry, g_sceneUnpackRequestSpare, direct)) == 0) {
                    goto missing;
                }
                world->resourceKey = level;
            }
        }
    }
    if (world->resourceHandle != 0) {
        return *world->resourceHandle;
    }
missing:
    return 0;
}

/* Print the level name, then the goal line and the mode's detail line of the results screen. */
void Scene_ShowResultsGoal(void) {
    char name[40];
    char goal[40];
    LevelGoal *levelGoal;
    u8 mode;
    u8 minutes;
    s32 seconds;
    s32 players;
    LevelChallenge *challenge;
    ResultsHeadingCharacter *character;

    Cinema_ClearMessageCount();
    copyLevelName(&g_world, g_selectedLevelId, name, 63);
    Cinema_AddMessage(name);
    if (currentGame()->controllerMode == 0) {
        return;
    }
    levelGoal = &g_currentResultMode; /* kind (0 rounds, 1 laps, 2 single laps, 3 targets), then the target goal */
    switch (levelGoal->kind) {
    case 0:
        if (currentGame()->controllerMode == 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsRoundsThreeFormat, g_resultsRoundsThreeFormatLocalized), g_currentStagePreset->rounds);
        } else if (g_currentStagePreset->rounds < 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsRoundsOneFormat, g_resultsRoundsOneFormatLocalized), g_currentStagePreset->rounds);
        } else {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsRoundsTwoFormat, g_resultsRoundsTwoFormatLocalized), g_currentStagePreset->rounds);
        }
        break;
    case 1:
        if (currentGame()->controllerMode == 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsLapsThreeFormat, g_resultsLapsThreeFormatLocalized), g_currentStagePreset->laps);
        } else if (g_currentStagePreset->laps < 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsLapsOneFormat, g_resultsLapsOneFormatLocalized), g_currentStagePreset->laps);
        } else {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsLapsTwoFormat, g_resultsLapsTwoFormatLocalized), g_currentStagePreset->laps);
        }
        break;
    case 2:
        if (g_currentStagePreset->laps < 2) {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsLapsFourFormat, g_resultsLapsFourFormatLocalized), g_currentStagePreset->laps);
        } else {
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsLapsFiveFormat, g_resultsLapsFiveFormatLocalized), g_currentStagePreset->laps);
        }
        break;
    case 3:
        switch (levelGoal->goal) {
        case 4:
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsGoalLabelFormat, g_resultsGoalLabelFormatLocalized), RESULTS_TEXT(g_characterPreviewTextReferenceShared2, g_characterPreviewTextReferenceShared6));
            break;
        case 9:
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsGoalValueFormat, g_resultsGoalValueFormatLocalized), RESULTS_TEXT(g_characterPreviewTextReferenceShared3, g_characterPreviewTextReferenceEu3),
                             RESULTS_TEXT(g_characterPreviewTextReferenceShared1, g_characterPreviewTextReferenceEu1));
            break;
        case 22:
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsGoalLabelFormat, g_resultsGoalLabelFormatLocalized), RESULTS_TEXT(g_characterPreviewTextReferenceShared4, g_characterPreviewTextReferenceShared7));
            break;
        case 35:
            XStdio_FormatBuffer(goal, RESULTS_TEXT(g_resultsGoalLabelFormat, g_resultsGoalLabelFormatLocalized), RESULTS_TEXT(g_characterPreviewTextReferenceShared5, g_characterPreviewTextReferenceShared8));
            break;
        default:
            if (g_currentStagePreset->targetCount < 2) {
                XStdio_FormatBuffer(goal, RW_LOCALIZED_TEXT(g_resultsGoalOneFormat, g_resultsGoalOneFormatLocalized, g_resultsGoalOneFormatLocalized, g_languageIndex),
                                 g_currentStagePreset->targetCount);
            } else {
                XStdio_FormatBuffer(goal, RW_LOCALIZED_TEXT(g_resultsGoalTwoFormat, g_resultsGoalTwoFormatLocalized, g_resultsGoalTwoFormatLocalized, g_languageIndex),
                                 g_currentStagePreset->targetCount);
            }
            break;
        }
        break;
    }
    mode = currentGame()->controllerMode;
    switch (mode) {
    case 1:
        Cinema_AddMessage(goal);
        players = (Player_GetLevelProgress(g_localPlayerProfiles, g_localPlayerProfiles[0].slot) >> 1) + 1;
        if (players < 2) {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsPlayerOrLivesOneFormat, g_resultsPlayerOrLivesOneFormatLocalized), players);
        } else {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_pakDialogTextReferenceShared1, g_resultsPlayerOrLivesTwoFormatLocalized), players);
        }
        Cinema_AddMessage(name);
        break;
    case 3:
        Cinema_AddMessage(goal);
        if (g_currentStagePreset->timeLimit <= 60) {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsTimeLimitFormat, g_resultsTimeLimitFormatLocalized), g_currentStagePreset->timeLimit);
        } else {
            minutes = g_currentStagePreset->timeLimit / 60;
            if (minutes < 2) {
                seconds = g_currentStagePreset->timeLimit % 60;
                if (seconds == 0) {
                    XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsMinutesOneFormat, g_resultsMinutesOneFormatLocalized), minutes);
                } else {
                    XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsMinutesSecondsOneFormat, g_resultsMinutesSecondsOneFormatLocalized), minutes, seconds);
                }
            } else {
                seconds = g_currentStagePreset->timeLimit % 60;
                if (seconds == 0) {
                    XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsMinutesTwoFormat, g_resultsMinutesTwoFormatLocalized), minutes);
                } else {
                    XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsMinutesSecondsTwoFormat, g_resultsMinutesSecondsTwoFormatLocalized), minutes, seconds);
                }
            }
        }
        Cinema_AddMessage(name);
        break;
    case 4:
        challenge = findLevelChallenge(&g_world, g_selectedLevelId);
        character = &RESULTS_CHARACTERS[Key_FindKeyIndex(challenge->character)];
        XStdio_FormatBuffer(name, RESULTS_NAME_FORMAT, character->name[RESULTS_LANGUAGE].text);
        Cinema_AddMessage(name);
        Cinema_AddMessage(goal);
        if (g_currentStagePreset->lives < 2) {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_resultsPlayerOrLivesOneFormat, g_resultsPlayerOrLivesOneFormatLocalized), g_currentStagePreset->lives);
        } else {
            XStdio_FormatBuffer(name, RESULTS_TEXT(g_pakDialogTextReferenceShared1, g_resultsPlayerOrLivesTwoFormatLocalized), g_currentStagePreset->lives);
        }
        Cinema_AddMessage(name);
        break;
    case 2:
        Cinema_AddMessage(goal);
        switch (g_currentResultMode.kind) {
        case 0:
            break;
        case 1:
            Cinema_AddMessage(RESULTS_TEXT(g_slotSelectionTextReferenceShared4, g_slotSelectionTextReferenceEu7));
            break;
        case 2:
            Cinema_AddMessage(RESULTS_TEXT(g_slotSelectionTextReferenceShared4, g_slotSelectionTextReferenceEu7));
            break;
        }
        break;
    }
}
