#ifndef DATA_REST_SOURCE_RECORDS_H
#define DATA_REST_SOURCE_RECORDS_H
#include "TYPES.H"

/* Source records for the fixed data/link sections. Field layouts follow consumers. */
typedef struct RestLinkerAlignmentFill4 {
    u8 linkerAlignmentFill[4];
} RestLinkerAlignmentFill4;

typedef struct RestLinkerAlignmentFill12 {
    u8 linkerAlignmentFill[12];
} RestLinkerAlignmentFill12;

typedef struct RestLinkerAlignmentFill8 {
    u8 linkerAlignmentFill[8];
} RestLinkerAlignmentFill8;

typedef struct RestCharacterPreviewKeys05Words1Record270 {
    s32 resource;
    s32 character;
} RestCharacterPreviewKeys05Words1Record270;

typedef struct RestOvltab10Ovltab10CppRetainedWords14Record271 {
    s32 animation;
} RestOvltab10Ovltab10CppRetainedWords14Record271;

typedef struct RestOvltab10Ovltab10CppRetainedWords20Record272 {
    s32 lightOffsets[4];
} RestOvltab10Ovltab10CppRetainedWords20Record272;

typedef struct RestCharacterPreviewKeys06Words1Record273 {
    s32 resource;
    s32 character;
} RestCharacterPreviewKeys06Words1Record273;

typedef struct RestOvltab10Ovltab10CppRetainedWords8Record274 {
    s32 animation;
} RestOvltab10Ovltab10CppRetainedWords8Record274;

typedef struct RestCharacterPreviewLights06Words1Record275 {
    s32 lightOffsets[4];
} RestCharacterPreviewLights06Words1Record275;

typedef struct RestCharacterPreviewKeys07Words1Record276 {
    s32 resource;
    s32 character;
} RestCharacterPreviewKeys07Words1Record276;

typedef struct RestOvltab10Ovltab10CppRetainedWords15Record277 {
    s32 animation;
} RestOvltab10Ovltab10CppRetainedWords15Record277;

typedef struct RestCharacterPreviewLights07Words1Record278 {
    s32 lightOffsets[4];
} RestCharacterPreviewLights07Words1Record278;

typedef struct RestCharacterPreviewKeys08Words1Record279 {
    s32 resource;
    s32 character;
} RestCharacterPreviewKeys08Words1Record279;

typedef struct RestOvltab10Ovltab10CppRetainedWords12Record280 {
    s32 animation;
} RestOvltab10Ovltab10CppRetainedWords12Record280;

typedef struct RestCharacterPreviewLights08Words1Record281 {
    s32 lightOffsets[4];
} RestCharacterPreviewLights08Words1Record281;

typedef struct RestCharacterPreviewKeys09Words1Record282 {
    s32 resource;
    s32 character;
} RestCharacterPreviewKeys09Words1Record282;

typedef struct RestOvltab10Ovltab10CppRetainedWords13Record283 {
    s32 animation;
} RestOvltab10Ovltab10CppRetainedWords13Record283;

typedef struct RestOvltab10Ovltab10CppRetainedWords17Record284 {
    s32 lightOffsets[4];
} RestOvltab10Ovltab10CppRetainedWords17Record284;

typedef struct RestCharacterPreviewKeys10Words1Record285 {
    s32 resource;
    s32 character;
} RestCharacterPreviewKeys10Words1Record285;

typedef struct RestOvltab10Ovltab10CppRetainedWords16Record286 {
    s32 animation;
} RestOvltab10Ovltab10CppRetainedWords16Record286;

typedef struct RestOvltab10Ovltab10CppRetainedWords18Record287 {
    s32 lightOffsets[4];
} RestOvltab10Ovltab10CppRetainedWords18Record287;

typedef struct RestCharacterPreviewKeys11Words1Record288 {
    s32 resource;
    s32 character;
} RestCharacterPreviewKeys11Words1Record288;

typedef struct RestOvltab10Ovltab10CppRetainedWords6Record289 {
    s32 animation;
} RestOvltab10Ovltab10CppRetainedWords6Record289;

typedef struct RestOvltab10Ovltab10CppRetainedWords19Record290 {
    s32 lightOffsets[4];
} RestOvltab10Ovltab10CppRetainedWords19Record290;

typedef struct RestCharacterPreviewKeys12Words1Record291 {
    s32 resource;
    s32 character;
} RestCharacterPreviewKeys12Words1Record291;

typedef struct RestOvltab10Ovltab10CppRetainedWords10Record292 {
    s32 animation;
} RestOvltab10Ovltab10CppRetainedWords10Record292;

typedef struct RestCharacterPreviewLights12Words1Record293 {
    s32 lightOffsets[4];
} RestCharacterPreviewLights12Words1Record293;

typedef struct RestPlayerStateSpecialTiming01Words1Record645 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming01Words1Record645;

typedef struct RestPlayerStateSpecialCallbacks02PointerWords1Record647 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks02PointerWords1Record647;

typedef struct RestPlayerStateSpecialTiming02Words1Record649 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming02Words1Record649;

typedef struct RestPlayerStateSpecialCallbacks03PointerWords1Record651 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks03PointerWords1Record651;

typedef struct RestPlayerStateSpecialTiming03Words1Record653 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming03Words1Record653;

typedef struct RestPlayerStateSpecialCallbacks04PointerWords1Record655 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks04PointerWords1Record655;

typedef struct RestPlayerStateSpecialTiming04Words1Record657 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming04Words1Record657;

typedef struct RestPlayerStateSpecialCallbacks05PointerWords1Record659 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks05PointerWords1Record659;

typedef struct RestPlayerStateSpecialTiming05Words1Record661 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming05Words1Record661;

typedef struct RestPlayerStateSpecialCallbacks06PointerWords1Record663 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks06PointerWords1Record663;

typedef struct RestPlayerStateSpecialTiming06Words1Record665 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming06Words1Record665;

typedef struct RestPlayerStateSpecialCallbacks07PointerWords1Record667 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks07PointerWords1Record667;

typedef struct RestPlayerStateSpecialTiming07Words1Record669 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming07Words1Record669;

typedef struct RestPlayerStateSpecialCallbacks08PointerWords1Record671 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks08PointerWords1Record671;

typedef struct RestPlayerStateSpecialTiming08Words1Record673 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming08Words1Record673;

typedef struct RestPlayerStateSpecialCallbacks09PointerWords1Record675 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks09PointerWords1Record675;

typedef struct RestPlayerStateSpecialTiming09Words1Record677 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming09Words1Record677;

typedef struct RestPlayerStateSpecialCallbacks10PointerWords1Record679 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks10PointerWords1Record679;

typedef struct RestPlayerStateSpecialTiming10Words1Record681 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming10Words1Record681;

typedef struct RestPlayerStateSpecialCallbacks11PointerWords1Record683 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks11PointerWords1Record683;

typedef struct RestPlayerStateSpecialTiming11Words1Record685 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming11Words1Record685;

typedef struct RestPlayerStateSpecialCallbacks12PointerWords1Record687 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks12PointerWords1Record687;

typedef struct RestPlayerStateSpecialTiming12Words1Record689 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming12Words1Record689;

typedef struct RestPlayerStateSpecialCallbacks13PointerWords1Record691 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks13PointerWords1Record691;

typedef struct RestPlayerStateSpecialTiming13Words1Record693 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming13Words1Record693;

typedef struct RestPlayerStateSpecialCallbacks14PointerWords1Record695 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks14PointerWords1Record695;

typedef struct RestPlayerStateSpecialTiming14Words1Record697 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming14Words1Record697;

typedef struct RestPlayerStateSpecialCallbacks15PointerWords1Record699 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks15PointerWords1Record699;

typedef struct RestPlayerStateSpecialTiming15Words1Record701 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming15Words1Record701;

typedef struct RestPlayerStateSpecialCallbacks16PointerWords1Record703 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks16PointerWords1Record703;

typedef struct RestPlayerStateSpecialTiming16Words1Record705 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateSpecialTiming16Words1Record705;

typedef struct RestPlayerStateSpecialCallbacks17PointerWords1Record707 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateSpecialCallbacks17PointerWords1Record707;

typedef struct RestoverlayOneFLinkRecordLinkWordsRecord708 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordLinkWordsRecord708;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock1Record709 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock1Record709;

typedef struct RestoverlayOneFLinkRecordConstantWordsRecord710 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsRecord710;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock1Record711 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock1Record711;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock2Record712 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock2Record712;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock2Record713 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock2Record713;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock3Record714 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordLinkWordsBlock3Record714;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock4Record715 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock4Record715;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock3Record716 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock3Record716;

typedef struct RestoverlayOneFLinkRecordSentinelWordsRecord717 {
    s32 endState;
} RestoverlayOneFLinkRecordSentinelWordsRecord717;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock4Record718 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock4Record718;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock5Record719 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock5Record719;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock5Record720 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock5Record720;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock6Record721 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock6Record721;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock6Record722 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock6Record722;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock7Record723 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock7Record723;

typedef struct RestoverlayOneFLinkRecordSentinelWordsBlock1Record724 {
    s32 endState;
} RestoverlayOneFLinkRecordSentinelWordsBlock1Record724;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock7Record725 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordLinkWordsBlock7Record725;

typedef struct RestoverlayOneFLinkRecordSentinelWordsBlock2Record728 {
    s32 endState;
} RestoverlayOneFLinkRecordSentinelWordsBlock2Record728;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock9Record729 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock9Record729;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock9Record730 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock9Record730;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock10Record731 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock10Record731;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock11Record732 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock11Record732;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock10Record733 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock10Record733;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock12Record734 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock12Record734;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock11Record735 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordLinkWordsBlock11Record735;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock12Record736 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock12Record736;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock13Record737 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock13Record737;

typedef struct RestoverlayOneFLinkRecordSentinelWordsBlock3Record738 {
    s32 endState;
} RestoverlayOneFLinkRecordSentinelWordsBlock3Record738;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock14Record740 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock14Record740;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock13Record741 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock13Record741;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock15Record742 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock15Record742;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock16Record743 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock16Record743;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock14Record744 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock14Record744;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock17Record745 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock17Record745;

typedef struct RestoverlayOneFLinkRecordSentinelWordsBlock4Record746 {
    s32 endState;
} RestoverlayOneFLinkRecordSentinelWordsBlock4Record746;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock18Record748 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock18Record748;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock15Record749 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock15Record749;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock19Record750 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock19Record750;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock20Record751 {
    s32 state;
    u32 enterAddress;
} RestoverlayOneFLinkRecordConstantWordsBlock20Record751;

typedef struct RestoverlayOneFLinkRecordLinkWordsBlock16Record752 {
    u32 selectorAddress;
    u32 flags;
} RestoverlayOneFLinkRecordLinkWordsBlock16Record752;

typedef struct RestoverlayOneFLinkRecordConstantWordsBlock21Record753 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestoverlayOneFLinkRecordConstantWordsBlock21Record753;

typedef struct RestoverlayOneFLinkRecordSentinelWordsBlock5Record754 {
    s32 endState;
} RestoverlayOneFLinkRecordSentinelWordsBlock5Record754;

typedef struct RestoverlayOneIPreviewConstantWordsRecord755 {
    s32 lightOffsets[4];
} RestoverlayOneIPreviewConstantWordsRecord755;

typedef struct RestoverlayOneIPreviewConstantWordsBlock1Record758 {
    s32 resource;
    s32 character;
} RestoverlayOneIPreviewConstantWordsBlock1Record758;

typedef struct RestoverlayOneIPreviewConstantWordsBlock2Record759 {
    s32 animation;
} RestoverlayOneIPreviewConstantWordsBlock2Record759;

typedef struct RestoverlayOneIPreviewConstantWordsBlock3Record760 {
    s32 lightOffsets[4];
} RestoverlayOneIPreviewConstantWordsBlock3Record760;

typedef struct RestoverlayOneIPreviewConstantWordsBlock4Record762 {
    s32 resource;
    s32 character;
} RestoverlayOneIPreviewConstantWordsBlock4Record762;

typedef struct RestoverlayOneIPreviewConstantWordsBlock5Record763 {
    s32 animation;
} RestoverlayOneIPreviewConstantWordsBlock5Record763;

typedef struct RestoverlayOneIPreviewConstantWordsBlock6Record764 {
    s32 lightOffsets[4];
} RestoverlayOneIPreviewConstantWordsBlock6Record764;

typedef struct RestoverlayOneIPreviewConstantWordsBlock7Record766 {
    s32 resource;
    s32 character;
} RestoverlayOneIPreviewConstantWordsBlock7Record766;

typedef struct RestoverlayOneIPreviewConstantWordsBlock8Record767 {
    s32 animation;
} RestoverlayOneIPreviewConstantWordsBlock8Record767;

typedef struct RestoverlayOneIPreviewConstantWordsBlock9Record768 {
    s32 lightOffsets[4];
} RestoverlayOneIPreviewConstantWordsBlock9Record768;

typedef struct RestoverlayOneIPreviewConstantWordsBlock10Record770 {
    s32 resource;
    s32 character;
} RestoverlayOneIPreviewConstantWordsBlock10Record770;

typedef struct RestoverlayOneIPreviewConstantWordsBlock11Record771 {
    s32 animation;
} RestoverlayOneIPreviewConstantWordsBlock11Record771;

typedef struct RestoverlayOneIPreviewConstantWordsBlock12Record772 {
    s32 lightOffsets[4];
} RestoverlayOneIPreviewConstantWordsBlock12Record772;

typedef struct RestplayerStateNormalCallbacks01WordsRecord798 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks01WordsRecord798;

typedef struct RestPlayerStateNormalCallbacks01TrailWordsRecord799 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks01TrailWordsRecord799;

typedef struct RestplayerStateNormalTiming01WordsRecord800 {
    s32 duration;
    s32 nextAnimation;
} RestplayerStateNormalTiming01WordsRecord800;

typedef struct RestPlayerStateNormalTiming01TrailWordsRecord801 {
    u32 stateFlags;
} RestPlayerStateNormalTiming01TrailWordsRecord801;

typedef struct RestplayerStateNormalCallbacks02WordsRecord802 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks02WordsRecord802;

typedef struct RestPlayerStateNormalCallbacks02TrailWordsRecord803 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks02TrailWordsRecord803;

typedef struct RestplayerStateNormalTiming02WordsRecord804 {
    s32 duration;
    s32 nextAnimation;
} RestplayerStateNormalTiming02WordsRecord804;

typedef struct RestplayerStateNormalCallbacks03WordsRecord806 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks03WordsRecord806;

typedef struct RestPlayerStateNormalCallbacks03TrailWordsRecord807 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks03TrailWordsRecord807;

typedef struct RestplayerStateNormalTiming03WordsRecord808 {
    s32 duration;
    s32 nextAnimation;
} RestplayerStateNormalTiming03WordsRecord808;

typedef struct RestPlayerStateNormalTiming03TrailWordsRecord809 {
    u32 stateFlags;
} RestPlayerStateNormalTiming03TrailWordsRecord809;

typedef struct RestplayerStateNormalCallbacks04WordsRecord810 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks04WordsRecord810;

typedef struct RestPlayerStateNormalCallbacks04TrailWordsRecord811 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks04TrailWordsRecord811;

typedef struct RestPlayerStateNormalTiming04WordsRecord812 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateNormalTiming04WordsRecord812;

typedef struct RestPlayerStateNormalCallbacks05WordsRecord814 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateNormalCallbacks05WordsRecord814;

typedef struct RestplayerStateNormalCallbacks05TrailWordsRecord815 {
    u32 exitAddress;
} RestplayerStateNormalCallbacks05TrailWordsRecord815;

typedef struct RestplayerStateNormalTiming05WordsRecord816 {
    s32 duration;
    s32 nextAnimation;
} RestplayerStateNormalTiming05WordsRecord816;

typedef struct RestPlayerStateNormalTiming05TrailWordsRecord817 {
    u32 stateFlags;
} RestPlayerStateNormalTiming05TrailWordsRecord817;

typedef struct RestPlayerStateNormalCallbacks06WordsRecord818 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateNormalCallbacks06WordsRecord818;

typedef struct RestplayerStateNormalCallbacks06TrailWordsRecord819 {
    u32 exitAddress;
} RestplayerStateNormalCallbacks06TrailWordsRecord819;

typedef struct RestPlayerStateNormalTiming06WordsRecord820 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateNormalTiming06WordsRecord820;

typedef struct RestPlayerStateNormalCallbacks07WordsRecord822 {
    u32 enterAddress;
    u32 updateAddress;
} RestPlayerStateNormalCallbacks07WordsRecord822;

typedef struct RestplayerStateNormalCallbacks07TrailWordsRecord823 {
    u32 exitAddress;
} RestplayerStateNormalCallbacks07TrailWordsRecord823;

typedef struct RestPlayerStateNormalTiming07WordsRecord824 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateNormalTiming07WordsRecord824;

typedef struct RestplayerStateNormalTiming07TrailWordsRecord825 {
    u32 stateFlags;
} RestplayerStateNormalTiming07TrailWordsRecord825;

typedef struct RestplayerStateNormalCallbacks08WordsRecord826 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks08WordsRecord826;

typedef struct RestPlayerStateNormalCallbacks08TrailWordsRecord827 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks08TrailWordsRecord827;

typedef struct RestplayerStateNormalTiming08WordsRecord828 {
    s32 duration;
    s32 nextAnimation;
} RestplayerStateNormalTiming08WordsRecord828;

typedef struct RestplayerStateNormalCallbacks09WordsRecord830 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks09WordsRecord830;

typedef struct RestPlayerStateNormalCallbacks09TrailWordsRecord831 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks09TrailWordsRecord831;

typedef struct RestplayerStateNormalTiming09WordsRecord832 {
    s32 duration;
    s32 nextAnimation;
} RestplayerStateNormalTiming09WordsRecord832;

typedef struct RestPlayerStateNormalTiming09TrailWordsRecord833 {
    u32 stateFlags;
} RestPlayerStateNormalTiming09TrailWordsRecord833;

typedef struct RestplayerStateNormalCallbacks10WordsRecord834 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks10WordsRecord834;

typedef struct RestPlayerStateNormalCallbacks10TrailWordsRecord835 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks10TrailWordsRecord835;

typedef struct RestplayerStateNormalTiming10WordsRecord836 {
    s32 duration;
    s32 nextAnimation;
} RestplayerStateNormalTiming10WordsRecord836;

typedef struct RestplayerStateNormalCallbacks11WordsRecord838 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks11WordsRecord838;

typedef struct RestPlayerStateNormalCallbacks11TrailWordsRecord839 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks11TrailWordsRecord839;

typedef struct RestPlayerStateNormalTiming11WordsRecord840 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateNormalTiming11WordsRecord840;

typedef struct RestplayerStateNormalTiming11TrailWordsRecord841 {
    u32 stateFlags;
} RestplayerStateNormalTiming11TrailWordsRecord841;

typedef struct RestplayerStateNormalCallbacks12WordsRecord842 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks12WordsRecord842;

typedef struct RestPlayerStateNormalCallbacks12TrailWordsRecord843 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks12TrailWordsRecord843;

typedef struct RestPlayerStateNormalTiming12WordsRecord844 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateNormalTiming12WordsRecord844;

typedef struct RestplayerStateNormalCallbacks13WordsRecord846 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks13WordsRecord846;

typedef struct RestPlayerStateNormalCallbacks13TrailWordsRecord847 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks13TrailWordsRecord847;

typedef struct RestplayerStateNormalTiming13WordsRecord848 {
    s32 duration;
    s32 nextAnimation;
} RestplayerStateNormalTiming13WordsRecord848;

typedef struct RestPlayerStateNormalTiming13TrailWordsRecord849 {
    u32 stateFlags;
} RestPlayerStateNormalTiming13TrailWordsRecord849;

typedef struct RestplayerStateNormalCallbacks14WordsRecord850 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks14WordsRecord850;

typedef struct RestPlayerStateNormalCallbacks14TrailWordsRecord851 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks14TrailWordsRecord851;

typedef struct RestPlayerStateNormalTiming14WordsRecord852 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateNormalTiming14WordsRecord852;

typedef struct RestplayerStateNormalCallbacks15WordsRecord854 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks15WordsRecord854;

typedef struct RestPlayerStateNormalCallbacks15TrailWordsRecord855 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks15TrailWordsRecord855;

typedef struct RestPlayerStateNormalTiming15WordsRecord856 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateNormalTiming15WordsRecord856;

typedef struct RestplayerStateNormalTiming15TrailWordsRecord857 {
    u32 stateFlags;
} RestplayerStateNormalTiming15TrailWordsRecord857;

typedef struct RestplayerStateNormalCallbacks16WordsRecord858 {
    u32 enterAddress;
    u32 updateAddress;
} RestplayerStateNormalCallbacks16WordsRecord858;

typedef struct RestPlayerStateNormalCallbacks16TrailWordsRecord859 {
    u32 exitAddress;
} RestPlayerStateNormalCallbacks16TrailWordsRecord859;

typedef struct RestPlayerStateNormalTiming16WordsRecord860 {
    s32 duration;
    s32 nextAnimation;
} RestPlayerStateNormalTiming16WordsRecord860;

typedef struct RestWeaponStateEntryD0500UsRev1Record885 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD0500UsRev1Record885;

typedef struct RestOvltab6EncodedWordsBlock13Record886 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsBlock13Record886;

typedef struct RestWeaponStateResourceAnimationD0510UsRev1Record887 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestWeaponStateResourceAnimationD0510UsRev1Record887;

typedef struct RestWeaponStateEntryD0520UsRev1Record888 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD0520UsRev1Record888;

typedef struct RestOvltab6EncodedWordsBlock8Record889 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsBlock8Record889;

typedef struct RestOvltab6EncodedWordsBlock16Record890 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestOvltab6EncodedWordsBlock16Record890;

typedef struct RestWeaponStateEntryD0540UsRev1Record891 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD0540UsRev1Record891;

typedef struct RestOvltab6EncodedWordsBlock11Record892 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsBlock11Record892;

typedef struct RestWeaponStateResourceAnimationD0550UsRev1Record893 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestWeaponStateResourceAnimationD0550UsRev1Record893;

typedef struct RestWeaponStateEndD0560UsRev1Record894 {
    s32 endState;
} RestWeaponStateEndD0560UsRev1Record894;

typedef struct RestWeaponStateEntryD05A0UsRev1Record896 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD05A0UsRev1Record896;

typedef struct RestOvltab6EncodedWordsBlock5Record897 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsBlock5Record897;

typedef struct RestOvltab6EncodedWordsBlock18Record898 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestOvltab6EncodedWordsBlock18Record898;

typedef struct RestWeaponStateEndD05C0UsRev1Record899 {
    s32 endState;
} RestWeaponStateEndD05C0UsRev1Record899;

typedef struct RestWeaponStateEntryD0604UsRev1Record901 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD0604UsRev1Record901;

typedef struct RestOvltab6EncodedWordsBlock4Record902 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsBlock4Record902;

typedef struct RestOvltab6EncodedWordsBlock15Record903 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestOvltab6EncodedWordsBlock15Record903;

typedef struct RestWeaponStateEntryD0624UsRev1Record904 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD0624UsRev1Record904;

typedef struct RestOvltab6EncodedWordsRecord905 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsRecord905;

typedef struct RestOvltab6EncodedWordsBlock14Record906 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestOvltab6EncodedWordsBlock14Record906;

typedef struct RestWeaponStateEntryD0644UsRev1Record907 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD0644UsRev1Record907;

typedef struct RestOvltab6EncodedWordsBlock10Record908 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsBlock10Record908;

typedef struct RestOvltab6EncodedWordsBlock17Record909 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestOvltab6EncodedWordsBlock17Record909;

typedef struct RestWeaponStateEndD0664UsRev1Record910 {
    s32 endState;
} RestWeaponStateEndD0664UsRev1Record910;

typedef struct RestWeaponStateEntryD06A4UsRev1Record912 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD06A4UsRev1Record912;

typedef struct RestOvltab6EncodedWordsBlock9Record913 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsBlock9Record913;

typedef struct RestOvltab6EncodedWordsBlock19Record914 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestOvltab6EncodedWordsBlock19Record914;

typedef struct RestWeaponStateEntryD06C4UsRev1Record915 {
    s32 state;
    u32 enterAddress;
} RestWeaponStateEntryD06C4UsRev1Record915;

typedef struct RestOvltab6EncodedWordsBlock2Record916 {
    u32 selectorAddress;
    u32 flags;
} RestOvltab6EncodedWordsBlock2Record916;

typedef struct RestWeaponStateResourceAnimationD06D4UsRev1Record917 {
    s32 animation;
    float speed;
    s32 threshold;
    u32 flags;
} RestWeaponStateResourceAnimationD06D4UsRev1Record917;

typedef struct RestWeaponStateEndD06E4UsRev1Record918 {
    s32 endState;
} RestWeaponStateEndD06E4UsRev1Record918;

typedef struct RestscenarioSetupMenuEventHandlerWordsRecord35 {
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
} RestscenarioSetupMenuEventHandlerWordsRecord35;

typedef struct RestslotSelectionMenuEventHandlerRecordsUsRev1Record438 {
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
} RestslotSelectionMenuEventHandlerRecordsUsRev1Record438;

typedef struct RestjoinOptionsEventHandlerRecordsRecord442 {
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
} RestjoinOptionsEventHandlerRecordsRecord442;

typedef struct RestjoinOptionsEventHandlerRecordsRecord443 {
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
} RestjoinOptionsEventHandlerRecordsRecord443;

typedef struct RestjoinOptionsEventHandlerRecordsRecord444 {
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
} RestjoinOptionsEventHandlerRecordsRecord444;

typedef struct RestjoinOptionsEventHandlerRecordsRecord445 {
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
} RestjoinOptionsEventHandlerRecordsRecord445;

typedef struct RestjoinOptionsEventHandlerRecordsRecord446 {
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
} RestjoinOptionsEventHandlerRecordsRecord446;

typedef struct RestlistButtonEventHandlerRecordsUsRev1Record451 {
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
} RestlistButtonEventHandlerRecordsUsRev1Record451;

typedef struct RestsixChoiceMenuUpdateEventRecordUsRev1Record452 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
} RestsixChoiceMenuUpdateEventRecordUsRev1Record452;

typedef struct RestbuttonEventHandlerRecordsUsRev1Record453 {
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
} RestbuttonEventHandlerRecordsUsRev1Record453;

typedef struct RestpakDialogEventHandlerRecordsUsRecord458 {
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
} RestpakDialogEventHandlerRecordsUsRecord458;

typedef struct RestD_src_e3e7c440Record462 {
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
} RestD_src_e3e7c440Record462;

typedef struct RestD_src_e3e7c440Record463 {
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
} RestD_src_e3e7c440Record463;

typedef struct RestD_src_e3e7c440Record464 {
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
} RestD_src_e3e7c440Record464;

typedef struct RestAchieveCreateresultsscreenPointerWords1Record465 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
} RestAchieveCreateresultsscreenPointerWords1Record465;

typedef struct RestAchieveCreateresultsscreenPointerWordsTailUsRecord466 {
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
} RestAchieveCreateresultsscreenPointerWordsTailUsRecord466;

typedef struct RestFrontendPulseprofileresetwidgetPointerWords1Record478 {
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
} RestFrontendPulseprofileresetwidgetPointerWords1Record478;

typedef struct RestMenuCreatesoundoptionsscreenPointerWords1Record502 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
} RestMenuCreatesoundoptionsscreenPointerWords1Record502;

typedef struct RestMenuDispatchsettingstableeventPointerWords1Record507 {
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
} RestMenuDispatchsettingstableeventPointerWords1Record507;

typedef struct RestPlayerDispatchplayersettingseventPointerWords1Record511 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
} RestPlayerDispatchplayersettingseventPointerWords1Record511;

typedef struct RestMenuEventHandlersE6804UsRev1Record778 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 event2;
    u32 widgetType2;
    u32 callbackAddress2;
} RestMenuEventHandlersE6804UsRev1Record778;

typedef struct RestOvl1JEncodedWordsRecord779 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
} RestOvl1JEncodedWordsRecord779;

typedef struct RestMenuEventHandlersE6834UsRev1Record780 {
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
} RestMenuEventHandlersE6834UsRev1Record780;

typedef struct RestsmpFrameControllerEventRecordsUsRev1Record877 {
    u32 event0;
    u32 widgetType0;
    u32 callbackAddress0;
    u32 event1;
    u32 widgetType1;
    u32 callbackAddress1;
    u32 eventTableTail[3];
} RestsmpFrameControllerEventRecordsUsRev1Record877;

typedef struct RestsmpSliderListEventRecordsUsRev1Record879 {
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
} RestsmpSliderListEventRecordsUsRev1Record879;

typedef struct Restwidth320Height240MinusOneWordsRecord15 {
    s32 width;
    s32 height;
    s32 unset;
} Restwidth320Height240MinusOneWordsRecord15;

typedef struct RestArenaCatalogueRecord { s32 arena; s32 label; s32 category; s32 index; } RestArenaCatalogueRecord;

typedef struct Resthuffman_signed7_single_dictionaryLayout307 {
    s32 rangeAndDictionary0[7];
    void * treeAndValues0[2];
    s32 rangeAndDictionary1[7];
    void * treeAndValues1[2];
    s32 rangeAndDictionary2[7];
    void * treeAndValues2[2];
    s32 rangeAndDictionary3[7];
    void * treeAndValues3[2];
} Resthuffman_signed7_single_dictionaryLayout307;

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

typedef struct RestplayerMovementTuningAndLookupUsRev1Layout400 {
    float movementScales[3];
    u32 stateMasks[9];
    float movementLimits[3];
} RestplayerMovementTuningAndLookupUsRev1Layout400;

typedef struct RestrewardItemTierPairsUsRev1Layout439 {
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
} RestrewardItemTierPairsUsRev1Layout439;

typedef struct RestDecodeEncodedWordsBlock1Layout618 {
    float movementScales[3];
    u32 stateMasks[9];
    float movementLimits[3];
} RestDecodeEncodedWordsBlock1Layout618;

typedef struct RestLoadoutEquipmentItemsUsRev1Layout775 {
    s32 resourceIconAndWeapon0[3];
    void * label0;
    s32 resourceIconAndWeapon1[3];
    void * label1;
    s32 resourceIconAndWeapon2[3];
    void * label2;
} RestLoadoutEquipmentItemsUsRev1Layout775;

typedef struct RestloadoutWeaponItemsLayout776 {
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
} RestloadoutWeaponItemsLayout776;

typedef struct RestLoadoutAbilitiesItemsUsRev1Layout777 {
    s32 resourceIconAndWeapon0[3];
    void * label0;
    s32 resourceIconAndWeapon1[3];
    void * label1;
    s32 resourceIconAndWeapon2[3];
    void * label2;
    s32 resourceIconAndWeapon3[3];
    void * label3;
} RestLoadoutAbilitiesItemsUsRev1Layout777;

typedef struct RestOvldat2ConstantWordsLayout4 {
    s32 idsAt0[6];
    float constantsAt24[22];
    void * referencesAt112[314];
    char textAt1368[44];
    void * referencesAt1412[4];
    float constantsAt1428;
    s32 idsAt1432[3];
    void * referencesAt1444[4];
    float constantsAt1460;
    s32 idsAt1464[3];
    void * referencesAt1476[4];
    float constantsAt1492;
    s32 idsAt1496[3];
    void * referencesAt1508[4];
    float constantsAt1524;
    s32 idsAt1528[3];
    void * referencesAt1540[4];
    float constantsAt1556;
    s32 idsAt1560[3];
    void * referencesAt1572[4];
    float constantsAt1588;
    s32 idsAt1592[3];
    void * referencesAt1604[4];
    float constantsAt1620;
    s32 idsAt1624[3];
    void * referencesAt1636[4];
    float constantsAt1652;
    s32 idsAt1656[3];
    void * referencesAt1668[4];
    float constantsAt1684;
    s32 idsAt1688[3];
    void * referencesAt1700[4];
    float constantsAt1716;
    s32 idsAt1720[3];
    void * referencesAt1732[4];
    float constantsAt1748;
    s32 idsAt1752[3];
    void * referencesAt1764[4];
    float constantsAt1780;
    s32 idsAt1784[3];
    void * referencesAt1796[4];
    float constantsAt1812;
    s32 idsAt1816[3];
    void * referencesAt1828[4];
    float constantsAt1844;
    s32 idsAt1848[10];
} RestOvldat2ConstantWordsLayout4;

typedef struct RestGControllerpakfilenamealphabetEncodedWordsBlock1Layout12 {
    s32 idsAt0[3];
} RestGControllerpakfilenamealphabetEncodedWordsBlock1Layout12;

typedef struct RestsliderDimEventRecordUsRev1Layout18 {
    s32 idsAt0;
    void * referencesAt4;
    s32 idsAt8;
} RestsliderDimEventRecordUsRev1Layout18;

typedef struct RestaudioGlobalsTailWordsUsLayout295 {
    s32 idsAt0[4];
    float constantsAt16[2];
    char textAt24[28];
    s32 idsAt52[14];
} RestaudioGlobalsTailWordsUsLayout295;

typedef struct RestcommonConstantWordsLayout296 {
    void * referencesAt0[891];
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
} RestcommonConstantWordsLayout296;

typedef struct RestCommonEncodedWordsLayout299 {
    void * audioGlobals;
    s32 reverbParameters[103];
    s16 sineCoefficients[128];
    u32 libraryStateAndFill[27];
} RestCommonEncodedWordsLayout299;

typedef struct RestCommonEncodedWordsBlock1Layout300 {
    char textAt0[8];
    float constantsAt8[60];
    void * referencesAt248[21];
    float constantsAt332[19];
} RestCommonEncodedWordsBlock1Layout300;

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

typedef struct RestfrontendShutdownWritableWordsLayout304 {
    s32 idsAt0[6];
    char textAt24[8];
    float constantsAt32[60];
    void * referencesAt272[21];
    float constantsAt356[19];
} RestfrontendShutdownWritableWordsLayout304;

typedef struct RestCurveDecodethreebitsamplesEncodedWordsLayout313 {
    s32 idsAt0[8];
    void * referencesAt32[10];
    s32 idsAt72[2];
} RestCurveDecodethreebitsamplesEncodedWordsLayout313;

typedef struct RestCurveDecodethreebitsamplesEncodedWordsLayout314 {
    s32 idsAt0[8];
    void * referencesAt32[10];
    s32 idsAt72;
    char textAt76[4];
} RestCurveDecodethreebitsamplesEncodedWordsLayout314;

typedef struct RestCurveDecodethreebitsamplesEncodedWordsLayout315 {
    s32 idsAt0[8];
    void * referencesAt32[10];
    s32 idsAt72;
    float constantsAt76;
} RestCurveDecodethreebitsamplesEncodedWordsLayout315;

typedef struct RestCurveDecodethreebitsamplesEncodedWordsLayout316 {
    s32 idsAt0[8];
    void * referencesAt32[10];
    s32 idsAt72;
    char textAt76[4];
} RestCurveDecodethreebitsamplesEncodedWordsLayout316;

typedef struct RestCurveDecodethreebitsamplesEncodedWordsLayout317 {
    s32 idsAt0[8];
    void * referencesAt32[10];
    s32 idsAt72;
} RestCurveDecodethreebitsamplesEncodedWordsLayout317;

typedef struct RestEventsDelivercontacteffectWords2Layout318 {
    u32 displayCommandAt0;
    s32 idsAt4;
    u32 displayCommandAt8;
    u32 displayCommandAt12;
    u32 displayCommandAt16;
    s32 idsAt20;
    u32 displayCommandAt24;
    s32 idsAt28;
    u32 displayCommandAt32;
    s32 idsAt36;
    u32 displayCommandAt40;
    u32 displayCommandAt44;
    u32 displayCommandAt48;
    s32 idsAt52;
    u32 displayCommandAt56;
    s32 idsAt60;
    u32 displayCommandAt64;
    s32 idsAt68;
    u32 displayCommandAt72;
    s32 idsAt76;
    u32 displayCommandAt80;
    u32 displayCommandAt84;
    u32 displayCommandAt88;
    s32 idsAt92;
    u32 displayCommandAt96;
    s32 idsAt100;
    u32 displayCommandAt104;
    s32 idsAt108;
    u32 displayCommandAt112;
    s32 idsAt116;
    u32 displayCommandAt120;
    s32 idsAt124;
    u32 displayCommandAt128;
    s32 idsAt132;
} RestEventsDelivercontacteffectWords2Layout318;

typedef struct ResteffectCallbackFlagsLayout320 {
    void * referencesAt0[5];
    s32 idsAt20;
    void * referencesAt24;
    s32 idsAt28;
    void * referencesAt32;
    s32 idsAt36;
    void * referencesAt40;
    s32 idsAt44;
    void * referencesAt48;
    s32 idsAt52;
    void * referencesAt56;
    s32 idsAt60;
    void * referencesAt64[15];
    s32 idsAt124;
    void * referencesAt128;
    s32 idsAt132;
    void * referencesAt136;
    s32 idsAt140;
    void * referencesAt144;
    s32 idsAt148;
    void * referencesAt152;
    s32 idsAt156;
    void * referencesAt160;
    s32 idsAt164;
    void * referencesAt168[9];
    s32 idsAt204;
    void * referencesAt208[15];
    s32 idsAt268;
    void * referencesAt272[6];
} ResteffectCallbackFlagsLayout320;

typedef struct RestemacTextLayout324 {
    s32 idsAt0[2];
    float constantsAt8[3];
    s32 idsAt20[2];
} RestemacTextLayout324;

typedef struct RestemacTextLayout325 {
    s32 idsAt0[2];
    float constantsAt8[3];
    s32 idsAt20[2];
} RestemacTextLayout325;

typedef struct RestemacTextLayout326 {
    s32 idsAt0[2];
    float constantsAt8[3];
    s32 idsAt20;
    char textAt24[4];
} RestemacTextLayout326;

typedef struct RestminigunTextLayout331 {
    s32 idsAt0[2];
    void * referencesAt8[15];
    char textAt68[12];
    float constantsAt80;
} RestminigunTextLayout331;

typedef struct RestpakAdjustownernotificationoptionDataConstantWordsLayout336 {
    void * referencesAt0[891];
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
    void * referencesAt3872[7];
    u32 packedValueAt3900;
    char textAt3904[8];
} RestpakAdjustownernotificationoptionDataConstantWordsLayout336;

typedef struct RestSSmackformatEncodedWordsBlock1Layout339 {
    s32 idsAt0[11];
    float constantsAt44;
    s32 idsAt48;
    u32 packedValueAt52;
    u32 packedValueAt56;
    s32 idsAt60;
} RestSSmackformatEncodedWordsBlock1Layout339;

typedef struct RestSSmackformatEncodedWordsBlock1Layout340 {
    s32 idsAt0[13];
    float constantsAt52[3];
} RestSSmackformatEncodedWordsBlock1Layout340;

typedef struct RestSSmackformatEncodedWordsBlock1Layout341 {
    s32 idsAt0[11];
    char textAt44[4];
    s32 idsAt48;
    char textAt52[12];
} RestSSmackformatEncodedWordsBlock1Layout341;

typedef struct RestSSmackformatEncodedWordsBlock1Layout342 {
    s32 idsAt0[13];
    char textAt52[12];
} RestSSmackformatEncodedWordsBlock1Layout342;

typedef struct RestSSmackformatEncodedWordsLayout343 {
    s32 idsAt0[11];
    char textAt44[4];
    s32 idsAt48;
    char textAt52[12];
} RestSSmackformatEncodedWordsLayout343;

typedef struct RestsmackFormatLayout345 {
    s32 idsAt0[2];
    float constantsAt8[2];
} RestsmackFormatLayout345;

typedef struct RestsmackFormatLayout347 {
    s32 idsAt0;
    char textAt4[4];
    s32 idsAt8[2];
} RestsmackFormatLayout347;

typedef struct RestXplusNextrandomintegerEncodedWordsLayout350 {
    s32 idsAt0;
    char textAt4[4];
} RestXplusNextrandomintegerEncodedWordsLayout350;

typedef struct RestxplusSeedRandomGeneratorWordsDeLayout351 {
    s32 idsAt0;
    u32 packedValueAt4;
    s32 idsAt8[3];
    u32 packedValueAt20;
    s32 idsAt24[22];
    float constantsAt112[10];
    s32 idsAt152[2];
} RestxplusSeedRandomGeneratorWordsDeLayout351;

typedef struct RestxPlusWritableWords_us_rev1Layout352 {
    s32 idsAt0[10];
    float constantsAt40[10];
} RestxPlusWritableWords_us_rev1Layout352;

typedef struct RestxPlusWritableWords_usLayout353 {
    s32 idsAt0;
    char textAt4[8];
    u32 packedValueAt12;
    s32 idsAt16;
    u32 packedValueAt20;
    s32 idsAt24[15];
    char textAt84[28];
    float constantsAt112[10];
    s32 idsAt152[2];
} RestxPlusWritableWords_usLayout353;

typedef struct RestmaterialPlusModeConstantsUsRev1Layout354 {
    u32 displayCommandAt0;
    u32 displayCommandAt4;
    s32 idsAt8[2];
} RestmaterialPlusModeConstantsUsRev1Layout354;

typedef struct RestConstantsEncodedWordsLayout359 {
    s32 idsAt0;
    char textAt4[4];
    u32 packedValueAt8;
    s32 idsAt12[3];
} RestConstantsEncodedWordsLayout359;

typedef struct RestConstantsEncodedWordsBlock1Layout360 {
    u32 packedValueAt0;
    s32 idsAt4;
    u32 packedValueAt8;
    float constantsAt12[3];
} RestConstantsEncodedWordsBlock1Layout360;

typedef struct RestplayerActionStateTableWordsUsLayout362 {
    s32 idsAt0;
    float constantsAt4[21];
    void * referencesAt88[4];
    s32 idsAt104[3];
    void * referencesAt116[3];
    s32 idsAt128[2];
    void * referencesAt136[4];
    s32 idsAt152[2];
    void * referencesAt160[4];
    s32 idsAt176[2];
    void * referencesAt184[4];
    s32 idsAt200[2];
    void * referencesAt208[3];
    s32 idsAt220[4];
    void * referencesAt236[2];
    s32 idsAt244[3];
    void * referencesAt256[4];
    s32 idsAt272[3];
    void * referencesAt284[3];
    s32 idsAt296[2];
    void * referencesAt304[3];
    s32 idsAt316[3];
    void * referencesAt328[3];
    s32 idsAt340[3];
    void * referencesAt352[3];
    s32 idsAt364[3];
    void * referencesAt376[3];
    s32 idsAt388[3];
    void * referencesAt400[4];
    s32 idsAt416[2];
    void * referencesAt424[4];
    s32 idsAt440[2];
    void * referencesAt448[3];
    s32 idsAt460[3];
    void * referencesAt472[3];
    s32 idsAt484[3];
    void * referencesAt496[3];
    s32 idsAt508[3];
    void * referencesAt520[5];
    s32 idsAt540;
    void * referencesAt544[5];
    s32 idsAt564;
    void * referencesAt568[5];
    s32 idsAt588;
    void * referencesAt592[5];
    s32 idsAt612;
    void * referencesAt616[4];
    s32 idsAt632[2];
    void * referencesAt640[4];
    s32 idsAt656[2];
    void * referencesAt664[4];
    s32 idsAt680[2];
    void * referencesAt688[4];
    s32 idsAt704[2];
    void * referencesAt712[4];
    s32 idsAt728[2];
    void * referencesAt736[4];
    s32 idsAt752[2];
    void * referencesAt760[4];
    s32 idsAt776[2];
    void * referencesAt784[4];
    s32 idsAt800[2];
    void * referencesAt808[4];
    s32 idsAt824[2];
    void * referencesAt832[4];
    s32 idsAt848[2];
    void * referencesAt856[4];
    s32 idsAt872[2];
    void * referencesAt880[4];
    s32 idsAt896[2];
    void * referencesAt904[5];
    s32 idsAt924;
    void * referencesAt928[4];
    s32 idsAt944[2];
    void * referencesAt952[3];
    s32 idsAt964[3];
    void * referencesAt976[3];
    s32 idsAt988[3];
    void * referencesAt1000[4];
    s32 idsAt1016[2];
    void * referencesAt1024[4];
    s32 idsAt1040[2];
    void * referencesAt1048[4];
    s32 idsAt1064[2];
    void * referencesAt1072[4];
    s32 idsAt1088[2];
    void * referencesAt1096[4];
    s32 idsAt1112[2];
    void * referencesAt1120[4];
    s32 idsAt1136[2];
    void * referencesAt1144[4];
    s32 idsAt1160[2];
    void * referencesAt1168[4];
    s32 idsAt1184[2];
    void * referencesAt1192[4];
    s32 idsAt1208[2];
    void * referencesAt1216[4];
    s32 idsAt1232[3];
    void * referencesAt1244[3];
    s32 idsAt1256[2];
    void * referencesAt1264[4];
    s32 idsAt1280[2];
    void * referencesAt1288[4];
    s32 idsAt1304[2];
    void * referencesAt1312[4];
    s32 idsAt1328[2];
    void * referencesAt1336[3];
    s32 idsAt1348[4];
    void * referencesAt1364[2];
    s32 idsAt1372[3];
    void * referencesAt1384[4];
    s32 idsAt1400[3];
    void * referencesAt1412[3];
    s32 idsAt1424[2];
    void * referencesAt1432[3];
    s32 idsAt1444[3];
    void * referencesAt1456[3];
    s32 idsAt1468[3];
    void * referencesAt1480[3];
    s32 idsAt1492[3];
    void * referencesAt1504[3];
    s32 idsAt1516[3];
    void * referencesAt1528[4];
    s32 idsAt1544[2];
    void * referencesAt1552[4];
    s32 idsAt1568[2];
    void * referencesAt1576[3];
    s32 idsAt1588[3];
    void * referencesAt1600[3];
    s32 idsAt1612[3];
    void * referencesAt1624[3];
    s32 idsAt1636[3];
    void * referencesAt1648[5];
    s32 idsAt1668;
    void * referencesAt1672[5];
    s32 idsAt1692;
    void * referencesAt1696[5];
    s32 idsAt1716;
    void * referencesAt1720[5];
    s32 idsAt1740;
    void * referencesAt1744[4];
    s32 idsAt1760[2];
    void * referencesAt1768[4];
    s32 idsAt1784[2];
    void * referencesAt1792[4];
    s32 idsAt1808[2];
    void * referencesAt1816[4];
    s32 idsAt1832[2];
    void * referencesAt1840[4];
    s32 idsAt1856[2];
    void * referencesAt1864[4];
    s32 idsAt1880[2];
    void * referencesAt1888[4];
    s32 idsAt1904[2];
    void * referencesAt1912[4];
    s32 idsAt1928[2];
    void * referencesAt1936[4];
    s32 idsAt1952[2];
    void * referencesAt1960[4];
    s32 idsAt1976[2];
    void * referencesAt1984[4];
    s32 idsAt2000[2];
    void * referencesAt2008[4];
    s32 idsAt2024[2];
    void * referencesAt2032[5];
    s32 idsAt2052;
    void * referencesAt2056[4];
    s32 idsAt2072[2];
    void * referencesAt2080[3];
    s32 idsAt2092[3];
    void * referencesAt2104[3];
    s32 idsAt2116[3];
    void * referencesAt2128[4];
    s32 idsAt2144[2];
    void * referencesAt2152[4];
    s32 idsAt2168[2];
    void * referencesAt2176[4];
    s32 idsAt2192[2];
    void * referencesAt2200[4];
    s32 idsAt2216[2];
    void * referencesAt2224[4];
    s32 idsAt2240[2];
    void * referencesAt2248[4];
    s32 idsAt2264[2];
    void * referencesAt2272[4];
    s32 idsAt2288[2];
    void * referencesAt2296[4];
    s32 idsAt2312[2];
    void * referencesAt2320[4];
    s32 idsAt2336[3];
    u32 packedValueAt2348;
    u32 packedValueAt2352;
    u32 packedValueAt2356;
    u32 packedValueAt2360;
    u32 packedValueAt2364;
    float constantsAt2368;
} RestplayerActionStateTableWordsUsLayout362;

typedef struct RestsceneEffectTuningUsRev1Layout363 {
    float constantsAt0[60];
    s32 idsAt240;
    float constantsAt244[8];
    s32 idsAt276;
    float constantsAt280[21];
    void * referencesAt364[4];
    s32 idsAt380[3];
    void * referencesAt392[3];
    s32 idsAt404[2];
    void * referencesAt412[4];
    s32 idsAt428[2];
    void * referencesAt436[4];
    s32 idsAt452[2];
    void * referencesAt460[4];
    s32 idsAt476[2];
    void * referencesAt484[3];
    s32 idsAt496[4];
    void * referencesAt512[2];
    s32 idsAt520[3];
    void * referencesAt532[4];
    s32 idsAt548[3];
    void * referencesAt560[3];
    s32 idsAt572[2];
    void * referencesAt580[3];
    s32 idsAt592[3];
    void * referencesAt604[3];
    s32 idsAt616[3];
    void * referencesAt628[3];
    s32 idsAt640[3];
    void * referencesAt652[3];
    s32 idsAt664[3];
    void * referencesAt676[4];
    s32 idsAt692[2];
    void * referencesAt700[4];
    s32 idsAt716[2];
    void * referencesAt724[3];
    s32 idsAt736[3];
    void * referencesAt748[3];
    s32 idsAt760[3];
    void * referencesAt772[3];
    s32 idsAt784[3];
    void * referencesAt796[5];
    s32 idsAt816;
    void * referencesAt820[5];
    s32 idsAt840;
    void * referencesAt844[5];
    s32 idsAt864;
    void * referencesAt868[5];
    s32 idsAt888;
    void * referencesAt892[4];
    s32 idsAt908[2];
    void * referencesAt916[4];
    s32 idsAt932[2];
    void * referencesAt940[4];
    s32 idsAt956[2];
    void * referencesAt964[4];
    s32 idsAt980[2];
    void * referencesAt988[4];
    s32 idsAt1004[2];
    void * referencesAt1012[4];
    s32 idsAt1028[2];
    void * referencesAt1036[4];
    s32 idsAt1052[2];
    void * referencesAt1060[4];
    s32 idsAt1076[2];
    void * referencesAt1084[4];
    s32 idsAt1100[2];
    void * referencesAt1108[4];
    s32 idsAt1124[2];
    void * referencesAt1132[4];
    s32 idsAt1148[2];
    void * referencesAt1156[4];
    s32 idsAt1172[2];
    void * referencesAt1180[5];
    s32 idsAt1200;
    void * referencesAt1204[4];
    s32 idsAt1220[2];
    void * referencesAt1228[3];
    s32 idsAt1240[3];
    void * referencesAt1252[3];
    s32 idsAt1264[3];
    void * referencesAt1276[4];
    s32 idsAt1292[2];
    void * referencesAt1300[4];
    s32 idsAt1316[2];
    void * referencesAt1324[4];
    s32 idsAt1340[2];
    void * referencesAt1348[4];
    s32 idsAt1364[2];
    void * referencesAt1372[4];
    s32 idsAt1388[2];
    void * referencesAt1396[4];
    s32 idsAt1412[2];
    void * referencesAt1420[4];
    s32 idsAt1436[2];
    void * referencesAt1444[4];
    s32 idsAt1460[2];
    void * referencesAt1468[4];
    s32 idsAt1484[2];
    void * referencesAt1492[4];
    s32 idsAt1508[3];
    void * referencesAt1520[3];
    s32 idsAt1532[2];
    void * referencesAt1540[4];
    s32 idsAt1556[2];
    void * referencesAt1564[4];
    s32 idsAt1580[2];
    void * referencesAt1588[4];
    s32 idsAt1604[2];
    void * referencesAt1612[3];
    s32 idsAt1624[4];
    void * referencesAt1640[2];
    s32 idsAt1648[3];
    void * referencesAt1660[4];
    s32 idsAt1676[3];
    void * referencesAt1688[3];
    s32 idsAt1700[2];
    void * referencesAt1708[3];
    s32 idsAt1720[3];
    void * referencesAt1732[3];
    s32 idsAt1744[3];
    void * referencesAt1756[3];
    s32 idsAt1768[3];
    void * referencesAt1780[3];
    s32 idsAt1792[3];
    void * referencesAt1804[4];
    s32 idsAt1820[2];
    void * referencesAt1828[4];
    s32 idsAt1844[2];
    void * referencesAt1852[3];
    s32 idsAt1864[3];
    void * referencesAt1876[3];
    s32 idsAt1888[3];
    void * referencesAt1900[3];
    s32 idsAt1912[3];
    void * referencesAt1924[5];
    s32 idsAt1944;
    void * referencesAt1948[5];
    s32 idsAt1968;
    void * referencesAt1972[5];
    s32 idsAt1992;
    void * referencesAt1996[5];
    s32 idsAt2016;
    void * referencesAt2020[4];
    s32 idsAt2036[2];
    void * referencesAt2044[4];
    s32 idsAt2060[2];
    void * referencesAt2068[4];
    s32 idsAt2084[2];
    void * referencesAt2092[4];
    s32 idsAt2108[2];
    void * referencesAt2116[4];
    s32 idsAt2132[2];
    void * referencesAt2140[4];
    s32 idsAt2156[2];
    void * referencesAt2164[4];
    s32 idsAt2180[2];
    void * referencesAt2188[4];
    s32 idsAt2204[2];
    void * referencesAt2212[4];
    s32 idsAt2228[2];
    void * referencesAt2236[4];
    s32 idsAt2252[2];
    void * referencesAt2260[4];
    s32 idsAt2276[2];
    void * referencesAt2284[4];
    s32 idsAt2300[2];
    void * referencesAt2308[5];
    s32 idsAt2328;
    void * referencesAt2332[4];
    s32 idsAt2348[2];
    void * referencesAt2356[3];
    s32 idsAt2368[3];
    void * referencesAt2380[3];
    s32 idsAt2392[3];
    void * referencesAt2404[4];
    s32 idsAt2420[2];
    void * referencesAt2428[4];
    s32 idsAt2444[2];
    void * referencesAt2452[4];
    s32 idsAt2468[2];
    void * referencesAt2476[4];
    s32 idsAt2492[2];
    void * referencesAt2500[4];
    s32 idsAt2516[2];
    void * referencesAt2524[4];
    s32 idsAt2540[2];
    void * referencesAt2548[4];
    s32 idsAt2564[2];
    void * referencesAt2572[4];
    s32 idsAt2588[2];
    void * referencesAt2596[4];
    s32 idsAt2612[3];
    u32 packedValueAt2624;
    u32 packedValueAt2628;
    u32 packedValueAt2632;
    u32 packedValueAt2636;
    u32 packedValueAt2640;
    float constantsAt2644;
} RestsceneEffectTuningUsRev1Layout363;

typedef struct RestSceneEffectLookupWordsEuEncodedHalfwordsLayout365 {
    float constantsAt0[2];
    s32 idsAt8[45];
    float constantsAt188[22];
    s32 idsAt276[300];
    void * referencesAt1476[14];
    float constantsAt1532[11];
    s32 idsAt1576[4];
    float constantsAt1592;
    s32 idsAt1596[7];
    float constantsAt1624;
    s32 idsAt1628[7];
    float constantsAt1656;
    s32 idsAt1660[7];
    float constantsAt1688;
    s32 idsAt1692[7];
    float constantsAt1720;
    s32 idsAt1724[7];
    float constantsAt1752;
    s32 idsAt1756[7];
    float constantsAt1784;
    s32 idsAt1788[7];
    float constantsAt1816;
    s32 idsAt1820[7];
    float constantsAt1848;
    s32 idsAt1852[7];
    float constantsAt1880;
    s32 idsAt1884[7];
    float constantsAt1912;
    s32 idsAt1916[7];
    float constantsAt1944;
    s32 idsAt1948[7];
    float constantsAt1976;
    s32 idsAt1980[7];
    float constantsAt2008;
    s32 idsAt2012[58];
    u32 packedValueAt2244;
    s32 idsAt2248;
    u32 packedValueAt2252;
    s32 idsAt2256;
    u32 packedValueAt2260;
    s32 idsAt2264;
    u32 packedValueAt2268;
    s32 idsAt2272;
    u32 packedValueAt2276;
    s32 idsAt2280;
    u32 packedValueAt2284;
    s32 idsAt2288;
    float constantsAt2292;
    s32 idsAt2296;
    void * referencesAt2300;
    s32 idsAt2304[7];
    float constantsAt2332[2];
    s32 idsAt2340[8];
    float constantsAt2372[3];
} RestSceneEffectLookupWordsEuEncodedHalfwordsLayout365;

typedef struct RestsceneEffectTuningDeLayout371 {
    float constantsAt0[3];
    s32 idsAt12;
} RestsceneEffectTuningDeLayout371;

typedef struct RestgeometryDrawResourceModelWritableWords_euLayout372 {
    s32 idsAt0[10];
    float constantsAt40[10];
} RestgeometryDrawResourceModelWritableWords_euLayout372;

typedef struct RestGeometryDrawresourcemodelEncodedWordsBlock2Layout374 {
    float constantsAt0[2];
    u32 packedValueAt8;
    s32 idsAt12;
} RestGeometryDrawresourcemodelEncodedWordsBlock2Layout374;

typedef struct RestGeometryDrawresourcemodelEncodedWordsLayout375 {
    u32 displayCommandAt0;
    s32 idsAt4;
    u32 displayCommandAt8;
    s32 idsAt12;
    u32 displayCommandAt16;
    s32 idsAt20;
    u32 displayCommandAt24;
    s32 idsAt28;
    u32 displayCommandAt32;
    s32 idsAt36;
    u32 displayCommandAt40;
    s32 idsAt44;
    u32 displayCommandAt48;
    s32 idsAt52;
    u32 displayCommandAt56;
    s32 idsAt60;
    u32 displayCommandAt64;
    s32 idsAt68[4];
    u32 displayCommandAt84;
} RestGeometryDrawresourcemodelEncodedWordsLayout375;

typedef struct RestGeometryDrawresourcemodelEncodedWordsBlock1Layout376 {
    u32 displayCommandAt0;
    u32 displayCommandAt4;
    s32 idsAt8[2];
} RestGeometryDrawresourcemodelEncodedWordsBlock1Layout376;

typedef struct RestvideoScaleUnsignedBias_StorageWordsLayout386 {
    float constantsAt0[3];
} RestvideoScaleUnsignedBias_StorageWordsLayout386;

typedef struct RestplayerControllerStateAndTuningWordsUsLayout395 {
    s32 idsAt0[6];
    char textAt24[4];
    s32 idsAt28[9];
    float constantsAt64[3];
} RestplayerControllerStateAndTuningWordsUsLayout395;

typedef struct RestplayerControllerStateHeaderUsRev1Layout396 {
    s32 idsAt0[2];
    float constantsAt8;
    s32 idsAt12[2];
} RestplayerControllerStateHeaderUsRev1Layout396;

typedef struct RestplayerControllerStateHeaderAlternateUsRev1Layout398 {
    s32 idsAt0[2];
    float constantsAt8;
    s32 idsAt12[2];
} RestplayerControllerStateHeaderAlternateUsRev1Layout398;

typedef struct RestweaponControllerAndMovementTuningUsRev1Layout404 {
    s32 idsAt0[2];
    void * referencesAt8;
    s32 idsAt12[8];
    float constantsAt44[3];
} RestweaponControllerAndMovementTuningUsRev1Layout404;

typedef struct RestConstantsEncodedWordsBlock11Layout405 {
    s32 idsAt0[2];
    float constantsAt8[2];
    void * referencesAt16[3];
} RestConstantsEncodedWordsBlock11Layout405;

typedef struct RestConstantsEncodedWordsBlock13Layout406 {
    s32 idsAt0[2];
    float constantsAt8[2];
    void * referencesAt16[3];
} RestConstantsEncodedWordsBlock13Layout406;

typedef struct RestConstantsEncodedWordsBlock15Layout407 {
    s32 idsAt0[2];
    float constantsAt8[2];
    void * referencesAt16[3];
} RestConstantsEncodedWordsBlock15Layout407;

typedef struct RestConstantsEncodedWordsBlock17Layout408 {
    s32 idsAt0[2];
    float constantsAt8[2];
    void * referencesAt16[3];
} RestConstantsEncodedWordsBlock17Layout408;

typedef struct RestConstantsEncodedWordsBlock19Layout409 {
    s32 idsAt0[2];
    float constantsAt8[2];
    void * referencesAt16[3];
} RestConstantsEncodedWordsBlock19Layout409;

typedef struct RestConstantsEncodedWordsBlock21Layout410 {
    s32 idsAt0[2];
    float constantsAt8[2];
    void * referencesAt16[3];
} RestConstantsEncodedWordsBlock21Layout410;

typedef struct RestConstantsEncodedWordsBlock7Layout411 {
    s32 idsAt0[2];
    float constantsAt8[2];
    void * referencesAt16[3];
} RestConstantsEncodedWordsBlock7Layout411;

typedef struct RestConstantsEncodedWordsBlock9Layout412 {
    s32 idsAt0[2];
    float constantsAt8[2];
    void * referencesAt16[3];
} RestConstantsEncodedWordsBlock9Layout412;

typedef struct RestConstantsEncodedWordsLayout413 {
    char textAt0[4];
    u32 packedValueAt4;
    s32 idsAt8[3];
    u32 packedValueAt20;
    void * referencesAt24[4];
    s32 idsAt40[5];
    u32 packedValueAt60;
    u32 packedValueAt64;
    float constantsAt68;
    s32 idsAt72[6];
    u32 packedValueAt96;
    u32 packedValueAt100;
    u32 packedValueAt104;
    void * referencesAt108;
    s32 idsAt112[8];
    u32 packedValueAt144;
    u32 packedValueAt148;
    u32 packedValueAt152;
    float constantsAt156[61];
} RestConstantsEncodedWordsLayout413;

typedef struct RestConstantsEncodedWordsBlock14Layout415 {
    u32 packedValueAt0;
    u32 packedValueAt4;
    u32 packedValueAt8;
} RestConstantsEncodedWordsBlock14Layout415;

typedef struct RestOsstartthreadEncodedWordsLayout422 {
    void * referencesAt0[4];
    char textAt16[4];
    float constantsAt20;
} RestOsstartthreadEncodedWordsLayout422;

typedef struct RestD_src_567cc0c4Layout424 {
    float constantsAt0[13];
    s32 idsAt52[2];
    void * referencesAt60;
    s32 idsAt64[3];
    float constantsAt76[22];
    s32 idsAt164[2];
    void * referencesAt172;
    s32 idsAt176[3];
    float constantsAt188[22];
    s32 idsAt276[2];
    void * referencesAt284;
    s32 idsAt288[3];
    float constantsAt300[20];
    s32 idsAt380[4];
    void * referencesAt396;
    s32 idsAt400[3];
    float constantsAt412[22];
    s32 idsAt500[2];
    void * referencesAt508;
    s32 idsAt512[3];
    float constantsAt524[22];
    s32 idsAt612[2];
    void * referencesAt620;
    s32 idsAt624[3];
    float constantsAt636[22];
    s32 idsAt724[2];
    void * referencesAt732;
    s32 idsAt736[3];
    float constantsAt748[22];
    s32 idsAt836[2];
    void * referencesAt844;
    s32 idsAt848[3];
    float constantsAt860[22];
    s32 idsAt948[2];
    void * referencesAt956;
    s32 idsAt960[3];
    float constantsAt972[22];
    s32 idsAt1060[2];
    void * referencesAt1068;
    s32 idsAt1072[3];
    float constantsAt1084[22];
    s32 idsAt1172[2];
    void * referencesAt1180;
    s32 idsAt1184[3];
    float constantsAt1196[22];
    s32 idsAt1284[2];
    void * referencesAt1292;
    s32 idsAt1296[3];
    float constantsAt1308[22];
    s32 idsAt1396[2];
    void * referencesAt1404;
    s32 idsAt1408[3];
    float constantsAt1420[22];
    s32 idsAt1508[2];
    void * referencesAt1516;
    s32 idsAt1520[3];
    float constantsAt1532[22];
    s32 idsAt1620[2];
    void * referencesAt1628;
    s32 idsAt1632[3];
    float constantsAt1644[22];
    s32 idsAt1732[2];
    void * referencesAt1740;
    s32 idsAt1744[3];
    float constantsAt1756[22];
    s32 idsAt1844[2];
    void * referencesAt1852;
    s32 idsAt1856[68];
} RestD_src_567cc0c4Layout424;

typedef struct RestcharacterPreviewDefinitionsEuXLayout425 {
    s32 idsAt0[4];
    void * referencesAt16;
    s32 idsAt20[3];
    float constantsAt32[22];
    s32 idsAt120[2];
    void * referencesAt128;
    s32 idsAt132[3];
    float constantsAt144[22];
    s32 idsAt232[2];
    void * referencesAt240;
    s32 idsAt244[3];
    float constantsAt256[20];
    s32 idsAt336[4];
    void * referencesAt352;
    s32 idsAt356[3];
    float constantsAt368[22];
    s32 idsAt456[2];
    void * referencesAt464;
    s32 idsAt468[3];
    float constantsAt480[22];
    s32 idsAt568[2];
    void * referencesAt576;
    s32 idsAt580[3];
    float constantsAt592[22];
    s32 idsAt680[2];
    void * referencesAt688;
    s32 idsAt692[3];
    float constantsAt704[22];
    s32 idsAt792[2];
    void * referencesAt800;
    s32 idsAt804[3];
    float constantsAt816[22];
    s32 idsAt904[2];
    void * referencesAt912;
    s32 idsAt916[3];
    float constantsAt928[22];
    s32 idsAt1016[2];
    void * referencesAt1024;
    s32 idsAt1028[3];
    float constantsAt1040[22];
    s32 idsAt1128[2];
    void * referencesAt1136;
    s32 idsAt1140[3];
    float constantsAt1152[22];
    s32 idsAt1240[2];
    void * referencesAt1248;
    s32 idsAt1252[3];
    float constantsAt1264[22];
    s32 idsAt1352[2];
    void * referencesAt1360;
    s32 idsAt1364[3];
    float constantsAt1376[22];
    s32 idsAt1464[2];
    void * referencesAt1472;
    s32 idsAt1476[3];
    float constantsAt1488[22];
    s32 idsAt1576[2];
    void * referencesAt1584;
    s32 idsAt1588[3];
    float constantsAt1600[22];
    s32 idsAt1688[2];
    void * referencesAt1696;
    s32 idsAt1700[3];
    float constantsAt1712[22];
    s32 idsAt1800[2];
    void * referencesAt1808;
    s32 idsAt1812[68];
} RestcharacterPreviewDefinitionsEuXLayout425;

typedef struct RestcharacterPreviewDefinitionsEuLayout426 {
    s32 idsAt0[4];
    void * referencesAt16;
    s32 idsAt20[3];
    float constantsAt32[22];
    s32 idsAt120[2];
    void * referencesAt128;
    s32 idsAt132[3];
    float constantsAt144[22];
    s32 idsAt232[2];
    void * referencesAt240;
    s32 idsAt244[3];
    float constantsAt256[20];
    s32 idsAt336[4];
    void * referencesAt352;
    s32 idsAt356[3];
    float constantsAt368[22];
    s32 idsAt456[2];
    void * referencesAt464;
    s32 idsAt468[3];
    float constantsAt480[22];
    s32 idsAt568[2];
    void * referencesAt576;
    s32 idsAt580[3];
    float constantsAt592[22];
    s32 idsAt680[2];
    void * referencesAt688;
    s32 idsAt692[3];
    float constantsAt704[22];
    s32 idsAt792[2];
    void * referencesAt800;
    s32 idsAt804[3];
    float constantsAt816[22];
    s32 idsAt904[2];
    void * referencesAt912;
    s32 idsAt916[3];
    float constantsAt928[22];
    s32 idsAt1016[2];
    void * referencesAt1024;
    s32 idsAt1028[3];
    float constantsAt1040[22];
    s32 idsAt1128[2];
    void * referencesAt1136;
    s32 idsAt1140[3];
    float constantsAt1152[22];
    s32 idsAt1240[2];
    void * referencesAt1248;
    s32 idsAt1252[3];
    float constantsAt1264[22];
    s32 idsAt1352[2];
    void * referencesAt1360;
    s32 idsAt1364[3];
    float constantsAt1376[22];
    s32 idsAt1464[2];
    void * referencesAt1472;
    s32 idsAt1476[3];
    float constantsAt1488[22];
    s32 idsAt1576[2];
    void * referencesAt1584;
    s32 idsAt1588[3];
    float constantsAt1600[22];
    s32 idsAt1688[2];
    void * referencesAt1696;
    s32 idsAt1700[3];
    float constantsAt1712[22];
    s32 idsAt1800[2];
    void * referencesAt1808;
    s32 idsAt1812[66];
    u32 packedValueAt2076;
    s32 idsAt2080;
} RestcharacterPreviewDefinitionsEuLayout426;

typedef struct RestcharacterPreviewEntryKeysUsRev1Layout430 {
    s32 idsAt0[2];
} RestcharacterPreviewEntryKeysUsRev1Layout430;

typedef struct RestcharacterPreviewEntryStateUsRev1Layout431 {
    s32 idsAt0;
} RestcharacterPreviewEntryStateUsRev1Layout431;

typedef struct RestFrontendAnimateslotselectionmenuEncodedWordsLayout433 {
    s32 idsAt0;
    void * referencesAt4;
    s32 idsAt8;
    void * referencesAt12;
    s32 idsAt16;
    void * referencesAt20;
    s32 idsAt24;
    void * referencesAt28;
    s32 idsAt32;
    void * referencesAt36;
    s32 idsAt40;
    void * referencesAt44;
    s32 idsAt48;
    void * referencesAt52;
    s32 idsAt56;
    void * referencesAt60;
    s32 idsAt64;
    void * referencesAt68;
    s32 idsAt72;
    void * referencesAt76;
    s32 idsAt80;
    void * referencesAt84;
    s32 idsAt88;
    void * referencesAt92;
    s32 idsAt96;
    void * referencesAt100;
    s32 idsAt104;
    void * referencesAt108;
    s32 idsAt112;
    void * referencesAt116;
    s32 idsAt120;
    void * referencesAt124;
    s32 idsAt128;
    void * referencesAt132;
    s32 idsAt136;
    void * referencesAt140;
    s32 idsAt144;
    void * referencesAt148;
    s32 idsAt152;
    void * referencesAt156;
    s32 idsAt160;
    void * referencesAt164;
    s32 idsAt168;
    void * referencesAt172;
    s32 idsAt176;
    void * referencesAt180;
    s32 idsAt184;
    void * referencesAt188;
    s32 idsAt192;
    void * referencesAt196;
    s32 idsAt200;
    void * referencesAt204;
    s32 idsAt208;
    void * referencesAt212;
    s32 idsAt216;
    void * referencesAt220;
    s32 idsAt224;
    void * referencesAt228;
    s32 idsAt232;
    void * referencesAt236;
    s32 idsAt240;
    void * referencesAt244;
    s32 idsAt248;
    void * referencesAt252;
    s32 idsAt256;
    void * referencesAt260;
    s32 idsAt264;
    void * referencesAt268;
    s32 idsAt272;
    void * referencesAt276;
    s32 idsAt280;
    void * referencesAt284;
    s32 idsAt288;
    void * referencesAt292;
    s32 idsAt296;
    void * referencesAt300;
    s32 idsAt304;
    void * referencesAt308;
    s32 idsAt312;
    void * referencesAt316;
    s32 idsAt320;
    void * referencesAt324;
    s32 idsAt328;
    void * referencesAt332;
    s32 idsAt336;
    void * referencesAt340;
    s32 idsAt344;
    void * referencesAt348;
    s32 idsAt352;
    void * referencesAt356;
    s32 idsAt360;
    void * referencesAt364;
    s32 idsAt368;
    void * referencesAt372;
    s32 idsAt376;
    void * referencesAt380;
    s32 idsAt384;
    void * referencesAt388;
    s32 idsAt392;
    void * referencesAt396;
    s32 idsAt400[63];
    void * referencesAt652;
    s32 idsAt656;
    void * referencesAt660;
    s32 idsAt664;
    void * referencesAt668;
    s32 idsAt672;
    void * referencesAt676;
    s32 idsAt680;
    void * referencesAt684;
    s32 idsAt688;
    void * referencesAt692;
    s32 idsAt696;
    void * referencesAt700;
    s32 idsAt704;
    void * referencesAt708;
    s32 idsAt712;
    void * referencesAt716;
    s32 idsAt720;
    void * referencesAt724;
    s32 idsAt728;
    void * referencesAt732;
    s32 idsAt736;
    void * referencesAt740;
    s32 idsAt744;
    void * referencesAt748;
    s32 idsAt752;
    void * referencesAt756;
    s32 idsAt760;
    void * referencesAt764;
    s32 idsAt768;
    void * referencesAt772;
    s32 idsAt776;
    void * referencesAt780[3];
    s32 idsAt792;
    void * referencesAt796;
    s32 idsAt800;
    void * referencesAt804;
    s32 idsAt808;
    void * referencesAt812;
    s32 idsAt816;
    void * referencesAt820;
    s32 idsAt824;
    void * referencesAt828;
    s32 idsAt832;
    void * referencesAt836;
    s32 idsAt840;
    void * referencesAt844;
    s32 idsAt848;
    void * referencesAt852;
    s32 idsAt856;
    void * referencesAt860;
    s32 idsAt864;
    void * referencesAt868;
    s32 idsAt872;
    void * referencesAt876;
    s32 idsAt880;
    void * referencesAt884;
    s32 idsAt888;
    void * referencesAt892;
    s32 idsAt896;
    void * referencesAt900;
    s32 idsAt904;
    void * referencesAt908;
    s32 idsAt912;
    void * referencesAt916[3];
    s32 idsAt928;
    void * referencesAt932;
    s32 idsAt936;
    void * referencesAt940;
    s32 idsAt944;
    void * referencesAt948;
    s32 idsAt952;
    void * referencesAt956;
    s32 idsAt960;
    void * referencesAt964;
    s32 idsAt968;
    void * referencesAt972;
    s32 idsAt976;
    void * referencesAt980;
    s32 idsAt984;
    void * referencesAt988;
    s32 idsAt992;
    void * referencesAt996;
    s32 idsAt1000;
    void * referencesAt1004;
    s32 idsAt1008;
    void * referencesAt1012;
    s32 idsAt1016;
    void * referencesAt1020;
    s32 idsAt1024;
    void * referencesAt1028;
    s32 idsAt1032;
    void * referencesAt1036;
    s32 idsAt1040;
    void * referencesAt1044;
    s32 idsAt1048;
    void * referencesAt1052[4];
} RestFrontendAnimateslotselectionmenuEncodedWordsLayout433;

typedef struct RestFrontendAnimateslotselectionmenuEncodedWordsLayout434 {
    s32 idsAt0;
    void * referencesAt4;
    s32 idsAt8;
    void * referencesAt12;
    s32 idsAt16;
    void * referencesAt20;
    s32 idsAt24;
    void * referencesAt28;
    s32 idsAt32;
    void * referencesAt36;
    s32 idsAt40;
    void * referencesAt44;
    s32 idsAt48;
    void * referencesAt52;
    s32 idsAt56;
    void * referencesAt60;
    s32 idsAt64;
    void * referencesAt68;
    s32 idsAt72;
    void * referencesAt76;
    s32 idsAt80;
    void * referencesAt84;
    s32 idsAt88;
    void * referencesAt92;
    s32 idsAt96;
    void * referencesAt100;
    s32 idsAt104;
    void * referencesAt108;
    s32 idsAt112;
    void * referencesAt116;
    s32 idsAt120;
    void * referencesAt124;
    s32 idsAt128;
    void * referencesAt132;
    s32 idsAt136;
    void * referencesAt140;
    s32 idsAt144;
    void * referencesAt148;
    s32 idsAt152;
    void * referencesAt156;
    s32 idsAt160;
    void * referencesAt164;
    s32 idsAt168;
    void * referencesAt172;
    s32 idsAt176;
    void * referencesAt180;
    s32 idsAt184;
    void * referencesAt188;
    s32 idsAt192;
    void * referencesAt196;
    s32 idsAt200;
    void * referencesAt204;
    s32 idsAt208;
    void * referencesAt212;
    s32 idsAt216;
    void * referencesAt220;
    s32 idsAt224;
    void * referencesAt228;
    s32 idsAt232;
    void * referencesAt236;
    s32 idsAt240;
    void * referencesAt244;
    s32 idsAt248;
    void * referencesAt252;
    s32 idsAt256;
    void * referencesAt260;
    s32 idsAt264;
    void * referencesAt268;
    s32 idsAt272;
    void * referencesAt276;
    s32 idsAt280;
    void * referencesAt284;
    s32 idsAt288;
    void * referencesAt292;
    s32 idsAt296;
    void * referencesAt300;
    s32 idsAt304;
    void * referencesAt308;
    s32 idsAt312;
    void * referencesAt316;
    s32 idsAt320;
    void * referencesAt324;
    s32 idsAt328;
    void * referencesAt332;
    s32 idsAt336;
    void * referencesAt340;
    s32 idsAt344;
    void * referencesAt348;
    s32 idsAt352;
    void * referencesAt356;
    s32 idsAt360;
    void * referencesAt364;
    s32 idsAt368;
    void * referencesAt372;
    s32 idsAt376;
    void * referencesAt380;
    s32 idsAt384;
    void * referencesAt388;
    s32 idsAt392;
    void * referencesAt396;
    s32 idsAt400[63];
    void * referencesAt652;
    s32 idsAt656;
    void * referencesAt660;
    s32 idsAt664;
    void * referencesAt668;
    s32 idsAt672;
    void * referencesAt676;
    s32 idsAt680;
    void * referencesAt684;
    s32 idsAt688;
    void * referencesAt692;
    s32 idsAt696;
    void * referencesAt700;
    s32 idsAt704;
    void * referencesAt708;
    s32 idsAt712;
    void * referencesAt716;
    s32 idsAt720;
    void * referencesAt724;
    s32 idsAt728;
    void * referencesAt732;
    s32 idsAt736;
    void * referencesAt740;
    s32 idsAt744;
    void * referencesAt748;
    s32 idsAt752;
    void * referencesAt756;
    s32 idsAt760;
    void * referencesAt764;
    s32 idsAt768;
    void * referencesAt772;
    s32 idsAt776;
    void * referencesAt780[3];
    s32 idsAt792;
    void * referencesAt796;
    s32 idsAt800;
    void * referencesAt804;
    s32 idsAt808;
    void * referencesAt812;
    s32 idsAt816;
    void * referencesAt820;
    s32 idsAt824;
    void * referencesAt828;
    s32 idsAt832;
    void * referencesAt836;
    s32 idsAt840;
    void * referencesAt844;
    s32 idsAt848;
    void * referencesAt852;
    s32 idsAt856;
    void * referencesAt860;
    s32 idsAt864;
    void * referencesAt868;
    s32 idsAt872;
    void * referencesAt876;
    s32 idsAt880;
    void * referencesAt884;
    s32 idsAt888;
    void * referencesAt892;
    s32 idsAt896;
    void * referencesAt900;
    s32 idsAt904;
    void * referencesAt908;
    s32 idsAt912;
    void * referencesAt916[3];
    s32 idsAt928;
    void * referencesAt932;
    s32 idsAt936;
    void * referencesAt940;
    s32 idsAt944;
    void * referencesAt948;
    s32 idsAt952;
    void * referencesAt956;
    s32 idsAt960;
    void * referencesAt964;
    s32 idsAt968;
    void * referencesAt972;
    s32 idsAt976;
    void * referencesAt980;
    s32 idsAt984;
    void * referencesAt988;
    s32 idsAt992;
    void * referencesAt996;
    s32 idsAt1000;
    void * referencesAt1004;
    s32 idsAt1008;
    void * referencesAt1012;
    s32 idsAt1016;
    void * referencesAt1020;
    s32 idsAt1024;
    void * referencesAt1028;
    s32 idsAt1032;
    void * referencesAt1036;
    s32 idsAt1040;
    void * referencesAt1044;
    s32 idsAt1048;
    void * referencesAt1052[4];
} RestFrontendAnimateslotselectionmenuEncodedWordsLayout434;

typedef struct RestFrontendAnimateslotselectionmenuEncodedWordsLayout435 {
    s32 idsAt0;
    void * referencesAt4;
    s32 idsAt8;
    void * referencesAt12;
    s32 idsAt16;
    void * referencesAt20;
    s32 idsAt24;
    void * referencesAt28;
    s32 idsAt32;
    void * referencesAt36;
    s32 idsAt40;
    void * referencesAt44;
    s32 idsAt48;
    void * referencesAt52;
    s32 idsAt56;
    void * referencesAt60;
    s32 idsAt64;
    void * referencesAt68;
    s32 idsAt72;
    void * referencesAt76;
    s32 idsAt80;
    void * referencesAt84;
    s32 idsAt88;
    void * referencesAt92;
    s32 idsAt96;
    void * referencesAt100;
    s32 idsAt104;
    void * referencesAt108;
    s32 idsAt112;
    void * referencesAt116;
    s32 idsAt120;
    void * referencesAt124;
    s32 idsAt128;
    void * referencesAt132;
    s32 idsAt136;
    void * referencesAt140;
    s32 idsAt144;
    void * referencesAt148;
    s32 idsAt152;
    void * referencesAt156;
    s32 idsAt160;
    void * referencesAt164;
    s32 idsAt168;
    void * referencesAt172;
    s32 idsAt176;
    void * referencesAt180;
    s32 idsAt184;
    void * referencesAt188;
    s32 idsAt192;
    void * referencesAt196;
    s32 idsAt200;
    void * referencesAt204;
    s32 idsAt208;
    void * referencesAt212;
    s32 idsAt216;
    void * referencesAt220;
    s32 idsAt224;
    void * referencesAt228;
    s32 idsAt232;
    void * referencesAt236;
    s32 idsAt240;
    void * referencesAt244;
    s32 idsAt248;
    void * referencesAt252;
    s32 idsAt256;
    void * referencesAt260;
    s32 idsAt264;
    void * referencesAt268;
    s32 idsAt272;
    void * referencesAt276;
    s32 idsAt280;
    void * referencesAt284;
    s32 idsAt288;
    void * referencesAt292;
    s32 idsAt296;
    void * referencesAt300;
    s32 idsAt304;
    void * referencesAt308;
    s32 idsAt312;
    void * referencesAt316;
    s32 idsAt320;
    void * referencesAt324;
    s32 idsAt328;
    void * referencesAt332;
    s32 idsAt336;
    void * referencesAt340;
    s32 idsAt344;
    void * referencesAt348;
    s32 idsAt352;
    void * referencesAt356;
    s32 idsAt360;
    void * referencesAt364;
    s32 idsAt368;
    void * referencesAt372;
    s32 idsAt376;
    void * referencesAt380;
    s32 idsAt384;
    void * referencesAt388;
    s32 idsAt392;
    void * referencesAt396;
    s32 idsAt400[63];
    void * referencesAt652;
    s32 idsAt656;
    void * referencesAt660;
    s32 idsAt664;
    void * referencesAt668;
    s32 idsAt672;
    void * referencesAt676;
    s32 idsAt680;
    void * referencesAt684;
    s32 idsAt688;
    void * referencesAt692;
    s32 idsAt696;
    void * referencesAt700;
    s32 idsAt704;
    void * referencesAt708;
    s32 idsAt712;
    void * referencesAt716;
    s32 idsAt720;
    void * referencesAt724;
    s32 idsAt728;
    void * referencesAt732;
    s32 idsAt736;
    void * referencesAt740;
    s32 idsAt744;
    void * referencesAt748;
    s32 idsAt752;
    void * referencesAt756;
    s32 idsAt760;
    void * referencesAt764;
    s32 idsAt768;
    void * referencesAt772;
    s32 idsAt776;
    void * referencesAt780[3];
    s32 idsAt792;
    void * referencesAt796;
    s32 idsAt800;
    void * referencesAt804;
    s32 idsAt808;
    void * referencesAt812;
    s32 idsAt816;
    void * referencesAt820;
    s32 idsAt824;
    void * referencesAt828;
    s32 idsAt832;
    void * referencesAt836;
    s32 idsAt840;
    void * referencesAt844;
    s32 idsAt848;
    void * referencesAt852;
    s32 idsAt856;
    void * referencesAt860;
    s32 idsAt864;
    void * referencesAt868;
    s32 idsAt872;
    void * referencesAt876;
    s32 idsAt880;
    void * referencesAt884;
    s32 idsAt888;
    void * referencesAt892;
    s32 idsAt896;
    void * referencesAt900;
    s32 idsAt904;
    void * referencesAt908;
    s32 idsAt912;
    void * referencesAt916[3];
    s32 idsAt928;
    void * referencesAt932;
    s32 idsAt936;
    void * referencesAt940;
    s32 idsAt944;
    void * referencesAt948;
    s32 idsAt952;
    void * referencesAt956;
    s32 idsAt960;
    void * referencesAt964;
    s32 idsAt968;
    void * referencesAt972;
    s32 idsAt976;
    void * referencesAt980;
    s32 idsAt984;
    void * referencesAt988;
    s32 idsAt992;
    void * referencesAt996;
    s32 idsAt1000;
    void * referencesAt1004;
    s32 idsAt1008;
    void * referencesAt1012;
    s32 idsAt1016;
    void * referencesAt1020;
    s32 idsAt1024;
    void * referencesAt1028;
    s32 idsAt1032;
    void * referencesAt1036;
    s32 idsAt1040;
    void * referencesAt1044;
    s32 idsAt1048;
    void * referencesAt1052[4];
} RestFrontendAnimateslotselectionmenuEncodedWordsLayout435;

typedef struct RestFrontendAnimateslotselectionmenuEncodedWordsLayout436 {
    s32 idsAt0;
    void * referencesAt4;
    s32 idsAt8;
    void * referencesAt12;
    s32 idsAt16;
    void * referencesAt20;
    s32 idsAt24;
    void * referencesAt28;
    s32 idsAt32;
    void * referencesAt36;
    s32 idsAt40;
    void * referencesAt44;
    s32 idsAt48;
    void * referencesAt52;
    s32 idsAt56;
    void * referencesAt60;
    s32 idsAt64;
    void * referencesAt68;
    s32 idsAt72;
    void * referencesAt76;
    s32 idsAt80;
    void * referencesAt84;
    s32 idsAt88;
    void * referencesAt92;
    s32 idsAt96;
    void * referencesAt100;
    s32 idsAt104;
    void * referencesAt108;
    s32 idsAt112;
    void * referencesAt116;
    s32 idsAt120;
    void * referencesAt124;
    s32 idsAt128;
    void * referencesAt132;
    s32 idsAt136;
    void * referencesAt140;
    s32 idsAt144;
    void * referencesAt148;
    s32 idsAt152;
    void * referencesAt156;
    s32 idsAt160;
    void * referencesAt164;
    s32 idsAt168;
    void * referencesAt172;
    s32 idsAt176;
    void * referencesAt180;
    s32 idsAt184;
    void * referencesAt188;
    s32 idsAt192;
    void * referencesAt196;
    s32 idsAt200;
    void * referencesAt204;
    s32 idsAt208;
    void * referencesAt212;
    s32 idsAt216;
    void * referencesAt220;
    s32 idsAt224;
    void * referencesAt228;
    s32 idsAt232;
    void * referencesAt236;
    s32 idsAt240;
    void * referencesAt244;
    s32 idsAt248;
    void * referencesAt252;
    s32 idsAt256;
    void * referencesAt260;
    s32 idsAt264;
    void * referencesAt268;
    s32 idsAt272;
    void * referencesAt276;
    s32 idsAt280;
    void * referencesAt284;
    s32 idsAt288;
    void * referencesAt292;
    s32 idsAt296;
    void * referencesAt300;
    s32 idsAt304;
    void * referencesAt308;
    s32 idsAt312;
    void * referencesAt316;
    s32 idsAt320;
    void * referencesAt324;
    s32 idsAt328;
    void * referencesAt332;
    s32 idsAt336;
    void * referencesAt340;
    s32 idsAt344;
    void * referencesAt348;
    s32 idsAt352;
    void * referencesAt356;
    s32 idsAt360;
    void * referencesAt364;
    s32 idsAt368;
    void * referencesAt372;
    s32 idsAt376;
    void * referencesAt380;
    s32 idsAt384;
    void * referencesAt388;
    s32 idsAt392;
    void * referencesAt396;
    s32 idsAt400[63];
    void * referencesAt652;
    s32 idsAt656;
    void * referencesAt660;
    s32 idsAt664;
    void * referencesAt668;
    s32 idsAt672;
    void * referencesAt676;
    s32 idsAt680;
    void * referencesAt684;
    s32 idsAt688;
    void * referencesAt692;
    s32 idsAt696;
    void * referencesAt700;
    s32 idsAt704;
    void * referencesAt708;
    s32 idsAt712;
    void * referencesAt716;
    s32 idsAt720;
    void * referencesAt724;
    s32 idsAt728;
    void * referencesAt732;
    s32 idsAt736;
    void * referencesAt740;
    s32 idsAt744;
    void * referencesAt748;
    s32 idsAt752;
    void * referencesAt756;
    s32 idsAt760;
    void * referencesAt764;
    s32 idsAt768;
    void * referencesAt772;
    s32 idsAt776;
    void * referencesAt780[3];
    s32 idsAt792;
    void * referencesAt796;
    s32 idsAt800;
    void * referencesAt804;
    s32 idsAt808;
    void * referencesAt812;
    s32 idsAt816;
    void * referencesAt820;
    s32 idsAt824;
    void * referencesAt828;
    s32 idsAt832;
    void * referencesAt836;
    s32 idsAt840;
    void * referencesAt844;
    s32 idsAt848;
    void * referencesAt852;
    s32 idsAt856;
    void * referencesAt860;
    s32 idsAt864;
    void * referencesAt868;
    s32 idsAt872;
    void * referencesAt876;
    s32 idsAt880;
    void * referencesAt884;
    s32 idsAt888;
    void * referencesAt892;
    s32 idsAt896;
    void * referencesAt900;
    s32 idsAt904;
    void * referencesAt908;
    s32 idsAt912;
    void * referencesAt916[3];
    s32 idsAt928;
    void * referencesAt932;
    s32 idsAt936;
    void * referencesAt940;
    s32 idsAt944;
    void * referencesAt948;
    s32 idsAt952;
    void * referencesAt956;
    s32 idsAt960;
    void * referencesAt964;
    s32 idsAt968;
    void * referencesAt972;
    s32 idsAt976;
    void * referencesAt980;
    s32 idsAt984;
    void * referencesAt988;
    s32 idsAt992;
    void * referencesAt996;
    s32 idsAt1000;
    void * referencesAt1004;
    s32 idsAt1008;
    void * referencesAt1012;
    s32 idsAt1016;
    void * referencesAt1020;
    s32 idsAt1024;
    void * referencesAt1028;
    s32 idsAt1032;
    void * referencesAt1036;
    s32 idsAt1040;
    void * referencesAt1044;
    s32 idsAt1048;
    void * referencesAt1052[4];
} RestFrontendAnimateslotselectionmenuEncodedWordsLayout436;

typedef struct RestslotSelectionLabelIdPointerPairsUsRev1Layout437 {
    s32 idsAt0;
    void * referencesAt4;
    s32 idsAt8;
    void * referencesAt12;
    s32 idsAt16;
    void * referencesAt20;
    s32 idsAt24;
    void * referencesAt28;
    s32 idsAt32;
    void * referencesAt36;
    s32 idsAt40;
    void * referencesAt44;
    s32 idsAt48;
    void * referencesAt52;
    s32 idsAt56;
    void * referencesAt60;
    s32 idsAt64;
    void * referencesAt68;
    s32 idsAt72;
    void * referencesAt76;
    s32 idsAt80;
    void * referencesAt84;
    s32 idsAt88;
    void * referencesAt92;
    s32 idsAt96;
    void * referencesAt100;
    s32 idsAt104;
    void * referencesAt108;
    s32 idsAt112;
    void * referencesAt116;
    s32 idsAt120;
    void * referencesAt124;
    s32 idsAt128;
    void * referencesAt132;
    s32 idsAt136;
    void * referencesAt140;
    s32 idsAt144;
    void * referencesAt148;
    s32 idsAt152;
    void * referencesAt156;
    s32 idsAt160;
    void * referencesAt164;
    s32 idsAt168;
    void * referencesAt172;
    s32 idsAt176;
    void * referencesAt180;
    s32 idsAt184;
    void * referencesAt188;
    s32 idsAt192;
    void * referencesAt196;
    s32 idsAt200;
    void * referencesAt204;
    s32 idsAt208;
    void * referencesAt212;
    s32 idsAt216;
    void * referencesAt220;
    s32 idsAt224;
    void * referencesAt228;
    s32 idsAt232;
    void * referencesAt236;
    s32 idsAt240;
    void * referencesAt244;
    s32 idsAt248;
    void * referencesAt252;
    s32 idsAt256;
    void * referencesAt260;
    s32 idsAt264;
    void * referencesAt268;
    s32 idsAt272;
    void * referencesAt276;
    s32 idsAt280;
    void * referencesAt284;
    s32 idsAt288;
    void * referencesAt292;
    s32 idsAt296;
    void * referencesAt300;
    s32 idsAt304;
    void * referencesAt308;
    s32 idsAt312;
    void * referencesAt316;
    s32 idsAt320;
    void * referencesAt324;
    s32 idsAt328;
    void * referencesAt332;
    s32 idsAt336;
    void * referencesAt340;
    s32 idsAt344;
    void * referencesAt348;
    s32 idsAt352;
    void * referencesAt356;
    s32 idsAt360;
    void * referencesAt364;
    s32 idsAt368;
    void * referencesAt372;
    s32 idsAt376;
    void * referencesAt380;
    s32 idsAt384;
    void * referencesAt388;
    s32 idsAt392;
    void * referencesAt396;
} RestslotSelectionLabelIdPointerPairsUsRev1Layout437;

typedef struct RestjoinOptionsTrailingWordsLayout447 {
    s32 idsAt0[3];
    float constantsAt12[4];
} RestjoinOptionsTrailingWordsLayout447;

typedef struct RestjoinOptionsTrailingWords_eu_xLayout448 {
    s32 idsAt0[3];
    float constantsAt12[4];
} RestjoinOptionsTrailingWords_eu_xLayout448;

typedef struct RestjoinOptionsTrailingWords_deLayout449 {
    s32 idsAt0[3];
    float constantsAt12[4];
} RestjoinOptionsTrailingWords_deLayout449;

typedef struct RestbuttonWidgetHandlerTailUsRev1Layout454 {
    void * referencesAt0;
    s32 idsAt4[2];
    void * referencesAt12;
    s32 idsAt16[2];
    void * referencesAt24;
    s32 idsAt28[2];
    void * referencesAt36;
    s32 idsAt40[2];
    void * referencesAt48;
    s32 idsAt52[2];
    void * referencesAt60;
    s32 idsAt64[2];
    void * referencesAt72;
    s32 idsAt76[2];
    void * referencesAt84;
    s32 idsAt88[2];
    void * referencesAt96[4];
    s32 idsAt112;
} RestbuttonWidgetHandlerTailUsRev1Layout454;

typedef struct RestD_src_897c5b16Layout455 {
    s32 idsAt0[21];
    u32 packedValueAt84;
    u32 packedValueAt88;
    float constantsAt92[2];
    s32 idsAt100[2];
    void * referencesAt108;
    s32 idsAt112;
} RestD_src_897c5b16Layout455;

typedef struct RestD_src_897c5b16Layout456 {
    s32 idsAt0[21];
    u32 packedValueAt84;
    u32 packedValueAt88;
    float constantsAt92[2];
    s32 idsAt100[2];
    float constantsAt108;
    u32 packedValueAt112;
} RestD_src_897c5b16Layout456;

typedef struct RestD_src_897c5b16Layout457 {
    s32 idsAt0[21];
    u32 packedValueAt84;
    u32 packedValueAt88;
    float constantsAt92[2];
    s32 idsAt100[4];
} RestD_src_897c5b16Layout457;

typedef struct RestpakDialogStyleAndTextWords_usLayout459 {
    u32 packedValueAt0;
    u32 packedValueAt4;
    float constantsAt8[2];
    s32 idsAt16[2];
    char textAt24[8];
} RestpakDialogStyleAndTextWords_usLayout459;

typedef struct RestEncodedInserttextentrycharacterEncodedHalfwordsLayout468 {
    s32 idsAt0[6];
    void * referencesAt24;
    char textAt28[20];
    void * referencesAt48;
    char textAt52[24];
    void * referencesAt76[10];
    s32 idsAt116;
    u32 packedValueAt120;
    s32 idsAt124[8];
    u32 packedValueAt156;
    s32 idsAt160[2];
    void * referencesAt168;
    s32 idsAt172[8];
    void * referencesAt204;
    s32 idsAt208[8];
    void * referencesAt240;
    s32 idsAt244[8];
    void * referencesAt276;
    s32 idsAt280[4];
    void * referencesAt296;
    s32 idsAt300[28];
} RestEncodedInserttextentrycharacterEncodedHalfwordsLayout468;

typedef struct RestEncodedInserttextentrycharacterEncodedHalfwordsLayout469 {
    s32 idsAt0[6];
    void * referencesAt24[4];
    char textAt40[20];
    void * referencesAt60[4];
    char textAt76[24];
    void * referencesAt100[24];
    s32 idsAt196;
    u32 packedValueAt200;
    s32 idsAt204[8];
    u32 packedValueAt236;
    s32 idsAt240[2];
    void * referencesAt248;
    s32 idsAt252[8];
    void * referencesAt284;
    s32 idsAt288[8];
    void * referencesAt320;
    s32 idsAt324[8];
    void * referencesAt356;
    s32 idsAt360[4];
    void * referencesAt376;
    s32 idsAt380[28];
} RestEncodedInserttextentrycharacterEncodedHalfwordsLayout469;

typedef struct RestEncodedInserttextentrycharacterEncodedHalfwordsLayout470 {
    s32 idsAt0[6];
    void * referencesAt24[4];
    char textAt40[20];
    void * referencesAt60[4];
    char textAt76[24];
    void * referencesAt100[24];
    s32 idsAt196;
    u32 packedValueAt200;
    s32 idsAt204[8];
    u32 packedValueAt236;
    s32 idsAt240[2];
    void * referencesAt248;
    s32 idsAt252[8];
    void * referencesAt284;
    s32 idsAt288[8];
    void * referencesAt320;
    s32 idsAt324[8];
    void * referencesAt356;
    s32 idsAt360[4];
    void * referencesAt376;
    s32 idsAt380[28];
} RestEncodedInserttextentrycharacterEncodedHalfwordsLayout470;

typedef struct RestEncodedInserttextentrycharacterEncodedHalfwordsLayout471 {
    s32 idsAt0[6];
    void * referencesAt24;
    char textAt28[20];
    void * referencesAt48;
    char textAt52[24];
    void * referencesAt76;
    char textAt80[4];
    void * referencesAt84[8];
    s32 idsAt116;
    u32 packedValueAt120;
    s32 idsAt124[8];
    u32 packedValueAt156;
    s32 idsAt160[2];
    void * referencesAt168;
    s32 idsAt172[8];
    void * referencesAt204;
    s32 idsAt208[8];
    void * referencesAt240;
    s32 idsAt244[8];
    void * referencesAt276;
    s32 idsAt280[4];
    void * referencesAt296;
    s32 idsAt300[28];
} RestEncodedInserttextentrycharacterEncodedHalfwordsLayout471;

typedef struct RestD_src_9d8a2047Layout476 {
    s32 idsAt0[2];
    u32 packedCallbackAt8;
    s32 idsAt12[2];
    u32 packedCallbackAt20;
    s32 idsAt24[2];
    u32 packedCallbackAt32;
    s32 idsAt36[2];
    u32 packedCallbackAt44;
    s32 idsAt48[2];
    u32 packedCallbackAt56;
    s32 idsAt60[2];
    void * referencesAt68[4];
    u32 packedCallbackAt84;
    s32 idsAt88[3];
    u32 packedCallbackAt100;
    s32 idsAt104[2];
    u32 packedCallbackAt112;
    s32 idsAt116[2];
    u32 packedCallbackAt124;
    s32 idsAt128[3];
} RestD_src_9d8a2047Layout476;

typedef struct RestD_src_9d8a2047Layout477 {
    s32 idsAt0[21];
    u32 packedValueAt84;
    u32 packedValueAt88;
    s32 idsAt92[12];
} RestD_src_9d8a2047Layout477;

typedef struct RestFrontendPulseprofileresetwidgetPointerWordsTailUsLayout479 {
    u32 packedValueAt0;
    char textAt4[4];
    s32 idsAt8[12];
} RestFrontendPulseprofileresetwidgetPointerWordsTailUsLayout479;

typedef struct RestGMenuboxcornersWords1Layout481 {
    s32 idsAt0;
    char textAt4[28];
    u32 packedValueAt32;
    float constantsAt36;
    s32 idsAt40;
} RestGMenuboxcornersWords1Layout481;

typedef struct RestGMenuboxcornersWords1Layout482 {
    s32 idsAt0;
    char textAt4[28];
    u32 packedValueAt32;
    s32 idsAt36[2];
} RestGMenuboxcornersWords1Layout482;

typedef struct RestGMenuboxcornersWords1Layout483 {
    s32 idsAt0;
    char textAt4[32];
    u32 packedValueAt36;
    s32 idsAt40;
} RestGMenuboxcornersWords1Layout483;

typedef struct RestGMenuboxcornersWords1Layout484 {
    s32 idsAt0;
    char textAt4[36];
    s32 idsAt40;
} RestGMenuboxcornersWords1Layout484;

typedef struct RestGMenuboxcornersWords1Layout485 {
    s32 idsAt0;
    char textAt4[36];
    s32 idsAt40;
} RestGMenuboxcornersWords1Layout485;

typedef struct RestD_src_afbf569bLayout486 {
    s32 idsAt0;
    float constantsAt4[4];
    u32 packedValueAt20;
    char textAt24[4];
    s32 idsAt28;
    float constantsAt32[4];
    u32 packedValueAt48;
    char textAt52[12];
    float constantsAt64[3];
    u32 packedValueAt76;
    char textAt80[4];
    s32 idsAt84;
    float constantsAt88[4];
    u32 packedValueAt104;
    char textAt108[12];
    float constantsAt120[3];
    s32 idsAt132;
    char textAt136[4];
    s32 idsAt140;
    float constantsAt144[4];
    u32 packedValueAt160;
    char textAt164[8];
    float constantsAt172[4];
    u32 packedValueAt188;
    char textAt192[4];
    s32 idsAt196;
    float constantsAt200[4];
    u32 packedValueAt216;
    s32 idsAt220[2];
    float constantsAt228[4];
    u32 packedValueAt244;
    char textAt248[4];
} RestD_src_afbf569bLayout486;

typedef struct RestGMenuboxcornersLevelTextWords1Layout487 {
    s32 idsAt0[2];
    float constantsAt8;
    char textAt12[28];
    void * referencesAt40;
    char textAt44[24];
    void * referencesAt68;
    char textAt72[24];
    void * referencesAt96;
    char textAt100[24];
    void * referencesAt124;
    u32 packedValueAt128;
    u32 packedValueAt132;
    u32 packedValueAt136;
    u32 packedValueAt140;
    u32 packedValueAt144;
    u32 packedValueAt148;
    u32 packedValueAt152;
    u32 packedValueAt156;
    u32 packedValueAt160;
    u32 packedValueAt164;
    u32 packedValueAt168;
    u32 packedValueAt172;
    void * referencesAt176;
} RestGMenuboxcornersLevelTextWords1Layout487;

typedef struct RestD_src_afbf569bLayout488 {
    s32 idsAt0;
    float constantsAt4[4];
    u32 packedValueAt20;
    char textAt24[4];
    s32 idsAt28;
    char textAt32[12];
    float constantsAt44;
    u32 packedValueAt48;
    char textAt52[12];
    float constantsAt64[3];
    u32 packedValueAt76;
    char textAt80[4];
    s32 idsAt84;
    float constantsAt88[4];
    u32 packedValueAt104;
    char textAt108[12];
    float constantsAt120[3];
    s32 idsAt132;
    char textAt136[8];
    float constantsAt144[4];
    u32 packedValueAt160;
    char textAt164[8];
    float constantsAt172[4];
    u32 packedValueAt188;
    char textAt192[4];
    s32 idsAt196;
    float constantsAt200[4];
    u32 packedValueAt216;
    s32 idsAt220[2];
    float constantsAt228[4];
    u32 packedValueAt244;
    char textAt248[4];
} RestD_src_afbf569bLayout488;

typedef struct RestGMenuboxcornersOurclevelTextWords1Layout489 {
    s32 idsAt0[2];
    float constantsAt8;
    char textAt12[28];
    void * referencesAt40;
    char textAt44[24];
    void * referencesAt68;
    char textAt72[24];
    void * referencesAt96;
    char textAt100[24];
    void * referencesAt124;
    u32 packedValueAt128;
    u32 packedValueAt132;
    u32 packedValueAt136;
    u32 packedValueAt140;
    u32 packedValueAt144;
    u32 packedValueAt148;
    u32 packedValueAt152;
    u32 packedValueAt156;
    u32 packedValueAt160;
    u32 packedValueAt164;
    u32 packedValueAt168;
    u32 packedValueAt172;
    void * referencesAt176;
} RestGMenuboxcornersOurclevelTextWords1Layout489;

typedef struct RestfloatRecordWordsEuXLayout490 {
    s32 idsAt0;
    float constantsAt4[4];
    u32 packedValueAt20;
    char textAt24[4];
    s32 idsAt28;
    float constantsAt32[4];
    u32 packedValueAt48;
    char textAt52[8];
    float constantsAt60[4];
    u32 packedValueAt76;
    char textAt80[4];
    s32 idsAt84;
    float constantsAt88[4];
    u32 packedValueAt104;
    char textAt108[8];
    float constantsAt116[4];
    s32 idsAt132;
    char textAt136[4];
    s32 idsAt140;
    float constantsAt144[4];
    u32 packedValueAt160;
    char textAt164[8];
    float constantsAt172[4];
    u32 packedValueAt188;
    char textAt192[4];
    s32 idsAt196;
    float constantsAt200[4];
    u32 packedValueAt216;
    s32 idsAt220[2];
    float constantsAt228[4];
    u32 packedValueAt244;
    char textAt248[8];
    float constantsAt256[4];
    u32 packedValueAt272;
    char textAt276[4];
    s32 idsAt280;
    float constantsAt284[4];
    u32 packedValueAt300;
    char textAt304[8];
    float constantsAt312[4];
    u32 packedValueAt328;
    char textAt332[4];
    s32 idsAt336;
    float constantsAt340[4];
    u32 packedValueAt356;
    char textAt360[8];
    float constantsAt368[4];
    s32 idsAt384;
    char textAt388[4];
    s32 idsAt392;
    float constantsAt396[4];
    u32 packedValueAt412;
    char textAt416[8];
    float constantsAt424[4];
    u32 packedValueAt440;
    char textAt444[4];
    s32 idsAt448;
    float constantsAt452[4];
    u32 packedValueAt468;
    s32 idsAt472[2];
    float constantsAt480[4];
    u32 packedValueAt496;
    char textAt500[8];
    float constantsAt508[4];
    u32 packedValueAt524;
    char textAt528[4];
    s32 idsAt532;
    float constantsAt536[4];
    u32 packedValueAt552;
    char textAt556[8];
    float constantsAt564[4];
    u32 packedValueAt580;
    char textAt584[4];
    s32 idsAt588;
    float constantsAt592[4];
    u32 packedValueAt608;
    char textAt612[8];
    float constantsAt620[4];
    s32 idsAt636;
    char textAt640[4];
    s32 idsAt644;
    float constantsAt648[4];
    u32 packedValueAt664;
    char textAt668[8];
    float constantsAt676[4];
    u32 packedValueAt692;
    char textAt696[4];
    s32 idsAt700;
    float constantsAt704[4];
    u32 packedValueAt720;
    s32 idsAt724[2];
    float constantsAt732[4];
    u32 packedValueAt748;
    char textAt752[4];
} RestfloatRecordWordsEuXLayout490;

typedef struct RestGMenuboxcornersLevelTextWords2Layout491 {
    s32 idsAt0[2];
    float constantsAt8;
    char textAt12[24];
    void * referencesAt36[4];
    char textAt52[24];
    void * referencesAt76[4];
    char textAt92[24];
    void * referencesAt116[4];
    char textAt132[24];
    void * referencesAt156[4];
    u32 packedValueAt172;
    u32 packedValueAt176;
    u32 packedValueAt180;
    u32 packedValueAt184;
    u32 packedValueAt188;
    u32 packedValueAt192;
    u32 packedValueAt196;
    u32 packedValueAt200;
    u32 packedValueAt204;
    u32 packedValueAt208;
    u32 packedValueAt212;
    u32 packedValueAt216;
    void * referencesAt220[4];
} RestGMenuboxcornersLevelTextWords2Layout491;

typedef struct RestfloatRecordWordsEuLayout492 {
    s32 idsAt0;
    float constantsAt4[4];
    u32 packedValueAt20;
    char textAt24[4];
    s32 idsAt28;
    float constantsAt32[4];
    u32 packedValueAt48;
    char textAt52[8];
    float constantsAt60[4];
    u32 packedValueAt76;
    char textAt80[4];
    s32 idsAt84;
    float constantsAt88[4];
    u32 packedValueAt104;
    char textAt108[8];
    float constantsAt116[4];
    s32 idsAt132;
    char textAt136[4];
    s32 idsAt140;
    float constantsAt144[4];
    u32 packedValueAt160;
    char textAt164[8];
    float constantsAt172[4];
    u32 packedValueAt188;
    char textAt192[4];
    s32 idsAt196;
    float constantsAt200[4];
    u32 packedValueAt216;
    s32 idsAt220[2];
    float constantsAt228[4];
    u32 packedValueAt244;
    char textAt248[8];
    float constantsAt256[4];
    u32 packedValueAt272;
    char textAt276[4];
    s32 idsAt280;
    float constantsAt284[4];
    u32 packedValueAt300;
    char textAt304[8];
    float constantsAt312[4];
    u32 packedValueAt328;
    char textAt332[4];
    s32 idsAt336;
    float constantsAt340[4];
    u32 packedValueAt356;
    char textAt360[8];
    float constantsAt368[4];
    s32 idsAt384;
    char textAt388[4];
    s32 idsAt392;
    float constantsAt396[4];
    u32 packedValueAt412;
    char textAt416[8];
    float constantsAt424[4];
    u32 packedValueAt440;
    char textAt444[4];
    s32 idsAt448;
    float constantsAt452[4];
    u32 packedValueAt468;
    s32 idsAt472[2];
    float constantsAt480[4];
    u32 packedValueAt496;
    char textAt500[8];
    float constantsAt508[4];
    u32 packedValueAt524;
    char textAt528[4];
    s32 idsAt532;
    float constantsAt536[4];
    u32 packedValueAt552;
    char textAt556[8];
    float constantsAt564[4];
    u32 packedValueAt580;
    char textAt584[4];
    s32 idsAt588;
    float constantsAt592[4];
    u32 packedValueAt608;
    char textAt612[8];
    float constantsAt620[4];
    s32 idsAt636;
    char textAt640[4];
    s32 idsAt644;
    float constantsAt648[4];
    u32 packedValueAt664;
    char textAt668[8];
    float constantsAt676[4];
    u32 packedValueAt692;
    char textAt696[4];
    s32 idsAt700;
    float constantsAt704[4];
    u32 packedValueAt720;
    s32 idsAt724[2];
    float constantsAt732[4];
    u32 packedValueAt748;
    char textAt752[4];
} RestfloatRecordWordsEuLayout492;

typedef struct RestGMenuboxcornersLevelTextWords3Layout493 {
    s32 idsAt0[2];
    float constantsAt8;
    char textAt12[24];
    void * referencesAt36[4];
    char textAt52[24];
    void * referencesAt76[4];
    char textAt92[24];
    void * referencesAt116[4];
    char textAt132[24];
    void * referencesAt156[4];
    u32 packedValueAt172;
    u32 packedValueAt176;
    u32 packedValueAt180;
    u32 packedValueAt184;
    u32 packedValueAt188;
    u32 packedValueAt192;
    u32 packedValueAt196;
    u32 packedValueAt200;
    u32 packedValueAt204;
    u32 packedValueAt208;
    u32 packedValueAt212;
    u32 packedValueAt216;
    void * referencesAt220[4];
} RestGMenuboxcornersLevelTextWords3Layout493;

typedef struct RestminusOneSentinelWordsLayout495 {
    s32 idsAt0[3];
    float constantsAt12;
} RestminusOneSentinelWordsLayout495;

typedef struct RestminusOneSentinelWordsLayout496 {
    s32 idsAt0[3];
    u32 packedValueAt12;
} RestminusOneSentinelWordsLayout496;

typedef struct RestD_src_3cb405cbLayout499 {
    s32 idsAt0[2];
    u32 packedCallbackAt8;
    s32 idsAt12[2];
    u32 packedCallbackAt20;
    s32 idsAt24[2];
    u32 packedCallbackAt32;
    s32 idsAt36[2];
    u32 packedCallbackAt44;
    s32 idsAt48[2];
    u32 packedCallbackAt56;
    s32 idsAt60[2];
    u32 packedCallbackAt68;
    s32 idsAt72[5];
    u32 packedCallbackAt92;
    s32 idsAt96[2];
    u32 packedCallbackAt104;
    s32 idsAt108[2];
    u32 packedCallbackAt116;
    s32 idsAt120[2];
    u32 packedCallbackAt128;
    s32 idsAt132[2];
    u32 packedCallbackAt140;
    s32 idsAt144[2];
    u32 packedCallbackAt152;
    s32 idsAt156[3];
} RestD_src_3cb405cbLayout499;

typedef struct RestD_src_3cb405cbLayout500 {
    s32 idsAt0[2];
    void * referencesAt8;
    s32 idsAt12[2];
    void * referencesAt20;
    s32 idsAt24[2];
    void * referencesAt32;
    s32 idsAt36[2];
    void * referencesAt44;
    s32 idsAt48[2];
    void * referencesAt56;
    s32 idsAt60[2];
    void * referencesAt68[4];
    s32 idsAt84[2];
    void * referencesAt92;
    s32 idsAt96[2];
    void * referencesAt104;
    s32 idsAt108[2];
    void * referencesAt116;
    s32 idsAt120[2];
    void * referencesAt128;
    s32 idsAt132[2];
    void * referencesAt140;
    s32 idsAt144[2];
    void * referencesAt152[4];
} RestD_src_3cb405cbLayout500;

typedef struct RestD_src_3cb405cbLayout501 {
    s32 idsAt0[2];
    u32 packedCallbackAt8;
    s32 idsAt12[2];
    u32 packedCallbackAt20;
    s32 idsAt24[2];
    u32 packedCallbackAt32;
    s32 idsAt36[2];
    u32 packedCallbackAt44;
    s32 idsAt48[2];
    u32 packedCallbackAt56;
    s32 idsAt60[2];
    u32 packedCallbackAt68;
    s32 idsAt72[5];
    u32 packedCallbackAt92;
    s32 idsAt96[2];
    u32 packedCallbackAt104;
    s32 idsAt108[2];
    u32 packedCallbackAt116;
    s32 idsAt120[2];
    u32 packedCallbackAt128;
    s32 idsAt132[2];
    u32 packedCallbackAt140;
    s32 idsAt144[2];
    u32 packedCallbackAt152;
    s32 idsAt156[3];
} RestD_src_3cb405cbLayout501;

typedef struct RestMenuCreatesoundoptionsscreenPointerWordsTailUsLayout503 {
    s32 idsAt0[2];
    u32 packedCallbackAt8;
    s32 idsAt12[2];
    u32 packedCallbackAt20;
    s32 idsAt24[2];
    u32 packedCallbackAt32;
    s32 idsAt36[2];
    u32 packedCallbackAt44;
    s32 idsAt48[5];
    u32 packedCallbackAt68;
    s32 idsAt72[2];
    u32 packedCallbackAt80;
    s32 idsAt84[2];
    u32 packedCallbackAt92;
    s32 idsAt96[2];
    u32 packedCallbackAt104;
    s32 idsAt108[2];
    u32 packedCallbackAt116;
    s32 idsAt120[2];
    u32 packedCallbackAt128;
    s32 idsAt132[3];
} RestMenuCreatesoundoptionsscreenPointerWordsTailUsLayout503;

typedef struct RestMenuDispatchsettingscolumneventPointerWords1Layout504 {
    s32 idsAt0[2];
    void * referencesAt8;
    s32 idsAt12[5];
    void * referencesAt32;
    s32 idsAt36[2];
    void * referencesAt44;
    s32 idsAt48[2];
    void * referencesAt56;
    s32 idsAt60[2];
    void * referencesAt68[4];
    s32 idsAt84[2];
    void * referencesAt92;
    s32 idsAt96[2];
    void * referencesAt104;
    s32 idsAt108[2];
    void * referencesAt116;
    s32 idsAt120[2];
    void * referencesAt128;
    s32 idsAt132[2];
    void * referencesAt140;
    s32 idsAt144[2];
    void * referencesAt152[4];
} RestMenuDispatchsettingscolumneventPointerWords1Layout504;

typedef struct RestD_src_846838eaLayout505 {
    s32 idsAt0[2];
    void * referencesAt8;
    s32 idsAt12[2];
    u32 packedCallbackAt20;
    s32 idsAt24[2];
    void * referencesAt32;
    s32 idsAt36[2];
    void * referencesAt44;
    s32 idsAt48[2];
    void * referencesAt56;
    s32 idsAt60[2];
    void * referencesAt68[4];
    s32 idsAt84[2];
    void * referencesAt92;
    s32 idsAt96[2];
    void * referencesAt104;
    s32 idsAt108[2];
    void * referencesAt116;
    s32 idsAt120[2];
    void * referencesAt128;
    s32 idsAt132[2];
    void * referencesAt140;
    s32 idsAt144[2];
    void * referencesAt152[4];
} RestD_src_846838eaLayout505;

typedef struct RestD_src_846838eaLayout506 {
    s32 idsAt0[2];
    u32 packedCallbackAt8;
    s32 idsAt12[2];
    u32 packedCallbackAt20;
    s32 idsAt24[2];
    u32 packedCallbackAt32;
    s32 idsAt36[2];
    u32 packedCallbackAt44;
    s32 idsAt48[2];
    u32 packedCallbackAt56;
    s32 idsAt60[2];
    u32 packedCallbackAt68;
    s32 idsAt72[5];
    u32 packedCallbackAt92;
    s32 idsAt96[2];
    u32 packedCallbackAt104;
    s32 idsAt108[2];
    u32 packedCallbackAt116;
    s32 idsAt120[2];
    u32 packedCallbackAt128;
    s32 idsAt132[2];
    u32 packedCallbackAt140;
    s32 idsAt144[2];
    u32 packedCallbackAt152;
    s32 idsAt156[3];
} RestD_src_846838eaLayout506;

typedef struct RestD_src_638b7747Layout508 {
    s32 idsAt0[2];
    u32 packedCallbackAt8;
    s32 idsAt12[2];
    u32 packedCallbackAt20;
    s32 idsAt24[2];
    u32 packedCallbackAt32;
    s32 idsAt36[2];
    u32 packedCallbackAt44;
    s32 idsAt48[2];
    u32 packedCallbackAt56;
    s32 idsAt60[2];
    u32 packedCallbackAt68;
    s32 idsAt72[2];
    u32 packedCallbackAt80;
    s32 idsAt84[2];
    u32 packedCallbackAt92;
    s32 idsAt96[2];
    u32 packedCallbackAt104;
    s32 idsAt108[5];
    u32 packedCallbackAt128;
    s32 idsAt132[2];
    u32 packedCallbackAt140;
    s32 idsAt144[2];
    u32 packedCallbackAt152;
    s32 idsAt156[2];
    void * referencesAt164;
    s32 idsAt168[2];
    u32 packedCallbackAt176;
    s32 idsAt180[2];
    u32 packedCallbackAt188;
    s32 idsAt192[2];
    u32 packedCallbackAt200;
    s32 idsAt204[2];
    u32 packedCallbackAt212;
    s32 idsAt216[4];
} RestD_src_638b7747Layout508;

typedef struct RestD_src_638b7747Layout509 {
    s32 idsAt0[2];
    void * referencesAt8;
    s32 idsAt12[2];
    void * referencesAt20;
    s32 idsAt24[2];
    void * referencesAt32;
    s32 idsAt36[2];
    void * referencesAt44;
    s32 idsAt48[2];
    void * referencesAt56;
    s32 idsAt60[2];
    void * referencesAt68;
    s32 idsAt72[2];
    void * referencesAt80;
    s32 idsAt84[2];
    void * referencesAt92;
    s32 idsAt96[2];
    void * referencesAt104[4];
    s32 idsAt120[2];
    void * referencesAt128;
    s32 idsAt132[2];
    void * referencesAt140;
    s32 idsAt144[2];
    void * referencesAt152;
    s32 idsAt156[2];
    void * referencesAt164;
    s32 idsAt168[2];
    void * referencesAt176;
    s32 idsAt180[2];
    void * referencesAt188;
    s32 idsAt192[2];
    void * referencesAt200;
    s32 idsAt204[2];
    void * referencesAt212[5];
} RestD_src_638b7747Layout509;

typedef struct RestD_src_638b7747Layout510 {
    s32 idsAt0[57];
    float constantsAt228;
} RestD_src_638b7747Layout510;

typedef struct RestplayerSettingsEventHandlersUsLayout512 {
    s32 idsAt0[51];
    u32 packedValueAt204;
    s32 idsAt208[44];
} RestplayerSettingsEventHandlersUsLayout512;

typedef struct RestAudioDecodeframeEncodedWordsLayout515 {
    s32 idsAt0[4];
    void * referencesAt16[3];
    s32 idsAt28[2];
    void * referencesAt36[2];
    s32 idsAt44[3];
    void * referencesAt56[2];
    s32 idsAt64[3];
    void * referencesAt76;
} RestAudioDecodeframeEncodedWordsLayout515;

typedef struct RestGfxdataEncodedWordsLayout517 {
    void * referencesAt0[2674];
    float constantsAt10696;
    void * referencesAt10700[4];
    float constantsAt10716;
    void * referencesAt10720[4];
    float constantsAt10736;
    void * referencesAt10740[4];
    float constantsAt10756;
    void * referencesAt10760[4];
    float constantsAt10776;
    void * referencesAt10780[4];
    float constantsAt10796;
    void * referencesAt10800[4];
    float constantsAt10816;
    void * referencesAt10820[4];
    float constantsAt10836;
    void * referencesAt10840[4];
    float constantsAt10856;
    void * referencesAt10860[4];
    float constantsAt10876;
    void * referencesAt10880[4];
    float constantsAt10896;
    void * referencesAt10900[4];
    float constantsAt10916;
    void * referencesAt10920[4];
    float constantsAt10936;
    void * referencesAt10940[4];
    float constantsAt10956;
    void * referencesAt10960[4];
    float constantsAt10976;
    void * referencesAt10980[4];
    u32 packedValueAt10996;
    void * referencesAt11000[4];
    u32 packedValueAt11016;
    void * referencesAt11020[4];
    u32 packedValueAt11036;
    void * referencesAt11040[4];
    u32 packedValueAt11056;
    void * referencesAt11060[4];
    u32 packedValueAt11076;
    void * referencesAt11080[4];
    u32 packedValueAt11096;
    void * referencesAt11100[4];
    u32 packedValueAt11116;
    void * referencesAt11120[4];
    u32 packedValueAt11136;
    void * referencesAt11140[4];
    u32 packedValueAt11156;
    void * referencesAt11160[4];
    u32 packedValueAt11176;
    void * referencesAt11180[4];
    u32 packedValueAt11196;
    void * referencesAt11200[4];
    u32 packedValueAt11216;
    void * referencesAt11220[4];
    u32 packedValueAt11236;
    void * referencesAt11240[4];
    u32 packedValueAt11256;
    void * referencesAt11260[4];
    u32 packedValueAt11276;
    void * referencesAt11280[4];
    u32 packedValueAt11296;
    void * referencesAt11300[4];
    u32 packedValueAt11316;
    void * referencesAt11320[4];
    u32 packedValueAt11336;
    void * referencesAt11340[4];
    u32 packedValueAt11356;
    void * referencesAt11360[4];
    float constantsAt11376;
    void * referencesAt11380[4];
    float constantsAt11396;
    void * referencesAt11400[4];
    u32 packedValueAt11416;
    void * referencesAt11420[4];
    u32 packedValueAt11436;
    void * referencesAt11440[4];
    u32 packedValueAt11456;
    void * referencesAt11460[13];
    s32 idsAt11512;
} RestGfxdataEncodedWordsLayout517;

typedef struct RestSmpframeanimDispatcheventEncodedWordsLayout518 {
    s32 idsAt0[2];
    void * referencesAt8;
    s32 idsAt12[2];
    void * referencesAt20[5];
    char textAt40[8];
    s32 idsAt48[2];
    void * referencesAt56;
    s32 idsAt60[2];
    void * referencesAt68[4];
    s32 idsAt84;
    u32 packedValueAt88;
    s32 idsAt92[3];
    void * referencesAt104;
    s32 idsAt108[2];
    void * referencesAt116[4];
    s32 idsAt132;
    u32 packedValueAt136;
    s32 idsAt140[3];
    void * referencesAt152;
    s32 idsAt156[2];
    void * referencesAt164;
    s32 idsAt168[2];
    void * referencesAt176;
    s32 idsAt180[2];
    void * referencesAt188;
    s32 idsAt192[2];
    void * referencesAt200;
    s32 idsAt204[2];
    void * referencesAt212;
    s32 idsAt216[2];
    void * referencesAt224;
    s32 idsAt228[2];
    void * referencesAt236[4];
    char textAt252[4];
    s32 idsAt256[2];
    void * referencesAt264;
    s32 idsAt268[2];
    void * referencesAt276;
    s32 idsAt280[2];
    void * referencesAt288;
    s32 idsAt292[2];
    void * referencesAt300;
    s32 idsAt304[2];
    void * referencesAt312;
    s32 idsAt316[2];
    void * referencesAt324[4];
    s32 idsAt340[5];
    void * referencesAt360;
    s32 idsAt364[2];
    void * referencesAt372;
    s32 idsAt376[2];
    void * referencesAt384;
    s32 idsAt388[2];
    void * referencesAt396[4];
    char textAt412[4];
    s32 idsAt416[2];
    void * referencesAt424;
    s32 idsAt428[2];
    void * referencesAt436;
    s32 idsAt440[2];
    void * referencesAt448;
    s32 idsAt452[2];
    void * referencesAt460;
    s32 idsAt464[2];
    void * referencesAt472;
    s32 idsAt476[2];
    void * referencesAt484;
    s32 idsAt488[2];
    void * referencesAt496;
    s32 idsAt500[2];
    void * referencesAt508[4];
    char textAt524[4];
} RestSmpframeanimDispatcheventEncodedWordsLayout518;

typedef struct RestMaincodeEncodedWordsLayout570 {
    s32 idsAt0[9];
} RestMaincodeEncodedWordsLayout570;

typedef struct RestOvl3EncodedWordsLayout597 {
    s32 idsAt0[3];
} RestOvl3EncodedWordsLayout597;

typedef struct RestkeyboardKeyLabelWordsLayout601 {
    float constantsAt0;
    void * referencesAt4;
    float constantsAt8;
    void * referencesAt12;
    float constantsAt16;
    void * referencesAt20;
    float constantsAt24;
    void * referencesAt28;
    float constantsAt32;
    void * referencesAt36;
    float constantsAt40;
    void * referencesAt44;
    float constantsAt48;
    void * referencesAt52;
    float constantsAt56;
    void * referencesAt60;
    float constantsAt64;
    void * referencesAt68;
    float constantsAt72;
    void * referencesAt76;
    float constantsAt80;
    void * referencesAt84;
    float constantsAt88;
    void * referencesAt92;
    float constantsAt96;
    void * referencesAt100;
    float constantsAt104;
    void * referencesAt108;
    float constantsAt112;
    void * referencesAt116;
    u32 packedValueAt120;
    void * referencesAt124;
    u32 packedValueAt128;
    void * referencesAt132;
    u32 packedValueAt136;
    void * referencesAt140;
    u32 packedValueAt144;
    void * referencesAt148;
    u32 packedValueAt152;
    void * referencesAt156;
    u32 packedValueAt160;
    void * referencesAt164;
    u32 packedValueAt168;
    void * referencesAt172;
    u32 packedValueAt176;
    void * referencesAt180;
    u32 packedValueAt184;
    void * referencesAt188;
    u32 packedValueAt192;
    void * referencesAt196;
    u32 packedValueAt200;
    void * referencesAt204;
    u32 packedValueAt208;
    void * referencesAt212;
    u32 packedValueAt216;
    void * referencesAt220;
    u32 packedValueAt224;
    void * referencesAt228;
    u32 packedValueAt232;
    void * referencesAt236;
    u32 packedValueAt240;
    void * referencesAt244;
    u32 packedValueAt248;
    void * referencesAt252;
    u32 packedValueAt256;
    void * referencesAt260;
    u32 packedValueAt264;
    void * referencesAt268;
    float constantsAt272;
    void * referencesAt276;
    float constantsAt280;
    void * referencesAt284;
    u32 packedValueAt288;
    void * referencesAt292;
    u32 packedValueAt296;
    void * referencesAt300;
    u32 packedValueAt304;
    void * referencesAt308[3];
} RestkeyboardKeyLabelWordsLayout601;

typedef struct RestoverlayOneCFloatConstantWordsLayout634 {
    s32 idsAt0[4];
} RestoverlayOneCFloatConstantWordsLayout634;

typedef struct ResteventHandlerAddressTable_euLayout639 {
    s32 idsAt0[4];
    u32 displayCommandAt16;
    s32 idsAt20;
    u32 displayCommandAt24;
    s32 idsAt28;
    u32 displayCommandAt32;
    s32 idsAt36;
    u32 displayCommandAt40;
    u32 displayCommandAt44;
    u32 displayCommandAt48;
    u32 displayCommandAt52;
    u32 displayCommandAt56;
    s32 idsAt60;
    u32 displayCommandAt64;
    s32 idsAt68;
    u32 displayCommandAt72;
    s32 idsAt76;
    u32 displayCommandAt80;
    s32 idsAt84;
    u32 displayCommandAt88;
    s32 idsAt92;
    u32 displayCommandAt96;
    s32 idsAt100;
    u32 displayCommandAt104;
    s32 idsAt108;
    u32 displayCommandAt112;
    s32 idsAt116;
    u32 displayCommandAt120;
    s32 idsAt124;
    u32 displayCommandAt128;
    s32 idsAt132;
    u32 displayCommandAt136;
    s32 idsAt140;
    u32 displayCommandAt144;
    s32 idsAt148;
    u32 displayCommandAt152;
    s32 idsAt156;
    u32 displayCommandAt160;
    u32 displayCommandAt164;
    u32 displayCommandAt168;
    u32 displayCommandAt172;
    u32 displayCommandAt176;
    s32 idsAt180;
    u32 displayCommandAt184;
    s32 idsAt188;
    u32 displayCommandAt192;
    u32 displayCommandAt196;
    u32 displayCommandAt200;
    u32 displayCommandAt204;
    u32 displayCommandAt208;
    u32 displayCommandAt212;
    u32 displayCommandAt216;
    u32 displayCommandAt220;
    u32 displayCommandAt224;
    u32 displayCommandAt228;
    u32 displayCommandAt232;
    u32 displayCommandAt236;
    u32 displayCommandAt240;
    u32 displayCommandAt244;
    u32 displayCommandAt248;
    u32 displayCommandAt252;
    u32 displayCommandAt256;
    u32 displayCommandAt260;
    u32 displayCommandAt264;
    u32 displayCommandAt268;
    u32 displayCommandAt272;
    s32 idsAt276;
    u32 displayCommandAt280;
    s32 idsAt284;
    u32 displayCommandAt288;
    u32 displayCommandAt292;
    u32 displayCommandAt296;
    u32 displayCommandAt300;
    u32 displayCommandAt304;
    s32 idsAt308;
    u32 displayCommandAt312;
    s32 idsAt316;
    u32 displayCommandAt320;
    u32 displayCommandAt324;
    u32 displayCommandAt328;
    u32 displayCommandAt332;
    u32 displayCommandAt336;
    u32 displayCommandAt340;
    u32 displayCommandAt344;
    u32 displayCommandAt348;
    u32 displayCommandAt352;
    u32 displayCommandAt356;
    u32 displayCommandAt360;
    u32 displayCommandAt364;
    u32 displayCommandAt368;
    u32 displayCommandAt372;
    u32 displayCommandAt376;
    u32 displayCommandAt380;
    u32 displayCommandAt384;
    u32 displayCommandAt388;
    u32 displayCommandAt392;
    u32 displayCommandAt396;
    u32 displayCommandAt400;
    s32 idsAt404;
    u32 displayCommandAt408;
    s32 idsAt412;
    u32 displayCommandAt416;
    u32 displayCommandAt420;
    u32 displayCommandAt424;
    u32 displayCommandAt428;
    u32 displayCommandAt432;
    s32 idsAt436;
    u32 displayCommandAt440;
    s32 idsAt444;
    u32 displayCommandAt448;
    u32 displayCommandAt452;
    u32 displayCommandAt456;
    u32 displayCommandAt460;
    u32 displayCommandAt464;
    u32 displayCommandAt468;
    u32 displayCommandAt472;
    u32 displayCommandAt476;
    u32 displayCommandAt480;
    u32 displayCommandAt484;
    u32 displayCommandAt488;
    u32 displayCommandAt492;
    u32 displayCommandAt496;
    u32 displayCommandAt500;
    u32 displayCommandAt504;
    u32 displayCommandAt508;
    u32 displayCommandAt512;
    u32 displayCommandAt516;
    u32 displayCommandAt520;
    u32 displayCommandAt524;
    u32 displayCommandAt528;
    u32 displayCommandAt532;
    u32 displayCommandAt536;
    u32 displayCommandAt540;
    u32 displayCommandAt544;
    s32 idsAt548;
    u32 displayCommandAt552;
    s32 idsAt556;
    u32 displayCommandAt560;
    s32 idsAt564;
    u32 displayCommandAt568;
    u32 displayCommandAt572;
    u32 displayCommandAt576;
    u32 displayCommandAt580;
    u32 displayCommandAt584;
    s32 idsAt588;
    u32 displayCommandAt592;
    s32 idsAt596;
    u32 displayCommandAt600;
    u32 displayCommandAt604;
    u32 displayCommandAt608;
    u32 displayCommandAt612;
    u32 displayCommandAt616;
    u32 displayCommandAt620;
    u32 displayCommandAt624;
    u32 displayCommandAt628;
    u32 displayCommandAt632;
    u32 displayCommandAt636;
    u32 displayCommandAt640;
    u32 displayCommandAt644;
    u32 displayCommandAt648;
    u32 displayCommandAt652;
    u32 displayCommandAt656;
    u32 displayCommandAt660;
    u32 displayCommandAt664;
    u32 displayCommandAt668;
    u32 displayCommandAt672;
    u32 displayCommandAt676;
    u32 displayCommandAt680;
    u32 displayCommandAt684;
    u32 displayCommandAt688;
    u32 displayCommandAt692;
    u32 displayCommandAt696;
    s32 idsAt700;
    u32 displayCommandAt704;
    s32 idsAt708;
    u32 displayCommandAt712;
    s32 idsAt716;
    u32 displayCommandAt720;
    u32 displayCommandAt724;
    u32 displayCommandAt728;
    u32 displayCommandAt732;
    u32 displayCommandAt736;
    s32 idsAt740;
    u32 displayCommandAt744;
    s32 idsAt748;
    u32 displayCommandAt752;
    u32 displayCommandAt756;
    u32 displayCommandAt760;
    u32 displayCommandAt764;
    u32 displayCommandAt768;
    u32 displayCommandAt772;
    u32 displayCommandAt776;
    u32 displayCommandAt780;
    u32 displayCommandAt784;
    u32 displayCommandAt788;
    u32 displayCommandAt792;
    u32 displayCommandAt796;
    u32 displayCommandAt800;
    u32 displayCommandAt804;
    u32 displayCommandAt808;
    u32 displayCommandAt812;
    u32 displayCommandAt816;
    u32 displayCommandAt820;
    u32 displayCommandAt824;
    u32 displayCommandAt828;
    u32 displayCommandAt832;
    u32 displayCommandAt836;
    u32 displayCommandAt840;
    u32 displayCommandAt844;
    u32 displayCommandAt848;
    s32 idsAt852;
    u32 displayCommandAt856;
    s32 idsAt860;
    u32 displayCommandAt864;
    s32 idsAt868;
    u32 displayCommandAt872;
    s32 idsAt876;
    u32 displayCommandAt880;
    u32 displayCommandAt884;
    u32 displayCommandAt888;
    s32 idsAt892;
    u32 displayCommandAt896;
    s32 idsAt900;
    u32 displayCommandAt904;
    s32 idsAt908;
    u32 displayCommandAt912;
    u32 displayCommandAt916;
    u32 displayCommandAt920;
    s32 idsAt924;
    u32 displayCommandAt928;
    s32 idsAt932;
    u32 displayCommandAt936;
    s32 idsAt940;
    u32 displayCommandAt944;
    s32 idsAt948;
    u32 displayCommandAt952;
    u32 displayCommandAt956;
    u32 displayCommandAt960;
    s32 idsAt964;
    u32 displayCommandAt968;
    s32 idsAt972;
    u32 displayCommandAt976;
    s32 idsAt980;
    u32 displayCommandAt984;
    s32 idsAt988;
    u32 displayCommandAt992;
    s32 idsAt996;
    u32 displayCommandAt1000;
    s32 idsAt1004;
    u32 displayCommandAt1008;
    s32 idsAt1012;
    u32 displayCommandAt1016;
    u32 displayCommandAt1020;
    u32 displayCommandAt1024;
    s32 idsAt1028;
    u32 displayCommandAt1032;
    s32 idsAt1036;
    u32 displayCommandAt1040;
    s32 idsAt1044;
    u32 displayCommandAt1048;
    u32 displayCommandAt1052;
    u32 displayCommandAt1056;
    s32 idsAt1060;
    u32 displayCommandAt1064;
    s32 idsAt1068;
    u32 displayCommandAt1072;
    s32 idsAt1076;
    u32 displayCommandAt1080;
    s32 idsAt1084;
    u32 displayCommandAt1088;
    u32 displayCommandAt1092;
    u32 displayCommandAt1096;
    s32 idsAt1100;
    u32 displayCommandAt1104;
    s32 idsAt1108;
    u32 displayCommandAt1112;
    s32 idsAt1116;
    u32 displayCommandAt1120;
    s32 idsAt1124;
    u32 displayCommandAt1128;
    s32 idsAt1132;
    u32 displayCommandAt1136;
    s32 idsAt1140;
    char textAt1144[8];
    u32 packedCallbackAt1152;
    s32 idsAt1156;
    u32 packedCallbackAt1160;
    s32 idsAt1164;
    u32 packedCallbackAt1168;
    s32 idsAt1172;
    u32 packedCallbackAt1176;
    s32 idsAt1180;
    u32 packedCallbackAt1184;
    s32 idsAt1188;
    u32 packedCallbackAt1192;
    s32 idsAt1196;
    u32 packedCallbackAt1200;
    s32 idsAt1204;
    u32 packedCallbackAt1208;
    s32 idsAt1212;
    u32 packedCallbackAt1216;
    s32 idsAt1220;
    u32 packedCallbackAt1224;
    s32 idsAt1228;
    u32 packedCallbackAt1232;
    s32 idsAt1236;
    u32 packedCallbackAt1240;
    s32 idsAt1244;
    u32 packedCallbackAt1248;
    s32 idsAt1252;
    u32 packedCallbackAt1256;
    s32 idsAt1260;
    u32 packedCallbackAt1264;
    s32 idsAt1268;
    u32 packedCallbackAt1272;
    s32 idsAt1276;
    u32 packedCallbackAt1280;
    s32 idsAt1284;
    u32 packedCallbackAt1288;
    s32 idsAt1292;
    u32 packedCallbackAt1296;
    s32 idsAt1300;
    u32 packedCallbackAt1304;
    s32 idsAt1308;
    u32 packedCallbackAt1312;
    s32 idsAt1316;
    u32 packedCallbackAt1320;
    s32 idsAt1324;
    u32 packedCallbackAt1328;
    s32 idsAt1332;
    u32 packedCallbackAt1336;
    s32 idsAt1340;
    u32 packedCallbackAt1344;
    s32 idsAt1348;
    u32 packedCallbackAt1352;
    s32 idsAt1356;
    u32 packedCallbackAt1360;
    s32 idsAt1364;
    u32 packedCallbackAt1368;
    s32 idsAt1372;
    u32 packedCallbackAt1376;
    s32 idsAt1380;
    u32 packedCallbackAt1384;
    s32 idsAt1388;
    u32 packedCallbackAt1392;
    s32 idsAt1396;
    u32 packedCallbackAt1400;
    s32 idsAt1404;
    u32 packedCallbackAt1408;
    s32 idsAt1412;
    u32 packedCallbackAt1416;
    s32 idsAt1420;
    u32 packedCallbackAt1424;
    s32 idsAt1428;
    u32 packedCallbackAt1432;
    s32 idsAt1436;
    u32 packedCallbackAt1440;
    s32 idsAt1444;
    char textAt1448[28];
    s32 idsAt1476;
    u32 displayCommandAt1480;
    s32 idsAt1484[2];
    u32 displayCommandAt1492;
    u32 displayCommandAt1496;
    u32 displayCommandAt1500;
    s32 idsAt1504;
    char textAt1508[8];
    u32 displayCommandAt1516;
    s32 idsAt1520;
    u32 displayCommandAt1524;
    u32 displayCommandAt1528;
    u32 displayCommandAt1532;
    s32 idsAt1536;
    u32 displayCommandAt1540;
    u32 displayCommandAt1544;
    u32 displayCommandAt1548;
    s32 idsAt1552;
    u32 displayCommandAt1556;
    u32 displayCommandAt1560;
    u32 displayCommandAt1564;
    s32 idsAt1568;
    u32 displayCommandAt1572;
    u32 displayCommandAt1576;
    u32 displayCommandAt1580;
    s32 idsAt1584;
    u32 displayCommandAt1588;
    u32 displayCommandAt1592;
    u32 displayCommandAt1596;
    s32 idsAt1600;
    u32 displayCommandAt1604;
    u32 displayCommandAt1608;
    u32 displayCommandAt1612;
    s32 idsAt1616;
    u32 displayCommandAt1620;
    u32 displayCommandAt1624;
    u32 displayCommandAt1628;
    s32 idsAt1632;
    u32 displayCommandAt1636;
    u32 displayCommandAt1640;
    u32 displayCommandAt1644;
    s32 idsAt1648;
    char textAt1652[8];
    u32 displayCommandAt1660;
    s32 idsAt1664;
    u32 displayCommandAt1668;
    u32 displayCommandAt1672;
    u32 displayCommandAt1676;
    s32 idsAt1680[2];
    u32 displayCommandAt1688;
    s32 idsAt1692[5];
} ResteventHandlerAddressTable_euLayout639;

typedef struct RestSndplayerEncodedWordsLayout640 {
    float constantsAt0[4];
    void * referencesAt16[13];
} RestSndplayerEncodedWordsLayout640;

typedef struct RestOvl1EOvl1ECppRetainedWords24Layout650 {
    s32 idsAt0;
} RestOvl1EOvl1ECppRetainedWords24Layout650;

typedef struct RestOvl1EOvl1ECppRetainedWords17Layout658 {
    s32 idsAt0;
} RestOvl1EOvl1ECppRetainedWords17Layout658;

typedef struct RestOvl1EOvl1ECppRetainedWords15Layout666 {
    s32 idsAt0;
} RestOvl1EOvl1ECppRetainedWords15Layout666;

typedef struct RestOvl1EOvl1ECppRetainedWords25Layout674 {
    s32 idsAt0;
} RestOvl1EOvl1ECppRetainedWords25Layout674;

typedef struct RestOvl1EOvl1ECppRetainedWords30Layout682 {
    s32 idsAt0;
} RestOvl1EOvl1ECppRetainedWords30Layout682;

typedef struct RestOvl1EOvl1ECppRetainedWords18Layout690 {
    s32 idsAt0;
} RestOvl1EOvl1ECppRetainedWords18Layout690;

typedef struct RestOvl1EOvl1ECppRetainedWords22Layout698 {
    s32 idsAt0;
} RestOvl1EOvl1ECppRetainedWords22Layout698;

typedef struct RestOvl1EOvl1ECppRetainedWords27Layout706 {
    s32 idsAt0;
} RestOvl1EOvl1ECppRetainedWords27Layout706;

typedef struct RestcharacterPreviewRecordWordsUsLayout756 {
    void * referencesAt0;
    s32 idsAt4[3];
    float constantsAt16[22];
    s32 idsAt104[2];
    void * referencesAt112;
    s32 idsAt116[3];
    float constantsAt128[22];
    s32 idsAt216[2];
    void * referencesAt224;
    s32 idsAt228[3];
    float constantsAt240[20];
    s32 idsAt320[4];
    void * referencesAt336;
    s32 idsAt340[3];
    float constantsAt352[22];
    s32 idsAt440[2];
    void * referencesAt448;
    s32 idsAt452[3];
    float constantsAt464[22];
    s32 idsAt552[2];
    void * referencesAt560;
    s32 idsAt564[3];
    float constantsAt576[22];
    s32 idsAt664[2];
    void * referencesAt672;
    s32 idsAt676[3];
    float constantsAt688[22];
    s32 idsAt776[2];
    void * referencesAt784;
    s32 idsAt788[3];
    float constantsAt800[22];
    s32 idsAt888[2];
    void * referencesAt896;
    s32 idsAt900[3];
    float constantsAt912[22];
    s32 idsAt1000[2];
    void * referencesAt1008;
    s32 idsAt1012[3];
    float constantsAt1024[22];
    s32 idsAt1112[2];
    void * referencesAt1120;
    s32 idsAt1124[3];
    float constantsAt1136[22];
    s32 idsAt1224[2];
    void * referencesAt1232;
    s32 idsAt1236[3];
    float constantsAt1248[22];
    s32 idsAt1336[2];
    void * referencesAt1344;
    s32 idsAt1348[3];
    float constantsAt1360[22];
    s32 idsAt1448[2];
    void * referencesAt1456;
    s32 idsAt1460[3];
    float constantsAt1472[22];
    s32 idsAt1560[2];
    void * referencesAt1568;
    s32 idsAt1572[3];
    float constantsAt1584[22];
    s32 idsAt1672[2];
    void * referencesAt1680;
    s32 idsAt1684[3];
    float constantsAt1696[22];
    s32 idsAt1784[2];
    void * referencesAt1792;
    s32 idsAt1796[66];
    char textAt2060[8];
} RestcharacterPreviewRecordWordsUsLayout756;

typedef struct RestbossActivTextLayout861 {
    void * referencesAt0[3564];
    float constantsAt14256;
    void * referencesAt14260[4];
    float constantsAt14276;
    void * referencesAt14280[4];
    float constantsAt14296;
    void * referencesAt14300[4];
    float constantsAt14316;
    void * referencesAt14320[4];
    float constantsAt14336;
    void * referencesAt14340[4];
    float constantsAt14356;
    void * referencesAt14360[4];
    float constantsAt14376;
    void * referencesAt14380[4];
    float constantsAt14396;
    void * referencesAt14400[4];
    float constantsAt14416;
    void * referencesAt14420[4];
    float constantsAt14436;
    void * referencesAt14440[4];
    float constantsAt14456;
    void * referencesAt14460[4];
    float constantsAt14476;
    void * referencesAt14480[4];
    float constantsAt14496;
    void * referencesAt14500[4];
    float constantsAt14516;
    void * referencesAt14520[4];
    float constantsAt14536;
    void * referencesAt14540[4];
    u32 packedValueAt14556;
    void * referencesAt14560[4];
    u32 packedValueAt14576;
    void * referencesAt14580[4];
    u32 packedValueAt14596;
    void * referencesAt14600[4];
    u32 packedValueAt14616;
    void * referencesAt14620[4];
    u32 packedValueAt14636;
    void * referencesAt14640[4];
    u32 packedValueAt14656;
    void * referencesAt14660[4];
    u32 packedValueAt14676;
    void * referencesAt14680[4];
    u32 packedValueAt14696;
    void * referencesAt14700[4];
    u32 packedValueAt14716;
    void * referencesAt14720[4];
    u32 packedValueAt14736;
    void * referencesAt14740[4];
    u32 packedValueAt14756;
    void * referencesAt14760[4];
    u32 packedValueAt14776;
    void * referencesAt14780[4];
    u32 packedValueAt14796;
    void * referencesAt14800[4];
    u32 packedValueAt14816;
    void * referencesAt14820[4];
    u32 packedValueAt14836;
    void * referencesAt14840[4];
    u32 packedValueAt14856;
    void * referencesAt14860[4];
    u32 packedValueAt14876;
    void * referencesAt14880[4];
    u32 packedValueAt14896;
    void * referencesAt14900[4];
    u32 packedValueAt14916;
    void * referencesAt14920[4];
    float constantsAt14936;
    void * referencesAt14940[4];
    float constantsAt14956;
    void * referencesAt14960[4];
    u32 packedValueAt14976;
    void * referencesAt14980[4];
    u32 packedValueAt14996;
    void * referencesAt15000[4];
    u32 packedValueAt15016;
    void * referencesAt15020[13];
    char textAt15072[12];
} RestbossActivTextLayout861;

typedef struct RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout866 {
    s32 idsAt0[201];
    void * referencesAt804;
    s32 idsAt808[2];
    void * referencesAt816;
    s32 idsAt820[2];
    void * referencesAt828;
    s32 idsAt832[2];
    void * referencesAt840;
    s32 idsAt844[2];
    void * referencesAt852;
    s32 idsAt856[2];
    void * referencesAt864;
    s32 idsAt868[2];
    void * referencesAt876;
    s32 idsAt880[2];
    void * referencesAt888;
    s32 idsAt892[2];
    void * referencesAt900;
    s32 idsAt904[2];
    void * referencesAt912;
    s32 idsAt916[2];
    void * referencesAt924;
    s32 idsAt928[2];
    void * referencesAt936[4];
    s32 idsAt952[40];
} RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout866;

typedef struct RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout867 {
    s32 idsAt0[201];
    void * referencesAt804;
    s32 idsAt808[2];
    void * referencesAt816;
    s32 idsAt820[2];
    void * referencesAt828;
    s32 idsAt832[2];
    void * referencesAt840;
    s32 idsAt844[2];
    void * referencesAt852;
    s32 idsAt856[2];
    void * referencesAt864;
    s32 idsAt868[2];
    void * referencesAt876;
    s32 idsAt880[2];
    void * referencesAt888;
    s32 idsAt892[2];
    void * referencesAt900;
    s32 idsAt904[2];
    void * referencesAt912;
    s32 idsAt916[2];
    void * referencesAt924;
    s32 idsAt928[2];
    void * referencesAt936[4];
    s32 idsAt952[40];
} RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout867;

typedef struct RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout868 {
    s32 idsAt0[201];
    void * referencesAt804;
    s32 idsAt808[2];
    void * referencesAt816;
    s32 idsAt820[2];
    void * referencesAt828;
    s32 idsAt832[2];
    void * referencesAt840;
    s32 idsAt844[2];
    void * referencesAt852;
    s32 idsAt856[2];
    void * referencesAt864;
    s32 idsAt868[2];
    void * referencesAt876;
    s32 idsAt880[2];
    void * referencesAt888;
    s32 idsAt892[2];
    void * referencesAt900;
    s32 idsAt904[2];
    void * referencesAt912;
    s32 idsAt916[2];
    void * referencesAt924;
    s32 idsAt928[2];
    void * referencesAt936[4];
    s32 idsAt952[40];
} RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout868;

typedef struct RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout869 {
    s32 idsAt0[201];
    void * referencesAt804;
    s32 idsAt808[2];
    void * referencesAt816;
    s32 idsAt820[2];
    void * referencesAt828;
    s32 idsAt832[2];
    void * referencesAt840;
    s32 idsAt844[2];
    void * referencesAt852;
    s32 idsAt856[2];
    void * referencesAt864;
    s32 idsAt868[2];
    void * referencesAt876;
    s32 idsAt880[2];
    void * referencesAt888;
    s32 idsAt892[2];
    void * referencesAt900;
    s32 idsAt904[2];
    void * referencesAt912;
    s32 idsAt916[2];
    void * referencesAt924;
    s32 idsAt928[2];
    void * referencesAt936[4];
    s32 idsAt952[40];
} RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout869;

typedef struct RestsmpWidgetEventHandlerRecordsAndTailsUsLayout870 {
    s32 idsAt0[2];
    void * referencesAt8;
    s32 idsAt12[2];
    void * referencesAt20[4];
    s32 idsAt36;
    void * referencesAt40;
    s32 idsAt44[3];
    void * referencesAt56;
    s32 idsAt60[2];
    void * referencesAt68[4];
    s32 idsAt84;
    void * referencesAt88;
    s32 idsAt92[3];
    void * referencesAt104;
    s32 idsAt108[2];
    void * referencesAt116[4];
    s32 idsAt132;
    void * referencesAt136;
    s32 idsAt140[3];
    void * referencesAt152;
    s32 idsAt156[2];
    void * referencesAt164;
    s32 idsAt168[2];
    void * referencesAt176;
    s32 idsAt180[2];
    void * referencesAt188;
    s32 idsAt192[2];
    void * referencesAt200;
    s32 idsAt204[2];
    void * referencesAt212;
    s32 idsAt216[2];
    void * referencesAt224;
    s32 idsAt228[2];
    void * referencesAt236[4];
    s32 idsAt252[3];
    void * referencesAt264;
    s32 idsAt268[2];
    void * referencesAt276;
    s32 idsAt280[2];
    void * referencesAt288;
    s32 idsAt292[2];
    void * referencesAt300;
    s32 idsAt304[2];
    void * referencesAt312;
    s32 idsAt316[2];
    void * referencesAt324[4];
    s32 idsAt340;
    void * referencesAt344;
    s32 idsAt348[3];
    void * referencesAt360;
    s32 idsAt364[2];
    void * referencesAt372;
    s32 idsAt376[2];
    void * referencesAt384;
    s32 idsAt388[2];
    void * referencesAt396[4];
    s32 idsAt412[3];
    void * referencesAt424;
    s32 idsAt428[2];
    void * referencesAt436;
    s32 idsAt440[2];
    void * referencesAt448;
    s32 idsAt452[2];
    void * referencesAt460;
    s32 idsAt464[2];
    void * referencesAt472;
    s32 idsAt476[2];
    void * referencesAt484;
    s32 idsAt488[2];
    void * referencesAt496;
    s32 idsAt500[2];
    void * referencesAt508[4];
    s32 idsAt524;
} RestsmpWidgetEventHandlerRecordsAndTailsUsLayout870;

typedef struct RestTrackDrawtrackoverlayEncodedWordsBlock1Layout871 {
    float constantsAt0[3];
} RestTrackDrawtrackoverlayEncodedWordsBlock1Layout871;

typedef struct RestsmpControllerStateAndEventWordsLayout872 {
    s32 idsAt0[17];
    float constantsAt68[2];
    s32 idsAt76[2];
    void * referencesAt84;
    s32 idsAt88;
} RestsmpControllerStateAndEventWordsLayout872;

typedef struct RestsmpControllerStateAndEventWordsLayout873 {
    s32 idsAt0[17];
    u32 packedValueAt68;
    u32 packedValueAt72;
    s32 idsAt76;
    float constantsAt80;
    u32 packedValueAt84;
    u32 packedValueAt88;
} RestsmpControllerStateAndEventWordsLayout873;

typedef struct RestsmpControllerStateAndEventWordsLayout874 {
    s32 idsAt0[23];
} RestsmpControllerStateAndEventWordsLayout874;

typedef struct RestsmpControllerStateAndEventWordsLayout875 {
    s32 idsAt0[17];
    char textAt68[4];
    u32 packedValueAt72;
    s32 idsAt76[2];
    u32 packedValueAt84;
    char textAt88[4];
} RestsmpControllerStateAndEventWordsLayout875;

typedef struct RestsmpControllerStateAndEventWordsLayout876 {
    s32 idsAt0[23];
} RestsmpControllerStateAndEventWordsLayout876;

typedef struct RestsmpControllerEventRecordTailsUsRev1Layout878 {
    s32 idsAt0[5];
    void * referencesAt20;
    s32 idsAt24[2];
    void * referencesAt32[4];
    s32 idsAt48[5];
    void * referencesAt68;
    s32 idsAt72[2];
    void * referencesAt80[5];
    s32 idsAt100[2];
} RestsmpControllerEventRecordTailsUsRev1Layout878;

typedef struct RestsmpEventHandlerTablesLayout880 {
    s32 idsAt0[132];
} RestsmpEventHandlerTablesLayout880;

typedef struct RestsmpEventHandlerTablesLayout881 {
    s32 idsAt0[2];
    void * referencesAt8;
    s32 idsAt12[2];
    void * referencesAt20[4];
    float constantsAt36;
    u32 packedValueAt40;
    u32 packedValueAt44;
    s32 idsAt48[2];
    void * referencesAt56;
    s32 idsAt60[2];
    void * referencesAt68[5];
    u32 packedValueAt88;
    u32 packedValueAt92;
    s32 idsAt96[2];
    void * referencesAt104;
    s32 idsAt108[2];
    void * referencesAt116[4];
    u32 packedValueAt132;
    u32 packedValueAt136;
    u32 packedValueAt140;
    s32 idsAt144[2];
    void * referencesAt152;
    s32 idsAt156[2];
    void * referencesAt164;
    s32 idsAt168[2];
    void * referencesAt176;
    s32 idsAt180[2];
    void * referencesAt188;
    s32 idsAt192[2];
    void * referencesAt200;
    s32 idsAt204[2];
    void * referencesAt212;
    s32 idsAt216[2];
    void * referencesAt224;
    s32 idsAt228[2];
    void * referencesAt236[4];
    float constantsAt252;
    s32 idsAt256[2];
    void * referencesAt264;
    s32 idsAt268[2];
    void * referencesAt276;
    s32 idsAt280[2];
    void * referencesAt288;
    s32 idsAt292[2];
    void * referencesAt300;
    s32 idsAt304[2];
    void * referencesAt312;
    s32 idsAt316[2];
    void * referencesAt324[4];
    u32 packedValueAt340;
    float constantsAt344;
    u32 packedValueAt348;
    s32 idsAt352[2];
    void * referencesAt360;
    s32 idsAt364[2];
    void * referencesAt372;
    s32 idsAt376[2];
    void * referencesAt384;
    s32 idsAt388[2];
    void * referencesAt396[4];
    u32 packedValueAt412;
    s32 idsAt416[2];
    void * referencesAt424;
    s32 idsAt428[2];
    void * referencesAt436;
    s32 idsAt440[2];
    void * referencesAt448;
    s32 idsAt452[2];
    void * referencesAt460;
    s32 idsAt464[2];
    void * referencesAt472;
    s32 idsAt476[2];
    void * referencesAt484;
    s32 idsAt488[2];
    void * referencesAt496;
    s32 idsAt500[2];
    void * referencesAt508[4];
    u32 packedValueAt524;
} RestsmpEventHandlerTablesLayout881;

typedef struct RestOvltab6EncodedWordsBlock1Layout900 {
    s32 idsAt0[7];
    float constantsAt28;
    void * referencesAt32[8];
} RestOvltab6EncodedWordsBlock1Layout900;

typedef struct RestTrigConstantPool3 { s32 zero; s32 precision[2]; double one; } __attribute__((packed)) RestTrigConstantPool3;

typedef struct RestDecimalPowersPool5 { u32 prefix[2]; double powers[9]; char tail[8]; } RestDecimalPowersPool5;

typedef struct RestOvlgameInitializeplayerpoolEncodedWordsRecord391 {
    s32 state;
} RestOvlgameInitializeplayerpoolEncodedWordsRecord391;

typedef struct RestOvlgameInitializeplayerpoolEncodedWordsBlock1Record392 {
    s32 state;
} RestOvlgameInitializeplayerpoolEncodedWordsBlock1Record392;

typedef struct RestOvlgameInitializeplayerpoolEncodedWordsBlock2Record393 {
    s32 state;
} RestOvlgameInitializeplayerpoolEncodedWordsBlock2Record393;

typedef struct RestplayerMovementProfileFourStateFlagUsRev1Record394 {
    s32 state[2];
} RestplayerMovementProfileFourStateFlagUsRev1Record394;

typedef struct RestplayerControllerStateIdThirteenUsRev1Record397 {
    s32 state;
} RestplayerControllerStateIdThirteenUsRev1Record397;

typedef struct RestplayerControllerStateEndUsRev1Record399 {
    s32 endState;
} RestplayerControllerStateEndUsRev1Record399;

typedef struct RestLinkerAlignmentFill2 {
    u8 linkerAlignmentFill[2];
} RestLinkerAlignmentFill2;

typedef struct RestDecimalPowersPool621 { u32 prefix[2]; double powers[9]; char tail[8]; } RestDecimalPowersPool621;

typedef struct RestTrigConstantPool624 { s32 zero; s32 precision[2]; double one; } __attribute__((packed)) RestTrigConstantPool624;

typedef struct RestTrigConstantPool790 { float unsignedBias; float frameRate; u32 zero; double one; } __attribute__((packed)) RestTrigConstantPool790;

typedef struct RestDecimalPowersPool793 { u32 prefix[2]; double powers[9]; char tail[8]; } RestDecimalPowersPool793;

typedef struct RestOvldat10EncodedWordsBlock17AfterLayout603 {
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
} RestOvldat10EncodedWordsBlock17AfterLayout603;

typedef struct RestOvldat10EncodedWordsBlock17MidLayout604 {
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
} RestOvldat10EncodedWordsBlock17MidLayout604;

typedef struct RestOvldat10EncodedWordsBlock14RestLayout605 {
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
} RestOvldat10EncodedWordsBlock14RestLayout605;

typedef struct RestOvldat10EncodedWordsBlock3Layout607 {
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
} RestOvldat10EncodedWordsBlock3Layout607;

typedef struct RestOvldat10EncodedWordsBlock4Layout609 {
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
} RestOvldat10EncodedWordsBlock4Layout609;

typedef struct RestOvldat10EncodedWordsBlock8Layout610 {
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
} RestOvldat10EncodedWordsBlock8Layout610;

typedef struct RestOvldat10EncodedWordsBlock17Layout611 {
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
} RestOvldat10EncodedWordsBlock17Layout611;

typedef struct RestplayerEffectLightPatternWordsLayout269 {
    s16 lightPatterns[16];
    s32 characterAndHudModelIds[20];
    s32 hudMoverScripts[165];
    float rideAndJumpParameters[17];
} RestplayerEffectLightPatternWordsLayout269;
#endif
