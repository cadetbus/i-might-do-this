#pragma once

#include "Ent.h"
#include "Offsets.h"
#include "vec3.h"

constexpr auto SemiAuto = 0;
constexpr auto attack = 5;
constexpr auto stopAttack = 4;


static DWORD client = (DWORD)GetModuleHandle(L"client.dll");

inline bool IsEnemy(Ent* ent) {
	LocalPlayer* localEnt = *(LocalPlayer**)(client + hazedumper::signatures::dwLocalPlayer);
	if (ent->GetTeam() != localEnt->GetTeam()) {
		return true;
	}
	return false;
}

inline int SetDelay(const vec3& localOrigin, const vec3& EnemyOrigin, const int& weaponIndex) {
	float distance = localOrigin.Distance(EnemyOrigin);

	float scale = 0;
	switch (weaponIndex) {
	case 1:
		break;
	default:
		scale = 1;
	}

	float delay = static_cast<float>(distance * scale);
	return static_cast<int>(delay);
}

void RunTriggerBot() {
	LocalPlayer* localEnt = *reinterpret_cast<LocalPlayer**>(client + hazedumper::signatures::dwLocalPlayer);

	int health = localEnt->GetHealth();

	//if(!Engine->InGame())
	if (!localEnt->IsAlive()) // && !localEnt->IsNotDefusing())
		return;
	int delay = 50;
	int weaponIndex = localEnt->GetWeaponIndex();
	//if (weaponIndex == SemiAuto) {}

	int crosshairId = localEnt->GetCrosshairId();
	if (crosshairId > 0 && crosshairId < 64) {
		Ent* ent = *reinterpret_cast<Ent**>(client + hazedumper::signatures::dwEntityList + (crosshairId - 1) * 0x10);
		if (ent->IsAlive() && !ent->Dormant() && IsEnemy(ent)) {
			int delay = SetDelay(localEnt->GetVecOrigin(), ent->GetVecOrigin(), weaponIndex);
			localEnt->ForceAttack(delay);
		}
	}
}
	//do something

