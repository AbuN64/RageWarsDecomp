#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/TRIPLE.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

void Playerai_DrawAmmoCounters(PowerHudPlayer *player, Shared_HudView *view) {
    f32 sx,sy,numberScale,offset,halfWidth,x,y;
    sx=view->width/(f32)g_hudReferenceViewportWidth;
    sy=view->height/(f32)g_hudReferenceViewportHeight;
    if (Frontend_GetScreenMode()==0) {
        numberScale=g_playerAmmoNumberScaleStandard;
        offset=g_playerAmmoNumberOffsetStandard;
    } else {
        numberScale=g_playerAmmoNumberScaleAlternate;
        offset=g_playerAmmoNumberOffsetAlternate;
    }
    halfWidth=sx*g_playerAmmoIconHalfWidth;
    if(player->first!=player->a.last || player->refreshA) {
        if(Frontend_GetScreenMode()==0) OnScreen_StartMoverScript(&player->a,g_playerAmmoFirstMoverScript);
        else OnScreen_StartMoverScript(&player->a,g_playerAmmoFirstMoverScript+12);
        player->refreshA=0;
        player->a.last=player->first;
    }
    if(player->second!=player->b.last || player->refreshB) {
        if(Frontend_GetScreenMode()==0) OnScreen_StartMoverScript(&player->b,g_playerAmmoSecondMoverScript-12);
        else OnScreen_StartMoverScript(&player->b,g_playerAmmoSecondMoverScript);
        player->refreshB=0;
        player->b.last=player->second;
    }
    if(player->third!=player->c.last || player->refreshC) {
        if(Frontend_GetScreenMode()==0) OnScreen_StartMoverScript(&player->c,g_playerAmmoThirdMoverScriptStandard);
        else OnScreen_StartMoverScript(&player->c,g_playerAmmoThirdMoverScriptAlternate);
        player->refreshC=0;
        player->c.last=player->third;
    }
    if(Playerai_GetSelectedAmmoIcon(player)!=-1) {
        if(player->a.object && player->a.state && player->weapon<18) {
            x=player->a.x*sx+view->x;
            y=player->a.y*sy+view->y+view->height;
            x+=offset;
            OnScreen_DrawSpriteResource(3050,0,(s16)(x-halfWidth),(s16)(y-sy*g_playerAmmoFirstIconYOffset),sx,sy,1);
            x-=sx*g_playerAmmoFirstNumberXOffset;
            y-=sy*g_playerAmmoFirstNumberYOffset;
            OnScreen_DrawSpriteNumber(player->first,x,y,sx*numberScale,sy,1,0,0);
        }
        if(player->b.object && player->b.state && player->weapon<18) {
            x=player->b.x*sx+view->x;
            y=player->b.y*sy+view->y+view->height;
            x+=offset;
            OnScreen_DrawSpriteResource(3051,0,(s16)(x-halfWidth),(s16)(y-sy*g_playerAmmoSecondIconYOffset),sx,sy,1);
            x-=sx*g_playerAmmoSecondNumberXOffset;
            y-=sy*g_playerAmmoSecondNumberYOffset;
            OnScreen_DrawSpriteNumber(player->second,x,y,sx*numberScale,sy,1,0,0);
        }
        if(player->c.object && player->c.state && player->weapon<18) {
            x=player->c.x*sx+view->x;
            y=player->c.y*sy+view->y+view->height;
            x+=offset;
            OnScreen_DrawSpriteResource(3052,0,(s16)(x-halfWidth),(s16)(y-sy*g_playerAmmoThirdIconYOffset),sx,sy,1);
            x-=sx*g_playerAmmoThirdNumberXOffset;
            y-=sy*g_playerAmmoThirdNumberYOffset;
            OnScreen_DrawSpriteNumber(player->third,x,y,sx*numberScale,sy,1,0,0);
        }
    }
}
