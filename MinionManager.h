#pragma once

#include "Offsets.h"
#include "Vector.h"
#include "Utils.h"
#include <regex>
#include <string>
#include "Globals.h"

class CMinionManager {
public:

	Object* getMinionByIndex(int index) {
		return reinterpret_cast<Object*>(Globals::MinionList[index]);
	}
};
extern CMinionManager* MinionManager;

class Spells {
public:
	static Spell* getSpellByIndex(int index) {
		return (Spell*)*reinterpret_cast<uint64_t*>(Globals::localPlayer + Offsets::ObjSpellBook + Offsets::SpellInstance + (0x8 * index));
	}
};