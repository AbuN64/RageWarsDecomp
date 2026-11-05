#ifndef ENGINE_LISTS_H
#define ENGINE_LISTS_H
#include "Common/small_records.h"
#include "Lists/externs.h"
#include "Common/runtime_declarations.h"
#include "Common/listheader.h"
#include "types.h"



struct ListNodeNextView {
    char pad[0x4];
    void * value;
};
typedef struct ListNodeNextView ListNodeNextView;

struct ListPreviousLinkView {
    void * previous;
};
typedef struct ListPreviousLinkView ListPreviousLinkView;

struct WeightedTable;
struct ListLinkHeader;
struct ListLink;
struct Lists18;
extern void Lists_MoveNodeToActiveList(struct Lists18 *list, struct ListLink *node);
extern int Lists_Remove(struct ListLinkHeader *listHeader, struct ListLink *listLink);
extern s32 Lists_Append(struct ListLinkHeader *list, struct ListLink *node);
extern struct ListLink *Lists_MoveHeadToInactiveList(struct Lists18 *lists);
extern s32 Lists_AppendWeightedEntry(struct WeightedTable *table, s16 value, s16 weight);
extern s16 Lists_ChooseWeightedTableEntry(struct WeightedTable *weightedTable);
#endif
