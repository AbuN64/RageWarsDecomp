#ifndef COMMON_WIDGET_TEXTURE_RETENTION_H
#define COMMON_WIDGET_TEXTURE_RETENTION_H
#include "types.h"
#include "Common/runtime_declarations.h"
extern void Node_InitializeResourceState(void);

struct WidgetTextureRetentionView;
typedef struct WidgetTextureRetentionView WidgetTextureRetentionView;

extern s16 Node_GetResourceLanguageCount(void);


extern void Node_ReleaseUnretainedTextureEntries(void);

extern void Node_ClearResourceInitializationFlag(void);


extern short Node_GetFontVerticalOffset(int index);

extern int Node_ReturnOne(void);



extern int Node_ReturnConstantOne(void);

extern void Node_AcquireAllResourceTextures(void);



extern short Node_GetFontLineHeight(int index);

struct ManagerFrontendReleaseAllChunkImages;
typedef struct ManagerFrontendReleaseAllChunkImages ManagerFrontendReleaseAllChunkImages;

extern void Node_LoadLanguageStringsIfAny(s32);

extern short Node_GetFontBitmapCount(int index);

extern int Node_ReturnUnitValue(void);

extern signed char Node_GetFontCharacterPhysicalWidth(int entry, int index);

extern short g_frontendResourceLanguageCount;


extern short Node_GetFontLetterSpacing(int index);

struct ManagerFrontendReleaseAllChunkImages;
struct ManagerFrontendReleaseAllChunkImages {
    short count;
    char pad2[0x32];
    int mode;
};

extern signed char Node_GetFontCharacterHeight(int entry, int index);

struct WidgetTextureRetentionView;
struct WidgetTextureRetentionView {
    char pad0[4];
    struct WidgetTextureRetentionView *next;
    struct WidgetTextureRetentionView *child;
    char padC[2];
    u16 type;
    char pad10[0x1C];
    struct WidgetTextureRetentionView *normal;
    struct WidgetTextureRetentionView *highlighted;
    struct WidgetTextureRetentionView *pressed;
};

#endif
