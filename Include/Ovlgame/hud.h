#ifndef OVLGAME_HUD_H
#define OVLGAME_HUD_H
struct ActorWorld;
struct RibbonWorld;
void Hud_InitializeWorldActorPools(struct RibbonWorld *world);
struct HudTables;
struct Hud;
void Hud_ResetHudCharTables(struct Hud *hud);
struct PanelMovers;
struct Hud;
void Hud_StartPanelMovers(struct Hud *panel);
#endif
