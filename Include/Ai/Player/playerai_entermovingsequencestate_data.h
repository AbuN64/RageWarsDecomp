#ifndef AI_PLAYER_PLAYERAI_ENTERMOVINGSEQUENCESTATE_DATA_H
#define AI_PLAYER_PLAYERAI_ENTERMOVINGSEQUENCESTATE_DATA_H
#include "types.h"
#include "Common/small_records.h"

struct PlayerBodyPositionYawView;
struct PlayerBodyPositionYawView {
    char pad0[0x8];
    CVector3 position;
    char pad14[4];
    struct Model *model; /* +0x18: actor definition */
    char pad1C[0x1C];
    u32 flags; /* +0x38 */
    char pad3C[0x30];
    f32 yaw;
};
typedef struct PlayerBodyPositionYawView PlayerBodyPositionYawView;

struct SharedPlayer;
struct PlayerBodyPositionYawView;
void Playerai_UpdateMountedMovement(struct SharedPlayer *player,struct PlayerBodyPositionYawView *body);
#endif
