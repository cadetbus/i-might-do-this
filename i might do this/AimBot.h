#pragma once
#include "ent.h"
#include "vec3.h"


void GetTarget();
void AimAt(LocalPlayer* local, Ent* target) {
	vec3 localOrigin = local->GetVecOrigin();
	vec3 targetOrigin = target->GetVecOrigin();
}
