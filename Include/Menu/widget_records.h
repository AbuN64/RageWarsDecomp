#ifndef MENU_WIDGET_RECORDS_H
#define MENU_WIDGET_RECORDS_H
#include "types.h"
#include "Common/vector.h"

struct Args {
    u32 words[10];
};

typedef struct Args Args;

struct Header44 {
    s32 words[11];
};

typedef struct Header44 Header44;

struct InstanceHdr {
    union {
        s32 w[5];
        struct { s32 header[2]; CVector3 position; } spatial;
    };
};

typedef struct InstanceHdr InstanceHdr;

struct QuadN64EngDrawNumericWidgetChildren {
    u32 x;
    u32 y;
    u32 z;
    u32 w;
};

typedef struct QuadN64EngDrawNumericWidgetChildren QuadN64EngDrawNumericWidgetChildren;

struct WidgetFlagsView {
    unsigned char padding_0[16];
    unsigned char alpha;
};

struct WidgetLabelTextView {
    char pad0[0x38];
    void * text;
};

typedef struct WidgetLabelTextView WidgetLabelTextView;

struct ObjRecAt40V1 {
    char p[64];
    s32 value;
};

typedef struct ObjRecAt40V1 ObjRecAt40V1;

#endif
