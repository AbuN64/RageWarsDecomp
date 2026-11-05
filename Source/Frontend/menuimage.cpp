#include "include_asm.h"
#include "Frontend/results_player_panels.h"
#include "types.h"
#include "Frontend/menuimage.h"
#include "Render/soundelement_playflatsound.h"

/* unit MENUIMAGE.CPP */
/* Clears the step, frame and state of a menu image, then stores the first value through
   Frontend_SetMenuImageResource and the next three through Frontend_SetMenuImageColor. */
void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth) {
    ((MenuImageState *)record)->step = 0;
    ((MenuImageState *)record)->frame = 0;
    ((MenuImageState *)record)->state = 0;
    Frontend_SetMenuImageResource(record, first);
    Frontend_SetMenuImageColor(record, second, third, fourth);
}

/* Sets a menu image's step to one, frame to zero and state to one, then calls
   SoundElement_PlayFlatSound with 0xE83. */
void Frontend_StartMenuImageTransition(s32 *record) {
    ((MenuImageState *)record)->step = 1;
    ((MenuImageState *)record)->frame = 0;
    ((MenuImageState *)record)->state = 1;
    SoundElement_PlayFlatSound(3715);
}

/* Advances the transition frame by the step; once the frame reaches 13 both are cleared and the
   state becomes 2. */
void Frontend_AdvanceMenuImageTransition(s32 *record) {
    ((MenuImageState *)record)->frame += ((MenuImageState *)record)->step;
    if (((MenuImageState *)record)->frame >= 13) {
        ((MenuImageState *)record)->frame = 0;
        ((MenuImageState *)record)->step = 0;
        ((MenuImageState *)record)->state = 2;
    }
}

/* Returns the frame field of the record. */
s32 Frontend_GetMenuImageFrame(s32 *record) {
    return ((MenuImageState *)record)->frame;
}

/* Returns whether the menu image state equals 2, the transition-complete state. */
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

/* Returns the state field of the record. */
s32 Frontend_GetMenuImageState(s32 *record) {
    return ((MenuImageState *)record)->state;
}
