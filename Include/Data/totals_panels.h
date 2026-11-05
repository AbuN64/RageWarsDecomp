#ifndef DATA_TOTALS_PANELS_H
#define DATA_TOTALS_PANELS_H

/* One player's totals panel: the four placing rows, then tags, frags, deaths and suicides, each "<label>:0000". */
typedef struct TotalsPanelWide {
    char one[32];
    char two[32];
    char three[32];
    char four[32];
    char tags[32];
    char frags[32];
    char deaths[32];
    char suicides[16];
} TotalsPanelWide;

/* The later panels keep the placing rows wide and pack tags, frags, deaths and suicides into 16 bytes each. */
typedef struct TotalsPanel {
    char one[32];
    char two[32];
    char three[32];
    char four[32];
    char tags[16];
    char frags[16];
    char deaths[16];
    char suicides[16];
} TotalsPanel;

/* The four players' totals panels that follow a "totals" title. */
typedef struct TotalsPanels {
    TotalsPanelWide first;
    TotalsPanel rest[3];
} TotalsPanels;

/* The German build's totals panel: every row 16 bytes. */
typedef struct TotalsPanelDe {
    char eins[16];
    char zwei[16];
    char drei[16];
    char vier[16];
    char tags[16];
    char frags[16];
    char erledigt[16];
    char tschuess[16];
} TotalsPanelDe;

/* The French totals panel in the eu build: every row 16 bytes. */
typedef struct TotalsPanelFr {
    char un[16];
    char deux[16];
    char trois[16];
    char quatre[16];
    char marques[16];
    char victimes[16];
    char morts[16];
    char suicides[16];
} TotalsPanelFr;

#endif
