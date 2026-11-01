#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "TYPES.H"
#include "RENDER/WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA.H"
#include "COMMON/ITEMRECAT20V1.H"

/* 8022AE90_10.CPP */
void Playerai_BeginHeldAlternateFire(struct SharedPlayer *actor) {
    if (actor->views5E8.view1210_152.marker == 0) {
        Player_SetPlayerState(actor, actor, 39);
        actor->views5E8.view1210_152.marker = 1;
        actor->views5E8.view1214_154.markerState = 0;
    }
}

/* 8022AE90_11.CPP */
void Playerai_EndHeldAlternateFire(void *actor) {
    if ((((struct PlayerAlternateFireStateView *) ((s8 *) actor))->alternateFireMarker) != 0) {
        if ((((struct PlayerAlternateFireStateView *) ((s8 *) actor))->health) != 0) {
            Player_SetPlayerState(actor, actor, 2);
        }
        (((struct PlayerAlternateFireStateView *) ((s8 *) actor))->alternateFireMarker) = 0;
        (((struct PlayerAlternateFireStateView *) ((s8 *) actor))->alternateFireMarkerState) = 0;
    }
}

/** Return the linked record with the greatest eight-slot score excluding itself. */
void *Playerai_FindHighestScoringOtherPlayer(Context *context) {
    ScoredPlayerRecord *node;
    ScoredPlayerRecord *base;
    ScoredPlayerRecord *bestNode = 0;
    int best = -1;

    node = context->head;
    if (node != 0) {
        base = context->base;
        do {
            unsigned int own = (unsigned int)((u8 *)node - (u8 *)base) / sizeof(ScoredPlayerRecord);
            int score = 0;
            int i;
            for (i = 0; i < 8; i++) {
                if (i == own) {
                    continue;
                }
                score += node->scores->value[i];
                if (best < score) {
                    best = score;
                    bestNode = node;
                }
            }
            node = node->next;
        } while (node != 0);
    }
    return bestNode;
}

/** Read the global word at VRAM 0x80145048. */

int Playerai_GetPlayerCount(void) {
    return g_playerCount;
}
