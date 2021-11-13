#pragma once
#include "pch.h"

constexpr auto MAXPLAYERS = 64;
constexpr auto LIFEALIVE = 0;

namespace modules {
	static DWORD clientModule = (DWORD)GetModuleHandle(L"client.dll");
	static DWORD engineModule = (DWORD)GetModuleHandle(L"engine.dll");
}