#pragma once
#include "pch.h"


class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual void* GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(int hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(int hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual void* GetClientEntity(int entnum) = 0;
	virtual void* GetClientEntityFromHandle(int hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};

typedef void* (__cdecl* tcreateInterface)(const char* name, int* returnCode);

void* Getinterface(const wchar_t* dllname, const char* interfacename) {
	HMODULE hMod = GetModuleHandle(dllname);
	if (!hMod)
		return nullptr;
	tcreateInterface CreateInterface = (tcreateInterface)GetProcAddress(hMod, "CreateInterface");
	if (CreateInterface == nullptr)
		return nullptr;

	int returnCode = 0;
	void* interface = CreateInterface(interfacename, &returnCode);
	if (interface == nullptr)
		return nullptr;

	return interface;
}
