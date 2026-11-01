#include "TYPES.H"

extern char g_itemLabelSlots[];
extern char g_weaponFireStateCallbackTable[];

#include "DATA/WEAPON_EVENT_TRANSLATION/WEAPONAI_INITIALIZESWITCHANDREQUESTIDLE_DATA.H"

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
} g_WeaponaiInitializeswitchandrequestidleWords1 __attribute__((aligned(4))) = {
    0,
    0,
    1.0f,
    1.0f,
    (void *)&g_weaponFireStateCallbackTable,
    0,
    0
};
typedef char g_WeaponaiInitializeswitchandrequestidleWords1SizeCheck[(sizeof(g_WeaponaiInitializeswitchandrequestidleWords1) == 28) ? 1 : -1];
#endif

extern char g_weaponPresentationResource1219[];
extern char g_weaponSlot2PresentationUsRev1[];
extern char g_weaponSlot3PresentationUsRev1[];
extern char g_weaponSlot4PresentationUsRev1[];
extern char g_weaponSlot5PresentationUsRev1[];
extern char g_weaponSlot6PresentationUsRev1[];
extern char g_weaponSlot7PresentationUsRev1[];
extern char g_weaponSlot8PresentationUsRev1[];
extern char g_weaponPresentation6_us_rev1[];
extern char g_weaponPresentation1_us_rev1[];
extern char g_weaponPresentation2_us_rev1[];
extern char g_weaponPresentation3_us_rev1[];
extern char g_weaponPresentation4_us_rev1[];
extern char g_weaponPresentation5_us_rev1[];
extern char g_weaponPresentation7_us_rev1[];
extern char g_weaponPresentation8_us_rev1[];
extern char g_weaponPresentationResource1235[];
extern char g_weaponSlot1PresentationUsRev1[];
extern char g_weaponPresentationDescriptor0Rev1[];
extern char g_weaponPresentationDescriptor1Rev1[];
extern char g_weaponPresentationDescriptor2Rev1[];
extern char g_weaponPresentationDescriptor3Rev1[];
void * g_WeaponResourceDirectoryWords1[22] = {
    (void *)&g_weaponPresentationResource1219, (void *)&g_weaponSlot2PresentationUsRev1, (void *)&g_weaponSlot3PresentationUsRev1, (void *)&g_weaponSlot4PresentationUsRev1,
    (void *)&g_weaponSlot5PresentationUsRev1, (void *)&g_weaponSlot6PresentationUsRev1, (void *)&g_weaponSlot7PresentationUsRev1, (void *)&g_weaponSlot8PresentationUsRev1,
    (void *)&g_weaponPresentation6_us_rev1, (void *)&g_weaponPresentation1_us_rev1, (void *)&g_weaponPresentation2_us_rev1, (void *)&g_weaponPresentation3_us_rev1,
    (void *)&g_weaponPresentation4_us_rev1, (void *)&g_weaponPresentation5_us_rev1, (void *)&g_weaponPresentation7_us_rev1, (void *)&g_weaponPresentation8_us_rev1,
    (void *)&g_weaponPresentationResource1235, (void *)&g_weaponSlot1PresentationUsRev1, (void *)&g_weaponPresentationDescriptor0Rev1, (void *)&g_weaponPresentationDescriptor1Rev1,
    (void *)&g_weaponPresentationDescriptor2Rev1, (void *)&g_weaponPresentationDescriptor3Rev1,
};

#if defined(VERSION_US_REV1)
struct {
    u32 previousReserved;
    s16 ammoClassIconIds[8];
    void * indexedValues[7];
    s32 indexedSentinel;
    s32 cameraModes[3];
    void * cameraCallback;
} g_WeaponaiInitializeswitchandrequestidlePointerWords1 __attribute__((aligned(4))) = {
    0x0,
    { 3050, 3051, 3052, -1, 3053, 3054, 3055, 3056 },
    { (void *)&g_itemLabelSlots, (void *)((char *)&g_itemLabelSlots + 4), (void *)((char *)&g_itemLabelSlots + 8), (void *)((char *)&g_itemLabelSlots + 12), (void *)((char *)&g_itemLabelSlots + 16), (void *)((char *)&g_itemLabelSlots + 20), (void *)((char *)&g_itemLabelSlots + 24) },
    -1,
    { 1, 1, 0 },
    (void *)&g_Gsky_FloorSurfaceNoOpAddress
};
typedef char g_WeaponaiInitializeswitchandrequestidlePointerWords1SizeCheck[(sizeof(g_WeaponaiInitializeswitchandrequestidlePointerWords1) == 68) ? 1 : -1];
#endif
#endif
