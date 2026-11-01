#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PLAYER_ACTION_AND_POSE_VIEWS.H"
#include "TYPES.H"


/* Places a marker in front of an actor: takes the node in *slot or allocates one from pool
   g_dynamicLightPool, turns the offset (0, 0, distance) into world space by the actor's facing through
   Gobjinst_TransformVectorByActorAim, adds the actor's position and stores it as short coordinates, the height raised by
   the actor's size scaled by g_playerOutOfBoundsAndMarkerHeightConstants[1], with scale g_playerOffsetMarkerScale and the node marked active. */






extern f32 g_playerOutOfBoundsAndMarkerHeightConstants[];

extern Marker *Gdynlight_AllocateLightNode(char *, s32);

#include "ENGINE/INSTANCE/GOBJINST_GETACTOROFFSETPOSITIONANDMODEL.H"

extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

extern f32 Gobjinst_GetActorHeight(void *);

/* Returns whether the entity registered under an id in g_weaponInfoByType has flag 1 (mode 0) or flag 2
   (mode 1) set in its word at 0x14; other modes give 0. The interval also holds the empty function
   Playerai_EmptyImpactSoundHook that follows. */


extern LinkedWorldFlagsView *g_weaponInfoByType[];

u8 Playerai_GetImpactSoundEnabled(s32 unused0, s32 soundId) {
    u8 *ptr;

    if (soundId == 730) {
        ptr = &g_gameSettings.local;
        if (*ptr != 0) {
            return ptr[14];
        }
    }
    return 1;
}

void Playerai_UpdateOffsetMarker(Player *actor, Marker **slot, s32 kind, f32 distance) {
    Marker *marker;
    CVector3 offset;
    CVector3 pos;

    marker = *slot;
    if (marker == 0) {
        marker = Gdynlight_AllocateLightNode(&g_dynamicLightPool, kind);
        if (marker == 0) {
            return;
        }
    }
    *slot = marker;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = distance;
    Gobjinst_TransformVectorByActorAim(&pos, actor, offset);
    Graphu64_AddVec3(&pos, &pos, &actor->pos);
    marker->active = 1;
    marker->x = pos.x;
    marker->y = pos.y + Gobjinst_GetActorHeight(actor) * g_playerOutOfBoundsAndMarkerHeightConstants[1];
    marker->z = pos.z;
    marker->scale = g_playerOffsetMarkerScale;
}

void Playerai_ReleaseMarkerSlot(void *unused0, s32 *markerSlot) {
    s32 lightHandle;

    lightHandle = *markerSlot;
    if (lightHandle != 0) {
        Gdynlight_ReleaseLight(&g_dynamicLightPool, lightHandle);
        *markerSlot = 0;
    }
}

int Playerai_HasWeaponModeFlag(short id, int mode) {
    switch (mode) {
    case 0:
        if (!(g_weaponInfoByType[id]->flags & 1)) {
            break;
        }
        return 1;
    case 1:
        if (g_weaponInfoByType[id]->flags & 2) {
            return 1;
        }
        break;
    }
    return 0;
}

void Playerai_EmptyImpactSoundHook(void) {
}
