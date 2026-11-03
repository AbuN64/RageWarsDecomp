#ifndef OVLGAME_HUD_H
#define OVLGAME_HUD_H
struct ActorWorld;
void Hud_InitializeWorldActorPools(struct ActorWorld *world);
struct HudTables;
void Hud_ResetHudCharTables(struct HudTables *hud);
struct PanelMovers;
void Hud_StartPanelMovers(struct PanelMovers *panel);
#endif
