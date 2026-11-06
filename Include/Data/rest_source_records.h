#include "Data/rom_callback_word.h"
#ifndef DATA_REST_SOURCE_RECORDS_H
#define DATA_REST_SOURCE_RECORDS_H
#include "types.h"
#include "Weapon_state_tables/weapon_state_tables.h"
#include "Data/Ui/event_handler_record.h"
#include "Io/debug_memory.h"

typedef struct WeaponStateRecordsUs {
    u32 words0[1021];
    u32 text1[3];
    u32 words2[2];
} WeaponStateRecordsUs;
extern WeaponStateRecordsUs k_weaponStateRecordsUs;
typedef struct ActorStateEndUsRev1 { s32 endState; } ActorStateEndUsRev1;
extern ActorStateEndUsRev1 g_actorStateEnd_us_rev1;

/* Source records for the fixed data/link sections. Field layouts follow consumers. */
typedef struct RestBytes4 {
    u8 bytes[4];
} RestBytes4;

typedef struct ByteBlock12 {
    u8 bytes[12];
} ByteBlock12;

typedef struct RestBytes8 {
    u8 bytes[8];
} RestBytes8;

typedef struct PlayerStateSpecialTiming01Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming01Record;

typedef struct PlayerStateSpecialCallbacks02PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks02PointerRecord;

typedef struct PlayerStateSpecialTiming02Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming02Record;

typedef struct PlayerStateSpecialCallbacks03PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks03PointerRecord;

typedef struct PlayerStateSpecialTiming03Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming03Record;

typedef struct PlayerStateSpecialCallbacks04PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks04PointerRecord;

typedef struct PlayerStateSpecialTiming04Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming04Record;

typedef struct PlayerStateSpecialCallbacks05PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks05PointerRecord;

typedef struct PlayerStateSpecialTiming05Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming05Record;

typedef struct PlayerStateSpecialCallbacks06PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks06PointerRecord;

typedef struct PlayerStateSpecialTiming06Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming06Record;

typedef struct PlayerStateSpecialCallbacks07PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks07PointerRecord;

typedef struct PlayerStateSpecialTiming07Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming07Record;

typedef struct PlayerStateSpecialCallbacks08PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks08PointerRecord;

typedef struct PlayerStateSpecialTiming08Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming08Record;

typedef struct PlayerStateSpecialCallbacks09PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks09PointerRecord;

typedef struct PlayerStateSpecialTiming09Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming09Record;

typedef struct PlayerStateSpecialCallbacks10PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks10PointerRecord;

typedef struct PlayerStateSpecialTiming10Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming10Record;

typedef struct PlayerStateSpecialCallbacks11PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks11PointerRecord;

typedef struct PlayerStateSpecialTiming11Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming11Record;

typedef struct PlayerStateSpecialCallbacks12PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks12PointerRecord;

typedef struct PlayerStateSpecialTiming12Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming12Record;

typedef struct PlayerStateSpecialCallbacks13PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks13PointerRecord;

typedef struct PlayerStateSpecialTiming13Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming13Record;

typedef struct PlayerStateSpecialCallbacks14PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks14PointerRecord;

typedef struct PlayerStateSpecialTiming14Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming14Record;

typedef struct PlayerStateSpecialCallbacks15PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks15PointerRecord;

typedef struct PlayerStateSpecialTiming15Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming15Record;

typedef struct PlayerStateSpecialCallbacks16PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks16PointerRecord;

typedef struct PlayerStateSpecialTiming16Record {
    s32 duration;
    s32 nextAnimation;
} PlayerStateSpecialTiming16Record;

typedef struct PlayerStateSpecialCallbacks17PointerRecord {
    u32 enterAddress;
    u32 updateAddress;
} PlayerStateSpecialCallbacks17PointerRecord;

typedef struct OverlayOneFLinkRecordLinkWordsRecord {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordLinkWordsRecord;

typedef struct OverlayOneFLinkRecordLinkWordsBlock1Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock1Record;

typedef struct OverlayOneFLinkRecordConstantWordsRecord {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsRecord;

typedef struct OverlayOneFLinkRecordConstantWordsBlock1Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock1Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock2Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock2Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock2Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock2Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock3Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordLinkWordsBlock3Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock4Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock4Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock3Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock3Record;

typedef struct OverlayOneFLinkRecordSentinelWordsRecord {
    s32 endState;
} OverlayOneFLinkRecordSentinelWordsRecord;

typedef struct OverlayOneFLinkRecordConstantWordsBlock4Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock4Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock5Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock5Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock5Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock5Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock6Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock6Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock6Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock6Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock7Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock7Record;

typedef struct OverlayOneFLinkRecordSentinelWordsBlock1Record {
    s32 endState;
} OverlayOneFLinkRecordSentinelWordsBlock1Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock7Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordLinkWordsBlock7Record;

typedef struct OverlayOneFLinkRecordSentinelWordsBlock2Record {
    s32 endState;
} OverlayOneFLinkRecordSentinelWordsBlock2Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock9Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock9Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock9Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock9Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock10Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock10Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock11Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock11Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock10Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock10Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock12Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock12Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock11Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordLinkWordsBlock11Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock12Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock12Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock13Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock13Record;

typedef struct OverlayOneFLinkRecordSentinelWordsBlock3Record {
    s32 endState;
} OverlayOneFLinkRecordSentinelWordsBlock3Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock14Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock14Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock13Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock13Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock15Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock15Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock16Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock16Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock14Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock14Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock17Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock17Record;

typedef struct OverlayOneFLinkRecordSentinelWordsBlock4Record {
    s32 endState;
} OverlayOneFLinkRecordSentinelWordsBlock4Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock18Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock18Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock15Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock15Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock19Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock19Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock20Record {
    s32 state;
    u32 enterAddress;
} OverlayOneFLinkRecordConstantWordsBlock20Record;

typedef struct OverlayOneFLinkRecordLinkWordsBlock16Record {
    u32 selectorAddress;
    u32 flags;
} OverlayOneFLinkRecordLinkWordsBlock16Record;

typedef struct OverlayOneFLinkRecordConstantWordsBlock21Record {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} OverlayOneFLinkRecordConstantWordsBlock21Record;

typedef struct OverlayOneFLinkRecordSentinelWordsBlock5Record {
    s32 endState;
} OverlayOneFLinkRecordSentinelWordsBlock5Record;

typedef struct CharacterUnlocksPreviewConstantWordsRecord {
    s32 lightOffsets[4];
} CharacterUnlocksPreviewConstantWordsRecord;
typedef struct CharacterPreviewSlotRecord {
    RestBytes4 namePointer;
    s32 resource;
    s32 character;
    s32 animation;
    float scaleDistance[8];
    float positions[12];
    s32 lightOffsets[4];
} CharacterPreviewSlotRecord;













typedef struct ScenarioSetupMenuEventHandlerWords {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 event8;
    u32 widgetType8;
    u32 callbackAddress8;
    u32 event9;
    u32 widgetType9;
    u32 callbackAddress9;
    u32 event10;
    u32 widgetType10;
    u32 callbackAddress10;
    u32 event11;
    u32 widgetType11;
    u32 callbackAddress11;
    u32 eventTableTail[3];
} ScenarioSetupMenuEventHandlerWords;

typedef struct RestSlotSelectionMenuEventHandlerRecordsUsRev1Record {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 eventTableTail[3];
} RestSlotSelectionMenuEventHandlerRecordsUsRev1Record;

typedef struct RestJoinOptionsEventHandlerRecordsRecord {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 event8;
    u32 widgetType8;
    u32 callbackAddress8;
    u32 event9;
    u32 widgetType9;
    u32 callbackAddress9;
    u32 eventTableTail[5];
} RestJoinOptionsEventHandlerRecordsRecord;

typedef struct RestJoinOptionsEventHandlerRecordsRecordVariant2 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 event8;
    u32 widgetType8;
    u32 callbackAddress8;
    u32 event9;
    u32 widgetType9;
    u32 callbackAddress9;
    u32 eventTableTail[5];
} RestJoinOptionsEventHandlerRecordsRecordVariant2;

typedef struct RestJoinOptionsEventHandlerRecordsRecordVariant3 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 event8;
    u32 widgetType8;
    u32 callbackAddress8;
    u32 event9;
    u32 widgetType9;
    u32 callbackAddress9;
    u32 eventTableTail[5];
} RestJoinOptionsEventHandlerRecordsRecordVariant3;

typedef struct RestJoinOptionsEventHandlerRecordsRecordVariant4 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 event8;
    u32 widgetType8;
    u32 callbackAddress8;
    u32 event9;
    u32 widgetType9;
    u32 callbackAddress9;
    u32 eventTableTail[5];
} RestJoinOptionsEventHandlerRecordsRecordVariant4;

typedef struct RestJoinOptionsEventHandlerRecordsRecordVariant5 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 event8;
    u32 widgetType8;
    u32 callbackAddress8;
    u32 event9;
    u32 widgetType9;
    u32 callbackAddress9;
    u32 eventTableTail[5];
} RestJoinOptionsEventHandlerRecordsRecordVariant5;

typedef struct ListButtonEventHandlerRecords {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 eventTableTail[3];
} ListButtonEventHandlerRecords;

typedef struct PakActionMenuUpdateEventRecord {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
} PakActionMenuUpdateEventRecord;

typedef struct RestButtonEventHandlerRecordsUsRev1Record {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 eventTableTail[3];
} RestButtonEventHandlerRecordsUsRev1Record;

typedef struct RestPakDialogEventHandlerRecordsUsRecord {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 eventTableTail[3];
} RestPakDialogEventHandlerRecordsUsRecord;

typedef struct RestAchieveCreateResultsScreenDataRecord {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 eventTableTail[6];
} RestAchieveCreateResultsScreenDataRecord;

typedef struct RestAchieveCreateResultsScreenDataRecordVariant2 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 eventTableTail[6];
} RestAchieveCreateResultsScreenDataRecordVariant2;

typedef struct RestAchieveCreateResultsScreenDataRecordVariant3 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 eventTableTail[6];
} RestAchieveCreateResultsScreenDataRecordVariant3;

typedef struct RestAchieveCreateresultsscreenPointerTable1Record {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
} RestAchieveCreateresultsscreenPointerTable1Record;

typedef struct RestAchieveCreateresultsscreenPointerTableTailUsRecord {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 eventTableTail[6];
} RestAchieveCreateresultsscreenPointerTableTailUsRecord;

typedef struct RestFrontendPulseprofileresetwidgetPointerTable1Record {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 eventTableTail[3];
} RestFrontendPulseprofileresetwidgetPointerTable1Record;

typedef struct RestMenuCreatesoundoptionsscreenPointerTable1Record {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
} RestMenuCreatesoundoptionsscreenPointerTable1Record;

typedef struct RestMenuDispatchsettingstableeventPointerTable1Record {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 eventTableTail[3];
} RestMenuDispatchsettingstableeventPointerTable1Record;

typedef struct RestPlayerDispatchplayersettingseventPointerTable1Record {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
} RestPlayerDispatchplayersettingseventPointerTable1Record;

typedef struct RestFourPlayerResultsEventHandlersRecord {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
} RestFourPlayerResultsEventHandlersRecord;

typedef struct RestOvl1JDataRecord {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
} RestOvl1JDataRecord;

typedef struct RestEquipmentScreenEventHandlersRecord {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 eventTableTail[3];
} RestEquipmentScreenEventHandlersRecord;

typedef struct SmpFrameControllerEventRecords {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 eventTableTail[3];
} SmpFrameControllerEventRecords;

typedef struct SmpSliderListEventRecords {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
    u32 event3;
    u32 widgetType3;
    u32 callbackAddress3;
    u32 event4;
    u32 widgetType4;
    u32 callbackAddress4;
    u32 event5;
    u32 widgetType5;
    u32 callbackAddress5;
    u32 event6;
    u32 widgetType6;
    u32 callbackAddress6;
    u32 event7;
    u32 widgetType7;
    u32 callbackAddress7;
    u32 eventTableTail[3];
} SmpSliderListEventRecords;

typedef struct ScreenExtentMinusOneWords {
    s32 width;
    s32 height;
    s32 unset;
} ScreenExtentMinusOneWords;

typedef struct RestArenaCatalogueRecord { s32 arena; s32 label; s32 category; s32 index; } RestArenaCatalogueRecord;

typedef struct RestlightVolumeConeDistanceLookupLayout309 {
    float coneDistance[65];
    s32 enabled;
    s8 colorJitter[92];
    s32 state[2];
    void * actorDispatch[15];
    u32 tail[4];
} RestlightVolumeConeDistanceLookupLayout309;

typedef struct RestlightVolumeConeDistanceLookupLayout310 {
    float coneDistance[65];
    s32 enabled;
    s8 colorJitter[92];
    s32 state[2];
    void * actorDispatch[15];
    u32 tail[4];
} RestlightVolumeConeDistanceLookupLayout310;

typedef struct RestlightVolumeConeDistanceLookupLayout311 {
    float coneDistance[65];
    s32 enabled;
    s8 colorJitter[92];
    s32 state[2];
    void * actorDispatch[15];
    u32 tail[4];
} RestlightVolumeConeDistanceLookupLayout311;

typedef struct RestlightVolumeConeDistanceLookupLayout312 {
    float coneDistance[65];
    s32 enabled;
    s8 colorJitter[92];
    s32 state[2];
    void * actorDispatch[15];
    u32 tail[4];
} RestlightVolumeConeDistanceLookupLayout312;

typedef struct RestAudioFourByteDoubleConstant { double value; } __attribute__((packed, aligned(4))) RestAudioFourByteDoubleConstant;

typedef struct PlayerMovementTuningAndLookupUsRev1Layout {
    float movementScales[3];
    u32 stateMasks[9];
    float movementLimits[3];
} PlayerMovementTuningAndLookupUsRev1Layout;

typedef struct RewardItemTierPairsUsRev1Layout {
    s32 item0;
    s32 tier0;
    s32 item1;
    s32 tier1;
    s32 item2;
    s32 tier2;
    s32 item3;
    s32 tier3;
    s32 item4;
    s32 tier4;
} RewardItemTierPairsUsRev1Layout;

typedef struct DecodeEncodedWordsBlock1Layout {
    float movementScales[3];
    u32 stateMasks[9];
    float movementLimits[3];
} DecodeEncodedWordsBlock1Layout;

typedef struct LoadoutEquipmentItemsUsRev1Layout {
    s32 resourceIconAndWeapon0[3];
    void * label0;
    s32 resourceIconAndWeapon1[3];
    void * label1;
    s32 resourceIconAndWeapon2[3];
    void * label2;
} LoadoutEquipmentItemsUsRev1Layout;

typedef struct LoadoutWeaponItemsLayout {
    s32 resourceIconAndWeapon0[3];
    void * label0;
    s32 resourceIconAndWeapon1[3];
    void * label1;
    s32 resourceIconAndWeapon2[3];
    void * label2;
    s32 resourceIconAndWeapon3[3];
    void * label3;
    s32 resourceIconAndWeapon4[3];
    void * label4;
    s32 resourceIconAndWeapon5[3];
    void * label5;
    s32 resourceIconAndWeapon6[3];
    void * label6;
    s32 resourceIconAndWeapon7[3];
    void * label7;
} LoadoutWeaponItemsLayout;

typedef struct LoadoutAbilitiesItemsUsRev1Layout {
    s32 resourceIconAndWeapon0[3];
    void * label0;
    s32 resourceIconAndWeapon1[3];
    void * label1;
    s32 resourceIconAndWeapon2[3];
    void * label2;
    s32 resourceIconAndWeapon3[3];
    void * label3;
} LoadoutAbilitiesItemsUsRev1Layout;

typedef struct Ovldat2ConstantWordsLayout {
    s32 ids2[6];
    float constants[22];
    RomCallbackWord references2[300];
    RomCallbackWord *behaviorRows[14];
    char text[44];
    struct { RomCallbackWord references[4]; float constant; s32 ids[3]; } rows[13];
    RomCallbackWord references3[4];
    float constant;
    s32 ids3[10];
} Ovldat2ConstantWordsLayout;
typedef char Ovldat2ConstantWordsLayoutSizeCheck[sizeof(Ovldat2ConstantWordsLayout) == 1888 ? 1 : -1];

typedef struct GControllerpakfilenamealphabetEncodedWordsBlock1Layout {
    s32 ids[3];
} GControllerpakfilenamealphabetEncodedWordsBlock1Layout;

typedef struct SliderDimEventRecordUsRev1Layout {
    s32 id;
    void * reference;
    s32 id2;
} SliderDimEventRecordUsRev1Layout;
typedef char SliderDimEventRecordUsRev1LayoutSizeCheck[sizeof(SliderDimEventRecordUsRev1Layout) == 12 ? 1 : -1];

typedef struct AudioGlobalsTailWordsUsLayout {
    s32 ids[4];
    float constants[2];
    char text[28];
    s32 ids2[14];
} AudioGlobalsTailWordsUsLayout;

typedef struct CharacterKeyedReference {
    char character[4];
    void * reference;
} CharacterKeyedReference;
typedef char CharacterKeyedReferenceSizeCheck[sizeof(CharacterKeyedReference) == 8 ? 1 : -1];

typedef struct CharacterKeyedReferences {
    char character[4];
    void * references[4];
} CharacterKeyedReferences;
typedef char CharacterKeyedReferencesSizeCheck[sizeof(CharacterKeyedReferences) == 20 ? 1 : -1];

typedef struct CommonConstantWordsLayout {
    void * screenMessageLinks[102];
    void * energiestETextLinks;
    void * energiestE2TextLinks;
    void * schuTextLinks;
    void * schu2TextLinks;
    void * explosivgeschosseTextLinks;
    void * explosivgeschosse2TextLinks;
    void * munitionTextLinks[783];
    float constantsAt3564;
    void * referencesAt3568;
    float constantsAt3572;
    void * referencesAt3576;
    float constantsAt3580;
    void * referencesAt3584;
    float constantsAt3588;
    void * referencesAt3592;
    float constantsAt3596;
    void * referencesAt3600;
    float constantsAt3604;
    void * referencesAt3608;
    float constantsAt3612;
    void * referencesAt3616;
    float constantsAt3620;
    void * referencesAt3624;
    float constantsAt3628;
    void * referencesAt3632;
    float constantsAt3636;
    void * referencesAt3640;
    float constantsAt3644;
    void * referencesAt3648;
    float constantsAt3652;
    void * referencesAt3656;
    float constantsAt3660;
    void * referencesAt3664;
    float constantsAt3668;
    void * referencesAt3672;
    float constantsAt3676;
    void * referencesAt3680;
    u32 packedValueAt3684;
    void * referencesAt3688;
    u32 packedValueAt3692;
    void * referencesAt3696;
    u32 packedValueAt3700;
    void * referencesAt3704;
    u32 packedValueAt3708;
    void * referencesAt3712;
    u32 packedValueAt3716;
    void * referencesAt3720;
    u32 packedValueAt3724;
    void * referencesAt3728;
    u32 packedValueAt3732;
    void * referencesAt3736;
    u32 packedValueAt3740;
    void * referencesAt3744;
    u32 packedValueAt3748;
    void * referencesAt3752;
    u32 packedValueAt3756;
    void * referencesAt3760;
    u32 packedValueAt3764;
    void * referencesAt3768;
    u32 packedValueAt3772;
    void * referencesAt3776;
    u32 packedValueAt3780;
    void * referencesAt3784;
    u32 packedValueAt3788;
    void * referencesAt3792;
    u32 packedValueAt3796;
    void * referencesAt3800;
    u32 packedValueAt3804;
    void * referencesAt3808;
    u32 packedValueAt3812;
    void * referencesAt3816;
    u32 packedValueAt3820;
    void * referencesAt3824;
    u32 packedValueAt3828;
    void * referencesAt3832;
    float constantsAt3836;
    void * referencesAt3840;
    float constantsAt3844;
    void * referencesAt3848;
    u32 packedValueAt3852;
    void * referencesAt3856;
    u32 packedValueAt3860;
    void * referencesAt3864;
    u32 packedValueAt3868;
    void * referencesAt3872[9];
} CommonConstantWordsLayout;
typedef char CommonConstantWordsLayoutSizeCheck[sizeof(CommonConstantWordsLayout) == 3908 ? 1 : -1];

typedef struct CommonEncodedWordsLayout {
    void * audioGlobals;
    s32 reverbParameters[103];
    s16 sineCoefficients[128];
    u32 libraryStateAndFill[27];
} CommonEncodedWordsLayout;

typedef struct CommonEncodedWordsBlock1Layout {
    char text[8];
    float constants[60];
    void * references[21];
    float constants2[19];
} CommonEncodedWordsBlock1Layout;
typedef char CommonEncodedWordsBlock1LayoutSizeCheck[sizeof(CommonEncodedWordsBlock1Layout) == 408 ? 1 : -1];
extern CommonEncodedWordsBlock1Layout k_commonFragment;

typedef struct RestaudioGlobalsLayout302 {
    void * audioGlobals;
    s32 reverbParameters[103];
    s16 sineCoefficients[128];
    u32 libraryStateAndFill[27];
} RestaudioGlobalsLayout302;

typedef struct RestaudioGlobalsLayout303 {
    void * audioGlobals;
    s32 reverbParameters[103];
    s16 sineCoefficients[128];
    u32 libraryStateAndFill[27];
} RestaudioGlobalsLayout303;

typedef struct FrontendShutdownWritableWordsLayout {
    s32 ids[6];
    char text[8];
    float constants[60];
    void * references[21];
    float constants2[19];
} FrontendShutdownWritableWordsLayout;
typedef char FrontendShutdownWritableWordsLayoutSizeCheck[sizeof(FrontendShutdownWritableWordsLayout) == 432 ? 1 : -1];

typedef struct CurveDecodethreebitsamplesEncodedWordsLayout313 {
    s32 ids[8];
    void * references[10];
    s32 ids2[2];
} CurveDecodethreebitsamplesEncodedWordsLayout313;
typedef char CurveDecodethreebitsamplesEncodedWordsLayout313SizeCheck[sizeof(CurveDecodethreebitsamplesEncodedWordsLayout313) == 80 ? 1 : -1];

typedef struct CurveDecodethreebitsamplesEncodedWordsLayout314 {
    s32 ids[8];
    void * references[10];
    s32 id;
    char text[4];
} CurveDecodethreebitsamplesEncodedWordsLayout314;
typedef char CurveDecodethreebitsamplesEncodedWordsLayout314SizeCheck[sizeof(CurveDecodethreebitsamplesEncodedWordsLayout314) == 80 ? 1 : -1];

typedef struct CurveDecodethreebitsamplesEncodedWordsLayout315 {
    s32 ids[8];
    void * references[10];
    s32 id;
    float constant;
} CurveDecodethreebitsamplesEncodedWordsLayout315;
typedef char CurveDecodethreebitsamplesEncodedWordsLayout315SizeCheck[sizeof(CurveDecodethreebitsamplesEncodedWordsLayout315) == 80 ? 1 : -1];

typedef struct CurveDecodethreebitsamplesEncodedWordsLayout316 {
    s32 ids[8];
    void * references[10];
    s32 id;
    char text[4];
} CurveDecodethreebitsamplesEncodedWordsLayout316;
typedef char CurveDecodethreebitsamplesEncodedWordsLayout316SizeCheck[sizeof(CurveDecodethreebitsamplesEncodedWordsLayout316) == 80 ? 1 : -1];

typedef struct CurveDecodethreebitsamplesEncodedWordsLayout317 {
    s32 ids[8];
    void * references[10];
    s32 id;
} CurveDecodethreebitsamplesEncodedWordsLayout317;
typedef char CurveDecodethreebitsamplesEncodedWordsLayout317SizeCheck[sizeof(CurveDecodethreebitsamplesEncodedWordsLayout317) == 76 ? 1 : -1];

typedef struct DisplayListCommandWords {
    u32 command;
    u32 argument;
} DisplayListCommandWords;
typedef char DisplayListCommandWordsSizeCheck[sizeof(DisplayListCommandWords) == 8 ? 1 : -1];

typedef struct EventsDelivercontacteffectWords2Layout {
    DisplayListCommandWords commands[17];
} EventsDelivercontacteffectWords2Layout;
typedef char EventsDelivercontacteffectWords2LayoutSizeCheck[sizeof(EventsDelivercontacteffectWords2Layout) == 136 ? 1 : -1];

typedef struct EffectCallbackFlagsLayout {
    struct { void * handler; u32 flags; } entries[37]; /* ContactEffectEntry, read by events.cpp */
} EffectCallbackFlagsLayout;
typedef char EffectCallbackFlagsLayoutSizeCheck[sizeof(EffectCallbackFlagsLayout) == 296 ? 1 : -1];

typedef struct RestemacTextLayout324 {
    s32 ids[2];
    float constants[3];
    s32 ids2[2];
} RestemacTextLayout324;
typedef char RestemacTextLayout324SizeCheck[sizeof(RestemacTextLayout324) == 28 ? 1 : -1];

typedef struct RestemacTextLayout325 {
    s32 ids[2];
    float constants[3];
    s32 ids2[2];
} RestemacTextLayout325;
typedef char RestemacTextLayout325SizeCheck[sizeof(RestemacTextLayout325) == 28 ? 1 : -1];

typedef struct RestemacTextLayout326 {
    s32 ids[2];
    float constants[3];
    s32 id;
    char text[4];
} RestemacTextLayout326;
typedef char RestemacTextLayout326SizeCheck[sizeof(RestemacTextLayout326) == 28 ? 1 : -1];

typedef struct MinigunTextLayout {
    s32 ids[2];
    void * references[15];
    char text[12];
    float constant;
} MinigunTextLayout;
typedef char MinigunTextLayoutSizeCheck[sizeof(MinigunTextLayout) == 84 ? 1 : -1];

typedef struct PakAdjustownernotificationoptionDataConstantWordsLayout {
    void * references[891];
    CharacterKeyedReference characterEntries[39];
    void * references2[6];
    u32 packedValue2;
    char text[8];
} PakAdjustownernotificationoptionDataConstantWordsLayout;
typedef char PakAdjustownernotificationoptionDataConstantWordsLayoutSizeCheck[sizeof(PakAdjustownernotificationoptionDataConstantWordsLayout) == 3912 ? 1 : -1];

typedef struct SmackFormatTableLayoutA {
    s32 ids[11];
    float constant;
    s32 id;
    u32 packedValues[2];
    s32 id2;
} SmackFormatTableLayoutA;
typedef char SmackFormatTableLayoutASizeCheck[sizeof(SmackFormatTableLayoutA) == 64 ? 1 : -1];

typedef struct SmackFormatTableLayoutB {
    s32 ids[13];
    float constants[3];
} SmackFormatTableLayoutB;
typedef char SmackFormatTableLayoutBSizeCheck[sizeof(SmackFormatTableLayoutB) == 64 ? 1 : -1];

typedef struct SmackFormatTableLayoutC {
    s32 ids[11];
    char text[4];
    s32 id;
    char text2[12];
} SmackFormatTableLayoutC;
typedef char SmackFormatTableLayoutCSizeCheck[sizeof(SmackFormatTableLayoutC) == 64 ? 1 : -1];

typedef struct SmackFormatTableLayoutD {
    s32 ids[13];
    char text[12];
} SmackFormatTableLayoutD;
typedef char SmackFormatTableLayoutDSizeCheck[sizeof(SmackFormatTableLayoutD) == 64 ? 1 : -1];

typedef struct SmackFormatTableAltLayout {
    s32 ids[11];
    char text[4];
    s32 id;
    char text2[12];
} SmackFormatTableAltLayout;
typedef char SmackFormatTableAltLayoutSizeCheck[sizeof(SmackFormatTableAltLayout) == 64 ? 1 : -1];

typedef struct XplusNextrandomintegerEncodedWordsLayout {
    s32 id;
    char text[4];
} XplusNextrandomintegerEncodedWordsLayout;
typedef char XplusNextrandomintegerEncodedWordsLayoutSizeCheck[sizeof(XplusNextrandomintegerEncodedWordsLayout) == 8 ? 1 : -1];

typedef struct XplusSeedRandomGeneratorWordsDeLayout {
    s32 id;
    u32 packedValue;
    s32 ids[3];
    u32 packedValue2;
    s32 ids2[22];
    float constants[10];
    s32 ids3[2];
} XplusSeedRandomGeneratorWordsDeLayout;
typedef char XplusSeedRandomGeneratorWordsDeLayoutSizeCheck[sizeof(XplusSeedRandomGeneratorWordsDeLayout) == 160 ? 1 : -1];

typedef struct XPlusWritableWords_us_rev1Layout {
    s32 ids[10];
    float constants[10];
} XPlusWritableWords_us_rev1Layout;
typedef char XPlusWritableWords_us_rev1LayoutSizeCheck[sizeof(XPlusWritableWords_us_rev1Layout) == 80 ? 1 : -1];

typedef struct XPlusWritableWords_usLayout {
    s32 id;
    char text[8];
    u32 packedValue;
    s32 id2;
    u32 packedValue2;
    s32 ids[15];
    char text2[28];
    float constants[10];
    s32 ids2[2];
} XPlusWritableWords_usLayout;
typedef char XPlusWritableWords_usLayoutSizeCheck[sizeof(XPlusWritableWords_usLayout) == 160 ? 1 : -1];

typedef struct MaterialPlusModeConstantsUsRev1Layout {
    u32 colorMasks[4];
} MaterialPlusModeConstantsUsRev1Layout;
typedef char MaterialPlusModeConstantsUsRev1LayoutSizeCheck[sizeof(MaterialPlusModeConstantsUsRev1Layout) == 16 ? 1 : -1];

typedef struct RestConstantsData {
    s32 id;
    char text[4];
    u32 packedValue;
    s32 ids[3];
} RestConstantsData;
typedef char RestConstantsDataSizeCheck[sizeof(RestConstantsData) == 24 ? 1 : -1];

typedef struct ConstantsEncodedWordsBlock1Layout {
    u32 packedValue;
    s32 id;
    u32 packedValue2;
    float constants[3];
} ConstantsEncodedWordsBlock1Layout;
typedef char ConstantsEncodedWordsBlock1LayoutSizeCheck[sizeof(ConstantsEncodedWordsBlock1Layout) == 24 ? 1 : -1];

typedef struct PlayerActionStateRecord {
    void * enterCallback;
    void * updateCallback;
    void * enterTarget;
    u32 enterMask;
    s32 actionId;
    u32 modeFlags;
} PlayerActionStateRecord;
typedef char PlayerActionStateRecordSizeCheck[sizeof(PlayerActionStateRecord) == 24 ? 1 : -1];

typedef struct PlayerActionStateTableWordsUsLayout {
    s32 id;
    float constants[21];
    PlayerActionStateRecord states[94];
    s32 trailingId;
    u32 trailingHalfwordPairs[5];
    float trailingConstant;
} PlayerActionStateTableWordsUsLayout;
typedef char PlayerActionStateTableWordsUsLayoutSizeCheck[sizeof(PlayerActionStateTableWordsUsLayout) == 2372 ? 1 : -1];

typedef struct SceneEffectTuningUsRev1Layout {
    float constants[60];
    s32 id;
    float constants2[8];
    PlayerActionStateTableWordsUsLayout playerActionStates;
} SceneEffectTuningUsRev1Layout;
typedef char SceneEffectTuningUsRev1LayoutSizeCheck[sizeof(SceneEffectTuningUsRev1Layout) == 2648 ? 1 : -1];

typedef struct SceneEffectLookupWordsEuEncodedHalfwordsLayout {
    float constants[2];
    s32 ids2[45];
    float constants2[22];
    s32 ids3[300];
    void * references[14];
    float constants3[11];
    s32 ids4[4];
    struct { float constant; s32 ids[7]; } rows[13];
    float constant;
    s32 ids5[58];
    struct { u32 packedValue; s32 id; } packedValueIdRows[6];
    float constant2;
    s32 id;
    void * reference;
    s32 ids6[7];
    float constants4[2];
    s32 ids7[8];
    float constants5[3];
} SceneEffectLookupWordsEuEncodedHalfwordsLayout;
typedef char SceneEffectLookupWordsEuEncodedHalfwordsLayoutSizeCheck[sizeof(SceneEffectLookupWordsEuEncodedHalfwordsLayout) == 2384 ? 1 : -1];

typedef struct SceneEffectTuningDeLayout {
    float constants[3];
    s32 id;
} SceneEffectTuningDeLayout;
typedef char SceneEffectTuningDeLayoutSizeCheck[sizeof(SceneEffectTuningDeLayout) == 16 ? 1 : -1];

typedef struct GeometryDrawResourceModelWritableWords_euLayout {
    s32 ids[10];
    float constants[10];
} GeometryDrawResourceModelWritableWords_euLayout;
typedef char GeometryDrawResourceModelWritableWords_euLayoutSizeCheck[sizeof(GeometryDrawResourceModelWritableWords_euLayout) == 80 ? 1 : -1];

typedef struct GeometryDrawresourcemodelEncodedWordsBlock2Layout {
    float constants[2];
    u32 packedValue;
    s32 id;
} GeometryDrawresourcemodelEncodedWordsBlock2Layout;
typedef char GeometryDrawresourcemodelEncodedWordsBlock2LayoutSizeCheck[sizeof(GeometryDrawresourcemodelEncodedWordsBlock2Layout) == 16 ? 1 : -1];

typedef struct GeometryDrawresourcemodelEncodedWordsLayout {
    MemoryBoundary boundaries[10];
    s32 lastMappedSlot;
    u32 retainedInstructionWord;
} GeometryDrawresourcemodelEncodedWordsLayout;
typedef char GeometryDrawresourcemodelEncodedWordsLayoutSizeCheck[sizeof(GeometryDrawresourcemodelEncodedWordsLayout) == 88 ? 1 : -1];


/* eu resource model colour masks: two 0xA0000000 words, then the two 0x00FF0000 red channel masks. */
typedef struct ResourceModelColorMasksLayout {
    u32 firstCommand;
    u32 secondCommand;
    s32 colorMasks[2];
} ResourceModelColorMasksLayout;

typedef struct VideoScaleUnsignedBias_StorageWordsLayout {
    float constants[3];
} VideoScaleUnsignedBias_StorageWordsLayout;

typedef struct PlayerControllerStateAndTuningWordsUsLayout {
    s32 ids[6];
    char text[4];
    s32 ids2[9];
    float constants[3];
} PlayerControllerStateAndTuningWordsUsLayout;
typedef char PlayerControllerStateAndTuningWordsUsLayoutSizeCheck[sizeof(PlayerControllerStateAndTuningWordsUsLayout) == 76 ? 1 : -1];

typedef struct PlayerControllerStateHeaderUsRev1Layout {
    s32 ids[2];
    float constant;
    s32 ids2[2];
} PlayerControllerStateHeaderUsRev1Layout;

typedef struct PlayerControllerStateHeaderAlternateUsRev1Layout {
    s32 ids[2];
    float constant;
    s32 ids2[2];
} PlayerControllerStateHeaderAlternateUsRev1Layout;

typedef struct WeaponControllerAndMovementTuningUsRev1Layout {
    s32 ids[2];
    void * reference;
    s32 ids2[8];
    float constants[3];
} WeaponControllerAndMovementTuningUsRev1Layout;
typedef char WeaponControllerAndMovementTuningUsRev1LayoutSizeCheck[sizeof(WeaponControllerAndMovementTuningUsRev1Layout) == 56 ? 1 : -1];

typedef struct ConstantsEncodedWordsBlock11Layout {
    s32 ids[2];
    float constants[2];
    void * references[3];
} ConstantsEncodedWordsBlock11Layout;

typedef struct ConstantsEncodedWordsBlock13Layout {
    s32 ids[2];
    float constants[2];
    void * references[3];
} ConstantsEncodedWordsBlock13Layout;

typedef struct ConstantsEncodedWordsBlock15Layout {
    s32 ids[2];
    float constants[2];
    void * references[3];
} ConstantsEncodedWordsBlock15Layout;

typedef struct ConstantsEncodedWordsBlock17Layout {
    s32 ids[2];
    float constants[2];
    void * references[3];
} ConstantsEncodedWordsBlock17Layout;

typedef struct ConstantsEncodedWordsBlock19Layout {
    s32 ids[2];
    float constants[2];
    void * references[3];
} ConstantsEncodedWordsBlock19Layout;

typedef struct ConstantsEncodedWordsBlock21Layout {
    s32 ids[2];
    float constants[2];
    void * references[3];
} ConstantsEncodedWordsBlock21Layout;

typedef struct ConstantsEncodedWordsBlock7Layout {
    s32 ids[2];
    float constants[2];
    void * references[3];
} ConstantsEncodedWordsBlock7Layout;

typedef struct ConstantsEncodedWordsBlock9Layout {
    s32 ids[2];
    float constants[2];
    void * references[3];
} ConstantsEncodedWordsBlock9Layout;

typedef struct RestConstantsDataVariant2 {
    char text[4];
    u32 packedValue;
    s32 ids[3];
    u32 packedValue2;
    void * references[4];
    s32 ids2[5];
    u32 packedValues[2];
    float constant;
    s32 ids3[6];
    u32 packedValues2[3];
    void * reference;
    s32 ids4[8];
    u32 packedValues3[3];
    float constants[61];
} RestConstantsDataVariant2;
typedef char RestConstantsDataVariant2SizeCheck[sizeof(RestConstantsDataVariant2) == 400 ? 1 : -1];

typedef struct ConstantsEncodedWordsBlock14Layout {
    u32 packedValues[3];
} ConstantsEncodedWordsBlock14Layout;
typedef char ConstantsEncodedWordsBlock14LayoutSizeCheck[sizeof(ConstantsEncodedWordsBlock14Layout) == 12 ? 1 : -1];

typedef struct OsstartthreadEncodedWordsLayout {
    void * references[4];
    char text[4];
    float constant;
} OsstartthreadEncodedWordsLayout;

typedef struct CharacterPreviewDefinitionsDataLayout {
    float constants3[13];
    struct { s32 ids1[2]; void * reference; s32 ids2[3]; float constants[22]; } rows[2];
    s32 ids5[2];
    void * reference;
    s32 ids6[3];
    float constants4[20];
    s32 ids7[4];
    struct { void * reference; s32 ids1[3]; float constants[22]; s32 ids2[2]; } referenceIdConstantRows[13];
    void * reference2;
    s32 ids8[68];
} CharacterPreviewDefinitionsDataLayout;
typedef char CharacterPreviewDefinitionsDataLayoutSizeCheck[sizeof(CharacterPreviewDefinitionsDataLayout) == 2128 ? 1 : -1];

typedef struct CharacterPreviewDefinitionsEuXLayout {
    s32 ids5[4];
    struct { void * name; s32 resource; s32 character; s32 animation; float scaleDistance[8]; float positions[12]; s32 lightOffsets[4]; } profiles[16]; /* CharacterPreviewProfile */
    void * reference2;
    s32 ids8[68];
} CharacterPreviewDefinitionsEuXLayout;
typedef char CharacterPreviewDefinitionsEuXLayoutSizeCheck[sizeof(CharacterPreviewDefinitionsEuXLayout) == 2084 ? 1 : -1];

typedef struct CharacterPreviewDefinitionsEuLayout {
    s32 ids5[4];
    struct { void * name; s32 resource; s32 character; s32 animation; float scaleDistance[8]; float positions[12]; s32 lightOffsets[4]; } profiles[16]; /* CharacterPreviewProfile */
    void * reference2;
    s32 ids8[66];
    u32 packedValue;
    s32 id;
} CharacterPreviewDefinitionsEuLayout;
typedef char CharacterPreviewDefinitionsEuLayoutSizeCheck[sizeof(CharacterPreviewDefinitionsEuLayout) == 2084 ? 1 : -1];

typedef struct CharacterPreviewEntryKeysUsRev1Layout {
    s32 ids[2];
} CharacterPreviewEntryKeysUsRev1Layout;
typedef char CharacterPreviewEntryKeysUsRev1LayoutSizeCheck[sizeof(CharacterPreviewEntryKeysUsRev1Layout) == 8 ? 1 : -1];

typedef struct CharacterPreviewEntryStateUsRev1Layout {
    s32 id;
} CharacterPreviewEntryStateUsRev1Layout;
typedef char CharacterPreviewEntryStateUsRev1LayoutSizeCheck[sizeof(CharacterPreviewEntryStateUsRev1Layout) == 4 ? 1 : -1];

typedef struct RestFrontendAnimateslotselectionmenuData {
    struct { s32 textId; void * text; } textEntries[50];
    s32 ids[62];
    struct { s32 rank; void * rankName; } rankNameLists[3][17];
    void * references[3];
} RestFrontendAnimateslotselectionmenuData;
typedef char RestFrontendAnimateslotselectionmenuDataSizeCheck[sizeof(RestFrontendAnimateslotselectionmenuData) == 1068 ? 1 : -1];

typedef struct RestFrontendAnimateslotselectionmenuDataVariant2 {
    struct { s32 textId; void * text; } textEntries[50];
    s32 ids[62];
    struct { s32 rank; void * rankName; } rankNameLists[3][17];
    void * references[3];
} RestFrontendAnimateslotselectionmenuDataVariant2;
typedef char RestFrontendAnimateslotselectionmenuDataVariant2SizeCheck[sizeof(RestFrontendAnimateslotselectionmenuDataVariant2) == 1068 ? 1 : -1];

typedef struct RestFrontendAnimateslotselectionmenuDataVariant3 {
    struct { s32 textId; void * text; } textEntries[50];
    s32 ids[62];
    struct { s32 rank; void * rankName; } rankNameLists[3][17];
    void * references[3];
} RestFrontendAnimateslotselectionmenuDataVariant3;
typedef char RestFrontendAnimateslotselectionmenuDataVariant3SizeCheck[sizeof(RestFrontendAnimateslotselectionmenuDataVariant3) == 1068 ? 1 : -1];

typedef struct RestFrontendAnimateslotselectionmenuDataVariant4 {
    struct { s32 textId; void * text; } textEntries[50];
    s32 ids[62];
    struct { s32 rank; void * rankName; } rankNameLists[3][17];
    void * references[3];
} RestFrontendAnimateslotselectionmenuDataVariant4;
typedef char RestFrontendAnimateslotselectionmenuDataVariant4SizeCheck[sizeof(RestFrontendAnimateslotselectionmenuDataVariant4) == 1068 ? 1 : -1];

typedef struct SlotSelectionLabelIdPointerPairsUsRev1Layout {
    struct { s32 id; void * reference; } records[50];
} SlotSelectionLabelIdPointerPairsUsRev1Layout;
typedef char SlotSelectionLabelIdPointerPairsUsRev1LayoutSizeCheck[sizeof(SlotSelectionLabelIdPointerPairsUsRev1Layout) == 400 ? 1 : -1];

typedef struct SlotSelectionLabel {
    s32 id;
    void *reference;
} SlotSelectionLabel;

/* Slot-selection label table of eu, eu-x and us (us-rev1 keeps its 50 pairs only). */
typedef struct SlotSelectionLabelTable {
    SlotSelectionLabel labels[50];
    s32 menuEventWords[63];
    void *menuEventReference;
    SlotSelectionLabel rankLabels[15];
    s32 rankListId;
    void *rankListReferences[3];
    SlotSelectionLabel achievementLabels[15];
    s32 achievementListId;
    void *achievementListReferences[3];
    SlotSelectionLabel optionLabels[15];
    s32 optionListId;
    void *optionListReferences[4];
} SlotSelectionLabelTable;
typedef char SlotSelectionLabelTableSizeCheck[sizeof(SlotSelectionLabelTable) == 0x42C ? 1 : -1];

typedef struct JoinOptionsTrailingWordsLayout {
    s32 ids[3];
    float constants[4];
} JoinOptionsTrailingWordsLayout;
typedef char JoinOptionsTrailingWordsLayoutSizeCheck[sizeof(JoinOptionsTrailingWordsLayout) == 28 ? 1 : -1];

typedef struct JoinOptionsTrailingWords_eu_xLayout {
    s32 ids[3];
    float constants[4];
} JoinOptionsTrailingWords_eu_xLayout;
typedef char JoinOptionsTrailingWords_eu_xLayoutSizeCheck[sizeof(JoinOptionsTrailingWords_eu_xLayout) == 28 ? 1 : -1];

typedef struct JoinOptionsTrailingWords_deLayout {
    s32 ids[3];
    float constants[4];
} JoinOptionsTrailingWords_deLayout;
typedef char JoinOptionsTrailingWords_deLayoutSizeCheck[sizeof(JoinOptionsTrailingWords_deLayout) == 28 ? 1 : -1];

typedef struct ButtonWidgetHandlerTailUsRev1Layout {
    struct { void * reference; s32 ids[2]; } rows[8];
    void * references[4];
    s32 id;
} ButtonWidgetHandlerTailUsRev1Layout;
typedef char ButtonWidgetHandlerTailUsRev1LayoutSizeCheck[sizeof(ButtonWidgetHandlerTailUsRev1Layout) == 116 ? 1 : -1];

typedef struct RestSmpOverlayDispatchPakDialogEventDataLayout455 {
    s32 ids[21];
    u32 packedValues[2];
    float constants[2];
    s32 ids2[2];
    void * reference;
    s32 id;
} RestSmpOverlayDispatchPakDialogEventDataLayout455;
typedef char RestSmpOverlayDispatchPakDialogEventDataLayout455SizeCheck[sizeof(RestSmpOverlayDispatchPakDialogEventDataLayout455) == 116 ? 1 : -1];

typedef struct RestSmpOverlayDispatchPakDialogEventDataLayout456 {
    s32 ids[21];
    u32 packedValues[2];
    float constants[2];
    s32 ids2[2];
    float constant;
    u32 packedValue;
} RestSmpOverlayDispatchPakDialogEventDataLayout456;
typedef char RestSmpOverlayDispatchPakDialogEventDataLayout456SizeCheck[sizeof(RestSmpOverlayDispatchPakDialogEventDataLayout456) == 116 ? 1 : -1];

typedef struct RestSmpOverlayDispatchPakDialogEventDataLayout457 {
    s32 ids[21];
    u32 packedValues[2];
    float constants[2];
    s32 ids2[4];
} RestSmpOverlayDispatchPakDialogEventDataLayout457;
typedef char RestSmpOverlayDispatchPakDialogEventDataLayout457SizeCheck[sizeof(RestSmpOverlayDispatchPakDialogEventDataLayout457) == 116 ? 1 : -1];

typedef struct PakDialogStyleAndTextWords_usLayout {
    u32 packedValues[2];
    float constants[2];
    s32 ids[2];
    char text[8];
} PakDialogStyleAndTextWords_usLayout;
typedef char PakDialogStyleAndTextWords_usLayoutSizeCheck[sizeof(PakDialogStyleAndTextWords_usLayout) == 32 ? 1 : -1];

typedef struct RestEncodedInserttextentrycharacterHalfwords {
    s32 ids2[6];
    void * reference;
    char text[20];
    void * reference2;
    char text2[24];
    void * references[10];
    s32 id;
    u32 packedValue;
    s32 ids3[8];
    u32 packedValue2;
    s32 ids4[2];
    struct { void * reference; s32 ids[8]; } rows[3];
    void * reference3;
    s32 ids5[4];
    void * reference4;
    s32 ids6[28];
} RestEncodedInserttextentrycharacterHalfwords;
typedef char RestEncodedInserttextentrycharacterHalfwordsSizeCheck[sizeof(RestEncodedInserttextentrycharacterHalfwords) == 412 ? 1 : -1];

typedef struct RestEncodedInserttextentrycharacterHalfwordsVariant2 {
    s32 ids2[6];
    void * references[4];
    char text[20];
    void * references2[4];
    char text2[24];
    void * references3[24];
    s32 id;
    u32 packedValue;
    s32 ids3[8];
    u32 packedValue2;
    s32 ids4[2];
    void * reference;
    s32 ids5[8];
    void * reference2;
    struct { s32 ids[8]; void * reference; } rows[2];
    s32 ids6[4];
    void * reference3;
    s32 ids7[28];
} RestEncodedInserttextentrycharacterHalfwordsVariant2;
typedef char RestEncodedInserttextentrycharacterHalfwordsVariant2SizeCheck[sizeof(RestEncodedInserttextentrycharacterHalfwordsVariant2) == 492 ? 1 : -1];

typedef struct RestEncodedInserttextentrycharacterHalfwordsVariant3 {
    s32 ids2[6];
    void * references[4];
    char text[20];
    void * references2[4];
    char text2[24];
    void * references3[24];
    s32 id;
    u32 packedValue;
    s32 ids3[8];
    u32 packedValue2;
    s32 ids4[2];
    void * reference;
    s32 ids5[8];
    void * reference2;
    struct { s32 ids[8]; void * reference; } rows[2];
    s32 ids6[4];
    void * reference3;
    s32 ids7[28];
} RestEncodedInserttextentrycharacterHalfwordsVariant3;
typedef char RestEncodedInserttextentrycharacterHalfwordsVariant3SizeCheck[sizeof(RestEncodedInserttextentrycharacterHalfwordsVariant3) == 492 ? 1 : -1];

typedef struct RestEncodedInserttextentrycharacterHalfwordsVariant4 {
    s32 ids2[6];
    void * reference;
    char text[20];
    void * reference2;
    char text2[24];
    void * reference3;
    char text3[4];
    void * references[8];
    s32 id;
    u32 packedValue;
    s32 ids3[8];
    u32 packedValue2;
    s32 ids4[2];
    struct { void * reference; s32 ids[8]; } rows[3];
    void * reference4;
    s32 ids5[4];
    void * reference5;
    s32 ids6[28];
} RestEncodedInserttextentrycharacterHalfwordsVariant4;
typedef char RestEncodedInserttextentrycharacterHalfwordsVariant4SizeCheck[sizeof(RestEncodedInserttextentrycharacterHalfwordsVariant4) == 412 ? 1 : -1];

typedef struct RestFrontendPulseProfileResetWidgetData {
    EventHandlerRecord profileResetHandlers[7];
    u32 retainedDispatchWords[2];
    EventHandlerRecord nodePairHandlers[4];
} RestFrontendPulseProfileResetWidgetData;
typedef char RestFrontendPulseProfileResetWidgetDataSizeCheck[sizeof(RestFrontendPulseProfileResetWidgetData) == 140 ? 1 : -1];

typedef struct RestFrontendPulseProfileResetWidgetDataVariant2 {
    s32 ids[21];
    u32 packedValues[2];
    s32 ids2[12];
} RestFrontendPulseProfileResetWidgetDataVariant2;
typedef char RestFrontendPulseProfileResetWidgetDataVariant2SizeCheck[sizeof(RestFrontendPulseProfileResetWidgetDataVariant2) == 140 ? 1 : -1];

typedef struct FrontendPulseprofileresetwidgetPointerWordsTailUsLayout {
    u32 packedValue;
    char text[4];
    s32 ids[12];
} FrontendPulseprofileresetwidgetPointerWordsTailUsLayout;
typedef char FrontendPulseprofileresetwidgetPointerWordsTailUsLayoutSizeCheck[sizeof(FrontendPulseprofileresetwidgetPointerWordsTailUsLayout) == 56 ? 1 : -1];

typedef struct RestGMenuboxcornersWords1 {
    s32 id;
    char text[28];
    u32 packedValue;
    float constant;
    s32 id2;
} RestGMenuboxcornersWords1;
typedef char RestGMenuboxcornersWords1SizeCheck[sizeof(RestGMenuboxcornersWords1) == 44 ? 1 : -1];

typedef struct RestGMenuboxcornersWords1Variant2 {
    s32 id;
    char text[28];
    u32 packedValue;
    s32 ids[2];
} RestGMenuboxcornersWords1Variant2;
typedef char RestGMenuboxcornersWords1Variant2SizeCheck[sizeof(RestGMenuboxcornersWords1Variant2) == 44 ? 1 : -1];

typedef struct RestGMenuboxcornersWords1Variant3 {
    s32 id;
    char text[32];
    u32 packedValue;
    s32 id2;
} RestGMenuboxcornersWords1Variant3;
typedef char RestGMenuboxcornersWords1Variant3SizeCheck[sizeof(RestGMenuboxcornersWords1Variant3) == 44 ? 1 : -1];

typedef struct RestGMenuboxcornersWords1Variant4 {
    s32 id;
    char text[36];
    s32 id2;
} RestGMenuboxcornersWords1Variant4;
typedef char RestGMenuboxcornersWords1Variant4SizeCheck[sizeof(RestGMenuboxcornersWords1Variant4) == 44 ? 1 : -1];

typedef struct RestGMenuboxcornersWords1Variant5 {
    s32 id;
    char text[36];
    s32 id2;
} RestGMenuboxcornersWords1Variant5;
typedef char RestGMenuboxcornersWords1Variant5SizeCheck[sizeof(RestGMenuboxcornersWords1Variant5) == 44 ? 1 : -1];

typedef struct RestMenuBoxCornersData {
    s32 id;
    float constants3[4];
    struct { u32 packedValue1; char text1[4]; s32 id; float constants1[4]; u32 packedValue2; char text2[12]; float constants2[3]; } rows[2];
    s32 id2;
    char text[4];
    s32 id3;
    float constants4[4];
    u32 packedValue;
    char text2[8];
    float constants5[4];
    u32 packedValue2;
    char text3[4];
    s32 id4;
    float constants6[4];
    u32 packedValue3;
    s32 ids[2];
    float constants7[4];
    u32 packedValue4;
    char text4[4];
} RestMenuBoxCornersData;
typedef char RestMenuBoxCornersDataSizeCheck[sizeof(RestMenuBoxCornersData) == 252 ? 1 : -1];

typedef struct GMenuboxcornersLevelTextWords1Layout {
    s32 ids[2];
    float constant;
    char text[28];
    struct { void * reference; char text[24]; } rows[3];
    void * reference;
    u32 packedValue;
    u32 packedValues[11];
    void * reference2;
} GMenuboxcornersLevelTextWords1Layout;
typedef char GMenuboxcornersLevelTextWords1LayoutSizeCheck[sizeof(GMenuboxcornersLevelTextWords1Layout) == 180 ? 1 : -1];

typedef struct RestMenuBoxCornersDataVariant2 {
    s32 id;
    float constants2[4];
    u32 packedValue;
    char text[4];
    s32 id2;
    char text2[12];
    float constant;
    u32 packedValue2;
    char text3[12];
    float constants3[3];
    u32 packedValue3;
    char text4[4];
    s32 id3;
    float constants4[4];
    u32 packedValue4;
    char text5[12];
    float constants5[3];
    s32 id4;
    struct { char text[8]; float constants[4]; u32 packedValue; } rows[2];
    char text6[4];
    s32 id5;
    float constants6[4];
    u32 packedValue5;
    s32 ids[2];
    float constants7[4];
    u32 packedValue6;
    char text7[4];
} RestMenuBoxCornersDataVariant2;
typedef char RestMenuBoxCornersDataVariant2SizeCheck[sizeof(RestMenuBoxCornersDataVariant2) == 252 ? 1 : -1];

typedef struct GMenuboxcornersOurclevelTextWords1Layout {
    s32 ids[2];
    float constant;
    char text[28];
    struct { void * reference; char text[24]; } rows[3];
    void * reference;
    u32 packedValue;
    u32 packedValues[11];
    void * reference2;
} GMenuboxcornersOurclevelTextWords1Layout;
typedef char GMenuboxcornersOurclevelTextWords1LayoutSizeCheck[sizeof(GMenuboxcornersOurclevelTextWords1Layout) == 180 ? 1 : -1];

/* Menu_MeasureMenuText reads width/height; Menu_DrawStyledMenuText reads scale, text and shadow colors. */
typedef struct MenuFontStyleRecord {
    s32 kind;
    float width;
    float height;
    float scaleX;
    float scaleY;
    u8 shadowOffset;
    u8 textColor[3];
    u8 shadowColor[3];
    u8 alignmentPadding;
} MenuFontStyleRecord;
typedef char MenuFontStyleRecordSizeCheck[sizeof(MenuFontStyleRecord) == 28 ? 1 : -1];

typedef struct FloatRecordWordsEuXLayout {
    /* Three language groups of nine styles; Menu_DrawStyledMenuText uses languageIndex * 9. */
    MenuFontStyleRecord styles[27];
} FloatRecordWordsEuXLayout;
typedef char FloatRecordWordsEuXLayoutSizeCheck[sizeof(FloatRecordWordsEuXLayout) == 756 ? 1 : -1];

typedef struct GMenuboxcornersLevelTextWords2Layout {
    s32 ids[2];
    float constant;
    char levelText[24];
    void * references[4];
    char lodChangeDistanceText[24];
    void * references2[4];
    char globalScalerText[24];
    void * references3[4];
    char musicText[24];
    void * references4[4];
    u32 packedValue;
    u32 packedValues[11];
    void * references5[4];
} GMenuboxcornersLevelTextWords2Layout;

typedef struct FloatRecordWordsEuLayout {
    /* Three language groups of nine styles; Menu_DrawStyledMenuText uses languageIndex * 9. */
    MenuFontStyleRecord styles[27];
} FloatRecordWordsEuLayout;
typedef char FloatRecordWordsEuLayoutSizeCheck[sizeof(FloatRecordWordsEuLayout) == 756 ? 1 : -1];

typedef struct GMenuboxcornersLevelTextWords3Layout {
    s32 ids[2];
    float constant;
    char levelText[24];
    void * references[4];
    char lodChangeDistanceText[24];
    void * references2[4];
    char globalScalerText[24];
    void * references3[4];
    char musicText[24];
    void * references4[4];
    u32 packedValue;
    u32 packedValues[11];
    void * references5[4];
} GMenuboxcornersLevelTextWords3Layout;

typedef struct RestMinusOneSentinelWords {
    s32 ids[3];
    float constant;
} RestMinusOneSentinelWords;
typedef char RestMinusOneSentinelWordsSizeCheck[sizeof(RestMinusOneSentinelWords) == 16 ? 1 : -1];

typedef struct RestMinusOneSentinelWordsVariant2 {
    s32 ids[3];
    u32 packedValue;
} RestMinusOneSentinelWordsVariant2;
typedef char RestMinusOneSentinelWordsVariant2SizeCheck[sizeof(RestMinusOneSentinelWordsVariant2) == 16 ? 1 : -1];

typedef struct RestMenuCreateSoundOptionsScreenData {
    EventHandlerRecord soundOptionsHandlers[7];
    EventHandlerRecord alternateSoundOptionsHandlers[7];
} RestMenuCreateSoundOptionsScreenData;
typedef char RestMenuCreateSoundOptionsScreenDataSizeCheck[sizeof(RestMenuCreateSoundOptionsScreenData) == 168 ? 1 : -1];

typedef struct RestMenuCreateSoundOptionsScreenDataVariant2 {
    EventHandlerRecord records[14];
} RestMenuCreateSoundOptionsScreenDataVariant2;
typedef char RestMenuCreateSoundOptionsScreenDataVariant2SizeCheck[sizeof(RestMenuCreateSoundOptionsScreenDataVariant2) == 168 ? 1 : -1];

typedef struct RestMenuCreateSoundOptionsScreenDataVariant3 {
    EventHandlerRecord soundOptionsHandlers[7];
    EventHandlerRecord alternateSoundOptionsHandlers[7];
} RestMenuCreateSoundOptionsScreenDataVariant3;
typedef char RestMenuCreateSoundOptionsScreenDataVariant3SizeCheck[sizeof(RestMenuCreateSoundOptionsScreenDataVariant3) == 168 ? 1 : -1];

typedef struct MenuCreatesoundoptionsscreenPointerWordsTailUsLayout {
    EventHandlerRecord soundOptionsHandlers[5];
    EventHandlerRecord alternateSoundOptionsHandlers[7];
} MenuCreatesoundoptionsscreenPointerWordsTailUsLayout;
typedef char MenuCreatesoundoptionsscreenPointerWordsTailUsLayoutSizeCheck[sizeof(MenuCreatesoundoptionsscreenPointerWordsTailUsLayout) == 144 ? 1 : -1];

typedef struct MenuDispatchsettingscolumneventPointerWords1Layout {
    s32 ids3[2];
    void * reference;
    s32 ids4[5];
    struct { void * reference; s32 ids[2]; } rows[3];
    void * references[4];
    struct { s32 ids[2]; void * reference; } idReferenceRows[5];
    s32 ids5[2];
    void * references2[4];
} MenuDispatchsettingscolumneventPointerWords1Layout;
typedef char MenuDispatchsettingscolumneventPointerWords1LayoutSizeCheck[sizeof(MenuDispatchsettingscolumneventPointerWords1Layout) == 168 ? 1 : -1];

typedef struct RestMenuDispatchSettingsTableEventData {
    EventHandlerRecord records[14];
} RestMenuDispatchSettingsTableEventData;

typedef struct RestMenuDispatchSettingsTableEventDataVariant2 {
    EventHandlerRecord settingsHandlers[7];
    EventHandlerRecord alternateSettingsHandlers[7];
} RestMenuDispatchSettingsTableEventDataVariant2;
typedef char RestMenuDispatchSettingsTableEventDataVariant2SizeCheck[sizeof(RestMenuDispatchSettingsTableEventDataVariant2) == 168 ? 1 : -1];

typedef struct RestPlayerDispatchPlayerSettingsEventData {
    EventHandlerRecord playerSettingsHandlers[10];
    EventHandlerRecord alternatePlayerSettingsHandlers[9];
    u32 alignmentPadding;
} RestPlayerDispatchPlayerSettingsEventData;
typedef char RestPlayerDispatchPlayerSettingsEventDataSizeCheck[sizeof(RestPlayerDispatchPlayerSettingsEventData) == 232 ? 1 : -1];

typedef struct RestPlayerDispatchPlayerSettingsEventDataVariant2 {
    EventHandlerRecord playerSettingsHandlers[10];
    EventHandlerRecord alternatePlayerSettingsHandlers[9];
    u32 alignmentPadding;
} RestPlayerDispatchPlayerSettingsEventDataVariant2;
typedef char RestPlayerDispatchPlayerSettingsEventDataVariant2SizeCheck[sizeof(RestPlayerDispatchPlayerSettingsEventDataVariant2) == 232 ? 1 : -1];

typedef struct RestPlayerDispatchPlayerSettingsEventDataVariant3 {
    s32 ids[57];
    float constant;
} RestPlayerDispatchPlayerSettingsEventDataVariant3;
typedef char RestPlayerDispatchPlayerSettingsEventDataVariant3SizeCheck[sizeof(RestPlayerDispatchPlayerSettingsEventDataVariant3) == 232 ? 1 : -1];

typedef struct PlayerSettingsEventHandlersUsLayout {
    s32 ids[51];
    u32 packedValue;
    s32 ids2[44];
} PlayerSettingsEventHandlersUsLayout;
typedef char PlayerSettingsEventHandlersUsLayoutSizeCheck[sizeof(PlayerSettingsEventHandlersUsLayout) == 384 ? 1 : -1];

typedef struct AudioDecodeframeEncodedWordsLayout {
    s32 ids2[4];
    void * references2[3];
    s32 ids3[2];
    struct { void * references[2]; s32 ids[3]; } rows[2];
    void * reference;
} AudioDecodeframeEncodedWordsLayout;
typedef char AudioDecodeframeEncodedWordsLayoutSizeCheck[sizeof(AudioDecodeframeEncodedWordsLayout) == 80 ? 1 : -1];

typedef struct EncodedConstantRow {
    float constant;
    void * references[4];
} EncodedConstantRow;

typedef struct EncodedPackedRow {
    u32 packedValue;
    void * references[4];
} EncodedPackedRow;

typedef struct SelfLinkedFloatRow {
    float value;
    void * links[4];
} SelfLinkedFloatRow;
typedef struct SelfLinkedWordRow {
    u32 value;
    void * links[4];
} SelfLinkedWordRow;

typedef struct GfxdataEncodedWordsLayout {
    void * screenMessageLinks[2674];
    SelfLinkedFloatRow powerScales[15];
    SelfLinkedWordRow characterCodes[19];
    SelfLinkedFloatRow fractionScales[2];
    SelfLinkedWordRow formatCodes[3];
    void * trailingLinks[9];
    s32 trailingId;
} GfxdataEncodedWordsLayout;
typedef char GfxdataEncodedWordsLayoutSizeCheck[sizeof(GfxdataEncodedWordsLayout) == 11516 ? 1 : -1];


typedef struct MaincodeEncodedWordsLayout {
    s32 ids[9];
} MaincodeEncodedWordsLayout;
typedef char MaincodeEncodedWordsLayoutSizeCheck[sizeof(MaincodeEncodedWordsLayout) == 36 ? 1 : -1];

typedef struct Ovl3EncodedWordsLayout {
    s32 ids[3];
} Ovl3EncodedWordsLayout;
typedef char Ovl3EncodedWordsLayoutSizeCheck[sizeof(Ovl3EncodedWordsLayout) == 12 ? 1 : -1];

typedef struct KeyboardKeyLabelWordsLayout {
    struct { float constant; void * reference; } scaleStepRows[15];
    struct { u32 packedValue; void * reference; } keyCharacterRows[19];
    struct { float constant; void * reference; } fineScaleStepRows[2];
    struct { u32 packedValue; void * reference; } keyCodeRows[2];
    u32 packedValue;
    void * references[3];
} KeyboardKeyLabelWordsLayout;
typedef char KeyboardKeyLabelWordsLayoutSizeCheck[sizeof(KeyboardKeyLabelWordsLayout) == 320 ? 1 : -1];

typedef struct OverlayOneCFloatConstantWordsLayout {
    s32 ids[4];
} OverlayOneCFloatConstantWordsLayout;

typedef struct EventHandlerAddressTable_euLayout {
    u32 directionalLightWords[4];
    DisplayListCommandWords cameraView[6];
    DisplayListCommandWords cameraViewSecondary[12];
    DisplayListCommandWords textureTileDefault[16];
    DisplayListCommandWords textureTileWrapped[16];
    DisplayListCommandWords textureTileAlternate[19];
    DisplayListCommandWords textureTilePalette[19];
    DisplayListCommandWords textureTileFinish[19];
    DisplayListCommandWords geometryDefaultMaterial[17];
    DisplayListCommandWords geometryAlternateMaterial[17];
    char retainedProgrammerText[8];
    struct { u32 handler; u32 flags; } effectCallbacks[37];
    char retainedDirectorText[8];
    u8 materialIntensityMaskTexture[16][16];
} EventHandlerAddressTable_euLayout;
typedef char EventHandlerAddressTable_euLayoutSizeCheck[sizeof(EventHandlerAddressTable_euLayout) == 1712 ? 1 : -1];

typedef struct SndplayerEncodedWordsLayout {
    float constants[4];
    void * references[13];
} SndplayerEncodedWordsLayout;
typedef char SndplayerEncodedWordsLayoutSizeCheck[sizeof(SndplayerEncodedWordsLayout) == 68 ? 1 : -1];

typedef struct Ovl1EOvl1ECppRetainedWords24Layout {
    s32 id;
} Ovl1EOvl1ECppRetainedWords24Layout;

typedef struct Ovl1EOvl1ECppRetainedWords17Layout {
    s32 id;
} Ovl1EOvl1ECppRetainedWords17Layout;

typedef struct Ovl1EOvl1ECppRetainedWords15Layout {
    s32 id;
} Ovl1EOvl1ECppRetainedWords15Layout;

typedef struct Ovl1EOvl1ECppRetainedWords25Layout {
    s32 id;
} Ovl1EOvl1ECppRetainedWords25Layout;

typedef struct Ovl1EOvl1ECppRetainedWords30Layout {
    s32 id;
} Ovl1EOvl1ECppRetainedWords30Layout;

typedef struct Ovl1EOvl1ECppRetainedWords18Layout {
    s32 id;
} Ovl1EOvl1ECppRetainedWords18Layout;

typedef struct Ovl1EOvl1ECppRetainedWords22Layout {
    s32 id;
} Ovl1EOvl1ECppRetainedWords22Layout;

typedef struct Ovl1EOvl1ECppRetainedWords27Layout {
    s32 id;
} Ovl1EOvl1ECppRetainedWords27Layout;

typedef struct CharacterPreviewRecordWordsUsLayout {
    struct { void * name; s32 resource; s32 character; s32 animation; float scaleDistance[8]; float positions[12]; s32 lightOffsets[4]; } profiles[16]; /* CharacterPreviewProfile */
    void * reference2;
    s32 ids7[66];
    char text[8];
} CharacterPreviewRecordWordsUsLayout;
typedef char CharacterPreviewRecordWordsUsLayoutSizeCheck[sizeof(CharacterPreviewRecordWordsUsLayout) == 2068 ? 1 : -1];

typedef struct BossActivTextLayout {
    void * screenMessageLinks[24];
    void * health2TextLinks[4];
    void * health10TextLinks[4];
    void * health15TextLinks[4];
    void * health25TextLinks[4];
    void * health50TextLinks[4];
    void * fullHealthTextLinks[4];
    void * ultraHealthTextLinks[12];
    void * invincibilityTextLinks[4];
    void * planeWalkerTextLinks[4];
    void * flashlightTextLinks[4];
    void * flashlightBatteryTextLinks[4];
    void * infraredGogglesTextLinks[4];
    void * breathOfLifeTextLinks[4];
    void * eyeOfTruthTextLinks[4];
    void * leapOfFaithTextLinks[4];
    void * whispersTextLinks[4];
    void * heartOfFireTextLinks[4];
    void * blueEagleFeatherTextLinks[4];
    void * greyEagleFeatherTextLinks[4];
    void * brownEagleFeatherTextLinks[4];
    void * purpleEagleFeatherTextLinks[4];
    void * redEagleFeatherTextLinks[4];
    void * nukeWeaponPartTextLinks[4];
    void * retaliationTextLinks[284];
    void * energyRoundsTextLinks[4];
    void * energyRounds2TextLinks[4];
    void * bulletRoundsTextLinks[4];
    void * bulletRounds2TextLinks[4];
    void * explosiveRoundsTextLinks[4];
    void * explosiveRounds2TextLinks[4];
    void * ammoPackTextLinks[3132];
    SelfLinkedFloatRow powerScales[15];
    SelfLinkedWordRow characterCodes[19];
    SelfLinkedFloatRow fractionScales[2];
    SelfLinkedWordRow formatCodes[3];
    void * trailingLinks[9];
    char trailingText[12];
} BossActivTextLayout;
typedef char BossActivTextLayoutSizeCheck[sizeof(BossActivTextLayout) == 15084 ? 1 : -1];

typedef struct ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout866 {
    s32 ids2[201];
    struct { void * reference; s32 ids[2]; } rows[11];
    void * references[4];
    s32 ids3[40];
} ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout866;
typedef char ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout866SizeCheck[sizeof(ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout866) == 1112 ? 1 : -1];

typedef struct ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout867 {
    s32 ids2[201];
    struct { void * reference; s32 ids[2]; } rows[11];
    void * references[4];
    s32 ids3[40];
} ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout867;
typedef char ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout867SizeCheck[sizeof(ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout867) == 1112 ? 1 : -1];

typedef struct ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout868 {
    s32 ids2[201];
    struct { void * reference; s32 ids[2]; } rows[11];
    void * references[4];
    s32 ids3[40];
} ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout868;
typedef char ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout868SizeCheck[sizeof(ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout868) == 1112 ? 1 : -1];

typedef struct ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout869 {
    s32 ids2[201];
    struct { void * reference; s32 ids[2]; } rows[11];
    void * references[4];
    s32 ids3[40];
} ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout869;
typedef char ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout869SizeCheck[sizeof(ScenariosetupHidearenacataloguewidgetsEncodedWordsLayout869) == 1112 ? 1 : -1];

typedef struct TrackDrawtrackoverlayEncodedWordsBlock1Layout {
    float constants[3];
} TrackDrawtrackoverlayEncodedWordsBlock1Layout;
typedef char TrackDrawtrackoverlayEncodedWordsBlock1LayoutSizeCheck[sizeof(TrackDrawtrackoverlayEncodedWordsBlock1Layout) == 12 ? 1 : -1];

typedef struct RestsmpControllerStateAndEventWordsLayout872 {
    s32 ids[17];
    float constants[2];
    s32 ids2[2];
    void * reference;
    s32 id;
} RestsmpControllerStateAndEventWordsLayout872;
typedef char RestsmpControllerStateAndEventWordsLayout872SizeCheck[sizeof(RestsmpControllerStateAndEventWordsLayout872) == 92 ? 1 : -1];

typedef struct RestsmpControllerStateAndEventWordsLayout873 {
    s32 ids[17];
    u32 packedValues[2];
    s32 id;
    float constant;
    u32 packedValues2[2];
} RestsmpControllerStateAndEventWordsLayout873;
typedef char RestsmpControllerStateAndEventWordsLayout873SizeCheck[sizeof(RestsmpControllerStateAndEventWordsLayout873) == 92 ? 1 : -1];

typedef struct RestsmpControllerStateAndEventWordsLayout874 {
    s32 ids[23];
} RestsmpControllerStateAndEventWordsLayout874;
typedef char RestsmpControllerStateAndEventWordsLayout874SizeCheck[sizeof(RestsmpControllerStateAndEventWordsLayout874) == 92 ? 1 : -1];

typedef struct RestsmpControllerStateAndEventWordsLayout875 {
    s32 ids[17];
    char text[4];
    u32 packedValue;
    s32 ids2[2];
    u32 packedValue2;
    char text2[4];
} RestsmpControllerStateAndEventWordsLayout875;
typedef char RestsmpControllerStateAndEventWordsLayout875SizeCheck[sizeof(RestsmpControllerStateAndEventWordsLayout875) == 92 ? 1 : -1];

typedef struct RestsmpControllerStateAndEventWordsLayout876 {
    s32 ids[23];
} RestsmpControllerStateAndEventWordsLayout876;
typedef char RestsmpControllerStateAndEventWordsLayout876SizeCheck[sizeof(RestsmpControllerStateAndEventWordsLayout876) == 92 ? 1 : -1];

typedef struct SmpControllerEventRecordTails {
    s32 ids[5];
    void * reference;
    s32 ids2[2];
    void * references[4];
    s32 ids3[5];
    void * reference2;
    s32 ids4[2];
    void * references2[5];
    s32 ids5[2];
} SmpControllerEventRecordTails;
typedef char SmpControllerEventRecordTailsSizeCheck[sizeof(SmpControllerEventRecordTails) == 108 ? 1 : -1];

typedef struct RestsmpEventHandlerTablesLayout880 {
    s32 ids[132];
} RestsmpEventHandlerTablesLayout880;
typedef char RestsmpEventHandlerTablesLayout880SizeCheck[sizeof(RestsmpEventHandlerTablesLayout880) == 528 ? 1 : -1];

typedef struct RestsmpEventHandlerTablesLayout881 {
    /* Each SMP widget kind's event table ends with a zero record and is padded to 16 bytes with stale words. */
    struct { EventHandlerRecord handlers[3]; u32 alignmentFill[3]; } frameAnimHandlers;
    struct { EventHandlerRecord handlers[3]; u32 alignmentFill[3]; } flickerHandlers;
    struct { EventHandlerRecord handlers[3]; u32 alignmentFill[3]; } sliderFadeHandlers;
    struct { EventHandlerRecord handlers[9]; u32 alignmentFill; } sliderListHandlers;
    struct { EventHandlerRecord handlers[7]; u32 alignmentFill[3]; } buttonListHandlers;
    struct { EventHandlerRecord handlers[5]; u32 alignmentFill; } buttonHandlers;
    struct { EventHandlerRecord handlers[9]; u32 alignmentFill; } overlayHandlers;
} RestsmpEventHandlerTablesLayout881;
typedef char RestsmpEventHandlerTablesLayout881SizeCheck[sizeof(RestsmpEventHandlerTablesLayout881) == 528 ? 1 : -1];

typedef struct RestTrigConstantPool3 { s32 zero; s32 precision[2]; double one; } __attribute__((packed)) RestTrigConstantPool3;

typedef struct RestDecimalPowersPool5 { u32 prefix[2]; double powers[9]; char tail[8]; } RestDecimalPowersPool5;

typedef struct PlayerPoolInitWords {
    s32 state;
} PlayerPoolInitWords;

typedef struct PlayerControllerStateThirteenWords {
    s32 state;
} PlayerControllerStateThirteenWords;

typedef struct PlayerControllerStateEndWords {
    s32 endState;
} PlayerControllerStateEndWords;

typedef struct RestBytes2 {
    u8 bytes[2];
} RestBytes2;

typedef struct RestDecimalPowersPool621 { u32 prefix[2]; double powers[9]; char tail[8]; } RestDecimalPowersPool621;

typedef struct RestTrigConstantPool624 { s32 zero; s32 precision[2]; double one; } __attribute__((packed)) RestTrigConstantPool624;

typedef struct RestTrigConstantPool790 { float unsignedBias; float frameRate; u32 zero; double one; } __attribute__((packed)) RestTrigConstantPool790;

typedef struct RestDecimalPowersPool793 { u32 prefix[2]; double powers[9]; char tail[8]; } RestDecimalPowersPool793;

typedef struct Ovldat10EncodedWordsBlock17AfterLayout {
    u8 record0_line_inc_opcode;
    u8 record0_line_inc_offsetLE[2];
    u8 record0_line_inc_deltaLE;
    u8 record1_patch_opcode;
    u8 record1_patch_relocationKind;
    u8 record1_patch_offsetLE[2];
    u8 record1_patch_expression[9];
    u8 record2_patch_opcode;
    u8 record2_patch_relocationKind;
    u8 record2_patch_offsetLE[2];
    u8 record2_patch_expression[9];
    u8 record3_line_inc_opcode;
    u8 record3_line_inc_offsetLE[2];
    u8 record4_patch_opcode;
    u8 record4_patch_relocationKind;
    u8 record4_patch_offsetLE[2];
    u8 record4_patch_expression[9];
    u8 record5_line_inc_opcode;
    u8 record5_line_inc_offsetLE[2];
    u8 record5_line_inc_deltaLE;
    u8 record6_patch_opcode;
    u8 record6_patch_relocationKind;
    u8 record6_patch_offsetLE[2];
    u8 record6_patch_expression[9];
    u8 record7_patch_opcode;
    u8 record7_patch_relocationKind;
    u8 record7_patch_offsetLE[2];
    u8 record7_patch_expression[9];
    u8 record8_line_inc_opcode;
    u8 record8_line_inc_offsetLE[2];
    u8 record9_patch_opcode;
    u8 record9_patch_relocationKind;
    u8 record9_patch_offsetLE[2];
    u8 record9_patch_expression[9];
    u8 record10_line_inc_opcode;
    u8 record10_line_inc_offsetLE[2];
    u8 record10_line_inc_deltaLE;
    u8 record11_patch_opcode;
    u8 record11_patch_relocationKind;
    u8 record11_patch_offsetLE[2];
    u8 record11_patch_expression[9];
    u8 record12_patch_opcode;
    u8 record12_patch_relocationKind;
    u8 record12_patch_offsetLE[2];
    u8 record12_patch_expression[9];
    u8 record13_line_inc_opcode;
    u8 record13_line_inc_offsetLE[2];
    u8 record13_line_inc_deltaLE;
    u8 record14_patch_opcode;
    u8 record14_patch_relocationKind;
    u8 record14_patch_offsetLE[2];
    u8 record14_patch_expression[9];
    u8 record15_line_inc_opcode;
    u8 record15_line_inc_offsetLE[2];
    u8 record15_line_inc_deltaLE;
    u8 record16_patch_opcode;
    u8 record16_patch_relocationKind;
    u8 record16_patch_offsetLE[2];
    u8 record16_patch_expression[9];
    u8 record17_patch_opcode;
    u8 record17_patch_relocationKind;
    u8 record17_patch_offsetLE[2];
    u8 record17_patch_expression[9];
    u8 record18_line_inc_opcode;
    u8 record18_line_inc_offsetLE[2];
    u8 record19_patch_opcode;
    u8 record19_patch_relocationKind;
    u8 record19_patch_offsetLE[2];
    u8 record19_patch_expression[9];
    u8 record20_line_inc_opcode;
    u8 record20_line_inc_offsetLE[2];
    u8 record20_line_inc_deltaLE;
    u8 record21_patch_opcode;
    u8 record21_patch_relocationKind;
    u8 record21_patch_offsetLE[2];
    u8 record21_patch_expression[9];
    u8 record22_patch_opcode;
    u8 record22_patch_relocationKind;
    u8 record22_patch_offsetLE[2];
    u8 record22_patch_expression[9];
    u8 record23_line_inc_opcode;
    u8 record23_line_inc_offsetLE[2];
    u8 record24_patch_opcode;
    u8 record24_patch_relocationKind;
    u8 record24_patch_offsetLE[2];
    u8 record24_patch_expression[9];
    u8 record25_line_inc_opcode;
    u8 record25_line_inc_offsetLE[2];
    u8 record25_line_inc_deltaLE;
    u8 record26_patch_opcode;
    u8 record26_patch_relocationKind;
    u8 record26_patch_offsetLE[2];
    u8 record26_patch_expression[9];
    u8 record27_patch_opcode;
    u8 record27_patch_relocationKind;
    u8 record27_patch_offsetLE[2];
    u8 record27_patch_expression[9];
    u8 record28_patch_opcode;
    u8 record28_patch_relocationKind;
    u8 record28_patch_offsetLE[2];
    u8 record28_patch_expression[9];
    u8 record29_patch_opcode;
    u8 record29_patch_relocationKind;
    u8 record29_patch_offsetLE[2];
    u8 record29_patch_expression[9];
    u8 record30_patch_opcode;
    u8 record30_patch_relocationKind;
    u8 record30_patch_offsetLE[2];
    u8 record30_patch_expression[3];
    u8 record31_line_inc_opcode;
    u8 record31_line_inc_offsetLE[2];
    u8 record32_patch_opcode;
    u8 record32_patch_relocationKind;
    u8 record32_patch_offsetLE[2];
    u8 record32_patch_expression[9];
    u8 record33_line_inc_opcode;
    u8 record33_line_inc_offsetLE[2];
    u8 record33_line_inc_deltaLE;
    u8 record34_line_inc_opcode;
    u8 record34_line_inc_offsetLE[2];
    u8 record34_line_inc_deltaLE;
    u8 record35_line_inc_opcode;
    u8 record35_line_inc_offsetLE[2];
    u8 record35_line_inc_deltaLE;
    u8 record36_line_inc_opcode;
    u8 record36_line_inc_offsetLE[2];
    u8 record36_line_inc_deltaLE;
    u8 record37_line_inc_opcode;
    u8 record37_line_inc_offsetLE[2];
    u8 record38_line_inc_opcode;
    u8 record38_line_inc_offsetLE[2];
    u8 record38_line_inc_deltaLE;
    u8 record39_patch_opcode;
    u8 record39_patch_relocationKind;
    u8 record39_patch_offsetLE[2];
    u8 record39_patch_expression[9];
    u8 record40_patch_opcode;
    u8 record40_patch_relocationKind;
    u8 record40_patch_offsetLE[2];
    u8 record40_patch_expression[9];
    u8 record41_patch_opcode;
    u8 record41_patch_relocationKind;
    u8 record41_patch_offsetLE[2];
    u8 record41_patch_expression[9];
    u8 record42_patch_opcode;
    u8 record42_patch_relocationKind;
    u8 record42_patch_offsetLE[2];
    u8 record42_patch_expression[9];
    u8 record43_patch_opcode;
    u8 record43_patch_relocationKind;
    u8 record43_patch_offsetLE[2];
    u8 record43_patch_expression[9];
    u8 record44_patch_opcode;
    u8 record44_patch_relocationKind;
    u8 record44_patch_offsetLE[2];
    u8 record44_patch_expression[3];
    u8 record45_line_inc_opcode;
    u8 record45_line_inc_offsetLE[2];
    u8 record45_line_inc_deltaLE;
    u8 record46_line_inc_opcode;
    u8 record46_line_inc_offsetLE[2];
    u8 record47_patch_opcode;
    u8 record47_patch_relocationKind;
    u8 record47_patch_offsetLE[2];
    u8 record47_patch_expression[9];
    u8 record48_patch_opcode;
    u8 record48_patch_relocationKind;
    u8 record48_patch_offsetLE[2];
    u8 record48_patch_expression[9];
    u8 record49_line_inc_opcode;
    u8 record49_line_inc_offsetLE[2];
    u8 record49_line_inc_deltaLE;
    u8 record50_patch_opcode;
    u8 record50_patch_relocationKind;
    u8 record50_patch_offsetLE[2];
    u8 record50_patch_expression[9];
    u8 record51_patch_opcode;
    u8 record51_patch_relocationKind;
    u8 record51_patch_offsetLE[2];
    u8 record51_patch_expression[9];
    u8 record52_line_inc_opcode;
    u8 record52_line_inc_offsetLE[2];
    u8 record52_line_inc_deltaLE;
    u8 record53_patch_opcode;
    u8 record53_patch_relocationKind;
    u8 record53_patch_offsetLE[2];
    u8 record53_patch_expression[9];
    u8 record54_line_inc_opcode;
    u8 record54_line_inc_offsetLE[2];
    u8 record54_line_inc_deltaLE;
    u8 record55_line_inc_opcode;
    u8 record55_line_inc_offsetLE[2];
    u8 record55_line_inc_deltaLE;
    u8 record56_patch_opcode;
    u8 record56_patch_relocationKind;
    u8 record56_patch_offsetLE[2];
    u8 record56_patch_expression[9];
    u8 record57_line_inc_opcode;
    u8 record57_line_inc_offsetLE[2];
    u8 record57_line_inc_deltaLE;
    u8 record58_patch_opcode;
    u8 record58_patch_relocationKind;
    u8 record58_patch_offsetLE[2];
    u8 record58_patch_expression[9];
    u8 record59_patch_opcode;
    u8 record59_patch_relocationKind;
    u8 record59_patch_offsetLE[2];
    u8 record59_patch_expression[9];
    u8 record60_line_inc_opcode;
    u8 record60_line_inc_offsetLE[2];
    u8 record61_patch_opcode;
    u8 record61_patch_relocationKind;
    u8 record61_patch_offsetLE[2];
    u8 record61_patch_expression[3];
    u8 record62_patch_opcode;
    u8 record62_patch_relocationKind;
    u8 record62_patch_offsetLE[2];
    u8 record62_patch_expression[3];
    u8 record63_line_inc_opcode;
    u8 record63_line_inc_offsetLE[2];
    u8 record63_line_inc_deltaLE;
    u8 record64_patch_opcode;
    u8 record64_patch_relocationKind;
    u8 record64_patch_offsetLE[2];
    u8 record64_patch_expression[3];
    u8 record65_line_inc_opcode;
    u8 record65_line_inc_offsetLE[2];
    u8 record65_line_inc_deltaLE;
    u8 record66_line_inc_opcode;
    u8 record66_line_inc_offsetLE[2];
    u8 record66_line_inc_deltaLE;
    u8 record67_patch_opcode;
    u8 record67_patch_relocationKind;
    u8 record67_patch_offsetLE[2];
    u8 record67_patch_expression[9];
    u8 record68_patch_opcode;
    u8 record68_patch_relocationKind;
    u8 record68_patch_offsetLE[2];
    u8 record68_patch_expression[9];
    u8 record69_line_inc_opcode;
    u8 record69_line_inc_offsetLE[2];
    u8 record70_patch_opcode;
    u8 record70_patch_relocationKind;
    u8 record70_patch_offsetLE[2];
    u8 record70_patch_expression[9];
    u8 record71_line_inc_opcode;
    u8 record71_line_inc_offsetLE[2];
    u8 record71_line_inc_deltaLE;
    u8 record72_line_inc_opcode;
    u8 record72_line_inc_offsetLE[2];
    u8 record72_line_inc_deltaLE;
    u8 record73_patch_opcode;
    u8 record73_patch_relocationKind;
    u8 record73_patch_offsetLE[2];
    u8 record73_patch_expression[9];
    u8 record74_line_inc_opcode;
    u8 record74_line_inc_offsetLE[2];
    u8 record75_line_inc_opcode;
    u8 record75_line_inc_offsetLE[2];
    u8 record75_line_inc_deltaLE;
    u8 record76_switch_opcode;
    u8 record76_switch_offsetLE[2];
    u8 record77_code_opcode;
    u8 record77_code_payload[27];
    u8 record78_switch_opcode;
    u8 record78_switch_offsetLE[2];
    u8 recordContinuationTail[3];
} Ovldat10EncodedWordsBlock17AfterLayout;

typedef struct Ovldat10EncodedWordsBlock17MidLayout {
    u8 record0_patch_opcode;
    u8 record0_patch_relocationKind;
    u8 record0_patch_offsetLE[2];
    u8 record0_patch_expression[9];
    u8 record1_patch_opcode;
    u8 record1_patch_relocationKind;
    u8 record1_patch_offsetLE[2];
    u8 record1_patch_expression[9];
    u8 record2_patch_opcode;
    u8 record2_patch_relocationKind;
    u8 record2_patch_offsetLE[2];
    u8 record2_patch_expression[9];
    u8 record3_patch_opcode;
    u8 record3_patch_relocationKind;
    u8 record3_patch_offsetLE[2];
    u8 record3_patch_expression[9];
    u8 record4_patch_opcode;
    u8 record4_patch_relocationKind;
    u8 record4_patch_offsetLE[2];
    u8 record4_patch_expression[9];
    u8 record5_switch_opcode;
    u8 record5_switch_offsetLE[2];
    u8 recordContinuationTail[3];
} Ovldat10EncodedWordsBlock17MidLayout;

typedef struct Ovldat10EncodedWordsBlock14RestLayout {
    u8 record0_line_inc_opcode;
    u8 record0_line_inc_offsetLE[2];
    u8 record0_line_inc_deltaLE;
    u8 record1_patch_opcode;
    u8 record1_patch_relocationKind;
    u8 record1_patch_offsetLE[2];
    u8 record1_patch_expression[9];
    u8 record2_patch_opcode;
    u8 record2_patch_relocationKind;
    u8 record2_patch_offsetLE[2];
    u8 record2_patch_expression[9];
    u8 record3_line_inc_opcode;
    u8 record3_line_inc_offsetLE[2];
    u8 record4_line_inc_opcode;
    u8 record4_line_inc_offsetLE[2];
    u8 record4_line_inc_deltaLE;
    u8 record5_patch_opcode;
    u8 record5_patch_relocationKind;
    u8 record5_patch_offsetLE[2];
    u8 record5_patch_expression[3];
    u8 record6_line_inc_opcode;
    u8 record6_line_inc_offsetLE[2];
    u8 record6_line_inc_deltaLE;
    u8 record7_line_inc_opcode;
    u8 record7_line_inc_offsetLE[2];
    u8 record7_line_inc_deltaLE;
    u8 record8_line_inc_opcode;
    u8 record8_line_inc_offsetLE[2];
    u8 record8_line_inc_deltaLE;
    u8 record9_patch_opcode;
    u8 record9_patch_relocationKind;
    u8 record9_patch_offsetLE[2];
    u8 record9_patch_expression[9];
    u8 record10_line_inc_opcode;
    u8 record10_line_inc_offsetLE[2];
    u8 record10_line_inc_deltaLE;
    u8 record11_line_inc_opcode;
    u8 record11_line_inc_offsetLE[2];
    u8 record12_line_inc_opcode;
    u8 record12_line_inc_offsetLE[2];
    u8 record12_line_inc_deltaLE;
    u8 record13_line_inc_opcode;
    u8 record13_line_inc_offsetLE[2];
    u8 record13_line_inc_deltaLE;
    u8 record14_line_inc_opcode;
    u8 record14_line_inc_offsetLE[2];
    u8 record14_line_inc_deltaLE;
    u8 record15_line_inc_opcode;
    u8 record15_line_inc_offsetLE[2];
    u8 record16_line_inc_opcode;
    u8 record16_line_inc_offsetLE[2];
    u8 record16_line_inc_deltaLE;
    u8 record17_patch_opcode;
    u8 record17_patch_relocationKind;
    u8 record17_patch_offsetLE[2];
    u8 record17_patch_expression[9];
    u8 record18_patch_opcode;
    u8 record18_patch_relocationKind;
    u8 record18_patch_offsetLE[2];
    u8 record18_patch_expression[9];
    u8 record19_patch_opcode;
    u8 record19_patch_relocationKind;
    u8 record19_patch_offsetLE[2];
    u8 record19_patch_expression[9];
    u8 record20_patch_opcode;
    u8 record20_patch_relocationKind;
    u8 record20_patch_offsetLE[2];
    u8 record20_patch_expression[9];
    u8 record21_patch_opcode;
    u8 record21_patch_relocationKind;
    u8 record21_patch_offsetLE[2];
    u8 record21_patch_expression[9];
    u8 record22_patch_opcode;
    u8 record22_patch_relocationKind;
    u8 record22_patch_offsetLE[2];
    u8 record22_patch_expression[3];
    u8 record23_line_inc_opcode;
    u8 record23_line_inc_offsetLE[2];
    u8 record23_line_inc_deltaLE;
    u8 record24_line_inc_opcode;
    u8 record24_line_inc_offsetLE[2];
    u8 record25_patch_opcode;
    u8 record25_patch_relocationKind;
    u8 record25_patch_offsetLE[2];
    u8 record25_patch_expression[9];
    u8 record26_patch_opcode;
    u8 record26_patch_relocationKind;
    u8 record26_patch_offsetLE[2];
    u8 record26_patch_expression[9];
    u8 record27_patch_opcode;
    u8 record27_patch_relocationKind;
    u8 record27_patch_offsetLE[2];
    u8 record27_patch_expression[3];
    u8 record28_patch_opcode;
    u8 record28_patch_relocationKind;
    u8 record28_patch_offsetLE[2];
    u8 record28_patch_expression[3];
    u8 record29_patch_opcode;
    u8 record29_patch_relocationKind;
    u8 record29_patch_offsetLE[2];
    u8 record29_patch_expression[3];
    u8 record30_line_inc_opcode;
    u8 record30_line_inc_offsetLE[2];
    u8 record30_line_inc_deltaLE;
    u8 record31_patch_opcode;
    u8 record31_patch_relocationKind;
    u8 record31_patch_offsetLE[2];
    u8 record31_patch_expression[3];
    u8 record32_line_inc_opcode;
    u8 record32_line_inc_offsetLE[2];
    u8 record33_line_inc_opcode;
    u8 record33_line_inc_offsetLE[2];
    u8 record33_line_inc_deltaLE;
    u8 record34_line_inc_opcode;
    u8 record34_line_inc_offsetLE[2];
    u8 record34_line_inc_deltaLE;
    u8 record35_patch_opcode;
    u8 record35_patch_relocationKind;
    u8 record35_patch_offsetLE[2];
    u8 record35_patch_expression[9];
    u8 record36_line_inc_opcode;
    u8 record36_line_inc_offsetLE[2];
    u8 record36_line_inc_deltaLE;
    u8 record37_patch_opcode;
    u8 record37_patch_relocationKind;
    u8 record37_patch_offsetLE[2];
    u8 record37_patch_expression[9];
    u8 record38_line_inc_opcode;
    u8 record38_line_inc_offsetLE[2];
    u8 record39_line_inc_opcode;
    u8 record39_line_inc_offsetLE[2];
    u8 record39_line_inc_deltaLE;
    u8 record40_line_inc_opcode;
    u8 record40_line_inc_offsetLE[2];
    u8 record40_line_inc_deltaLE;
    u8 record41_line_inc_opcode;
    u8 record41_line_inc_offsetLE[2];
    u8 record41_line_inc_deltaLE;
    u8 record42_line_inc_opcode;
    u8 record42_line_inc_offsetLE[2];
    u8 record42_line_inc_deltaLE;
    u8 record43_line_inc_opcode;
    u8 record43_line_inc_offsetLE[2];
    u8 record43_line_inc_deltaLE;
    u8 record44_patch_opcode;
    u8 record44_patch_relocationKind;
    u8 record44_patch_offsetLE[2];
    u8 record44_patch_expression[3];
    u8 record45_line_inc_opcode;
    u8 record45_line_inc_offsetLE[2];
    u8 record45_line_inc_deltaLE;
    u8 record46_line_inc_opcode;
    u8 record46_line_inc_offsetLE[2];
    u8 record46_line_inc_deltaLE;
    u8 record47_patch_opcode;
    u8 record47_patch_relocationKind;
    u8 record47_patch_offsetLE[2];
    u8 record47_patch_expression[9];
    u8 record48_line_inc_opcode;
    u8 record48_line_inc_offsetLE[2];
    u8 record48_line_inc_deltaLE;
    u8 record49_patch_opcode;
    u8 record49_patch_relocationKind;
    u8 record49_patch_offsetLE[2];
    u8 record49_patch_expression[9];
    u8 record50_line_inc_opcode;
    u8 record50_line_inc_offsetLE[2];
    u8 record50_line_inc_deltaLE;
    u8 record51_patch_opcode;
    u8 record51_patch_relocationKind;
    u8 record51_patch_offsetLE[2];
    u8 record51_patch_expression[9];
    u8 record52_patch_opcode;
    u8 record52_patch_relocationKind;
    u8 record52_patch_offsetLE[2];
    u8 record52_patch_expression[9];
    u8 record53_line_inc_opcode;
    u8 record53_line_inc_offsetLE[2];
    u8 record53_line_inc_deltaLE;
    u8 record54_patch_opcode;
    u8 record54_patch_relocationKind;
    u8 record54_patch_offsetLE[2];
    u8 record54_patch_expression[9];
    u8 record55_line_inc_opcode;
    u8 record55_line_inc_offsetLE[2];
    u8 record56_line_set_opcode;
    u8 record56_line_set_offsetLE[2];
    u8 record56_line_set_lineLE[4];
    u8 record57_patch_opcode;
    u8 record57_patch_relocationKind;
    u8 record57_patch_offsetLE[2];
    u8 record57_patch_expression[9];
    u8 record58_line_inc_opcode;
    u8 record58_line_inc_offsetLE[2];
    u8 record58_line_inc_deltaLE;
    u8 record59_patch_opcode;
    u8 record59_patch_relocationKind;
    u8 record59_patch_offsetLE[2];
    u8 record59_patch_expression[9];
    u8 record60_patch_opcode;
    u8 record60_patch_relocationKind;
    u8 record60_patch_offsetLE[2];
    u8 record60_patch_expression[9];
    u8 record61_patch_opcode;
    u8 record61_patch_relocationKind;
    u8 record61_patch_offsetLE[2];
    u8 record61_patch_expression[3];
    u8 record62_patch_opcode;
    u8 record62_patch_relocationKind;
    u8 record62_patch_offsetLE[2];
    u8 record62_patch_expression[3];
    u8 record63_patch_opcode;
    u8 record63_patch_relocationKind;
    u8 record63_patch_offsetLE[2];
    u8 record63_patch_expression[3];
    u8 record64_line_inc_opcode;
    u8 record64_line_inc_offsetLE[2];
    u8 record64_line_inc_deltaLE;
    u8 record65_patch_opcode;
    u8 record65_patch_relocationKind;
    u8 record65_patch_offsetLE[2];
    u8 record65_patch_expression[9];
    u8 record66_patch_opcode;
    u8 record66_patch_relocationKind;
    u8 record66_patch_offsetLE[2];
    u8 record66_patch_expression[9];
    u8 record67_patch_opcode;
    u8 record67_patch_relocationKind;
    u8 record67_patch_offsetLE[2];
    u8 record67_patch_expression[3];
    u8 record68_patch_opcode;
    u8 record68_patch_relocationKind;
    u8 record68_patch_offsetLE[2];
    u8 record68_patch_expression[3];
    u8 record69_patch_opcode;
    u8 record69_patch_relocationKind;
    u8 record69_patch_offsetLE[2];
    u8 record69_patch_expression[3];
    u8 record70_line_inc_opcode;
    u8 record70_line_inc_offsetLE[2];
    u8 record70_line_inc_deltaLE;
    u8 record71_line_inc_opcode;
    u8 record71_line_inc_offsetLE[2];
    u8 record72_line_inc_opcode;
    u8 record72_line_inc_offsetLE[2];
    u8 record72_line_inc_deltaLE;
    u8 record73_line_inc_opcode;
    u8 record73_line_inc_offsetLE[2];
    u8 record73_line_inc_deltaLE;
    u8 record74_patch_opcode;
    u8 record74_patch_relocationKind;
    u8 record74_patch_offsetLE[2];
    u8 record74_patch_expression[9];
    u8 record75_patch_opcode;
    u8 record75_patch_relocationKind;
    u8 record75_patch_offsetLE[2];
    u8 record75_patch_expression[9];
    u8 record76_line_inc_opcode;
    u8 record76_line_inc_offsetLE[2];
    u8 record77_patch_opcode;
    u8 record77_patch_relocationKind;
    u8 record77_patch_offsetLE[2];
    u8 record77_patch_expression[9];
    u8 record78_patch_opcode;
    u8 record78_patch_relocationKind;
    u8 record78_patch_offsetLE[2];
    u8 record78_patch_expression[9];
    u8 record79_line_inc_opcode;
    u8 record79_line_inc_offsetLE[2];
    u8 record80_patch_opcode;
    u8 record80_patch_relocationKind;
    u8 record80_patch_offsetLE[2];
    u8 record80_patch_expression[9];
    u8 record81_line_inc_opcode;
    u8 record81_line_inc_offsetLE[2];
    u8 record81_line_inc_deltaLE;
    u8 record82_patch_opcode;
    u8 record82_patch_relocationKind;
    u8 record82_patch_offsetLE[2];
    u8 record82_patch_expression[9];
    u8 record83_line_inc_opcode;
    u8 record83_line_inc_offsetLE[2];
    u8 record84_line_inc_opcode;
    u8 record84_line_inc_offsetLE[2];
    u8 record84_line_inc_deltaLE;
    u8 record85_line_inc_opcode;
    u8 record85_line_inc_offsetLE[2];
    u8 record85_line_inc_deltaLE;
    u8 record86_line_inc_opcode;
    u8 record86_line_inc_offsetLE[2];
    u8 record86_line_inc_deltaLE;
    u8 record87_line_inc_opcode;
    u8 record87_line_inc_offsetLE[2];
    u8 record88_line_inc_opcode;
    u8 record88_line_inc_offsetLE[2];
    u8 record88_line_inc_deltaLE;
    u8 record89_patch_opcode;
    u8 record89_patch_relocationKind;
    u8 record89_patch_offsetLE[2];
    u8 record89_patch_expression[9];
    u8 record90_patch_opcode;
    u8 record90_patch_relocationKind;
    u8 record90_patch_offsetLE[2];
    u8 record90_patch_expression[9];
    u8 record91_patch_opcode;
    u8 record91_patch_relocationKind;
    u8 record91_patch_offsetLE[2];
    u8 record91_patch_expression[9];
    u8 record92_patch_opcode;
    u8 record92_patch_relocationKind;
    u8 record92_patch_offsetLE[2];
    u8 record92_patch_expression[9];
    u8 record93_patch_opcode;
    u8 record93_patch_relocationKind;
    u8 record93_patch_offsetLE[2];
    u8 record93_patch_expression[9];
    u8 record94_patch_opcode;
    u8 record94_patch_relocationKind;
    u8 record94_patch_offsetLE[2];
    u8 record94_patch_expression[3];
    u8 record95_line_inc_opcode;
    u8 record95_line_inc_offsetLE[2];
    u8 record95_line_inc_deltaLE;
    u8 record96_line_inc_opcode;
    u8 record96_line_inc_offsetLE[2];
    u8 record96_line_inc_deltaLE;
    u8 record97_patch_opcode;
    u8 record97_patch_relocationKind;
    u8 record97_patch_offsetLE[2];
    u8 record97_patch_expression[9];
    u8 record98_line_inc_opcode;
    u8 record98_line_inc_offsetLE[2];
    u8 record99_patch_opcode;
    u8 record99_patch_relocationKind;
    u8 record99_patch_offsetLE[2];
    u8 record99_patch_expression[9];
    u8 record100_patch_opcode;
    u8 record100_patch_relocationKind;
    u8 record100_patch_offsetLE[2];
    u8 record100_patch_expression[9];
    u8 record101_line_inc_opcode;
    u8 record101_line_inc_offsetLE[2];
    u8 record102_patch_opcode;
    u8 record102_patch_relocationKind;
    u8 record102_patch_offsetLE[2];
    u8 record102_patch_expression[3];
    u8 record103_line_inc_opcode;
    u8 record103_line_inc_offsetLE[2];
    u8 record104_line_inc_opcode;
    u8 record104_line_inc_offsetLE[2];
    u8 record104_line_inc_deltaLE;
    u8 record105_line_inc_opcode;
    u8 record105_line_inc_offsetLE[2];
    u8 record105_line_inc_deltaLE;
    u8 record106_patch_opcode;
    u8 record106_patch_relocationKind;
    u8 record106_patch_offsetLE[2];
    u8 record106_patch_expression[3];
    u8 record107_line_inc_opcode;
    u8 record107_line_inc_offsetLE[2];
    u8 record107_line_inc_deltaLE;
    u8 record108_line_inc_opcode;
    u8 record108_line_inc_offsetLE[2];
    u8 record108_line_inc_deltaLE;
    u8 record109_patch_opcode;
    u8 record109_patch_relocationKind;
    u8 record109_patch_offsetLE[2];
    u8 record109_patch_expression[9];
    u8 record110_line_inc_opcode;
    u8 record110_line_inc_offsetLE[2];
    u8 record111_line_inc_opcode;
    u8 record111_line_inc_offsetLE[2];
    u8 record112_patch_opcode;
    u8 record112_patch_relocationKind;
    u8 record112_patch_offsetLE[2];
    u8 record112_patch_expression[9];
    u8 record113_line_inc_opcode;
    u8 record113_line_inc_offsetLE[2];
    u8 record113_line_inc_deltaLE;
    u8 record114_patch_opcode;
    u8 record114_patch_relocationKind;
    u8 record114_patch_offsetLE[2];
    u8 record114_patch_expression[3];
    u8 record115_line_inc_opcode;
    u8 record115_line_inc_offsetLE[2];
    u8 record115_line_inc_deltaLE;
    u8 record116_patch_opcode;
    u8 record116_patch_relocationKind;
    u8 record116_patch_offsetLE[2];
    u8 record116_patch_expression[9];
    u8 record117_line_inc_opcode;
    u8 record117_line_inc_offsetLE[2];
    u8 record117_line_inc_deltaLE;
    u8 record118_patch_opcode;
    u8 record118_patch_relocationKind;
    u8 record118_patch_offsetLE[2];
    u8 record118_patch_expression[3];
    u8 record119_line_inc_opcode;
    u8 record119_line_inc_offsetLE[2];
    u8 record119_line_inc_deltaLE;
    u8 record120_line_inc_opcode;
    u8 record120_line_inc_offsetLE[2];
    u8 record120_line_inc_deltaLE;
    u8 record121_patch_opcode;
    u8 record121_patch_relocationKind;
    u8 record121_patch_offsetLE[2];
    u8 record121_patch_expression[9];
    u8 record122_patch_opcode;
    u8 record122_patch_relocationKind;
    u8 record122_patch_offsetLE[2];
    u8 record122_patch_expression[9];
    u8 record123_line_inc_opcode;
    u8 record123_line_inc_offsetLE[2];
    u8 record124_patch_opcode;
    u8 record124_patch_relocationKind;
    u8 record124_patch_offsetLE[2];
    u8 record124_patch_expression[9];
    u8 recordContinuationTail[7];
} Ovldat10EncodedWordsBlock14RestLayout;

typedef struct Ovldat10EncodedWordsBlock3Layout {
    u8 recordContinuation[11];
    u8 record0_line_inc_opcode;
    u8 record0_line_inc_offsetLE[2];
    u8 record1_line_inc_opcode;
    u8 record1_line_inc_offsetLE[2];
    u8 record1_line_inc_deltaLE;
    u8 record2_line_inc_opcode;
    u8 record2_line_inc_offsetLE[2];
    u8 record2_line_inc_deltaLE;
    u8 record3_line_inc_opcode;
    u8 record3_line_inc_offsetLE[2];
    u8 record3_line_inc_deltaLE;
    u8 recordContinuationTail[2];
} Ovldat10EncodedWordsBlock3Layout;

typedef struct Ovldat10EncodedWordsBlock4Layout {
    u8 recordContinuation;
    u8 record0_line_inc_opcode;
    u8 record0_line_inc_offsetLE[2];
    u8 record1_patch_opcode;
    u8 record1_patch_relocationKind;
    u8 record1_patch_offsetLE[2];
    u8 record1_patch_expression[9];
    u8 record2_line_inc_opcode;
    u8 record2_line_inc_offsetLE[2];
    u8 record2_line_inc_deltaLE;
    u8 recordContinuationTail[7];
} Ovldat10EncodedWordsBlock4Layout;

typedef struct Ovldat10EncodedWordsBlock8Layout {
    u8 recordContinuation[6];
    u8 record0_patch_opcode;
    u8 record0_patch_relocationKind;
    u8 record0_patch_offsetLE[2];
    u8 record0_patch_expression[9];
    u8 record1_patch_opcode;
    u8 record1_patch_relocationKind;
    u8 record1_patch_offsetLE[2];
    u8 record1_patch_expression[9];
    u8 recordContinuationTail[4];
} Ovldat10EncodedWordsBlock8Layout;

typedef struct Ovldat10EncodedWordsBlock17Layout {
    u8 recordContinuation[9];
    u8 record0_patch_opcode;
    u8 record0_patch_relocationKind;
    u8 record0_patch_offsetLE[2];
    u8 record0_patch_expression[9];
    u8 record1_patch_opcode;
    u8 record1_patch_relocationKind;
    u8 record1_patch_offsetLE[2];
    u8 record1_patch_expression[9];
    u8 record2_line_inc_opcode;
    u8 record2_line_inc_offsetLE[2];
    u8 record2_line_inc_deltaLE;
    u8 record3_line_set_opcode;
    u8 record3_line_set_offsetLE[2];
    u8 record3_line_set_lineLE[4];
    u8 record4_patch_opcode;
    u8 record4_patch_relocationKind;
    u8 record4_patch_offsetLE[2];
    u8 record4_patch_expression[9];
    u8 record5_line_inc_opcode;
    u8 record5_line_inc_offsetLE[2];
    u8 record5_line_inc_deltaLE;
    u8 record6_patch_opcode;
    u8 record6_patch_relocationKind;
    u8 record6_patch_offsetLE[2];
    u8 record6_patch_expression[9];
    u8 record7_line_inc_opcode;
    u8 record7_line_inc_offsetLE[2];
    u8 record8_line_inc_opcode;
    u8 record8_line_inc_offsetLE[2];
    u8 record8_line_inc_deltaLE;
    u8 record9_line_inc_opcode;
    u8 record9_line_inc_offsetLE[2];
    u8 record9_line_inc_deltaLE;
    u8 record10_line_inc_opcode;
    u8 record10_line_inc_offsetLE[2];
    u8 record10_line_inc_deltaLE;
    u8 record11_line_inc_opcode;
    u8 record11_line_inc_offsetLE[2];
    u8 record12_line_inc_opcode;
    u8 record12_line_inc_offsetLE[2];
    u8 record12_line_inc_deltaLE;
    u8 record13_line_inc_opcode;
    u8 record13_line_inc_offsetLE[2];
    u8 record14_patch_opcode;
    u8 record14_patch_relocationKind;
    u8 record14_patch_offsetLE[2];
    u8 record14_patch_expression[9];
    u8 record15_line_inc_opcode;
    u8 record15_line_inc_offsetLE[2];
    u8 record15_line_inc_deltaLE;
    u8 record16_patch_opcode;
    u8 record16_patch_relocationKind;
    u8 record16_patch_offsetLE[2];
    u8 record16_patch_expression[9];
    u8 record17_patch_opcode;
    u8 record17_patch_relocationKind;
    u8 record17_patch_offsetLE[2];
    u8 record17_patch_expression[9];
    u8 record18_patch_opcode;
    u8 record18_patch_relocationKind;
    u8 record18_patch_offsetLE[2];
    u8 record18_patch_expression[9];
    u8 record19_patch_opcode;
    u8 record19_patch_relocationKind;
    u8 record19_patch_offsetLE[2];
    u8 record19_patch_expression[9];
    u8 record20_line_inc_opcode;
    u8 record20_line_inc_offsetLE[2];
    u8 record20_line_inc_deltaLE;
    u8 record21_line_set_opcode;
    u8 record21_line_set_offsetLE[2];
    u8 record21_line_set_lineLE[4];
    u8 record22_patch_opcode;
    u8 record22_patch_relocationKind;
    u8 record22_patch_offsetLE[2];
    u8 record22_patch_expression[9];
    u8 record23_line_inc_opcode;
    u8 record23_line_inc_offsetLE[2];
    u8 record23_line_inc_deltaLE;
    u8 record24_patch_opcode;
    u8 record24_patch_relocationKind;
    u8 record24_patch_offsetLE[2];
    u8 record24_patch_expression[9];
    u8 record25_line_inc_opcode;
    u8 record25_line_inc_offsetLE[2];
    u8 record26_line_inc_opcode;
    u8 record26_line_inc_offsetLE[2];
    u8 record26_line_inc_deltaLE;
    u8 record27_line_inc_opcode;
    u8 record27_line_inc_offsetLE[2];
    u8 record27_line_inc_deltaLE;
    u8 record28_line_inc_opcode;
    u8 record28_line_inc_offsetLE[2];
    u8 record28_line_inc_deltaLE;
    u8 record29_line_inc_opcode;
    u8 record29_line_inc_offsetLE[2];
    u8 record30_line_inc_opcode;
    u8 record30_line_inc_offsetLE[2];
    u8 record30_line_inc_deltaLE;
    u8 record31_line_inc_opcode;
    u8 record31_line_inc_offsetLE[2];
    u8 record32_patch_opcode;
    u8 record32_patch_relocationKind;
    u8 record32_patch_offsetLE[2];
    u8 record32_patch_expression[9];
    u8 record33_line_inc_opcode;
    u8 record33_line_inc_offsetLE[2];
    u8 record33_line_inc_deltaLE;
    u8 record34_patch_opcode;
    u8 record34_patch_relocationKind;
    u8 record34_patch_offsetLE[2];
    u8 record34_patch_expression[9];
    u8 record35_patch_opcode;
    u8 record35_patch_relocationKind;
    u8 record35_patch_offsetLE[2];
    u8 record35_patch_expression[9];
    u8 record36_line_inc_opcode;
    u8 record36_line_inc_offsetLE[2];
    u8 record36_line_inc_deltaLE;
    u8 record37_line_set_opcode;
    u8 record37_line_set_offsetLE[2];
    u8 record37_line_set_lineLE[4];
    u8 record38_patch_opcode;
    u8 record38_patch_relocationKind;
    u8 record38_patch_offsetLE[2];
    u8 record38_patch_expression[9];
    u8 record39_line_inc_opcode;
    u8 record39_line_inc_offsetLE[2];
    u8 record39_line_inc_deltaLE;
    u8 record40_patch_opcode;
    u8 record40_patch_relocationKind;
    u8 record40_patch_offsetLE[2];
    u8 record40_patch_expression[9];
    u8 record41_line_inc_opcode;
    u8 record41_line_inc_offsetLE[2];
    u8 record42_line_inc_opcode;
    u8 record42_line_inc_offsetLE[2];
    u8 record42_line_inc_deltaLE;
    u8 record43_line_inc_opcode;
    u8 record43_line_inc_offsetLE[2];
    u8 record43_line_inc_deltaLE;
    u8 record44_line_inc_opcode;
    u8 record44_line_inc_offsetLE[2];
    u8 record44_line_inc_deltaLE;
    u8 record45_line_inc_opcode;
    u8 record45_line_inc_offsetLE[2];
    u8 record46_line_inc_opcode;
    u8 record46_line_inc_offsetLE[2];
    u8 record46_line_inc_deltaLE;
    u8 record47_patch_opcode;
    u8 record47_patch_relocationKind;
    u8 record47_patch_offsetLE[2];
    u8 record47_patch_expression[9];
    u8 record48_line_inc_opcode;
    u8 record48_line_inc_offsetLE[2];
    u8 record48_line_inc_deltaLE;
    u8 record49_patch_opcode;
    u8 record49_patch_relocationKind;
    u8 record49_patch_offsetLE[2];
    u8 record49_patch_expression[9];
    u8 record50_patch_opcode;
    u8 record50_patch_relocationKind;
    u8 record50_patch_offsetLE[2];
    u8 record50_patch_expression[9];
    u8 record51_patch_opcode;
    u8 record51_patch_relocationKind;
    u8 record51_patch_offsetLE[2];
    u8 record51_patch_expression[9];
    u8 record52_patch_opcode;
    u8 record52_patch_relocationKind;
    u8 record52_patch_offsetLE[2];
    u8 record52_patch_expression[9];
    u8 record53_patch_opcode;
    u8 record53_patch_relocationKind;
    u8 record53_patch_offsetLE[2];
    u8 record53_patch_expression[9];
    u8 record54_patch_opcode;
    u8 record54_patch_relocationKind;
    u8 record54_patch_offsetLE[2];
    u8 record54_patch_expression[9];
    u8 record55_line_inc_opcode;
    u8 record55_line_inc_offsetLE[2];
    u8 record55_line_inc_deltaLE;
    u8 record56_patch_opcode;
    u8 record56_patch_relocationKind;
    u8 record56_patch_offsetLE[2];
    u8 record56_patch_expression[9];
    u8 record57_line_set_opcode;
    u8 record57_line_set_offsetLE[2];
    u8 record57_line_set_lineLE[4];
    u8 record58_patch_opcode;
    u8 record58_patch_relocationKind;
    u8 record58_patch_offsetLE[2];
    u8 record58_patch_expression[9];
    u8 record59_line_inc_opcode;
    u8 record59_line_inc_offsetLE[2];
    u8 record59_line_inc_deltaLE;
    u8 record60_patch_opcode;
    u8 record60_patch_relocationKind;
    u8 record60_patch_offsetLE[2];
    u8 record60_patch_expression[9];
    u8 record61_line_inc_opcode;
    u8 record61_line_inc_offsetLE[2];
    u8 record61_line_inc_deltaLE;
    u8 record62_patch_opcode;
    u8 record62_patch_relocationKind;
    u8 record62_patch_offsetLE[2];
    u8 record62_patch_expression[9];
    u8 record63_patch_opcode;
    u8 record63_patch_relocationKind;
    u8 record63_patch_offsetLE[2];
    u8 record63_patch_expression[9];
    u8 record64_line_inc_opcode;
    u8 record64_line_inc_offsetLE[2];
    u8 record65_patch_opcode;
    u8 record65_patch_relocationKind;
    u8 record65_patch_offsetLE[2];
    u8 record65_patch_expression[9];
    u8 record66_line_set_opcode;
    u8 record66_line_set_offsetLE[2];
    u8 record66_line_set_lineLE[4];
    u8 record67_patch_opcode;
    u8 record67_patch_relocationKind;
    u8 record67_patch_offsetLE[2];
    u8 record67_patch_expression[9];
    u8 record68_line_inc_opcode;
    u8 record68_line_inc_offsetLE[2];
    u8 record68_line_inc_deltaLE;
    u8 record69_patch_opcode;
    u8 record69_patch_relocationKind;
    u8 record69_patch_offsetLE[2];
    u8 record69_patch_expression[9];
    u8 record70_line_inc_opcode;
    u8 record70_line_inc_offsetLE[2];
    u8 record71_line_inc_opcode;
    u8 record71_line_inc_offsetLE[2];
    u8 record71_line_inc_deltaLE;
    u8 record72_line_inc_opcode;
    u8 record72_line_inc_offsetLE[2];
    u8 record72_line_inc_deltaLE;
    u8 record73_line_inc_opcode;
    u8 record73_line_inc_offsetLE[2];
    u8 record73_line_inc_deltaLE;
    u8 record74_line_inc_opcode;
    u8 record74_line_inc_offsetLE[2];
    u8 record75_line_inc_opcode;
    u8 record75_line_inc_offsetLE[2];
    u8 record75_line_inc_deltaLE;
    u8 record76_line_inc_opcode;
    u8 record76_line_inc_offsetLE[2];
    u8 record76_line_inc_deltaLE;
    u8 record77_patch_opcode;
    u8 record77_patch_relocationKind;
    u8 record77_patch_offsetLE[2];
    u8 record77_patch_expression[9];
    u8 record78_patch_opcode;
    u8 record78_patch_relocationKind;
    u8 record78_patch_offsetLE[2];
    u8 record78_patch_expression[9];
    u8 record79_patch_opcode;
    u8 record79_patch_relocationKind;
    u8 record79_patch_offsetLE[2];
    u8 record79_patch_expression[3];
    u8 record80_patch_opcode;
    u8 record80_patch_relocationKind;
    u8 record80_patch_offsetLE[2];
    u8 record80_patch_expression[3];
    u8 record81_patch_opcode;
    u8 record81_patch_relocationKind;
    u8 record81_patch_offsetLE[2];
    u8 record81_patch_expression[3];
    u8 record82_line_inc_opcode;
    u8 record82_line_inc_offsetLE[2];
    u8 record82_line_inc_deltaLE;
    u8 record83_patch_opcode;
    u8 record83_patch_relocationKind;
    u8 record83_patch_offsetLE[2];
    u8 record83_patch_expression[9];
    u8 record84_line_inc_opcode;
    u8 record84_line_inc_offsetLE[2];
    u8 record84_line_inc_deltaLE;
    u8 record85_patch_opcode;
    u8 record85_patch_relocationKind;
    u8 record85_patch_offsetLE[2];
    u8 record85_patch_expression[3];
    u8 record86_patch_opcode;
    u8 record86_patch_relocationKind;
    u8 record86_patch_offsetLE[2];
    u8 record86_patch_expression[3];
    u8 record87_patch_opcode;
    u8 record87_patch_relocationKind;
    u8 record87_patch_offsetLE[2];
    u8 record87_patch_expression[3];
    u8 record88_line_inc_opcode;
    u8 record88_line_inc_offsetLE[2];
    u8 record89_line_set_opcode;
    u8 record89_line_set_offsetLE[2];
    u8 record89_line_set_lineLE[4];
    u8 record90_patch_opcode;
    u8 record90_patch_relocationKind;
    u8 record90_patch_offsetLE[2];
    u8 record90_patch_expression[9];
    u8 record91_line_inc_opcode;
    u8 record91_line_inc_offsetLE[2];
    u8 record91_line_inc_deltaLE;
    u8 record92_patch_opcode;
    u8 record92_patch_relocationKind;
    u8 record92_patch_offsetLE[2];
    u8 record92_patch_expression[9];
    u8 record93_line_inc_opcode;
    u8 record93_line_inc_offsetLE[2];
    u8 record93_line_inc_deltaLE;
    u8 record94_patch_opcode;
    u8 record94_patch_relocationKind;
    u8 record94_patch_offsetLE[2];
    u8 record94_patch_expression[9];
    u8 record95_patch_opcode;
    u8 record95_patch_relocationKind;
    u8 record95_patch_offsetLE[2];
    u8 record95_patch_expression[9];
    u8 record96_line_inc_opcode;
    u8 record96_line_inc_offsetLE[2];
    u8 record96_line_inc_deltaLE;
    u8 record97_line_inc_opcode;
    u8 record97_line_inc_offsetLE[2];
    u8 record97_line_inc_deltaLE;
    u8 record98_patch_opcode;
    u8 record98_patch_relocationKind;
    u8 record98_patch_offsetLE[2];
    u8 record98_patch_expression[3];
    u8 record99_patch_opcode;
    u8 record99_patch_relocationKind;
    u8 record99_patch_offsetLE[2];
    u8 record99_patch_expression[3];
    u8 record100_patch_opcode;
    u8 record100_patch_relocationKind;
    u8 record100_patch_offsetLE[2];
    u8 record100_patch_expression[9];
    u8 record101_patch_opcode;
    u8 record101_patch_relocationKind;
    u8 record101_patch_offsetLE[2];
    u8 record101_patch_expression[9];
    u8 record102_patch_opcode;
    u8 record102_patch_relocationKind;
    u8 record102_patch_offsetLE[2];
    u8 record102_patch_expression[3];
    u8 record103_line_inc_opcode;
    u8 record103_line_inc_offsetLE[2];
    u8 record103_line_inc_deltaLE;
    u8 record104_line_set_opcode;
    u8 record104_line_set_offsetLE[2];
    u8 record104_line_set_lineLE[4];
    u8 record105_patch_opcode;
    u8 record105_patch_relocationKind;
    u8 record105_patch_offsetLE[2];
    u8 record105_patch_expression[9];
    u8 record106_line_inc_opcode;
    u8 record106_line_inc_offsetLE[2];
    u8 record106_line_inc_deltaLE;
    u8 record107_patch_opcode;
    u8 record107_patch_relocationKind;
    u8 record107_patch_offsetLE[2];
    u8 record107_patch_expression[9];
    u8 record108_line_inc_opcode;
    u8 record108_line_inc_offsetLE[2];
    u8 record108_line_inc_deltaLE;
    u8 record109_patch_opcode;
    u8 record109_patch_relocationKind;
    u8 record109_patch_offsetLE[2];
    u8 record109_patch_expression[9];
    u8 record110_patch_opcode;
    u8 record110_patch_relocationKind;
    u8 record110_patch_offsetLE[2];
    u8 record110_patch_expression[9];
    u8 record111_line_inc_opcode;
    u8 record111_line_inc_offsetLE[2];
    u8 record111_line_inc_deltaLE;
    u8 record112_patch_opcode;
    u8 record112_patch_relocationKind;
    u8 record112_patch_offsetLE[2];
    u8 record112_patch_expression[9];
    u8 record113_line_inc_opcode;
    u8 record113_line_inc_offsetLE[2];
    u8 record113_line_inc_deltaLE;
    u8 record114_patch_opcode;
    u8 record114_patch_relocationKind;
    u8 record114_patch_offsetLE[2];
    u8 record114_patch_expression[9];
    u8 record115_patch_opcode;
    u8 record115_patch_relocationKind;
    u8 record115_patch_offsetLE[2];
    u8 record115_patch_expression[9];
    u8 record116_line_inc_opcode;
    u8 record116_line_inc_offsetLE[2];
    u8 record116_line_inc_deltaLE;
    u8 record117_patch_opcode;
    u8 record117_patch_relocationKind;
    u8 record117_patch_offsetLE[2];
    u8 record117_patch_expression[3];
    u8 record118_patch_opcode;
    u8 record118_patch_relocationKind;
    u8 record118_patch_offsetLE[2];
    u8 record118_patch_expression[3];
    u8 record119_patch_opcode;
    u8 record119_patch_relocationKind;
    u8 record119_patch_offsetLE[2];
    u8 record119_patch_expression[9];
    u8 record120_patch_opcode;
    u8 record120_patch_relocationKind;
    u8 record120_patch_offsetLE[2];
    u8 record120_patch_expression[9];
    u8 record121_patch_opcode;
    u8 record121_patch_relocationKind;
    u8 record121_patch_offsetLE[2];
    u8 record121_patch_expression[3];
    u8 record122_line_inc_opcode;
    u8 record122_line_inc_offsetLE[2];
    u8 record123_patch_opcode;
    u8 record123_patch_relocationKind;
    u8 record123_patch_offsetLE[2];
    u8 record123_patch_expression[9];
    u8 record124_line_set_opcode;
    u8 record124_line_set_offsetLE[2];
    u8 record124_line_set_lineLE[4];
    u8 record125_patch_opcode;
    u8 record125_patch_relocationKind;
    u8 record125_patch_offsetLE[2];
    u8 record125_patch_expression[9];
    u8 record126_line_set_opcode;
    u8 record126_line_set_offsetLE[2];
    u8 record126_line_set_lineLE[4];
    u8 record127_patch_opcode;
    u8 record127_patch_relocationKind;
    u8 record127_patch_offsetLE[2];
    u8 record127_patch_expression[9];
    u8 record128_line_inc_opcode;
    u8 record128_line_inc_offsetLE[2];
    u8 record128_line_inc_deltaLE;
    u8 record129_line_inc_opcode;
    u8 record129_line_inc_offsetLE[2];
    u8 record129_line_inc_deltaLE;
    u8 record130_line_inc_opcode;
    u8 record130_line_inc_offsetLE[2];
    u8 record130_line_inc_deltaLE;
    u8 record131_line_inc_opcode;
    u8 record131_line_inc_offsetLE[2];
    u8 record131_line_inc_deltaLE;
    u8 record132_line_inc_opcode;
    u8 record132_line_inc_offsetLE[2];
    u8 record132_line_inc_deltaLE;
    u8 record133_patch_opcode;
    u8 record133_patch_relocationKind;
    u8 record133_patch_offsetLE[2];
    u8 record133_patch_expression[9];
    u8 record134_patch_opcode;
    u8 record134_patch_relocationKind;
    u8 record134_patch_offsetLE[2];
    u8 record134_patch_expression[9];
    u8 record135_patch_opcode;
    u8 record135_patch_relocationKind;
    u8 record135_patch_offsetLE[2];
    u8 record135_patch_expression[9];
    u8 record136_patch_opcode;
    u8 record136_patch_relocationKind;
    u8 record136_patch_offsetLE[2];
    u8 record136_patch_expression[9];
    u8 record137_patch_opcode;
    u8 record137_patch_relocationKind;
    u8 record137_patch_offsetLE[2];
    u8 record137_patch_expression[9];
    u8 record138_patch_opcode;
    u8 record138_patch_relocationKind;
    u8 record138_patch_offsetLE[2];
    u8 record138_patch_expression[3];
    u8 record139_line_inc_opcode;
    u8 record139_line_inc_offsetLE[2];
    u8 record139_line_inc_deltaLE;
    u8 record140_line_inc_opcode;
    u8 record140_line_inc_offsetLE[2];
    u8 record140_line_inc_deltaLE;
    u8 record141_line_inc_opcode;
    u8 record141_line_inc_offsetLE[2];
    u8 record141_line_inc_deltaLE;
    u8 record142_line_inc_opcode;
    u8 record142_line_inc_offsetLE[2];
    u8 record142_line_inc_deltaLE;
    u8 record143_line_inc_opcode;
    u8 record143_line_inc_offsetLE[2];
    u8 record143_line_inc_deltaLE;
    u8 record144_patch_opcode;
    u8 record144_patch_relocationKind;
    u8 record144_patch_offsetLE[2];
    u8 record144_patch_expression[3];
    u8 record145_line_inc_opcode;
    u8 record145_line_inc_offsetLE[2];
    u8 record146_patch_opcode;
    u8 record146_patch_relocationKind;
    u8 record146_patch_offsetLE[2];
    u8 record146_patch_expression[9];
    u8 record147_patch_opcode;
    u8 record147_patch_relocationKind;
    u8 record147_patch_offsetLE[2];
    u8 record147_patch_expression[9];
    u8 record148_line_inc_opcode;
    u8 record148_line_inc_offsetLE[2];
    u8 record149_patch_opcode;
    u8 record149_patch_relocationKind;
    u8 record149_patch_offsetLE[2];
    u8 record149_patch_expression[9];
    u8 record150_patch_opcode;
    u8 record150_patch_relocationKind;
    u8 record150_patch_offsetLE[2];
    u8 record150_patch_expression[9];
    u8 record151_line_inc_opcode;
    u8 record151_line_inc_offsetLE[2];
    u8 record151_line_inc_deltaLE;
    u8 record152_patch_opcode;
    u8 record152_patch_relocationKind;
    u8 record152_patch_offsetLE[2];
    u8 record152_patch_expression[9];
    u8 record153_patch_opcode;
    u8 record153_patch_relocationKind;
    u8 record153_patch_offsetLE[2];
    u8 record153_patch_expression[9];
    u8 record154_line_inc_opcode;
    u8 record154_line_inc_offsetLE[2];
    u8 record154_line_inc_deltaLE;
    u8 record155_line_inc_opcode;
    u8 record155_line_inc_offsetLE[2];
    u8 record155_line_inc_deltaLE;
    u8 record156_patch_opcode;
    u8 record156_patch_relocationKind;
    u8 record156_patch_offsetLE[2];
    u8 record156_patch_expression[9];
    u8 record157_patch_opcode;
    u8 record157_patch_relocationKind;
    u8 record157_patch_offsetLE[2];
    u8 record157_patch_expression[9];
    u8 record158_patch_opcode;
    u8 record158_patch_relocationKind;
    u8 record158_patch_offsetLE[2];
    u8 record158_patch_expression[9];
    u8 record159_patch_opcode;
    u8 record159_patch_relocationKind;
    u8 record159_patch_offsetLE[2];
    u8 record159_patch_expression[9];
    u8 record160_switch_opcode;
    u8 record160_switch_offsetLE[2];
    u8 recordContinuationTail[3];
} Ovldat10EncodedWordsBlock17Layout;

typedef struct DebugColorThicknessLabels {
    unsigned int titleTextPointer;
    unsigned char redText[20];
    unsigned int redTextPointer;
    unsigned char greenText[20];
    unsigned int greenTextPointer;
    unsigned char blueText[20];
    unsigned int blueTextPointer;
    unsigned char thicknessText[20];
    unsigned int thicknessTextPointer;
} DebugColorThicknessLabels;
extern DebugColorThicknessLabels g_debugColorThicknessLabels;

/* One us-rev1 weapon slot presentation row (Source/Data/Frontend/G/constants.cpp). */
struct WeaponSlotPresentationRow {
    void *ammoCapacityPointers[7];
    float viewOffset[3];
    ConstantsEncodedWordsBlock7Layout stateBinding;
    struct {
        unsigned int text;
        unsigned short ids[2];
    } presentation;
    unsigned short markers[2];
    struct {
        unsigned short limits[4];
        unsigned int flags;
    } trailer;
    unsigned int padding;
};

extern struct WeaponSlotPresentationRow g_weaponSlotPresentationRows[8];

#endif

#if defined(VERSION_US)
extern Ovldat2ConstantWordsLayout k_playerNavDirectionAndHandlerTable;
#endif
