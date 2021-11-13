// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Menu.h"
#include "TriggerBot.h"
#include "Glow.h"
#include "icliententitylist.h"


uintptr_t exitKey = VK_END;
uintptr_t triggerBot = VK_F1;
uintptr_t bHop = VK_F2;
uintptr_t glow = VK_F3;

bool bTrigger = false, bGlow = false;

DWORD WINAPI HackThread(HMODULE hModule) {
    menu::run();


    while (!GetAsyncKeyState(exitKey)) {
        if (GetAsyncKeyState(triggerBot) & 1) { bTrigger = !bTrigger; }
        if (GetAsyncKeyState(bHop) & 1) { bHop = !bHop; }
        if (GetAsyncKeyState(glow) & 1) { glow = !glow; }

        if (bTrigger) { RunTriggerBot(); }
        if (bGlow) { RunGlow(); }
        if (bHop) { //RunBHop(); }
    }
   
    menu::disable();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        HANDLE hThread = nullptr;
        hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL);
        if (hThread)
            CloseHandle(hThread);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

