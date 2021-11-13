#pragma once
#include "vec3.h"
#include "Offsets.h"
#include "globals.h"
#include <vector>

class Ent
{

public:
	//Vars
	int GetHealth();
	int GetTeam();
	int GetLifeState();
	vec3 GetVecOrigin();
	vec3 GetVecVeloctiy();
	int GetCrosshairId();
	int GetWeaponIndex();
	bool Dormant();
	int ShotsFired();
	int GlowIndex();
	bool IsDefusing();
	bool IsSpotted();
	//Functions
	bool IsAlive();
	void ParseEnt(std::vector<Ent>* vec);
};

class LocalPlayer : public Ent {
public:
	//Functions
	void ForceAttack(int delay);
};

bool FillEnts(std::vector<Ent>* vec, uintptr_t* entity) {
	for (int i = 0; i < MAXPLAYERS) {

	}
}