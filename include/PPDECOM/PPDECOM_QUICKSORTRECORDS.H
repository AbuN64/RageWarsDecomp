#ifndef PPDECOM_PPDECOM_QUICKSORTRECORDS_H
#define PPDECOM_PPDECOM_QUICKSORTRECORDS_H
void PpDecom_QuickSortRecords(char *base, u32 num, u32 width, s32 (*compare)(char *, char *), void (*swap)(char *, char *));
#endif
