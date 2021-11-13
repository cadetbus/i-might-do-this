#include "pch.h"
#include "Ent.h"

int Ent::GetHealth()
{
    return *reinterpret_cast<int*>(this + hazedumper::netvars::m_iHealth);
}

int Ent::GetTeam()
{
    return *reinterpret_cast<int*>(this + hazedumper::netvars::m_iTeamNum);
}

int Ent::GetLifeState()
{
    return *reinterpret_cast<int*>(this + hazedumper::netvars::m_lifeState);
}

vec3 Ent::GetVecOrigin()
{
    return *reinterpret_cast<vec3*>(this + hazedumper::netvars::m_vecOrigin);
}

vec3 Ent::GetVecVeloctiy()
{
    return *reinterpret_cast<vec3*>(this + hazedumper::netvars::m_vecVelocity);
}

int Ent::GetCrosshairId()
{
    return *reinterpret_cast<int*>(this + hazedumper::netvars::m_iCrosshairId);
}

int Ent::GetWeaponIndex()
{
    //TO DO 
    return 0;
}

bool Ent::Dormant()
{
    return *reinterpret_cast<int*>(this + hazedumper::signatures::m_bDormant);
}

int Ent::ShotsFired()
{
    return *reinterpret_cast<int*>(this + hazedumper::netvars::m_iShotsFired);
}

int Ent::GlowIndex()
{
    return *reinterpret_cast<int*>(this + hazedumper::netvars::m_iGlowIndex);
}

bool Ent::IsDefusing()
{
    return *reinterpret_cast<bool*>(this + hazedumper::netvars::m_bIsDefusing);
}

bool Ent::IsSpotted()
{
    return *reinterpret_cast<bool*>(this + hazedumper::netvars::m_bSpotted);
}

bool Ent::IsAlive()
{
    return (this->GetLifeState() == LIFEALIVE) ? true : false;
}

void Ent::ParseEnt(std::vector<Ent>* vec)
{
    if (this == nullptr)
        return;
    vec->push_back(*this);
}

void LocalPlayer::ForceAttack(int delay)
{
    uintptr_t* forceAttack = reinterpret_cast<uintptr_t*>(modules::clientModule + hazedumper::signatures::dwForceAttack);
    Sleep(delay);
    *forceAttack = 5;
    Sleep(20);
    *forceAttack = 4;
}
