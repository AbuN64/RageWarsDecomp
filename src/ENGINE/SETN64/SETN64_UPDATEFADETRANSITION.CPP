#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "include_asm.h"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/VIDEO_DIMENSIONS.H"
#include "ENGINE/SETN64.H"
#include "RENDER/SETN64_UPDATEFADETRANSITION.H"
#include "../../../sdk/include/AUDIO/sprintf.H"

extern void SetN64_DrawColorRectangle(void *unused, s8 *color, s32 left, s32 top,
                          s32 right, s32 bottom);


s32 SetN64_StartGameThreadAndIdle(s32 *, s32);

#include "COMMON/GAME_SESSION.H"










void SetN64_DrawSessionFade(struct GameSession *session) {
    s8 color[4];
    f32 value;
    s32 alpha;

    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    value = session->timer;
    alpha = 0xFF;
    if (!(value < 0)) {
        alpha = 0;
        if (!((&g_systemTimeFrameRate)[1] < value)) {
            alpha = 0xFF;
            if (!(value < 0)) {
                alpha = ~(s32)(value * g_sessionFadeAlphaScale);
            }
        }
    }
    color[3] = alpha;
    SetN64_DrawColorRectangle(session, color, 0, 0, SCREEN_WD, SCREEN_HT);
}

/* Compares two byte strings lexicographically, returning -1 for either null pointer. */
int SetN64_CompareByteStrings(u8 *a, u8 *b) {
 if (!a || !b) return -1;
 while (*a && *b) {
  if (*a < *b) return -1;
  if (*a > *b) return 1;
  a++; b++;
 }
 if (*a) return 1;
 if (*b) return -1;
 return 0;
}

u8 *SetN64_CopyString(u8 *destination, u8 *source)
{
  u8 *readCursor;
  u8 *writeCursor;
  u8 firstByte;
  u8 copiedByte;
 do { firstByte = *source; readCursor = source + 1; } while (0);
  *destination = firstByte;
  writeCursor = destination - -1;
  if (firstByte & 0xFF)
  {
    do
    {
      copiedByte = *readCursor;
      readCursor += 1;
      *writeCursor = copiedByte;
      writeCursor += 1;
    }
    while (copiedByte & 0xFF);
  }
  return destination;
}

int SetN64_IsModeThirteen(void) {
    return g_gameSession.mode == 13;
}

void SetN64_RunBootstrapThread(s32 threadArgument) {
    SetN64_StartGameThreadAndIdle(&g_gameSession, threadArgument);
}

void SetN64_RunGameThread(void) {
    Libc_FormatString(g_buildVersionTextBuffer, g_buildVersionFormat, g_buildDateTimeTextRev1, g_buildVersionSuffix);
    __osSetFpcCsr(__osGetFpcCsr() | 0x400);
    SetN64_RunGameLoop(&g_gameSession);
}

/** Reset three large-offset fields and mark the record active. */
void SetN64_BeginSessionFadeIn(void *gameSession) {
    struct GameSession *session = gameSession;
    session->phase = 1;
    session->timer = 0;
    session->fastFade = 0;
}

/* Steps the session's screen fade by the frame time g_frameElapsedTime (fastFade picks the fast rate). Phase 2 fades out: the
 * timer falls to zero, then keeps counting below it until -4 before the session switches to mode 0x14 and fades back
 * in. Phase 1 fades in, at least half the rate per frame, until the timer reaches one. */
void SetN64_UpdateFadeTransition(GameSession *session) {
    f32 step;
    f32 rate;
    f32 timer;
    f32 next;

    if (session->phase == 0) {
        return;
    }
    step = 0.1f;
    if (session->fastFade != 0) {
        step = 0.5f;
    }
    rate = step;
    switch (session->phase) {
    case 2:
        timer = session->timer;
        if (timer > 0.0f) {
            step = g_frameElapsedTime;
            next = timer - rate * step;
            session->timer = next;
            if (next < 0.0f) {
                session->timer = 0.0f;
            }
        } else {
            session->timer = timer - 1.0f;
        }
        if (session->timer < -4.0f) {
            s32 saved = session->mode;
            session->mode = 20;
            session->timer = 0.0f;
            session->phase = 1;
            session->previousMode = saved;
        }
        break;
    case 1:
        timer = session->timer;
        if (g_frameElapsedTime < 0.5f) {
            next = timer + step * 0.5f;
        } else {
            next = timer + step * g_frameElapsedTime;
        }
        session->timer = next;
        if (next >= 1.0f) {
            session->phase = 0;
            session->timer = 1.0f;
            session->fastFade = 0;
        }
        break;
    }
}
