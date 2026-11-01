#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "MENU/MENU_REQUESTOPTIONSSCREEN22.H"

/* Calls Tsmos_DeactivateControllerState and then SmXlate_SwitchScreen with 0x16. */
extern void Tsmos_DeactivateControllerState(void);
extern void SmXlate_SwitchScreen(int);

void Menu_RequestOptionsScreen22(void) {
    Tsmos_DeactivateControllerState();
    SmXlate_SwitchScreen(22);
}
