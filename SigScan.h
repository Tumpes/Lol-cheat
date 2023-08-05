#pragma once

#include <vector>
#include <cstdint>
#include <Windows.h>
#include <psapi.h>

uint64_t GetAddressFromSignature(std::vector<int> signature, uint64_t startaddress = 0, uint64_t endaddress = 0);