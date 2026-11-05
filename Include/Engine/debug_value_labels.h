#ifndef ENGINE_DEBUG_VALUE_LABELS_H
#define ENGINE_DEBUG_VALUE_LABELS_H

/* us-rev1 debug menu value labels: the title text address, the editable value text, then the address of that text. */
typedef struct DebugFieldOfViewLabel {
    unsigned int titleTextPointer;
    unsigned char fieldOfViewText[20];
    unsigned int fieldOfViewTextPointer;
} DebugFieldOfViewLabel;
typedef struct DebugColorLabel {
    unsigned int titleTextPointer;
    unsigned char redText[16];
    unsigned int redTextPointer;
} DebugColorLabel;

extern struct DebugFieldOfViewLabel g_debugFieldOfViewLabel;
extern struct DebugColorLabel g_debugAmbientColorLabel;
extern struct DebugColorLabel g_debugDirectionalColorLabel;

#endif
