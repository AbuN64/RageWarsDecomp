#include "include_asm.h"

#include "FRONTEND/ENTRYRECAT4D4.H"
#include "TYPES.H"
#include "FRONTEND/MENUIMAGE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Clears the words at offsets 0x10 to 0x18 of a record, then stores the first value through
   Frontend_SetMenuImageResource and the next three through Frontend_SetMenuImageColor. */

void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth) {
    ((MenuImageState *)record)->step = 0;
    ((MenuImageState *)record)->frame = 0;
    ((MenuImageState *)record)->state = 0;
    Frontend_SetMenuImageResource(record, first);
    Frontend_SetMenuImageColor(record, second, third, fourth);
}

/* Sets the words at offsets 0x10, 0x14 and 0x18 of a record to one, zero and one, then calls
   SoundElement_PlayFlatSound with 0xE83. */

void Frontend_StartMenuImageTransition(s32 *record) {
    ((MenuImageState *)record)->step = 1;
    ((MenuImageState *)record)->frame = 0;
    ((MenuImageState *)record)->state = 1;
    SoundElement_PlayFlatSound(3715);
}

/* Advances the counter at offset 0x14 of a record by the step at 0x10; once it reaches 0xD both
   are cleared and the state word at 0x18 becomes 2. */
void Frontend_AdvanceMenuImageTransition(s32 *record) {
    ((MenuImageState *)record)->frame += ((MenuImageState *)record)->step;
    if (((MenuImageState *)record)->frame >= 13) {
        ((MenuImageState *)record)->frame = 0;
        ((MenuImageState *)record)->step = 0;
        ((MenuImageState *)record)->state = 2;
    }
}

/* Returns the word at offset 0x14 of a record. */
s32 Frontend_GetMenuImageFrame(s32 *record) {
    return ((MenuImageState *)record)->frame;
}

/* Returns whether the word at offset 0x18 of a record equals 2; Frontend_GetMenuImageState returns that word. */
s32 Frontend_IsMenuImageTransitionComplete(s32 *record) {
    return ((MenuImageState *)record)->state == 2;
}

/* Stores a value into the first word of a record; Frontend_SetMenuImageColor, which follows it, fills the
   words after it. */
void Frontend_SetMenuImageResource(s32 *record, s32 value) {
    ((MenuImageState *)record)->resource = value;
}

/* Stores three values into words 1 to 3 of a record; Frontend_SetMenuImageResource stores word 0. */
void Frontend_SetMenuImageColor(s32 *record, s32 first, s32 second, s32 third) {
    ((MenuImageState *)record)->color[0] = first;
    ((MenuImageState *)record)->color[1] = second;
    ((MenuImageState *)record)->color[2] = third;
}

/* Returns the word at offset 0x18 of a record. */
s32 Frontend_GetMenuImageState(s32 *record) {
    return ((MenuImageState *)record)->state;
}
