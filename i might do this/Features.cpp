#include "pch.h"
#include "Features.h"

void TriggerBot() {
    uintptr_t localPlayer = *(uintptr_t*)(modules::clientModule + hazedumper::signatures::dwLocalPlayer);
    
}

void NoRecoil() {
    uintptr_t localPlayer = *(uintptr_t*)(modules::clientModule + hazedumper::signatures::dwLocalPlayer);
    vec3* viewAngles = (vec3*)(*(uintptr_t*)(modules::engineModule + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_ViewAngles);
    int* iShotsFired = (int*)(localPlayer + hazedumper::netvars::m_iShotsFired);
    vec3* aimPunchAngle = (vec3*)(localPlayer + hazedumper::netvars::m_aimPunchAngle);
    vec3 oPunch{ 0,0,0 };
    vec3 punchAngle = *aimPunchAngle * 2;
    if (*iShotsFired > 1) {
        vec3 newAngle = *viewAngles = oPunch - punchAngle;
        newAngle.Normalize();
        *viewAngles = newAngle;
    }
    oPunch = punchAngle;
}