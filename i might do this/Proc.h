#pragma once
#include "pch.h"

DWORD GetProcId(const wchar_t* procName);
uintptr_t GetModuleBase(DWORD procId,const wchar_t* procName);


