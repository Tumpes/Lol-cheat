#include "SigScan.h"

uint64_t GetAddressFromSignature(std::vector<int> signature, uint64_t startaddress, uint64_t endaddress) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if (startaddress == 0) {
        startaddress = (uint64_t)(si.lpMinimumApplicationAddress);
    }
    if (endaddress == 0) {
        endaddress = (uint64_t)(si.lpMaximumApplicationAddress);
    }

    MEMORY_BASIC_INFORMATION mbi{ 0 };
    uint64_t protectflags = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

    for (uint64_t i = startaddress; i < endaddress - signature.size(); i++) {
        //std::cout << "scanning: " << std::hex << i << std::endl;
        if (VirtualQuery((LPCVOID)i, &mbi, sizeof(mbi))) {
            if (mbi.Protect & protectflags || !(mbi.State & MEM_COMMIT)) {
                i += mbi.RegionSize;
                continue; // if bad adress then dont read from it
            }
           for (uint64_t k = (uint64_t)mbi.BaseAddress; k < (uint64_t)mbi.BaseAddress + mbi.RegionSize - signature.size(); k++) {
                for (uint64_t j = 0; j < signature.size(); j++) {
                    if (signature.at(j) != -1 && signature.at(j) != *(byte*)(k + j))
                        break;
                    if (j + 1 == signature.size())
                        return k;
                }
            }
            i = (uint64_t)mbi.BaseAddress + mbi.RegionSize;
        }
    }
    return NULL;
}