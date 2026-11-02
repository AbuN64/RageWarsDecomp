#include "COMMON/GROUP.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/TRACK_REQUESTTRACKBYKEY.H"
#include "COMMON/OBJRECAT4V6.H"

void CCinema_DrawMessages(void)
{
  f32 messageScaleY;
  f32 screenScaleX;
  int unusedMessageIndex;
  f32 messageLineAdvance;
  f32 followingMessageScale;
  f32 messageDrawScale;
  f32 resolutionScale;
  f32 messageScaleX;
  s32 messageIndex;
  s32 messageY;
  s32 firstMessageIndex;
  s32 screenHeight;
  void *sequenceContext;
  if ((g_cinemaSequenceState->messageCount) > 0)
  {
    s32 messageLineHeight;
    s32 messageCenterX;
    messageLineHeight = 26;
    messageCenterX = g_hudReferenceViewportWidth / 2;
    OnScreen_SetupTextRendering();
    screenScaleX = (f32) (g_hudReferenceViewportWidth / 284);
    messageScaleY = (f32) (g_hudReferenceViewportHeight / 222);
    screenHeight = g_hudReferenceViewportHeight;
    if (screenHeight >= 223)
    {
      messageY = 180;
      resolutionScale = g_cinemaHighResolutionMessageScale;
      messageScaleX = screenScaleX * resolutionScale;
      messageScaleY *= resolutionScale;
    }
    else
    {
      messageY = 110;
      resolutionScale = g_cinemaLowResolutionMessageScale;
      messageScaleX = screenScaleX * resolutionScale;
      messageScaleY *= resolutionScale;
    }
    firstMessageIndex = 0;
    OnScreen_SetTextScale(messageScaleX, messageScaleY);
    sequenceContext = g_cinemaSequenceState;
    g_tutorialStatusBars.shadowX = 1;
    g_tutorialStatusBars.shadowY = 1;
    messageIndex = firstMessageIndex;
    if ((((Shared_MenuContext *)(sequenceContext))->messageCount) > firstMessageIndex)
    {
      unusedMessageIndex = 0;
      messageDrawScale = g_cinemaFirstMessageScale;
      followingMessageScale = g_cinemaFollowingMessageScale;
      do
      {
        Onscrn_DrawText(((Shared_MenuContext *)sequenceContext)->messages[messageIndex], messageCenterX, messageY, 0xFF, 1, 1, messageDrawScale, messageDrawScale);
        messageLineAdvance = ((f32) messageLineHeight) * messageScaleY;
        screenScaleX = (f32) (g_hudReferenceViewportWidth / 284);
        messageScaleY = ((f32) (g_hudReferenceViewportHeight / 222)) * followingMessageScale;
        messageY = (s32) (((f32) messageY) + messageLineAdvance);
        OnScreen_SetTextScale(screenScaleX * followingMessageScale, messageScaleY);
        messageIndex += 1;
      }
      while (messageIndex < ((Shared_MenuContext *)(sequenceContext = g_cinemaSequenceState))->messageCount);
    }
  }
}

s32 CCinema_RequestTrackWithCallbacks(s32 requestId, ContextCallback requestContextCallback, VoidCallback completionCallback) {
    s32 result;

    result = Track_RequestTrackByKey(requestId);
    if (g_cinemaSequenceState->requestE0 == requestId) {
        g_cinemaSequenceState->callbackE4 = requestContextCallback;
        g_cinemaSequenceState->callbackE8 = completionCallback;
    } else {
        if (requestContextCallback != 0) {
            requestContextCallback(g_cinemaSequenceState);
        }
        if (completionCallback != 0) {
            completionCallback();
        }
    }
    return result;
}
