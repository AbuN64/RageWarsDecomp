#ifndef MENU_BUILD_DEFINITION_DATA_H
#define MENU_BUILD_DEFINITION_DATA_H

/* ROM menu records consumed by Menu_InitializeMenu through the cartridge window.
 * Keep halfwords and color bytes at their load widths; callback words retain
 * the relocations of their paged entry points. Both records are 0x24 bytes. */
struct MenuBuildItemData {
    short type;
    unsigned short reserved02;
    unsigned int flags;
    short x;
    short y;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    int resource;
    unsigned int resourceCallback;
    unsigned int callback;
    unsigned int initializeCallback;
    unsigned int parameter;
};

struct MenuBuildDefinitionData {
    unsigned int items;
    short count;
    unsigned short reserved06;
    unsigned int initializeCallback;
    unsigned int callback1;
    unsigned int callback2;
    unsigned int callback3;
    short x;
    short y;
    short kind;
    unsigned short reserved1E;
    int value;
};

/* Twelve paged cheat records: Encoded_ApplyCheatCode reads code, flags and sound;
   the result widget reads the label at the second word of each record. */
struct MenuCheatCodeData {
    unsigned int code;
    unsigned int label;
    unsigned int flags;
    unsigned int sound;
};

#endif
