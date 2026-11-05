#ifndef WEAPON_WEAPON_H
#define WEAPON_WEAPON_H
struct WeaponFireState;
int Weapon_GetIndexedTableValue(int tableIndex);
struct Player;
extern void Weapon_InitializeChargeAndLoopSound(struct Player *actorView, struct WeaponFireState *fireState);
#endif
