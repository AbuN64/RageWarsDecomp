#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/WORLD.H"
#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "TYPES.H"
#include "../../../sdk/include/SCHED/sched_runeventloopus.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "ENGINE/SCENE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* Collects platform actors, records the special actor and selects one of three random states. */

extern LevelActor *g_sceneSpecialActorTables[];
extern LevelActor *g_sceneSpecialModelBd6Actor;
extern s32 XPlus_NextRandomInteger(void);
void Scene_CollectSecondarySpecialActors(LevelActorArrayView *scene) {
 s32 count=0,i=9,offset=36;LevelActor *actor=scene->actors;
 g_sceneSpecialModelBd6Actor=0;
 do {*(LevelActor **)((char *)g_sceneSpecialActorTables+offset)=0;i--;offset-=4;} while(i>=0);
 i=0;
 if(scene->count>0)do {
  if(((struct Def *)actor->definition)->type==3) {if(((struct Def *)actor->definition)->id==3030){if(scene->count)g_sceneSpecialModelBd6Actor=actor;else g_sceneSpecialModelBd6Actor=actor;}}
  else if(((struct Def *)actor->definition)->type==10) {if(actor->type==1614)g_sceneSpecialActorTables[count++]=actor;}
  if(count>=10)return;
  actor++;

 }while(++i<scene->count);
 g_gameSettings.counters.m_nFragTagSkin=XPlus_NextRandomInteger()%3;
}

/* Remaps every 4-bit pixel of every image in each of the 256 entries of a table through the given
   nibble table. */

extern void OnScreen_GetImageEntry(void *table, s32 index, void **out, u8 *tag);

void Scene_RemapFourBitImagePixels(void *unused0, void *table, u8 *remap) {
    s32 i;
    void *data;
    u8 tag;
    ImageSet *set;
    struct IntPair *image;
    s32 rows;
    s32 columns;
    u32 count;
    u8 *pixel;
    s32 hi;
    s32 lo;
    s32 end;
    s32 width;
    s32 height;

    i = 0;
    end = -1;
    for (; i < 256; i++) {
        end = -1;
        OnScreen_GetImageEntry(table, i, &data, &tag);
        rows = data == 0;
        if (rows) {
            continue;
        }
        set = data;
        rows = set->rows;
        rows--;
        image = (struct IntPair *)(set + 1);
        while (1) {
            if (rows == end) {
                break;
            }
            columns = set->columns;
            columns--;
            for (; columns != end; columns--) {
                width = image->first;
                height = image->second;
                count = (u32)(width * height) >> 1;
                pixel = (u8 *)(image + 1);
                while (count--) {
                    hi = *pixel >> 4;
                    lo = *pixel & 0xF;
                    hi = remap[hi];
                    lo = remap[lo];
                    *pixel = (hi << 4) | lo;
                    pixel++;
                }
                image = (struct IntPair *)((u8 *)image + ((u32)(width * height) >> 1));
                image++;
            }
            rows--;
        }
    }
}

/* Remaps every 4-bit pixel of every image in each of the 256 entries of a resource through the nibble table g_imageLowBoostNibbleRemap, once the resource has been loaded by Ppdecom_UnpackResource_SceneUnpackimageswithhighboost. */

extern s32 Ppdecom_UnpackResource(void *resource, s32 flags);

void Scene_UnpackImagesWithLowBoost(void *unused0, void **resource) {
    s32 i;
    void *data;
    u8 tag;
    void *table;
    u8 *remap;
    ImageSet *set;
    struct IntPair *image;
    s32 rows;
    s32 columns;
    u32 count;
    u8 *pixel;
    s32 hi;
    s32 lo;
    s32 end;
    s32 width;
    s32 height;

    end = Ppdecom_UnpackResource(resource, 0) == 0;
    if (end) {
        return;
    }
    table = *resource;
    remap = g_imageLowBoostNibbleRemap;
    do {
        for (i = 0; i < 256; i++) {
            end = -1;
            OnScreen_GetImageEntry(table, i, &data, &tag);
            if (data == 0) {
                continue;
            }
            set = data;
            rows = set->rows;
            rows--;
            image = (struct IntPair *)(set + 1);
            while (1) {
                if (rows == end) {
                    break;
                }
                columns = set->columns;
                columns--;
                for (; columns != end; columns--) {
                    width = image->first;
                    height = image->second;
                    count = (u32)(width * height) >> 1;
                    pixel = (u8 *)(image + 1);
                    while (count--) {
                        hi = *pixel >> 4;
                        lo = *pixel & 0xF;
                        hi = remap[hi];
                        lo = remap[lo];
                        *pixel = (hi << 4) | lo;
                        pixel++;
                    }
                    image = (struct IntPair *)((u8 *)image + ((u32)(width * height) >> 1));
                    image++;
                }
                rows--;
            }
        }
    } while (0);
}

/* Remaps every 4-bit pixel of every image in each of the 256 entries of a resource through the nibble table g_imageHighBoostNibbleRemap, once the resource has been loaded by Ppdecom_UnpackResource_SceneUnpackimageswithhighboost. Adapted from Scene_UnpackImagesWithLowBoost with the nibble table changed to g_imageHighBoostNibbleRemap. */

void Scene_UnpackImagesWithHighBoost(void *unused0, void **resource) {
    s32 i;
    void *data;
    u8 tag;
    void *table;
    u8 *remap;
    ImageSet *set;
    struct IntPair *image;
    s32 rows;
    s32 columns;
    u32 count;
    u8 *pixel;
    s32 hi;
    s32 lo;
    s32 end;
    s32 width;
    s32 height;

    end = Ppdecom_UnpackResource(resource, 0) == 0;
    if (end) {
        return;
    }
    table = *resource;
    remap = g_imageHighBoostNibbleRemap;
    do {
        for (i = 0; i < 256; i++) {
            end = -1;
            OnScreen_GetImageEntry(table, i, &data, &tag);
            if (data == 0) {
                continue;
            }
            set = data;
            rows = set->rows;
            rows--;
            image = (struct IntPair *)(set + 1);
            while (1) {
                if (rows == end) {
                    break;
                }
                columns = set->columns;
                columns--;
                for (; columns != end; columns--) {
                    width = image->first;
                    height = image->second;
                    count = (u32)(width * height) >> 1;
                    pixel = (u8 *)(image + 1);
                    while (count--) {
                        hi = *pixel >> 4;
                        lo = *pixel & 0xF;
                        hi = remap[hi];
                        lo = remap[lo];
                        *pixel = (hi << 4) | lo;
                        pixel++;
                    }
                    image = (struct IntPair *)((u8 *)image + ((u32)(width * height) >> 1));
                    image++;
                }
                rows--;
            }
        }
    } while (0);
}

/* ROM-grounded data: src/g_scene_TestNearbyActiveActorConstantWords_SceneUnpackimageswithhighboost.c */
const float g_scene_TestNearbyActiveActorConstantWords[1] = {
    6.5536e+06f,
};

s32 Scene_TestSectorSectionTwoEntries(Shared_World *world)
{
  Shared_World *elem;
  s32 i;
  void *field;
  char *unusedPointer1;
  void *ret;
  s32 count;
  count = world->sectorCount;
  if (count <= 0)
  {
    return 0;
  }
  i = 0;
  elem = world;
  do
  {
    field = world->sectors[i].resource;
    ret = SetN64_GetPackSection(*((s32 *) field), 2);
    if ((((struct IntPair *)ret)->second) != 0)
    {
      if (world || i)
      {
        return 1;
      }
      else
      {
        return 1;
      }
    }
    count = world->sectorCount;
    i += 1;

  }
  while (i < count);
  return 0;
}

/** Return an indexed record from the table at object offset 0xAC. */
void *Scene_GetStridedActorRecord(struct Shared_World *object, int index) {
    char *base = (char *)object->actorRecords;
    int stride = *(int *)base;
    return base + (index * stride + 8);
}

extern void Graphu64_SubtractVectors(CVector3 *difference, CVector3 *leftVector, CVector3 *rightVector);

s32 Scene_TestNearbyActiveActor(struct SceneNearestActorView *actor, CVector3 *rightVector) {
    CVector3 vector;
    f32 magnitude;
    u16 type;

    Graphu64_SubtractVectors(&vector, &actor->x, rightVector);
    magnitude = (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
    if (*actor->kind != 1) {
        return 0;
    }
    type = actor->team;
    if (type == 1102 || type == 1107 || type == 1105 || type == 1104 ||
        type == 1108 || type == 1109 || type == 1110) {
        return 0;
    }
    if (actor->active == 0) {
        return 0;
    }
    if (actor->state == 61) {
        return 0;
    }
    return magnitude <= g_sceneImageVectorTolerance;
}

/* Reports whether rightVector is within range of actor, using its type and state to pick the check. */

s32 Scene_ClassifyNearbySpecialActor(NearbySpecialActorView *player, CVector3 *rightVector) {
    CVector3 delta;
    u16 type;

    if (player->kind == 1 && *player->definition == 7) {
        Graphu64_SubtractVectors(&delta, &((Player *)(player))->pos, rightVector);
        delta.y = 0;
        if (262144.0f < delta.x * delta.x + delta.z * delta.z) {
            return 0;
        }
        return 0xFF;
    }
    if (*player->definition != 1) {
        return 0;
    }
    type = player->modelId;
    if (type == 1102 || type == 1107 || type == 1105 || type == 1104 ||
        type == 1108 || type == 1109 || type == 1110) {
        return 0xFF;
    }
    return 0;
}


#if defined(VERSION_DE)
float k_SceneUnpackimageswithhighboostEncodedWords[3] = {
    1.0e-06f, 1.0e-06f, 1.0e-06f,
};
#endif
