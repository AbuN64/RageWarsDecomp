#ifndef COMMON_SHARED_DEBUGFIELD_H
#define COMMON_SHARED_DEBUGFIELD_H
#include "Common/shared_menuselection.h"
#include "types.h"
struct Shared_DebugField;
typedef struct Shared_DebugField Shared_DebugField;
struct Shared_DebugField {
    char *name;
    u32 type;
    u32 unknown08[3];
    f32 scale;
    void *(*get)(void);
};
typedef struct Shared_DebugWidget Shared_DebugWidget;
struct PlayerRankInner;
struct Shared_DebugWidget {
    u32 unknown00;
    s16 type;
    u16 unknown06;
    u32 unknown08[3];
    union {
        struct Shared_DebugField *field;
        char **text;
    };
    struct PlayerRankInner *inner;
};





extern struct Shared_DebugField *g_profileSelectionResources[];
#endif
