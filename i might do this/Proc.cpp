#include "Proc.h"
#include "pch.h"

DWORD GetProcId(const wchar_t* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(hSnap, &pe32)) {

            do {
                if (_wcsicmp(pe32.szExeFile, procName)) {
                    procId = pe32.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &pe32));
        }
        CloseHandle(hSnap);
    }
    return procId;
}

uintptr_t GetModuleBase(DWORD procId,const wchar_t* procName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 mo32;
        mo32.dwSize = sizeof(PROCESSENTRY32);

        if (Module32First(hSnap, &mo32)) {

            do {
                if (_wcsicmp(mo32.szModule, procName)) {
                    modBaseAddr = (uintptr_t)mo32.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &mo32));
        }
        CloseHandle(hSnap);
    }
    return modBaseAddr;
}