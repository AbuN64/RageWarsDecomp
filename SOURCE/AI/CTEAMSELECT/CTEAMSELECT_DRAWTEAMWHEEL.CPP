#include "COMMON/SHAREDPLAYER.H"
#include "MENU/TEAMMENU.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

/* Lays out the four team choices around the open menu and draws their icons. */





extern f32 Graphu64_ApproachValue(f32, f32, f32);
extern void Graphu64_IdentityMatrix(Matrix *);
extern void RollMatrix(Matrix *, f32);
extern void Cteamselect_DrawTeamIcons(MenuCteamselectDrawTeamWheel *, TeamMenuIconView *, s32, void *);

void Cteamselect_DrawTeamWheel(MenuCteamselectDrawTeamWheel *menu, s32 unused1, void *player) {
    Matrix matrix;
    CVector3 position;
    TeamMenuIconView items[4];
    CVector3 offset;
    s32 i;
    TeamMenuSlotView *slot;
    TeamMenuIconView *item;
    f32 target;

    if (menu->active != 0) {
        offset.x = 0.0f;
        item = items;
        offset.y = -0.6f - (0.4f - menu->open * 0.4f);
        offset.z = 0.0f;
        for (i = 0; i < 4; i++) {
            slot = &menu->slots[i];
            if (i == menu->cursor) {
                target = *(&g_teamWheelScalePoolPrefix + 1) * 1.3f;
            } else {
                target = *(&g_teamWheelScalePoolPrefix + 1);
            }
            slot->scale = Graphu64_ApproachValue(slot->scale, target, *(&g_teamWheelScalePoolPrefix + 1) * 0.1f);
            Graphu64_IdentityMatrix(&matrix);
            RollMatrix(&matrix, slot->angle);
            Graphu64_TransformPoint(&matrix, &offset, &position);
            item->slot = i;
            item->position = position;
            item->icon = i + 3100;
            item->width = 1.0f;
            item->height = 1.0f;
            item++;
        }
        Cteamselect_DrawTeamIcons(menu, items, 4, player);
    }
}
