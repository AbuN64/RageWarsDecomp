#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"

extern s32 InstHdr_GetActorType(void *prop);




s32 Barrel_GetImpactSlot(void *actorObject)
{
    char *actor = actorObject;
    CGameStatus *audio;
    s32 type;

    type = InstHdr_GetActorType(actor);
    switch (type) {
    case 1:
    case 2:
        return 0;
    case 3:
    case 4:
        return 1;
    case 5:
    case 6:
        return 2;
    case 7:
    case 8:
        return 3;
    case 9:
    case 10:
    case 100:
    case 102:
    case 1120:
    case 1121:
    case 1122:
    case 1123:
    case 1126:
        if (*(u8 *)actor == 1) {
            if ((((ActorProfileImpulseFlagsView *)(actor))->profileFlags & 0x300000) != 0) {
                if ((((ActorProfileImpulseFlagsView *)(actor))->impulseFlags & 0x18400) != 0) {
                    return 9;
                }
                audio = &g_gameSettings.counters;
                if (audio->enabled != 0 &&
                    ((struct PlayerCharacterKindView *) ((ActorProfileImpulseFlagsView *) actor)->characterProfile)->characterKind == 11 &&
                    audio->m_nBastilleShield > 0) {
                    return 9;
                }
            }
        }
        return 4;
    case 11:
    case 12:
        return 5;
    case 13:
    case 14:
        return 6;
    case 15:
    case 16:
        return 7;
    case 17:
    case 18:
        return 8;
    case 19:
    case 20:
    case 103:
        return 9;
    default:
        return 3;
    }
}
