#include "COMMON/LEVEL.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/TRIGGER_AND_FLOAT_VALUE_OPERATIONS.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "OVLGAME/SCENE_DISPATCHANDRECYCLEQUEUEDTRIGGERS.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "ENGINE/SCENE_LOADLEVELRESOURCES.H"
/* Spawns the pickups of a level: between Cinema_ClearPlaybackFlag and Cinema_SetPlaybackFlag it passes every item of both item tables whose kind is 1, 2, 4 or 10 to Scene_DispatchEnabledEntityTrigger. */
extern s32 Scene_GetIndexedModelResource(s32, s32);
void Scene_DispatchSelectedEntityKinds(Level *level) {
    s32 i;
    s32 n;
    ItemOvlSceneDispatchSelectedEntityKinds *item;

    Cinema_ClearPlaybackFlag();
    n = level->counts[0];
    for (i = 0; i < n; i++) {
        item = &level->items[0][i];
        if (item->kind == 1 || item->kind == 4 || item->kind == 2 || item->kind == 10) {
            Scene_DispatchEnabledEntityTrigger(level, item);
        }
    }
    n = level->counts[1];
    for (i = 0; i < n; i++) {
        item = &level->items[1][i];
        if (item->kind == 1 || item->kind == 4 || item->kind == 2 || item->kind == 10) {
            Scene_DispatchEnabledEntityTrigger(level, item);
        }
    }
    Cinema_SetPlaybackFlag();
}
void Scene_DispatchAndRecycleQueuedTriggers(SceneTriggerQueueOwner *scene) {
    EntryOvlSceneDispatchAndRecycleQueuedTriggers *entry;
    EntryOvlSceneDispatchAndRecycleQueuedTriggers *next;

    entry = scene->active;
    while (entry != 0) {
        next = entry->next;
        Link_DispatchTrigger(entry->handle);
        List_RemoveIntrusive(&scene->active, entry);
        List_PrependIntrusive(&scene->spare, entry);
        entry = next;
    }
}
void Scene_RelocateParticleEffectData(s32 world, void ***handle) {
    void *obj;
    PieceGroup *group;
    Piece *piece;
    s32 base;
    s32 count;
    s32 i;

    if (Ppdecom_UnpackResource(handle, 0) != 0) {
        obj = **handle;
        group = SetN64_GetPackSection(obj, 2);
        count = group->count;
        piece = group->pieces;
        i = 0;
        base = (s32) SetN64_GetPackSection(obj, i);
        if (count > 0) {
            do {
                if (piece[i].tag == -1) {
                    piece[i].tag = 0;
                } else {
                    piece[i].tag = Scene_GetIndexedModelResource(world, piece[i].tag);
                }
                piece[i].relocatedOffset18 = base + piece[i].relocatedOffset18;
                piece[i].relocatedOffset1C = base + piece[i].relocatedOffset1C;
                piece[i].relocatedOffset20 = base + piece[i].relocatedOffset20;
                piece[i].relocatedOffset24 = base + piece[i].relocatedOffset24;
                piece[i].relocatedOffset28 = base + piece[i].relocatedOffset28;
                piece[i].relocatedOffset2C = base + piece[i].relocatedOffset2C;
                piece[i].relocatedOffset30 = base + piece[i].relocatedOffset30;
                piece[i].relocatedOffset34 = base + piece[i].relocatedOffset34;
                piece[i].relocatedOffset38 = base + piece[i].relocatedOffset38;
                i++;
            } while (i < count);
        }
    }
}
void Scene_ScaleDefinitionFields(s32 unused0, void ***handle) {
    f32 scale;
    void *obj;
    Ent *ent;
    s32 count;
    s32 i;

    scale = k_sceneDefinitionFieldScale_de;
    if (Ppdecom_UnpackResource(handle, 0) != 0) {
        obj = **handle;
        count = *(s32 *) obj;
        for (i = 0; i < count; i++) {
            ent = SetN64_GetPackSection(obj, i);
            switch (ent->kind) {
            case 1:
                ent->scaledValueA = ent->scaledValueA * scale;
                ent->scaledValueB = ent->scaledValueB * scale;
                ent->scaledValueC = ent->scaledValueC * scale;
                ent->scaledValueD = ent->scaledValueD * scale;
                ent->scaledValueE = ent->scaledValueE * scale;
                ent->scaledValueF = ent->scaledValueF * scale;
                break;
            case 11:
                ent->scaledKind11ValueA = ent->scaledKind11ValueA * scale;
                ent->scaledKind11ValueB = ent->scaledKind11ValueB * scale;
                break;
            case 0:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                break;
            }
        }
    }
}
void Scene_ResolveFrameItemReferences(SceneTriggerQueueOwner *scene, void ***handle) {
    void *obj;
    ParticleEffectRelocationFrame *frame;
    SceneFrameItemBank *bank;
    struct SceneFrameItemReference *items;
    struct SceneFrameItemReference *item;
    ParticleEffectRelocationSlot *slot;
    s32 count;
    s32 inner;
    s32 i;
    s32 j;
    s32 index;

    if (Ppdecom_UnpackResource(handle, 0) != 0) {
        obj = **handle;
        count = *(s32 *) obj;
        for (i = 0; i < count; i++) {
            frame = SetN64_GetPackSection(SetN64_GetPackSection(obj, i), 1);
            inner = frame->count;
            j = 0;
            if (j < inner) {
                slot = frame->slots;
                do {
                    index = slot->item;
                    if (index != -1) {
                        bank = SetN64_GetPackSection(scene->modelBankData, 2);
                        items = bank->items;
                        if ((index < 0) || (index >= bank->count)) {
                            item = 0;
                        } else {
                            item = &items[index];
                        }
                        slot->item = (s32) item;
                    } else {
                        slot->item = 0;
                    }
                    slot++;
                    j++;
                } while (j < inner);
            }
        }
        scene->frameResourceData = obj;
    }
}
