#ifndef MENU_MENU_EVENT_HANDLERS_H
#define MENU_MENU_EVENT_HANDLERS_H
#include "types.h"

struct PakActionLabelView;
struct PakOperationLabelItem;
struct FrameSequence;

/* Menu callbacks that resident menu tables refer to by code address. */
s32 CMenuProfile_ProfileModeReturnZero(void);
s32 Character_CreateSelectionMenuGerman(void *screen);
s32 Menu_SelectPakOperationActionLabel(struct PakOperationLabelItem *labelItem);
s32 Pak_OpenMusicPreviewMenu(void *first, void *second, void *third);
s32 Pak_SelectPromptTextGroupThree(struct PakActionLabelView *field);
s32 SmpFrameAnim_UpdateFrameSequence(struct FrameSequence *sequence, s32 eventId, s32 elapsed);
s32 Timer_UpdateAlternateActionLabel(struct PakActionLabelView *field);
s32 Timer_UpdatePreviewKindLabel(struct PakActionLabelView *field);
typedef struct PakActionLabelView {
    char pad[0x14];
    char *text;
} PakActionLabelView;

#endif
