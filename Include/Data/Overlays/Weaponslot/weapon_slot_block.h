#ifndef DATA_OVERLAYS_WEAPONSLOT_WEAPON_SLOT_BLOCK_H
#define DATA_OVERLAYS_WEAPONSLOT_WEAPON_SLOT_BLOCK_H

#include "types.h"

/* One weapon slot of the us-rev1 slot block (rom 0xD0F84, stride 0x60). */
typedef struct WeaponSlot {
    f32 viewOffset[3];
    struct {
        void * reserved0;
        void * reserved1;
        f32 scale;
        f32 speed;
        void * states;
        void * enter;
        void * update;
    } stateRecord;
    struct {
        unsigned int textLine;
        unsigned short resourceIds[2];
    } presentationDescriptor;
    struct {
        s16 resource;
        s16 sentinel;
    } descriptorTerminator;
    struct {
        unsigned short ids[4];
        unsigned int count;
    } aimPresentationIds;
    f32 aimTail; /* slot 0: 4.0f; slots 1-3: zero fill after the 12-byte AimIds row */
    struct {
        f32 scale;
        void * primaryStates;
        void * primaryActions;
        void * primaryReserved;
        void * alternateStates;
        void * alternateActions;
        void * alternateReserved;
    } primaryAlternateStateRecord;
} WeaponSlot;

typedef struct WeaponSlotBlock {
    WeaponSlot slots[4];
    f32 closingViewOffset[3];
} WeaponSlotBlock;

#if defined(VERSION_US_REV1)
extern WeaponSlotBlock g_weaponSlotBlock;
#endif

typedef struct WeaponSlotBehavior {
    void *reserved[2];
    f32 scaleAndSpeed[2];
    void *states;
    void *enter;
    void *update;
} WeaponSlotBehavior;

typedef struct WeaponSlotHead {
    WeaponSlotBehavior behavior;
    struct {
        unsigned int textLine;
        unsigned short resourceIds[2];
    } presentation;
    struct {
        s16 resource;
        s16 sentinel;
    } availability;
    struct {
        unsigned short limits[4];
        unsigned int flags;
    } trailer;
} WeaponSlotHead;

typedef struct WeaponSlotAmmoLinks {
    f32 aimSpread;
    void *primaryStates;
    void *primaryActions;
    void *primaryReserved;
    void *alternateStates;
    void *alternateActions;
    void *alternateReserved;
} WeaponSlotAmmoLinks;

/* One weapon slot as laid out from rom 0xD0984 (us-rev1): 0x60 bytes. reserved (+0x40) is zero in
 * every slot; no reader is known. */
typedef struct WeaponSlotLinkedRecord {
    f32 viewOffset[3];
    WeaponSlotHead head;
    unsigned int reserved;
    WeaponSlotAmmoLinks links;
} WeaponSlotLinkedRecord;

/* Slot 8 ends before its ammo links, which g_weaponSlotPresentationRows owns at rom 0xD0C68. */
typedef struct WeaponSlotLastRecord {
    f32 viewOffset[3];
    WeaponSlotHead head;
    unsigned int reserved;
} WeaponSlotLastRecord;

/* Rows indexed by slot: slots 1-7 are slots[slot - 1], slot 8 is lastSlot. */
typedef struct WeaponSlotRecordTable {
    WeaponSlotLinkedRecord slots[7];
    WeaponSlotLastRecord lastSlot;
} WeaponSlotRecordTable;

extern WeaponSlotRecordTable g_weaponSlotRecords;

#endif
