#include <windows.h>
#include <stdint.h>
#include <string.h>

static BOOL patch_xgameruntime(HMODULE self_module, DWORD reason) {
    if (reason != DLL_PROCESS_ATTACH) {
        return TRUE;
    }
    
    DisableThreadLibraryCalls(self_module);
    
    HMODULE target = GetModuleHandleA("xgameruntime.dll");
    if (target == NULL) {
        target = LoadLibraryA("xgameruntime.dll");
        if (target == NULL) {
            return TRUE;
        }
    }
    
    uint8_t *base = (uint8_t *)target;
    int32_t pe_off = *(int32_t *)(base + 0x3C);
    uint32_t size_of_image = *(uint32_t *)(base + pe_off + 0x50);
    
    if (size_of_image <= 7) {
        return TRUE;
    }
    
    for (uint32_t i = 0; i < size_of_image - 7; ++i) {
        char *p = (char *)(base + i);
        
        if (memcmp(p, "isTrial", 8) != 0) {
            continue;
        }
        
        DWORD old_protect = 0;
        if (!VirtualProtect(p, 7, PAGE_READWRITE, &old_protect)) {
            continue;
        }
        
        memcpy(p, "xzNope", 7);
        VirtualProtect(p, 7, old_protect, &old_protect);
    }
    
    return TRUE;
}

BOOL WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    (void)reserved;
    return patch_xgameruntime(module, reason);
}