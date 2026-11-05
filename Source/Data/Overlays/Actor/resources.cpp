#include "types.h"
#include "include_asm.h"
#include "Engine/link.h"

/* ALCSEQSECTOTICKS_DATA.CPP */
#if defined(VERSION_DE)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif
#if defined(VERSION_EU)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif
#if defined(VERSION_EU_X)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif
#if defined(VERSION_US)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif
#if defined(VERSION_US_REV1)
const f32 k_AlcseqsectoticksEncodedWords[3] = {
    30.0f, 0.0f, 2.14748365e+09f
};
#endif

#if defined(VERSION_US)
struct {
    u8 retainedFrameTagWords[12];
} k_alcseqsectoticksFragment __attribute__((aligned(4))) = {
    { 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x43, 0x46, 0x72, 0x61, 0x6D }
};
#endif

#if defined(VERSION_EU_X)
struct {
    u8 retainedRecordWords[12];
} k_alcseqsectoticksFragment __attribute__((aligned(4))) = {
    { 0x00, 0x27, 0x91, 0xAC, 0x00, 0x27, 0x91, 0xEC, 0x00, 0x27, 0x90, 0xF0 }
};
#endif

#if defined(VERSION_EU)
struct {
    u8 retainedRecordWords[12];
} k_alcseqsectoticksFragment __attribute__((aligned(4))) = {
    { 0x00, 0x22, 0x9E, 0xD8, 0x00, 0x22, 0x9E, 0xE0, 0x00, 0x22, 0x9E, 0xE8 }
};
#endif

#if defined(VERSION_DE)
char s_AlcseqsectoticksAudioCsplayText[12] =
    "audio/csplay";
#endif

/* S_TESTERSTEXT.CPP */
#if defined(VERSION_US_REV1)
char s_testersText[44] __attribute__((aligned(1))) = "                                   TESTERS\000\000";
#endif

/* G_PROJECTLEADQACREDITSTEXTPOOL.CPP */
#if defined(VERSION_US_REV1)
char g_projectLeadQaCreditsTextPool[1052] = "RUSS BREWER\000PROJECT LEAD\000\000\000\000TODD DOWD\000\000\000QA MANAGER\000\000                           AUSTIN QA\000\000\000\000JOHN HENKE\000\000MARC SCHAEFGEN\000\000DARREN MITCHELL\000                           SOUND DESIGN\000BEY BICKERTON\000\000\000DAVID DIENSTBIER\000\000\000\000                       ADDITIONAL DESIGN\000\000\000\000BRIAN WATSON\000\000\000\000DAVID SMITH\000ANDY ONEIL\000\000STEVAN HIRD\000STEVE BROUMLEY\000\000                   ADDITIONAL PROGRAMMING\000\000\000DIGITAL IMAGING GROUP\000\000\000RYAN TRACY\000\000ALEX OMLANSKY\000\000\000PETER FRANCO\000\000\000\000SCOTT BROCKER\000\000\000                         ADDITIONAL ART\000ROB WHITAKER - DIGITAL PRODUCTIONS\000\000ROBERT WILSHER - DIGITAL PRODUCTIONS\000\000\000\000JEFF SHELTON - DESIGN\000\000\000ROBBIE MILLER - DIGITAL PRODUCTIONS\000PAUL MASTERS - PROGRAMMING\000\000BRAD MARQUES - DIGITAL PRODUCTIONS\000\000MARC MACKIN - DIGITAL PRODUCTIONS\000\000\000TREVOR LEMOINE - DIGITAL PRODUCTIONS\000\000\000\000MATT KYLE - PROGRAMMING\000MICHAEL HUEY - DESIGN\000\000\000NEILL GLANCY - DESIGN\000\000\000MICHAEL FONG - DIGITAL PRODUCTIONS\000\000JIM COWLISHAW - PROGRAMMING\000BRUCE COONER - PROGRAMMING\000\000JASON BEHR - DESIGN\000MICHAEL DAUBERT\000LEAD ARTIST\000FRANCISCO JAVIER LAFUENTE\000\000\000LEAD PROGRAMMER\000MARK PACINI\000PROJECT MANAGER";
#endif

/* S_RAGEWARSTEAMTEXT.CPP */
#if defined(VERSION_US_REV1)
char s_rageWarsTeamText[42] = "                           RAGE WARS TEAM";
#endif

/* G_RESOURCESENCODEDHALFWORDS.CPP */
#if defined(VERSION_US_REV1)
unsigned short g_ResourcesEncodedHalfwords[1] = {
    0x43D8,
};
#endif

/* G_OVERLAYTHREEUNITYVECTOR.CPP */
#if defined(VERSION_US_REV1)
struct {
    u8 retainedRecordWords[12];
} g_actorUnitYVector __attribute__((aligned(4))) = {
    { 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};
#endif

/* G_LINKPLAYTRIGGERSOUNDCALLBACKCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_linkPlayTriggerSoundCallbackCallbacks[3] = {
    (void *)&Link_PlayTriggerSoundCallback, (void *)&Link_PlayTriggerSound, (void *)&Link_DispatchTriggerAudio
};
#endif
