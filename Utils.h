#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include "Offsets.h"
#include <fstream>
#include "Globals.h"
#include "Object.h"
#include "MinionManager.h"
#include <sstream>

std::string ReadString(void* dst, void* addr, int length);

float GetSmiteDamage();

int GetSmiteSlot();

uint64_t GetPointerAddress(uint64_t ptr, std::vector<uint64_t> offsets);

bool IsPointOnScreen(Vector2 pos);

std::string intToString(uint64_t inputint);

void logToFile(std::ofstream& file, std::string message);

void fninit();