#include "COMMON/SCREEN.H"
#include "COMMON/NAME.H"
#include "FRONTEND/PAKMENU.H"
#include "TYPES.H"
#include "FRONTEND/PAKINTERFACE_FINDREADYTRANSFERPLAYER.H"

extern void PAKInterface_RefreshPlayerPanel(s32 player);

/* Dispatch player-slot events using the current shared menu controller and
 * its measured 0xB68-byte player records. */
s32 Frontend_HandlePakProfileInput(s32 a,s32 b,u32 event,s32 key){
    s32 index=event&65535;
    if((event>>16)==3){
        switch(g_pakProfileScreenState->phase){
            case 6:
            if(key==10){
                s32 state;
                state=g_pakProfileScreenState->players[index].state;
                if(state==4){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].back=2;
                    g_pakProfileScreenState->players[index].state=2;
                    g_pakProfileScreenState->players[index].next=state;
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 4:
            switch(key){
                case 11:
                case 13:
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].back=2;
                    g_pakProfileScreenState->players[index].state=2;
                    g_pakProfileScreenState->players[index].next=4;
                    PAKInterface_RefreshPlayerPanel(index);
                }
                break;
                case 10:
                {
                    s32 state;
                    state=g_pakProfileScreenState->players[index].state;
                    if(state==4){
                        MarkMenuEventHandled();
                        g_pakProfileScreenState->players[index].back=2;
                        g_pakProfileScreenState->players[index].state=2;
                        g_pakProfileScreenState->players[index].next=state;
                        PAKInterface_RefreshPlayerPanel(index);
                    }
                    break;
                }
            }
            break;
            case 0:
            if(key==11||key==13){
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].back=2;
                    g_pakProfileScreenState->players[index].state=2;
                    g_pakProfileScreenState->players[index].next=12;
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 3:
            if(key==11||key==13){
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].back=2;
                    g_pakProfileScreenState->players[index].state=2;
                    g_pakProfileScreenState->players[index].next=13;
                    g_pakProfileScreenState->players[index].sub=5;
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 1:
            if(key==11||key==13){
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].state=14;
                    if(PAKInterface_FindReadyTransferPlayer()>=0){
                        g_pakProfileScreenState->players[index].back=2;
                        g_pakProfileScreenState->players[index].state=2;
                        g_pakProfileScreenState->players[index].next=13;
                        g_pakProfileScreenState->players[index].sub=6;
                    }
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 2:
            if(key==11||key==13){
                if(g_pakProfileScreenState->players[index].state==0){
                    MarkMenuEventHandled();
                    g_pakProfileScreenState->players[index].state=14;
                    if(PAKInterface_FindReadyTransferPlayer()>=0){
                        g_pakProfileScreenState->players[index].back=2;
                        g_pakProfileScreenState->players[index].state=2;
                        g_pakProfileScreenState->players[index].next=13;
                        g_pakProfileScreenState->players[index].sub=3;
                    }
                    PAKInterface_RefreshPlayerPanel(index);
                }
            }
            break;
            case 5:
            case 7:
            break;
        }
    }
    return 0;
}
