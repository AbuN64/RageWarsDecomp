#ifndef MENU_PAK_PROMPT_LINES_H
#define MENU_PAK_PROMPT_LINES_H

/* Controller pak prompt line cells: one row per prompt kind (rows in ROM order), five lines per row,
   one text pointer per language in each cell. */
#if defined(VERSION_EU)
#define PAK_PROMPT_LINE_LANGUAGES 4
#elif defined(VERSION_EU_X)
#define PAK_PROMPT_LINE_LANGUAGES 3
#else
#define PAK_PROMPT_LINE_LANGUAGES 1
#endif
enum PakPromptRow {
    PAK_PROMPT_ROW_DEFAULT,
    PAK_PROMPT_ROW_KIND1,
    PAK_PROMPT_ROW_KIND2,
    PAK_PROMPT_ROW_KIND4,
    PAK_PROMPT_ROW_KIND3,
    PAK_PROMPT_ROW_KIND5,
    PAK_PROMPT_ROW_KIND6,
    PAK_PROMPT_ROW_KIND7,
    PAK_PROMPT_ROW_KIND8,
    PAK_PROMPT_ROW_KIND9,
    PAK_PROMPT_ROW_KIND10,
    PAK_PROMPT_ROW_KIND11,
    PAK_PROMPT_ROW_KIND12,
    PAK_PROMPT_ROW_KIND13,
    PAK_PROMPT_ROW_KIND14,
    PAK_PROMPT_ROW_KIND15,
    PAK_PROMPT_ROW_COUNT
};
extern char g_pakPromptLineCells[PAK_PROMPT_ROW_COUNT][5][PAK_PROMPT_LINE_LANGUAGES * 4];

#endif
