#include "TYPES.H"

extern char g_overlayOneFLinkRecordAddressWordsBlock1[];

#include "DATA/WEAPON_SPIN_CALLBACKS/WEAPON_NO_OPERATION_CALLBACK_ADDRESS_US_REV1.H"

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    void * reserved0;
    void * reserved1;
    f32 scale;
    f32 speed;
    void * states;
    void * enter;
    void * update;
} g_weaponSlot3BehaviorUsRev1 __attribute__((aligned(4))) = {
    0,
    0,
    1.0f,
    1.0f,
    (void *)((char *)&g_overlayOneFLinkRecordAddressWordsBlock1 + 28),
    0,
    (void *)&g_weaponNoOperationCallbackAddressUsRev1
};
typedef char g_weaponSlot3BehaviorUsRev1SizeCheck[(sizeof(g_weaponSlot3BehaviorUsRev1) == 28) ? 1 : -1];
#endif
#endif
