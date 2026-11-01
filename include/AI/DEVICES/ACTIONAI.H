#ifndef AI_DEVICES_ACTIONAI_H
#define AI_DEVICES_ACTIONAI_H
#include "COMMON/OBJRECAT30.H"
#include "COMMON/VECTOR4F.H"

struct ActionTrackCallbackRecord {
    char pad0[0x30];
    Hook * callbackHook;
};
extern void Actionai_SetDrawHandler(void *unused0, void *motionState);
extern void Actionai_CopyTrackBytes(char *ownerRecord, char *eventRecord);
extern void Actionai_DisableTrigger(struct Trigger *trigger);
extern void Actionai_InitBreakableMotion(struct LevelActor *actor, struct ActorMotionState *motionState);
extern s32 Actionai_UpdateHealthFlag(struct LevelActor *actor);
extern void Actionai_ClearMotionFlags(struct LevelActor *object);
extern void Actionai_EnableTrigger(struct Trigger *trigger);
extern s32 Actionai_UpdateTriggerFlag(struct LevelActor *actor);
void Actionai_DrawFadedActor(struct FadedActorRenderView *actor, struct ActionFadeInput *input, struct Lookup *lookup);

/* Instruction word encoders for code that data tables hold as words (exception vector patches). */
#define MIPS_K0 26
#define MIPS_MTC0(rt, rd) (0x40800000 | ((rt) << 16) | ((rd) << 11))
#define MIPS_LUI(rt, imm) (0x3C000000 | ((rt) << 16) | (imm))
#define MIPS_ADDIU(rt, rs, imm) (0x24000000 | ((rs) << 21) | ((rt) << 16) | (imm))
#define MIPS_ORI(rt, rs, imm) (0x34000000 | ((rs) << 21) | ((rt) << 16) | (imm))
#define MIPS_JR(rs) (((rs) << 21) | 0x08)
#define MIPS_NOP 0
#endif
