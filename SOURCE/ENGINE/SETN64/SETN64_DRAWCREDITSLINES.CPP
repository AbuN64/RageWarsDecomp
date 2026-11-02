#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJRECAT20V1.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "TYPES.H"

/* Draws the scrolling text lines from the current line index, fading each in with alpha sixteen times its distance below the top edge (capped at 255) and spacing lines ten 222ths of the screen height apart until past the bottom; the top edge is a zero-valued local, which keeps 0.0f in one saved register as the cartridge does. */





extern void OnScreen_DrawTextWithShadow(char *, f32, f32, f32, f32, s32, s32, s32);



void SetN64_DrawCreditsLines(void) {
    s32 line;
    f32 y;
    char *text;
    f32 fade;
    s32 alpha;
    f32 top;

    top = 0.0f;
    line = g_creditsCurrentLine;
    y = g_creditsScrollPosition;
    OnScreen_SetupTextRendering();
    OnScreen_LoadTextTileModeTwo();
    OnScreen_SetTextScale(1.0f, 1.0f);
    do {
        #if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = g_creditsLocalizedLines[g_gameSettings.language][line];
#else
        text = g_creditsLocalizedLines[0][line];
#endif
        if (text != 0) {
            fade = top;
            if (!(y < top)) {
                if (!(16.0f < y)) {
                    if (!(y < top)) {
                        fade = y * 16.0f;
                    }
                } else {
                    fade = 256.0f;
                }
            }
            if (fade > 255.0f) {
                fade = 255.0f;
            }
            alpha = fade;
            OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, alpha, alpha, alpha);
            if (y >= top) {
                OnScreen_DrawTextWithShadow(text, (f32)(g_hudReferenceViewportWidth * 14 / 284), (f32)(s32)y,
                              g_hudReferenceViewportWidth * 0.0028169013f, g_hudReferenceViewportHeight * 0.0045045046f, 1, alpha,
                              g_creditsTextDrawingEnabled);
            }
            line++;
        }
        y += g_hudReferenceViewportHeight * 0.045045048f;
    } while (y <= g_hudReferenceViewportHeight);
}
