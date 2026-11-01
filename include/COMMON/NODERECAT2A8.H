#ifndef COMMON_NODERECAT2A8_H
#define COMMON_NODERECAT2A8_H
#include "TYPES.H"
#include "COMMON/PAK_MENU.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/TEXTLAYERMETRICS.H"

extern int g_geometryTexturePerspectiveOverride;

extern int g_frontendViDitherFilterEnabled;

struct Shared_PakMenu;


struct Shared_PakMenu;


struct FrontendScreenViewport;
typedef struct FrontendScreenViewport FrontendScreenViewport;

struct PakCancelActionView;
typedef struct PakCancelActionView PakCancelActionView;

struct FrontendVideoModeParameters;
struct FrontendVideoModeParameters {
    int width;
    int viewportHeight;
    int offsetX;
    int offsetY;
    int borderX;
    int borderY;
    int reservedWord;
};

extern int g_frontendVideoModeCounts[];


struct FrontendVideoDimensions;
struct FrontendVideoDimensions {
    int width;
    int height;
    int rest[5];
};

extern int g_geometryTextureFilterOverride;

struct Shared_PakMenu;

struct FrontendScreenViewport;
struct FrontendScreenViewport {
    int unused;
    struct FrontendScreenViewport *next;
    char pad[0x294];
    float width;
    float height;
    int x;
    int y;
};

struct PakCancelActionView;
struct PakCancelActionView {
    char a[28];
    ActorOwnerView *player;
    s32 controller;
    s32 dialogList;
};


extern int g_frontendStartupState;

struct Shared_PakMenu;


struct FrontendVideoDimensions;
typedef struct FrontendVideoDimensions FrontendVideoDimensions;





struct Shared_PakMenu;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Pak_FormatOperationChannelLabel(struct LayeredText *field, struct Shared_PakMenu *holder);
#endif
#endif
