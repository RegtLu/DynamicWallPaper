//
// Created by Regt on 25-9-16.
//

#ifndef MINHOOKDLL_H
#define MINHOOKDLL_H

#include <Windows.h>
#include <stdexcept>
#include <string>
#include <iostream>

class MinHookDLL {
public:
    typedef int (WINAPI *MH_INITIALIZE)();

    typedef int (WINAPI *MH_UNINITIALIZE)();

    typedef int (WINAPI *MH_CREATEHOOK)(LPVOID, LPVOID, LPVOID *);

    typedef int (WINAPI *MH_ENABLEHOOK)(LPVOID);

    typedef int (WINAPI *MH_DISABLEHOOK)(LPVOID);

    typedef int (WINAPI *MH_REMOVEHOOK)(LPVOID);

    typedef const char * (WINAPI *MH_STATUSTOSTRING)(int);

    MH_INITIALIZE Initialize = nullptr;
    MH_UNINITIALIZE Uninitialize = nullptr;
    MH_CREATEHOOK CreateHook = nullptr;
    MH_ENABLEHOOK EnableHook = nullptr;
    MH_DISABLEHOOK DisableHook = nullptr;
    MH_REMOVEHOOK RemoveHook = nullptr;
    MH_STATUSTOSTRING StatusToString = nullptr;

    explicit MinHookDLL(const std::string &dllPath) {
        hModule = LoadLibraryA(dllPath.c_str());
        if (!hModule) throw std::runtime_error("Failed to load DLL: " + dllPath);
        Initialize = (MH_INITIALIZE) GetProcAddress(hModule, "MH_Initialize");
        Uninitialize = (MH_UNINITIALIZE) GetProcAddress(hModule, "MH_Uninitialize");
        CreateHook = (MH_CREATEHOOK) GetProcAddress(hModule, "MH_CreateHook");
        EnableHook = (MH_ENABLEHOOK) GetProcAddress(hModule, "MH_EnableHook");
        DisableHook = (MH_DISABLEHOOK) GetProcAddress(hModule, "MH_DisableHook");
        RemoveHook = (MH_REMOVEHOOK) GetProcAddress(hModule, "MH_RemoveHook");
        StatusToString = (MH_STATUSTOSTRING) GetProcAddress(hModule, "MH_StatusToString");
        if (!Initialize || !Uninitialize || !CreateHook || !EnableHook || !DisableHook || !RemoveHook || !
            StatusToString) {
            FreeLibrary(hModule);
            throw std::runtime_error("Failed to load function from DLL");
        }
    }

    ~MinHookDLL() {
        if (hModule) FreeLibrary(hModule);
    }

private:
    HMODULE hModule = nullptr;
};

#endif //MINHOOKDLL_H
