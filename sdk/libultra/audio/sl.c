#include "../../include/libgultra.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJRECAT18V1.H"
#include "TYPES.H"
#include "../../include/libgultra/alunlink.h"
#include "../../include/al_globals.h"

void alUnlink(ALLink *node) {
    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    }
}

void alLink(ALLink *node, ALLink *previousNode) {
    ALLink *temp;

    temp = previousNode->next;
    node->prev = previousNode;
    node->next = temp;
    temp = previousNode->next;
    if (temp != 0) {
        temp->prev = node;
    }
    previousNode->next = node;
}



void alInit(ALGlobals *audioGlobals, ALSynConfig *config) {
    void **p;

    p = (void **)&g_audioGlobals;
    if (*p == 0) {
        *p = audioGlobals;
        alSynNew(&audioGlobals->drvr, config);
    }
}


void alClose(ALGlobals *audioGlobals) {
    void **p;

    p = (void **)&g_audioGlobals;
    if (*p != 0) {
        alSynDelete(audioGlobals);
        *p = 0;
    }
}
