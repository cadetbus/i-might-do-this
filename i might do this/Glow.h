#pragma once
#include "Ent.h"
#include "vec3.h"
#include "globals.h"
#include "Offsets.h"
#include "icliententitylist.h"

struct GlowEntry
{
	int32_t m_nNextFreeSlot; //0x0000
	uint32_t pEntity; //0x0004
	float R; //0x0008
	float G; //0x000C
	float B; //0x0010
	float A; //0x0014
	char pad_0018[4]; //0x0018
	float flUnk; //0x001C
	float flBloom; //0x0020
	float localplayeriszeropoint3; //0x0024
	bool m_bRenderWhenOccluded; //0x0028
	bool m_bRenderWhenUnoccluded; //0x0029
	bool m_bFullBloomRender; //0x002A
	char pad_002B[1]; //0x002B
	int32_t m_nFullBloomStencilTestValue; //0x002C
	int32_t iUnk; //0x0030
	int32_t m_nSplitScreenSlot; //0x0034
	void ParseGlow(Vec4 glow) {
		this->R = glow.r;
		this->G = glow.g;
		this->B = glow.b;
		this->A = glow.a;
	}
}; //Size: 0x0038

inline void SetGlowColor(Vec4& glow,Ent* entity,int health) {
	glow.r = health * -0.01f + 1;
	glow.g = health * 0.01f;

	if (entity->IsDefusing()) {
		glow.r = 2.0f;
		glow.a = 1.4f;
	}
	if (entity->IsSpotted()) {
		glow.r = health * -0.01f + 1.5f;
		glow.a = 1.2f;
	}
}

inline void TeamGlow(Ent* entity, GlowEntry* glowObj) {
	Vec4 glow{0.0f,1.0f,0.0f,1.0f};
	SetGlowColor(glow,entity, entity->GetHealth());
	glowObj->ParseGlow(glow);

}

inline void EnemyGlow(Ent* entity, GlowEntry* glowObj) {
	Vec4 glow{ 0.0f,2.0f,0.0f,1.0f };
	SetGlowColor(glow,entity, entity->GetHealth());
	glowObj->ParseGlow(glow);
}

inline bool IsTeam(Ent* entity) {

	LocalPlayer* localPlayer = *reinterpret_cast<LocalPlayer**>(modules::clientModule + hazedumper::signatures::dwLocalPlayer);
	int entityTeam = reinterpret_cast<int>(entity + entity->GetTeam());
	return localPlayer->GetTeam() == entity->GetTeam() ? true : false;
}


void RunGlow() {
	DWORD clientModule = (DWORD)GetModuleHandle(L"client.dll");
	uintptr_t local = clientModule + hazedumper::signatures::dwLocalPlayer;
	uintptr_t pglowObjectManager = *(uintptr_t*)(clientModule + hazedumper::signatures::dwGlowObjectManager);

	std::vector<Ent>* ents;

	if (local != NULL && pglowObjectManager != NULL) {
		for (int i = 0; i < MAXPLAYERS; ++i) {
			Ent* entity = *reinterpret_cast<Ent**>(clientModule + hazedumper::signatures::dwEntityList + i * 0x10);
			if (entity == nullptr) { continue; }
			GlowEntry* glowObj = reinterpret_cast<GlowEntry*>(pglowObjectManager + (entity->GlowIndex() * 0x38));
			IsTeam(entity) ? TeamGlow(entity, glowObj) : EnemyGlow(entity, glowObj);
			glowObj->m_bRenderWhenOccluded = true;
			glowObj->m_bRenderWhenUnoccluded = false;
		}
	}
}